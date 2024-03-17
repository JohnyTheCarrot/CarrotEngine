#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include "Base/Component.h"
#include "Texture2D.h"
#include "Util/PointerAliases.h"
#include <optional>
#include <string_view>

namespace dae {

	class GameObject;
	class TransformComponent;

	struct TextureSize final {
		float width;
		float height;
	};

	class TextureComponent final : public Component {
		Texture2D                           m_Texture;
		NonOwningPtrMut<TransformComponent> m_pTransformComponent;
		std::optional<TextureSize>          m_Size;

	public:
		void OnRender() override;

		void OnUpdate() override;

		void OnFixedUpdate() override;

		TextureComponent(
		        Component::Parent pParent, const std::optional<TextureSize> &textureSize, std::string_view fileName
		);

		TextureComponent(Component::Parent pParent, Texture2D &&texture);

		~TextureComponent() override = default;
	};

}// namespace dae

#endif//TEXTURECOMPONENT_H
