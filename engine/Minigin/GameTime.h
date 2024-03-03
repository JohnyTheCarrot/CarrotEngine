#ifndef GAMETIME_H
#define GAMETIME_H

#include "Singleton.h"
#include <chrono>

namespace dae {
	constexpr size_t DURATION_FRACTION{1};
	using GameTimeDurationPrecision = float;
	using GameLoopTimeUnit = std::chrono::duration<GameTimeDurationPrecision, std::ratio<1, DURATION_FRACTION>>;

	constexpr GameLoopTimeUnit operator""_t(unsigned long long time) {
		return GameLoopTimeUnit{time};
	}

	class GameTime final : public Singleton<GameTime> {

	public:
		static constexpr GameTimeDurationPrecision FIXED_TIME_DELTA{(10_t).count()};

		void StartDeltaTimeMeasurement();

		void EndDeltaTimeMeasurement();

		[[nodiscard]]
		GameTimeDurationPrecision GetDeltaTime() const noexcept;

		[[nodiscard]]
		double GetFps() const noexcept;

		GameTime() {
			StartDeltaTimeMeasurement();
		}

	private:
		std::chrono::time_point<std::chrono::system_clock> m_Start{};

		GameLoopTimeUnit m_DeltaTime{};
		GameLoopTimeUnit m_FpsTimeProgress{};
		double           m_Fps{};
		int              m_Frames{};
	};

}// namespace dae

#endif//GAMETIME_H
