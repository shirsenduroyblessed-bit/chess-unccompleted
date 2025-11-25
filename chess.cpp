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
    const SDL_Color RED = {231, 76, 60, 255};
    const SDL_Color DARK_GRAY = {64, 64, 64, 255};
}

struct record
{
    int px, py, nx, ny;
    std::string nm, tr;

    record(int i, int j, int k, int l, std::string str1, std::string str2) : px(i), py(j), nx(k), ny(l), nm(str1), tr(str2) {}

    ~record() { std::cout << "Deleted!" << std::endl; }
};

struct event
{
    std::vector<record> this_event;
    std::string event_what;
    ~event()
    {
        if (!this_event.empty())
            this_event.clear();
    }
};

struct ListItem
{
    std::string text;
    SDL_Color bgColor;
    SDL_Color textColor;
    std::function<void()> onClick;

    ListItem(const std::string &t, SDL_Color bg = Colors::WHITE, SDL_Color tc = Colors::BLACK) : text(t), bgColor(bg), textColor(tc), onClick(nullptr) {}
};

struct Button
{
    SDL_Rect rect;
    std::string text;
    SDL_Color normalColor;
    SDL_Color hoverColor;
    std::function<void()> onClick;
    bool isHovered;

    Button(int x, int y, int w, int h, const std::string &t,
           SDL_Color normal, SDL_Color hover, std::function<void()> callback)
        : rect{x, y, w, h}, text(t), normalColor(normal),
          hoverColor(hover), onClick(callback), isHovered(false)
    {
    }

    bool contains(int x, int y) const
    {
        return x >= rect.x && x <= rect.x + rect.w &&
               y >= rect.y && y <= rect.y + rect.h;
    }
};

class AdvancedTable
{
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font, *titleFont;
    // bool running;

    SDL_Rect listArea;

    std::vector<std::shared_ptr<ListItem>> items;
    std::vector<Button> buttons;

    std::string headerText;
    SDL_Rect headerRect;

    int itemHeight, hoveredIndex, selectedIndex;
    int counter;
    int windowWidth, windowHeight;
    int posix, posiy;
    int maxScroll;
    float targetScroll;
    float currentScroll;
    float scrollVelocity;
    AdvancedTable(int, int, int, int, SDL_Window *, SDL_Renderer *);
    ~AdvancedTable();

    bool init();
    void addItem(std::string, SDL_Color, SDL_Color);
    void removeLastItem();
    void clearItems();
    void addButton(int, int, int, int, const std::string &, SDL_Color, SDL_Color, std::function<void()>);
    void updateMaxScroll();
    void smoothScrollTo(float);
    void updateScrollPhysics();
    int getItemIndexAtPosition(int, int);
    void handleEvents();
    void update();
    void renderButton(const Button &);
    void renderList();
    void renderScrollbar();
    void renderHeader();
    void renderText(const std::string &, int, int, SDL_Color, TTF_Font *);
    void renderTextCentered(const std::string &, const SDL_Rect &, SDL_Color, TTF_Font *);
    void render();
    void run();
};
class Board
{
public:
    SDL_Renderer *renderer;
    SDL_Rect tile;
    bool White_s_Turn, IsWhiteKingHaveCastlingChance, IsBlackKingHaveCastlingChance, Casting_WK_with_UpRook, Casting_WK_with_DownRook, Casting_BK_with_UpRook, Casting_BK_with_DownRook;
    bool nowYouHave_wk_caslingWithUpWR, nowYouHave_wk_caslingWithDownWR, nowYouHave_bk_caslingWithUpBR, nowYouHave_bk_caslingWithDownBR;
    bool isAnycheckMate;
    bool isToken, doesCastlingOccured;
    std::vector<event> BoardEvents;
    bool ismoved;
    Mix_Music *MoveSound, *CheckSound, *TakeOffSound;

    std::vector<std::vector<bool>> Black_king_SurroundingDangerousGrid;
    std::vector<std::vector<bool>> White_king_SurroundingDangerousGrid;
    int Black_King_positionAtRow;
    int Black_King_positionAtCol;
    int White_King_positionAtRow;
    int White_King_positionAtCol;

    const int TileSize = 120;
    // each square is 120x120 px

    std::map<std::string, SDL_Texture *> pieceTextures;

    void loadPieceTextures(); // one time used
    bool pieceSelected;       // It's needed or result fall segment coredump
    int selectedRow = -1;     // new fourth
    int selectedCol = -1;     // new fourth
    std::vector<std::vector<std::string>> board;
    Board(SDL_Renderer *, Mix_Music *, Mix_Music *, Mix_Music *);
    ~Board();

    void setupBoard(); // one time used
    void draw();
    void handleClick(int, int); // new fourth for mouse controlling the
    void drawPieces();
    bool movePiece(int, int); // new 5th
    bool isWhite(int, int);
    bool isBlack(int, int);
    bool AnyPieaceAtPlusPath(int, int);
    bool AnyPieaceAtRoundPath(int, int);
    bool KnightPath(int, int);
    bool AnyPieaceAtCrossPath(int, int);
    bool QueenPath(int, int);
    bool function(int, int);
    bool ifCaslingPossible(char, bool *, bool *);
    bool CanBlackAttackThisGrid(int, int);
    bool CanWhiteAttackThisGrid(int, int);
    void ShowPosibilitiesGrid();
    void DrawSquereRing(int, int, char);
    void DrawKnightPath(int, int);
    void DrawRookPath(int, int);
    void DrawBishopPath(int, int);
    void DrawQueenPath(int, int);
    void DrawKingPath(int, int);
    void KingsUpdate();
    void rectangleSides(SDL_Rect &);
};

class Game
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture *side_text1, *side_text2, *side_text3, *hint;
    TTF_Font *font1, *font2;
    SDL_Rect Text_Rect1, Text_Rect2, Text_Rect3, Text_Rect4, hintRct;
    Mix_Music *MoveSound, *checkSound, *takeOffSound, *clickSound;
    bool running;
    int x, y;

    std::shared_ptr<Board> BoardClass;
    std::shared_ptr<AdvancedTable> list;

public:
    Game();
    ~Game();
    bool isInitOkey(const char *, int, int);
    void handleOut(int, int);
    void handleEvents();
    void update();
    void buttonUpdate();
    void render();
    void clean();
    bool isRunning() const;
    void rest_for_a_little();
    void necessaryFunction();
    void scrollingBoxUpdate();
    void run();
};

void Board::loadPieceTextures() //---------------2.4.2
{
    // std::string base = "Pieces/";
    std::string name[12] = {"wp", "wr", "wn", "wb", "wq", "wk", "bp", "br", "bn", "bb", "bq", "bk"};

    for (int i = 0; i < 12; i++)
    {
        std::string temp = "Pieces/", png = ".png";
        temp += (name[i] + png);
        pieceTextures[name[i]] = IMG_LoadTexture(renderer, temp.c_str()); //----------------------2.4.2.1
    }
}

Board::Board(SDL_Renderer *rend, Mix_Music *Sound, Mix_Music *sound1, Mix_Music *sound2) : renderer(rend), board(8, std::vector<std::string>(8)), CheckSound(sound1), TakeOffSound(sound2), MoveSound(Sound), Black_king_SurroundingDangerousGrid(3, std::vector<bool>(3)), White_king_SurroundingDangerousGrid(3, std::vector<bool>(3))
{
    loadPieceTextures(); //----------------2.4.2
    setupBoard();        //----------------2.4.3
}

bool Board::movePiece(int targetRow, int targetCol)
{
    if (selectedRow == targetRow && selectedCol == targetCol)
        return true;

    bool check = function(targetRow, targetCol); //-------------------4.4.3_II_2

    if (!check)
    {
        std::cout << "## Moved to : [" << targetRow << " , " << targetCol << "]" << std::endl; //-------------------4.4.3_II_3
        KingsUpdate();                                                                         // Update The King's Surrounding

        if (White_king_SurroundingDangerousGrid[1][1] || Black_king_SurroundingDangerousGrid[1][1])
            Mix_PlayMusic(CheckSound, 0);
        else if (isToken)
        {
            isToken = false;
            Mix_PlayMusic(TakeOffSound, 0);
        }
        else if (doesCastlingOccured)
        {
            doesCastlingOccured = false;
            Mix_PlayMusic(MoveSound, 2);
        }
        else
            Mix_PlayMusic(MoveSound, 0);
    }
    return check;
}

