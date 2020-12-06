#pragma once
#include "mygl.h"
#include <cstdlib>

namespace glwrapper
{
	class Cube
	{
		struct Vertex
		{
			float x, y, z;
			float nx, ny, nz;
			float s, t;
		};

		static constexpr GLuint VERTEX_COUNT = 36;
		static constexpr size_t STRIDE = sizeof(Vertex);
		static constexpr size_t POS_OFFSET = offsetof(Vertex, x);
		static constexpr size_t NOR_OFFSET = offsetof(Vertex, nx);
		static constexpr size_t UV_OFFSET = offsetof(Vertex, s);

		GLuint m_vbo;

	public:
		Cube(float width, float height, float depth);
		~Cube();

		void Bind() const;
		static void Unbind();
		static void Draw();

	private:
		static inline void EnableAttributes();
		static inline void DisableAttributes();
	};
}
