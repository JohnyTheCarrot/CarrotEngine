#include "ResourceManager.h"
#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdexcept>

void dae::ResourceManager::Init(const std::filesystem::path &dataPath) {
	m_DataPath = dataPath;

	if (TTF_Init() != 0) {
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<dae::Texture2D> dae::ResourceManager::LoadTexture(std::string_view fileName) const {
	const auto fullPath = m_DataPath / fileName;
	auto       texture  = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.string().c_str());
	if (texture == nullptr) {
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<dae::Font> dae::ResourceManager::LoadFont(std::string_view fileName, unsigned int size) const {
	const auto fullPath = m_DataPath / fileName;
	return std::make_shared<Font>(fullPath.string(), size);
}
