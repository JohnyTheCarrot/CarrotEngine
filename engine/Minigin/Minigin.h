#ifndef MINIGIN_H
#define MINIGIN_H

#include <chrono>
#include <filesystem>
#include <functional>
#include <string>

using namespace std::literals::chrono_literals;

using GameLoopTimeUnit = std::chrono::milliseconds;

constexpr GameLoopTimeUnit operator""_t(unsigned long long time) {
	return GameLoopTimeUnit{time};
}

namespace dae {
	class Minigin final {
		bool m_Quit{};

		static constexpr GameLoopTimeUnit FIXED_TIME_DELTA{10_t};

	public:
		explicit Minigin(const std::filesystem::path &dataPath);

		~Minigin();

		void Run(const std::function<void()> &load);

		void RunOneFrame();

		Minigin(const Minigin &other) = delete;

		Minigin(Minigin &&other) = delete;

		Minigin &operator=(const Minigin &other) = delete;

		Minigin &operator=(Minigin &&other) = delete;
	};
}// namespace dae

#endif
