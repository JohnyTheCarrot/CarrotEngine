#include "InputManager.h"
#include "imgui/imgui_impl_sdl2.h"
#include <SDL.h>

bool dae::InputManager::ProcessInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {}
		if (e.type == SDL_MOUSEBUTTONDOWN) {}
		// etc...
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}
