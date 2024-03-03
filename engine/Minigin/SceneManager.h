#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "Singleton.h"
#include "Util/PointerAliases.h"
#include <memory>
#include <string>
#include <vector>

namespace dae {
	class SceneManager final : public Singleton<SceneManager> {
	public:
		template<std::convertible_to<std::string> TStr>
		Scene &CreateScene(TStr &&name) {
			return m_Scenes.emplace_back(std::forward<TStr>(name));
		}

		void Update();

		void FixedUpdate();

		void Render();

		Scene &GetCurrentScene() noexcept;

	private:
		friend class Singleton<SceneManager>;

		SceneManager() = default;

		size_t             m_CurrentSceneIdx{};
		std::vector<Scene> m_Scenes{};
	};
}// namespace dae

#endif
