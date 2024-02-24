#include "TextObject.h"
#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include <stdexcept>

dae::TextObject::TextObject(const std::string &text, std::shared_ptr<Font> font)
    : m_NeedsUpdate(true)
    , m_Text(text)
    , m_Font(std::move(font))
    , m_TextTexture(nullptr) {
}

void dae::TextObject::Update() {
	if (!m_NeedsUpdate) {
		return;
	}

	const SDL_Color color{255, 255, 255, 255};// only white text is supported now
	const auto      surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr) {
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}

	const auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);

	SDL_FreeSurface(surf);

	if (texture == nullptr) {
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}

	m_TextTexture = std::make_shared<Texture2D>(texture);
	m_NeedsUpdate = false;
}

void dae::TextObject::Render() const {
	if (m_TextTexture != nullptr) {
		const auto &pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextObject::SetText(const std::string &text) {
	m_Text        = text;
	m_NeedsUpdate = true;
}

void dae::TextObject::SetPosition(const float x, const float y) {
	m_Transform.SetPosition(x, y, 0.0f);
}
