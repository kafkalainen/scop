#include "../headers/nerd.hpp"

namespace kaf_model
{
	Model::Model(void)
	{
		this->initialized = false;
	}

	void Model::Draw(kaf_shader::Shader &shader)
	{
		for(unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);
	}

	void Model::loadModel(string path)
	{
		Assimp::Importer import;
		const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
			return;
		}
		this->directory = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene);
		initialized = true;
	}

	void Model::processNode(aiNode *node, const aiScene *scene)
	{
		for(unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}
		for(unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	kaf_mesh::Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
	{
		vector<t_vertex>		vertices;
		vector<unsigned int>	indices;
		vector<t_texture>		textures;
		for(unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			t_vertex	vertex;
			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.pos = vector;
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
			if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.texel = vec;
			}
			else
				vertex.texel = glm::vec2(0.0f, 0.0f);
			vertices.push_back(vertex);
		}
		for(unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for(unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		vector<t_texture> diffuseMaps = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<t_texture> specularMaps = loadMaterialTextures(material,
			aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		return kaf_mesh::Mesh(vertices, indices, textures);
	}

	vector<t_texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
	{
		vector<t_texture> textures;
		for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			t_texture texture;
			texture.id = load_image(str.C_Str(), directory, true);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
		}
		return textures;
	}
}
