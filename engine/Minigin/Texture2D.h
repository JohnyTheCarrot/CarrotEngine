#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glm/vec2.hpp>

struct SDL_Texture;

namespace dae {
	/**
     * Simple RAII wrapper for an SDL_Texture
     */
	class Texture2D final {
	public:
		[[nodiscard]]
		SDL_Texture *GetSDLTexture() const;

		explicit Texture2D(SDL_Texture *texture);

		~Texture2D();

		[[nodiscard]]
		glm::ivec2 GetSize() const;

		Texture2D(const Texture2D &) = delete;

		Texture2D(Texture2D &&) noexcept;

		Texture2D &operator=(const Texture2D &) = delete;

		Texture2D &operator=(Texture2D &&) noexcept;

	private:
		SDL_Texture *m_Texture;
	};
}// namespace dae

#endif
