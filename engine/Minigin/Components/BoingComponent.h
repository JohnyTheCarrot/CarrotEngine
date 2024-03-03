#ifndef BOINGCOMPONENT_H
#define BOINGCOMPONENT_H

#include "Base/Component.h"

namespace dae {

	class BoingComponent final : public Component {
		NonOwningPtrMut<class TransformComponent> m_pTransformComponent;
		float                                     m_Amplitude{};

	public:
		BoingComponent(Component::Parent pGameObject, float amplitude);

		void OnRender() override;

		void OnUpdate() override;

		void OnFixedUpdate() override;
	};

}// namespace dae

#endif//BOINGCOMPONENT_H
