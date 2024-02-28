#include "Scene.h"
#include "GameObject.h"

#include <utility>

namespace dae {
	unsigned int Scene::m_IdCounter = 0;

	void Scene::RemoveAll() {
		m_Objects.clear();
	}

	void Scene::Update() {
		for (auto &object: m_Objects) { object.UpdateComponents(); }
	}

	void Scene::FixedUpdate() {
		for (auto &object: m_Objects) { object.FixedUpdateComponents(); }
	}

	void Scene::Render() const {
		for (const auto &object: m_Objects) { object.RenderComponents(); }
	}

	void Scene::Add(const std::function<void(GameObject &)> &setup) {
		GameObject gameObject{};
		setup(gameObject);

		m_Objects.emplace_back(std::move(gameObject));
	}
}// namespace dae
