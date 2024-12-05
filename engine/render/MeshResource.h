#pragma once
#include <GL/glew.h>
#include <render/MeshResource.h>
#include "core/vec3.h"
#include "core/vec2.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>





using namespace std;




class MeshResource
{
public:


	// sructure for vertices to create cube. 
	struct Vertex
	{
		vec3 position;   // position x,y,z, 
		vec3 color;      // color r,g,b,and a, 
		vec2 texCoord;   // texture coordinates u and v, 
		vec3 normal;

	};
	struct Face
	{
		unsigned int vertexIndex;
		unsigned int textureIndex;
		unsigned int normalIndex;
	};


	GLuint vao; 
	// for vertex data like position and col0rs.  
	GLuint vertexBuffer;
	// show the order of vertices to form primitives like triangles. 
	GLuint indexBuffer;
	GLuint IndexSize; 

	unsigned int indexSize;




	// show the order of vertices's to form primitives like triangles. 
	MeshResource();
	~MeshResource();

	

	// create the vertices with pos and texture cooordinate for each face of the cube.
	static MeshResource* CreateCube(float width, float height, float depth);
	std::shared_ptr<MeshResource> CreateCube_SharedPtr(float width, float height, float depth);



	void BindVBO();
	void BindIBO();

	// Stores vetex and index data for position, normal , texcoord and EBO
	// Can be in private also


	// data storage for vertices, normal texture coordinates and indices. 
	std::vector<Vertex> verticies;
	std::vector<Face> faces;
	std::vector<vec3>position; 
	std::vector<vec3>normals;
	std::vector<vec2> uvs;
	std::vector<vec2> texCoords;
	std::vector<unsigned int> indices;

	

	void setVertices(const std::vector<vec3>& position); 
	void setUVs(const std::vector<vec2>& uvs);
	void setIndices(const std::vector<unsigned int>& Indices);

	

	// obj file loader 
	bool LoadOBJFiles(const std::string& filePath);
	//void loadFromOBJ(const std::string& filename, float scale); 
	// creat a cube. 
	void CreateVBO(float width, float height, float depth);
	void CreateIBO();
	void Draw();
	

	// help function for obj parsing. 
	void ParseVertexData(const std::string& line); 
	void ParseTextureData(const std::string& line);
	void ParseNormalData(const std::string& line);
	void ParseFaceData(const std::string& line);
	



	// method to rerurn the index count 
	GLsizei GetIndexCount() const; 
	GLsizei GetVertexCount()const;
	//void setupMesh(); 
	
	// clean up resource
	void Cleanup(); 

	
};

