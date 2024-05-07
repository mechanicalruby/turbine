#include "gu.hpp"

bool GU_Renderer::should_window_close() {
    return false;
}

void GU_Renderer::initialize(const std::string& w_title, int w_width, int w_height) {
    void* fbp0 = getStaticVramBuffer(PSP_BUF_WIDTH, PSP_SCR_HEIGHT, GU_PSM_8888);
    void* fbp1 = getStaticVramBuffer(PSP_BUF_WIDTH, PSP_SCR_HEIGHT, GU_PSM_8888);
    void* zbp = getStaticVramBuffer(PSP_BUF_WIDTH, PSP_SCR_HEIGHT, GU_PSM_4444);

    sceGuInit();

    sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(GU_PSM_8888, fbp0, PSP_BUF_WIDTH);
    sceGuDispBuffer(PSP_SCR_WIDTH, PSP_SCR_HEIGHT, fbp1, PSP_BUF_WIDTH);
    sceGuDepthBuffer(zbp, PSP_BUF_WIDTH);
    sceGuOffset(2048 - (PSP_SCR_WIDTH / 2), 2048 - (PSP_SCR_HEIGHT / 2));
    sceGuViewport(2048, 2048, PSP_SCR_WIDTH, PSP_SCR_HEIGHT);
    sceGuDepthRange(65535, 0);
    sceGuScissor(0, 0, PSP_SCR_WIDTH, PSP_SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuDepthFunc(GU_GEQUAL);
    sceGuEnable(GU_DEPTH_TEST);
    sceGuFrontFace(GU_CW);
    sceGuShadeModel(GU_SMOOTH);
    sceGuEnable(GU_CULL_FACE);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuEnable(GU_CLIP_PLANES);
    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);
}

void GU_Renderer::clean_up() {
    sceGuTerm();
}

/*
void GU_Renderer::bind_texture(Texture* texture) {
    if (texture == nullptr)
        return;

    sceGuTexMode(GU_TEXTURE_BIT, 0, 0, 1);
    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    sceGuTexFilter(texture->filterMin, texture->filterMag);
    sceGuTexWrap(GU_REPEAT, GU_REPEAT);
    sceGuTexImage(0, texture->powHeight, texture->powWidth, texture->powHeight, texture->data);
}
*/

void GU_Renderer::set_viewport(int width, int height, ViewportMode mode) {

}

void GU_Renderer::set_ortho(float left, float right, float bottom, float top, float near, float far) {
    sceGumMatrixMode(GU_PROJECTION);
    sceGumLoadIdentity();
    sceGumOrtho(left, right, bottom, top, near, far);

    sceGumMatrixMode(GU_VIEW);
    sceGumLoadIdentity();

    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();
}

void GU_Renderer::load_identity() {
    sceGumLoadIdentity();
}

void GU_Renderer::begin_frame() {
    sceGuStart(GU_DIRECT, list);
}

void GU_Renderer::end_frame() {
    sceKernelDcacheWritebackInvalidateAll(); // cache writeback just in case there's something at the end of the loop needing it ...
    sceGuFinish();
    sceGuSync(0, 0);
    sceDisplayWaitVblankStart();
    sceGuSwapBuffers();
}

void GU_Renderer::clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    unsigned int j = ((b & 0xff) << 16) + ((g & 0xff) << 8) + (r & 0xff);

    sceGuClearDepth(0);
    sceGuClearColor(j);
    sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT | GU_STENCIL_BUFFER_BIT);
}


void GU_Renderer::set_blend_mode(BlendMode mode) {
    switch (mode) {
    case BLENDING_ALPHA:
        sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
        sceGuEnable(GU_BLEND);
        break;
    case BLENDING_OFF:

        break;
    }
}