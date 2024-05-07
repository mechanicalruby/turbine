#include "shader.hpp"

// Shader ------
namespace Turbine {
Shader::Shader() {}
Shader::~Shader() {}

void Shader::use() {
	glUseProgram(this->ID);
}

void Shader::compile(const GLchar* vertex_source, const GLchar* fragment_source) {
	unsigned int sVertex, sFragment, gShader;

	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertex_source, NULL);
	glCompileShader(sVertex);
	check_compilation_errors(sVertex, "VERTEX");

	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragment_source, NULL);
	glCompileShader(sFragment);
	check_compilation_errors(sFragment, "FRAGMENT");

	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);
	glAttachShader(this->ID, sFragment);

	glLinkProgram(this->ID);
	check_compilation_errors(this->ID, "PROGRAM");

	// delete the already linked shaders
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
}

bool Shader::check_compilation_errors(unsigned int object, std::string type) {
	if (type != "PROGRAM") {
		GLint isCompiled;
		glGetShaderiv(object, GL_COMPILE_STATUS, &isCompiled);

		if (!isCompiled) {
			GLint maxLength = 0;
			glGetShaderiv(object, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(1024);
			glGetShaderInfoLog(object, maxLength, &maxLength, &errorLog[0]);
			std::cout << "Failed to compile shader" << '\n';
			return false;
		}
	}
	else {
		// test
		int success;
		char infoLog[512];
		glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
			std::cout << infoLog << std::endl;
		}
	}

	return true;
}

bool Shader::set_bool(const std::string& name, bool value) const {
	auto location = glGetUniformLocation(this->ID, name.c_str());
	if (location == -1)
		return false;

	glUniform1i(location, value);
	return true;
}

bool Shader::set_int(const std::string& name, int value) const {
	auto location = glGetUniformLocation(this->ID, name.c_str());
	if (location == -1)
		return false;

	glUniform1f(location, value);
	return true;
}

bool Shader::set_float(const std::string& name, float value) const {
	auto location = glGetUniformLocation(this->ID, name.c_str());
	if (location == -1)
		return false;

	glUniform1f(location, value);
	return true;
}

bool Shader::set_vec2(const std::string& name, const glm::vec2& value) const {
	auto location = glGetUniformLocation(this->ID, name.c_str());
	if (location == -1)
		return false;

	glUniform2f(location, value.x, value.y);
	return true;
}

bool Shader::set_vec3(const std::string& name, const glm::vec3& value) const {
	glUniform3f(glGetUniformLocation(this->ID, name.c_str()), value.x, value.y, value.z);
	return true;
}

bool Shader::set_vec4(const std::string& name, const glm::vec4& value) const {
	glUniform4f(glGetUniformLocation(this->ID, name.c_str()), value.x, value.y, value.z, value.w);
	return true;
}

bool Shader::set_mat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	return true;
}

// ShaderManager ------

ShaderManager::ShaderManager() {};
ShaderManager::~ShaderManager() {};

auto ShaderManager::load_shader(const std::string& name, const std::string& vertex_path, const std::string& fragment_path) -> std::shared_ptr<Shader> {
	std::string vertexCode;
	std::string fragmentCode;

	try {
		std::ifstream vertexShaderFile(vertex_path);
		std::ifstream fragmentShaderFile(fragment_path);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::exception e) {
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	auto shader = std::make_shared<Shader>();
	shader->compile(vShaderCode, fShaderCode);
	shader_map.emplace(name, shader);
	return shader;
}

auto ShaderManager::get_shader(const std::string& name) -> std::shared_ptr<Shader> {
	std::unordered_map<std::string, std::shared_ptr<Shader>>::iterator it = shader_map.find(name);
	if (it != shader_map.end()) {
		return it->second;
	}
	return nullptr;
}

auto ShaderManager::clear() -> void {
	shader_map.clear();
}
}