#include "TextComponent.h"
#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "SDL_ttf.h"
#include "TransformComponent.h"
#include <stdexcept>

namespace dae {
	TextComponent::TextComponent(Component::Parent pParent, const SharedOwningPtr<Font> &pFont, const std::string &text)
	    : Component{pParent}
	    , m_Texture{pFont.get(), text}
	    , m_pFont{pFont}
	    , m_pTransformComponent{pParent->GetComponent<TransformComponent>()} {
		if (m_pTransformComponent == nullptr)
			throw std::runtime_error("GameObject is missing a transform");
	}

	void TextComponent::OnRender() {
		Renderer::GetInstance().RenderTexture(
		        *m_Texture, m_pTransformComponent->GetWorldPosition().x, m_pTransformComponent->GetWorldPosition().y
		);
	}

	void TextComponent::OnUpdate() {
	}

	void TextComponent::OnFixedUpdate() {
	}

	Texture2D FontTextureUpdater::operator()(NonOwningPtr<Font> m_pFont, std::string_view text) {
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
}// namespace dae
