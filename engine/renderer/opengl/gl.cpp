#include "gl.hpp"

OpenGL_Renderer::OpenGL_Renderer() {}

bool OpenGL_Renderer::initialize(const std::string& title, int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Turn off resizing
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    // glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (window == NULL)
    {
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
	glViewport(0, 0, width, height);
    });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
	std::cout << "Failed to initialize GLAD" << std::endl;
	return false;
    }

    return true;
}

bool OpenGL_Renderer::should_window_close() {
    return glfwWindowShouldClose(window);
}

void OpenGL_Renderer::clean_up()
{
    std::cout << "Closing renderer." << '\n';
    glfwDestroyWindow(window);
    glfwTerminate();
}

void OpenGL_Renderer::begin_frame() {

}

void OpenGL_Renderer::end_frame() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void OpenGL_Renderer::clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL_Renderer::set_blend_mode(BlendMode mode)
{
    switch (mode) {
    case BLENDING_ALPHA:
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	break;
    case BLENDING_OFF:
	break;
    }
}

#if WIN32

#endif
