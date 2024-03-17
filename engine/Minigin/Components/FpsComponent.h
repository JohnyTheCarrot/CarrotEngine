#ifndef FPSCOMPONENT_H
#define FPSCOMPONENT_H

#include "Base/Component.h"
#include "Util/PointerAliases.h"

namespace dae {

	class Font;

	class TextComponent;

	class FpsComponent final : public Component {
		SharedOwningPtr<Font>          m_pFont;
		NonOwningPtrMut<TextComponent> m_pTextComponent{};

	public:
		FpsComponent(Component::Parent pParent, SharedOwningPtr<Font> pFont);

		void OnUpdate() override;

		void OnFixedUpdate() override;

		void OnRender() override;
	};

}// namespace dae

#endif//FPSCOMPONENT_H
