#ifndef _MODEL_H_
#define _MODEL_H_
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "stb_image.h"
#include "ShaderManager.h"
#include "Mesh.h"

#include <string>
#include <vector>
#include <iostream>


using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model
{
public:
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;

	Model(string const &path,bool gamma = false) : gammaCorrection(gamma)
	{
		loadModel(path);
	}

	void Draw(ShaderManager pShader)
	{
		for (int i = 0;i < meshes.size();i++)
		{
			meshes[i].Draw(pShader);
		}
	}

protected:

private:

	void loadModel(string const &path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "load model failed ! error msg:" << importer.GetErrorString() << endl;
			return;
		}
		directory = path.substr(0,path.find_last_of("/"));

		processNode(scene->mRootNode,scene);
	}

	void processNode(aiNode* node,const aiScene* scene)
	{
		for (int i = 0; i < node->mNumMeshes;i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh,scene));
		}

		for (int i = 0;i < node->mNumChildren;i++)
		{
			processNode(node->mChildren[i],scene);
		}
	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;
		//vertices
		for (int i = 0; i < mesh->mNumVertices;i++)
		{
			Vertex vertex;
			glm::vec3 vector;
			//Position
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			//Normal
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
			//TexCoords
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f,0.0f);
			// tangent
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.Tangent = vector;
			// bitangent
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vector;
			vertices.push_back(vertex);
		}
		//indices
		for (int i = 0;i < mesh->mNumFaces;i++)
		{
			aiFace face = mesh->mFaces[i];
			for (int j = 0;j < face.mNumIndices;j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
		//textures
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = loadMaterialTextures(mat,aiTextureType_DIFFUSE,"texture_diffse");
		textures.insert(textures.end(),diffuseMaps.begin(),diffuseMaps.end());
		vector<Texture> specularMaps = loadMaterialTextures(mat,aiTextureType_SPECULAR,"texture_specular");
		textures.insert(textures.end(),specularMaps.begin(),specularMaps.end());
		vector<Texture> normalMaps = loadMaterialTextures(mat,aiTextureType_HEIGHT,"texture_normal");
		textures.insert(textures.end(),normalMaps.begin(),normalMaps.end());
		vector<Texture> heightMaps = loadMaterialTextures(mat,aiTextureType_AMBIENT,"texture_height");
		textures.insert(textures.end(),heightMaps.begin(),heightMaps.end());
		return Mesh(vertices,indices,textures);
	}

	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		for (int i = 0;i < mat->GetTextureCount(type);i++)
		{
			aiString str;
			mat->GetTexture(type,i,&str);
			bool skip = false;
			for (int j = 0; j < textures_loaded.size();j++)
			{
				if (strcmp(textures_loaded[j].path.data(),str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if(!skip)
			{
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(),this->directory);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
			}
		}
		return textures;
	}
};

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
#endif // !_MODEL_H_
