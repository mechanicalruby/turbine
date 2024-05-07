#include "systems/sprite_system.hpp"
#include "components/common.hpp"

namespace Turbine {
	SpriteSystem::SpriteSystem(){}
	SpriteSystem::~SpriteSystem(){}

	auto SpriteSystem::initialize_mesh(SpriteComponent& sprite) -> void {
		if(sprite.mesh == nullptr)
			sprite.mesh = std::make_unique<FixedMesh<Vertex, 4, 6>>();

		sprite.mesh->vertices[0] = Vertex{ 0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f, -1.0f };
		sprite.mesh->vertices[1] = Vertex{ 1.0f, 0.0f, 0xFFFFFFFF, 128.0f, 0.0, -1.0f };
		sprite.mesh->vertices[2] = Vertex{ 1.0f, 1.0f, 0xFFFFFFFF, 128.0f, 128.0f, -1.0f };
		sprite.mesh->vertices[3] = Vertex{ 0.0f, 1.0f, 0xFFFFFFFF, 0.0f, 128.0f, -1.0f };

		sprite.mesh->indices[0] = 0;
		sprite.mesh->indices[1] = 1;
		sprite.mesh->indices[2] = 2;
		sprite.mesh->indices[3] = 2;
		sprite.mesh->indices[4] = 3;
		sprite.mesh->indices[5] = 0;
	}

	auto SpriteSystem::update(const std::shared_ptr<Scene>& scene) -> void {

	}

	auto SpriteSystem::draw(const std::shared_ptr<Scene>& scene) -> void {
		auto view = scene->get_registry().view<Turbine::SpriteComponent>();
		for(auto entity: view) {
			auto &sprite = view.get<Turbine::SpriteComponent>(entity);

		#if PSP
			sceGumMatrixMode(GU_MODEL);
			sceGumLoadIdentity();
			ScePspFVector3 v = {
				.x = sprite.transform.position.x,
				.y = sprite.transform.position.y,
				.z = -1.0f,
			};
			sceGumTranslate(&v);
			sceGumRotateZ(sprite.transform.rotation);
			ScePspFVector3 s = {
				.x = sprite.transform.scale.x,
				.y = sprite.transform.scale.y,
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

			if(sprite.texture != nullptr)
				sprite.texture->bind();

			sprite.mesh->draw();
		}
	}
}
