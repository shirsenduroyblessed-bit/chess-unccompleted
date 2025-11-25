#include "Board.hpp"

class WindoW
{
private:
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Cursor *cursor;
    Mix_Music *clk;

    std::vector<Button *> buttons;
    SDL_Texture *img;
    int w, h;
    bool is_new, is_exit, running, clicked, is_continue;

public:
    int *ptr;
    WindoW(int w, int h, bool isnew, int *ptr) : running(true), clk(nullptr), window(nullptr), render(nullptr), cursor(nullptr)
    {
        this->w = w;
        this->h = h;
        is_new = isnew;
        is_continue = false;
        is_exit = false;
        clicked = false;
        this->ptr = ptr;
    }
    ~WindoW()
    {
        for (auto &i : buttons)
            delete i;

        TTF_Quit();
        Mix_HaltChannel(-1);

        if (clk)
            Mix_FreeMusic(clk);
        Mix_CloseAudio();
        if (img)
            SDL_DestroyTexture(img);

        if (cursor)
            SDL_FreeCursor(cursor);

        if (render)
            SDL_DestroyRenderer(render);

        if (window)
            SDL_DestroyWindow(window);

        IMG_Quit();
        SDL_Quit();
    }

    bool init();
    void handleEvent();
    void run();
    void rener();
};
