
// test opengl code basic model logic


class model 
{
    public:
        Model(char *path)
        {
            loadModel(path);
        }
        void Draw (Shader &shader);
    private:
        vector<Mesh> meshes;
        string directory;

        void loadModel (string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh (aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

};

// contains a vector mesh objects thast requires us to give it a file location in its constructor
// then loads the file in loadModel function that is called inside the constructor

void Draw(Shader &shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
    meshes[i].Draw(shader);
}

// importing a 3D model into opengl
// #include <assimp/Importer.hpp
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>

// uses assup to load model into a generla data structure of assimp called a scene object
// the reason why we use this library is because alot of 3D model file formats gets much more complicated data structures & differ between 3D file formats
// obj is the most readable & easiest to understand

Assump::Importer importer;
const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

// aiProcess_Triangulate -> tell assimp if the model does not consist of triangles, it should trandform all the models primitce shapes to triangles first
// aiProcess_FlipUVs -> flips the texture coordinates on the y-axis 

// aiProcess_GenNormals -> creates normal vectors for each vertex if the model doesn't contain normal vectors
// aiProcess_SplitLargeMeshes -> splits larges meshes into smaller sub meshes which is useful if your rendering has maximum number of vertices allowed & can only process smaller meshes
// aiProcess_OptimizeMeshes -> does the reverse by trying to join several meshes intok one larger mesh, reducing drawing calls for optimization

// complete loadModel func

void loadModel(string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipsUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}


// pass the first node (root node) to the recursive processNode fun. each node contains a set of childtren (attributes) we want to first process the node in question
// to continue processing all the nodes children, etc...

// must retrieve these mesh indices, retrieve each mesh, process each mesh, -> repeat process with children nodes

void processNode ( aiNode *node, const aiScene *scene)
{
    // process all the nodes meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[nodes->mMeshes[i]];
        meshes.push_back(processMesh(mesh,scene));
    }
    for (unsigned int = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}
// uses a for loop to check each nodes meshes indices + retrive corresponding mesh by indexing the scenes nMeshes array
// returned mesh -> processMesh func -> returns Mesh object -> stores in meshes list/vector


// after the intial first node or parent node, it goes thru the children


// Assimp to Mesh

Mesh processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex pos, vertex normal, and vertex textures coordinates
        [...]
        vertices.push_back(vertex);
    }

    // process indicies 
    [...]
    //process material

    if(mesh->mMaterialIndex >= 0)
    {
        [...]
    }
    return Mesh(vertices, indicies, textures);
}

// processed data is stored in one of the 3 vectors -> Mesh is created & returns to the func caller

// retrive vertex data
// define vertex struct, add vertices array -> after each loop interation
// loop as much vertices that exists within a mesh (pulled from >mNumVertices

// vertex pos:

glm::vec3 vector;
vector.x = mesh->mVertices[i].x;
vector.y = mesh->mVertices[i].y;
vector.x = mesh->mVertices[i].z;
vertex.Position = vector;

// we use vec3 because there are 3 types of data stores 
// do the same strcture for vertex normals 


// vertex textures are similar but Assimps allows a mdodel to have up to 8 different texture coordinates per vertex

// vertex texture

if(mesh->mTextureCoords[0])
{
    glm::vec3 vec;
    vec.x = mesh->mTextureCoords[0][i].x;
    vec.y = mesh->mTextureCoords[0][i].y;
    vertex.TexCoords = vec;
}
else 
    vertex.TexCoords glm::vec2(0.0f, 0.0f);

// assimps interface defines each mesh as having an array of faces, each face -> a single primitave (aiProcess_Triangulate) are always triagnles
// a face comntains the indices of the vertices we need to draw in what order for its primitive. 
// have to interate over all the faces + store all the faces indicies -> indices vector


