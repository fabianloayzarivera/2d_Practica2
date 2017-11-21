#pragma once
#include "stb_image.h"
#include <string>
#include <iostream>
#include <litegfx.h>

using namespace std;

ltex_t* createTexture(const char* filename, int width, int height);
