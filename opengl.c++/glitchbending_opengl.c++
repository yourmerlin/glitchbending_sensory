
// ------ OUR LOGIC FLOW -------

// load 3D model
// class of model
// sub-class (attribute) of vertices, indices, textures
// processNode -> processMesh -> loadMaterialTextures
// use framebuffers to help with optimization
// struct vertex textures should be a global variable so it can run in the GPU


// struct vertex, indicies, textures (because c++ is a compiled language, we need to define the struct before we can use it in the Mesh class)
// use geometry shader effet to create the explosion(be able to move vertices in the coordinate system

// you can use time to have a dynamic/live effect
// i will be using a heart rate sensor BPM (analog signal -> converted to BPM)
// bpm -> send to shader (global var for bpm)


// would need to pull my obj file 


// get the normal vector of the triangle (3 vertices) and use it to move the vertices in the direction of the normal vector

// include file + libraries 
#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <learnopengl/mesh.h>
#include <learnopengl/shader.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);


void framebuffer_size_callback(GLFWwindow* window, int width, int height);


// settings for window w/h
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// my logic is having them as seperate struc so i can have a better control of the attributes of the model (vertices, indices, textures) and be able to manipulate them in the shader
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
}

// struct to hold the texture data (id, type, path)

struct Texture {
    unsigned int id;
    string type;
    string path;
}

struct Mesh {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        setupMesh();
    }

    void Draw(Shader &shader);

    private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
}
// geometry shader to get the normal vector of the triangles
vec GetNormalVector()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_ins[2].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 normal = cross(a, b);
    return normal;
}

// glitchbending class to handle the model and its attributes
    // vertices = change pos based on noise threshold
    // vertex texture = change vt pos based on noise threshold. maybe try to incorporate fragshaders to give a more visual distortion effect
    // faces = faces will be deleted based on noise threshold
    
class glitchbending
{
    public:
    glitchbending();
    void Draw(Shader &shader);
    private:
    vector<Model> models;
}

// model class to handle the loading of the model and its attributes
class model 
{
    public:
    Model(chat *path)
    {
        loadModel(path);
    }
    void Draw(Shader &shader);
    private:
    vector<Mesh> meshes;
    string directory;

    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
}

void processNode (aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

Mesh processMesh (aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        
        vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}
// steps to create glitch bend
// open model
// create ruleset for each elements (vertices, vertex normal & verte texture
// seperated into their own sub-class (attribute)

// by storing the loaded textutes globally, checks if it hasnt been loaded