void Board::handleClick(int mouseX, int mouseY) //------------4.4.1
{
    int row = mouseY / TileSize;
    int col = mouseX / TileSize;

    {
        if (!pieceSelected) //--------------this is clever
        {
            if (board[row][col] != "\'")
            {
                if (White_s_Turn == WHITEs_TURN && board[row][col][0] == 'w')
                {
                    pieceSelected = true;
                    selectedRow = row;
                    selectedCol = col;
                    std::cout << "WHITE***# Selected: \"" << board[row][col] << "\" is at : [" << row << " , " << col << "]" << std::endl; //------------------4.4.3I
                }
                else if (White_s_Turn == BLACKs_TURN && board[row][col][0] == 'b')
                {
                    pieceSelected = true;
                    selectedRow = row;
                    selectedCol = col;
                    std::cout << "BLACK___# Selected: \"" << board[row][col] << "\" is at : [" << row << " , " << col << "]" << std::endl; //------------------4.4.3I
                }
            }
        }
        else
        {
            bool check = movePiece(row, col); //--------------------4.4.3_II
            selectedRow = -1;
            selectedCol = -1; // for reseting all again
            pieceSelected = false;

            if (!check)
                White_s_Turn = !White_s_Turn;
            else
                std::cout << "No turning !\n";
            if (White_king_SurroundingDangerousGrid[1][1])
                printf("White King is in Attack!\n");
            if (Black_king_SurroundingDangerousGrid[1][1])
                printf("Black King is in Attack!\n");
            if (White_s_Turn == WHITEs_TURN)
                printf("Now it's White's turn!\n");
            else
                printf("Now it's Black's Turn!\n");
        }
    }
    /// SO here I gonna do external works
}

void Board::setupBoard() //--------------------2.4.3
{
    for (int j = 2; j < 6; ++j)
        for (int i = 0; i < 8; ++i)
            board[i][j] = "\'";

    // pawns
    for (int i = 0; i < 8; i++)
    {
        board[i][1] = "wp";
        board[i][6] = "bp";
    }

    // setting rooks
    board[0][0] = board[7][0] = "wr";
    board[0][7] = board[7][7] = "br";

    board[1][0] = board[6][0] = "wn";
    board[1][7] = board[6][7] = "bn";
    // setting knight

    board[2][0] = board[5][0] = "wb";
    board[2][7] = board[5][7] = "bb";
    // set the Bishop

    board[3][0] = "wq";
    board[3][7] = "bq";
    // setting the queen or minister

    board[4][0] = "wk";
    board[4][7] = "bk";
    // setting the king

    Black_King_positionAtRow = 4;
    Black_King_positionAtCol = 7;
    White_King_positionAtRow = 4;
    White_King_positionAtCol = 0;
    White_s_Turn = WHITEs_TURN;
    pieceSelected = false;
    selectedCol = -1;
    selectedRow = -1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            Black_king_SurroundingDangerousGrid[i][j] =
                White_king_SurroundingDangerousGrid[i][j] =
                    false;

    Casting_BK_with_DownRook =
        Casting_BK_with_UpRook =
            Casting_WK_with_DownRook =
                Casting_WK_with_UpRook =
                    IsBlackKingHaveCastlingChance =
                        IsWhiteKingHaveCastlingChance =
                            true;
    nowYouHave_bk_caslingWithDownBR =
        nowYouHave_bk_caslingWithUpBR =
            nowYouHave_wk_caslingWithDownWR =
                nowYouHave_wk_caslingWithUpWR =
                    isAnycheckMate =
                        isToken =
                            doesCastlingOccured = false;
    system("clear");
    std::cout << "\033[34mSO______HERE_____WE_____GO\033[37m" << std::endl;
}
Board::~Board()
{
    for (auto &target : pieceTextures)
    {
        if (target.second)
            SDL_DestroyTexture(target.second);
        // SDL_Delay(1000);
    }
}

Game::Game() : window(nullptr), renderer(nullptr), running(false), side_text1(nullptr), side_text2(nullptr), side_text3(nullptr), font1(nullptr), font2(nullptr), hint(nullptr)
{
    Text_Rect1 = {970, 10, 125, 50};
    Text_Rect2 = {1070, 10, 76, 50};
    Text_Rect3 = {970, 80, 76, 60};
    hintRct = {1046, 80, 76, 60};
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

    BoardClass = std::make_shared<Board>(renderer, MoveSound, checkSound, takeOffSound); //----------2.4
    list = std::make_shared<AdvancedTable>(530, 600, 995, 240, window, renderer);
    if (list->init())
        return true;

    running = true; //--------2.5
    return false;
}

void Game::handleOut(int MouseX, int MouseY)
{

    if (MouseX >= 970 && MouseX <= 1046 && MouseY >= 10 && MouseY <= 60)
    {
        Mix_PlayMusic(clickSound, 0);
        SDL_Delay(300);
        running = !running;
    }
    else if (MouseX >= 1070 && MouseX <= 1146 && MouseY >= 10 && MouseY <= 60)
    {
        Mix_PlayMusic(clickSound, 0);
        SDL_Delay(300);
        BoardClass->setupBoard(); // reset all board again
    }
    else if (MouseX >= 970 && MouseX <= 1110 && MouseY >= 80 && MouseY <= 130)
    {
        Mix_PlayMusic(clickSound, 0);
        SDL_Delay(300);
    }
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
            if (row <= 7 && col <= 7)
                BoardClass->handleClick(x, y); //----------------4.4
            else if (col > 7)
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
                    list->items[idx]->onClick();
            }
            break;
        }
        }
    }
    // list->handleEvents();
}

void Game::update() //----------------5.1
{
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
    BoardClass->rectangleSides(Text_Rect3);

    SDL_RenderCopy(renderer, side_text1, nullptr, &Text_Rect1);
    SDL_RenderCopy(renderer, side_text2, nullptr, &Text_Rect2);
    SDL_RenderCopy(renderer, side_text3, nullptr, &Text_Rect3);
    SDL_RenderCopy(renderer, hint, nullptr, &hintRct);
}

void Game::render() //-------------6.1
{
    list->render();
    SDL_RenderPresent(renderer); //-------------------6.3
}
void Game::clean()
{
    // BoardClass;

    Mix_HaltChannel(-1);
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
    if (side_text3)
        SDL_DestroyTexture(side_text3);
    if (hint)
        SDL_DestroyTexture(hint);

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

    temp = TTF_RenderText_Blended(font1, "HINT", colour);

    Text_Rect3.h = temp->h;
    Text_Rect3.w = temp->w;
    side_text3 = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);

    hint = IMG_LoadTexture(renderer, "Pieces/hint.png");
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

