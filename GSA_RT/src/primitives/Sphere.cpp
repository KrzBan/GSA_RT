#include "Sphere.hpp"

#include "Utils.hpp"

namespace gsa::primitives {

	Sphere::Sphere(const glm::vec3& position, float radius, const glm::vec3& color)
        : m_Position{ position }, m_Radius{ radius }, m_Color{ color } {}

	bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitInfo& hitInfo) const {
        glm::vec3 oc = ray.Origin() - m_Position;
        auto rayLen = glm::length(ray.Direction());
        auto a = rayLen * rayLen;
        auto half_b = glm::dot(oc, ray.Direction());
        auto ocLen = glm::length(oc);
        auto c = ocLen * ocLen - m_Radius * m_Radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;
        auto sqrtd = std::sqrt(discriminant);
        
        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (root < tMin || tMax < root) {
            root = (-half_b + sqrtd) / a;
            if (root < tMin || tMax < root)
                return false;
        }

        hitInfo.t = root;
        hitInfo.position = ray.At(root);
        glm::vec3 outwardNormal = (hitInfo.position - m_Position) / m_Radius;
        hitInfo.SetFaceNormal(ray, outwardNormal);
        hitInfo.color = m_Color;

        return true;
	}

}