#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H

#include "Base/Component.h"

namespace dae {

	class TransformComponent;

	class PlayableCharacter final : public Component {
	public:
		PlayableCharacter(
		        Component::Parent pParent, std::string_view textureFileName, float width, float height, float speed
		);

		void RegisterControllerCommands();

		void RegisterKeyboardCommands();

		void OnRender() override;

		void OnUpdate() override;

		void OnFixedUpdate() override;

		void Move(float x, float y);

	private:
		NonOwningPtrMut<TransformComponent> m_pTransformComponent;
		float                               m_Speed;
	};

}// namespace dae

#endif//PLAYABLECHARACTER_H
