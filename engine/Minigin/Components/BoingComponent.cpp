#include "BoingComponent.h"
#include "../GameObject.h"
#include "../GameTime.h"
#include "TransformComponent.h"

namespace dae {
	BoingComponent::BoingComponent(Component::Parent pGameObject, float amplitude)
	    : Component{pGameObject}
	    , m_pTransformComponent{pGameObject->GetComponent<TransformComponent>()}
	    , m_Amplitude{amplitude} {
	}

	void BoingComponent::OnRender() {
	}

	void BoingComponent::OnUpdate() {
		static float x{0.f};

		x += 1.0f * GameTime::GetInstance().GetDeltaTime();

		const float scaleX{std::abs(std::sinf(x)) + 1.f};
		const float scaleY{2.f / scaleX + 1.0f};

		m_pTransformComponent->Scale(scaleX, scaleY, 1.f);
	}

	void BoingComponent::OnFixedUpdate() {
	}
}// namespace dae
