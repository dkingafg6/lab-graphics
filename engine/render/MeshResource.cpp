#pragma once
#include <config.h>
#include <GL/glew.h>
#include <render/MeshResource.h>
#include "core/vec3.h"
#include "core/vec2.h"
//#include "Vertex.h"





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
    //glDeleteBuffers(1, &vertexBuffer); 
    //glDeleteBuffers(1, &indexBuffer);
    ////glDeleteVertexArrays(1, &vbo);
    //// meshresource shuold clean when the object is destroyed. 
    //printf("Cleanup called in MeshResouce \n");
    Cleanup(); 
    
}



bool MeshResource::LoadOBJFiles(const std::string& filePath)
{
    //std::string file;
    std::ifstream objFile(filePath);
    if (!objFile.is_open())
    {
        std::cerr << "Faile to open OBJ file: " << filePath << std::endl;
        return false; 
       
    }

    std::cout << "loadig OBJ file: " << filePath << std::endl;
    std::string line;
    while (std::getline(objFile, line))
    {
        std::istringstream stream(line);
        std::string prefix;
        stream >> prefix;


        //Vertex vertex;
        //
        //Face face; 

        if (prefix == "v") 
        {  // Vertex position
            ParseVertexData(line); 
            /*vec3 position;
            stream >> position.x >> position.y >> position.z;
            vertex.position = position;*/
        }
        else if (prefix == "vt") 
        {  // Texture coordinate
            ParseTextureData(line); 
            /*vec2 texCoord;
            stream >> texCoord.x >> texCoord.y;*/
            /*if (!verticies.empty())
            {
                verticies.back().texCoord = texCoord;

            }*/
        }
        else if (prefix == "vn") 
        {  // Vertex normal
            ParseNormalData(line); 
           /* vec3 normal; 
            stream >> normal.x >> normal.y;
            vertex.normal = normal;
           
         */
        }
  

        else if (prefix == "f") 
        {  // Face
            ParseFaceData(line); 
            
            //std::string vertexInfo;
            //while (stream >> vertexInfo)
            //{
            //    std::istringstream vertexStream(vertexInfo);
            //    

            //        vertexStream >> face.vertexIndex; // Read vertex index

            //    if (vertexStream.peek() == '/')
            //    { // Check for '/' delimiter
            //        vertexStream.ignore(1); // Skip '/'
            //        if (vertexStream.peek() != '/') { // If there's no second '/', read texture index
            //            vertexStream >> face.textureIndex;
            //        }
            //        if (vertexStream.peek() == '/') { // Check for '/' delimiter again
            //            vertexStream.ignore(1); // Skip '/'
            //            vertexStream >> face.normalIndex; // Read normal index
            //        }
            //    }

            //}
            //verticies.push_back(vertex);
            //faces.push_back(face);
        }
    }

    objFile.close();

    std::cout << "OBJ file loaded: " 
        << positions.size() << " vertices, "
        << texCoords.size() << " Texture coordinates"
        << normals.size() << " normals, and "
        << indices.size() << " indices. " 
        << std::endl;


    CreateVBO(0, 0, 0); // generate vbo, 
    CreateIBO(); 
    return true; 

};



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
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);



    // Generate and bind vertex buffer /VBOS
    glGenBuffers(1, &vertexBuffer);
    // Biding the VBO 
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // for VBO send the size of the float in array.
    // allocate buffer data for vertex pos.
    glBufferData(GL_ARRAY_BUFFER, position.size() * sizeof(vec3), position.data(), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
   


    // position attribute 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)NULL); // position 
    //position.
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // color
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
    indexSize = indices.size(); 
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
    glBindVertexArray(vao); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    // bind vertex buffer. 
    BindVBO();
    // bind index buffer.
    BindIBO();

    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, nullptr);

    // unbind both VBO and IBO 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
std::vector<vec3> positions; 
void MeshResource::ParseVertexData(const std::string& line)
{
    std::istringstream stream(line); 
    std::string prefix; 
    vec3 position; 
    stream >> prefix >> position.x >> position.y >> position.z;  
    positions.push_back(position); 
    
}

void MeshResource::ParseTextureData(const std::string& line)
{

    std::istringstream stream(line);
    std::string prefix;
    vec2 texCoord; 
    stream >> prefix >> texCoord.x >> texCoord.y ;
    texCoords.push_back(texCoord);
}

void MeshResource::ParseNormalData(const std::string& line)
{

    std::istringstream stream(line);
    std::string prefix;
    vec3 normal;
    stream >> prefix >> normal.x >> normal.y >> normal.z;
    normals.push_back(normal);
}

void MeshResource::ParseFaceData(const std::string& line)
{

    std::istringstream stream(line);
    std::string prefix;
    stream >> prefix; 

    std::string vertexInfo; 

    while( stream >> vertexInfo)
    { 
        std::istringstream vertexStream(vertexInfo);
        unsigned int vertexIndex, texCoordIndex, normalIndex;
        char slash;

        vertexStream >> vertexIndex >> slash >> texCoordIndex >> slash >> normalIndex;


        indices.push_back(vertexIndex -1); // obj indices 1-base change to 0-based. 
        
    }

  
   
}



GLsizei MeshResource::GetIndexCount() const
{
    return GLsizei();
}

GLsizei MeshResource::GetVertexCount() const
{
    return GLsizei();
}

void MeshResource::Cleanup()
{
    if (vao) glDeleteVertexArrays(1, &vao);
    if (vertexBuffer) glDeleteBuffers(1, &vertexBuffer);
    if (indexBuffer) glDeleteBuffers(1, &indexBuffer);
    vao = vertexBuffer = indexBuffer = 0;
    
    
    /*
    if (vertexBuffer)
    {
        glDeleteBuffers(1, &vertexBuffer);
        vertexBuffer = 0;

    }

    if (indexBuffer)
    {
        glDeleteBuffers(1, &indexBuffer);
        indexBuffer = 0;

    }*/

}

// static factory methode
//static std::shared_ptr<MeshResource>CreateCube(float width, float height, float depth); 

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

std::shared_ptr<MeshResource> MeshResource::CreateCube_SharedPtr(float width, float height, float depth)
{
    // allocate a new meshResource object. 
    shared_ptr<MeshResource> mesh = std::make_shared<MeshResource>();
    // create both vertex and index buffer object for the cube. 
    mesh->CreateVBO(width, height, depth);
    mesh->CreateIBO();
    return mesh;   // return the create mesh resource. 


}


// set vertex data for mesh.
void MeshResource::setVertices(const std::vector<vec3>& position)
{
    this->position = position; 
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

  

//void MeshResource::LoadFromOBJ(const std::string& filePath)
//{
//   
//
//    return false;
//}


//
//std::shared_ptr<MeshResource> CreateCube(float width, float height, float depth)
//{
//    return std::shared_ptr<MeshResource>();
//}