void Board::DrawKnightPath(int Row, int Col)
{
    if (White_s_Turn == WHITEs_TURN)
    {
        if (isBlack(Row + 1, Col + 2))
            DrawSquereRing(Row + 1, Col + 2, 'r');
        else if (!isWhite(Row + 1, Col + 2))
            DrawSquereRing(Row + 1, Col + 2, 'g');
        if (isBlack(Row + 2, Col + 1))
            DrawSquereRing(Row + 2, Col + 1, 'r');
        else if (!isWhite(Row + 2, Col + 1))
            DrawSquereRing(Row + 2, Col + 1, 'g');
        if (isBlack(Row - 1, Col + 2))
            DrawSquereRing(Row - 1, Col + 2, 'r');
        else if (!isWhite(Row - 1, Col + 2))
            DrawSquereRing(Row - 1, Col + 2, 'g');
        if (isBlack(Row - 2, Col + 1))
            DrawSquereRing(Row - 2, Col + 1, 'r');
        else if (!isWhite(Row - 2, Col + 1))
            DrawSquereRing(Row - 2, Col + 1, 'g');
        if (isBlack(Row - 2, Col - 1))
            DrawSquereRing(Row - 2, Col - 1, 'r');
        else if (!isWhite(Row - 2, Col - 1))
            DrawSquereRing(Row - 2, Col - 1, 'g');
        if (isBlack(Row - 1, Col - 2))
            DrawSquereRing(Row - 1, Col - 2, 'r');
        else if (!isWhite(Row - 1, Col - 2))
            DrawSquereRing(Row - 1, Col - 2, 'g');
        if (isBlack(Row + 1, Col - 2))
            DrawSquereRing(Row + 1, Col - 2, 'r');
        else if (!isWhite(Row + 1, Col - 2))
            DrawSquereRing(Row + 1, Col - 2, 'g');
        if (isBlack(Row + 2, Col - 1))
            DrawSquereRing(Row + 2, Col - 1, 'r');
        else if (!isWhite(Row + 2, Col - 1))
            DrawSquereRing(Row + 2, Col - 1, 'g');
    }
    else
    {
        if (isWhite(Row + 1, Col + 2))
            DrawSquereRing(Row + 1, Col + 2, 'r');
        else if (!isBlack(Row + 1, Col + 2))
            DrawSquereRing(Row + 1, Col + 2, 'g');
        if (isWhite(Row + 2, Col + 1))
            DrawSquereRing(Row + 2, Col + 1, 'r');
        else if (!isBlack(Row + 2, Col + 1))
            DrawSquereRing(Row + 2, Col + 1, 'g');
        if (isWhite(Row - 1, Col + 2))
            DrawSquereRing(Row - 1, Col + 2, 'r');
        else if (!isBlack(Row - 1, Col + 2))
            DrawSquereRing(Row - 1, Col + 2, 'g');
        if (isWhite(Row - 2, Col + 1))
            DrawSquereRing(Row - 2, Col + 1, 'r');
        else if (!isBlack(Row - 2, Col + 1))
            DrawSquereRing(Row - 2, Col + 1, 'g');
        if (isWhite(Row - 2, Col - 1))
            DrawSquereRing(Row - 2, Col - 1, 'r');
        else if (!isBlack(Row - 2, Col - 1))
            DrawSquereRing(Row - 2, Col - 1, 'g');
        if (isWhite(Row - 1, Col - 2))
            DrawSquereRing(Row - 1, Col - 2, 'r');
        else if (!isBlack(Row - 1, Col - 2))
            DrawSquereRing(Row - 1, Col - 2, 'g');
        if (isWhite(Row + 1, Col - 2))
            DrawSquereRing(Row + 1, Col - 2, 'r');
        else if (!isBlack(Row + 1, Col - 2))
            DrawSquereRing(Row + 1, Col - 2, 'g');
        if (isWhite(Row + 2, Col - 1))
            DrawSquereRing(Row + 2, Col - 1, 'r');
        else if (!isBlack(Row + 2, Col - 1))
            DrawSquereRing(Row + 2, Col - 1, 'g');
    }
}
void Board::DrawRookPath(int Row, int Col)
{
    if (White_s_Turn == WHITEs_TURN)
    {
        for (int i = Col + 1; i < 8; i++)
        {
            if (board[Row][i] == "\'")
                DrawSquereRing(Row, i, 'g');
            else
            {
                if (board[Row][i][0] == 'b')
                    DrawSquereRing(Row, i, 'r');
                break;
            }
        }
        for (int i = Col - 1; i >= 0; i--)
        {
            if (board[Row][i] == "\'")
                DrawSquereRing(Row, i, 'g');
            else
            {
                if (board[Row][i][0] == 'b')
                    DrawSquereRing(Row, i, 'r');
                break;
            }
        }
        for (int i = Row + 1; i < 8; i++)
        {
            if (board[i][Col] == "\'")
                DrawSquereRing(i, Col, 'g');
            else
            {
                if (board[i][Col][0] == 'b')
                    DrawSquereRing(i, Col, 'r');
                break;
            }
        }
        for (int i = Row - 1; i >= 0; i--)
        {
            if (board[i][Col] == "\'")
                DrawSquereRing(i, Col, 'g');
            else
            {
                if (board[i][Col][0] == 'b')
                    DrawSquereRing(i, Col, 'r');
                break;
            }
        }
    }
    else
    {
        for (int i = Col + 1; i < 8; i++)
        {
            if (board[Row][i] == "\'")
            {
                DrawSquereRing(Row, i, 'g');
            }
            else
            {
                if (board[Row][i][0] == 'w')
                    DrawSquereRing(Row, i, 'r');
                break;
            }
        }
        for (int i = Col - 1; i >= 0; i--)
        {
            if (board[Row][i] == "\'")
            {
                DrawSquereRing(Row, i, 'g');
            }
            else
            {
                if (board[Row][i][0] == 'w')
                    DrawSquereRing(Row, i, 'r');
                break;
            }
        }
        for (int i = Row + 1; i < 8; i++)
        {
            if (board[i][Col] == "\'")
            {
                DrawSquereRing(i, Col, 'g');
            }
            else
            {
                if (board[i][Col][0] == 'w')
                    DrawSquereRing(i, Col, 'r');
                break;
            }
        }
        for (int i = Row - 1; i >= 0; i--)
        {
            if (board[i][Col] == "\'")
            {
                DrawSquereRing(i, Col, 'g');
            }
            else
            {
                if (board[i][Col][0] == 'w')
                    DrawSquereRing(i, Col, 'r');
                break;
            }
        }
    }
}
void Board::DrawBishopPath(int Row, int Col)
{
    if (White_s_Turn == WHITEs_TURN)
    {
        for (int j = Col + 1, i = Row + 1; i < 8 && j < 8; i++, j++)
        {
            if (board[i][j] == "\'")
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j][0] == 'b')
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
        for (int j = Col - 1, i = Row + 1; i < 8 && j >= 0; i++, j--)
        {
            if (board[i][j] == "\'")
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j][0] == 'b')
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
        for (int j = Col - 1, i = Row - 1; i >= 0 && j >= 0; i--, j--)
        {
            if (board[i][j] == "\'")
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j][0] == 'b')
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
        for (int j = Col + 1, i = Row - 1; i >= 0 && j < 8; i--, j++)
        {
            if (board[i][j] == "\'")
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j][0] == 'b')
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
    }
    else
    {
        for (int j = Col + 1, i = Row + 1; i < 8 && j < 8; i++, j++)
        {
            if (board[i][j] == "\'")
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j][0] == 'w')
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
        for (int j = Col - 1, i = Row + 1; i < 8 && j >= 0; i++, j--)
        {
            if (board[i][j] == "\'")
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j][0] == 'w')
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
        for (int j = Col - 1, i = Row - 1; i >= 0 && j >= 0; i--, j--)
        {
            if (board[i][j] == "\'")
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j][0] == 'w')
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
        for (int j = Col + 1, i = Row - 1; i >= 0 && j < 8; i--, j++)
        {
            if (board[i][j] == "\'")
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j][0] == 'w')
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
    }
}
void Board::DrawQueenPath(int Row, int Col)
{
    DrawBishopPath(Row, Col);
    DrawRookPath(Row, Col);
}
void Board::DrawKingPath(int Row, int Col)
{
    if (White_s_Turn == WHITEs_TURN)
    {
        if (isBlack(Row + 1, Col + 1))
            DrawSquereRing(Row + 1, Col + 1, 'r');
        else if (!isWhite(Row + 1, Col + 1))
            DrawSquereRing(Row + 1, Col + 1, 'g');
        if (isBlack(Row, Col + 1))
            DrawSquereRing(Row, Col + 1, 'r');
        else if (!isWhite(Row, Col + 1))
            DrawSquereRing(Row, Col + 1, 'g');
        if (isBlack(Row - 1, Col + 1))
            DrawSquereRing(Row - 1, Col + 1, 'r');
        else if (!isWhite(Row - 1, Col + 1))
            DrawSquereRing(Row - 1, Col + 1, 'g');
        if (isBlack(Row - 1, Col))
            DrawSquereRing(Row - 1, Col, 'r');
        else if (!isWhite(Row - 1, Col))
            DrawSquereRing(Row - 1, Col, 'g');
        if (isBlack(Row - 1, Col - 1))
            DrawSquereRing(Row - 1, Col - 1, 'r');
        else if (!isWhite(Row - 1, Col - 1))
            DrawSquereRing(Row - 1, Col - 1, 'g');
        if (isBlack(Row, Col - 1))
            DrawSquereRing(Row, Col - 1, 'r');
        else if (!isWhite(Row, Col - 1))
            DrawSquereRing(Row, Col - 1, 'g');
        if (isBlack(Row + 1, Col - 1))
            DrawSquereRing(Row + 1, Col - 1, 'r');
        else if (!isWhite(Row + 1, Col - 1))
            DrawSquereRing(Row + 1, Col - 1, 'g');
        if (isBlack(Row + 1, Col))
            DrawSquereRing(Row + 1, Col, 'r');
        else if (!isWhite(Row + 1, Col))
            DrawSquereRing(Row + 1, Col, 'g');
    }
    else
    {
        if (isWhite(Row + 1, Col + 1))
            DrawSquereRing(Row + 1, Col + 1, 'r');
        else if (!isBlack(Row + 1, Col + 1))
            DrawSquereRing(Row + 1, Col + 1, 'g');
        if (isWhite(Row, Col + 1))
            DrawSquereRing(Row, Col + 1, 'r');
        else if (!isBlack(Row, Col + 1))
            DrawSquereRing(Row, Col + 1, 'g');
        if (isWhite(Row - 1, Col + 1))
            DrawSquereRing(Row - 1, Col + 1, 'r');
        else if (!isBlack(Row - 1, Col + 1))
            DrawSquereRing(Row - 1, Col + 1, 'g');
        if (isWhite(Row - 1, Col))
            DrawSquereRing(Row - 1, Col, 'r');
        else if (!isBlack(Row - 1, Col))
            DrawSquereRing(Row - 1, Col, 'g');
        if (isWhite(Row - 1, Col - 1))
            DrawSquereRing(Row - 1, Col - 1, 'r');
        else if (!isBlack(Row - 1, Col - 1))
            DrawSquereRing(Row - 1, Col - 1, 'g');
        if (isWhite(Row, Col - 1))
            DrawSquereRing(Row, Col - 1, 'r');
        else if (!isBlack(Row, Col - 1))
            DrawSquereRing(Row, Col - 1, 'g');
        if (isWhite(Row + 1, Col - 1))
            DrawSquereRing(Row + 1, Col - 1, 'r');
        else if (!isBlack(Row + 1, Col - 1))
            DrawSquereRing(Row + 1, Col - 1, 'g');
        if (isWhite(Row + 1, Col))
            DrawSquereRing(Row + 1, Col, 'r');
        else if (!isBlack(Row + 1, Col))
            DrawSquereRing(Row + 1, Col, 'g');
    }
}
void Board::DrawSquereRing(int Row, int Colunm, char ch)
{
    if (Row < 0 || Row > 7 || Colunm < 0 || Colunm > 7)
        return;
    SDL_Rect rect1 = {Colunm * TileSize + 6, Row * TileSize + 6, 108, 6};
    SDL_Rect rect2 = {Colunm * TileSize + 6, Row * TileSize + 12, 6, 96};
    SDL_Rect rect3 = {Colunm * TileSize + 108, Row * TileSize + 12, 6, 96};
    SDL_Rect rect4 = {Colunm * TileSize + 6, Row * TileSize + 108, 108, 6};

    if (ch == 'r')
    {
        SDL_SetRenderDrawColor(renderer, 255, 10, 10, 0xff);
        SDL_RenderFillRect(renderer, &rect1);
        SDL_SetRenderDrawColor(renderer, 220, 10, 10, 0xff);
        SDL_RenderFillRect(renderer, &rect2);
        SDL_SetRenderDrawColor(renderer, 200, 10, 10, 0xff);
        SDL_RenderFillRect(renderer, &rect3);
        SDL_SetRenderDrawColor(renderer, 170, 10, 10, 0xff);
        SDL_RenderFillRect(renderer, &rect4);
    }
    else if (ch == 'g')
    {
        SDL_SetRenderDrawColor(renderer, 10, 255, 10, 0xff);
        SDL_RenderFillRect(renderer, &rect1);
        SDL_SetRenderDrawColor(renderer, 10, 220, 10, 0xff);
        SDL_RenderFillRect(renderer, &rect2);
        SDL_SetRenderDrawColor(renderer, 10, 200, 10, 0xff);
        SDL_RenderFillRect(renderer, &rect3);
        SDL_SetRenderDrawColor(renderer, 10, 170, 10, 0xff);
        SDL_RenderFillRect(renderer, &rect4);
    }
    else if (ch == 'b')
    {
        SDL_SetRenderDrawColor(renderer, 10, 10, 225, 0xff);
        SDL_RenderFillRect(renderer, &rect1);
        SDL_SetRenderDrawColor(renderer, 10, 10, 190, 0xff);
        SDL_RenderFillRect(renderer, &rect2);
        SDL_SetRenderDrawColor(renderer, 10, 10, 170, 0xff);
        SDL_RenderFillRect(renderer, &rect3);
        SDL_SetRenderDrawColor(renderer, 10, 10, 140, 0xff);
        SDL_RenderFillRect(renderer, &rect4);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 10, 10, 170, 0xff);
        SDL_RenderFillRect(renderer, &rect1);
        SDL_SetRenderDrawColor(renderer, 10, 10, 140, 0xff);
        SDL_RenderFillRect(renderer, &rect2);
        SDL_SetRenderDrawColor(renderer, 10, 10, 100, 0xff);
        SDL_RenderFillRect(renderer, &rect3);
        SDL_SetRenderDrawColor(renderer, 10, 10, 90, 0xff);
        SDL_RenderFillRect(renderer, &rect4);
    }
}

