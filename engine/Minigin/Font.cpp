#include "Font.h"
#include <SDL_ttf.h>
#include <stdexcept>

TTF_Font *dae::Font::GetFont() const {
	return m_Font;
}

dae::Font::Font(std::string_view fullPath, unsigned int size)
    : m_Font{nullptr} {
	m_Font = TTF_OpenFont(fullPath.data(), size);
	if (m_Font == nullptr) {
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

dae::Font::~Font() {
	TTF_CloseFont(m_Font);
}
