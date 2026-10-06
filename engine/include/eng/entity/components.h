#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <glm.hpp>
#include <eng/renderer/mesh.h>
#include <gtc/matrix_transform.hpp>
#include <gtx/quaternion.hpp>
#include <eng/graphics/shader_program.h>
#include <eng/graphics/material/material.h>
#include <memory>

namespace eng
{
	struct TransformComponent
	{
		glm::vec3 Translation{0.0f};
		glm::vec3 Rotation{0.0f};
		glm::vec3 Scale{1.0f};		

		TransformComponent() = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::vec3 GetPosition() const
		{
			return Translation;
		}
		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
		void Translate(const glm::vec3& delta)
		{
			Translation += delta;
		}
		void MoveTo(const glm::vec3& pos)
		{
			Translation = pos;
		}
		void SetScale(const glm::vec3& scale)
		{
			Scale = scale;
		}
	};
	struct MeshComponent
	{
		MeshComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
			: mesh(mesh), material {material}
		{
			
		}
		void Draw() const
		{
			if (mesh)
			{
				mesh->Bind();
				mesh->Draw();
			}
		}
		std::shared_ptr<Material> material;
		std::shared_ptr<Mesh> mesh;
	};
	struct LightComponent
	{
		glm::vec3 ambient{0.2f};
		glm::vec3 diffuse{0.5f};
		glm::vec3 specular{1.0f};
	};
}
#endif // !COMPONENTS_H
