#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

namespace dae {
	class Transform final {
	public:
		[[nodiscard]]
		const glm::vec3 &GetPosition() const {
			return m_Position;
		}

		void SetPosition(float x, float y, float z);

	private:
		glm::vec3 m_Position;
	};
}// namespace dae

#endif
