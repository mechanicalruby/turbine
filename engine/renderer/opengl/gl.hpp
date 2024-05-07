#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../renderer.hpp"

class OpenGL_Renderer : public Renderer {
public:
	OpenGL_Renderer();
	~OpenGL_Renderer() = default;

	bool initialize(const std::string& title, int width, int height);
	void clean_up();

	bool should_window_close();

	void begin_frame();
	void end_frame();

	void clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void set_blend_mode(BlendMode mode);

	GLFWwindow* window;
};

#endif