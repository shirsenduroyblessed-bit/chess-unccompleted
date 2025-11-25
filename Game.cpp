#include "Game.hpp"

Game::Game() : window(nullptr), renderer(nullptr), running(false), side_text1(nullptr), side_text2(nullptr), font1(nullptr), font2(nullptr), cursor(nullptr), cursor_away(true)
{
    Text_Rect1 = {960 + 20 + 30, 120 + 30, 125, 40};
    Text_Rect2 = {960 + 20 + 100 + 30, 120 + 30, 66, 40};
    // Text_Rect3 = {960 + 20 + 30, 180 + 30, 66, 50};
    // hintRct = {960 + 20 + 66 + 30, 180 + 30, 66, 50};
} //----------1

bool Game::isInitOkey(const char *TITLE, int WIDTH, int HEIGHT)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) //------2.1
    {
        std::cerr << "SDL Init Error at " << __LINE__ << ": " << SDL_GetError() << std::endl;
        return true;
    }

    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) //-----2.2
    {
        std::cerr << "CreateWindow Error at " << __LINE__ << ": " << SDL_GetError() << std::endl;
        return true;
    }

    if ((IMG_Init(IMG_Flag) & IMG_Flag) != IMG_Flag)
    {
        std::cerr << "Img Load Error! at " << __LINE__ << ": " << IMG_GetError() << std::endl;
        return true;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //---------2.3
    if (!renderer)
    {
        std::cerr << "CreateRenderer Error at " << __LINE__ << ": " << SDL_GetError() << std::endl;
        return true;
    }

    if (TTF_Init())
    {
        std::cerr << "TTF Error at " << __LINE__ << ": " << TTF_GetError() << std::endl;
        return true;
    }

    if ((Mix_Init(MIXER_FLAGS) & MIXER_FLAGS) != MIXER_FLAGS)
    {
        std::cerr << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
        return true;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048)) // AUDIO MIX INIT
    {
        std::cerr << "Error Opening Audio: " << Mix_GetError() << std::endl;
        return true;
    }

    if (!(cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND)))
        return true;

    SDL_SetCursor(cursor);

    takeOffSound = Mix_LoadMUS("Sound/takeOff.mp3");
    checkSound = Mix_LoadMUS("Sound/check.mp3");
    MoveSound = Mix_LoadMUS("Sound/moveSound.mp3");
    clickSound = Mix_LoadMUS("Sound/click.mp3");

    if (!takeOffSound || !checkSound || !MoveSound || !clickSound)
    {
        std::cerr << "Error loading Music: " << Mix_GetError() << '\n';
        return true;
    }

    necessaryFunction();

    BoardClass = new Board(renderer, MoveSound, checkSound, takeOffSound); //----------2.4
    list = new AdvancedTable(520, 650, 995 + 30, 280 + 30, window, renderer);
    if (list->init())
        return true;

    running = true; //--------2.5

    // SDL_StartTextInput();

    return false;
}

void Game::handleOut(int MouseX, int MouseY)
{
    if (MouseX >= Text_Rect1.x && MouseX <= Text_Rect1.x + Text_Rect1.w && MouseY >= Text_Rect1.y && MouseY <= Text_Rect1.y + Text_Rect1.h)
    {
        Mix_PlayMusic(clickSound, 0);
        SDL_Delay(300);
        running = !running;
    }
    else if (MouseX >= Text_Rect2.x && MouseX <= Text_Rect2.x + Text_Rect2.w && MouseY >= Text_Rect2.y && MouseY <= Text_Rect2.y + Text_Rect2.h)
    {
        Mix_PlayMusic(clickSound, 0);
        SDL_Delay(300);
        BoardClass->setupBoard(); // reset all board again
        list->clearItems();
    } /*
     else if ((MouseX >= Text_Rect3.x && MouseX <= Text_Rect3.x + Text_Rect3.w && MouseY >= Text_Rect3.y && MouseY <= Text_Rect3.y + Text_Rect3.h) || (MouseX >= hintRct.x && MouseX <= hintRct.x + hintRct.w && MouseY >= hintRct.y && MouseY <= hintRct.y + hintRct.h))
     {
         Mix_PlayMusic(clickSound, 0);
         SDL_Delay(300);
     }*/
}

