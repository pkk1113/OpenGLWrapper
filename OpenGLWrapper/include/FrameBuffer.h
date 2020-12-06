#pragma once
#include "mygl.h"
#include <map>
#include <memory>

namespace glwrapper
{
	class FrameBuffer
	{
		struct Texture
		{
			GLuint name;
			GLenum internalFormat;

			void Bind(GLuint unit) const;
			static void Unbind(GLuint unit);
		};

		using Textures = std::map<GLenum, Texture>;
	public:
		class Builder
		{
			GLsizei m_width;
			GLsizei m_height;
			Textures m_textures;

		public:
			Builder(GLsizei width, GLsizei height) : m_width(width), m_height(height) {}
			/**
			 * @param attach : GL_COLOR_ATTACHMENT0, GL_DEPTH_STENCIL_ATTACHMENT, etc..
			 * @param internalFormat : GL_RGBA32F, GL_DEPTH24_STENCIL8, etc..
			 */
			Builder& Add(GLenum attach, GLenum internalFormat);
			/**
			 * Build all the added with Add().
			 * After Build(), all the added is removed.
			 */
			FrameBuffer* Build_Ptr();
			std::unique_ptr<FrameBuffer> Build_UniquePtr();
		};

	private:
		GLuint m_fbo;
		GLsizei m_width;
		GLsizei m_height;
		Textures m_textures;

	public:
		FrameBuffer(GLuint fbo, GLsizei width, GLsizei height, Textures&& textures);
		~FrameBuffer();
		void Bind(std::initializer_list<GLenum> attachments) const;
		static void Unbind();
		const Texture& operator[](GLuint attachment) const;
		const Texture& Get(GLuint attachment) const;

	private:
		static void Delete(GLuint& fbo, Textures&& textures);
	};
}
