#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <memory>
#include <functional>
#include <fstream>

#define MIXER_FLAGS MIX_INIT_MP3
#define IMG_Flag IMG_INIT_PNG

enum TURN
{
    WHITEs_TURN,
    BLACKs_TURN
};

namespace Colors
{
    const SDL_Color WHITE = {255, 255, 255, 255};
    const SDL_Color BLACK = {0, 0, 0, 255};
    const SDL_Color BLUE = {41, 128, 185, 255};
    const SDL_Color LIGHT_BLUE = {52, 152, 219, 255};
    const SDL_Color LIGHT_GRAY = {200, 200, 200, 255};
    const SDL_Color GREEN = {46, 204, 113, 255};
    const SDL_Color GREEN1 = {50, 170, 70, 255};
    const SDL_Color RED = {231, 76, 60, 255};
    const SDL_Color RED1 = {200, 60, 30, 0xff};
    const SDL_Color DARK_GRAY = {64, 64, 64, 255};
    const SDL_Color DARK_GRAY1 = {99, 99, 99, 0xff};
    const SDL_Color neoRed = {255, 165, 0, 1};
    const SDL_Color neogreen = {57, 255, 20, 1};
    const SDL_Color neoBlue = {0, 191, 255, 1};
}

enum PIECES
{
    WK,
    WP,
    WN,
    WQ,
    WR,
    WB,
    BK,
    BP,
    BN,
    BQ,
    BR,
    BB,
    EM = -1
};
