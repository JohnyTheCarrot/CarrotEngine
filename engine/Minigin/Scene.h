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

		auto FindGameObject(GameObject::Handle handle) {
			return std::find_if(m_Objects.begin(), m_Objects.end(), [handle](const GameObject &gameObject) {
				return gameObject.GetHandle() == handle;
			});
		}

		void RemoveAll();

		void Update();

		void FixedUpdate();

		void Render() const;
	};

}// namespace dae

#endif
