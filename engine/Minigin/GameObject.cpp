#include "GameObject.h"
#include "Components/TransformComponent.h"
#include "Scene.h"
#include "SceneManager.h"

namespace dae {
	GameObject::GameObject(GameObject &&other) noexcept
	    : ComponentStore<Component>{std::move(other)}
	    , m_pParent{other.m_pParent}
	    , m_Children{std::move(other.m_Children)}
	    , m_Handle{other.m_Handle} {
		SetGameObjectPtr(this);

		for (auto &pChild: m_Children) { pChild->m_pParent = this; }

		if (m_pParent == nullptr)
			return;

		const auto oldChild{std::find_if(
		        m_pParent->m_Children.begin(), m_pParent->m_Children.end(),
		        [&](auto childPtr) { return childPtr == &other; }
		)};

		if (oldChild != m_pParent->m_Children.end())
			*oldChild = this;
	}

	GameObject &GameObject::operator=(GameObject &&other) noexcept {
		if (&other == this)
			return *this;

		ComponentStore<Component>::operator=(std::move(other));
		SetGameObjectPtr(this);

		m_pParent  = other.m_pParent;
		m_Children = std::move(other.m_Children);
		m_Handle   = other.m_Handle;

		for (auto &pChild: m_Children) { pChild->m_pParent = this; }

		if (m_pParent == nullptr)
			return *this;

		const auto oldChild{std::find_if(
		        m_pParent->m_Children.begin(), m_pParent->m_Children.end(),
		        [&](auto childPtr) { return childPtr == &other; }
		)};

		if (oldChild != m_pParent->m_Children.end())
			*oldChild = this;

		return *this;
	}

	NonOwningPtrMut<GameObject> GameObject::GetParentPtr() const noexcept {
		return m_pParent;
	}

	void GameObject::SetParent(NonOwningPtrMut<GameObject> pParent) noexcept {
		if (pParent == m_pParent)
			return;

		if (m_pParent != nullptr)
			std::erase_if(m_pParent->m_Children, [this](auto childPtr) { return childPtr == this; });

		m_pParent = pParent;
		const auto transCompPtr{GetComponent<TransformComponent>()};
		if (transCompPtr)
			transCompPtr->SetParentGameObjectPtr(pParent);

		if (pParent == nullptr) {
			return;
		}

		m_pParent->m_Children.emplace_back(this);
	}

	GameObject::Handle GameObject::GetHandle() const noexcept {
		return m_Handle;
	}

	void GameObject::SetParent(GameObject::Handle parentHandle) noexcept {
		if (parentHandle == m_Handle)
			return;

		Scene &currentScene{SceneManager::GetInstance().GetCurrentScene()};
		SetParent(&*currentScene.FindGameObject(parentHandle));
	}
}// namespace dae
