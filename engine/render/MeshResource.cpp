#pragma once
#include <config.h>
#include <GL/glew.h>
#include <render/MeshResource.h>

using namespace std; 

// Constructor
MeshResource::MeshResource()
{
    vertexBuffer = 0; 
    indexBuffer = 0; 
    indexSize = 0; 
    
}

// Destructor
MeshResource::~MeshResource()
{
    // meshresource shuold clean when the object is destroyed. 
    Cleanup(); 
    
}
MeshResource* MeshResource::CreateCube(float width, float height, float depth) 
{
    MeshResource* mesh = new MeshResource(); 
    mesh->CreateVBO(width, height, depth); 
    mesh->CreateIBO(); 
    return mesh; 


}

// optional higher grade function spherical 
//MeshResource* MeshResource::CreateSpher(float radius, unsigned int rings, unsigned int sectors)
//{
//    std::vector<vec3> vertices; 
//    std::vector<vec2> uvs;
//    std::vector<unsigned int> indices;
//
//    //
//    for (unsigned int r = 0; r <= rings; ++r)
//    {
//        for (unsigned int s = 0; s <= sectors; ++s)
//        {
//            float y = cos((2 * asin(1.0) * r )/ rings);
//            float x = cos(2 * (2 * asin(1.0) )* s / sectors) * sin((2 * asin(1.0)) * r / rings);
//            float z = sin(2 * (2 * asin(1.0)) * s / sectors) * sin((2 * asin(1.0) )* r / rings);
//
//            vertices.emplace_back(x * radius, y * radius, z * radius); 
//            uvs.emplace_back((float)s / sectors, (float)r / rings); 
//        }
//
//    }
//
//    for (unsigned int r = 0; r < rings; ++r) 
//    {
//        for (unsigned int s = 0; s < sectors; ++s) 
//        {
//            unsigned int first = (r * (sectors + 1)) + s; 
//            unsigned int second = first + sectors + 1; 
//
//            indices.push_back(first); 
//            indices.push_back(second);
//            indices.push_back(first + 1);
//
//            indices.push_back(second);
//            indices.push_back(second + 1);
//            indices.push_back(first + 1);
//
//        }
//
//    }
//
//    MeshResource* mesh = new MeshResource(); 
//    mesh->setVertices(vertices); 
//    mesh->setUVs(uvs); 
//    mesh->setIndices(indices); 
//    mesh->setupMesh(); 
//    return mesh;
//}
//void MeshResource::setVertices(const std::vector<vec3>& vertices)
//{
//    this->vertices = vertices; 
//}
//void MeshResource::setUVs(const std::vector<vec2>& uvs)
//{
//    this->uvs = uvs; 
//}
//void MeshResource::setIndices(const std::vector<unsigned int>& Indices)
//{
//    this->indices = Indices; 
//}
//void MeshResource::setupMesh()
//{
//    glGenBuffers(1, &vertexBuffer); 
//    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); 
//
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW); 
//
//    if (!uvs.empty()) 
//    {
//        GLuint uvBuffer; 
//        glGenBuffers(1, &uvBuffer); 
//        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer); 
//        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), uvs.data(), GL_STATIC_DRAW); 
//
//    }
//
//    //IBO 
//    glGenBuffers(1, &indexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
//
//    // unbinde 
//    glBindBuffer(GL_ARRAY_BUFFER, 0); 
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
//
//}
// Method to create a vertex buffer object for the cube. 
void MeshResource::CreateVBO(float width, float height, float depth)
{
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    float halfDepth = depth / 2.0f;


    // create vbo with vertext structure. 
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

    // Define vertex data (position, color, uv)

     // Generate and bind vertex buffer /VBOS
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    // position attribute 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*) NULL);
    //position.
    glEnableVertexAttribArray(0); 

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3  * sizeof(GLfloat)));
    // color.
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
    // uv.
    glEnableVertexAttribArray(2);

    // unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(indexes), indexes, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 

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

//void MeshResource::Draw()
//{
//    BindVBO();
//    BindIBO();
//
//    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0); 
//}

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