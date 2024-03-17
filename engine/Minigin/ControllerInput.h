#ifndef XIINPUTCONTROLLER_H
#define XIINPUTCONTROLLER_H

#define WIN32_LEAN_AND_MEAN
// clang-format off
#include "Util/PointerAliases.h"
#include <windows.h>
#include <XInput.h>
// clang-format on

namespace dae {

	class ControllerInput final {
	public:
		ControllerInput();

		~ControllerInput();

		ControllerInput(ControllerInput &&other) noexcept;
		ControllerInput &operator=(ControllerInput &&other) noexcept;

		[[nodiscard]]
		bool IsDown(DWORD buttonCode) const;

		[[nodiscard]]
		bool IsAnyInputActive() const;

		[[nodiscard]]
		static constexpr SHORT GetLeftDeadzone();

		[[nodiscard]]
		static constexpr SHORT GetRightDeadzone();

		[[nodiscard]]
		SHORT GetLeftThumbX() const;

		[[nodiscard]]
		SHORT GetLeftThumbY() const;

		[[nodiscard]]
		SHORT GetRightThumbX() const;

		[[nodiscard]]
		SHORT GetRightThumbY() const;

		void ProcessInput();

	private:
		class Impl;
		OwningPtr<Impl> m_pXInputController;
	};
}// namespace dae

#endif//XIINPUTCONTROLLER_H
