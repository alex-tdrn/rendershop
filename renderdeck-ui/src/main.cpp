#include "renderdeck/RandomColorSource.h"
#include "renderdeck/ClearBackgroundSink.h"
#include "renderdeck/GrayscaleColorPipe.h"
#include "renderdeck/Timer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <vector>


void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

int main(int argc, char** argv)
{
	if(!glfwInit())
		throw "Failed to initialize GLFW!";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
	
	GLFWwindow* window = glfwCreateWindow(200, 300, "renderdeck", nullptr, nullptr);
	if(!window)
		throw "Failed to create GLFW window\n";

	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		throw "Failed to initialize GLAD\n";

#ifdef _DEBUG
	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if(flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
#endif

	using namespace std::chrono_literals;
	glfwSwapInterval(1);

	RandomColorSource source;
	GrayscaleColorPipe pipe;
	ClearBackgroundSink sink;

	sink.getInputPort<ClearBackgroundSink::InputPort::Color>()
		.connect(&pipe.getOutputPort<GrayscaleColorPipe::OutputPort::Color>());

	pipe.getInputPort<GrayscaleColorPipe::InputPort::Color>()
		.connect(&source.getOutputPort<RandomColorSource::OutputPort::Color>());
	
	std::vector<Timer> timers(2);
	timers[0].setInterval(1s);
	timers[0].addSource(&source);
	timers[1].setInterval(1s / 50);
	timers[1].addSink(&sink);

	while(!glfwWindowShouldClose(window))
	{
		while(glfwPollEvents(), !glfwGetWindowAttrib(window, GLFW_FOCUSED))
			std::this_thread::yield();
		
		for(auto& timer : timers)
			timer.poll();

		glfwSwapBuffers(window);
	}
	glfwTerminate();

	return 0;
}

void glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::cout << "-----------------------------------\n"
		<< "OpenGL Debug Message (" << id << "): \n" << message << '\n';
	std::cout << "Source: ";
	switch(source)
	{
	case GL_DEBUG_SOURCE_API:
		std::cout << "API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		std::cout << "Window System";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		std::cout << "Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		std::cout << "Third Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		std::cout << "Application";
		break;
	default:
		std::cout << "Other";
		break;
	}
	std::cout << "\nType: ";
	switch(type)
	{
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "Error";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "Deprecated Behaviour";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "Undefined Behaviour";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "Portability";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "Performance";
		break;
	case GL_DEBUG_TYPE_MARKER:
		std::cout << "Marker";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		std::cout << "Push Group";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		std::cout << "Pop Group";
		break;
	default:
		std::cout << "Other";
		break;
	}
	std::cout << "\nSeverity: ";
	switch(severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "High";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "Medium";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "Low";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::cout << "Notification";
		break;
	}
	std::cout << '\n';
}
