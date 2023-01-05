#pragma once

#include "Core.hpp"

#include "primitives/Ray.hpp"

namespace gsa {

	struct HitInfo {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        double t;
        bool isFrontFace;

        inline void SetFaceNormal(const primitives::Ray& r, const glm::vec3& outward_normal) {
            isFrontFace = glm::dot(r.Direction(), outward_normal) < 0;
            normal = isFrontFace ? outward_normal : -outward_normal;
        }
	};

    inline float RandomFloat() {
        static std::mt19937 generator;
        static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
        return distribution(generator);
    }

}