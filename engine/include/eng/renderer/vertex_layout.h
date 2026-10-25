#ifndef VERTEX_LAYOUT_H
#define VERTEX_LAYOUT_H

#include <glad/glad.h>
#include <vector>
#include <stdint.h>
#include <vec3.hpp>

namespace eng
{
	struct VertexElement
	{
		GLuint index;
		GLuint size;
		GLenum type;
		
		uint32_t offset;
	};
	struct VertexLayout
	{
		std::vector<VertexElement> elements;
		uint32_t stride = 0;
	};
	//struct Vertex
	//{
	//	glm::vec3 Position;
	//	glm::vec3 Normal;
	//	glm::vec3 TexCoords;
	//};
}
#endif // !VERTEX_LAYOUT_H
