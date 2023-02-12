#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>
#include "shader.h"
#include "font_renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
   glViewport(0, 0, width, height);
}
int main(int argv, char** argc) {
   if(!glfwInit()) return 1;
   GLFWwindow* window = glfwCreateWindow(900, 600, "Text Editor", NULL, NULL);

   if(!window) return 1;

   glfwMakeContextCurrent(window);

   if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return 1;



   shader_program* font_shader = shader_program_create("../assets/shaders/default_vertex.glsl", "../assets/shaders/default_fragment.glsl");

   font_struct font = font_renderer_init_font("../assets/fonts/font.png");

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   while(!glfwWindowShouldClose(window)) {
      glfwPollEvents();
      glfwSwapBuffers(window);

      glClear(GL_COLOR_BUFFER_BIT);
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      
      font_renderer_render_string(20.0f, 400.0f, 100.0f, (vector4){1.0f, 1.0f, 1.0f, 1.0f}, "Hello World", font, font_shader);
   }

   font_renderer_delete_font(&font);
   glfwTerminate();
   glfwDestroyWindow(window);
}
