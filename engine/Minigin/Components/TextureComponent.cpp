#include "TextureComponent.h"
#include "../GameObject.h"
#include "../Renderer.h"
#include "../ResourceManager.h"
#include "TransformComponent.h"

namespace dae {
	TextureComponent::TextureComponent(Component::Parent pParent, std::string_view fileName)
	    : Component{pParent}
	    , m_Texture{ResourceManager::GetInstance().LoadTexture(fileName)}
	    , m_pTransformComponent{pParent->GetComponent<TransformComponent>()} {
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
		Renderer::GetInstance().RenderTexture(m_Texture, *m_pTransformComponent);
	}

	void TextureComponent::OnUpdate() {
	}

	void TextureComponent::OnFixedUpdate() {
	}
}// namespace dae
