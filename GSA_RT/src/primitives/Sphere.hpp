#pragma once

#include "Core.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

namespace gsa::primitives {

	class Sphere {
	private:

		glm::vec3 m_Position{};
		float m_Radius{};
		glm::vec3 m_Color{};


	public:
		explicit Sphere(const glm::vec3& position, float radius, const glm::vec3& color);

		bool Hit(const Ray& ray, float tMin, float tMax, HitInfo& hitInfo) const;

	};

}