void Board::draw() // called from game ------------------6.2.1 update
{
    SDL_Color light{0xea, 0xea, 0xea, 0xff}; // Light tile color
    SDL_Color dark{0x40, 0x50, 0x50, 0xff};  // Dark tile color
    bool isDark;

    SDL_Rect Side{960, 0, 600, 960};
    SDL_SetRenderDrawColor(renderer, 0, 100, 103, 255);
    SDL_RenderFillRect(renderer, &Side);

    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 8; ++col)
        {
            tile.x = col * TileSize;
            tile.y = row * TileSize;
            tile.w = tile.h = TileSize;

            isDark = (row + col) & 1 ? 0 : 1;

            SDL_SetRenderDrawColor(renderer,
                                   isDark ? dark.r : light.r,
                                   isDark ? dark.g : light.g,
                                   isDark ? dark.b : light.b,
                                   0xff);        // -----------just making grids ------6.2.2
            SDL_RenderFillRect(renderer, &tile); //------------------6.2.3
            if (isDark)
            {
                tile.x += 5;
                tile.y += 5;
                tile.h -= 10;
                tile.w -= 10;
                SDL_SetRenderDrawColor(renderer,
                                       dark.r + 0x7,
                                       dark.g + 0x7,
                                       dark.b + 0x7,
                                       0xff);
                SDL_RenderFillRect(renderer, &tile);
                tile.x += 5;
                tile.y += 5;
                tile.h -= 10;
                tile.w -= 10;
                SDL_SetRenderDrawColor(renderer,
                                       dark.r + 0xf,
                                       dark.g + 0xf,
                                       dark.b + 0xf,
                                       0xff);
                SDL_RenderFillRect(renderer, &tile);
            }
            else
            {
                tile.x += 5;
                tile.y += 5;
                tile.h -= 10;
                tile.w -= 10;
                SDL_SetRenderDrawColor(renderer,
                                       light.r + 0xa,
                                       light.g + 0xa,
                                       light.b + 0xa,
                                       0xff);
                SDL_RenderFillRect(renderer, &tile);
                tile.x += 5;
                tile.y += 5;
                tile.h -= 10;
                tile.w -= 10;
                SDL_SetRenderDrawColor(renderer,
                                       light.r + 0x14,
                                       light.g + 0x14,
                                       light.b + 0x14,
                                       0xff);
                SDL_RenderFillRect(renderer, &tile);
            }
        }
    if (selectedRow >= 0 && selectedCol >= 0) // so I can size the whole grid
    {
        // if(isPawn(row,col)){highlight_paths("")}
        // I will hight light the selected pieces
        SDL_Rect highlight; // for makng rect
        highlight.x = selectedCol * TileSize;
        highlight.y = selectedRow * TileSize;
        highlight.w = TileSize;
        highlight.h = TileSize;
        /*selectedRow and selectedCol are in "Board.hpp"*/
        SDL_SetRenderDrawColor(renderer, 20, 240, 245, 255); // Green translucent-----------------------6.2.4

        // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        // Showing the alpha feature

        SDL_RenderFillRect(renderer, &highlight); //-----------------6.2.5
        ShowPosibilitiesGrid();                   // the Another Critical function
    }

    drawPieces(); // new third---------------------6.2.6!
    // calling the drawPieces
}

void Board::drawPieces() // ------------------- 6.2.6.1
{
    SDL_Rect dest;
    for (int row = 0; row < 8; ++row)
    { //                         ------------6.2.6.2 ----setting all pieces
        for (int col = 0; col < 8; ++col)
        {
            if (board[row][col] == "\'")
                continue;

            dest.x = col * TileSize; //-----------------6.2.6.3 ------
            dest.y = row * TileSize;
            dest.w = dest.h = TileSize;

            SDL_RenderCopy(renderer, pieceTextures[board[row][col]], nullptr, &dest); //-----------------------6.2.6.4-----
        }
    }
}



void Board::rectangleSides(SDL_Rect &re)
{
    // SDL_Rect rect{x, y, w, h};
    // SDL_Color color{0xff, 0xff, 0xff, 0xff};

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderFillRect(renderer, &re);
}


// #include "Board.hpp"

bool Board::ifCaslingPossible(char ch, bool *up, bool *down)
{
    if (ch == 'w')
    {
        if (CanBlackAttackThisGrid(4, 0))
            return false;

        if (Casting_WK_with_DownRook && board[5][0] == "\'" && board[6][0] == "\'" && !CanBlackAttackThisGrid(5, 0) && !CanBlackAttackThisGrid(6, 0))
            *down = true;

        if (board[3][0] == board[2][0] && board[2][0] == board[1][0] && Casting_WK_with_UpRook && !CanBlackAttackThisGrid(3, 0) && !CanBlackAttackThisGrid(2, 0) && !CanBlackAttackThisGrid(1, 0))
            *up = true;
    }
    else
    {
        if (CanWhiteAttackThisGrid(4, 7))
            return false;

        if (board[5][7] == "\'" && board[6][7] == "\'" && Casting_BK_with_DownRook && !CanWhiteAttackThisGrid(5, 7) && !CanWhiteAttackThisGrid(6, 7))
            *down = true;

        if (board[3][7] == board[2][7] && board[2][7] == board[1][7] && Casting_BK_with_UpRook && !CanWhiteAttackThisGrid(3, 7) && !CanWhiteAttackThisGrid(2, 7) && !CanWhiteAttackThisGrid(1, 7))
            *up = true;
    }

    if (*up || *down)
        return true;
    else
        return false;
}

