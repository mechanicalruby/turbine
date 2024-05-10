#include "components/common.hpp"
#include <iostream>
#include <memory>

#if !PSP
	#include "renderer/opengl/gl.hpp"
	#include "renderer/opengl/vbuffer.hpp"
	#include "renderer/opengl/varray.hpp"
	#include "renderer/shader.hpp"

	#include "imgui.h"
	#include "backends/imgui_impl_glfw.h"
	#include "backends/imgui_impl_opengl3.h"
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
#include "systems/camera_system.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

auto main(void) -> int {
#if PSP
	GU_Renderer* renderer = new GU_Renderer();
	sce_psp::setup_callbacks();
	renderer->initialize("Turbine", 480, 272);
#else
	OpenGL_Renderer* renderer = new OpenGL_Renderer();
	renderer->initialize("Turbine", 1280, 720);
	glm::mat4 projection = glm::ortho(0.0f, 480.0f, 272.0f, 0.0f, -1.0f, 1.0f);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; 
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	ImGui_ImplGlfw_InitForOpenGL(renderer->window, true);
	ImGui_ImplOpenGL3_Init();
#endif

	auto texman = std::make_unique<Turbine::TextureManager>();
	auto texture = texman->load_texture("atlas", "./sample/player.png", true, TB_NEAREST, TB_NEAREST);
	auto texture1 = texman->load_texture("raft", "./sample/raft.png", true, TB_NEAREST, TB_NEAREST);

	Turbine::SpriteSystem sprite_system;
	Turbine::CameraSystem camera_system;

	auto scene = std::make_shared<Turbine::Scene>();
	auto player = scene->create_entity();
	player.add_component<Turbine::TransformComponent>(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 0.0f);
	player.add_component<Turbine::SpriteComponent>();
	player.get_component<Turbine::SpriteComponent>().texture = texture;
	player.get_component<Turbine::SpriteComponent>().transform = Turbine::TransformComponent({0.0f, 0.0f}, {1.0f, 1.0f}, 0.0f);
	player.get_component<Turbine::SpriteComponent>().region_rect = Rectangle(0, 0, 64, 64);
	sprite_system.initialize_mesh(player.get_component<Turbine::SpriteComponent>());
	
	auto raft = scene->create_entity();
	raft.add_component<Turbine::TransformComponent>(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 0.0f);
	raft.add_component<Turbine::SpriteComponent>();
	raft.get_component<Turbine::SpriteComponent>().texture = texture1;
	raft.get_component<Turbine::SpriteComponent>().transform = Turbine::TransformComponent({20.0f, 20.0f}, {1.0f, 1.0f}, 0.0f);
	raft.get_component<Turbine::SpriteComponent>().region_rect = Rectangle(0, 0, 64, 64);
	sprite_system.initialize_mesh(raft.get_component<Turbine::SpriteComponent>());
	
	std::vector<std::string> scenes = Turbine::get_scenes_in_directory("./sample/scenes/");

	auto camera = scene->create_entity();
	camera.add_component<Turbine::CameraComponent>();
	camera.add_component<Turbine::TransformComponent>(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 0.0f);
	
#if PSP
	renderer->set_ortho();
#endif
	while(true) {
		sprite_system.update(scene);

		renderer->begin_frame();
		renderer->set_blend_mode(BLENDING_ALPHA);
		renderer->clear(0, 0, 0, 255);

		sprite_system.draw(scene);

#if !PSP
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
		renderer->end_frame();
	}
	renderer->clean_up();
#if !PSP
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif
	return 0;
}
