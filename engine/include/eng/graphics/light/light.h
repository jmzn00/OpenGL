#ifndef LIGHT_H
#define LIGHT_H
#include "vec3.hpp"
namespace eng
{	
	enum class LightType : int
	{
		Point = 0,
		Direction = 1,
		Spot = 2,
		Count
	};
	namespace Light
	{
		constexpr const char* ToString(LightType type)
		{
			switch (type)
			{
			case LightType::Spot: return "Spot";
			case LightType::Point: return "Point";
			case LightType::Direction: return "Direction";
			default:	return "Unknown";
			}
		}
	}
	struct RenderLight
	{
		LightType type{ LightType::Spot };

		glm::vec3 position{ 0.0f };
		glm::vec3 direction{ 0.0f, -1.0f, 0.0f };


		glm::vec3 ambient{ 0.2f };
		glm::vec3 diffuse{ 0.5f	};
		glm::vec3 specular{ 1.0f };

		float constant{ 1.0f };
		float linear{ 0.09f };
		float quadratic{ 0.032f };

		float innerCutoff{ 0.0f };
		float outerCutoff{ 0.0f };
	};

	struct PointLight
	{	
		glm::vec3 position{ 0.0f };

		float constant{ 1.0f };
		float linear{ 0.09f };
		float quadratic{ 0.032f };

		glm::vec3 ambient{ 0.2f };
		glm::vec3 diffuse{ 0.5f };
		glm::vec3 specular{ 1.0f };
	};
	struct DirectionalLight
	{
		glm::vec3 direction{ 0.0f, -1.0f, 0.0f };

		glm::vec3 ambient{ 0.2f };
		glm::vec3 diffuse{ 0.5f };
		glm::vec3 specular{ 1.0f };
	};
}
#endif // !LIGHT_H
