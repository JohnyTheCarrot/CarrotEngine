#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

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
		Texture2D LoadTexture(std::string_view fileName) const;

		[[nodiscard]]
		std::shared_ptr<Font> LoadFont(std::string_view fileName, unsigned int size) const;

	private:
		friend class Singleton<ResourceManager>;

		ResourceManager() = default;

		std::filesystem::path m_DataPath;
	};
}// namespace dae

#endif
