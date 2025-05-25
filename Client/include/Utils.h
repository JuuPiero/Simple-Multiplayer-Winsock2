#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

// #include <glm/glm.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

// #include <spdlog/spdlog.h>

#include <cstdlib>
#include <stdlib.h>
#include <WinSock2.h>
#include <Windows.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <iostream>
#include <time.h>
#include <thread>
#include <algorithm>
#include <functional>
#include <ctime>
#include <iomanip>
#include <random>
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 380

#define MAX_CLIENTS 1024
#define DEFAULT_BUFLEN 2048
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Math/Vector2.h"
#define PrintLn(mess) std::cout << mess << std::endl

inline std::string GetFileContents(const char* filePath) {
    std::ifstream ifs(filePath);
    std::string content( (std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()) );
    return content;
}

inline void HSVtoRGB(float h, float s, float v, int* r, int* g, int* b) {
    float c = v * s;
    float x = c * (1 - fabs(fmod(h / 60.0f, 2) - 1));
    float m = v - c;
    float r1, g1, b1;

    if (h < 60)       { r1 = c; g1 = x; b1 = 0; }
    else if (h < 120) { r1 = x; g1 = c; b1 = 0; }
    else if (h < 180) { r1 = 0; g1 = c; b1 = x; }
    else if (h < 240) { r1 = 0; g1 = x; b1 = c; }
    else if (h < 300) { r1 = x; g1 = 0; b1 = c; }
    else              { r1 = c; g1 = 0; b1 = x; }

    *r = ((r1 + m) * 255);
    *g = ((g1 + m) * 255);
    *b = ((b1 + m) * 255);
}

inline void getDistinctColorFromInt(int a, int* r, int* g, int* b) {
    // Sử dụng hue khác nhau dựa trên số nguyên
    float hue = fmodf((a * 137) % 360, 360); // 137 là số nguyên tố giúp phân tán tốt
    HSVtoRGB(hue, 0.8f, 0.95f, r, g, b);
}

template <typename T> using Unique = std::unique_ptr<T>;
template <typename T> using Shared = std::shared_ptr<T>;
template <typename T> using Weak = std::weak_ptr<T>;
