#ifndef COMPONENTSTORE_H
#define COMPONENTSTORE_H

#include "Util/PointerAliases.h"
#include <algorithm>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace dae {
	class GameObject;

	template<class TItem>
	class ComponentStore {
		std::unordered_map<std::string_view, OwningPtr<TItem>> m_ComponentStore{};

		template<std::derived_from<TItem> TComponent>
		void RegisterComponent(OwningPtr<TComponent> &&pComponent) {
			m_ComponentStore.emplace(typeid(TComponent).name(), std::move(pComponent));
		}

		NonOwningPtrMut<GameObject> m_pGameObject{};

	protected:
		void SetGameObjectPtr(NonOwningPtrMut<GameObject> pGameObject) {
			for (auto &item: m_ComponentStore) { item.second->SetGameObjectPtr(pGameObject); }
			m_pGameObject = pGameObject;
		}

	public:
		template<
		        std::derived_from<TItem> TComponent, class... Args,
		        std::enable_if_t<std::is_constructible_v<TComponent, NonOwningPtrMut<GameObject>, Args &&...>, bool> =
		                true>
		NonOwningPtrMut<TComponent> AddComponent(Args &&...args) {
			if (const auto existingComponent{GetComponent<TComponent>()}; existingComponent != nullptr) {
				return existingComponent;
			}

			auto pComponent{std::make_unique<TComponent>(m_pGameObject, std::forward<Args>(args)...)};

			auto result{pComponent.get()};
			RegisterComponent(std::move(pComponent));

			return result;
		}

		template<std::derived_from<TItem> TComponent>
		[[nodiscard]]
		NonOwningPtrMut<TComponent> GetComponent() const {
			if (const auto compIt{m_ComponentStore.find(typeid(TComponent).name())}; compIt != m_ComponentStore.end())
				return dynamic_cast<NonOwningPtrMut<TComponent>>(compIt->second.get());

			return nullptr;
		}

		template<std::derived_from<TItem> TComponent>
		void RemoveComponent() {
			if (const auto compIt{m_ComponentStore.find(typeid(TComponent).name())}; compIt != m_ComponentStore.end()) {
				if (compIt->second->GetIsDependency())
					return;

				m_ComponentStore.erase(compIt);
			}
		}

		void RemoveComponent(NonOwningPtr<TItem> pComponent) {
			const auto &it{std::find_if(
			        m_ComponentStore.begin(), m_ComponentStore.end(),
			        [=](const auto &keyValuePair) { return keyValuePair.second.get() == pComponent; }
			)};

			m_ComponentStore.erase(it);
		}

		void UpdateComponents() {
			for (auto &pair: m_ComponentStore) { pair.second->Update(); }
		}

		void FixedUpdateComponents() {
			for (auto &pair: m_ComponentStore) { pair.second->FixedUpdate(); }
		}

		void RenderComponents() const {
			for (const auto &pair: m_ComponentStore) { pair.second->Render(); }
		}

		explicit ComponentStore(NonOwningPtrMut<GameObject> pGameObject)
		    : m_pGameObject{pGameObject} {
		}

		[[nodiscard]]
		NonOwningPtrMut<GameObject> GetGameObject() const noexcept {
			return m_pGameObject;
		}

		ComponentStore(const ComponentStore &)            = delete;
		ComponentStore &operator=(const ComponentStore &) = delete;

		ComponentStore(ComponentStore &&other) noexcept
		    : m_ComponentStore{std::move(other.m_ComponentStore)}
		    , m_pGameObject{other.m_pGameObject} {
			for (const auto &component: m_ComponentStore) { component.second->m_pGameObject = m_pGameObject; }
			other.m_pGameObject = nullptr;
		}

		ComponentStore &operator=(ComponentStore &&other) noexcept {
			if (&other == this)
				return *this;

			m_ComponentStore = std::move(other.m_ComponentStore);
			m_pGameObject    = other.m_pGameObject;
			for (const auto &component: m_ComponentStore) { component.second->m_pGameObject = m_pGameObject; }
			other.m_pGameObject = nullptr;

			return *this;
		}
	};
}// namespace dae

#endif//COMPONENTSTORE_H
