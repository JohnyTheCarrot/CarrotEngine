#include <iostream>
#include <sstream>
#include <stdexcept>

#if WIN32
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#endif

#include "GameTime.h"
#include "InputManager.h"
#include "Minigin.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Window *g_Window{};

void LogSDLVersion(const std::string &message, const SDL_version &v) {
#if WIN32
	std::stringstream ss;
	ss << message << (int) v.major << "." << (int) v.minor << "." << (int) v.patch << "\n";
	OutputDebugString(ss.str().c_str());
#else
	std::cout << message << (int) v.major << "." << (int) v.minor << "." << (int) v.patch << "\n";
#endif
}

#ifdef __EMSCRIPTEN__
#include "emscripten.h"

void LoopCallback(void *arg) {
	static_cast<dae::Minigin *>(arg)->RunOneFrame();
}
#endif

// Why bother with this? Because sometimes students have a different SDL version installed on their pc.
// That is not a problem unless for some reason the dll's from this project are not copied next to the exe.
// These entries in the debug output help to identify that issue.
void PrintSDLVersion() {
	SDL_version version{};
	SDL_VERSION(&version)
	LogSDLVersion("We compiled against SDL version ", version);

	SDL_GetVersion(&version);
	LogSDLVersion("We linked against SDL version ", version);

	SDL_IMAGE_VERSION(&version)
	LogSDLVersion("We compiled against SDL_image version ", version);

	version = *IMG_Linked_Version();
	LogSDLVersion("We linked against SDL_image version ", version);

	SDL_TTF_VERSION(&version)
	LogSDLVersion("We compiled against SDL_ttf version ", version);

	version = *TTF_Linked_Version();
	LogSDLVersion("We linked against SDL_ttf version ", version);
}

dae::Minigin::Minigin(const std::filesystem::path &dataPath) {
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_Window = SDL_CreateWindow(
	        "Programming 4 assignment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL
	);
	if (g_Window == nullptr) {
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_Window);
	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin() {
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_Window);
	g_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()> &load) {
	load();
#ifndef __EMSCRIPTEN__
	while (!m_Quit) RunOneFrame();
#else
	emscripten_set_main_loop_arg(&LoopCallback, this, 0, true);
#endif
}


#ifndef __EMSCRIPTEN__
void dae::Minigin::RunOneFrame() {
	GameTime &gameTime{GameTime::GetInstance()};
	gameTime.EndDeltaTimeMeasurement();
	gameTime.StartDeltaTimeMeasurement();

	static GameTimeDurationPrecision accumulator{0};

	accumulator += gameTime.GetDeltaTime();

	m_Quit = !InputManager::GetInstance().ProcessInput();

	while (accumulator >= GameTime::FIXED_TIME_DELTA) {
		accumulator -= GameTime::FIXED_TIME_DELTA;
		SceneManager::GetInstance().FixedUpdate();
	}

	SceneManager::GetInstance().Update();
	Renderer::GetInstance().Render();

	gameTime.Sleep();
}
#else
void dae::Minigin::RunOneFrame() {
	m_Quit = !InputManager::GetInstance().ProcessInput();
	SceneManager::GetInstance().Update();
	Renderer::GetInstance().Render();
}
#endif
