#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Transform.h"
#include <memory>
#include <string>

namespace dae {
	class Texture2D;

	class GameObject {
		std::shared_ptr<Texture2D> m_Texture{};

	protected:
		Transform m_Transform{};

	public:
		virtual void Update();

		virtual void Render() const;

		void SetTexture(const std::string &filename);

		void SetPosition(float x, float y);

		GameObject() = default;

		virtual ~GameObject();

		GameObject(const GameObject &other) = delete;

		GameObject(GameObject &&other) = delete;

		GameObject &operator=(const GameObject &other) = delete;

		GameObject &operator=(GameObject &&other) = delete;
	};
}// namespace dae

#endif
