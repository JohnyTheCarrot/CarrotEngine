#ifndef ROTATORCOMPONENT_H
#define ROTATORCOMPONENT_H

#include "Base/Component.h"

namespace dae {

	class RotatorComponent final : public Component {
		NonOwningPtrMut<class TransformComponent> m_pTransformComponent;
		float                                     m_RotationSpeed{};

	public:
		RotatorComponent(Component::Parent pGameObject, float rotationSpeed);

		void OnRender() override;

		void OnUpdate() override;

		void OnFixedUpdate() override;
	};

}// namespace dae

#endif//ROTATORCOMPONENT_H
