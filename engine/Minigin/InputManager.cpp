#include "InputManager.h"
#include "imgui/imgui_impl_sdl2.h"
#include <SDL.h>

namespace dae {
	bool InputManager::ProcessInput() {
		m_ControllerInput.ProcessInput();

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}

			ImGui_ImplSDL2_ProcessEvent(&e);
		}

		const uint8_t *pKeyboardState = SDL_GetKeyboardState(nullptr);

		for (const auto &command: m_Commands) {
			if (std::holds_alternative<RegisteredCommand::LeftStickValue>(command.input)) {
				HandleLeftStickValue(command);
			} else if (std::holds_alternative<RegisteredCommand::RightStickValue>(command.input)) {
				HandleRightStickValue(command);
			} else if (std::holds_alternative<DWORD>(command.input)) {
				DWORD buttonCode = std::get<DWORD>(command.input);
				if (m_ControllerInput.IsDown(buttonCode)) {
					command.command->Execute();
				}
			} else if (std::holds_alternative<RegisteredCommand::Key>(command.input)) {
				auto key{std::get<RegisteredCommand::Key>(command.input)};
				if (static_cast<bool>(pKeyboardState[key.key]) == key.pressed) {
					command.command->Execute();
				}
			}
		}

		return true;
	}

	void InputManager::AddCommand(RegisteredCommand::Input input, std::unique_ptr<Command> command) {
		m_Commands.emplace_back(input, std::move(command));
	}

	void InputManager::HandleLeftStickValue(const RegisteredCommand &command) {
		RegisteredCommand::LeftStickValue leftStickValue = std::get<RegisteredCommand::LeftStickValue>(command.input);

		bool stickLeft{
		        leftStickValue.x == RegisteredCommand::StickAxisValue::Negative && m_ControllerInput.GetLeftThumbX() < 0
		};
		bool stickRight{
		        leftStickValue.x == RegisteredCommand::StickAxisValue::Positive && m_ControllerInput.GetLeftThumbX() > 0
		};
		bool stickUp{
		        leftStickValue.y == RegisteredCommand::StickAxisValue::Positive && m_ControllerInput.GetLeftThumbY() > 0
		};
		bool stickDown{
		        leftStickValue.y == RegisteredCommand::StickAxisValue::Negative && m_ControllerInput.GetLeftThumbY() < 0
		};

		if (stickLeft || stickRight || stickUp || stickDown) {
			command.command->Execute();
		}
	}

	void InputManager::HandleRightStickValue(const RegisteredCommand &command) {
		RegisteredCommand::RightStickValue rightStickValue =
		        std::get<RegisteredCommand::RightStickValue>(command.input);
		bool stickLeft{
		        rightStickValue.x == RegisteredCommand::StickAxisValue::Negative &&
		        m_ControllerInput.GetRightThumbX() < 0
		};
		bool stickRight{
		        rightStickValue.x == RegisteredCommand::StickAxisValue::Positive &&
		        m_ControllerInput.GetRightThumbX() > 0
		};
		bool stickUp{
		        rightStickValue.y == RegisteredCommand::StickAxisValue::Positive &&
		        m_ControllerInput.GetRightThumbY() > 0
		};
		bool stickDown{
		        rightStickValue.y == RegisteredCommand::StickAxisValue::Negative &&
		        m_ControllerInput.GetRightThumbY() < 0
		};

		if (stickLeft || stickRight || stickUp || stickDown) {
			command.command->Execute();
		}
	}
}// namespace dae
