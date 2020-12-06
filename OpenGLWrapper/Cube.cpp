#include "Cube.h"

namespace glwrapper
{
	Cube::Cube(float width, float height, float depth)
	{
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		const float hw = width * 0.5f;
		const float hh = height * 0.5f;
		const float hd = depth * 0.5f;

		const Vertex data[] = {
			// +z
			{ -hw, -hh,	+hd,		0.f, 0.f, +1.f,			0.f, 0.f },
			{ +hw, -hh,	+hd,		0.f, 0.f, +1.f,			1.f, 0.f },
			{ -hw, +hh,	+hd,		0.f, 0.f, +1.f,			0.f, 1.f },
			{ -hw, +hh,	+hd,		0.f, 0.f, +1.f,			0.f, 1.f },
			{ +hw, -hh,	+hd,		0.f, 0.f, +1.f,			1.f, 0.f },
			{ +hw, +hh,	+hd,		0.f, 0.f, +1.f,			1.f, 1.f },
			// -z
			{ +hw, -hh,	-hd,		0.f, 0.f, -1.f,			0.f, 0.f },
			{ -hw, -hh,	-hd,		0.f, 0.f, -1.f,			1.f, 0.f },
			{ +hw, +hh,	-hd,		0.f, 0.f, -1.f,			0.f, 1.f },
			{ +hw, +hh,	-hd,		0.f, 0.f, -1.f,			0.f, 1.f },
			{ -hw, -hh,	-hd,		0.f, 0.f, -1.f,			1.f, 0.f },
			{ -hw, +hh,	-hd,		0.f, 0.f, -1.f,			1.f, 1.f },
			// +x
			{ +hw, -hh,	+hd,		+1.f, 0.f, 0.f,			0.f, 0.f },
			{ +hw, -hh,	-hd,		+1.f, 0.f, 0.f,			1.f, 0.f },
			{ +hw, +hh,	+hd,		+1.f, 0.f, 0.f,			0.f, 1.f },
			{ +hw, +hh,	+hd,		+1.f, 0.f, 0.f,			0.f, 1.f },
			{ +hw, -hh,	-hd,		+1.f, 0.f, 0.f,			1.f, 0.f },
			{ +hw, +hh,	-hd,		+1.f, 0.f, 0.f,			1.f, 1.f },
			// -x
			{ -hw, -hh,	-hd,		-1.f, 0.f, 0.f,			0.f, 0.f },
			{ -hw, -hh,	+hd,		-1.f, 0.f, 0.f,			1.f, 0.f },
			{ -hw, +hh,	-hd,		-1.f, 0.f, 0.f,			0.f, 1.f },
			{ -hw, +hh,	-hd,		-1.f, 0.f, 0.f,			0.f, 1.f },
			{ -hw, -hh,	+hd,		-1.f, 0.f, 0.f,			1.f, 0.f },
			{ -hw, +hh,	+hd,		-1.f, 0.f, 0.f,			1.f, 1.f },
			// +y
			{ -hw, +hh,	+hd,		0.f, +1.f, 0.f,			0.f, 0.f },
			{ +hw, +hh,	+hd,		0.f, +1.f, 0.f,			1.f, 0.f },
			{ -hw, +hh,	-hd,		0.f, +1.f, 0.f,			0.f, 1.f },
			{ -hw, +hh,	-hd,		0.f, +1.f, 0.f,			0.f, 1.f },
			{ +hw, +hh,	+hd,		0.f, +1.f, 0.f,			1.f, 0.f },
			{ +hw, +hh,	-hd,		0.f, +1.f, 0.f,			1.f, 1.f },
			// -y
			{ -hw, -hh,	-hd,		0.f, -1.f, 0.f,			0.f, 0.f },
			{ +hw, -hh,	-hd,		0.f, -1.f, 0.f,			1.f, 0.f },
			{ -hw, -hh,	+hd,		0.f, -1.f, 0.f,			0.f, 1.f },
			{ -hw, -hh,	+hd,		0.f, -1.f, 0.f,			0.f, 1.f },
			{ +hw, -hh,	-hd,		0.f, -1.f, 0.f,			1.f, 0.f },
			{ +hw, -hh,	+hd,		0.f, -1.f, 0.f,			1.f, 1.f },
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Cube::~Cube()
	{
		if (m_vbo != 0)
		{
			glDeleteBuffers(1, &m_vbo);
			m_vbo = 0;
		}
	}

	void Cube::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		EnableAttributes();
	}

	void Cube::Unbind()
	{
		DisableAttributes();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Cube::Draw()
	{
		glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT);
	}

	void Cube::EnableAttributes()
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE, (void*)POS_OFFSET);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE, (void*)NOR_OFFSET);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, STRIDE, (void*)UV_OFFSET);
	}

	void Cube::DisableAttributes()
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}