for(unsigned int i = 0; i < mesh->mNumFaces; i++)
{
    aiFace face = mesh->mFaces[i];
    for(unsigned int j = 0; j < face.mNumIndicies;j++)
    indicies.push_back(face.mIndices[j]);
}

// once finishes -> complete set of vertices & index data for drawing the mesh via glDrawElements
// if want detail (texture) -> process meshes material as well

// retrieving material of mesh, index the scenes mMaterials array. the material index is set in its mMaterialIndex property, which we can query to check if the mesh contaisn a material or not

if (mesh->mMaterialIndex >= 0)
{
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");

    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
}

// must retrieve the aiMaterial obkect sfrom the scene mMaterials array
// load the meshes diffuse and/or speculae textures
// ^ why? fidn out
// a material obkect internall stores an array of texture locations for each texture type

// diff texture type prefixed inside aiTextType_
// use a helper fun -> loadMaterialTextures to retrieve, loadm intialize textures from the materials

// func returns a vec of texture structs that we store at the end of the models textures vector

// loadMmaterialsTextues function interates over all the texture locations, retrieve the texture file location, the  loads & generates the textures && stores the info in a Vertex struct
// ex:
vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type);i++){
        aiString str;
        mat ->GetTexture(type, i, &str);
        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), directory);
        texture.type = typeName;
        texture.path = str;
        textures.push_back(texture);
    }
    returns textures;
}


// OPTIMIZATION !!!

// storing all the loaded textures globally. Wherever we want to load a 
// texture, we first check if it hasn't been loaded already. if so, we take the texture & skip the entire loading routine, saving us alot of processing power.
// ^ might be good to check every time a glitch-bending pass happens

struct Texture {
    unsigned int id;
    string type;
    string path;
}

// store all the loaded texture in another vector declaured at the topc of the models class file as a priv variable 

vector<Texture> textures_loaded;

// in loadMaterialsTextures fun, compared th texture path with all the textures in the textures_loaded vector to see if the current path equals any of those. if so, we skip the trexture loading/generation + simply use located texture struct as the meshes texture

vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type);i++)
    {
        aiString str;
        mat ->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
        if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
        {
            textures.push_back(textures_loaded[j]);
            skip = true;
            breaks;
        }
    }
    if (!skip)
    { // if texture hasnt been loaded alr, load it
        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), directory);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
        textures_loaded.push_back(texture);
    }
} 
return textures;
    
}

// by default depth testing is disabledm nust enable with GL_DEPTH_TEST

glEnable(GL_DEPTH_TEST);

// once enables, opengl automatically stores fragments of their z-val in the depth buffer if they passed 
// if depth test enabled, clear the depth buffer before each frame using GL_DEPTH_BUFFER_BIT ; otherwise stuck with depth val from last frame

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// if u want to preform depth test on all frag & discard but not update the depth buffer. you can disable (not rec)
glDepthMask(GL_FALSE);

// GL_LESS is used to discord all the frags that have a depth val higher than or equal to the current depth buffer val

// DEPTH VALUE PRECISION

// depth val between 0.0 - 1.0 && compares its content with the z val of all the objects in the scene as seen from the viewer
    


// DEPTH TESTING
// depth values the depth buffer (z-buffer) stores & how it actually detrermines if a fratment is in the front

// the depth buffer is automatically created by the windowing sytems + stores its depth value as 16, 24, 32 bit floats
// most systems will have a depth buffer with a percision of 24 bits

// transforming depth value range [0,1] -> [-1,1] -> NDC space -> perspective divide -> clip space -> view space -> world space

// transform the depth value to NDC
float ndc = depth * 2.0 - 1.0;

// resulting ndc value + apply inverse transformation to retrieve its linear depth value

float linearDepth = (2.0 * near * far) / (far + near - ndc *(far - near));
// equations rerirved from the projects matrix for non linear depth values, returning depth value between near && far

// complete fragment shader that transforms the non-linear deoth n screen-space to a linear depth value

#version 330 core
out vec4 FragColor;

