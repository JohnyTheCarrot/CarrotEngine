#include "Renderer.h"
#include "Components/TransformComponent.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include <cstring>
#include <stdexcept>

int GetOpenGLDriverIndex() {
	auto       openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++) {
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window *window) {
	m_Window   = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_Renderer == nullptr) {
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void dae::Renderer::Render() const {
	const auto &color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy() {
	if (m_Renderer != nullptr) {
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D &texture, float x, float y) const {
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D &texture, float x, float y, float width, float height) const {
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer *dae::Renderer::GetSDLRenderer() const {
	return m_Renderer;
}

void dae::Renderer::RenderTexture(const Texture2D &texture, TransformComponent &transform) const {
	const auto  scale{transform.GetScale()};
	const auto &pos{transform.GetWorldPosition()};

	SDL_Rect dst{};
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.w = static_cast<int>(static_cast<float>(dst.w) * scale.x);
	dst.h = static_cast<int>(static_cast<float>(dst.h) * scale.y);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}
