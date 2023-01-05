#include "Renderer.hpp"
#include "primitives/Sphere.hpp"

namespace gsa {

	struct Pixel {
		uint8_t r, g, b;
	};

	glm::vec3 ColorTest(const gsa::primitives::Ray& ray, const std::vector<gsa::primitives::Sphere>& spheres, uint32_t depth);
	Pixel Vec3ToPixel(const glm::vec3& color);

	void Renderer::Render() {

		using namespace gsa::primitives;

		spdlog::info("Render begin");
		auto clockStart = std::chrono::high_resolution_clock::now();

		constexpr uint32_t imageWidth = 640;
		constexpr uint32_t imageHeight = 480;
		constexpr float aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);
		
		constexpr uint32_t pixelCount = imageWidth * imageHeight;
		constexpr uint32_t channels = 3;

		std::vector<Sphere> spheres{
			Sphere({ 0.0f, -1000.0f, 0.0f}, 1000.0f, {0.1f, 0.7f, 0.1f}),
			Sphere({-4.0f, 3.0f, -8.0f}, 3.0f, {0.8f, 0.3f, 0.1f}),
			Sphere({ 6.0f, 3.0f, -10.0f}, 3.0f, {0.1f, 0.2f, 0.5f}),
			Sphere({ 2.0f, 0.5f, -5.0f}, 0.5f, {0.2f, 0.5f, 0.7f}),
			Sphere({ 0.0f, 0.5f, -5.5f}, 0.5f, {0.7f, 0.5f, 0.3f}),
		};

		// Camera settings
		constexpr float viewportHeight = 2.0f;
		constexpr float viewportWidth = aspectRatio * viewportHeight;
		constexpr float focalLength = 1.0f;

		constexpr auto cameraOrigin = glm::vec3(0.0f, 2.0f, 0.0f);
		constexpr auto horizontal = glm::vec3(viewportWidth, 0, 0);
		constexpr auto vertical = glm::vec3(0, viewportHeight, 0);
		constexpr auto upperLeftCorner = cameraOrigin - horizontal / 2.0f + vertical / 2.0f - glm::vec3(0, 0, focalLength);
		constexpr auto depth = 10;
		constexpr auto samples = 10;

		// Render
		std::vector<glm::vec3> renderResult( pixelCount );

		for (size_t j = 0; j < imageHeight; ++j) {
			for (size_t i = 0; i < imageWidth; ++i) {
				glm::vec3 pixelColor{};
				for (size_t s = 0; s < samples; ++s) {
					auto u = (i + RandomFloat()) / (imageWidth - 1);
					auto v = (j + RandomFloat()) / (imageHeight - 1);

					Ray r(cameraOrigin, upperLeftCorner + u * horizontal - v * vertical - cameraOrigin);
					pixelColor += ColorTest(r, spheres, depth);
				}
				renderResult.at(i + j * imageWidth) = pixelColor;
			}
		}

		// Normalize colors
		std::transform(renderResult.begin(), renderResult.end(), renderResult.begin(), [](const glm::vec3& color) {return color / static_cast<float>(samples); });
		// Gamma-Correct
		std::transform(renderResult.begin(), renderResult.end(), renderResult.begin(), 
			[](const glm::vec3& color) {return glm::vec3{std::sqrt(color.x), std::sqrt(color.y) , std::sqrt(color.z) }; });

		// Write to image
		std::vector<Pixel> data{ pixelCount };
		std::transform(renderResult.begin(), renderResult.end(), data.begin(), Vec3ToPixel);

		stbi_write_png("test.png", imageWidth, imageHeight, channels, data.data(), imageWidth * sizeof(Pixel));

		auto clockEnd = std::chrono::high_resolution_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(clockEnd - clockStart);

		spdlog::info("Render end");
		spdlog::info("Elapsed time: {} ms", deltaTime.count());
	}

	glm::vec3 ColorTest(const gsa::primitives::Ray& ray, const std::vector<gsa::primitives::Sphere>& spheres, uint32_t depth){

		if (depth == 0)
			return glm::vec3(0.0f, 0.0f, 0.0f);

		// Find Closest Hit
		HitInfo hitInfo{};
		bool hitAnything = false;
		float bestHit = std::numeric_limits<float>::infinity();

		for (const auto& sphere : spheres) {
			HitInfo tempInfo{};
			if (sphere.Hit(ray, 0.001, bestHit, tempInfo)) {
				hitAnything = true;
				bestHit = tempInfo.t;
				hitInfo = tempInfo;
			}
		}

		if (hitAnything) {
			gsa::primitives::Ray scattered{ hitInfo.position, hitInfo.normal };
			return hitInfo.color * ColorTest(scattered, spheres, depth - 1);
		}

		// Background color
		glm::vec3 unitDirection = glm::normalize(ray.Direction());
		float t = 0.5f * (unitDirection.y + 1.0f);
		return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
	}
	Pixel Vec3ToPixel(const glm::vec3& color) {
		return Pixel{ 
			static_cast<uint8_t>(color.x * 255.999f), 
			static_cast<uint8_t>(color.y * 255.999f) , 
			static_cast<uint8_t>(color.z * 255.999f) 
		};
	}

}