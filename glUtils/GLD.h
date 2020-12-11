#ifndef STARGAME_GLD_H
#define STARGAME_GLD_H

/*
 * GLD - OpenGL Drawer
 */

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include "../core/shortCalls.h"
#include <SOIL/stb_image_aug.h>

using namespace glm;

class Rect{
public:
    Rect(){

        this->texture = 0;
        this->x = 0.0f;
        this->y = 0.0f;
        this->w = 0.0f;
        this->h = 0.0f;
        this->color = vec3(1.0f,1.0f,1.0f);

        Shader* shader = new Shader("../assets/shaders/tex.v", "../assets/shaders/tex.f");
        myShader = shader;

        init();
    }

    fun init() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void setColor(vec3 c){
        myShader->use();
        myShader->setVec3("textColor", c.x, c.y, c.z);
    }

    void loadTexture(char* path){
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        //stb(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    void loadTextures(char* path){
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        //stb(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }



    void draw(float ww, float wh){

        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(ww),0.0f, static_cast<float>(wh) );
        myShader->use();
        myShader->setMat4("projection", projection);

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);


            float vertices[6][4] = {
                    { x,     y + h,   0.0f, 0.0f },
                    { x,     y,       0.0f, 1.0f },
                    { x + w, y,       1.0f, 1.0f },

                    { x,     y + h,   0.0f, 0.0f },
                    { x + w, y,       1.0f, 1.0f },
                    { x + w, y + h,   1.0f, 0.0f }
            };
            glBindTexture(GL_TEXTURE_2D, texture);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

    }

    void utilize(){
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
        glDeleteBuffers(1, &this->EBO);

        delete myShader;
    }

    fun setPos(float xC,float yC){
        this->x = xC;this->y = yC;
    }

    fun setSize(float xC,float yC){
        this->w = xC;this->h = yC;
    }

private:
    GLuint texture;
    float x,y,w,h;
    vec3 color;

    GLuint VBO, VAO, EBO;
    Shader* myShader = nullptr;
};

#endif //STARGAME_GLD_H
