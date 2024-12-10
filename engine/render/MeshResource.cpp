
#include <config.h>
#include <GL/glew.h>
#include <render/MeshResource.h>
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
    /*if (vao) glDeleteVertexArrays(1, &vao); 
    if (vertexBuffer) glDeleteBuffers(1, &vertexBuffer); 
    if (indexBuffer) glDeleteBuffers(1, &indexBuffer); */

    //glDeleteBuffers(1, &vertexBuffer); 
    //glDeleteBuffers(1, &indexBuffer);
    ////glDeleteVertexArrays(1, &vbo);
    //// meshresource shuold clean when the object is destroyed. 
    //printf("Cleanup called in MeshResouce \n");
    Cleanup(); 
    
}



void MeshResource::LoadOBJFiles(const std::string& filePath)
{
    std::ifstream objFile(filePath);
    std::string line = "";

    //vertex
    std::vector<vec3> tempVertices;
    std::vector<vec3> tempTexCoords;
    std::vector<vec3> tempNormals;

    //faces
    std::vector<Vertex> finalVertices;
    std::vector<GLuint> vertexIndices;

    if (!objFile.is_open())
    {
        cerr << "Error Faild to open OBJ file. " << filePath << endl;
    }

    std::cout << "loadig OBJ file: " << filePath << std::endl;
   

    while (std::getline(objFile, line))
    {
        std::cout << "Line: " << line << std::endl;
        std::istringstream stream(line);
        std::string prefix;
        stream >> prefix;

        if (prefix == "v") 
        {
            vec3 position;

            stream >> position.x >> position.y >> position.z;
            tempVertices.push_back(position);
        }
        else if (prefix == "vt") 
        {  
          
            vec3 texCoord;
            stream >> texCoord.x >> texCoord.y;
            texCoord.y = 1.0f - texCoord.y; // invert v cordinate for openGL
            texCoord.z = 0.0f;
            tempTexCoords.push_back(texCoord);


        }
        else if (prefix == "vn") 
        {  // Vertex normal
            
            vec3 normal; 
            stream >> normal.x >> normal.y >> normal.z;
            tempNormals.push_back(normal);
           
         
        }
  

        else if (prefix == "f")
        {  // Face
            int vertexIndex[3], texCoordIndex[3], normalIndex[3];


            for (int i = 0; i < 3; i++)
            {

                char slash; // to eat the '/' character

                stream >> vertexIndex[i] >> slash >> texCoordIndex[i] >> slash >> normalIndex[i];

                //// OBJ files use 1-based indexing so subtract 1
                //vertexIndex[i]--;
                //texCoordIndex[i]--;
                //normalIndex[i]--;

            }

            for (int i = 0; i < 3; i++)
            {
                Vertex vertex;
                vertex.position = tempVertices[vertexIndex[i] + tempVertices.size()];
                vertex.texCoord = tempTexCoords[texCoordIndex[i] + tempTexCoords.size()];
                vertex.color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
                vertex.normal = tempNormals[normalIndex[i] + tempNormals.size()];

                finalVertices.push_back(vertex);
                vertexIndices.push_back(finalVertices.size() - 1);
            }
            
        }
        int done = 56;
        
    }

    objFile.close();

    indexSize = vertexIndices.size();


    // Generate and bind vertex buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, finalVertices.size() * sizeof(Vertex), finalVertices.data(), GL_STATIC_DRAW);

    // Generate and bind index buffer
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(GLuint), vertexIndices.data(), GL_STATIC_DRAW);

    //// Set vertex attributes
    glEnableVertexAttribArray(0); // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1); // Color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));

    glEnableVertexAttribArray(2); // UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));

    glEnableVertexAttribArray(3); // normals
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

    // Unbind VAO and buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



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



GLsizei MeshResource::GetIndexCount() const
{
    return GLsizei();
}

GLsizei MeshResource::GetVertexCount
() const
{
    return GLsizei();
}

void MeshResource::Cleanup()
{
    if (vao) glDeleteVertexArrays(1, &vao);
    if (vertexBuffer) glDeleteBuffers(1, &vertexBuffer);
    if (indexBuffer) glDeleteBuffers(1, &indexBuffer);
    vao = vertexBuffer = indexBuffer = 0;
    
   

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

