#pragma once
#include <mygl.h>

namespace glwrapper
{
	class VertexArray
	{
		GLuint m_vao;

	public:
		VertexArray();
		~VertexArray();
		virtual void Bind();
		virtual void Draw();
		virtual void Unbind();
		GLuint vao() const;
	};

	class AutoVertexArray
	{
		VertexArray m_va;

	public:
		AutoVertexArray();
		~AutoVertexArray();
	};
}
