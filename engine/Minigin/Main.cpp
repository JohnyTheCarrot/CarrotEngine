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
#include "Minigin.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"

#include <filesystem>

namespace fs = std::filesystem;
using namespace dae;

void load() {
	auto font{ResourceManager::GetInstance().LoadFont("Lingua.otf", 36)};

	auto &scene = SceneManager::GetInstance().CreateScene("Demo");

	scene.Add([](GameObject &gameObject) {
		gameObject.AddComponent<TransformComponent>(0.f, 0.f);
		gameObject.AddComponent<TextureComponent>("background.tga");
	});

	//	scene.Add([](GameObject &gameObject) {
	//		gameObject.AddComponent<TransformComponent>(216.f, 180.f);
	//		gameObject.AddComponent<TextureComponent>("logo.tga");
	//	});

	scene.Add([=](GameObject &gameObject) {
		gameObject.AddComponent<TransformComponent>(80.f, 20.f);
		gameObject.AddComponent<FpsComponent>(font);
	});

	GameObject::Handle centerPog{scene.Add([=](GameObject &gameObject) {
		gameObject.AddComponent<TransformComponent>(216.f, 180.f);
		gameObject.AddComponent<TextComponent>(font, "pog");
	})};

	GameObject::Handle lastPog{centerPog};

	for (int num{0}; num < 25; ++num) {
		lastPog = scene.Add([=](GameObject &gameObject) {
			gameObject.AddComponent<TransformComponent>(500.f, 0.f)->Scale(0.1f);
			gameObject.AddComponent<TextureComponent>("cat_stare.jpg");
			gameObject.AddComponent<RotatorComponent>(static_cast<float>(num) * 25.f);
			gameObject.SetParent(lastPog);
		});
	}
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
