#include "Plane.h"

namespace glwrapper
{
	Plane::Plane(float width, float height)
	{
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		float hw = width * 0.5f;
		float hh = height * 0.5f;

		Vertex data[] = {
			// xy				nor					tex coord
			{ -hw, -hh, 0.f,	0.f, 0.f, 1.f,		0.f, 0.f },
			{ +hw, -hh, 0.f,	0.f, 0.f, 1.f,		1.f, 0.f },
			{ -hw, +hh, 0.f,	0.f, 0.f, 1.f,		0.f, 1.f },
			{ +hw, +hh, 0.f,	0.f, 0.f, 1.f,		1.f, 1.f },
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Plane::~Plane()
	{
		glDeleteBuffers(1, &m_vbo);
	}

	void Plane::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		EnableAttributes();
	}

	void Plane::Unbind()
	{
		DisableAttributes();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Plane::Draw()
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 0, VERTEX_COUNT);
	}

	void Plane::EnableAttributes()
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE, (void*)POS_OFFSET);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE, (void*)NOR_OFFSET);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, STRIDE, (void*)UV_OFFSET);
	}

	void Plane::DisableAttributes()
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}
