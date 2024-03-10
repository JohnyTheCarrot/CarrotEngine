#include "TrashTheCache.h"
#include "imgui/imgui.h"
#include "imgui/implot.h"
#include <numeric>
#include <utility>

using namespace std::chrono_literals;

namespace dae {
	void TrashTheCache::OnRender() {
		ImGui::Begin(m_Name.c_str());
		bool running{m_Running};

		if (running)
			ImGui::BeginDisabled();

		ImGui::InputInt("# samples", &m_SampleCount);
		if (ImGui::Button("Trash the cache")) {
			m_Times.clear();
			m_Running = true;
			m_Future  = std::async(std::launch::async, [&]() {
                for (int stepSize{1}; stepSize <= 1024; stepSize *= 2) {
                    std::vector<size_t> measurements(m_SampleCount);

                    for (auto &measurement: measurements) {
                        const auto start{std::chrono::high_resolution_clock::now()};
                        m_ToMeasure(stepSize);
                        measurement = std::chrono::duration_cast<std::chrono::microseconds>(
                                              std::chrono::high_resolution_clock::now() - start
                        )
                                              .count();
                    }
                    std::sort(measurements.begin(), measurements.end());
                    m_Times.emplace_back(
                            std::accumulate(std::next(measurements.cbegin()), std::prev(measurements.cend()), 0ull) / 8
                    );
                }
                m_Running = false;
            });
		}

		if (running) {
			ImGui::EndDisabled();
			ImGui::Text("Wait for it...");
		}

		if (m_Future.valid() && m_Future.wait_for(0s) == std::future_status::ready) {
			if (ImPlot::BeginPlot("Plot", ImVec2{-1, 0}, ImPlotFlags_None)) {
				ImPlot::SetupAxes(
				        "Step size", "Time", ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_NoLabel,
				        ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoLabel
				);

				ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Linear);

				ImPlot::PlotLine("Trash the cache", m_Times.data(), static_cast<int>(m_Times.size()));

				ImPlot::EndPlot();
			}
		}

		ImGui::End();
	}

	void TrashTheCache::OnUpdate() {
	}

	void TrashTheCache::OnFixedUpdate() {
	}

	TrashTheCache::TrashTheCache(Component::Parent pParent, std::function<void(int)> toMeasure, const std::string &name)
	    : Component{pParent}
	    , m_ToMeasure{std::move(toMeasure)}
	    , m_Name{name} {
		ImPlot::CreateContext();
	}

	TrashTheCache::~TrashTheCache() {
		ImPlot::DestroyContext();
	}
}// namespace dae
