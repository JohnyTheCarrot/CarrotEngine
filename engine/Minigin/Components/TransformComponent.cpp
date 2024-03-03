#include "TransformComponent.h"
#include "../GameObject.h"
#include "../GameTime.h"
#include <glm/ext/matrix_transform.hpp>

namespace dae {
	void TransformComponent::OnRender() {
	}

	void TransformComponent::OnUpdate() {
	}

	void TransformComponent::OnFixedUpdate() {
	}

	const glm::vec4 &TransformComponent::GetLocalPosition() noexcept {
		return *m_LocalPosition;
	}

	const glm::vec4 &TransformComponent::GetWorldPosition() noexcept {
		return *m_WorldPosition;
	}

	TransformComponent::TransformComponent(TransformComponent &&other) noexcept
	    : Component{std::move(other)}
	    , m_LocalPosition{std::move(other.m_LocalPosition)}
	    , m_WorldPosition{WorldPositionCalculator{GetGameObject()->GetParentPtr()}, m_LocalPosition} {
	}

	TransformComponent::TransformComponent(Component::Parent pGameObject)
	    : Component{pGameObject}
	    , m_LocalPosition{LocalPositionCalculator{}, glm::mat4{1.f}, glm::mat4{1.f}, glm::mat4{1.f}}
	    , m_WorldPosition{WorldPositionCalculator{pGameObject->GetParentPtr()}, m_LocalPosition}
	    , m_TranslationMatrix{glm::mat4{1.f}} {
	}

	TransformComponent::TransformComponent(Component::Parent pParent, float x, float y)
	    : Component{pParent}
	    , m_LocalPosition{LocalPositionCalculator{}, glm::translate(glm::mat4{1.f}, glm::vec3{x, y, 0.f}), glm::mat4{1.f}, glm::mat4{1.f}}
	    , m_WorldPosition{WorldPositionCalculator{pParent->GetParentPtr()}, m_LocalPosition}
	    , m_TranslationMatrix{glm::translate(glm::mat4{1.f}, glm::vec3{x, y, 0.f})} {
	}

	void TransformComponent::SetLocalPosition(float x, float y) noexcept {
		m_LocalPosition.SetFactory();
		Translate(x, y);
		m_WorldPosition.Update(m_LocalPosition);
	}

	void TransformComponent::Translate(float x, float y) noexcept {
		m_TranslationMatrix = glm::translate(m_TranslationMatrix, glm::vec3{x, y, 0.f});
		m_WorldPosition.Update(m_LocalPosition);
	}

	void TransformComponent::Rotate(float z) noexcept {
		const float actualRotation{z * GameTime::GetInstance().GetDeltaTime()};

		if (std::abs(z) < FLT_EPSILON)
			return;

		m_RotationMatrix = glm::rotate(m_RotationMatrix, actualRotation, glm::vec3{0.f, 0.f, 1.f});
		m_LocalPosition.Update(m_TranslationMatrix, m_RotationMatrix, m_ScaleMatrix);
		m_WorldPosition.Update(m_LocalPosition);
	}

	void TransformComponent::SetParentGameObjectPtr(NonOwningPtrMut<GameObject> goPtr) noexcept {
		m_WorldPosition.SetFactory(goPtr);
	}

	void TransformComponent::Scale(float scale) noexcept {
		Scale(scale, scale, scale);
	}

	void TransformComponent::Scale(float scaleX, float scaleY, float scaleZ) noexcept {
		m_ScaleMatrix = glm::scale(glm::mat4{1.f}, glm::vec3{scaleX, scaleY, scaleZ});
		m_LocalPosition.Update(m_TranslationMatrix, m_RotationMatrix, m_ScaleMatrix);
		m_WorldPosition.Update(m_LocalPosition);
	}

	glm::vec2 TransformComponent::GetScale() const noexcept {
		return glm::vec2{m_ScaleMatrix * glm::vec4{1.f}};
	}

	glm::vec4 WorldPositionCalculator::operator()(LocalPosDirty &localPosition) {
		if (m_pParentTransform == nullptr)
			return *localPosition;

		return m_pParentTransform->GetWorldPosition() + *localPosition;
	}

	WorldPositionCalculator::WorldPositionCalculator(NonOwningPtrMut<GameObject> pParentGameObject)
	    : m_pParentTransform{
	              pParentGameObject != nullptr ? pParentGameObject->GetComponent<TransformComponent>() : nullptr
	      } {
	}

	glm::vec4 LocalPositionCalculator::operator()(glm::mat4 transMat, glm::mat4 rotMat, glm::mat4 scaleMat) {
		return (scaleMat * rotMat * transMat) * m_LocalPosition;
	}
}// namespace dae
