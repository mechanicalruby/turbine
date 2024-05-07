#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <cstdint>
#include <cassert>

#ifndef PSP
#define TB_NEAREST GL_NEAREST
#define TB_LINEAR GL_LINEAR
#include <glad/glad.h>
#else
#define TB_NEAREST GU_NEAREST
#define TB_LINEAR GU_LINEAR
#include <pspdisplay.h>
#include <pspge.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspkernel.h>
#include <malloc.h>
#endif

#include "stb_image.hpp"

namespace Turbine {
struct Texture {
	unsigned int width, height;
	void* data;
	std::uint32_t id;
	std::uint32_t powWidth, powHeight; // power of two dimensions (PSP, GLES2)
	std::uint32_t filterMin, filterMag;
	std::uint32_t wrapS, wrapT;
	std::string name;

	inline void bind() {
#if __linux__ || WIN32 || VITA
		glBindTexture(GL_TEXTURE_2D, id);
#elif PSP
		sceGuTexMode(GU_TEXTURE_BITS, 0, 0, 1);
		sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
		sceGuTexFilter(filterMin, filterMag);
		sceGuTexWrap(wrapS, wrapT);
		sceGuTexImage(0, powHeight, powWidth, powHeight, data);
#endif
	}
};

class TextureManager {
private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> texture_map;
public:
	auto load_texture(const std::string& name,
		const std::string& file_path,
		bool vram,
		std::uint32_t magFilter,
		std::uint32_t minFilter) -> std::shared_ptr<Texture>;

	auto get_texture(const std::string& name) -> std::shared_ptr<Texture>;
	auto remove_texture(const std::string& name) -> void;
	auto clear() -> void;

	inline static auto get() -> TextureManager& {
		static TextureManager instance;
		return instance;
	}

	TextureManager();
	~TextureManager();
};
}

#endif
