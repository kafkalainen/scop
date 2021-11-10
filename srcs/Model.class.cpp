#include "../headers/nerd.hpp"

namespace kaf_model
{
	Model::Model(void)
	{
		this->initialized = false;
		this->gamma_correction = false;
	}

	void	Model::vec2_cpy(glm::vec2 &dest, aiVector3D &src)
	{
		dest.x = src.x;
		dest.y = src.y;
	}


	void	Model::vec3_cpy(glm::vec3 &dest, aiVector3D &src)
	{
		dest.x = src.x;
		dest.y = src.y;
		dest.z = src.z;
	}

	bool	Model::check_if_texture_loaded(vector<t_texture> &textures,
			const aiString &str)
	{
		for(unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if(kaf_strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				return (true);
			}
		}
		return (false);
	}

	void Model::Draw(kaf_shader::Shader &shader)
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);
	}

	void Model::loadModel(const string &path)
	{
		Assimp::Importer import;
		const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals
			| aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
			return ;
		}
		this->directory = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene);
		initialized = true;
	}

	void Model::processNode(aiNode *node, const aiScene *scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	kaf_mesh::Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
	{
		vector<t_vertex>		vertices;
		vector<unsigned int>	indices;
		vector<t_texture>		textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			t_vertex	vertex;
			glm::vec3 vector;
			vec3_cpy(vector, mesh->mVertices[i]);
			vertex.pos = vector;
			if (mesh->HasNormals())
			{
				vec3_cpy(vector, mesh->mNormals[i]);
				vertex.normal = vector;
			}
			if(mesh->mTextureCoords[0])
			{
				glm::vec2 texel;
				vec2_cpy(texel, mesh->mTextureCoords[0][i]);
				vertex.texel = texel;
				vec3_cpy(vector, mesh->mTangents[i]);
				vertex.tangent = vector;
				vec3_cpy(vector, mesh->mBitangents[i]);
				vertex.bitangent = vector;
			}
			else
				vertex.texel = glm::vec2(0.0f, 0.0f);
			vertices.push_back(vertex);
		}
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
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
		std::vector<t_texture> normalMaps = loadMaterialTextures(material,
			aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		std::vector<t_texture> heightMaps = loadMaterialTextures(material,
			aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		return kaf_mesh::Mesh(vertices, indices, textures);
	}

	vector<t_texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
	{
		vector<t_texture> textures;

		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = check_if_texture_loaded(textures, str);
			if (!skip)
			{
				t_texture texture;
				texture.id = load_image(str.C_Str(), this->directory, true);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				this->textures_loaded.push_back(texture);
			}
		}
		return (textures);
	}
}