bool Board::CanBlackAttackThisGrid(int r, int c)
{

    if (r < 0 || r > 7 || c < 0 || c > 7)
        return true;

    if (c < 7 && r < 7 && r > 0 && (board[r + 1][c + 1] == "bp" || board[r - 1][c + 1] == "bp")) // back pawn
        return true;
    // knight
    for (int cfb = -2; cfb < 3; cfb++)
    {
        if (cfb == 0 || c + cfb < 0 || c + cfb > 7)
            continue;
        for (int rud = -2; rud < 3; rud++)
        {
            if (rud == 0 || r + rud < 0 || r + rud > 7 || cfb == rud || cfb * (-1) == rud)
                continue;
            if (board[r + rud][c + cfb] == "bn")
                return true;
        }
    }

    // plus and cross.................

    bool UpForw = true, UpUp = true, UpBack = true, BackBack = true, BackDown = true, DownDown = true, DownForw = true, ForwForw = true;
    for (int x = 1; x < 8; x++)
    {
        if (c + x < 8 && board[r][c + x] != "\'" && ForwForw)
        {
            if (board[r][c + x] == "bq" || board[r][c + x] == "br")
                return true;
            else
                ForwForw = false;
        }
        if (r - x >= 0 && c + x < 8 && board[r - x][c + x] != "\'" && UpForw)
        {
            if (board[r - x][c + x] == "bq" || board[r - x][c + x] == "bb")
                return true;
            else
                UpForw = false;
        }
        if (r - x >= 0 && board[r - x][c] != "\'" && UpUp)
        {
            if (board[r - x][c] == "bq" || board[r - x][c] == "br")
                return true;
            else
                UpUp = false;
        }
        if (r - x >= 0 && c - x >= 0 && board[r - x][c - x] != "\'" && UpBack)
        {
            if (board[r - x][c - x] == "bq" || board[r - x][c - x] == "bb")
                return true;
            else
                UpBack = false;
        }
        if (c - x >= 0 && board[r][c - x] != "\'" && BackBack)
        {
            if (board[r][c - x] == "bq" || board[r][c - x] == "br")
                return true;
            else
                BackBack = false;
        }
        if (r + x < 8 && c - x >= 0 && board[r + x][c - x] != "\'" && BackDown)
        {
            if (board[r + x][c - x] == "bq" || board[r + x][c - x] == "bb")
                return true;
            else
                BackDown = false;
        }
        if (r + x < 8 && board[r + x][c] != "\'" && DownDown)
        {
            if (board[r + x][c] == "bq" || board[r + x][c] == "br")
                return true;
            else
                DownDown = false;
        }
        if (r + x < 8 && c + x < 8 && board[r + x][c + x] != "\'" && DownForw)
        {
            if (board[r + x][c + x] == "bq" || board[r + x][c + x] == "bb")
                return true;
            else
                DownForw = false;
        }
    }

    if ((r < 7 && c < 7 && board[r + 1][c + 1] == "bk") || (c < 7 && board[r][c + 1] == "bk") || (c < 7 && r > 0 && board[r - 1][c + 1] == "bk") || (r > 0 && board[r - 1][c] == "bk") || (r > 0 && c > 0 && board[r - 1][c - 1] == "bk") || (c > 0 && board[r][c - 1] == "bk") || (c > 0 && r < 7 && board[r + 1][c - 1] == "bk") || (r < 7 && board[r + 1][c] == "bk"))
        return true;

    return false;
}

bool Board::CanWhiteAttackThisGrid(int r, int c)
{

    if (r < 0 || r > 7 || c < 0 || c > 7)
        return true;

    if (c >= 1 && r < 7 && r >= 1 && (board[r + 1][c - 1] == "wp" || board[r - 1][c - 1] == "wp"))
        return true;

    // knight
    for (int cfb = -2; cfb < 3; cfb++)
    {
        if (cfb == 0 || c + cfb < 0 || c + cfb > 7)
            continue;
        for (int rud = -2; rud < 3; rud++)
        {
            if (rud == 0 || r + rud < 0 || r + rud > 7 || cfb == rud || cfb * (-1) == rud)
                continue;
            if (board[r + rud][c + cfb] == "wn")
                return true;
        }
    }

    // plus and cross.................

    bool UpForw = true, UpUp = true, UpBack = true, BackBack = true, BackDown = true, DownDown = true, DownForw = true, ForwForw = true;
    for (int x = 1; x < 8; x++)
    {
        if (c + x < 8 && board[r][c + x] != "\'" && ForwForw)
        {
            if (board[r][c + x] == "wq" || board[r][c + x] == "wr")
                return true;
            else
                ForwForw = false;
        }
        if (r - x >= 0 && c + x < 8 && board[r - x][c + x] != "\'" && UpForw)
        {
            if (board[r - x][c + x] == "wq" || board[r - x][c + x] == "wb")
                return true;
            else
                UpForw = false;
        }
        if (r - x >= 0 && board[r - x][c] != "\'" && UpUp)
        {
            if (board[r - x][c] == "wq" || board[r - x][c] == "wr")
                return true;
            else
                UpUp = false;
        }
        if (r - x >= 0 && c - x >= 0 && board[r - x][c - x] != "\'" && UpBack)
        {
            if (board[r - x][c - x] == "wq" || board[r - x][c - x] == "wb")
                return true;
            else
                UpBack = false;
        }
        if (c - x >= 0 && board[r][c - x] != "\'" && BackBack)
        {
            if (board[r][c - x] == "wq" || board[r][c - x] == "wr")
                return true;
            else
                BackBack = false;
        }
        if (r + x < 8 && c - x >= 0 && board[r + x][c - x] != "\'" && BackDown)
        {
            if (board[r + x][c - x] == "wq" || board[r + x][c - x] == "wb")
                return true;
            else
                BackDown = false;
        }
        if (r + x < 8 && board[r + x][c] != "\'" && DownDown)
        {
            if (board[r + x][c] == "wq" || board[r + x][c] == "wr")
                return true;
            else
                DownDown = false;
        }
        if (r + x < 8 && c + x < 8 && board[r + x][c + x] != "\'" && DownForw)
        {
            if (board[r + x][c + x] == "wq" || board[r + x][c + x] == "wb")
                return true;
            else
                DownForw = false;
        }
    }

    if ((r < 7 && c < 7 && board[r + 1][c + 1] == "wk") || (c < 7 && board[r][c + 1] == "wk") || (c < 7 && r > 0 && board[r - 1][c + 1] == "wk") || (r > 0 && board[r - 1][c] == "wk") || (r > 0 && c > 0 && board[r - 1][c - 1] == "wk") || (c > 0 && board[r][c - 1] == "wk") || (c > 0 && r < 7 && board[r + 1][c - 1] == "wk") || (r < 7 && board[r + 1][c] == "wk"))
        return true;

    return false;
}

void Board::KingsUpdate()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            White_king_SurroundingDangerousGrid[i][j] = CanBlackAttackThisGrid(White_King_positionAtRow + i - 1, White_King_positionAtCol + j - 1);
            Black_king_SurroundingDangerousGrid[i][j] = CanWhiteAttackThisGrid(Black_King_positionAtRow + i - 1, Black_King_positionAtCol + j - 1);
        }
}

// #include "Board.hpp"

bool Board::isWhite(int targetRow, int targetCol)
{
    if (targetCol < 0 || targetCol > 7 || targetRow < 0 || targetRow > 7)
        return false;
    if (board[targetRow][targetCol][0] == 'w')
        return true;
    else
        return false;
}

bool Board::isBlack(int targetRow, int targetCol)
{
    if (targetCol < 0 || targetCol > 7 || targetRow < 0 || targetRow > 7)
        return false;
    if (board[targetRow][targetCol][0] == 'b')
        return true;
    return false;
}

bool Board::AnyPieaceAtPlusPath(int r, int c)
{
    if (r == selectedRow)
    {
        if (c < selectedCol)
        {
            for (int i = c + 1; i < selectedCol; i++)
            {
                if (board[r][i] != "\'")
                    return false;
            }
        }
        else
        {
            for (int i = selectedCol + 1; i < c; i++)
            {
                if (board[r][i] != "\'")
                    return false;
            }
        }

        return true;
    }
    else if (c == selectedCol)
    {
        if (r < selectedRow)
        {
            for (int i = r + 1; i < selectedRow; i++)
            {
                if (board[i][c] != "\'")
                    return false;
            }
        }
        else
        {
            for (int i = selectedRow + 1; i < r; i++)
            {
                if (board[i][c] != "\'")
                    return false;
            }
        }

        return true;
    }

    return false;
}

