#pragma once

#include "Singleton.h"
#include <filesystem>
#include <memory>
#include <string>

namespace dae {
	class Texture2D;

	class Font;

	class ResourceManager final : public Singleton<ResourceManager> {
	public:
		void Init(const std::filesystem::path &data);

		[[nodiscard]]
		std::shared_ptr<Texture2D> LoadTexture(const std::string &file) const;

		[[nodiscard]]
		std::shared_ptr<Font> LoadFont(const std::string &file, unsigned int size) const;

	private:
		friend class Singleton<ResourceManager>;

		ResourceManager() = default;

		std::filesystem::path m_dataPath;
	};
}// namespace dae
