#ifndef COMPONENT_H
#define COMPONENT_H

#include "Util/PointerAliases.h"
#include "ComponentStore.h"
#include <vector>

namespace dae {
	class GameObject;

	class Component : public ComponentStore<Component> {
	public:
		using Parent = NonOwningPtrMut<GameObject>;

		explicit Component(Parent pParent)
		    : ComponentStore<Component>{pParent} {};

		virtual ~Component() = default;

		Component(const Component &)     = delete;
		Component(Component &&) noexcept = default;

		void       operator=(const Component &) = delete;
		Component &operator=(Component &&)      = default;

		void Update() {
			UpdateComponents();

			OnUpdate();
		}

		void FixedUpdate() {
			FixedUpdateComponents();

			OnFixedUpdate();
		}

		void Render() {
			RenderComponents();

			OnRender();
		}

	protected:
		virtual void OnUpdate() = 0;

		virtual void OnFixedUpdate() = 0;

		virtual void OnRender() = 0;
	};
}// namespace dae

#endif//COMPONENT_H
