#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <unordered_map>
#include <cstdint>
#include <vector>

#include <glad/glad.h>
#include "stb_image.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Probably want to make this an inherited OpenGLShader class, we may have to deal with other shader types

namespace Turbine {
class Shader {
	friend class ShaderManager;
private:
	unsigned int ID;
public:
	void use();
	void compile(const GLchar* vertex_source, const GLchar* fragment_source);
	bool check_compilation_errors(unsigned int object, std::string type);

	bool set_bool(const std::string& name, bool value) const;
	bool set_int(const std::string& name, int value) const;
	bool set_float(const std::string& name, float value) const;
	bool set_vec2(const std::string& name, const glm::vec2& value) const;
	bool set_vec3(const std::string& name, const glm::vec3& value) const;
	bool set_vec4(const std::string& name, const glm::vec4& value) const;
	bool set_mat4(const std::string& name, const glm::mat4& mat) const;

	Shader();
	~Shader();
};

class ShaderManager {
private:
	std::unordered_map<std::string, std::shared_ptr<Shader>> shader_map;
public:
	auto load_shader(const std::string& name, const std::string& vertex_path, const std::string& fragment_path) -> std::shared_ptr<Shader>;
	auto get_shader(const std::string& name) -> std::shared_ptr<Shader>;
	auto remove_shader(const std::string& name) -> void;
	auto clear() -> void;

	inline static auto get() -> ShaderManager& {
		static ShaderManager instance;
		return instance;
	}

	ShaderManager();
	~ShaderManager();
};
}

#endif
