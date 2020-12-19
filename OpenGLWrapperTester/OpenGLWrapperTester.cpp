#include "CppUnitTest.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <OpenGLWrapper.h>
#include <fstream>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpenGLWrapperTester
{
	TEST_CLASS(OpenGLWrapperTester)
	{
	public:

		TEST_METHOD(Shader_FromFile_func)
		{
			glfwInit();
			glfwDefaultWindowHints();
			glfwMakeContextCurrent(glfwCreateWindow(800, 600, "GL Tester", nullptr, nullptr));
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				// file data
				std::string vfd = "#version core 330\n void main() { gl_Position = vec4(0); }";
				std::string ffd = "#version core 330\n void main() { }";

				// file name
				const char* vertFile = "vertFile.vert";
				const char* fragFile = "fragFile.frag";

				// file stream
				std::ofstream vfs(vertFile); vfs << vfd; vfs.close();
				std::ofstream fss(fragFile); fss << ffd; fss.close();

				glwrapper::Shader shader = glwrapper::Shader::FromFile(vertFile, fragFile);
				Assert::AreNotEqual(GLuint(0), shader.id());
			}
			glfwTerminate();
		}
	};
}
