//
// Created by mahir on 2/14/23.
//

#ifndef UNTITLED2_GUI_H
#define UNTITLED2_GUI_H
#include <vector>
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_opengl3_loader.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <string>
#include "../Vector.h"
#include "../shapes.h"
#include <stdlib.h>
class gui
{
private:

    float r, g, b;
    std::string text;
    int width = 600, height = 400;
//    GLuint texture = NULL;
public:
    ImVec2 imagesize = ImVec2(width, height);
    GLuint texture = NULL;
//    unsigned char bluepixel[4] = {0,0,255,255};

//    unsigned char getPixel() {return bluepixel[4];}
    gui()
    {
        r = g = b = 0.f;
        text = "";
//        ImGui::Image(textureid, ImVec2(width, height));

//        glGenTextures(1, &texture);
//        glBindTexture(GL_TEXTURE_2D, texture);
        UpdateTexture();

    }
    void SetRed(const float rv)
    {
        r = rv;
//        Update();
//        std::cout << r <<"\n";
    }
    void SetGreen(const float gv)
    {
        g = gv;
//        Update();
    }
    void SetBlue(const float bv)
    {
        b = bv;
//        Update();
    }


//    GLuint GetTexture() { return texture; }
//    ImTextureID GetTextureID() {return texture;}
//    int GetTextureWidth() { return width; }
//    int GetTextureHeight() { return height; }
//    int SetTexture() {this.texture}

    const std::string GetText() { return text; }

    void Update() {
        UpdateText();
        UpdateTexture();
    }

//    void bluePixel()
//    {
//        glGenTextures(1, &texture);
//        glBindTexture(GL_TEXTURE_2D, texture);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,bluepixel);
//        glBindTexture(GL_TEXTURE_2D, 0);
//        ImGui::Image(reinterpret_cast<void *>(texture), imagesize);
//    }
    shapes::sphere sphere = shapes::sphere(Vector(0,-100,0));
    shapes::sphere sphere2 = shapes::sphere(Vector(250,200,25));
    std::vector<shapes::sphere> spheres;


//    spheres.push_back(1);


private:
    void UpdateText() {
        text = "red:=" + std::to_string(r) + " green:=" + std::to_string(g) + " blue:=" + std::to_string(b);
    }
//    Vector Light= Vector(150,150,-250);
    void UpdateTexture() {
        const int w = width/2, h = height/2;

        float spherex= 0;
        if (ImGui::SliderFloat("sphere x", &sphere.cs.x, -height, height));
        if (ImGui::SliderFloat("sphere y", &sphere.cs.y, -height, height));
        if (ImGui::SliderFloat("sphere z", &sphere.cs.z, -height, height));
        if (ImGui::SliderFloat("light x", &sphere.Light.x, -width, width));
        if (ImGui::SliderFloat("light y", &sphere.Light.y, -height, height));
        if (ImGui::SliderFloat("light z", &sphere.Light.z, -height, height));


        unsigned char* pixelData = new unsigned char [width * height * 4];

//        unsigned char* pixelData2 = new unsigned char [width * height * 4];
//        unsigned char* pixelData3 = pixelData + pixelData2;
//        unsigned char B = (unsigned char)255 * b, R = (unsigned char)255 * r, G = (unsigned char)255 * g;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int index = y * width * 4 + x * 4;
                // Line Origin
                sphere.setOrigin(Vector(x - w, y - h, 0));
                sphere.v = sphere.o - sphere.cs;
                sphere.calculations();
                pixelData[index] = sphere.intensity * sphere.red;           // R
                pixelData[index + 1] = sphere.intensity * sphere.green;       // G
                pixelData[index + 2] = sphere.intensity * sphere.blue;       // B
                pixelData[index + 3] = 255;     // A
//                std::cout << pixelData[index] << "\n";

            }
        }
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,pixelData);
        glBindTexture(GL_TEXTURE_2D, 0);
        ImGui::Image(reinterpret_cast<void *>(texture), imagesize);
    }
};
#endif //UNTITLED2_GUI_H