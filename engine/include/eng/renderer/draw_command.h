#ifndef DRAW_COMMAND_H
#define DRAW_COMMAND_H
namespace eng
{
	class Entity;
	class Mesh;
	class Material;	

	struct DrawCommand
	{
		Mesh* mesh;
		Material* material;
		glm::mat4 worldTransform{ 1.0f };
		Entity* entity;
	};
}
#endif // !DRAW_COMMAND_H
