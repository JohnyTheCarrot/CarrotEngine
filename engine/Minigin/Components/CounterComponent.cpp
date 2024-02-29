#include "CounterComponent.h"
#include "../Font.h"
#include "../GameObject.h"
#include "../GameTime.h"
#include "TextComponent.h"

namespace dae {
	CounterComponent::CounterComponent(Component::Parent pParent, SharedOwningPtr<Font> pFont)
	    : Component{pParent}
	    , m_pFont{std::move(pFont)}
	    , m_pTextComponent{AddComponent<TextComponent>(m_pFont, "text")} {
	}

	void CounterComponent::OnUpdate() {
		static double fps{};
		double        newFps{GameTime::GetInstance().GetCumAvgFps()};

		if (fps == newFps)
			return;

		fps = newFps;

		const auto fpsText{std::format("{:4.3f} FPS", fps)};
		m_pTextComponent->SetText(fpsText);
		++m_Count;
	}

	void CounterComponent::OnFixedUpdate() {
	}

	void CounterComponent::OnRender() const {
	}
}// namespace dae
