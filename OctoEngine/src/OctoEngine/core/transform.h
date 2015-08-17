#pragma once
#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
#define FORCE_TRANSFORM_MATRIX_RECALCULATION 0

namespace octo
{
	namespace core {



		class Transform
		{
		private:
			vec3 m_Position;
			quat m_Rotation;
			vec3 m_Scale;
			mat4 m_Transformation;

			bool m_HasChanged;
			Transform* m_Parent;
			mat4 m_ParentMatrix;

		public:
			Transform();
			~Transform();

			inline const vec3& getPosition() const { return m_Position; }
			inline const quat& getRotation() const { return m_Rotation; }
			inline const vec3& getScale() const { return m_Scale; }

			inline void setPosition(vec3& position) { m_HasChanged = true; m_Position = position; }
			inline void setRotation(quat& rotation) { m_HasChanged = true; m_Rotation = rotation; }
			inline void setScale(vec3& scale) { m_HasChanged = true; m_Scale = scale; }

			void rotate(vec3& axis);
			void translate(vec3& position);
			void scale(vec3& scale);

			void setParent(Transform* parent);
			inline const Transform* getParent() const { return m_Parent; }

			const mat4& getTransformationMatrix();

			// Returns TRUE if this transform changed since the last time the flag was set to 'false';
			//A change to the transform can be anything that can cause its matrix to be recalculated
			bool hasChanged() {
#ifdef 	FORCE_TRANSFORM_MATRIX_RECALCULATION
				return true;
#else
				return m_HasChanged;
#endif
			}

			// Updates the transform
			// It also sets HasChanged to false
			void update();

		};

	}
}