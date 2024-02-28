#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include <functional>

namespace dae {
	class Scene final {
		std::string             m_Name;
		std::vector<GameObject> m_Objects{};

		static unsigned int m_IdCounter;

	public:
		template<std::convertible_to<std::string> TStr>
		explicit Scene(TStr &&name)
		    : m_Name{std::forward<TStr>(name)} {
		}

		void Add(const std::function<void(GameObject &)> &setup);

		void RemoveAll();

		void Update();

		void FixedUpdate();

		void Render() const;
	};

}// namespace dae

#endif
