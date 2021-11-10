#ifndef MODEL_HPP
# define MODEL_HPP
# include "shader.hpp"
# include "mesh.hpp"
# include "../assimp/include/assimp/Importer.hpp"
# include "../assimp/include/assimp/scene.h"
# include "../assimp/include/assimp/postprocess.h"

namespace kaf_model
{
	class Model
	{
		public:
			string					directory;
			vector <t_texture>		textures_loaded;
			vector <kaf_mesh::Mesh>	meshes;

			Model(void);
			void	loadModel(const string &path);
			void	Draw(kaf_shader::Shader &shader);
		private:
			bool	gamma_correction;
			bool	initialized;

			void	vec3_cpy(glm::vec3 &dest, aiVector3D &src);
			void	vec2_cpy(glm::vec2 &dest, aiVector3D &src);
			bool	check_if_texture_loaded(vector<t_texture> &textures,
						const aiString &str);
			void	processNode(aiNode *node, const aiScene *scene);
			kaf_mesh::Mesh processMesh(aiMesh *mesh, const aiScene *scene);
			vector<t_texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
												string typeName);
	};
}
#endif
