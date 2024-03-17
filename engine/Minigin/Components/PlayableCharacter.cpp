#include "PlayableCharacter.h"
#include "Command/ControllerCommands.h"
#include "GameObject.h"
#include "GameTime.h"
#include "InputManager.h"
#include "SDL_keycode.h"
#include "TextureComponent.h"
#include "TransformComponent.h"

namespace dae {
	PlayableCharacter::PlayableCharacter(
	        Parent pParent, std::string_view textureFileName, float width, float height, float speed
	)
	    : Component{pParent}
	    , m_Speed{speed}
	    , m_pTransformComponent{pParent->GetComponent<TransformComponent>()} {
		AddComponent<TextureComponent>(TextureSize{width, height}, textureFileName);
	}

	void PlayableCharacter::OnRender() {
	}

	void PlayableCharacter::OnUpdate() {
	}

	void PlayableCharacter::OnFixedUpdate() {
	}

	void PlayableCharacter::Move(float x, float y) {
		const float actualSpeed = m_Speed * GameTime::GetInstance().GetDeltaTime();

		m_pTransformComponent->Translate(x * actualSpeed, y * actualSpeed);
	}

	void PlayableCharacter::RegisterControllerCommands() {
		InputManager::GetInstance().AddCommand(
		        RegisteredCommand::LeftStickValue{.x = RegisteredCommand::StickAxisValue::Positive},
		        std::make_unique<ControllerCommand<Movement::Positive, Movement::Neutral>>(GetGameObject(), this)
		);
		InputManager::GetInstance().AddCommand(
		        RegisteredCommand::LeftStickValue{.x = RegisteredCommand::StickAxisValue::Negative},
		        std::make_unique<ControllerCommand<Movement::Negative, Movement::Neutral>>(GetGameObject(), this)
		);
		InputManager::GetInstance().AddCommand(
		        RegisteredCommand::LeftStickValue{.y = RegisteredCommand::StickAxisValue::Negative},
		        std::make_unique<ControllerCommand<Movement::Neutral, Movement::Positive>>(GetGameObject(), this)
		);
		InputManager::GetInstance().AddCommand(
		        RegisteredCommand::LeftStickValue{.y = RegisteredCommand::StickAxisValue::Positive},
		        std::make_unique<ControllerCommand<Movement::Neutral, Movement::Negative>>(GetGameObject(), this)
		);
	}

	void PlayableCharacter::RegisterKeyboardCommands() {
		InputManager::GetInstance().AddCommand(
		        RegisteredCommand::Key{SDL_SCANCODE_A},
		        std::make_unique<ControllerCommand<Movement::Negative, Movement::Neutral>>(GetGameObject(), this)
		);
		InputManager::GetInstance().AddCommand(
		        RegisteredCommand::Key{SDL_SCANCODE_D},
		        std::make_unique<ControllerCommand<Movement::Positive, Movement::Neutral>>(GetGameObject(), this)
		);
		InputManager::GetInstance().AddCommand(
		        RegisteredCommand::Key{SDL_SCANCODE_W},
		        std::make_unique<ControllerCommand<Movement::Neutral, Movement::Negative>>(GetGameObject(), this)
		);
		InputManager::GetInstance().AddCommand(
		        RegisteredCommand::Key{SDL_SCANCODE_S},
		        std::make_unique<ControllerCommand<Movement::Neutral, Movement::Positive>>(GetGameObject(), this)
		);
	}
}// namespace dae
