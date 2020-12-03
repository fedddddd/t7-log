#pragma once

#pragma warning(disable: 4244)
#pragma warning(disable: 26812)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <vector>
#include <cassert>
#include <mutex>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <fstream>
#include <filesystem>

#include <MinHook.h>

using namespace std::literals;

#include "utils/memory.hpp"
#include "utils/string.hpp"
#include "utils/hook.hpp"

#include "game/structs.hpp"
#include "game/game.hpp"
