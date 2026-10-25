#ifndef MODEL_H
#define MODEL_H

#include <eng/renderer/mesh.h>
#include <eng/graphics/material/material.h>
#include <eng/graphics/texture/texture.h>
#include <eng/graphics/shader_library.h>
#include <eng/graphics/material/material_library.h>

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace eng
{
	struct ModelPart
	{
		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<Material> material;
		glm::mat4 transform{ 1.0f };
	};
	class Model
	{
	public:
		explicit Model(const std::string& path)		
		{			
			LoadModel(path);
		}
		const std::vector<ModelPart>& GetParts() const
		{
			return m_parts;
		}
	private:
		void LoadModel(const std::string& path)
		{
			Assimp::Importer import;
			const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate |
				aiProcess_FlipUVs);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
				!scene->mRootNode)
			{
				throw std::runtime_error(import.GetErrorString());
				return;
			}
			m_directory = path.substr(0, path.find_last_of('/'));
			ProcessNode(scene->mRootNode, scene);
		}
		void ProcessNode(aiNode* node, const aiScene* scene)
		{
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				m_parts.push_back(ProcessMesh(mesh, scene));
			}
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				ProcessNode(node->mChildren[i], scene);
			}
		}
		ModelPart ProcessMesh(aiMesh *mesh, const aiScene * scene)
		{
			std::vector<float> vertices;
			std::vector<uint32_t> indices;
			VertexLayout layout;

			layout.elements.push_back({
				0,
				3,
				GL_FLOAT,
				0
				});
			layout.elements.push_back({
				1,
				3,
				GL_FLOAT,
				3 * sizeof(float)
				});
			layout.elements.push_back({
				2,
				2,
				GL_FLOAT,
				6 * sizeof(float)
				});

			layout.stride = 8 * sizeof(float);

			ModelPart part;

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				auto& vertex = mesh->mVertices[i];
				auto& normal = mesh->mNormals[i];				

				vertices.push_back(vertex.x);
				vertices.push_back(vertex.y);
				vertices.push_back(vertex.z);

				vertices.push_back(normal.x);
				vertices.push_back(normal.y);
				vertices.push_back(normal.z);	

				if (mesh->mTextureCoords[0])
				{
					auto& texCoords = mesh->mTextureCoords[0];
					vertices.push_back(texCoords[i].x);
					vertices.push_back(texCoords[i].y);
				}
				else
				{
					vertices.push_back(0);
					vertices.push_back(0);
				}
			}
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				auto& face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
				{
					indices.push_back(face.mIndices[j]);
				}
			}		
			part.mesh = std::make_shared<Mesh>(layout, vertices, indices);
			part.material = MaterialLibrary::Get("Silver");
			part.material.get()->SetShaderProgram(ShaderLibrary::Get("Default"));

			return part;
		}
		std::vector<Mesh> m_meshes;
		std::vector<ModelPart> m_parts;
		std::string m_directory;
	};
}
#endif // !MODEL_HH
