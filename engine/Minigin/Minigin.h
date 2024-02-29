#ifndef MINIGIN_H
#define MINIGIN_H

#include <chrono>
#include <filesystem>
#include <functional>
#include <string>

using namespace std::literals::chrono_literals;

namespace dae {
	class Minigin final {
		bool m_Quit{};

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
