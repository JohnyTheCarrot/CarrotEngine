#include "CounterComponent.h"
#include "../Font.h"
#include "../GameObject.h"
#include "TextComponent.h"

namespace dae {
	CounterComponent::CounterComponent(Component::Parent pParent, SharedOwningPtr<Font> pFont)
	    : Component{pParent}
	    , m_pFont{std::move(pFont)}
	    , m_pTextComponent{AddComponent<TextComponent>(m_pFont, "text")} {
	}

	void CounterComponent::OnUpdate() {
		m_pTextComponent->SetText(std::to_string(m_Count));
		++m_Count;
	}

	void CounterComponent::OnFixedUpdate() {
	}

	void CounterComponent::OnRender() const {
	}
}// namespace dae
