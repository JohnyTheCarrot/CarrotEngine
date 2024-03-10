#ifndef TRASHTHECACHE_H
#define TRASHTHECACHE_H

#include "Base/Component.h"
#include <future>

namespace dae {

	class TrashTheCache final : public Component {
	public:
		void OnRender() override;

		void OnUpdate() override;

		void OnFixedUpdate() override;

		TrashTheCache(Component::Parent pParent, std::function<void(int)> toMeasure, const std::string &name);

		~TrashTheCache();

	private:
		int                      m_SampleCount{10};
		bool                     m_Running{};
		std::future<void>        m_Future;
		std::function<void(int)> m_ToMeasure{};
		std::vector<size_t>      m_Times{};
		std::string              m_Name{};
	};

}// namespace dae

#endif//TRASHTHECACHE_H
