#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include <spdlog/spdlog.h>

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
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
// #include <nlohmann/json.hpp>
// using json = nlohmann::json;
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

// inline Vector2 WindowSize() {

// }