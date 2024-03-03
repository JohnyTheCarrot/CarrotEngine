#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include "../Texture2D.h"
#include "../Util/PointerAliases.h"
#include "Base/Component.h"
#include <string_view>

namespace dae {

	class GameObject;
	class TransformComponent;

	class TextureComponent final : public Component {
		Texture2D                           m_Texture;
		NonOwningPtrMut<TransformComponent> m_pTransformComponent;

	public:
		void OnRender() override;

		void OnUpdate() override;

		void OnFixedUpdate() override;

		TextureComponent(Component::Parent pParent, std::string_view fileName);

		TextureComponent(Component::Parent pParent, Texture2D &&texture);

		~TextureComponent() override = default;
	};

}// namespace dae

#endif//TEXTURECOMPONENT_H