bool Board::AnyPieaceAtRoundPath(int Row, int Col)
{
    if (abs(selectedRow - Row) == 1)
    {
        if (abs(selectedCol - Col) == 1 || Col == selectedCol)
        {
            if (board[selectedRow][selectedCol][0] == 'w')
            {
                White_King_positionAtCol = Col;
                White_King_positionAtRow = Row;
            }
            else
            {
                Black_King_positionAtRow = Row;
                Black_King_positionAtCol = Col;
            }

            return true;
        }
        else
            return false;
    }
    else if (selectedRow == Row)
    {
        if (abs(selectedCol - Col) == 1)
        {

            if (board[selectedRow][selectedCol][0] == 'w')
            {
                White_King_positionAtCol = Col;
                White_King_positionAtRow = Row;
            }
            else
            {
                Black_King_positionAtRow = Row;
                Black_King_positionAtCol = Col;
            }

            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool Board::KnightPath(int r, int c)
{
    if ((abs(c - selectedCol) == 2 && abs(r - selectedRow) == 1) || (abs(c - selectedCol) == 1 && abs(r - selectedRow) == 2))
        return true;
    return false;
}

bool Board::AnyPieaceAtCrossPath(int r, int c)
{
    bool no_abstruct = true;
    if (r > selectedRow && c > selectedCol)
    {
        for (int x = selectedCol + 1, y = selectedRow + 1; x < c && y < r; x++, y++)
        {
            if (board[y][x] != "\'")
            {
                no_abstruct = false;
                break;
            }
        }
    }
    else if (r > selectedRow && c < selectedCol)
    {
        for (int x = selectedCol - 1, y = selectedRow + 1; x > c && y < r; x--, y++)
        {
            if (board[y][x] != "\'")
            {
                no_abstruct = false;
                break;
            }
        }
    }
    else if (r < selectedRow && c < selectedCol)
    {

        for (int x = selectedCol - 1, y = selectedRow - 1; x > c && y > r; x--, y--)
        {
            if (board[y][x] != "\'")
            {
                no_abstruct = false;
                break;
            }
        }
    }
    else if (r < selectedRow && c > selectedCol)
    {

        for (int x = selectedCol + 1, y = selectedRow - 1; x < c && y > r; x++, y--)
        {
            if (board[y][x] != "\'")
            {
                no_abstruct = false;
                break;
            }
        }
    }
    else
    {
    }

    if (abs(r - selectedRow) == abs(c - selectedCol) && no_abstruct)
        return true;
    else
        return false;
}

bool Board::QueenPath(int targetRow, int targetCol)
{
    if (targetCol == selectedCol || targetRow == selectedRow)
        return AnyPieaceAtPlusPath(targetRow, targetCol);
    else
        return AnyPieaceAtCrossPath(targetRow, targetCol);
    return false;
}
// here under ----------------------------------------4.4.3_II_2.1

bool Board::function(int targetRow, int targetCol) //-------------------4.4.3_II_2.1
{
    bool flag = true;
    if (board[selectedRow][selectedCol][0] == board[targetRow][targetCol][0])
        return true;

    // forPawn()
    if (board[selectedRow][selectedCol] == "wp")                                                                                              // White pawn//-------------------4.4.3_II_2.2
        if (selectedCol == 1 && (targetCol == 3 && targetRow == selectedRow && board[selectedRow][2] == "\'" && board[targetRow][3] == "\'")) // First move
        {
            // Move forward 2
        }
        else if (targetCol == selectedCol + 1 && targetRow == selectedRow && board[targetRow][targetCol] == "\'")
        {
            // Move forward 1
        }
        else if (targetCol - 1 == selectedCol && (targetRow == selectedRow + 1 || targetRow == selectedRow - 1) && isBlack(targetRow, targetCol))
        {
            // Diagonal capture
        }
        else
            return true;

    else if (board[selectedRow][selectedCol] == "bp")                                                                                         // Black pawn//-------------------4.4.3_II_2.3
        if (selectedCol == 6 && (targetCol == 4 && targetRow == selectedRow && board[selectedRow][5] == "\'" && board[targetRow][4] == "\'")) // First move
        {
            // Move forward 2
        }
        else if (targetCol == selectedCol - 1 && targetRow == selectedRow && board[targetRow][targetCol] == "\'")
        {
            // Move forward 1
        }
        else if (targetCol == selectedCol - 1 &&
                 (targetRow == selectedRow + 1 || targetRow == selectedRow - 1) && board[targetRow][targetCol][0] == 'w') // isWhite
        {
            // Diagonal capture
        }
        else
            return true;

    // for Rook()
    else if (board[selectedRow][selectedCol][1] == 'r') //-------------------4.4.3_II_2.4
    {
        if (AnyPieaceAtPlusPath(targetRow, targetCol))
        {
            if (White_s_Turn == WHITEs_TURN)
            {
                if (Casting_WK_with_UpRook && selectedCol == 0 && selectedRow == 0)
                    Casting_WK_with_UpRook = false;
                else if (Casting_WK_with_DownRook && selectedCol == 0 && selectedRow == 7)
                    Casting_WK_with_DownRook = false;
            }
            else
            {
                if (Casting_BK_with_UpRook && selectedCol == 7 && selectedRow == 0)
                    Casting_BK_with_UpRook = false;
                else if (Casting_BK_with_DownRook && selectedCol == 7 && selectedRow == 7)
                    Casting_BK_with_DownRook = false;
            }
        }
        else
            return true;
    }
    // for Knight()
    else if (board[selectedRow][selectedCol][1] == 'n') //-------------------4.4.3_II_2.5
    {
        if (KnightPath(targetRow, targetCol))
        {
        }
        else
            return true;
    }

    // for Bishop()
    else if (board[selectedRow][selectedCol][1] == 'b') //-------------------4.4.3_II_2.6
    {
        if (AnyPieaceAtCrossPath(targetRow, targetCol))
        {
        }
        else
            return true;
    }

    // for Queen()
    else if (board[selectedRow][selectedCol][1] == 'q') //-------------------4.4.3_II_2.7
    {
        if (QueenPath(targetRow, targetCol))
        {
        }
        else
            return true;
    }

    // for King()
    else if (board[selectedRow][selectedCol][1] == 'k') //-------------------4.4.3_II_2.8
    {
        if (AnyPieaceAtRoundPath(targetRow, targetCol))
        {
            if (White_s_Turn == WHITEs_TURN)
            {
                IsWhiteKingHaveCastlingChance = Casting_WK_with_UpRook = Casting_WK_with_DownRook = false;
                White_King_positionAtCol = targetCol;
                White_King_positionAtRow = targetRow;
                printf(" %d %d \n", targetCol, targetRow);
            }
            else
            {
                IsBlackKingHaveCastlingChance = Casting_BK_with_DownRook = Casting_BK_with_UpRook = false;
                Black_King_positionAtCol = targetCol;
                Black_King_positionAtRow = targetRow;
                printf(" %d %d \n", targetCol, targetRow);
            }
        }

        else
        {
            if (White_s_Turn == WHITEs_TURN)
            {
                if (IsWhiteKingHaveCastlingChance && targetCol == 0)
                {
                    if (nowYouHave_wk_caslingWithUpWR && targetRow == 2 && Casting_WK_with_UpRook)
                    {
                        flag = false;
                        IsWhiteKingHaveCastlingChance = Casting_WK_with_UpRook = Casting_WK_with_DownRook = false;
                        board[0][0] = "\'";
                        board[3][0] = "wr";
                        White_King_positionAtCol = targetCol;
                        White_King_positionAtRow = targetRow;
                        doesCastlingOccured = true;

                        {
                            event temp;
                            temp.this_event.emplace_back(selectedRow, selectedCol, targetRow, targetCol, board[selectedRow][selectedCol], board[targetRow][targetCol]);
                            std::string temp_str;

                            temp_str = "wk castled with Upper Rook";

                            temp.event_what = temp_str;
                            BoardEvents.emplace_back(temp);
                        }
                    }
                    else if (nowYouHave_wk_caslingWithDownWR && targetRow == 6 && Casting_WK_with_DownRook)
                    {
                        flag = false;
                        IsWhiteKingHaveCastlingChance = Casting_WK_with_UpRook = Casting_WK_with_DownRook = false;
                        board[7][0] = "\'";
                        board[5][0] = "wr";
                        White_King_positionAtCol = targetCol;
                        White_King_positionAtRow = targetRow;
                        doesCastlingOccured = true;

                        {
                            event temp;
                            temp.this_event.emplace_back(selectedRow, selectedCol, targetRow, targetCol, board[selectedRow][selectedCol], board[targetRow][targetCol]);
                            std::string temp_str;

                            temp_str = "wk castled with Below Rook";

                            temp.event_what = temp_str;
                            BoardEvents.emplace_back(temp);
                        }
                    }
                }
            }

            else
            {
                if (IsBlackKingHaveCastlingChance && targetCol == 7)
                {
                    if (nowYouHave_bk_caslingWithDownBR && targetRow == 6 && Casting_BK_with_DownRook)
                    {
                        flag = false;
                        IsBlackKingHaveCastlingChance = Casting_BK_with_DownRook = Casting_BK_with_UpRook = false;
                        board[7][7] = "\'";
                        board[5][7] = "br";
                        Black_King_positionAtCol = targetCol;
                        Black_King_positionAtRow = targetRow;
                        doesCastlingOccured = true;

                        {
                            event temp;
                            temp.this_event.emplace_back(selectedRow, selectedCol, targetRow, targetCol, board[selectedRow][selectedCol], board[targetRow][targetCol]);
                            std::string temp_str;

                            temp_str = "bk castled with Below Rook";

                            temp.event_what = temp_str;
                            BoardEvents.emplace_back(temp);
                        }
                    }
                    else if (nowYouHave_bk_caslingWithUpBR && targetRow == 2 && Casting_BK_with_UpRook)
                    {
                        flag = false;
                        IsBlackKingHaveCastlingChance = Casting_BK_with_DownRook = Casting_BK_with_UpRook = false;
                        board[0][7] = "\'";
                        board[3][7] = "br";
                        Black_King_positionAtCol = targetCol;
                        Black_King_positionAtRow = targetRow;
                        doesCastlingOccured = true;

                        {
                            event temp;
                            temp.this_event.emplace_back(selectedRow, selectedCol, targetRow, targetCol, board[selectedRow][selectedCol], board[targetRow][targetCol]);
                            std::string temp_str;

                            temp_str = "wk castled with Upper Rook";

                            temp.event_what = temp_str;
                            BoardEvents.emplace_back(temp);
                        }
                    }
                }
            }
            if (flag)
                return true;
        }
    }
    if (board[targetRow][targetCol] != "\'")
        isToken = true;
    if (flag)
    {
        event temp;
        temp.this_event.emplace_back(selectedRow, selectedCol, targetRow, targetCol, board[selectedRow][selectedCol], board[targetRow][targetCol]);
        std::string temp_str;
        if (isToken)
            temp_str = board[selectedRow][selectedCol] + " Catured " + board[targetRow][targetCol];
        else
            temp_str = std::to_string(selectedRow) + "," + std::to_string(selectedCol) + " " + board[selectedRow][selectedCol] + " moved at " + std::to_string(targetRow) + "," + std::to_string(targetCol);
        temp.event_what = temp_str;
        BoardEvents.emplace_back(temp);
    }

    board[targetRow][targetCol] = board[selectedRow][selectedCol];
    board[selectedRow][selectedCol] = "\'";
    ismoved = true;
    return false;
}


// #include "Board.hpp"

void Board::ShowPosibilitiesGrid()
{
    int Col = selectedCol, Row = selectedRow;
    if (board[Row][Col][1] == 'p')
    {
        if (White_s_Turn == WHITEs_TURN)
        {
            if (isBlack(Row + 1, Col + 1))
                DrawSquereRing(Row + 1, Col + 1, 'r');
            if (isBlack(Row - 1, Col + 1))
                DrawSquereRing(Row - 1, Col + 1, 'r');
            if (board[Row][Col + 1] == "\'")
                DrawSquereRing(Row, Col + 1, 'g');
            if (board[Row][3] == "\'" && Col == 1 && board[Row][2] == "\'")
                DrawSquereRing(Row, 3, 'B');
        }
        else
        {
            if (isWhite(Row + 1, Col - 1))
                DrawSquereRing(Row + 1, Col - 1, 'r');
            if (isWhite(Row - 1, Col - 1))
                DrawSquereRing(Row - 1, Col - 1, 'r');
            if (board[Row][Col - 1] == "\'")
                DrawSquereRing(Row, Col - 1, 'g');
            if (board[Row][4] == "\'" && Col == 6 && board[Row][5] == "\'")
                DrawSquereRing(Row, 4, 'B');
        }
    }
    else if (board[Row][Col][1] == 'n')
        DrawKnightPath(Row, Col);
    else if (board[Row][Col][1] == 'r')
        DrawRookPath(Row, Col);
    else if (board[Row][Col][1] == 'b')
        DrawBishopPath(Row, Col);
    else if (board[Row][Col][1] == 'q')
        DrawQueenPath(Row, Col);
    else if (board[Row][Col][1] == 'k')
    {
        DrawKingPath(Row, Col);
        bool up = false, down = false;

        if (White_s_Turn == WHITEs_TURN)
        {
            if (IsWhiteKingHaveCastlingChance)
            {
                if (!ifCaslingPossible('w', &up, &down))
                {
                    nowYouHave_wk_caslingWithDownWR = down;
                    nowYouHave_wk_caslingWithUpWR = up;
                    return;
                }

                nowYouHave_wk_caslingWithDownWR = down;
                nowYouHave_wk_caslingWithUpWR = up;
                if (Casting_WK_with_DownRook && down)
                    DrawSquereRing(Row + 2, Col, 'b');
                if (Casting_WK_with_UpRook && up)
                    DrawSquereRing(Row - 2, Col, 'b');
            }
        }
        else
        {
            if (IsBlackKingHaveCastlingChance)
            {
                if (!ifCaslingPossible('b', &up, &down))
                {
                    nowYouHave_bk_caslingWithDownBR = down;
                    nowYouHave_bk_caslingWithUpBR = up;
                    return;
                }

                nowYouHave_bk_caslingWithDownBR = down;
                nowYouHave_bk_caslingWithUpBR = up;
                if (Casting_BK_with_DownRook && down)
                    DrawSquereRing(Row + 2, Col, 'b');
                if (Casting_BK_with_UpRook && up)
                    DrawSquereRing(Row - 2, Col, 'b');
            }
        }
    }
}

// #include "Scroll.hpp"

AdvancedTable::AdvancedTable(int w = 530, int h = 600, int x = 995, int y = 240, SDL_Window *win = nullptr, SDL_Renderer *render = nullptr)
    : window(win), renderer(render), font(nullptr), titleFont(nullptr), windowWidth(w), windowHeight(h), itemHeight(60), hoveredIndex(-1), selectedIndex(-1), maxScroll(0), targetScroll(0), currentScroll(0), scrollVelocity(0), headerText("Piece's Move"), posix(x), posiy(y), counter(0)
{
    headerRect = {x, y, w, 70};
    listArea = {x + 20, y + 180, w - 40, h - 230};
}

AdvancedTable::~AdvancedTable()
{
    items.clear();
    buttons.clear();
    if (titleFont)
        TTF_CloseFont(titleFont);
    if (font)
        TTF_CloseFont(font);

    // if (renderer) //----------------------------------------------------------
    // SDL_DestroyRenderer(renderer);
    // if (window) //------------------------------------------------------------
    // SDL_DestroyWindow(window);
    // TTF_Quit();
    // SDL_Quit();
}

bool AdvancedTable::init()
{
    font = TTF_OpenFont("font.ttf", 22);
    if (!font)
    {
        font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 22);
        if (!font)
            return true;
    }

    titleFont = TTF_OpenFont("font.ttf", 20);
    if (!titleFont)
    {
        titleFont = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 32);
    }
    // int counter = 1;

    addButton(headerRect.x + 20, headerRect.y + 90, 100, 60, "Add Item", Colors::GREEN, Colors::LIGHT_BLUE, [this]()
              {addItem("Item #" + std::to_string(counter++),Colors::WHITE,Colors::BLACK);
                std::cout << "➕ Added item #" << counter - 1 << std::endl; });

    addButton(headerRect.x + 150, headerRect.y + 90, 100, 60, "Remove", Colors::RED, Colors::LIGHT_BLUE, [this]()
              {removeLastItem();std::cout << "➖ Removed last item" << std::endl; });

    addButton(headerRect.x + 280, headerRect.y + 90, 100, 60, "Clear All", Colors::DARK_GRAY, Colors::LIGHT_BLUE, [this]()
              {clearItems();counter = 1;std::cout << "🗑️  Cleared all items" << std::endl; });

    addButton(headerRect.x + 410, headerRect.y + 90, 100, 60, "All", Colors::LIGHT_GRAY, Colors::LIGHT_BLUE, [this]()
              {clearItems();counter = 1;std::cout << "🗑️Okey,  Cleared all items" << std::endl; });

    // running = true;
    return false;
}

void AdvancedTable::addItem(std::string text = "123", SDL_Color bg = Colors::WHITE, SDL_Color tc = Colors::BLACK)
{
    auto item = std::make_shared<ListItem>(text, bg, tc);
    items.push_back(item);
    updateMaxScroll();
}

void AdvancedTable::removeLastItem()
{
    if (!items.empty())
    {
        items.pop_back();
        updateMaxScroll();
        if (selectedIndex >= static_cast<int>(items.size()))
        {
            selectedIndex = -1;
        }
    }
}

void AdvancedTable::clearItems()
{
    items.clear();
    selectedIndex = -1;
    hoveredIndex = -1;
    targetScroll = 0;
    currentScroll = 0;
    scrollVelocity = 0;
    counter = 0;
    updateMaxScroll();
}

void AdvancedTable::addButton(int x, int y, int w, int h, const std::string &text, SDL_Color normal, SDL_Color hover, std::function<void()> callback)
{
    buttons.emplace_back(x, y, w, h, text, normal, hover, callback);
}

void AdvancedTable::updateMaxScroll()
{
    // int totalHeight = ;
    maxScroll = std::max(0, static_cast<int>(items.size() * itemHeight) - listArea.h);
}

void AdvancedTable::smoothScrollTo(float target)
{
    targetScroll = std::max(0.0f, std::min(static_cast<float>(maxScroll), target));
}

void AdvancedTable::updateScrollPhysics()
{
    // Calculate how far we need to move
    float difference = targetScroll - currentScroll;

    // Apply spring-like physics
    // 0.8 = damping (slows down existing velocity)
    // 0.2 = spring strength (how fast to approach target)
    scrollVelocity = scrollVelocity * 0.7f + difference * 0.3f;

    // Update position
    currentScroll += scrollVelocity;

    // Stop when very close (prevents endless tiny movements)
    if (std::abs(difference) < 0.5F)
    {
        currentScroll = targetScroll;
        scrollVelocity = 0;
    }
}

int AdvancedTable::getItemIndexAtPosition(int mouseX, int mouseY)
{
    if (mouseX < listArea.x || mouseX > listArea.x + listArea.w || mouseY < listArea.y || mouseY > listArea.y + listArea.h)
        return -1;

    int relativeY = mouseY - listArea.y + static_cast<int>(currentScroll);
    int index = relativeY / itemHeight;

    if (index >= 0 && index < static_cast<int>(items.size()))
        return index;
    return -1;
}

void AdvancedTable::handleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_UP)
                smoothScrollTo(targetScroll - itemHeight * 2);
            else if (event.key.keysym.sym == SDLK_DOWN)
                smoothScrollTo(targetScroll + itemHeight * 2);
            else if (event.key.keysym.sym == SDLK_HOME)
                smoothScrollTo(0);
            else if (event.key.keysym.sym == SDLK_END)
                smoothScrollTo(maxScroll);
            break;

        case SDL_MOUSEWHEEL:
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            if (mouseX >= listArea.x && mouseX <= listArea.x + listArea.w && mouseY >= listArea.y && mouseY <= listArea.y + listArea.h)
                // Smooth scroll instead of instant
                smoothScrollTo(targetScroll - event.wheel.y * 60);
            break;
        }

        case SDL_MOUSEMOTION:
        {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;

            // Update button hover states
            for (auto &btn : buttons)
                btn.isHovered = btn.contains(mouseX, mouseY);

            // Update item hover
            hoveredIndex = getItemIndexAtPosition(mouseX, mouseY);
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            // Check buttons
            for (auto &btn : buttons)
                if (btn.contains(mouseX, mouseY) && btn.onClick)
                    btn.onClick();

            // Check items
            int idx = getItemIndexAtPosition(mouseX, mouseY);
            if (idx >= 0 && idx < static_cast<int>(items.size()))
            {
                selectedIndex = idx;
                std::cout << "✅ Selected: " << items[idx]->text << std::endl;

                if (items[idx]->onClick)
                    items[idx]->onClick();
            }
            break;
        }
        }
    }
}

