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
		static constexpr std::chrono::duration     TIME_PER_FRAME{
                std::chrono::duration<GameTimeDurationPrecision, std::ratio<1>>{1} / 144.f
        };
		void StartDeltaTimeMeasurement();

		void EndDeltaTimeMeasurement();

		[[nodiscard]]
		GameTimeDurationPrecision GetDeltaTime() const noexcept;

		[[nodiscard]]
		double GetFps() const noexcept;

		void Sleep();

		GameTime() {
			StartDeltaTimeMeasurement();
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start{};

		GameLoopTimeUnit m_DeltaTime{};
		GameLoopTimeUnit m_FpsTimeProgress{};
		double           m_Fps{};
		int              m_Frames{};
	};

}// namespace dae

#endif//GAMETIME_H
