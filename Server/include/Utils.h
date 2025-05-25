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

template <typename T> using Unique = std::unique_ptr<T>;
template <typename T> using Shared = std::shared_ptr<T>;
template <typename T> using Weak = std::weak_ptr<T>;

inline uint32_t GetId() {
    static uint32_t clientIdCounter = 0;
    return ++clientIdCounter;
}


inline int RandomRangeInt(int min, int max) {
    static std::random_device rd;    
    static std::mt19937 gen(rd());   // Mersenne Twister RNG
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}