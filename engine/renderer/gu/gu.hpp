#ifndef GU_RENDERER_HPP
#define GU_RENDERER_HPP

#define PSP_BUF_WIDTH (512)
#define PSP_SCR_WIDTH (480)
#define PSP_SCR_HEIGHT (272)

#define GU_TEXTURE_BIT GU_PSM_8888

#include <iostream>

#include <pspge.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>

#include "../renderer.hpp"

// Note: all immediate mode rendering, no support for shaders
class GU_Renderer : public Renderer {
public:
    GU_Renderer() = default;

    bool should_window_close();

    void initialize(const std::string& w_title, int w_width, int w_height);
    void clean_up();

    // Default is a 2D orthographic view for the PSP's native resolution
    void set_ortho(float left = 0.0f, float right = 480.0f, float bottom = 272.0f, float top = 0.0f, float near = -1.0f, float far = 1.0f);
    void load_identity();

    void set_viewport(int width, int height, ViewportMode mode);

    void begin_frame();
    void end_frame();

    void clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void set_blend_mode(BlendMode mode);

    // vram stuff
    void* getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm) {
        static unsigned int staticOffset = 0;
        unsigned int memSize = getMemorySize(width, height, psm);
        void* result = (void*)staticOffset;
        staticOffset += memSize;

        return result;
    };

    // Vram Texture Request
    void* getStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm) {
        void* result = getStaticVramBuffer(width, height, psm);
        return (void*)(((unsigned int)result) + ((unsigned int)sceGeEdramGetAddr()));
    };

    static unsigned int getMemorySize(unsigned int width, unsigned int height, unsigned int psm) {
        switch (psm)
        {
        case GU_PSM_T4:
            return (width * height) >> 1;

        case GU_PSM_T8:
            return width * height;

        case GU_PSM_5650:
        case GU_PSM_5551:
        case GU_PSM_4444:
        case GU_PSM_T16:
            return 2 * width * height;

        case GU_PSM_8888:
        case GU_PSM_T32:
            return 4 * width * height;

        default:
            return 0;
        }
    };

private:
    unsigned int __attribute__((aligned(16))) list[262144];
};
#endif
