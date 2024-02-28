#include "TextComponent.h"
#include "../GameObject.h"
#include "../Renderer.h"
#include "SDL_ttf.h"
#include <stdexcept>

namespace dae {
	Texture2D CreateTextTexture(const SharedOwningPtr<Font> &m_pFont, std::string_view text) {
		const SDL_Color color{255, 255, 255, 255};
		const auto      surface{TTF_RenderText_Blended(m_pFont->GetFont(), text.data(), color)};
		if (surface == nullptr) {
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}

		const auto texture{SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface)};

		SDL_FreeSurface(surface);

		if (texture == nullptr) {
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}

		return Texture2D{texture};
	}

	TextComponent::TextComponent(Component::Parent pParent, const SharedOwningPtr<Font> &pFont, std::string_view text)
	    : Component{pParent}
	    , m_pFont{pFont}
	    , m_Texture{CreateTextTexture(pFont, text)} {
	}

	void TextComponent::OnRender() const {
		const auto &pos{GetGameObject()->m_Transform.GetPosition()};
		Renderer::GetInstance().RenderTexture(m_Texture, pos.x, pos.y);
	}

	void TextComponent::OnUpdate() {
	}

	void TextComponent::OnFixedUpdate() {
	}

	void TextComponent::SetText(std::string_view text) {
		m_Texture = CreateTextTexture(m_pFont, text);
	}
}// namespace dae
