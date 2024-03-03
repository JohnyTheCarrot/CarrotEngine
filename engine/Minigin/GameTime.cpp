#include "GameTime.h"
#include <thread>

using namespace std::literals::chrono_literals;

namespace dae {
	void GameTime::StartDeltaTimeMeasurement() {
		m_Start = std::chrono::high_resolution_clock::now();
	}

	void GameTime::EndDeltaTimeMeasurement() {
		const auto now{std::chrono::high_resolution_clock::now()};
		m_DeltaTime = std::chrono::duration_cast<GameLoopTimeUnit>(now - m_Start);
		m_FpsTimeProgress += m_DeltaTime;
		++m_Frames;

		if (m_FpsTimeProgress >= 1s) {
			m_Fps             = m_Frames * static_cast<double>(DURATION_FRACTION) / m_FpsTimeProgress.count();
			m_FpsTimeProgress = 0_t;
			m_Frames          = 0;
		}
	}

	GameTimeDurationPrecision GameTime::GetDeltaTime() const noexcept {
		return m_DeltaTime.count();
	}

	double GameTime::GetFps() const noexcept {
		return m_Fps;
	}

	void GameTime::Sleep() {
		const auto sleep_time{m_Start + TIME_PER_FRAME - std::chrono::high_resolution_clock::now()};
		std::this_thread::sleep_for(sleep_time);
	}
}// namespace dae
