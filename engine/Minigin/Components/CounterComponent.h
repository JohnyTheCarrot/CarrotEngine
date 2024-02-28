#ifndef COUNTERCOMPONENT_H
#define COUNTERCOMPONENT_H

#include "../Util/PointerAliases.h"
#include "Base/Component.h"

namespace dae {

	class Font;

	class TextComponent;

	class CounterComponent final : public Component {
		int                            m_Count{};
		SharedOwningPtr<Font>          m_pFont;
		NonOwningPtrMut<TextComponent> m_pTextComponent{};

	public:
		CounterComponent(Component::Parent pParent, SharedOwningPtr<Font> pFont);

		void OnUpdate() override;

		void OnFixedUpdate() override;

		void OnRender() const override;
	};

}// namespace dae

#endif//COUNTERCOMPONENT_H