#include "RotatorComponent.h"
#include "../GameObject.h"
#include "TransformComponent.h"

namespace dae {
	RotatorComponent::RotatorComponent(Component::Parent pGameObject, float rotationSpeed)
	    : Component(pGameObject)
	    , m_pTransformComponent{pGameObject->GetComponent<TransformComponent>()}
	    , m_RotationSpeed{rotationSpeed} {
		if (m_pTransformComponent == nullptr)
			throw std::runtime_error("GameObject is missing a transform");
	}

	void RotatorComponent::OnRender() {
	}

	void RotatorComponent::OnUpdate() {
		m_pTransformComponent->Rotate(glm::radians(m_RotationSpeed));
	}

	void RotatorComponent::OnFixedUpdate() {
	}
}// namespace dae
