#include "Shader.h"
#ifdef _DEBUG
#include <cstdio>
#endif
#include <fstream>
#include <sstream>

namespace glwrapper
{
#ifdef _DEBUG
	size_t Shader::m_programBuildCount_ = 0;
#endif

	Shader::Shader(const char* vert, const char* frag) :
		m_program(LoadOpenGLProgram(vert, frag))
	{}

	Shader::~Shader()
	{
		if (m_program != 0)
		{
			glDeleteProgram(m_program);
			m_program = 0;
		}
	}

	Shader Shader::FromFile(const char* vertFile, const char* fragFile)
	{
		auto vert = LoadFileData(vertFile);
		auto frag = LoadFileData(fragFile);
		return Shader(vert.c_str(), frag.c_str());
	}

	GLuint Shader::id() const
	{
		return m_program;
	}

	void Shader::Use() const
	{
		glUseProgram(m_program);
	}

	void Shader::Unuse()
	{
		glUseProgram(0);
	}

	void Shader::Set_float(const char* name, GLfloat value) const
	{
		glUniform1f(m_loc = glGetUniformLocation(m_program, name), value);
		// glProgramUniform1f(m_program, m_loc = glGetUniformLocation(m_program, name), value);
	}

	void Shader::Set_vec2(const char* name, const GLfloat* value) const
	{
		glUniform2fv(m_loc = glGetUniformLocation(m_program, name), 1, value);
	}

	void Shader::Set_vec3(const char* name, const GLfloat* value) const
	{
		glUniform3fv(m_loc = glGetUniformLocation(m_program, name), 1, value);
	}

	void Shader::Set_vec4(const char* name, const GLfloat* value) const
	{
		glUniform4fv(m_loc = glGetUniformLocation(m_program, name), 1, value);
	}

	void Shader::Set_int(const char* name, GLint value) const
	{
		glUniform1i(m_loc = glGetUniformLocation(m_program, name), value);
	}

	void Shader::Set_ivec2(const char* name, const GLint* value) const
	{
		glUniform2iv(m_loc = glGetUniformLocation(m_program, name), 1, value);
	}

	void Shader::Set_ivec3(const char* name, const GLint* value) const
	{
		glUniform3iv(m_loc = glGetUniformLocation(m_program, name), 1, value);
	}

	void Shader::Set_ivec4(const char* name, const GLint* value) const
	{
		glUniform4iv(m_loc = glGetUniformLocation(m_program, name), 1, value);
	}

	void Shader::Set_uint(const char* name, GLuint value) const
	{
		glUniform1ui(m_loc = glGetUniformLocation(m_program, name), value);
	}

	void Shader::Set_uivec2(const char* name, const GLuint* value) const
	{
		glUniform2uiv(m_loc = glGetUniformLocation(m_program, name), 1, value);
	}

	void Shader::Set_uivec3(const char* name, const GLuint* value) const
	{
		glUniform3uiv(m_loc = glGetUniformLocation(m_program, name), 1, value);
	}

	void Shader::Set_uivec4(const char* name, const GLuint* value) const
	{
		glUniform4uiv(m_loc = glGetUniformLocation(m_program, name), 1, value);
	}

	void Shader::Set_mat3(const char* name, const GLfloat* value) const
	{
		glUniformMatrix3fv(m_loc = glGetUniformLocation(m_program, name), 1, GL_FALSE, value);
	}

	void Shader::Set_mat4(const char* name, const GLfloat* value) const
	{
		glUniformMatrix4fv(m_loc = glGetUniformLocation(m_program, name), 1, GL_FALSE, value);
	}

	//

	void Shader::Set_float(GLint location, GLfloat value) const
	{
		glUniform1f(location, value);
	}

	void Shader::Set_vec2(GLint location, const GLfloat* value) const
	{
		glUniform2fv(location, 1, value);
	}

	void Shader::Set_vec3(GLint location, const GLfloat* value) const
	{
		glUniform3fv(location, 1, value);
	}

	void Shader::Set_vec4(GLint location, const GLfloat* value) const
	{
		glUniform4fv(location, 1, value);
	}

	void Shader::Set_int(GLint location, GLint value) const
	{
		glUniform1i(location, value);
	}

	void Shader::Set_ivec2(GLint location, const GLint* value) const
	{
		glUniform2iv(location, 1, value);
	}

	void Shader::Set_ivec3(GLint location, const GLint* value) const
	{
		glUniform3iv(location, 1, value);
	}

	void Shader::Set_ivec4(GLint location, const GLint* value) const
	{
		glUniform4iv(location, 1, value);
	}

	void Shader::Set_uint(GLint location, GLuint value) const
	{
		glUniform1ui(location, value);
	}

	void Shader::Set_uivec2(GLint location, const GLuint* value) const
	{
		glUniform2uiv(location, 1, value);
	}

	void Shader::Set_uivec3(GLint location, const GLuint* value) const
	{
		glUniform3uiv(location, 1, value);
	}

	void Shader::Set_uivec4(GLint location, const GLuint* value) const
	{
		glUniform4uiv(location, 1, value);
	}

	void Shader::Set_mat3(GLint location, const GLfloat* value) const
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, value);
	}

	void Shader::Set_mat4(GLint location, const GLfloat* value) const
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, value);
	}


	GLuint Shader::LoadOpenGLProgram(const char* vertexSource, const char* fragmentSource)
	{
#ifdef _DEBUG
		m_programBuildCount_ += 1;
#endif

		bool result = false;
		GLuint program = 0;
		GLuint vertexShader = 0;
		GLuint fragmentShader = 0;
		GLint linkStatus;

		do
		{
			vertexShader = LoadOpenGLShader(vertexSource, GL_VERTEX_SHADER);
			if (0 == vertexShader)
				break;

			fragmentShader = LoadOpenGLShader(fragmentSource, GL_FRAGMENT_SHADER);
			if (0 == fragmentShader)
				break;

			program = glCreateProgram();
			if (0 == program)
				break;

			glAttachShader(program, vertexShader);
			glAttachShader(program, fragmentShader);

			glLinkProgram(program);

			glDetachShader(program, vertexShader);
			glDetachShader(program, fragmentShader);

			glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

			if (GL_FALSE == linkStatus)
			{
#ifdef _DEBUG
				GLchar errorLog[512];
				glGetProgramInfoLog(program, 512, nullptr, errorLog);
				printf("Build Count: %02d ====================================\n", m_programBuildCount_);
				puts("[Link Error]");
				puts(errorLog);
#endif
				break;
			}

			result = true;
		} while (false);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		if (false == result)
		{
			glDeleteProgram(program);
			program = 0;
		}

		return program;
	}

	GLuint Shader::LoadOpenGLShader(const char* source, GLenum type)
	{
		GLuint shader = glCreateShader(type);
		GLint compileStatue;

		if (0 == shader)
		{
			return 0;
		}

		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatue);

		if (GL_FALSE == compileStatue)
		{
#ifdef _DEBUG
			GLchar errorLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, errorLog);
			printf("Build Count: %02d ====================================\n", m_programBuildCount_);
			puts((type == GL_VERTEX_SHADER) ? "[Vertex Compile Error]" : "[Fragment Compile Error]");
			puts(errorLog);
#endif
			glDeleteShader(shader);
			shader = 0;
		}

		return shader;
	}

	std::string Shader::LoadFileData(const char* file)
	{
		std::ifstream f(file);
		std::stringstream ss;
		ss << f.rdbuf();
		return ss.str();
	}
}
