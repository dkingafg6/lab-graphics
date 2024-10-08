#pragma once
#include <config.h>
#include <GL/glew.h>
#include <render/MeshResource.h>

using namespace std; 

// Constructor
MeshResource::MeshResource()
{
    // initialize vertex, index shader and indexSize to zero. 
    vertexBuffer = 0; 
    indexBuffer = 0; 
    indexSize = 0; 
    
}

// Destructor
MeshResource::~MeshResource()
{
    // meshresource shuold clean when the object is destroyed. 
    printf("Cleanup called \n");
    Cleanup(); 
    
}

// Create the Cube mesh resource with static method
MeshResource* MeshResource::CreateCube(float width, float height, float depth) 
{
    // allocate a new meshResource object. 
    MeshResource* mesh = new MeshResource(); 
    // create both vertex and index buffer object for the cube. 
    mesh->CreateVBO(width, height, depth); 
    mesh->CreateIBO();                    
    return mesh;   // return the create mesh resource. 


}


// set vertex data for mesh.
void MeshResource::setVertices(const std::vector<vec3>& vertices)
{
    this->vertices = vertices; 
}

// set UV coordinates for the mesh. 
void MeshResource::setUVs(const std::vector<vec2>& uvs)
{
    this->uvs = uvs; 
}

// set index data for the mesh. 
void MeshResource::setIndices(const std::vector<unsigned int>& Indices)
{
    this->indices = Indices; 
}

// buffer for the mesh's vertex data and index data. 
//void MeshResource::setupMesh()
//{
//    glGenBuffers(1, &vertexBuffer); // generate vertex buffer. 
//    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // binding the vertex buffer after generating. 
//
//    // allocate buffer data for vertices. 
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW); 
//
//    // checking 
//    if (!uvs.empty()) 
//    {
//        GLuint uvBuffer; 
//        // generate UV buffer and bind it. 
//        glGenBuffers(1, &uvBuffer); 
//        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer); 
//
//        // allocate buffer data for UVs
//        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), uvs.data(), GL_STATIC_DRAW); 
//
//    }
//
//    //Create (IBO) bind after that.  
//    glGenBuffers(1, &indexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
//
//    // allocate buffer data for indics. 
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
//
//    // unbind index buffer 
//    glBindBuffer(GL_ARRAY_BUFFER, 0); 
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
//
//}

