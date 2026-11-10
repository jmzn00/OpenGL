#ifndef DRAW_COMMAND_H
#define DRAW_COMMAND_H
namespace eng
{
	class Entity;
	class Mesh;
	class Material;
	struct TransformComponent;

	struct DrawCommand
	{
		Mesh* mesh;
		Material* material;
		TransformComponent* transform;
		Entity* entity;
	};
}
#endif // !DRAW_COMMAND_H
