#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Base/Component.h"
#include "Base/PossiblyDirty.h"
#include <glm/glm.hpp>

namespace dae {

	class TransformComponent;

	class LocalPositionCalculator final {
	public:
		glm::vec4 operator()(glm::mat4 transMat, glm::mat4 rotMat, glm::mat4 scaleMat);

		LocalPositionCalculator()
		    : m_LocalPosition{0.f, 0.f, 0.f, 1.f} {
		}

	private:
		glm::vec4 m_LocalPosition{};
	};

	using LocalPosDirty = PossiblyDirty<LocalPositionCalculator, glm::vec4, glm::mat4, glm::mat4, glm::mat4>;

	class WorldPositionCalculator final {
	public:
		glm::vec4 operator()(LocalPosDirty &localPosition);

		explicit WorldPositionCalculator(NonOwningPtrMut<GameObject> pParentGameObject);

	private:
		NonOwningPtrMut<TransformComponent> m_pParentTransform;
	};

	class TransformComponent final : public Component {
		LocalPosDirty                                                      m_LocalPosition;
		PossiblyDirty<WorldPositionCalculator, glm::vec4, LocalPosDirty &> m_WorldPosition;

		glm::mat4 m_TranslationMatrix{1.f}, m_RotationMatrix{1.f}, m_ScaleMatrix{1.f};

	public:
		explicit TransformComponent(Component::Parent pGameObject);

		TransformComponent(Component::Parent pParent, float x, float y);

		TransformComponent(TransformComponent &&) noexcept;

		void OnRender() override;

		void OnUpdate() override;

		void OnFixedUpdate() override;

		[[nodiscard]]
		const glm::vec4 &GetLocalPosition() noexcept;

		[[nodiscard]]
		const glm::vec4 &GetWorldPosition() noexcept;

		void SetLocalPosition(float x, float y) noexcept;

		void Translate(float x, float y) noexcept;

		void Rotate(float z) noexcept;

		[[nodiscard]]
		glm::vec2 GetScale() const noexcept;

		void Scale(float scaleX, float scaleY, float scaleZ) noexcept;

		void Scale(float scale) noexcept;

		void SetParentGameObjectPtr(NonOwningPtrMut<GameObject> goPtr) noexcept;
	};

}// namespace dae

#endif//TRANSFORMCOMPONENT_H
