#ifndef MESH_LIBRARY
#define MESH_LIBRARY
#include <eng/renderer/mesh.h>
#include <memory>
#include <vector>
#include <eng/debug/assert.h>
#include <string>
#include <unordered_map>
namespace eng
{
    inline std::shared_ptr<Mesh> CubeMesh();
    inline std::shared_ptr<Mesh> PyramidMesh();
    inline std::shared_ptr<Mesh> QuadMesh();
    inline std::shared_ptr<Mesh> LineMesh();


    class MeshLibrary
    {
    public:
        MeshLibrary()
        {            
        }
        ~MeshLibrary()
        {
            m_meshes.clear();
        }
        std::shared_ptr<Mesh> Create(const std::string& key)
        {
            if (const auto it = m_meshes.find(key); it != m_meshes.end())
                return it->second;

            std::shared_ptr<Mesh> mesh;
            if (key == "primitives::cube")
                mesh = CubeMesh();
            else if (key == "primitives::pyramid")
                mesh = PyramidMesh();
            else if (key == "primitives::quad")
                mesh = QuadMesh();
            else if (key == "primitives::line")
                mesh = LineMesh();
            else
                return nullptr;

            mesh->SetKey(key);
            m_meshes.emplace(key, mesh);
            return mesh;
        }
        void Clear()
        {
            m_meshes.clear();
        }
    private:        
        std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;        
    };
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
            0 });
        cubeVertexLayout.elements.push_back({
            1,
            3,
            GL_FLOAT,
            3 * sizeof(float) });
        cubeVertexLayout.elements.push_back({
            2,
            2,
            GL_FLOAT,
            6 * sizeof(float) });
        return std::make_shared<Mesh>(cubeVertexLayout, vertices, indices);
    }
    inline std::shared_ptr<Mesh> PyramidMesh()
    {
        std::vector<float> vertices =
        {
            -0.5f, -0.5f, -0.5f,   0.f,-1.f, 0.f,   0.f,0.f,
             0.5f, -0.5f, -0.5f,   0.f,-1.f, 0.f,   1.f,0.f,
             0.5f, -0.5f,  0.5f,   0.f,-1.f, 0.f,   1.f,1.f,
            -0.5f, -0.5f,  0.5f,   0.f,-1.f, 0.f,   0.f,1.f,

             0.0f,  0.5f,  0.0f,  -0.707f, 0.707f, 0.f,   0.5f,1.f,
            -0.5f, -0.5f,  0.5f,  -0.707f, 0.707f, 0.f,   0.f,0.f,
            -0.5f, -0.5f, -0.5f,  -0.707f, 0.707f, 0.f,   1.f,0.f,

             0.0f,  0.5f,  0.0f,   0.f, 0.707f,-0.707f,   0.5f,1.f,
            -0.5f, -0.5f, -0.5f,   0.f, 0.707f,-0.707f,   0.f,0.f,
             0.5f, -0.5f, -0.5f,   0.f, 0.707f,-0.707f,   1.f,0.f,

              0.0f,  0.5f,  0.0f,   0.707f, 0.707f, 0.f,   0.5f,1.f,
              0.5f, -0.5f, -0.5f,   0.707f, 0.707f, 0.f,   0.f,0.f,
              0.5f, -0.5f,  0.5f,   0.707f, 0.707f, 0.f,   1.f,0.f,

               0.0f,  0.5f,  0.0f,   0.f, 0.707f, 0.707f,   0.5f,1.f,
               0.5f, -0.5f,  0.5f,   0.f, 0.707f, 0.707f,   0.f,0.f,
              -0.5f, -0.5f,  0.5f,   0.f, 0.707f, 0.707f,   1.f,0.f,
        };
        std::vector<unsigned int> indices =
        {
            // bottom face
            0, 1, 2,
            0, 2, 3,

            // left triangle
            4, 5, 6,

            // back triangle
            7, 8, 9,

            // right triangle
            10, 11, 12,

            // front triangle
            13, 14, 15
        };    
        VertexLayout vertexLayout{};

        vertexLayout.stride = 8 * sizeof(float);
        vertexLayout.elements.push_back({
            0,
            3,
            GL_FLOAT,
            0});
        vertexLayout.elements.push_back({
            1,
            3,
            GL_FLOAT,
            3 * sizeof(float) });
        vertexLayout.elements.push_back({
            2,
            2,
            GL_FLOAT,
            6 * sizeof(float) });

        return std::make_shared<Mesh>(vertexLayout, vertices, indices);
    }
    inline std::shared_ptr<Mesh> QuadMesh()
    {
        std::vector<float> vertices =
        {
            // positions          // normals         // tex coords
            -0.5f,  0.5f, 0.0f,   0.f, 0.f, 1.f,    0.f, 1.f,
             0.5f,  0.5f, 0.0f,   0.f, 0.f, 1.f,    1.f, 1.f,
             0.5f, -0.5f, 0.0f,   0.f, 0.f, 1.f,    1.f, 0.f,
            -0.5f, -0.5f, 0.0f,   0.f, 0.f, 1.f,    0.f, 0.f
		};
        std::vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 3, 0
		};
        VertexLayout layout{};

		layout.stride = 8 * sizeof(float);
        layout.elements.push_back({
            0,
            3,
            GL_FLOAT,
            0 });
        layout.elements.push_back({
            1,
            3,
            GL_FLOAT,
            3 * sizeof(float) });
        layout.elements.push_back({
            2,
            2,
            GL_FLOAT,
            6 * sizeof(float) });

        return std::make_shared<Mesh>(layout, vertices, indices);
    }
    inline std::shared_ptr<Mesh> LineMesh()
    {
        std::vector<float> vertices =
        {
            -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
             0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
             0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        };

        std::vector<uint32_t> indices = { 0, 1, 2, 3};

        VertexLayout layout{};
        layout.stride = 5 * sizeof(float);
        layout.elements.push_back({ 0, 2, GL_FLOAT, 0});
        layout.elements.push_back({ 1, 3, GL_FLOAT, 2 * sizeof(float)});

        return std::make_shared<Mesh>(layout, vertices, indices, GL_POINTS);
    }   
}
#endif // !MESH_LIBRARY
