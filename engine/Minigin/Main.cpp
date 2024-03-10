#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Components/FpsComponent.h"
#include "Components/RotatorComponent.h"
#include "Components/TextComponent.h"
#include "Components/TextureComponent.h"
#include "Components/TransformComponent.h"
#include "Components/TrashTheCache.h"
#include "Minigin.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"

#include <filesystem>

namespace fs = std::filesystem;
using namespace dae;

class IntTrashTheCache {
public:
	IntTrashTheCache()
	    : m_Vec(1'000'000) {
		for (auto &val: m_Vec) val = 13;
	}

	void operator()(int stepSize) {
		for (int i{0}; i < m_Vec.size(); i += stepSize) { m_Vec[i] *= 2; }
	}

private:
	std::vector<int> m_Vec;
};

void load() {
	auto font{ResourceManager::GetInstance().LoadFont("Lingua.otf", 36)};

	auto &scene = SceneManager::GetInstance().CreateScene("Demo");

	scene.Add([](GameObject &gameObject) {
		gameObject.AddComponent<TransformComponent>(0.f, 0.f);
		gameObject.AddComponent<TextureComponent>("background.tga");
	});

	scene.Add([=](GameObject &gameObject) {
		gameObject.AddComponent<TransformComponent>(80.f, 20.f);
		gameObject.AddComponent<FpsComponent>(font);
	});

	scene.Add([=](GameObject &gameObject) {
		gameObject.AddComponent<TrashTheCache>(IntTrashTheCache(), "Exercise one");
	});
}

int main(int, char *[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
	return 0;
}
