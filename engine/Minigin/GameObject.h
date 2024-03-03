#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Components/Base/Component.h"
#include "Components/Base/ComponentStore.h"
#include "Util/PointerAliases.h"
#include <concepts>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace dae {
	class Texture2D;

	class GameObject final : public ComponentStore<Component> {
	public:
		using Handle = int;

		GameObject()
		    : ComponentStore<Component>{this} {
			static Handle handle{0};
			m_Handle = handle++;
		};

		GameObject(const GameObject &) = delete;

		GameObject(GameObject &&other) noexcept;

		GameObject &operator=(GameObject &&other) noexcept;

		void SetParent(Handle parentHandle) noexcept;

		void SetParent(NonOwningPtrMut<GameObject> pParent) noexcept;

		[[nodiscard]]
		NonOwningPtrMut<GameObject> GetParentPtr() const noexcept;

		[[nodiscard]]
		Handle GetHandle() const noexcept;

	private:
		std::vector<NonOwningPtrMut<GameObject>> m_Children{};
		NonOwningPtrMut<GameObject>              m_pParent{};
		Handle                                   m_Handle;
	};
}// namespace dae

#endif
