#include "systems/sprite_system.hpp"
#include "components/common.hpp"

namespace Turbine {
	SpriteSystem::SpriteSystem(){
#if !PSP
		if(sprite_shader == nullptr)
			sprite_shader = ShaderManager::get().load_shader("sprite_shader", "./shaders/shader.vert", "./shaders/shader.frag");
		if(sprite_vbo == nullptr)
			sprite_vbo = std::make_shared<OpenGLVertexBuffer>();
		if(sprite_vao == nullptr)
			sprite_vao = std::make_shared<OpenGLVertexArray>();

		vertex_layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		sprite_vbo->set_layout(vertex_layout);
		sprite_vao->add_vertex_buffer(sprite_vbo);
#endif
	}
	SpriteSystem::~SpriteSystem(){}

	auto SpriteSystem::initialize_mesh(SpriteComponent& sprite) -> void {
		if(sprite.mesh == nullptr)
			sprite.mesh = std::make_unique<FixedMesh<Vertex, 4, 6>>();

		sprite.mesh->vertices[0] = Vertex{sprite.region_rect.x/sprite.texture->width, sprite.region_rect.y/sprite.texture->height, 0xFFFFFFFF, 0.0f, 0.0f, -1.0f };
		sprite.mesh->vertices[1] = Vertex{(sprite.region_rect.x + sprite.region_rect.width)/sprite.texture->width, sprite.region_rect.y/sprite.texture->height, 0xFFFFFFFF, sprite.region_rect.width, 0.0f, -1.0f };
		sprite.mesh->vertices[2] = Vertex{(sprite.region_rect.x + sprite.region_rect.width)/sprite.texture->width, (sprite.region_rect.y + sprite.region_rect.height)/sprite.texture->height, 0xFFFFFFFF, sprite.region_rect.width, sprite.region_rect.height, -1.0f };
		sprite.mesh->vertices[3] = Vertex{sprite.region_rect.x/sprite.texture->width, (sprite.region_rect.y + sprite.region_rect.height)/sprite.texture->height, 0xFFFFFFFF, 0.0f, sprite.region_rect.height, -1.0f };

		sprite.mesh->indices[0] = 0;
		sprite.mesh->indices[1] = 1;
		sprite.mesh->indices[2] = 2;
		sprite.mesh->indices[3] = 2;
		sprite.mesh->indices[4] = 3;
		sprite.mesh->indices[5] = 0;
	}

	auto SpriteSystem::update(const std::shared_ptr<Scene>& scene) -> void {
		auto view = scene->get_registry().view<Turbine::TransformComponent>();
		for(auto entity: view) {
			auto &transform = view.get<Turbine::TransformComponent>(entity);
			transform.position.x += 1.0f;
		}
	}

	auto SpriteSystem::draw(const std::shared_ptr<Scene>& scene) -> void {
		auto view = scene->get_registry().view<Turbine::SpriteComponent, Turbine::TransformComponent>();
		for(auto entity: view) {
			// Local transform of the sprite
			auto &sprite = view.get<Turbine::SpriteComponent>(entity);
			// Global transform of the host entity (temporary hierarchy structure)
			auto &transform = view.get<Turbine::TransformComponent>(entity);

		#if PSP
			sceGumMatrixMode(GU_MODEL);
			sceGumLoadIdentity();
			ScePspFVector3 v = {
				.x = sprite.transform.position.x + transform.position.x,
				.y = sprite.transform.position.y + transform.position.y,
				.z = -1.0f,
			};
			sceGumTranslate(&v);
			sceGumRotateZ(sprite.transform.rotation);
			ScePspFVector3 s = {
				.x = sprite.transform.scale.x + transform.scale.x,
				.y = sprite.transform.scale.y + transform.scale.y,
				.z = -1.0f,
			};
			sceGumScale(&s);
			ScePspFVector3 o = {
				.x = -sprite.origin.x,
				.y = -sprite.origin.y,
				.z = -1.0f,
			};
			sceGumTranslate(&o);
		#endif

		#if !PSP
			sprite_shader->use();
			sprite_vao->bind();
		#endif

			if(sprite.texture != nullptr)
				sprite.texture->bind();

			sprite.mesh->draw();
		}
	}
}
