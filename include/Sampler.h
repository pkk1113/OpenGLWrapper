#pragma once
#include "mygl.h"
#include <memory>

namespace glwrapper
{
	class Sampler
	{
	public:
		class Builder
		{
			GLenum m_wrap_s;
			GLenum m_wrap_t;
			GLenum m_filter_min;
			GLenum m_filter_mag;

		public:
			Builder& Wrap_S(GLenum value) { m_wrap_s = value; return *this; }
			Builder& Wrap_T(GLenum value) { m_wrap_t = value; return *this; }
			Builder& Filter_Min(GLenum value) { m_filter_min = value; return *this; }
			Builder& Filter_Mag(GLenum value) { m_filter_mag = value; return *this; }
			Sampler* Build_Ptr() const;
			std::unique_ptr<Sampler> Build_UniquePtr() const;
		};

	private:
		GLuint m_sampler;

	public:
		explicit Sampler(GLuint sampler);
		~Sampler();
		void Bind(GLuint unit) const { glBindSampler(unit, m_sampler); }
		static void Unbind(GLuint unit) { glBindSampler(unit, 0); }
	};
}