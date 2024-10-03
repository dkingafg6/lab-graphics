#pragma once
#include <config.h>
#include <GL/glew.h>
#include <render/MeshResource.h>

using namespace std; 

//
//// sructure for vertices to create cube. 
//struct Vertex
//{
//    float position[3];   // position x,y,z, 
//    float colot[4];      // color r,g,b,and a, 
//    float texCoord[2];   // texture coordinates u and v, 
//
//};

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
// Method to create a vertex buffer object for the cube. 
void MeshResource::CreateVBO(float width, float height, float depth)
{
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    float halfDepth = depth / 2.0f;


    // create vbo with vertext structure. 
    Vertex positions[] = 
{
        // front face
        {-halfWidth, -halfHeight, -halfDepth},  { 1.0f, 0.0f, 0.0f, 1.0f},
        { halfWidth, -halfHeight, -halfDepth},  { 0.0f, 1.0f, 0.0f, 1.0f},
        { halfWidth,  halfHeight, -halfDepth,}, { 0.0f, 1.0f, 0.0f, 1.0f},
        {-halfWidth,  halfHeight, -halfDepth,}, { 0.0f, 0.0f, 1.0f, 1.0f},


        // back face
        {-halfWidth, -halfHeight, halfDepth},  { 0.0f, 0.0f, 1.0f, 1.0f},
        { halfWidth, -halfHeight, halfDepth},  { 0.0f, 1.0f, 0.0f, 1.0f},
        { halfWidth,  halfHeight, halfDepth,}, { 1.0f, 1.0f, 0.0f, 1.0f},
        {-halfWidth,  halfHeight, halfDepth,}, { 1.0f, 0.0f, 0.0f, 1.0f},


        // right face
        { halfWidth, -halfHeight, -halfDepth},  { 0.0f, 1.0f, 0.0f, 1.0f},
        { halfWidth,  halfHeight, -halfDepth},  { 0.0f, 1.0f, 0.0f, 1.0f},
        { halfWidth, -halfHeight,  halfDepth,}, { 0.0f, 1.0f, 0.0f, 1.0f},
        { halfWidth,  halfHeight,  halfDepth,}, { 0.0f, 0.0f, 0.0f, 1.0f},


        // left face
        {-halfWidth, -halfHeight, -halfDepth},  { 1.0f, 0.0f, 0.0f, 1.0f},
        { halfWidth,  halfHeight, -halfDepth},  { 0.0f, 0.0f, 1.0f, 1.0f},
        { halfWidth, -halfHeight,  halfDepth,}, { 0.0f, 0.0f, 1.0f, 1.0f},
        {-halfWidth,  halfHeight,  halfDepth,}, { 1.0f, 0.0f, 0.0f, 1.0f},


        // bottom face
        {-halfWidth, -halfHeight, -halfDepth},  { 1.0f, 0.0f, 0.0f, 1.0f},
        { halfWidth, -halfHeight, -halfDepth},  { 0.0f, 1.0f, 0.0f, 1.0f},
        { halfWidth, -halfHeight,  halfDepth,}, { 0.0f, 0.0f, 1.0f, 1.0f},
        {-halfWidth, -halfHeight,  halfDepth,}, { 0.0f, 1.0f, 0.0f, 1.0f},


        // top face
        {-halfWidth, halfHeight,  halfDepth},  { 1.0f, 0.0f, 0.0f, 1.0f},
        { halfWidth, halfHeight,  halfDepth},  { 1.0f, 1.0f, 0.0f, 1.0f},
        {-halfWidth, halfHeight, -halfDepth,}, { 1.0f, 1.0f, 0.0f, 1.0f},
        { halfWidth, halfHeight, -halfDepth,}, { 1.0f, 0.0f, 1.0f, 1.0f},

    };

    // Define vertex data (position, color, uv)

     // Generate and bind vertex buffer /VBOS
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

}
//    glEnableVertexAttribArray(0); //pos
//    glEnableVertexAttribArray(1); //color
//    glEnableVertexAttribArray(2); //UV
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 9, NULL);
//    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 9, (GLvoid*)(sizeof(float32) * 3));
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 9, (GLvoid*)(sizeof(float32) * 7));
//
//    // unbind the VBO
//    glBindBuffer(GL_ARRAY_BUFFER, 0);




// Method to create an index buffer object
void MeshResource::CreateIBO()
{
    unsigned int indexes[] =
    {

          0, 1, 2, 2, 3, 0, // front face

          4, 5, 6, 6, 7, 4, // back face 

          8, 9, 11, 11, 10, 8, // right face

          12, 13, 15, 15, 14, 12, // left face

          16, 17, 19, 19, 18, 16, // bottom face

          21, 20, 22, 23, 22, 21 // top face
    };

    // Generate and bind index buffer
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(indexes), indexes, GL_STATIC_DRAW);
    indexSize = sizeof(indexes) / sizeof(indexes[0]); 


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
    BindVBO();
    BindIBO();

    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0); 
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

