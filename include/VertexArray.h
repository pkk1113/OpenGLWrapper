#pragma once
#include "mygl.h"

namespace glwrapper
{
	class VertexArray
	{
		GLuint m_vao;

	public:
		VertexArray();
		~VertexArray();
		void Bind();
		static void Unbind();
	};

	class CAutoVertexArray
	{
		VertexArray m_va;

	public:
		CAutoVertexArray();
		~CAutoVertexArray();
	};
}
