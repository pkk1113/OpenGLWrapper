#include "VertexArray.h"

namespace glwrapper
{

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_vao);
	}

	VertexArray::~VertexArray()
	{
		if (m_vao != 0)
		{
			glDeleteVertexArrays(1, &m_vao);
			m_vao = 0;
		}
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_vao);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	CAutoVertexArray::CAutoVertexArray()
	{
		m_va.Bind();
	}

	CAutoVertexArray::~CAutoVertexArray()
	{
		m_va.Unbind();
	}
}
