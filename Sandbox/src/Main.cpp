#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

#if defined(_DEBUG) || defined(DEBUG) || !defined(NDEBUG)
    #define GL_CALL(x) \
        do { \
            x; \
            GLenum err; \
            while ((err = glGetError()) != GL_NO_ERROR) { \
                fprintf(stderr, "[OpenGL Error] (%d): %s in %s:%d\n", err, #x, __FILE__, __LINE__); \
                __debugbreak(); \
            } \
        } while (0)
#else
    #define GL_CALL(x) x
#endif

GLuint _width = 1280;
GLuint _height = 720;
const char* _title = "Sandbox";

GLFWwindow* _window;

int main()
{
    glfwSetErrorCallback([](int error, const char* description)
    {
        fprintf(stderr, "GLFW Error: %s\n", description);
    });

    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
    if (_window == nullptr)
    {
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        glfwTerminate();
        return -3;
    }

    GL_CALL(glEnable(GL_DEBUG_OUTPUT));
    GL_CALL(glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        fprintf(stderr, "[OpenGL Debug] %s\n", message);
    }, nullptr));

    // CornFlower Blue  0x6495ed | 100, 149, 237
    GL_CALL(glClearColor(0.392f, 0.584f, 0.929f, 1.0f));

    while (!glfwWindowShouldClose(_window))
    {
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        // start rendering here

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}