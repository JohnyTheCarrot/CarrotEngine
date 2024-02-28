#include "TextureComponent.h"
#include "../GameObject.h"
#include "../Renderer.h"
#include "../ResourceManager.h"

namespace dae {
	TextureComponent::TextureComponent(Component::Parent pParent, std::string_view fileName)
	    : Component{pParent}
	    , m_Texture{ResourceManager::GetInstance().LoadTexture(fileName)} {
	}

	TextureComponent::TextureComponent(Component::Parent pParent, Texture2D &&texture)
	    : Component{pParent}
	    , m_Texture{std::move(texture)} {
	}

	void TextureComponent::OnRender() const {
		const auto &pos{GetGameObject()->m_Transform.GetPosition()};
		Renderer::GetInstance().RenderTexture(m_Texture, pos.x, pos.y);
	}

	void TextureComponent::OnUpdate() {
	}

	void TextureComponent::OnFixedUpdate() {
	}
}// namespace dae
