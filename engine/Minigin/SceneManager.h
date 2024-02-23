#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H


#include "Singleton.h"
#include <memory>
#include <string>
#include <vector>

namespace dae {
	class Scene;

	class SceneManager final : public Singleton<SceneManager> {
	public:
		Scene &CreateScene(const std::string &name);

		void Update();

		void Render();

	private:
		friend class Singleton<SceneManager>;

		SceneManager() = default;

		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}// namespace dae

#endif
