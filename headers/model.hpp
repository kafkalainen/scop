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
			Model(void);
			void	loadModel(string path);
			void	Draw(kaf_shader::Shader &shader);
		private:
			bool	initialized;
			string	directory;
			vector <kaf_mesh::Mesh>	meshes;

			void processNode(aiNode *node, const aiScene *scene);
			kaf_mesh::Mesh processMesh(aiMesh *mesh, const aiScene *scene);
			vector<t_texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
												string typeName);
	};
}
#endif
