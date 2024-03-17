#include "FpsComponent.h"
#include "Font.h"
#include "GameObject.h"
#include "GameTime.h"
#include "TextComponent.h"

namespace dae {
	FpsComponent::FpsComponent(Component::Parent pParent, SharedOwningPtr<Font> pFont)
	    : Component{pParent}
	    , m_pFont{std::move(pFont)}
	    , m_pTextComponent{AddComponent<TextComponent>(m_pFont, "FPS")} {
	}

	void FpsComponent::OnUpdate() {
		static double fps{};
		double        newFps{GameTime::GetInstance().GetFps()};

		if (fps == newFps)
			return;

		fps = newFps;

		auto fpsText{std::format("{:4.3f} FPS", fps)};
		m_pTextComponent->SetText(std::move(fpsText));
	}

	void FpsComponent::OnFixedUpdate() {
	}

	void FpsComponent::OnRender() {
	}
}// namespace dae
