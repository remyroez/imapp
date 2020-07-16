// dear imgui app: OpenGL Loader

#pragma once
#include "imgui_app.h"      // IMGUI_APP_API

#if defined(IMGUI_APP_SYSTEM_EMSCRIPTEN)
// OpenGL ES 2
#if defined(IMGUI_APP_PLATFORM_SDL2)
#include <SDL_opengles2.h>
#elif defined(IMGUI_APP_PLATFORM_GLFW)
// GLFW for emscripten
#endif

#elif defined(IMGUI_APP_RENDERER_OPENGL3)
// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h>  // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>// Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#elif defined(IMGUI_APP_RENDERER_OPENGL2)
// OpenGL 2 header from platform headers
#if defined(IMGUI_APP_PLATFORM_SDL2)
#include <SDL_opengl.h>
#elif defined(IMGUI_APP_PLATFORM_GLFW)
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>
#endif
#endif

// Decide GL+GLSL versions
#ifndef IMGUI_APP_GLSL_VERSION
#ifdef __EMSCRIPTEN__
// For the browser using Emscripten, we are going to use WebGL1 with GL ES2. See the Makefile. for requirement details.
// It is very likely the generated file won't work in many browsers. Firefox is the only sure bet, but I have successfully
// run this code on Chrome for Android for example.
#define IMGUI_APP_GLSL_VERSION "#version 100"
//#define IMGUI_APP_GLSL_VERSION "#version 300 es"
#define IMGUI_APP_GL_CONTEXT_MAJOR_VERSION 2
#define IMGUI_APP_GL_CONTEXT_MINOR_VERSION 0
#elif defined(IMGUI_APP_RENDERER_OPENGL2)
// GL 2.*
#define IMGUI_APP_GLSL_VERSION "#version 100" // not use
#define IMGUI_APP_GL_CONTEXT_MAJOR_VERSION 2
#define IMGUI_APP_GL_CONTEXT_MINOR_VERSION 2
#elif __APPLE__
// GL 3.2 + GLSL 150
#define IMGUI_APP_GLSL_VERSION "#version 150"
#define IMGUI_APP_GL_CONTEXT_MAJOR_VERSION 3
#define IMGUI_APP_GL_CONTEXT_MINOR_VERSION 2
#else
// GL 3.0 + GLSL 130
#define IMGUI_APP_GLSL_VERSION "#version 130"
#define IMGUI_APP_GL_CONTEXT_MAJOR_VERSION 3
#define IMGUI_APP_GL_CONTEXT_MINOR_VERSION 0
#endif
#endif

namespace ImGuiApp
{

IMGUI_APP_API bool InitOpenGLLoader();

}
