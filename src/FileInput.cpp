#include <FileInput.h>
#include <memory>
#include <Types.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace OPut{

    /*
    What's good owen you are pretty sleepy right now but worried you'll forget 
    the approach we're using for our model loader, there are a few main issues with a model loader
    the main one is we don't know how much memory we need for this so we either have to return this as a pointer
    to the heap allocated memory, or a smart pointer to it (probably a unique pointer) however, we can get away with
    not worrying about keeping this memory around for very long if we just bind it straight in the vbo and run and gun from there,
    that decision lies in your hands, although I think that maybe you write both, a load Model behind the scenes function, and
    an easier plug to mesh straight up function, although that would fuck up the constructor, overall i feel there is a better case for just returning
    a struct with all the info;
    */


    Mesh loadModel(const char* path)
    {
        Assimp::Importer Im;
        const aiScene* Scene = Im.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        
        if(!Scene->HasMeshes())
        {
            std::cout << "unable to retrieve meshes\n";
        }
        int vertCount = Scene->mMeshes[0]->mNumVertices;
        int faceCount = Scene->mMeshes[0]->mNumFaces;

        std::unique_ptr<unsigned int[]>indices = std::make_unique<unsigned int[]>(faceCount * 3);
        for(int i = 0; i < faceCount; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                indices[(i*3)+j] = Scene->mMeshes[0]->mFaces[i].mIndices[j];
            }
        }

        std::unique_ptr<OTypes::Vertex[]>Vertices = std::make_unique<OTypes::Vertex[]>(vertCount);
        for(int i = 0; i < vertCount; i++)
        {
            aiVector3D texcoord = Scene->mMeshes[0]->mTextureCoords[0][i];
            aiVector3D vertcoord = Scene->mMeshes[0]->mVertices[i];
            OTypes::UV uvobj = {texcoord.x, texcoord.y};
            OTypes::Vec3 pos = {vertcoord.x, vertcoord.y, vertcoord.z};

            Vertices[i] = OTypes::Vertex{pos, uvobj};
        }
        Mesh m(Vertices.get(), vertCount, indices.get(), faceCount*3);
        return m;
    }

    std::string ReadFile(const char *Path)
    {
        std::ifstream f;
        f.open(Path, std::ios::in);
        if (!f.is_open())
        {
            std::cout << "file couldn't be read at" << Path << '\n';
        }

        // read whole file into stringstream buffer
        std::stringstream buffer;
        buffer << f.rdbuf();
        buffer << "\0";
        f.close();
        // need to copy, as pointer is deleted when call is finished
        std::string shaderCode = buffer.str();

        return shaderCode;
    }
    unsigned int genTexture(const char *Path)
    {
        unsigned int Texture;

        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int Width, Height, Channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *ImgSrc = stbi_load(Path, &Width, &Height, &Channels, 0);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, ImgSrc);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(ImgSrc);
        return Texture;
    }
}
