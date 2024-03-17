#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Command/Command.h"
#include "ControllerInput.h"
#include "Singleton.h"
#include <variant>
#include <vector>

namespace dae {
	struct RegisteredCommand {
		enum class StickAxisValue {
			Positive,
			Neutral,
			Negative,
		};

		struct RightStickValue {
			StickAxisValue x{StickAxisValue::Neutral};
			StickAxisValue y{StickAxisValue::Neutral};
		};

		struct LeftStickValue {
			StickAxisValue x{StickAxisValue::Neutral};
			StickAxisValue y{StickAxisValue::Neutral};
		};

		struct Key {
			int  key;
			bool pressed{true};
		};

		using Input = std::variant<Key, DWORD, RightStickValue, LeftStickValue>;

		Input                    input;
		std::unique_ptr<Command> command;
	};

	class InputManager final : public Singleton<InputManager> {
	public:
		bool ProcessInput();

		void AddCommand(RegisteredCommand::Input input, std::unique_ptr<Command> command);

		void HandleLeftStickValue(const RegisteredCommand &command);

		void HandleRightStickValue(const RegisteredCommand &command);

	private:
		ControllerInput                m_ControllerInput;
		std::vector<RegisteredCommand> m_Commands;
	};

}// namespace dae

#endif
