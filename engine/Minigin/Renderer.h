#ifndef RENDERER_H
#define RENDERER_H

#include "Singleton.h"
#include <SDL.h>

namespace dae {
	class Texture2D;

	class TransformComponent;

	/**
     * Simple RAII wrapper for the SDL renderer
     */
	class Renderer final : public Singleton<Renderer> {
		SDL_Renderer *m_Renderer{};
		SDL_Window   *m_Window{};
		SDL_Color     m_ClearColor{};

	public:
		void Init(SDL_Window *window);

		void Render() const;

		void Destroy();

		void RenderTexture(const Texture2D &texture, float x, float y) const;

		void RenderTexture(const Texture2D &texture, float x, float y, float width, float height) const;

		[[nodiscard]]
		SDL_Renderer *GetSDLRenderer() const;

		[[nodiscard]]
		const SDL_Color &GetBackgroundColor() const {
			return m_ClearColor;
		}

		void SetBackgroundColor(const SDL_Color &color) {
			m_ClearColor = color;
		}
	};
}// namespace dae

#endif