void Game::handleEvents() //-------------4.1
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) //----------------4.w
    {
        if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE || ((event.key.keysym.mod & (KMOD_CTRL)) && ((event.key.keysym.scancode == SDL_SCANCODE_W) || (event.key.keysym.scancode == SDL_SCANCODE_D))))
        {
            running = !running;
            break;
        }

        if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
        {
            Mix_PlayMusic(clickSound, 0);
            SDL_Delay(300);
            BoardClass->setupBoard(); // reset all board again
            list->clearItems();

            std::cout << "Key pressed: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_GetMouseState(&x, &y); //----------------4.3
            // x = event.wheel.x;  it don't sent the specific position
            // y = event.wheel.y;

            int row = y / BoardClass->TileSize;
            int col = x / BoardClass->TileSize;
            if (row <= 8 && col <= 8)
                BoardClass->handleClick(x, y); //----------------4.4
            else if (col > 8)
                handleOut(x, y);
        }

        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_UP)
                list->smoothScrollTo(list->targetScroll - list->itemHeight * 2);
            else if (event.key.keysym.sym == SDLK_DOWN)
                list->smoothScrollTo(list->targetScroll + list->itemHeight * 2);
            else if (event.key.keysym.sym == SDLK_HOME)
                list->smoothScrollTo(0);
            else if (event.key.keysym.sym == SDLK_END)
                list->smoothScrollTo(list->maxScroll);
            break;

        case SDL_MOUSEWHEEL:
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            if (mouseX >= list->listArea.x && mouseX <= list->listArea.x + list->listArea.w && mouseY >= list->listArea.y && mouseY <= list->listArea.y + list->listArea.h)
                // Smooth scroll instead of instant
                list->smoothScrollTo(list->targetScroll - event.wheel.y * 60);
            break;
        }

        case SDL_MOUSEMOTION:
        {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;

            {
                if (mouseX > 990 && cursor_away)
                {
                    SDL_FreeCursor(cursor);
                    if (!(cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW)))
                    {
                        running = false;
                        break;
                    }
                    SDL_SetCursor(cursor);
                    cursor_away = !cursor_away;
                }
                else if (mouseX <= 990 && !cursor_away)
                {
                    SDL_FreeCursor(cursor);
                    if (!(cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND)))
                    {
                        running = false;
                        break;
                    }
                    SDL_SetCursor(cursor);
                    cursor_away = !cursor_away;
                }
            }

            // Update button hover states
            for (auto &btn : list->buttons)
                btn.isHovered = btn.contains(mouseX, mouseY);

            // Update item hover
            list->hoveredIndex = list->getItemIndexAtPosition(mouseX, mouseY);
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            // Check buttons
            for (auto &btn : list->buttons)
                if (btn.contains(mouseX, mouseY) && btn.onClick)
                    btn.onClick();

            // Check items
            int idx = list->getItemIndexAtPosition(mouseX, mouseY);
            if (idx >= 0 && idx < static_cast<int>(list->items.size()))
            {
                list->selectedIndex = idx;
                std::cout << "✅ Selected: " << list->items[idx]->text << std::endl;

                if (list->items[idx]->onClick)
                {
                    printf("HI\n");
                    list->items[idx]->onClick();
                }
            }
            else
            {
                list->selectedIndex = -1;
            }
            break;
        }
        }
    }
}

void Game::update() //----------------5.1
{
    {
        if (BoardClass->ismoved)
        {
            if (!BoardClass->Events.empty())
            {
                if (BoardClass->White_s_Turn)
                    list->addItem(BoardClass->Events.back()->given_str(), Colors::LIGHT_GRAY, Colors::BLACK);
                else
                    list->addItem(BoardClass->Events.back()->given_str(), Colors::DARK_GRAY1, Colors::BLACK);

                list->make_remainnull();
                BoardClass->ismoved = false;
                if (!BoardClass->Events_redone.empty())
                {
                    for (auto &i : BoardClass->Events_redone)
                        delete i;
                    BoardClass->Events_redone.clear();
                }
                // printf("\033[34mOKey!\033[37m\n");
            }
        }

        // update

        if (list->undo_is_true)
        {
            list->undo_is_true = false;

            if (!BoardClass->Events.empty())
            {
                BoardClass->Events_redone.emplace_back(BoardClass->Events.back());
                BoardClass->Events.pop_back();
                BoardClass->undo_have_clicked = true;
            }
        }

        else if (list->redo_is_true)
        {
            list->redo_is_true = false;

            if (!BoardClass->Events_redone.empty())
            {
                BoardClass->Events.emplace_back(BoardClass->Events_redone.back());
                BoardClass->Events_redone.pop_back();
                BoardClass->redo_have_clicked = true;
            }
        }
        else
        {
        }

        if (BoardClass->redo_undo_update())
        {
            BoardClass->White_s_Turn = !BoardClass->White_s_Turn;
            Mix_PlayMusic(takeOffSound, 0);
        }
    }

    BoardClass->KingsUpdate();
    BoardClass->draw(); //-----------------6.2
    buttonUpdate();
    scrollingBoxUpdate();

    if (BoardClass->White_king_SurroundingDangerousGrid[1][1])
        BoardClass->DrawSquereRing(BoardClass->White_King_positionAtRow, BoardClass->White_King_positionAtCol, 'r');
    if (BoardClass->Black_king_SurroundingDangerousGrid[1][1])
        BoardClass->DrawSquereRing(BoardClass->Black_King_positionAtRow, BoardClass->Black_King_positionAtCol, 'r');
}

