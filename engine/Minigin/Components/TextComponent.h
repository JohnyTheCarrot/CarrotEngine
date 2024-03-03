#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include "../Texture2D.h"
#include "../Util/PointerAliases.h"
#include "Base/Component.h"
#include "Base/PossiblyDirty.h"
#include <string>

namespace dae {

	class Font;

	class FontTextureUpdater final {
	public:
		Texture2D operator()(NonOwningPtr<Font>, std::string_view);
	};

	class GameObject;

	class TransformComponent;

	class TextComponent final : public Component {
		using PossiblyDirtyTexture = PossiblyDirty<FontTextureUpdater, Texture2D, NonOwningPtr<Font>, std::string_view>;
		PossiblyDirtyTexture                m_Texture;
		SharedOwningPtr<Font>               m_pFont;
		std::string                         m_Text{};
		NonOwningPtrMut<TransformComponent> m_pTransformComponent{};

	public:
		TextComponent(Component::Parent pParent, const SharedOwningPtr<Font> &pFont, const std::string &text);

		void OnRender() override;

		void OnUpdate() override;

		void OnFixedUpdate() override;

		void SetText(const std::string &text) {
			m_Text = text;
			m_Texture.Update(m_pFont.get(), m_Text);
		}
	};

}// namespace dae

#endif//TEXTCOMPONENT_H
