#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Components/Base/Component.h"
#include "Components/Base/ComponentStore.h"
#include "Transform.h"
#include "Util/PointerAliases.h"
#include <concepts>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace dae {
	class Texture2D;

	class GameObject final : public ComponentStore<Component> {
	public:
		Transform m_Transform{};

		GameObject &SetPosition(float x, float y);

		GameObject()
		    : ComponentStore<Component>{this} {};

		GameObject(const GameObject &) = delete;

		GameObject(GameObject &&other) noexcept;

		GameObject &operator=(GameObject &&other) noexcept;
	};
}// namespace dae

#endif
