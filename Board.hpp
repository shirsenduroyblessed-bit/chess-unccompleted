#include "Scroll.hpp"

class Board
{
public:
    SDL_Renderer *renderer;
    SDL_Rect tile;
    bool White_s_Turn, IsWhiteKingHaveCastlingChance, IsBlackKingHaveCastlingChance, Casting_WK_with_UpRook, Casting_WK_with_DownRook, Casting_BK_with_UpRook, Casting_BK_with_DownRook;
    bool nowYouHave_wk_caslingWithUpWR, nowYouHave_wk_caslingWithDownWR, nowYouHave_bk_caslingWithUpBR, nowYouHave_bk_caslingWithDownBR;
    bool isAnycheckMate;
    bool isToken, doesCastlingOccured;
    bool pieceSelected;

    Mix_Music *MoveSound, *CheckSound, *TakeOffSound;

    std::vector<std::vector<bool>> Black_king_SurroundingDangerousGrid;
    std::vector<std::vector<bool>> White_king_SurroundingDangerousGrid;
    std::map<int, SDL_Texture *> pieceTextures;
    std::vector<std::vector<PIECES>> board;
    std::vector<event *> Events;
    std::vector<event *> Events_redone;

    int Black_King_positionAtRow, Black_King_positionAtCol, White_King_positionAtRow, White_King_positionAtCol;
    const int TileSize = 110;
    int selectedRow = -1; // new fourth
    int selectedCol = -1; // new fourth
    // each square is 120x120 px

    bool ismoved;
    bool undo_have_clicked, redo_have_clicked;

    void loadPieceTextures(); // one time used

    Board(SDL_Renderer *, Mix_Music *, Mix_Music *, Mix_Music *);
    ~Board();

    void setupBoard(); // one time used
    void draw();
    void handleClick(int, int); // new fourth for mouse controlling the
    void drawPieces();
    void ShowPosibilitiesGrid();
    void DrawSquereRing(int, int, char);
    void DrawKnightPath(int, int);
    void DrawRookPath(int, int);
    void DrawBishopPath(int, int);
    void DrawQueenPath(int, int);
    void DrawKingPath(int, int);
    void KingsUpdate();
    void rectangleSides(SDL_Rect &);
    void set_board_for_undo();
    void set_board_for_redo();

    bool redo_undo_update();
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

    // friend class player;
};
