#include "Sampler.h"
#include "FrameBuffer.h"

namespace glwrapper
{


	Sampler::Sampler(GLuint sampler) :
		m_sampler(sampler)
	{}

	Sampler::~Sampler()
	{
		glDeleteSamplers(1, &m_sampler);
	}

	Sampler* Sampler::Builder::Build_Ptr() const
	{
		GLuint sampler;
		glGenSamplers(1, &sampler);

		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, m_wrap_s);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, m_wrap_t);
		glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, m_filter_mag);
		glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, m_filter_min);

		return new Sampler(sampler);
	}

	std::unique_ptr<Sampler> Sampler::Builder::Build_UniquePtr() const
	{
		GLuint sampler;
		glGenSamplers(1, &sampler);

		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, m_wrap_s);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, m_wrap_t);
		glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, m_filter_mag);
		glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, m_filter_min);

		return std::make_unique<Sampler>(sampler);
	}
}
