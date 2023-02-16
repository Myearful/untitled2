#include <iostream>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_opengl3_loader.h"
#include <cmath>
//#include "glad.h"
#include "GLFW/glfw3.h"
#include "gui_src/gui.h"
void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow *window);



int main() {

//
//    glfwInit();
//    // SETS OpenGl version
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // creates window
//    GLFWwindow* window = glfwCreateWindow(800,600, "LearnOpenGl", NULL,NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to init glfw \n";
//        glfwTerminate();
//        return -1;
//    }
//    // sets current window as one to draw to
//    glfwMakeContextCurrent(window);
//    // dunno
//    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
//    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
//    {
//        std::cout <<" Failed to initialise GLAD \n";
//        return -1;
//    }
//    // 0,0 sets location of lower left corner of the window, 800,600 set the size of rendering pixels
//    glViewport(0,0,800,600);
//    // sets callback for when you resize window
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    while (!glfwWindowShouldClose(window))
//    {
//        // close window if ESCAPE key is pressed
//        processInput(window);
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    glfwTerminate();
//    return 0;
//unsigned int texture;
//glGenTextures(1, &texture);

    if (!glfwInit())
        return -1;
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Test Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool show_demo_window = true;
    bool show_another_window = false;

    while (!glfwWindowShouldClose(window))
    {
//        using namespace ImGui;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (false)
        {
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            {
                counter++;
            }
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        {
            static gui myGui;
            static float red,green, blue;
            ImGui::Begin("Test2", NULL, ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::PushItemWidth(200) ;
            if (ImGui::SliderFloat("green", &green, 0.f, 1.f))
            {
                myGui.SetGreen(green);
            }
            if (ImGui::SliderFloat("red", &red, 0.f, 1.f))
            {
                myGui.SetRed(red);
            }
            if (ImGui::SliderFloat("blue", &blue, 0.f, 1.f))
            {
                myGui.SetBlue(blue);
            }
//            ImGui::Separator();
            ImGui::TextWrapped("Debug Window");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(127, 127, 127, 100));
            ImGui::BeginChild("Debug_win", ImVec2(400,200), true, ImGuiWindowFlags_None);
            ImGui::TextWrapped(myGui.GetText().c_str());
            ImGui::EndChild();

            ImGui::Separator();
            ImVec2 uv_min = ImVec2(0.f, 0.f);
            ImVec2 uv_max = ImVec2(1.f, 1.f);
            ImVec4 tint_col = ImVec4(1.f, 1.f, 1.f, 1.f);
            ImVec4 border_col = ImVec4(1.f, 1.f, 1.f, .5f);

            ImVec2 imagesize(256, 256);

            if (false)   {
            GLuint testTexture;
            unsigned char bluepixel[4] = {0,0,255,255};
            glGenTextures(1, &testTexture);
            glBindTexture(GL_TEXTURE_2D, testTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, bluepixel);
            glBindTexture(GL_TEXTURE_2D, 0);
//            ImVec2 imagesize(256,256);
            ImGui::Image(reinterpret_cast<void*>(testTexture), imagesize);
            }
            if (false) {
                glGenTextures(1, &myGui.texture);
                glBindTexture(GL_TEXTURE_2D, myGui.texture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,myGui.bluepixel);
                glBindTexture(GL_TEXTURE_2D, 0);
                ImGui::Image(reinterpret_cast<void *>(myGui.texture), imagesize);
            }
            if (true)
            {
//                myGui.bluePixel();
//                myGui.bluePixel();
//                ImGui::Image(reinterpret_cast<void *>(myGui.texture), imagesize);
                myGui.Update();

            }
//            glDeleteTextures(1, &testTexture);
            ImGui::PopItemWidth();
            ImGui::PopStyleColor();
            ImGui::End();
        }

        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        ImGui::Render();
        int display_width, display_height;
        glfwGetFramebufferSize(window, &display_width, &display_height);
        glViewport(0,0,display_width,display_height);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}

// calls glfw and gives argument when resizing window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width, height);
}
// closes window if ESCAPE key is pressed
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}