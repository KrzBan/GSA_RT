#include "Renderer.hpp"

namespace gsa {

	struct Pixel {
		uint8_t r, g, b;
	};

	void Renderer::Render() {

		spdlog::info("Render begin");
		auto clockStart = std::chrono::high_resolution_clock::now();

		constexpr uint32_t width = 640;
		constexpr uint32_t height = 480;
		constexpr uint32_t pixelCount = width * height;
		constexpr uint32_t channels = 3;

		std::vector<Pixel> data{ pixelCount };
		std::ranges::fill(data, Pixel{ 64, 120, 10 });

		stbi_write_png("test.png", width, height, channels, data.data(), width * sizeof(Pixel));

		auto clockEnd = std::chrono::high_resolution_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(clockEnd - clockStart);

		spdlog::info("Render end");
		spdlog::info("Elapsed time: {} ms", deltaTime.count());
	}

}