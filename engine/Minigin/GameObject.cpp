#include "GameObject.h"

namespace dae {
	GameObject &GameObject::SetPosition(float x, float y) {
		m_Transform.SetPosition(x, y, 0.0f);

		return *this;
	}

	GameObject::GameObject(GameObject &&other) noexcept
	    : ComponentStore<Component>{std::move(other)}
	    , m_Transform{other.m_Transform} {
		SetGameObjectPtr(this);
	}

	GameObject &GameObject::operator=(GameObject &&other) noexcept {
		if (&other == this)
			return *this;

		m_Transform = other.m_Transform;

		ComponentStore<Component>::operator=(std::move(other));
		SetGameObjectPtr(this);

		return *this;
	}
}// namespace dae
