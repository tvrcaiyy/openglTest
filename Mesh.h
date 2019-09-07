#ifndef _MESH_H_
#define _MESH_H_
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderManager.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture
{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<Texture> textures;
	vector<unsigned int> indices;
	unsigned int VAO;

	Mesh(vector<Vertex> vertices,vector<unsigned int> indices,vector<Texture> textures)
	{
		this->vertices = vertices;
		this->textures = textures;
		this->indices = indices;

		setupMesh();
	}

	void Draw(ShaderManager pShader)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;

		for (int i = 0;i < textures.size();i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D,textures[i].id);

			string number;
			string name = textures[i].type;
			if (name == "texture_diffuse")
				number = to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = to_string(specularNr++);
			else if (name == "texture_normal")
				number = to_string(normalNr++);
			else if (name == "texture_height")
				number = to_string(heightNr++);
			pShader.setInt((name + number).c_str(),i);
		}
		//draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
		glBindVertexArray(0);
		//alway good practise to set everything back to default once configured.
		glActiveTexture(GL_TEXTURE0);
	}
protected:

private:
	unsigned int VBO,EBO;

	void setupMesh()
	{
		glGenVertexArrays(1,&VAO);
		glGenBuffers(1,&VBO);
		glGenBuffers(1,&EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex) * vertices.size(),&vertices[0],GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int) * indices.size(),&indices[0],GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,TexCoords));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Tangent));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Bitangent));

		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindVertexArray(0);
	}
};
#endif // !_MESH_H_
