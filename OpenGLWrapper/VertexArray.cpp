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

	void VertexArray::Draw()
	{

	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	GLuint VertexArray::vao() const
	{
		return m_vao;
	}

	AutoVertexArray::AutoVertexArray()
	{
		m_va.Bind();
	}

	AutoVertexArray::~AutoVertexArray()
	{
		m_va.Unbind();
	}
}
