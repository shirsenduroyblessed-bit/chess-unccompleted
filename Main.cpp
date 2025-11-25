#include "Game.hpp"

const char *TITLE = "SYMMETRICAL_IRON_CHESS_BOARD";
const int WIDTH = 1560 + 30;
const int HEIGHT = 960 + 30;

int main(int argc, char **argv)
{
    Game *game = nullptr;
    int x = -1;
    WindoW *win = nullptr;
    // std::vector<void *> set;
    /*if (game->isInitOkey(TITLE, WIDTH, HEIGHT)) //-----2
    {
        delete game; //------III (if something wrong)
        // destructor will automatically delete the game object at heap
        return -1;
    }*/

    while (x == -1)
    {
        win = new WindoW(800, 500, false, &x);
        if(win->init())
        {
            delete win;
            return -1;
        }
        win->run();
        delete win;
        win = nullptr;

        if (x == 2)
            break;

        game = new Game;
        if (game->isInitOkey(TITLE, WIDTH, HEIGHT)) //-----2
        {
            delete game; //------III (if something wrong)
            // destructor will automatically delete the game object at heap
            return -1;
        }
        game->run();
        delete game; //---------------8
        x = -1;
    }

    system("clear");
    std::cout << "\033[31mBYE!\033[37m" << std::endl;

    return 0; //-----------------9
}
