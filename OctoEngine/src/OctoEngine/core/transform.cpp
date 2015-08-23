#include "transform.h"

using namespace glm;

namespace octo
{
	namespace core {

		Transform::Transform()
			: m_HasChanged(true), m_Parent(nullptr), m_Scale(vec3(1.0, 1.0, 1.0)),
			m_Position(vec3(0.0, 0.0, 0.0))
		{
		}

		Transform::~Transform()
		{
		}

		void Transform::rotate(vec3& axis)
		{
			m_HasChanged = true;
			quat r(axis);
			m_Rotation *= r;
		}

		void Transform::translate(vec3& position)
		{
			m_HasChanged = true;
			m_Position += position;
		}

		void Transform::scale(vec3& scale)
		{
			m_HasChanged = true;
			m_Scale = m_Scale * scale;
		}

		void Transform::setParent(Transform* transform)
		{
			m_HasChanged = true;
			m_Parent = transform;
			m_ParentMatrix = m_Parent->getTransformationMatrix();
		}

		const mat4& Transform::getTransformationMatrix()
		{
			if (m_Parent != nullptr && m_Parent->hasChanged())
				m_ParentMatrix = m_Parent->getTransformationMatrix();

			mat4 transformations; // Identity
			
			// Translation
			transformations = glm::translate(transformations, m_Position);

			// Rotation
			transformations *= mat4_cast(m_Rotation);

			// Scale
			transformations = glm::scale(transformations, m_Scale);

			m_Transformation = m_ParentMatrix * transformations;
			return m_Transformation;
		}

		void Transform::update()
		{
			m_HasChanged = false;
		}
	}
}