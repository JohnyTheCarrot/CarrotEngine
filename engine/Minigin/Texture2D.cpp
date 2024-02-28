#include "Texture2D.h"
#include <SDL.h>

namespace dae {
	Texture2D::~Texture2D() {
		SDL_DestroyTexture(m_Texture);
	}

	glm::ivec2 Texture2D::GetSize() const {
		SDL_Rect dst;
		SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
		return {dst.w, dst.h};
	}

	SDL_Texture *Texture2D::GetSDLTexture() const {
		return m_Texture;
	}

	Texture2D::Texture2D(SDL_Texture *texture) {
		m_Texture = texture;
	}

	Texture2D::Texture2D(Texture2D &&other) noexcept
	    : m_Texture{other.m_Texture} {
		other.m_Texture = nullptr;
	}

	Texture2D &Texture2D::operator=(Texture2D &&other) noexcept {
		if (&other == this)
			return *this;

		m_Texture       = other.m_Texture;
		other.m_Texture = nullptr;

		return *this;
	}
}// namespace dae
