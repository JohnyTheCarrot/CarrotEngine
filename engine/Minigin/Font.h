#ifndef FONT_H
#define FONT_H

#include <string>

struct _TTF_Font;

namespace dae {
	/**
     * Simple RAII wrapper for a _TTF_Font
     */
	class Font final {
	public:
		[[nodiscard]]
		_TTF_Font *GetFont() const;

		Font(std::string_view fullPath, unsigned int size);

		~Font();

		Font(const Font &) = delete;

		Font(Font &&) = delete;

		Font &operator=(const Font &) = delete;

		Font &operator=(const Font &&) = delete;

	private:
		_TTF_Font *m_Font;
	};
}// namespace dae

#endif