void Game::buttonUpdate()
{
    BoardClass->rectangleSides(Text_Rect1);
    BoardClass->rectangleSides(Text_Rect2); // default white
    // BoardClass->rectangleSides(Text_Rect3);

    SDL_RenderCopy(renderer, side_text1, nullptr, &Text_Rect1);
    SDL_RenderCopy(renderer, side_text2, nullptr, &Text_Rect2);
    // SDL_RenderCopy(renderer, side_text3, nullptr, &Text_Rect3);
    // SDL_RenderCopy(renderer, hint, nullptr, &hintRct);
}

void Game::render() //-------------6.1
{
    list->render();
    SDL_RenderPresent(renderer); //-------------------6.3
}

void Game::clean()
{
    if (BoardClass)
        delete BoardClass;
    if (list)
        delete list;
    Mix_HaltChannel(-1);

    if (cursor)
        SDL_FreeCursor(cursor);

    if (takeOffSound)
        Mix_FreeMusic(takeOffSound);
    if (checkSound)
        Mix_FreeMusic(checkSound);
    if (MoveSound)
        Mix_FreeMusic(MoveSound);
    if (clickSound)
        Mix_FreeMusic(clickSound);
    Mix_CloseAudio();

    if (side_text1)
        SDL_DestroyTexture(side_text1);
    if (side_text2)
        SDL_DestroyTexture(side_text2);
    // if (side_text3)
    // SDL_DestroyTexture(side_text3);
    // if (hint)
    // SDL_DestroyTexture(hint);

    if (font1)
        TTF_CloseFont(font1);

    if (font2)
        TTF_CloseFont(font2);

    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (window)
        SDL_DestroyWindow(window);

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Game::isRunning() const //-------------------3.1
{
    return running;
}

void Game::rest_for_a_little() //------------------7
{
    SDL_Delay(16); // ~60 FPS
}

Game::~Game()
{
    Mix_PlayMusic(clickSound, 0);
    SDL_Delay(500);
    clean();
}

void Game::necessaryFunction()
{
    SDL_Color colour = {25, 34, 123, 255};
    font1 = TTF_OpenFont("Font/Bold.ttf", 40);
    font2 = TTF_OpenFont("Font/font.ttf", 25);
    SDL_Surface *temp = TTF_RenderText_Blended(font1, "Quit", colour);
    //*If You want to exit, type escape or cross icon\n *If you want to Reset all the game again, just type the \" \" (Space) button\n-->>ENJOY!\n", colour);

    Text_Rect1.h = 45;
    Text_Rect1.w = temp->w;
    // printf("\n%d\n", temp->w);
    side_text1 = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);

    temp = TTF_RenderText_Blended(font1, "NEW", colour);

    Text_Rect2.h = temp->h;
    Text_Rect2.w = temp->w;
    side_text2 = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);

    // temp = TTF_RenderText_Blended(font1, "HINT", colour);

    // Text_Rect3.h = temp->h;
    // Text_Rect3.w = temp->w;
    // side_text3 = SDL_CreateTextureFromSurface(renderer, temp);
    // SDL_FreeSurface(temp);

    // hint = IMG_LoadTexture(renderer, "Pieces/hint.png");
}

void Game::run()
{
    while (isRunning()) //-------------3
    {
        handleEvents();      //------------4
        update();            // ----------5.0
        render();            //------------6
        rest_for_a_little(); //------------7
    }
}

void Game::scrollingBoxUpdate()
{
    list->update();
}