void AdvancedTable::update()
{
    updateScrollPhysics(); // Smooth scrolling magic!
}

void AdvancedTable::renderButton(const Button &btn)
{
    SDL_Color color = btn.isHovered ? btn.hoverColor : btn.normalColor;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &btn.rect);

    SDL_SetRenderDrawColor(renderer,
                           Colors::DARK_GRAY.r, Colors::DARK_GRAY.g,
                           Colors::DARK_GRAY.b, Colors::DARK_GRAY.a);
    SDL_RenderDrawRect(renderer, &btn.rect);

    renderTextCentered(btn.text, btn.rect, Colors::BLUE, nullptr);
}

void AdvancedTable::renderList()
{
    SDL_RenderSetClipRect(renderer, &listArea);

    int scrollInt = static_cast<int>(currentScroll); // Convert float to int
    int firstVisible = scrollInt / itemHeight;
    int lastVisible = (scrollInt + listArea.h) / itemHeight + 2;

    firstVisible = std::max(0, firstVisible);
    lastVisible = std::min(static_cast<int>(items.size()), lastVisible);

    for (int i = firstVisible; i < lastVisible; i++)
    {
        int yPos = listArea.y + (i * itemHeight) - scrollInt;

        SDL_Rect itemRect = {
            listArea.x,
            yPos,
            listArea.w,
            itemHeight - 2};

        // Determine background color
        SDL_Color bgColor = items[i]->bgColor;
        if (i == selectedIndex)
            bgColor = Colors::GREEN;
        else if (i == hoveredIndex)
            bgColor = Colors::LIGHT_GRAY;

        // Draw item
        SDL_SetRenderDrawColor(renderer,
                               bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderFillRect(renderer, &itemRect);

        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL_RenderDrawRect(renderer, &itemRect);

        // Render text
        renderText(items[i]->text, itemRect.x + 10, itemRect.y + (itemHeight - 30) / 2, items[i]->textColor, nullptr);
    }

    SDL_RenderSetClipRect(renderer, nullptr);
}

void AdvancedTable::renderScrollbar()
{
    if (maxScroll <= 0)
        return;

    int barX = listArea.x + listArea.w + 5;
    int barY = listArea.y;
    int barWidth = 8;
    int barHeight = listArea.h;

    SDL_Rect track = {barX, barY, barWidth, barHeight};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &track);

    float visibleRatio = static_cast<float>(listArea.h) / (items.size() * itemHeight);
    int thumbHeight = std::max(20, static_cast<int>(barHeight * visibleRatio));

    float scrollPercentage = currentScroll / maxScroll;
    int thumbY = barY + static_cast<int>((barHeight - thumbHeight) * scrollPercentage);

    SDL_Rect thumb = {barX, thumbY, barWidth, thumbHeight};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &thumb);
}

