#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Components/CounterComponent.h"
#include "Components/TextComponent.h"
#include "Components/TextureComponent.h"
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

	scene.Add([](GameObject &gameObject) { gameObject.AddComponent<TextureComponent>("background.tga"); });

	scene.Add([](GameObject &gameObject) {
		gameObject.AddComponent<TextureComponent>("logo.tga");
		gameObject.SetPosition(216, 180);
	});

	scene.Add([=](GameObject &gameObject) {
		gameObject.AddComponent<CounterComponent>(font);
		gameObject.SetPosition(80, 20);
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