//
//// Static method to create a cube mesh
//MeshResource* MeshResource::CreateCube(float width, float height, float depth)
//{
//
//    MeshResource* cubeMesh = new MeshResource();
//    cubeMesh->CreateVBO(width, height, depth);
//    cubeMesh->CreateIBO();
//    return cubeMesh;
//}
//
//std::shared_ptr<MeshResource> MeshResource::CreateCubeSharedptr(float width, float height, float depth)
//{
//    std::shared_ptr<MeshResource> cubeMesh = std::make_shared<MeshResource>();
//    cubeMesh->CreateVBO(width, height, depth);
//    cubeMesh->CreateIBO();
//    return cubeMesh;
//}
//
//void MeshResource::loadFromOBJ(const std::string& filename, float scale)
//{
//    std::stringstream ss;
//    std::ifstream infile(filename);
//    std::string line = "";
//
//    std::vector<vec3> tempVertices;
//    std::vector<vec3> tempUVs;
//    std::vector<vec3> tempNormals;
//    std::vector<Vertex> finalVertices;
//    std::vector<GLuint> vertexIndices;
//
//    if (!infile.is_open())
//    {
//        std::cout << "error not loading file\n";
//    }
//
//    while ((std::getline(infile, line)))
//    {
//        std::istringstream iss(line);
//        std::string prefix;
//        iss >> prefix;
//
//        if (prefix == "v")
//        {
//            vec3 vertex;
//            iss >> vertex.x >> vertex.y >> vertex.z;
//            tempVertices.push_back(vertex);
//        }
//        else if (prefix == "vt")
//        {
//            vec3 uv;
//            iss >> uv.x >> uv.y;
//            uv.y = 1.0f - uv.y; // invert v cordinate for openGL
//            uv.z = 0.0f;
//            tempUVs.push_back(uv);
//        }
//        else if (prefix == "vn")
//        {
//            vec3 normal;
//            iss >> normal.x >> normal.y >> normal.z;
//            tempNormals.push_back(normal);
//        }
//        else if (prefix == "f")
//        {
//            GLuint vertexIndex[3], uvIndex[3], normalIndex[3];
//
//            for (int i = 0; i < 3; i++)
//            {
//
//                char slash; // to sonsume the '/' character
//
//                iss >> vertexIndex[i] >> slash >> uvIndex[i] >> slash >> normalIndex[i];
//
//                // OBJ files use 1-based indexing so subtract 1
//                vertexIndex[i]--;
//                uvIndex[i]--;
//                normalIndex[i]--;
//
//            }
//
//            for (int i = 0; i < 3; i++)
//            {
//                Vertex vertex;
//                vertex.position = tempVertices[vertexIndex[i]] * scale;
//                vertex.uv = tempUVs[uvIndex[i]];
//                vertex.color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
//
//                finalVertices.push_back(vertex);
//                vertexIndices.push_back(finalVertices.size() - 1);
//            }
//        }
//    }
//    infile.close();
//
//    indexCount = vertexIndices.size();
//
//
//    // Generate and bind vertex buffer
//    glGenBuffers(1, &vertexbuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//    glBufferData(GL_ARRAY_BUFFER, finalVertices.size() * sizeof(Vertex), finalVertices.data(), GL_STATIC_DRAW);
//
//    // Generate and bind index buffer
//    glGenBuffers(1, &indexbuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(GLuint), vertexIndices.data(), GL_STATIC_DRAW);
//
//    //// Set vertex attributes
//    glEnableVertexAttribArray(0); // Position
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
//
//    glEnableVertexAttribArray(1); // Color
//    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
//
//    glEnableVertexAttribArray(2); // UV
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
//
//    //glEnableVertexAttribArray(3); // normals
//    //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normals));
//
//    // Unbind VAO and buffers
//    glBindVertexArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//}
//
//
//// Method to delete buffers
//void MeshResource::deleteBuffers()
//{
//    if (buffersCreated)
//    {
//        if (vertexbuffer != 0)
//        {
//            glDeleteBuffers(1, &vertexbuffer);
//            vertexbuffer = 0;
//        }
//
//        if (indexbuffer != 0)
//        {
//            glDeleteBuffers(1, &indexbuffer);
//            indexbuffer = 0;
//        }
//
//        buffersCreated = false;
//    }
//}
