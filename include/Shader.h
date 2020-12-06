#pragma once
#include "mygl.h"

#define SHADER_MACRO(version, shader)\
	"#version " #version "\n"\
	#shader

namespace glwrapper
{
	class Shader
	{
#ifdef _DEBUG
		static size_t m_programBuildCount_;
#endif
		mutable GLint m_loc;
		GLuint m_program;

	public:
		Shader(const char* vert, const char* frag);
		virtual ~Shader();
		void Use() const;
		static void Unuse();

		/* with Name */
		void Set_float(const char* name, GLfloat value) const;
		void Set_vec2(const char* name, const GLfloat* value) const;
		void Set_vec3(const char* name, const GLfloat* value) const;
		void Set_vec4(const char* name, const GLfloat* value) const;
		void Set_int(const char* name, GLint value) const;
		void Set_ivec2(const char* name, const GLint* value) const;
		void Set_ivec3(const char* name, const GLint* value) const;
		void Set_ivec4(const char* name, const GLint* value) const;
		void Set_uint(const char* name, GLuint value) const;
		void Set_uivec2(const char* name, const GLuint* value) const;
		void Set_uivec3(const char* name, const GLuint* value) const;
		void Set_uivec4(const char* name, const GLuint* value) const;
		void Set_mat3(const char* name, const GLfloat* value) const;
		void Set_mat4(const char* name, const GLfloat* value) const;

		/* with Location */
		void Set_float(GLint location, GLfloat value) const;
		void Set_vec2(GLint location, const GLfloat* value) const;
		void Set_vec3(GLint location, const GLfloat* value) const;
		void Set_vec4(GLint location, const GLfloat* value) const;
		void Set_int(GLint location, GLint value) const;
		void Set_ivec2(GLint location, const GLint* value) const;
		void Set_ivec3(GLint location, const GLint* value) const;
		void Set_ivec4(GLint location, const GLint* value) const;
		void Set_uint(GLint location, GLuint value) const;
		void Set_uivec2(GLint location, const GLuint* value) const;
		void Set_uivec3(GLint location, const GLuint* value) const;
		void Set_uivec4(GLint location, const GLuint* value) const;
		void Set_mat3(GLint location, const GLfloat* value) const;
		void Set_mat4(GLint location, const GLfloat* value) const;

	private:
		static GLuint LoadOpenGLProgram(const char* vertexSource, const char* fragmentSource);
		static GLuint LoadOpenGLShader(const char* source, GLenum target);
	};
}
