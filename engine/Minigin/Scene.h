#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include <functional>

namespace dae {
	using GameObjectHandle = int;

	class Scene final {
		std::string             m_Name;
		std::vector<GameObject> m_Objects{};

		static unsigned int m_IdCounter;

	public:
		template<std::convertible_to<std::string> TStr>
		explicit Scene(TStr &&name)
		    : m_Name{std::forward<TStr>(name)} {
		}

		GameObject::Handle Add(const std::function<void(GameObject &)> &setup);

		NonOwningPtrMut<GameObject> FindGameObject(GameObject::Handle handle) {
			const auto goIt{std::find_if(m_Objects.begin(), m_Objects.end(), [handle](const GameObject &gameObject) {
				return gameObject.GetHandle() == handle;
			})};

			if (goIt == m_Objects.end())
				return nullptr;

			return &*goIt;
		}

		void RemoveAll();

		void Update();

		void FixedUpdate();

		void Render() const;
	};

}// namespace dae

#endif
