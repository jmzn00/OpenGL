#ifndef VERTEX_LAYOUT_H
#define VERTEX_LAYOUT_H
#include <glad/glad.h>
#include <vector>
#include <stdint.h>
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
}
#endif // !VERTEX_LAYOUT_H
