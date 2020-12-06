#pragma once
#include "mygl.h"

namespace glwrapper
{
	class Texture
	{
	public:
		explicit Texture(const char* file);
		Texture(const char* blob, size_t byte);
		Texture(GLenum format, int width, int height, const void* data);
		~Texture();
		void Bind(GLenum unit) const;
		static void Unbind(GLenum unit);

	private:
		GLuint m_texture = 0;
	};
}

