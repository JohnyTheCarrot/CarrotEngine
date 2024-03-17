#include "ControllerInput.h"

namespace dae {
	class ControllerInput::Impl {
		XINPUT_STATE m_CurrentState{};
		XINPUT_STATE m_PreviousState{};
		DWORD        m_ControllerId{};
		DWORD        m_ButtonsPressed{};
		DWORD        m_ButtonsReleased{};
		SHORT        m_LeftThumbX{};
		SHORT        m_LeftThumbY{};
		SHORT        m_RightThumbX{};
		SHORT        m_RightThumbY{};

	public:
		[[nodiscard]]
		bool IsDown(DWORD buttonCode) const {
			return (m_ButtonsPressed & buttonCode) == buttonCode;
		}

		[[nodiscard]]
		SHORT GetLeftThumbX() const {
			if (m_LeftThumbX > GetLeftDeadzone() || m_LeftThumbX < -GetLeftDeadzone())
				return m_LeftThumbX;

			return 0;
		}

		[[nodiscard]]
		SHORT GetLeftThumbY() const {
			if (m_LeftThumbY > GetLeftDeadzone() || m_LeftThumbY < -GetLeftDeadzone())
				return m_LeftThumbY;

			return 0;
		}

		[[nodiscard]]
		SHORT GetRightThumbX() const {
			if (m_RightThumbX > GetRightDeadzone() || m_RightThumbX < -GetRightDeadzone())
				return m_RightThumbX;

			return 0;
		}

		[[nodiscard]]
		SHORT GetRightThumbY() const {
			if (m_RightThumbY > GetRightDeadzone() || m_RightThumbY < -GetRightDeadzone())
				return m_RightThumbY;

			return 0;
		}

		void ProcessInput() {
			m_PreviousState = m_CurrentState;
			m_CurrentState  = {};
			XInputGetState(m_ControllerId, &m_CurrentState);

			auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
			m_ButtonsPressed   = buttonChanges & m_CurrentState.Gamepad.wButtons;
			m_ButtonsReleased  = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

			m_LeftThumbX = m_CurrentState.Gamepad.sThumbLX;
			m_LeftThumbY = m_CurrentState.Gamepad.sThumbLY;

			m_RightThumbX = m_CurrentState.Gamepad.sThumbRX;
			m_RightThumbY = m_CurrentState.Gamepad.sThumbRY;
		}
	};

	ControllerInput::ControllerInput()
	    : m_pXInputController{std::make_unique<ControllerInput::Impl>()} {
	}

	bool ControllerInput::IsDown(DWORD buttonCode) const {
		return m_pXInputController->IsDown(buttonCode);
	}

	bool ControllerInput::IsAnyInputActive() const {
		return IsDown(0xFFFF);
	}

	void ControllerInput::ProcessInput() {
		m_pXInputController->ProcessInput();
	}

	SHORT ControllerInput::GetLeftThumbX() const {
		return m_pXInputController->GetLeftThumbX();
	}

	SHORT ControllerInput::GetLeftThumbY() const {
		return m_pXInputController->GetLeftThumbY();
	}

	SHORT ControllerInput::GetRightThumbX() const {
		return m_pXInputController->GetRightThumbX();
	}

	SHORT ControllerInput::GetRightThumbY() const {
		return m_pXInputController->GetRightThumbY();
	}

	constexpr SHORT ControllerInput::GetLeftDeadzone() {
		return XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	}

	constexpr SHORT ControllerInput::GetRightDeadzone() {
		return XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	}

	ControllerInput::~ControllerInput()                                           = default;
	ControllerInput::ControllerInput(ControllerInput &&other) noexcept            = default;
	ControllerInput &ControllerInput::operator=(ControllerInput &&other) noexcept = default;
}// namespace dae
