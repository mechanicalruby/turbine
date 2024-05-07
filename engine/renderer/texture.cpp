#include "texture.hpp"

#if PSP
inline auto swizzle_fast(u8* out, const u8* in, unsigned int width,
	unsigned int height) -> void {
	unsigned int blockx, blocky;
	unsigned int j;

	unsigned int width_blocks = (width / 16);
	unsigned int height_blocks = (height / 8);

	unsigned int src_pitch = (width - 16) / 4;
	unsigned int src_row = width * 8;

	const u8* ysrc = in;
	u32* dst = (u32*)out;

	for (blocky = 0; blocky < height_blocks; ++blocky) {
		const u8* xsrc = ysrc;
		for (blockx = 0; blockx < width_blocks; ++blockx) {
			const u32* src = (u32*)xsrc;
			for (j = 0; j < 8; ++j) {
				*(dst++) = *(src++);
				*(dst++) = *(src++);
				*(dst++) = *(src++);
				*(dst++) = *(src++);
				src += src_pitch;
			}
			xsrc += 16;
		}
		ysrc += src_row;
	}
}

u32 offset = 10 * 512 * 272;

unsigned int pow2(const unsigned int val)
{
	// https://stackoverflow.com/questions/466204/rounding-up-to-next-power-of-2
	unsigned long v = val;

	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;

	return v;
}
#endif

namespace Turbine {
TextureManager::TextureManager() {};
TextureManager::~TextureManager() {};

auto TextureManager::load_texture(
	const std::string& name,
	const std::string& file_path,
	bool vram,
	std::uint32_t filterMag,
	std::uint32_t filterMin) -> std::shared_ptr<Texture> {

	// If there is a texture of an identical name in the texture map, do not load again, but return the already loaded texture of the same name.
	std::unordered_map<std::string, std::shared_ptr<Texture>>::iterator it = texture_map.find(name);
	if (it != texture_map.end()) {
		std::cout << "TEXTURE: Duplicate name in texture map: \"" << name << "\". Returning already loaded texture." << '\n';
		return it->second;
	}

	int width, height, comp;

	// top left pixel should be (0, 0). no flip.
	stbi_set_flip_vertically_on_load(false);
	unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &comp, STBI_rgb_alpha);

	auto texture = std::make_shared<Texture>();

	texture->width = width;
	texture->height = height;
	texture->filterMag = filterMag;
	texture->filterMin = filterMin;

#if !PSP
	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		texture->data = data;
		stbi_image_free(data);

		if (width > 512 || height > 512) {
			std::cout << "A texture was loaded that is bigger than 512px in one or more dimensions. PlayStation Portable system compatibility may be affected." << std::endl;
		}
	}
	else {
		std::cout << "Texture failed to load." << '\n';
	}
#elif PSP
	texture->powWidth = pow2(width);
	texture->powHeight = pow2(height);

	unsigned int* dataBuffer = (unsigned int*)memalign(16, texture->powHeight * texture->powWidth * 4);

	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			dataBuffer[x + y * texture->powWidth] = ((unsigned int*)data)[x + y * width];
		}
	}

	stbi_image_free(data);
	texture->data = (uint16_t*)dataBuffer;

	unsigned int* swizzled_pixels = nullptr;
	if (!vram)
		swizzled_pixels = (unsigned int*)memalign(16, texture->powHeight * texture->powWidth * 4);
	else {
		swizzled_pixels = (unsigned int*)((int)offset + (int)sceGeEdramGetAddr());
		offset += texture->powHeight * texture->powWidth * 4;
	}

	swizzle_fast((u8*)swizzled_pixels, (const u8*)dataBuffer, texture->powWidth * 4,
		texture->powHeight);

	free(dataBuffer);
	texture->data = (u16*)swizzled_pixels;

	sceKernelDcacheWritebackInvalidateAll();
#endif

	texture_map.emplace(name, texture);
	return texture;
}

auto TextureManager::get_texture(const std::string& name) -> std::shared_ptr<Texture> {
	std::unordered_map<std::string, std::shared_ptr<Texture>>::iterator it = texture_map.find(name);
	if (it != texture_map.end()) {
		return it->second;
	}
	return nullptr;
}

auto TextureManager::clear() -> void {
	texture_map.clear();
}
}
