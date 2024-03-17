#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Components/FpsComponent.h"
#include "Components/PlayableCharacter.h"
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
		gameObject.AddComponent<TextureComponent>(std::nullopt, "background.tga");
	});

	scene.Add([=](GameObject &gameObject) {
		gameObject.AddComponent<TransformComponent>(80.f, 20.f);
		gameObject.AddComponent<FpsComponent>(font);
	});

	scene.Add([=](GameObject &gameObject) {
		gameObject.AddComponent<TransformComponent>(100.f, 100.f);
		gameObject.AddComponent<PlayableCharacter>("cat.jpg", 100.f, 100.f, 100.f)->RegisterControllerCommands();
	});

	scene.Add([=](GameObject &gameObject) {
		gameObject.AddComponent<TransformComponent>(150.f, 200.f);
		gameObject.AddComponent<PlayableCharacter>("cat_stare.jpg", 100.f, 100.f, 200.f)->RegisterKeyboardCommands();
	});
}

int main(int, char *[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
	return 0;
}
