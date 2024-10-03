#pragma once
#include <config.h>
#include <GL/glew.h>
#include <vector>



using namespace std;



// sructure for vertices to create cube. 
struct Vertex
{
	float position[3];   // position x,y,z, 
	float color[4];      // color r,g,b,and a, 
	float texCoord[2];   // texture coordinates u and v, 

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


	// create the vertices with pos and texture cooordinate for each face of the cube.
	static MeshResource* CreateCube(float width, float height, float depth);
	
	//void createVBO();
	void CreateVBO(float width, float height, float depth);
	void CreateIBO();
	void BindVBO();
	void BindIBO();
	// draw the mesh 
	
	void Draw(); 
	void Cleanup(); 
	
	
};

