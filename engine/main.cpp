#include "components/common.hpp"
#include <iostream>
#include <memory>

#if !PSP
	#include "renderer/opengl/gl.hpp"
	#include "renderer/opengl/vbuffer.hpp"
	#include "renderer/opengl/varray.hpp"
	#include "renderer/shader.hpp"
#endif

#if PSP
	#include <pspkernel.h>
	#include <pspdebug.h>
	#include <pspdisplay.h>
	#include <pspctrl.h>

	#include "platform/psp/callbacks.hpp"
	#include "renderer/gu/gu.hpp"

	PSP_MODULE_INFO("turbine", 0, 1, 1);
	PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
#endif

#include "renderer/mesh.hpp"
#include "renderer/texture.hpp"
#include "scene/scene.hpp"
#include "scene/scene_tools.hpp"
#include "scene/entity.hpp"

#include "systems/sprite_system.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

int main(void) {
#if PSP
    GU_Renderer* renderer = new GU_Renderer();
    sce_psp::setup_callbacks();
#else
    OpenGL_Renderer* renderer = new OpenGL_Renderer();
#endif
    renderer->initialize("Turbine", 480, 272);

    auto texman = std::make_unique<Turbine::TextureManager>();
    auto texture = texman->load_texture("atlas", "./sample/bread1.png", true, TB_NEAREST, TB_NEAREST);
	auto texture1 = texman->load_texture("raft", "./sample/raft.png", true, TB_NEAREST, TB_NEAREST);

	Turbine::SpriteSystem sprite_system;

    auto scene = std::make_shared<Turbine::Scene>();
    auto player = scene->create_entity();
	player.add_component<Turbine::SpriteComponent>();
	player.get_component<Turbine::SpriteComponent>().texture = texture;
    sprite_system.initialize_mesh(player.get_component<Turbine::SpriteComponent>());

	auto raft = scene->create_entity();
	raft.add_component<Turbine::SpriteComponent>();
	raft.get_component<Turbine::SpriteComponent>().texture = texture1;
    sprite_system.initialize_mesh(raft.get_component<Turbine::SpriteComponent>());

    renderer->set_ortho();
    while(true) {
		renderer->begin_frame();
		renderer->set_blend_mode(BLENDING_ALPHA);
		renderer->clear(0, 40, 125, 255);

		sprite_system.update(scene);

		renderer->end_frame();
    }
    return 0;
}
