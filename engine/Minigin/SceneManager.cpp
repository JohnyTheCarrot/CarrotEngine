#include "SceneManager.h"

namespace dae {
	void SceneManager::Update() {
		for (auto &scene: m_Scenes) { scene.Update(); }
	}

	void SceneManager::FixedUpdate() {
		for (auto &scene: m_Scenes) { scene.FixedUpdate(); }
	}

	void SceneManager::Render() {
		for (const auto &scene: m_Scenes) { scene.Render(); }
	}
}// namespace dae
