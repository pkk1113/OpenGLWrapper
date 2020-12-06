#pragma once
#include "mygl.h"
#include <cstdlib>

namespace glwrapper
{
	class Plane
	{
		struct Vertex
		{
			float x, y, z;
			float nx, ny, nz;
			float s, t;
		};

		static constexpr GLuint VERTEX_COUNT = 4;
		static constexpr size_t STRIDE = sizeof(Vertex);
		static constexpr size_t POS_OFFSET = offsetof(Vertex, x);
		static constexpr size_t NOR_OFFSET = offsetof(Vertex, nx);
		static constexpr size_t UV_OFFSET = offsetof(Vertex, s);

		GLuint m_vbo;

	public:
		Plane(float width, float height);
		~Plane();

		void Bind() const;
		static void Unbind();
		static void Draw();

	private:
		static inline void EnableAttributes();
		static inline void DisableAttributes();
	};
}

