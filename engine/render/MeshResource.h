#pragma once

#include <config.h>
#include <GL/glew.h>
#include <vector>
#include "core/vec3.h"
#include "core/vec2.h"



using namespace std;



// sructure for vertices to create cube. 
struct Vertex
{
	float position;   // position x,y,z, 
	float color;      // color r,g,b,and a, 
	float texCoord;   // texture coordinates u and v, 

};
class MeshResource
{
public:
	// for vertex data like position and col0rs.  
	GLuint vertexBuffer ;
	// show the order of vertices to form primitives like triangles. 
	GLuint indexBuffer;

	unsigned int indexSize;

	// show the order of vertices's to form primitives like triangles. 
	MeshResource();
	~MeshResource();

	//void createVBO();
	void CreateVBO(float width, float height, float depth);
	void CreateIBO();
	void BindVBO();
	void BindIBO();
	void setupMesh();
	// draw the mesh 
	/*void Draw();*/ 



	// create the vertices with pos and texture cooordinate for each face of the cube.
	static MeshResource* CreateCube(float width, float height, float depth);


	std::vector<vec3> vertices;
	std::vector<vec2> uvs;
	std::vector<unsigned int> indices;

	static MeshResource* CreateSpher(float radius, unsigned int rings, unsigned int sectors);

	void setVertices(const std::vector<vec3>& vertices); 
	void setUVs(const std::vector<vec2>& uvs);
	void setIndices(const std::vector<unsigned int>& Indices);
	//void setupMesh(); 
	
	// clean up resource
	void Cleanup(); 
	
	
};

