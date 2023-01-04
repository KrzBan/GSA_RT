#pragma once

#include "Core.hpp"

namespace gsa::primitives {

	class Ray {
	private:
		glm::vec3 m_Origin{};
		glm::vec3 m_Direction{};

	public:
		explicit Ray(const glm::vec3& origin, const glm::vec3& direction);

		glm::vec3 Origin() const;
		glm::vec3 Direction() const;

		glm::vec3 At(float t) const;
	};

}