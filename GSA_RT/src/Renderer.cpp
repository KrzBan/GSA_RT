#include "Renderer.hpp"

namespace gsa {

	struct Pixel {
		uint8_t r, g, b;
	};

	void Renderer::Render() {

		constexpr uint32_t width = 640;
		constexpr uint32_t height = 480;
		constexpr uint32_t pixelCount = width * height;
		constexpr uint32_t channels = 3;

		std::vector<Pixel> data{ pixelCount };
		std::ranges::fill(data, Pixel{ 64, 120, 10 });

		stbi_write_png("test.png", width, height, channels, data.data(), width * sizeof(Pixel));
	}

}