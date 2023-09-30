//#define GL_SILENCE_DEPRECATION
//#define STB_IMAGE_IMPLEMENTATION
//#define GL_GLEXT_PROTOTYPES 1
//#define LOG(argument) std::cout << argument << '\n'
//
//#ifdef _WINDOWS
//#include <GL/glew.h>
//#endif
//
//#include <SDL.h>
//#include <SDL_opengl.h>
//#include "glm/mat4x4.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "ShaderProgram.h"
//#include "stb_image.h"
//
//enum Coordinate
//{
//    x_coordinate,
//    y_coordinate
//};
//
//const char V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
//           F_SHADER_PATH[] = "shaders/fragment_textured.glsl";
//
//const int WINDOW_WIDTH  = 640,
//          WINDOW_HEIGHT = 480;
//
//const float BG_RED     = 0.1922f,
//            BG_BLUE    = 0.549f,
//            BG_GREEN   = 0.9059f,
//            BG_OPACITY = 1.0f;
//
//const int VIEWPORT_X      = 0,
//          VIEWPORT_Y      = 0,
//          VIEWPORT_WIDTH  = WINDOW_WIDTH,
//          VIEWPORT_HEIGHT = WINDOW_HEIGHT;
//
//const int TRIANGLE_RED     = 1.0,
//          TRIANGLE_BLUE    = 0.4,
//          TRIANGLE_GREEN   = 0.4,
//          TRIANGLE_OPACITY = 1.0;
//
//const int MAX_FRAME       = 40;
//
//const float ROT_ANGLE  = glm::radians(1.5f);
//const float TRAN_VALUE = 0.025f;
//
//SDL_Window* g_display_window;
//
//bool g_game_is_running = true;
//bool g_is_growing      = true;
//int  g_frame_counter   = 0;
//
//ShaderProgram g_shader_program;
//glm::mat4 g_view_matrix,
//          g_model_matrix,
//          g_projection_matrix,
//          g_tran_matrix;
//
//
//GLuint kirby_player_texture_id;
//
//const int NUMBER_OF_TEXTURES = 1; // to be generated, that is
//const GLint LEVEL_OF_DETAIL = 0;  // base image level; Level n is the nth mipmap reduction image
//const GLint TEXTURE_BORDER = 0;   // this value MUST be zero
//
//
//const char KIRBY_SPRITE_FILEPATH[] = "/Users/matthewgong/School/Fall23/Intro-To-Game-Prog/SDLSimple/SDLSimple/resources/Kirby.png";
//
//
//GLuint load_texture(const char* filepath)
//{
//    // STEP 1: Loading the image file
//    int width, height, number_of_components;
//    unsigned char* image = stbi_load(filepath, &width, &height, &number_of_components, STBI_rgb_alpha);
//    
//    if (image == NULL)
//    {
//        LOG("Unable to load image. Make sure the path is correct.");
//        LOG(filepath);
//        assert(false);
//    }
//    
//    // STEP 2: Generating and binding a texture ID to our image
//    GLuint textureID;
//    glGenTextures(NUMBER_OF_TEXTURES, &textureID);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//    glTexImage2D(GL_TEXTURE_2D, LEVEL_OF_DETAIL, GL_RGBA, width, height, TEXTURE_BORDER, GL_RGBA, GL_UNSIGNED_BYTE, image);
//    
//    // STEP 3: Setting our texture filter parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    
//    // STEP 4: Releasing our file from memory and returning our texture id
//    stbi_image_free(image);
//    
//    return textureID;
//}
//
//void draw_object(glm::mat4 &object_model_matrix, GLuint &object_texture_id)
//{
//    g_shader_program.SetModelMatrix(object_model_matrix);
//    glBindTexture(GL_TEXTURE_2D, object_texture_id);
//    glDrawArrays(GL_TRIANGLES, 0, 6); // we are now drawing 2 triangles, so we use 6 instead of 3
//}
//
//void initialise()
//{
//    SDL_Init(SDL_INIT_VIDEO);
//    g_display_window = SDL_CreateWindow("Homework 1",
//                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//                                      WINDOW_WIDTH, WINDOW_HEIGHT,
//                                      SDL_WINDOW_OPENGL);
//    
//    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
//    SDL_GL_MakeCurrent(g_display_window, context);
//    
//#ifdef _WINDOWS
//    glewInit();
//#endif
//    
//    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
//    
//    g_shader_program.Load(V_SHADER_PATH, F_SHADER_PATH);
//    
//    g_model_matrix = glm::mat4(1.0f);
//    
////    m_model_matrix = glm::mat4(1.0f);
////    view_matrix = glm::mat4(1.0f);
////    m_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f); .
//
//
//    g_view_matrix = glm::mat4(1.0f);  // Defines the position (location and orientation) of the camera
//    g_model_matrix = glm::mat4(1.0f);  // Defines every translation, rotations, or scaling applied to an object
//    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);  // Defines the characteristics of your camera, such as clip planes, field of view, projection method etc.
//    g_tran_matrix = g_model_matrix;
//    
//    g_shader_program.SetProjectionMatrix(g_projection_matrix);
//    g_shader_program.SetViewMatrix(g_view_matrix);
//    
//    
//    glUseProgram(g_shader_program.programID);
//    
//    
//    g_shader_program.SetColor(TRIANGLE_RED, TRIANGLE_BLUE, TRIANGLE_GREEN, TRIANGLE_OPACITY);
//
//    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);
//    
//    kirby_player_texture_id = load_texture(KIRBY_SPRITE_FILEPATH);
//
//    
//    // enable blending
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//}
//
//void process_input()
//{
//    SDL_Event event;
//    while (SDL_PollEvent(&event))
//    {
//        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
//        {
//            g_game_is_running = false;
//        }
//    }
//}
//
//void update()
//{
//    g_model_matrix = glm::mat4(1.0f);
////    LOG(++frame_counter);
//    g_frame_counter++;
////    g_model_matrix = glm::translate(g_model_matrix, glm::vec3(0.0f, 0.0f, 0.0f));
//
//
//}
//
//
//void render() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    
//// Vertices
//    float kirby_vertices[] = {
//        -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f,  // triangle 1
//        -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f   // triangle 2
//    };
//
//    // Textures
//    float kirby_texture_coordinates[] = {
//        0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,     // triangle 1
//        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,     // triangle 2
//    };
//    
//    
//    glVertexAttribPointer(g_shader_program.positionAttribute, 2, GL_FLOAT, false, 0, kirby_vertices);
//    glEnableVertexAttribArray(g_shader_program.positionAttribute);
//    
//    glVertexAttribPointer(g_shader_program.texCoordAttribute, 2, GL_FLOAT, false, 0, kirby_texture_coordinates);
//    glEnableVertexAttribArray(g_shader_program.texCoordAttribute);
//    
//    // Bind texture
//    draw_object(g_model_matrix, kirby_player_texture_id);
//    
//    // We disable two attribute arrays now
//    glDisableVertexAttribArray(g_shader_program.positionAttribute);
//    glDisableVertexAttribArray(g_shader_program.texCoordAttribute);
//    
//    
//    SDL_GL_SwapWindow(g_display_window);
//}
//
//void shutdown() { SDL_Quit(); }
//
///**
// Start here—we can see the general structure of a game loop without worrying too much about the details yet.
// */
//int main(int argc, char* argv[])
//{
//    initialise();
//    
//    while (g_game_is_running)
//    {
//        process_input();
//        update();
//        render();
//    }
//    
//    shutdown();
//    return 0;
//}
//