void AdvancedTable::renderHeader()
{
    SDL_SetRenderDrawColor(renderer, Colors::BLUE.r, Colors::BLUE.g, Colors::BLUE.b, Colors::BLUE.a);
    SDL_RenderFillRect(renderer, &headerRect);

    if (!headerText.empty() && titleFont)
    {
        renderTextCentered(headerText, headerRect, Colors::WHITE, titleFont);
    }
}

void AdvancedTable::renderText(const std::string &text, int x, int y, SDL_Color color, TTF_Font *customFont = nullptr)
{
    TTF_Font *useFont = customFont ? customFont : font;
    SDL_Surface *surface = TTF_RenderText_Blended(useFont, text.c_str(), color);
    if (!surface)
        return;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void AdvancedTable::renderTextCentered(const std::string &text, const SDL_Rect &rect, SDL_Color color, TTF_Font *customFont)
{
    TTF_Font *useFont = customFont ? customFont : font;
    SDL_Surface *surface = TTF_RenderText_Blended(useFont, text.c_str(), color);
    if (!surface)
        return;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textX = rect.x + (rect.w - surface->w) / 2;
    int textY = rect.y + (rect.h - surface->h) / 2;

    SDL_Rect destRect = {textX, textY, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void AdvancedTable::render()
{
    renderHeader();

    for (const auto &btn : buttons)
        renderButton(btn);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &listArea);

    renderList();
    renderScrollbar();

    std::string status = "Items: " + std::to_string(items.size()) + " | Selected: " + (selectedIndex >= 0 ? std::to_string(selectedIndex + 1) : "None");
    renderText(status, 20 + posix, windowHeight - 35 + posiy, Colors::BLACK, nullptr);
}

void AdvancedTable::run()
{
    handleEvents();
    update();
    render();
}

const char *TITLE = "IRON_Chess_BOARD";
const int WIDTH = 1560;
const int HEIGHT = 960;

int main(int argc, char **argv)
{
    std::shared_ptr<Game> game(new Game); //----1

    if (game->isInitOkey(TITLE, WIDTH, HEIGHT)) //-----2
    {
        // delete game; //------III (if something wrong)
        // destructor will automatically delete the game object at heap
        return -1;
    }

    game->run();

    system("clear");
    std::cout << "\033[31mBYE!\033[37m" << std::endl;
    // delete game; //---------------8

    return 0; //-----------------9
}
