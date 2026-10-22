#ifndef MODEL_H
#define MODEL_H

#include <eng/renderer/mesh.h>
#include <eng/graphics/material/material.h>

#include <glm/mat4x4.hpp>;
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
				m_meshes.push_back(ProcessMesh(mesh, scene));
			}
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				ProcessNode(node->mChildren[i], scene);
			}
		}
		Mesh ProcessMesh(aiMesh *mesh, const aiScene * scene)
		{
		
		}
		std::vector<Mesh> m_meshes;
		std::vector<ModelPart> m_parts;
		std::string m_directory;
	};
}
#endif // !MODEL_HH
