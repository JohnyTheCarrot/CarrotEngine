#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include "../Font.h"
#include "../Texture2D.h"
#include "../Util/PointerAliases.h"
#include "Base/Component.h"

namespace dae {

	class GameObject;

	class TextComponent final : public Component {
		SharedOwningPtr<Font> m_pFont;
		Texture2D             m_Texture;

	public:
		TextComponent(Component::Parent pParent, const SharedOwningPtr<Font> &pFont, std::string_view text);

		void OnRender() const override;

		void OnUpdate() override;

		void OnFixedUpdate() override;

		void SetText(std::string_view text);
	};

}// namespace dae

#endif//TEXTCOMPONENT_H