float near = 0.1; // near plane
float far = 100.0; // far plane

float LinearizeDepth(float depth)
{
    float ndc = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - ndc * (far - near));    
}

void main()
{
    float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    FragColor = vec4(vec3(depth), 1.0);
}


// ------- FRAME BUFFERS ----------
// frambuffers are stored in the GPU memory
// screen buffer -> writing color values
// depth buffer -> writing depth values

// CREATEING a FRAME BUFFER OBJECT (FBO)
unsigned int fbo;
glGenFramebuffers(1, &fbo);

// to bing the frame buffer 
glBindFramebuffer(GL_FRAMEBUFFER, fbo);
// binding GL_FRAME BUFFFER target all the next read && write frambuffer operations will affect the currently bound frambuffer
// not done, must attach one buffer (color, depth, stencil), atleast 1 color attachment
// all attachemnets should be complete as well (reserved memory)
// each buffer should have the same # of samples


// creating some kind of attachment for the frambuffer 
if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)

// subsequent rendering operateions will now render to the attachments of the current bound framebuffer 
// our framebuffer is not default, rendering commands will have 0 impact on visual output (called off-screen rendering)

// if you want all rendering operations to have a visual impact on the main window. make the deault framebuffer active by binding to 0

glBindFramebuffer(GL_FRAMEBUFFER, 0);
//when done with operations, delete the framebuffer objects
glDeleteFramebuffers(1, &fbo);s


// ----- Texture Attachments -----
// attaching a texture to a framebuffer will allow for rendering comments to write to the texture like a normal color/depth buffer
// pros: render output is stoed inside the texture image that can easily be used in our shaders

