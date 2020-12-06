#include "FrameBuffer.h"

namespace glwrapper
{
	FrameBuffer::FrameBuffer(GLuint fbo, GLsizei width, GLsizei height, Textures&& textures) :
		m_fbo(fbo),
		m_width(width),
		m_height(height),
		m_textures(std::move(textures))
	{
	}

	FrameBuffer::~FrameBuffer()
	{
		if (m_fbo != 0)
		{
			Delete(m_fbo, std::move(m_textures));
		}
	}

	void FrameBuffer::Bind(std::initializer_list<GLenum> attachments) const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		glDrawBuffers(attachments.size(), attachments.begin());
		glViewport(0, 0, m_width, m_height);
	}

	void FrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	const FrameBuffer::Texture& FrameBuffer::operator[](GLuint attachment) const
	{
		return m_textures.at(attachment);
	}

	const FrameBuffer::Texture& FrameBuffer::Get(GLuint attachment) const
	{
		return m_textures.at(attachment);
	}

	void FrameBuffer::Delete(GLuint& fbo, Textures&& textures)
	{
		for (auto& tex : textures)
		{
			glDeleteTextures(1, &(tex.second.name));
			tex.second.name = 0;
		}

		glDeleteFramebuffers(1, &fbo);
		fbo = 0;
	}

	FrameBuffer::Builder& FrameBuffer::Builder::Add(GLenum attach, GLenum internalFormat)
	{
		m_textures[attach] = Texture{ 0, internalFormat };
		return *this;
	}

	FrameBuffer* FrameBuffer::Builder::Build_Ptr()
	{
		GLuint fbo;
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		for (auto& tex : m_textures)
		{
			glGenTextures(1, &(tex.second.name));
			glBindTexture(GL_TEXTURE_2D, tex.second.name);
			glTexStorage2D(GL_TEXTURE_2D, 1, tex.second.internalFormat, m_width, m_height);

			glFramebufferTexture2D(GL_FRAMEBUFFER, tex.first, GL_TEXTURE_2D, tex.second.name, 0);
		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			FrameBuffer::Delete(fbo, std::move(m_textures));
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return new FrameBuffer(fbo, m_width, m_height, std::move(m_textures));
	}

	std::unique_ptr<FrameBuffer> FrameBuffer::Builder::Build_UniquePtr()
	{
		GLuint fbo;
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		for (auto& tex : m_textures)
		{
			glGenTextures(1, &(tex.second.name));
			glBindTexture(GL_TEXTURE_2D, tex.second.name);
			glTexStorage2D(GL_TEXTURE_2D, 1, tex.second.internalFormat, m_width, m_height);

			glFramebufferTexture2D(GL_FRAMEBUFFER, tex.first, GL_TEXTURE_2D, tex.second.name, 0);
		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			FrameBuffer::Delete(fbo, std::move(m_textures));
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return std::make_unique<FrameBuffer>(fbo, m_width, m_height, std::move(m_textures));
	}

	void FrameBuffer::Texture::Bind(GLuint unit) const
	{
		glActiveTexture(unit);
		glBindTexture(GL_TEXTURE_2D, name);
	}

	void FrameBuffer::Texture::Unbind(GLuint unit)
	{
		glActiveTexture(unit);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
