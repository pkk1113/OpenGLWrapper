#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace glwrapper
{
	class Camera
	{
		glm::ivec4 m_vp;

		enum { ortho, persp } m_pmode = persp;
		float m_near = 0.1f;
		float m_far = 1000.f;
		float m_fov = 45.f; // (m_fov > 0) && (m_fov < 90)

		glm::vec3 m_pos;
		glm::quat m_rot;

	public:
		Camera();
		~Camera();

	public:
		//viewport
		void setViewport(int x, int y, int w, int h);

		//projection
		void setPerspMode();
		void setOrthoMode();
		void setNearAndFar(float near, float far);
		void setFov(float fov);
		void adjustFov(float deg);
		void adjustNear(float delta);
		void adjustFar(float delta);

		//view
		void setToPosIdentity();
		void setToRotIdentity();
		void setPos(float x, float y, float z);
		void setPos(const glm::vec3& pos);
		void setRot(float deg, const glm::vec3& axis);
		void setRot(const glm::quat& rot);
		void translate(float x, float y, float z);
		void translate(const glm::vec3& delta);
		void rotate(float deg, const glm::vec3& axis);
		void rotate(const glm::quat& rot);
		void lookAt(const glm::vec3& target, const glm::vec3& up = glm::vec3(0, 1, 0));
		void lookAt(float x, float y, float z, const glm::vec3& up = glm::vec3(0, 1, 0));
		void rotateAround(float deg, const glm::vec3& axis, const glm::vec3& target);
		void rotateAround(const glm::quat& rot, const glm::vec3& target);

	public:
		const glm::ivec4& getViewport() const;
		const int getWidth() const;
		const int getHeight() const;
		const glm::vec3& getPos() const;
		const glm::quat& getRot() const;
		float getNear() const;
		float getFar() const;
		float getFov() const;
		float getAspect() const;

		glm::vec3 getFront() const;
		glm::vec3 getBack() const;
		glm::vec3 getUp() const;
		glm::vec3 getDown() const;
		glm::vec3 getLeft() const;
		glm::vec3 getRight() const;

		const glm::mat4& getViewMatrix() const;
		const glm::mat4& getProjectionMatrix() const;

		const float* getPosPtr() const;
		const float* getViewMatrixPtr() const;
		const float* getProjectionMatrixPtr() const;

	public:
		glm::vec3 getRayFromScreen(int sx, int sy) const;
		glm::vec3 getNearPosFromScreen(int sx, int sy) const;
		glm::vec3 getFarPosFromScreen(int sx, int sy) const;
		glm::vec3 getPosFromScreen(const glm::vec3& spos) const;
		glm::vec3 getScreenPosFromWorld(const glm::vec3& pos) const;
	};
}

#endif // !CAMERA_H

