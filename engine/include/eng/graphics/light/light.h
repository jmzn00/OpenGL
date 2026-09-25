#ifndef LIGHT_H
#define LIGHT_H
#include "vec3.hpp"
namespace eng
{
	struct Light
	{
		glm::vec3 position;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}
#endif // !LIGHT_H
