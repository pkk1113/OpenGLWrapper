#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace glwrapper
{
	Texture::Texture(const char* file)
	{
		int w, h, c;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(file, &w, &h, &c, 0);

		if ((data == NULL) ||
			(c < 3))
		{
			stbi_image_free(data);
			return;
		}

		GLenum format = (c == 3) ? GL_RGB : GL_RGBA;

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	Texture::Texture(const char* blob, size_t byte)
	{
		int w, h, c;
		char* data = (char*)stbi_load_from_memory((unsigned char*)(blob), (int)(byte), &w, &h, &c, 0);

		GLenum format = (c == 3) ? GL_RGB : GL_RGBA;

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	Texture::Texture(GLenum format, int width, int height, const void* data)
	{
		if (data == NULL)
		{
			return;
		}

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_texture);
	}

	void Texture::Bind(GLenum unit) const
	{
		glActiveTexture(unit);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}

	void Texture::Unbind(GLenum unit)
	{
		glActiveTexture(unit);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