// Method to create a vertex buffer object for the cube. 
void MeshResource::CreateVBO(float width, float height, float depth)
{
    // calculate half dimensions for positioning. 
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    float halfDepth = depth / 2.0f;


    // create vertex data for the cube with pos, colors and Uvs 
    float positions[] = 
    {


        // front face
        -halfWidth, -halfHeight, -halfDepth,
        1.0f, 0.0f, 0.0f, 1.0f, // R  G  B   A 
        0.0f, 0.0f,  // u   v
        // 0       
         halfWidth, -halfHeight, -halfDepth,
         0.0f, 1.0f, 0.0f, 1.0f, // R  G  B   A 
         1.0f, 0.0f,  // u   v
         // 1
         halfWidth,  halfHeight, -halfDepth,
         0.0f, 1.0f, 0.0f, 1.0f, // R  G  B   A 
         1.0f, 1.0f,  // u   v
         // 2
        -halfWidth,  halfHeight, -halfDepth,
        0.0f, 0.0f, 1.0f, 1.0f, // R  G  B   A 
        0.0f, 1.0f,  // u   v
        // 3

        // back face
        -halfWidth, -halfHeight,  halfDepth,
        0.0f, 0.0f, 1.0f, 1.0f, // R  G  B   A 
        0.0f, 0.0f,  // u   v
        // 4
         halfWidth, -halfHeight,  halfDepth,
         0.0f, 1.0f, 0.0f, 1.0f, // A  G  B   A 
         1.0f, 0.0f,  // u   v
         // 5
         halfWidth,  halfHeight,  halfDepth,
         1.0f, 0.0f, 0.0f, 1.0f, // R  G  B   A 
         1.0f, 1.0f, // u   v  
         // 6
        -halfWidth,  halfHeight,  halfDepth,
        1.0f, 0.0f, 0.0f, 1.0f, // R  G  B   A 
        0.0f, 1.0f,  // u   v
        // 7

        // right face
         halfWidth, -halfHeight, -halfDepth,
         0.0f, 1.0f, 0.0f, 1.0f, // R  G  B   A 
         0.0f, 0.0f,  // u   v
         // 8
         halfWidth,  halfHeight, -halfDepth,
         0.0f, 1.0f, 0.0f, 1.0f, // R  G  B   A 
         0.0f, 1.0f,  // u   v
         // 9
         halfWidth, -halfHeight,  halfDepth,
         0.0f, 1.0f, 0.0f, 1.0f, // R  G  B   A 
         1.0f, 0.0f,  // u   v
         // 10
         halfWidth,  halfHeight,  halfDepth,
         1.0f, 0.0f, 0.0f, 1.0f, // R  G  B   A 
         1.0f, 1.0f,  // u   v
         // 11

         // left face
         -halfWidth, -halfHeight, -halfDepth,
         1.0f, 0.0f, 0.0f, 1.0f, // R  G  B   A 
         1.0f, 0.0f,  // u   v
         // 12
         -halfWidth,  halfHeight, -halfDepth,
         0.0f, 0.0f, 1.0f, 1.0f, // R  G  B   A 
         1.0f, 1.0f,  // u   v
         // 13
         -halfWidth, -halfHeight,  halfDepth,
         0.0f, 0.0f, 1.0f, 1.0f, // R  G  B   A 
         0.0f, 0.0f,  // u   v
         // 14
         -halfWidth,  halfHeight,  halfDepth,
         1.0f, 0.0f, 0.0f, 1.0f, // R  G  B   A 
         0.0f, 1.0f,  // u   v
         // 15

         // bottom face
         -halfWidth, -halfHeight, -halfDepth,
         1.0f, 0.0f, 0.0f, 1.0f, // R  G  B   A 
         0.0f, 0.0f,  // u   v
         // 16
         halfWidth, -halfHeight, -halfDepth,
         0.0f, 1.0f, 0.0f, 1.0f, // R  G  B   A 
         1.0f, 0.0f,  // u   v
         // 17
         -halfWidth, -halfHeight,  halfDepth,
         0.0f, 0.0f, 1.0f, 1.0f, // R G  B   A 
         0.0f, 1.0f,  // u   v
         // 18
         halfWidth, -halfHeight,  halfDepth,
         0.0f, 1.0f, 0.0f, 1.0f, // R  G  B   A 
         1.0f, 1.0f,  // u   v
         // 19

         // top face
        halfWidth,  halfHeight,  halfDepth,
        1.0f, 0.0f, 0.0f, 1.0f, // R  G  B   A 
        1.0f, 1.0f,  // u   v
        // 20
        -halfWidth,  halfHeight,  halfDepth,
        1.0f, 0.0f, 0.0f, 1.0f, // R  G  B   A 
        0.0f, 1.0f, // u   v
        // 21
        halfWidth,  halfHeight, -halfDepth,
        1.0f, 0.0f, 0.0f, 1.0f, // R  G  B   A 
        1.0f, 0.0f,  // u   v
        // 22
       -halfWidth,  halfHeight, -halfDepth,
       1.0f, 0.0f, 0.0f, 1.0f, // R  G  B   A 
       0.0f, 0.0f   
       // 23


    };

    

     // Generate and bind vertex buffer /VBOS
    glGenBuffers(1, &vertexBuffer);
    // Biding the VBO 
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // for VBO send the size of the float in array.
    // allocate buffer data for vertex pos.
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    // position attribute 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*) NULL); // position 
    //position.
    glEnableVertexAttribArray(0); 

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3  * sizeof(GLfloat))); // color
    // color.
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat))); // TexCoord
    // uv.
    glEnableVertexAttribArray(2);

    // unbind the VBO
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

}
   

    // Method to create an index buffer object
void MeshResource::CreateIBO()
{
  int indexes[] =
    {



          0, 1, 2, 2, 3, 0, // front face

          4, 5, 6, 6, 7, 4, // back face 

          8, 9, 11, 11, 10, 8, // right face

          12, 13, 15, 15, 14, 12, // left face

          16, 17, 19, 19, 18, 16, // bottom face

          21, 20, 22, 23, 22, 21 // top face
    };

    indexSize = sizeof(indexes) / sizeof(indexes[0]);

    // Generate and bind index buffer
    glGenBuffers(1, &indexBuffer);
    // binding IBO 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    // for IBO send the size of the float in array. 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(indexes), indexes, GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 

    //indexSize = sizeof(indexes) / sizeof(indexes[0]); 


    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   
}

void MeshResource::BindVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
}

void MeshResource::BindIBO()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

void MeshResource::Draw()
{

    // bind vertex buffer. 
    BindVBO();
    // bind index buffer.
    BindIBO();

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    // unbind both VBO and IBO 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MeshResource::Cleanup()
{
    if (vertexBuffer) 
    {
        glDeleteBuffers(1, &vertexBuffer); 
        vertexBuffer = 0; 

    }

    if (indexBuffer)
    {
        glDeleteBuffers(1, &indexBuffer);
        indexBuffer = 0;

    }

}