#include "Camera.h"

namespace glwrapper
{
	Camera::Camera()
	{
		setToPosIdentity();
		setToRotIdentity();
	}

	Camera::~Camera()
	{
	}

	void Camera::setViewport(int x, int y, int w, int h)
	{
		m_vp = glm::ivec4(x, y, w, h);
	}

	void Camera::setPerspMode()
	{
		m_pmode = persp;
	}

	void Camera::setOrthoMode()
	{
		m_pmode = ortho;
	}

	void Camera::setNearAndFar(float near, float far)
	{
		if (near >= far)
			return;

		m_near = near;
		m_far = far;
	}

	void Camera::setFov(float fov)
	{
		m_fov = fov;
	}

	void Camera::setToPosIdentity()
	{
		m_pos = glm::vec3();
	}

	void Camera::setToRotIdentity()
	{
		m_rot = glm::quat();
	}

	void Camera::setPos(float x, float y, float z)
	{
		m_pos = glm::vec3(x, y, z);
	}

	void Camera::setPos(const glm::vec3& pos)
	{
		m_pos = pos;
	}

	void Camera::setRot(float deg, const glm::vec3& axis)
	{
		m_rot = glm::angleAxis(glm::radians(deg), glm::normalize(axis));
	}

	void Camera::setRot(const glm::quat& rot)
	{
		m_rot = rot;
	}

	void Camera::translate(float x, float y, float z)
	{
		m_pos += glm::vec3(x, y, z);
	}

	void Camera::translate(const glm::vec3& delta)
	{
		m_pos += delta;
	}

	void Camera::rotate(float deg, const glm::vec3& axis)
	{
		if (glm::isnan<float>(glm::length(axis)) || glm::length(axis) == 0.f || deg == 0.f || glm::isnan(deg))
			return;

		m_rot = glm::angleAxis(glm::radians(deg), glm::normalize(axis)) * m_rot;
	}

	void Camera::rotate(const glm::quat& rot)
	{
		m_rot = rot * m_rot;
	}

	void Camera::lookAt(const glm::vec3& target, const glm::vec3& up)
	{
		glm::vec3 z = glm::normalize(m_pos - target); //+z is back(0, 0, 1) for me.
		glm::vec3 x = glm::normalize(glm::cross(up, z)); //+x
		glm::vec3 y = glm::normalize(glm::cross(z, x)); //+y
		glm::mat3 mat(x, y, z);

		m_rot = glm::normalize(glm::quat_cast(mat));
	}

	void Camera::lookAt(float x, float y, float z, const glm::vec3& up)
	{
		lookAt(glm::vec3(x, y, z), up);
	}

	void Camera::rotateAround(float deg, const glm::vec3& axis, const glm::vec3& target)
	{
		glm::quat rot = glm::angleAxis(glm::radians(deg), axis);
		rotateAround(rot, target);
	}

	void Camera::rotateAround(const glm::quat& rot, const glm::vec3& target)
	{
		//돌리고
		rotate(rot);

		//위치 돌리고
		translate(-target);
		m_pos = rot * m_pos;
		translate(target);
	}

	void Camera::adjustFov(float deg)
	{
		m_fov += deg;

		if (m_fov <= 0)
			m_fov = 1;
		else if (m_fov >= 180)
			m_fov = 179;
	}

	void Camera::adjustNear(float delta)
	{
		if (m_near + delta >= m_far)
			return;

		m_near += delta;
	}

	void Camera::adjustFar(float delta)
	{
		if (m_far + delta <= m_near)
			return;

		m_far += delta;
	}

	const glm::ivec4& Camera::getViewport() const
	{
		return m_vp;
	}

	const int Camera::getWidth() const
	{
		return m_vp.z; // width
	}

	const int Camera::getHeight() const
	{
		return m_vp.w; // height
	}

	const glm::vec3& Camera::getPos() const
	{
		return m_pos;
	}

	const glm::quat& Camera::getRot() const
	{
		return m_rot;
	}

	float Camera::getNear() const
	{
		return m_near;
	}

	float Camera::getFar() const
	{
		return m_far;
	}

	float Camera::getFov() const
	{
		return m_fov;
	}

	float Camera::getAspect() const
	{
		if (m_vp[3] != 0)
			return (float)m_vp[2] / (float)m_vp[3];
		else
			return (float)m_vp[2];
	}

	glm::vec3 Camera::getFront() const
	{
		return m_rot * glm::vec3(0, 0, -1);
	}

	glm::vec3 Camera::getBack() const
	{
		return m_rot * glm::vec3(0, 0, 1);
	}

	glm::vec3 Camera::getUp() const
	{
		return m_rot * glm::vec3(0, 1, 0);
	}

	glm::vec3 Camera::getDown() const
	{
		return m_rot * glm::vec3(0, -1, 0);
	}

	glm::vec3 Camera::getLeft() const
	{
		return m_rot * glm::vec3(-1, 0, 0);
	}

	glm::vec3 Camera::getRight() const
	{
		return m_rot * glm::vec3(1, 0, 0);
	}

	const glm::mat4& Camera::getViewMatrix() const
	{
		static glm::mat4 vmat;

		vmat = glm::lookAt(m_pos, m_pos + getFront(), getUp());

		return vmat;
	}

	const glm::mat4& Camera::getProjectionMatrix() const
	{
		static glm::mat4 pmat;

		if (m_pmode == ortho) {
			//float h_2 = 4.f * tan(glm::radians(m_fov*0.5f));
			//float w_2 = getAspect() * h_2;
			float h_2 = (float)m_vp[3] * 0.5f;
			float w_2 = (float)m_vp[2] * 0.5f;
			pmat = glm::ortho(-w_2, w_2, -h_2, h_2, -m_far, m_far);
		}
		else {
			float aspect = getAspect();
			pmat = glm::perspective(m_fov, aspect, m_near, m_far);
		}

		return pmat;
	}

	const float* Camera::getPosPtr() const
	{
		return glm::value_ptr(m_pos);
	}

	const float* Camera::getViewMatrixPtr() const
	{
		return glm::value_ptr(getViewMatrix());
	}

	const float* Camera::getProjectionMatrixPtr() const
	{
		return glm::value_ptr(getProjectionMatrix());
	}

	glm::vec3 Camera::getRayFromScreen(int sx, int sy) const
	{
		glm::vec3 sp(sx, m_vp[3] - sy, 0); //screen pos
		glm::vec3 near_pos = glm::unProject(sp, getViewMatrix(), getProjectionMatrix(), m_vp);
		return glm::normalize(near_pos - m_pos);
	}

	glm::vec3 Camera::getNearPosFromScreen(int sx, int sy) const
	{
		glm::vec3 sp(sx, m_vp[3] - sy, 0); //screen pos
		return glm::unProject(sp, getViewMatrix(), getProjectionMatrix(), m_vp);
	}

	glm::vec3 Camera::getFarPosFromScreen(int sx, int sy) const
	{
		glm::vec3 sp(sx, m_vp[3] - sy, 1); //screen pos
		return glm::unProject(sp, getViewMatrix(), getProjectionMatrix(), m_vp);
	}

	glm::vec3 Camera::getPosFromScreen(const glm::vec3& spos) const
	{
		glm::vec3 sp(spos.x, m_vp[3] - spos.y, spos.z);
		return glm::unProject(sp, getViewMatrix(), getProjectionMatrix(), m_vp);
	}

	glm::vec3 Camera::getScreenPosFromWorld(const glm::vec3& pos) const
	{
		return glm::project(pos, getViewMatrix(), getProjectionMatrix(), m_vp);
	}
}
