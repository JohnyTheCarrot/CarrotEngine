#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <string>

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update() {
}

void dae::GameObject::Render() const {
	const auto &pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(std::string_view filename) {
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y) {
	m_Transform.SetPosition(x, y, 0.0f);
}