// creating a texture for a framebuffer 
unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
glTexImage2D(GL_TEXTURE_2d, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


// attach texture to the framebuffer
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
// glFramebufferTexture2D parameters: target, attachment, textarget, texture, level


// create a texture img -> color attachement to the framebuffer

unsigned int textureColorbuffer;
glGenTextures(1, &textureColorbuffer);
glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
glTexImage2d(GL_TEXTURE_2D, 0, GL_RBG, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glBindTexture(GL_TEXTURE_2D, 0);

// attachiing it -> currently bound framebuffer object
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);


// ----- instancing ----

// basically calling the obj in a for loop  
// instead it can draw many of the same mesh obkects in a signle render call
// reduse cpu -> gpu communication 

// how you regularly call multiple of the same meshes

for (unsigned int i = 0; i < amount_of_models_to_draw; i++){
    DoSomePrep();
    glDrawArrays(GL_TRIANGLES, 0, amount_of_vertices);
}

// instead of calling glDrawArrays && glDrawElements
// glDrawArraysInstances && glDrawElementsInstances

// basically sending the instruction to render to the GPU once in a single call 
// renders the instances w/p continually communicating with CPU
// glsl built-in var : gl_InstanceID

// to call the multiple obj in action 

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

out vec3 fColor;

uniform vec2 offsets[100];

void main(){
    vec2 offset = offset[gl_InstanceID]
    gl_Position = vec4(aPox + offset, 0.0, 1.0);
    fColor = aColor;
}

// basically caling it 100 times + using the offset to lay it out on a grid
// set offset pos in a nested for loop before render loop

glm::vec2 offsets[100];
int index = 0;
float offset = 0.1f;
for (int y = -10; y < 10; y += 2)
{
    for (int x = -10; x < 10; x += 2)
    {
        glm::vec2 translation;
        translation.x = (float)x / 10.0f + offset;
        translation.y = (float)y / 10.0f + offset;
        offsets[index++] = translation;
    }
}   

//need to transfer the data to the vertex shader uniform array

shader.use();
for (unsigned int i = 0; i < 100; i++)
{
    shader.setVec2("offsets[" + std::to_string(i) + "]", offsets[i]);
}
// turning the for loop counteri to a string create a location string for querying the uniform location
// each item in the offset uniform array we then set the corresponding translation vector 

// now we can call
// glBindVertexArray(quadVAO);
// glDrawArraysInstances(GL_TRIANGLES, 0, 6, 100);
// instead of drawing 100 instances, it displays 100 quads in a 10 x 10 grid

// ---------- instanced arrays --------

// defined as a vertex attribute that are updated per instance of per vertex
// yodates the vertex shader by adding another vertex atttribute 

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aOffset;

out vec3 fColor;
void main (){
    gl_position = vec3(aPox + aOffset, 0.0, 1.0);
    fColor = aColor;
}

//instead of using instanceID we are directly using the offeset attribute because the location is stored as a global vari

// now that an instances array is a vertex attribute, just like pos && color var
// need to store them into a vertex buffer obj && config to attribute pointer

// store in translation array v

unsigned int instanceVBO;
glGenBuffers(1, &instanceVBO);
glBinderBuffer(GL_ARRAY_BUFFER, instanceVBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(glm:vec2) * 00, $translations[0], GL_STATIC_DRAW);
glBinderBuffer(GL_ARRAY_BUFFER,0);

// need to set vertex attri pointer to enable vertex attri 

glEnableVertexAttriArray(2);
glBinderBuffer(GL_ARRAY_BUFFER, instanceVBO);
glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
glBindBudder(GL_ARRAY_BUFFER, 0);
glVertexAttribDivisior(2,1); // tells openGL when to update the content of a vertex attri 

// by default Attri divisio is 0
// 2 = attrib ; 1 = attri divisior 

// ---------- anti-aliasing --------------

// because of the limtied amount of screen pixels, some pixels will be rendered along an edge and some wont
// giving that jagged edge, usually happens in single sampling points. where in each pixel there is 1 point  to determine coverage of the triangle
// however with multi sampling points there are multiple points within a pixel  to determine coverage. more likely to have smoother edges


// not all subsamples will be covered in the fragment shader but will have a sort of gradient 
// the less the subsample art part of the triangle, the less the color of the triangle 

// ---------- multisampled  anti aliasing in practice ------------
// need to use a buffer to be able to store more than oen sample value per pixel
// new buffer that can store multisamples -> multisample buffer

// must use 
glfwWindowHint(GLFW_SAMPLES, 4);
                 //        (# of subsamples)
// when we call the func, we are creating a rendering window but with a buffer containing 4 subsamples per screen coordinate 
// this also means size of buffer is increased by 4 

// glEnable (GL_MULTISAMPLE);

// GLFW takes care of creating multisampled buffers, but if we want our own frame buffers. must generate multisampled buffers ourselves
// to create multi sampled buffers to act as  attachments for frame buffers: texture attrachments and render buffer. 

// ------ multisampled texture attachment 

glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, tex);
glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, width, height, GL_TRUE);
glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,0);

// to attach the multi sampled texture, use glFramebufferTexture2D but use GL....Multisample as texture type

glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2d_MULTISAMPLE,text, 0);

// bounds framebuffer now has a multisampeld color buffer in the form of a texture img

// mutlisampled render buffer objects 
glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height);

// render to multi sampled framebuffer
// must downscale or resolve the img because it contains so much more information compared to a normal img 
// resolving a multi sampeld framebuffer is generally done through glBlitFrameBuffer
// glBlitFramebuffer func reads from  those two targets to determine which is the source and which is the target framebuffer

glBindFramebuffer(GL_READ_FRAMEBUFFER, multisampeldFBO);
glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

// to get texture value per substample, define the texture uniform sampled as sample2DMS instead of sampeler2D
uniform sampler2DMS screenTextureMS;

// use texelFeth func to retrieve color val per sample
vec5 colorSample = texelFetch(screenTextureMS, TexCoords, 3);

// loading obj files

bool loadOBJ(
    const char * path,
    std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals
) 