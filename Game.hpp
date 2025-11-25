#include "player.hpp"

#ifndef GAME_HPP
#define GAME_HPP

class Game
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Cursor *cursor;

    SDL_Texture *side_text1, *side_text2;
    TTF_Font *font1, *font2;
    SDL_Rect Text_Rect1, Text_Rect2, Text_Rect4;
    Mix_Music *MoveSound, *checkSound, *takeOffSound, *clickSound;

    bool running, cursor_away;
    int x, y;

    // std::vector<Button> buttons;
    Board *BoardClass;
    AdvancedTable *list;
    WindoW *show;
    // std::vector<event> events;

public:
    Game();
    ~Game();

    bool isInitOkey(const char *, int, int);
    bool isRunning() const;

    void handleOut(int, int);
    void handleEvents();
    void update();
    void buttonUpdate();
    void render();
    void clean();
    void rest_for_a_little();
    void necessaryFunction();
    void scrollingBoxUpdate();
    void run();

    // friend class player;
};

#endif
