#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <glm.hpp>
#include <eng/renderer/mesh.h>
#include <gtc/matrix_transform.hpp>
#include <gtx/quaternion.hpp>
#include <eng/graphics/shader_program.h>
#include <eng/graphics/material/material.h>
#include <memory>
#include <eng/graphics/light/light.h>
#include <eng/renderer/model.h>


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
		glm::vec3 GetForward() const
		{
			const glm::quat rotation = glm::quat(Rotation);
			return glm::normalize(glm::mat3_cast(rotation) * glm::vec3(0.0f, 0.0f, -1.0f));
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
	struct ModelComponent
	{
		std::shared_ptr<Model> model;
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
		LightType type{ LightType::Spot };

		glm::vec3 position{ 0.0f };
		glm::vec3 direction{ 0.0f, -1.0f, 0.0f };


		glm::vec3 ambient{ 0.2f };
		glm::vec3 diffuse{ 0.5f };
		glm::vec3 specular{ 1.0f };

		float constant{ 1.0f };
		float linear{ 0.09f };
		float quadratic{ 0.032f };


		float innerCutoff{ glm::cos(glm::radians(12.5f)) };
		float outerCutoff{ glm::cos(glm::radians(17.5f)) };
	};
}
#endif // !COMPONENTS_H
