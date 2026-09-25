#ifndef MATERIAL_H
#define MATERIAL_H
#include "vec3.hpp"
namespace eng
{
	struct Material
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};
}
#endif // !MATERIAL_H
