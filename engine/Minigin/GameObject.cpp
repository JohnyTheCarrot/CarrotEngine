#include "GameObject.h"
#include "Components/TransformComponent.h"
#include "Scene.h"
#include "SceneManager.h"

namespace dae {
	void GameObject::MoveHelper(GameObject &&other) noexcept {
		SetGameObjectPtr(this);
		m_pParent  = other.m_pParent;
		m_Children = std::move(other.m_Children);
		m_Handle   = other.m_Handle;

		for (auto pChild: m_Children) { pChild->m_pParent = this; }

		if (m_pParent == nullptr)
			return;

		const auto oldChild{std::find_if(
		        m_pParent->m_Children.begin(), m_pParent->m_Children.end(),
		        [&](auto childPtr) { return childPtr == &other; }
		)};

		if (oldChild != m_pParent->m_Children.end())
			*oldChild = this;
	}

	GameObject::GameObject(GameObject &&other) noexcept
	    : ComponentStore<Component>{std::move(other)} {
		MoveHelper(std::move(other));
	}

	GameObject &GameObject::operator=(GameObject &&other) noexcept {
		if (&other == this)
			return *this;

		// TODO: discuss safety of these moves in class
		ComponentStore<Component>::operator=(std::move(other));
		MoveHelper(std::move(other));

		return *this;
	}

	NonOwningPtrMut<GameObject> GameObject::GetParentPtr() const noexcept {
		return m_pParent;
	}

	void GameObject::SetParent(NonOwningPtrMut<GameObject> pParent, bool keepWorldPosition) {
		if (pParent == m_pParent || HasAsChildRecursively(pParent))
			return;

		if (m_pParent != nullptr)
			std::erase(m_pParent->m_Children, this);

		m_pParent = pParent;
		const auto transCompPtr{GetComponent<TransformComponent>()};
		if (transCompPtr) {
			transCompPtr->SetParentGameObjectPtr(pParent);

			if (pParent != nullptr) {
				const auto parentTransCompPtr{pParent->GetComponent<TransformComponent>()};
				if (parentTransCompPtr == nullptr)
					throw std::runtime_error{"SetParent: parent has no transform!"};

				glm::vec2 newLocal{parentTransCompPtr->GetWorldPosition()};
				if (keepWorldPosition)
					newLocal -= transCompPtr->GetWorldPosition();

				transCompPtr->SetLocalPosition(newLocal);
			}
		}

		if (pParent == nullptr) {
			return;
		}

		m_pParent->m_Children.emplace_back(this);
	}

	GameObject::Handle GameObject::GetHandle() const noexcept {
		return m_Handle;
	}

	void GameObject::SetParent(GameObject::Handle parentHandle) {
		if (parentHandle == m_Handle)
			return;

		Scene &currentScene{SceneManager::GetInstance().GetCurrentScene()};
		auto   go{currentScene.FindGameObject(parentHandle)};
		if (go == nullptr)
			throw std::runtime_error{"GameObject handle does not refer to an existing GameObject."};

		SetParent(go, false);
	}

	const GameObject::Children &GameObject::GetChildren() const noexcept {
		return m_Children;
	}

	bool GameObject::HasAsChildRecursively(NonOwningPtr<GameObject> pChildToFind) {
		if (pChildToFind == this)
			return true;

		return std::find_if(
		               pChildToFind->m_Children.cbegin(), pChildToFind->m_Children.cend(),
		               [pChildToFind](auto pChild) { return pChild->HasAsChildRecursively(pChildToFind); }
		       ) != pChildToFind->m_Children.cend();
	}
}// namespace dae
