#include "TextureComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TransformComponent.h"

namespace dae {
	TextureComponent::TextureComponent(
	        Component::Parent pParent, const std::optional<TextureSize> &textureSize, std::string_view fileName
	)
	    : Component{pParent}
	    , m_Texture{ResourceManager::GetInstance().LoadTexture(fileName)}
	    , m_pTransformComponent{pParent->GetComponent<TransformComponent>()}
	    , m_Size{textureSize} {
		if (m_pTransformComponent == nullptr)
			throw std::runtime_error("GameObject is missing a transform");
	}

	TextureComponent::TextureComponent(Component::Parent pParent, Texture2D &&texture)
	    : Component{pParent}
	    , m_Texture{std::move(texture)}
	    , m_pTransformComponent{pParent->GetComponent<TransformComponent>()} {
		if (m_pTransformComponent == nullptr)
			throw std::runtime_error("GameObject is missing a transform");
	}

	void TextureComponent::OnRender() {
		const float x{m_pTransformComponent->GetWorldPosition().x};
		const float y{m_pTransformComponent->GetWorldPosition().y};

		if (m_Size.has_value())
			Renderer::GetInstance().RenderTexture(m_Texture, x, y, m_Size->width, m_Size->height);
		else
			Renderer::GetInstance().RenderTexture(m_Texture, x, y);
	}

	void TextureComponent::OnUpdate() {
	}

	void TextureComponent::OnFixedUpdate() {
	}
}// namespace dae
