#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "glm\gtc\matrix_transform.hpp"

enum E_CameraMoveType
{
	CameraMoveForward,
	CameraMoveBackward,
	CameraMoveLeft,
	CameraMoveRight,
};
enum E_CameraType
{
	FPS,
	SLG,
};

float cameraMoveSpeed = 2.0f;
const float SENSITIVITY =  0.2f;

class CameraManager
{
public:
	float Zoom;
	glm::vec3 Position;
	bool bMove;
	CameraManager(glm::vec3 cameraPos,glm::vec3 lookPos,glm::vec3 worldUp,E_CameraType cameraType = SLG):Zoom(45.0f)
	{
		Position = cameraPos;
		m_lookPos = lookPos;
		m_worldUp = worldUp;

		m_front = glm::normalize(lookPos - cameraPos);
		m_right = glm::normalize(glm::cross(m_front,worldUp));
		m_up = glm::normalize(glm::cross(m_right,m_front));
		m_pitch = 0.0f;
		m_yaw = -90.0f;
		m_cameraType = cameraType;
		m_distance = glm::distance(Position,m_lookPos);
	}

	glm::mat4 GetLookAt()
	{
		if (m_cameraType == FPS)
		{
			//return getLookAtMatrix(Position,Position + m_front,m_worldUp);
			return glm::lookAt(Position,Position + m_front,m_worldUp);
		}
		else
			return getLookAtMatrix(Position,m_lookPos,m_worldUp);
	}

	void ProcessKeyboardInput(E_CameraMoveType moveType,float deltaTime)
	{
		if (m_cameraType == FPS)
		{
			switch (moveType)
			{
			case CameraMoveForward:
				Position += m_front * cameraMoveSpeed * deltaTime;
				break;
			case CameraMoveBackward:
				Position -= m_front * cameraMoveSpeed * deltaTime;
				break;
			case CameraMoveLeft:
				Position -= m_right * cameraMoveSpeed * deltaTime;
				break;
			case CameraMoveRight:
				Position += m_right * cameraMoveSpeed * deltaTime;
				break;
			default:
				break;
			}
		}
		else
		{

		}
		
		m_distance = glm::distance(Position,m_lookPos);
	}

	void ProcessMouseMovement(float offsetx,float offsety,bool constrainPitch = true)
	{
		offsetx *= SENSITIVITY;
		offsety *= SENSITIVITY;
		if (m_cameraType == FPS)
		{
			m_pitch += offsety;
			m_yaw += offsetx;
			if (constrainPitch)
			{
				if (m_pitch > 89.0f)
					m_pitch = 89.0f;
				else if (m_pitch < -89.0f)
					m_pitch = -89.0f;
			}
			updateCameraVectors();
		}
		else
		{
			if(bMove)
			{
				m_pitch += offsety;
				m_yaw += offsetx;
				if (constrainPitch)
				{
					if (m_pitch > 0.0f)
						m_pitch = 0.0f;
					else if (m_pitch < -89.0f)
						m_pitch = -89.0f;
				}
				updateCameraVectors();
			}
		}
	}

	void ProcessMouseScroll(float offset)
	{
		Zoom -= offset;
		if (Zoom >= 90.0f)
			Zoom = 90.0f;
		else if (Zoom < 1.0f)
			Zoom = 1.0f;
	}

	~CameraManager(){};

private:
	glm::vec3 m_lookPos;
	glm::vec3 m_worldUp;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	float m_pitch;
	float m_yaw;
	E_CameraType m_cameraType;
	float m_distance;

	void updateCameraVectors()
	{
		if (m_cameraType == FPS)
		{
			glm::vec3 front;
			front.y = sin(glm::radians(m_pitch));
			front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
			front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
			m_front = glm::normalize(front);
			m_right = glm::normalize(glm::cross(m_front,m_worldUp));
			m_up = glm::normalize(glm::cross(m_right,m_front));
		}
		else if (m_cameraType == SLG)
		{
			glm::vec3 front;
			front.y = sin(glm::radians(m_pitch));
			front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
			front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
			m_front = glm::normalize(front);

			Position = m_lookPos - (front * m_distance);
			m_right = glm::normalize(glm::cross(m_front,m_worldUp));
			m_up = glm::normalize(glm::cross(m_right,m_front));
		}
	}

	glm::mat4 getLookAtMatrix(glm::vec3 cameraPos,glm::vec3 lookPos,glm::vec3 worldUp)
	{
		glm::vec3 front = glm::normalize(cameraPos - lookPos);
		glm::vec3 right = glm::normalize(glm::cross(worldUp,front));
		glm::vec3 up = glm::normalize(glm::cross(front,right));

		glm::mat4 Result(1);
		Result[0][0] = right.x;
		Result[1][0] = right.y;
		Result[2][0] = right.z;
		Result[0][1] = up.x;
		Result[1][1] = up.y;
		Result[2][1] = up.z;
		Result[0][2] = front.x;
		Result[1][2] = front.y;
		Result[2][2] = front.z;
		Result[3][0] = -dot(right,cameraPos);
		Result[3][1] = -dot(up,cameraPos);
		Result[3][2] = -dot(front,cameraPos);
		return Result;
	}
};


#endif
