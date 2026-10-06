#ifndef MESH_H
#define MESH_H
#include <glad/glad.h>
#include <eng/renderer/vertex_layout.h>
#include <iostream>
namespace eng
{
	class Mesh
	{
	public:
		Mesh(const VertexLayout& layout, const std::vector<float>& vertices, const std::vector<uint32_t>& indices)
			: m_vertexLayout(layout), m_vertexCount(vertices.size()), m_indexCount(indices.size())
		{
			GLint prevVAO = 0;
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &prevVAO);

			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);

			m_VBO = 0;
			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

			for (auto& element : m_vertexLayout.elements)
			{
				glVertexAttribPointer(element.index, element.size, element.type,
					GL_FALSE, m_vertexLayout.stride, (void*)(uintptr_t)element.offset);
				glEnableVertexAttribArray(element.index);
			}

			m_EBO = 0;
			glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

			// restore previously bound VAO
			glBindVertexArray(static_cast<GLuint>(prevVAO));

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			
			m_vertexCount = (vertices.size() * sizeof(float)) / m_vertexLayout.stride;
			m_indexCount = indices.size();
		}
		~Mesh()
		{		
			glDeleteVertexArrays(1, &m_VAO);
			glDeleteBuffers(1, &m_VBO);
			glDeleteBuffers(1, &m_EBO);
		}
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		void Bind() const
		{
			glBindVertexArray(m_VAO);
		}
		void Draw() const
		{
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexCount), GL_UNSIGNED_INT, 0);			
		}
	private:
		VertexLayout m_vertexLayout;
		GLuint m_VBO{ 0 };
		GLuint m_EBO{ 0 };	
		GLuint m_VAO{ 0 };	

		size_t m_vertexCount{ 0 };
		size_t m_indexCount{ 0 };
	};
}
#endif // !MESH_H
