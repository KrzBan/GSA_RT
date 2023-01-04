#include "Ray.hpp"

namespace gsa::primitives {

	Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
		: m_Origin{ origin }, m_Direction{ direction } {}

	glm::vec3 Ray::Origin() const {
		return m_Origin;
	}

	glm::vec3 Ray::Direction() const {
		return m_Direction;
	}

	glm::vec3 Ray::At(float t) const {
		return m_Origin + t * m_Direction;
	}
}