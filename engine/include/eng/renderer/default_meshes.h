#ifndef DEFAULT_MESHES_H
#define DEFAULT_MESHES_H
#include <eng/renderer/mesh.h>
#include <memory>
#include <vector>

#include <eng/entity/entity.h>
#include <eng/entity/components.h>

#include <eng/graphics/shader_program.h>

namespace eng
{
	namespace Primitives
	{        
		inline std::shared_ptr<Mesh> CubeMesh()
		{
            std::vector<float> vertices =
            {
                // positions              // normals           // tex coords

                // Front face (+Z)
                -0.5f, -0.5f,  0.5f,      0,0,1,              0,0,
                 0.5f, -0.5f,  0.5f,      0,0,1,              1,0,
                 0.5f,  0.5f,  0.5f,      0,0,1,              1,1,
                -0.5f,  0.5f,  0.5f,      0,0,1,              0,1,

                // Back face (-Z)
                 0.5f, -0.5f, -0.5f,      0,0,-1,             0,0,
                -0.5f, -0.5f, -0.5f,      0,0,-1,             1,0,
                -0.5f,  0.5f, -0.5f,      0,0,-1,             1,1,
                 0.5f,  0.5f, -0.5f,      0,0,-1,             0,1,

                 // Left face (-X)
                 -0.5f, -0.5f, -0.5f,     -1,0,0,              0,0,
                 -0.5f, -0.5f,  0.5f,     -1,0,0,              1,0,
                 -0.5f,  0.5f,  0.5f,     -1,0,0,              1,1,
                 -0.5f,  0.5f, -0.5f,     -1,0,0,              0,1,

                 // Right face (+X)
                  0.5f, -0.5f,  0.5f,      1,0,0,              0,0,
                  0.5f, -0.5f, -0.5f,      1,0,0,              1,0,
                  0.5f,  0.5f, -0.5f,      1,0,0,              1,1,
                  0.5f,  0.5f,  0.5f,      1,0,0,              0,1,

                  // Top face (+Y)
                  -0.5f,  0.5f,  0.5f,      0,1,0,              0,0,
                   0.5f,  0.5f,  0.5f,      0,1,0,              1,0,
                   0.5f,  0.5f, -0.5f,      0,1,0,              1,1,
                  -0.5f,  0.5f, -0.5f,      0,1,0,              0,1,

                  // Bottom face (-Y)
                  -0.5f, -0.5f, -0.5f,      0,-1,0,             0,0,
                   0.5f, -0.5f, -0.5f,      0,-1,0,             1,0,
                   0.5f, -0.5f,  0.5f,      0,-1,0,             1,1,
                  -0.5f, -0.5f,  0.5f,      0,-1,0,             0,1,
            };
            std::vector<unsigned int> indices =
            {
                // Front
                0, 1, 2,
                2, 3, 0,

                // Back
                4, 5, 6,
                6, 7, 4,

                // Left
                8, 9, 10,
                10, 11, 8,

                // Right
                12, 13, 14,
                14, 15, 12,

                // Top
                16, 17, 18,
                18, 19, 16,

                // Bottom
                20, 21, 22,
                22, 23, 20
            };

            VertexLayout cubeVertexLayout{};
            cubeVertexLayout.stride = 8 * sizeof(float);
            
            cubeVertexLayout.elements.push_back({
                0,
                3, 
                GL_FLOAT,
                0});
            cubeVertexLayout.elements.push_back({
                1,
                3,
            	GL_FLOAT,
            	3 * sizeof(float)});
            cubeVertexLayout.elements.push_back({
                2,
            	2,
            	GL_FLOAT,
            	6 * sizeof(float)});
            return std::make_shared<Mesh>(cubeVertexLayout, vertices, indices);
		}
	}
}
#endif // !DEFAULT_MESHES_H
