#include "Board.hpp"

void Board::loadPieceTextures() //---------------2.4.2
{
    // std::string base = "Pieces/";
    std::string name[12] = {"WK", "WP", "WN", "WQ", "WR", "WB", "BK", "BP", "BN", "BQ", "BR", "BB"};

    for (int i = 0; i < 12; i++)
    {
        std::string temp = "Pieces/", png = ".png";
        temp += (name[i] + png);

        pieceTextures[i] = IMG_LoadTexture(renderer, temp.c_str()); //----------------------2.4.2.1
    }
}

Board::Board(SDL_Renderer *rend, Mix_Music *Sound, Mix_Music *sound1, Mix_Music *sound2) : renderer(rend), board(9, std::vector<PIECES>(9)), CheckSound(sound1), TakeOffSound(sound2), MoveSound(Sound), Black_king_SurroundingDangerousGrid(3, std::vector<bool>(3)), ismoved(false), White_king_SurroundingDangerousGrid(3, std::vector<bool>(3)), undo_have_clicked(false), redo_have_clicked(false) //----------------2.4.1
{
    loadPieceTextures(); //----------------2.4.2
    setupBoard();        //----------------2.4.3
}

bool Board::movePiece(int targetRow, int targetCol) //-------------4.4.3_II_1
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
            if (board[row][col] != EM)
            {
                if (White_s_Turn == WHITEs_TURN && board[row][col] < 6)
                {
                    pieceSelected = true;
                    selectedRow = row;
                    selectedCol = col;
                    std::cout << "WHITE***# Selected: \"" << board[row][col] << "\" is at : [" << row << " , " << col << "]" << std::endl; //------------------4.4.3I
                }
                else if (White_s_Turn == BLACKs_TURN && board[row][col] >= 6)
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
    for (int j = 2; j < 7; ++j)
        for (int i = 0; i < 9; ++i)
            board[i][j] = EM;

    // pawns
    for (int i = 0; i < 9; i++)
    {
        board[i][1] = WP;
        board[i][7] = BP;
    }

    // setting rooks
    board[0][0] = board[8][0] = WR;
    board[0][8] = board[8][8] = BR;

    board[1][0] = board[7][0] = WN;
    board[1][8] = board[7][8] = BN;

    // setting knight

    board[2][0] = board[6][0] = WB;
    board[2][8] = board[6][8] = BB;
    // set the Bishop

    board[3][0] = board[5][0] = WQ;
    board[3][8] = board[5][8] = BQ;
    // setting the queen or minister

    board[4][0] = WK;
    board[4][8] = BK;
    // setting the king

    Black_King_positionAtRow = 4;
    Black_King_positionAtCol = 8;
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
    if (!Events.empty())
    {
        for (auto &i : Events)
            delete i;
        Events.clear();
    }

    if (!Events_redone.empty())
    {
        for (auto &i : Events_redone)
            delete i;
        Events_redone.clear();
    }
    system("clear");
    std::cout << "\033[34mSO______HERE_____WE_____GO\033[37m" << std::endl;
}

// In SDL_Rect struct data , x and y is the top left position of the rectangle and w & h is weight and height of the rectangle

Board::~Board()
{
    for (auto &target : pieceTextures)
    {
        if (target.second)
            SDL_DestroyTexture(target.second);
        // SDL_Delay(1000);
    }
    if (!Events.empty())
    {
        for (auto &i : Events)
            delete i;
        Events.clear();
    }

    if (!Events_redone.empty())
    {
        for (auto &i : Events_redone)
            delete i;
        Events_redone.clear();
    }
}

void Board::set_board_for_redo()
{
    board[Events.back()->n_r][Events.back()->n_c] = Events.back()->selectd;
    board[Events.back()->pre_r][Events.back()->pre_c] = EM;

    if (Events.back()->selectd < 6)
    {
        if (Events.back()->castled == 1)
        {
            board[Events.back()->n_r + 1][Events.back()->n_c] = WR;
            board[0][0] = EM;
            IsWhiteKingHaveCastlingChance = Casting_WK_with_DownRook = Casting_WK_with_UpRook = false;
            White_King_positionAtCol = 0;
            White_King_positionAtRow = 4 - 2;
            doesCastlingOccured = true;
        }
        else if (Events.back()->castled == 2)
        {
            board[Events.back()->n_r - 1][Events.back()->n_c] = WR;
            board[8][0] = EM;
            IsWhiteKingHaveCastlingChance = Casting_WK_with_DownRook = Casting_WK_with_UpRook = false;
            White_King_positionAtCol = 0;
            White_King_positionAtRow = 4 + 2;
            doesCastlingOccured = true;
        }
    }
    else
    {
        if (Events.back()->castled == 1)
        {
            board[Events.back()->n_r + 1][Events.back()->n_c] = BR;
            board[0][8] = EM;

            Black_King_positionAtCol = 8;
            Black_King_positionAtRow = 4 - 2;
            doesCastlingOccured = true;
            IsBlackKingHaveCastlingChance = Casting_BK_with_DownRook = Casting_BK_with_UpRook = false;
        }
        else if (Events.back()->castled == 2)
        {
            board[Events.back()->n_r - 1][Events.back()->n_c] = BR;
            board[8][8] = EM;

            Black_King_positionAtCol = 8;
            Black_King_positionAtRow = 4 + 2;
            IsBlackKingHaveCastlingChance = Casting_BK_with_DownRook = Casting_BK_with_UpRook = false;
            doesCastlingOccured = true;
        }
    }
}

void Board::set_board_for_undo()
{
    board[Events_redone.back()->pre_r][Events_redone.back()->pre_c] = Events_redone.back()->selectd;

    if (Events_redone.back()->selectd < 6)
    {
        if (Events_redone.back()->castled == 1)
        {
            board[Events_redone.back()->n_r][Events_redone.back()->n_c] = EM;
            board[Events_redone.back()->n_r + 1][Events_redone.back()->n_c] = EM;
            board[0][0] = WR;
            IsWhiteKingHaveCastlingChance = Casting_WK_with_DownRook = Casting_WK_with_UpRook = true;
            White_King_positionAtCol = 0;
            White_King_positionAtRow = 4;
            doesCastlingOccured = false;
        }
        else if (Events_redone.back()->castled == 2)
        {
            board[Events_redone.back()->n_r][Events_redone.back()->n_c] = EM;
            board[Events_redone.back()->n_r - 1][Events_redone.back()->n_c] = EM;
            board[8][0] = WR;
            IsWhiteKingHaveCastlingChance = Casting_WK_with_DownRook = Casting_WK_with_UpRook = true;
            White_King_positionAtCol = 0;
            White_King_positionAtRow = 4;
            doesCastlingOccured = false;
        }
        else
            board[Events_redone.back()->n_r][Events_redone.back()->n_c] = Events_redone.back()->targtd;
    }
    else
    {
        if (Events_redone.back()->castled == 1)
        {
            board[Events_redone.back()->n_r][Events_redone.back()->n_c] = EM;
            board[Events_redone.back()->n_r + 1][Events_redone.back()->n_c] = EM;
            board[0][8] = BR;
            Black_King_positionAtCol = 8;
            Black_King_positionAtRow = 4;
            doesCastlingOccured = false;
            IsBlackKingHaveCastlingChance = Casting_BK_with_DownRook = Casting_BK_with_UpRook = true;
        }
        else if (Events_redone.back()->castled == 2)
        {
            board[Events_redone.back()->n_r][Events_redone.back()->n_c] = EM;
            board[Events_redone.back()->n_r - 1][Events_redone.back()->n_c] = EM;
            board[8][8] = BR;
            Black_King_positionAtCol = 8;
            Black_King_positionAtRow = 4;
            doesCastlingOccured = false;
            IsBlackKingHaveCastlingChance = Casting_BK_with_DownRook = Casting_BK_with_UpRook = true;
        }
        else
            board[Events_redone.back()->n_r][Events_redone.back()->n_c] = Events_redone.back()->targtd;
    }
}

bool Board::redo_undo_update()
{
    bool is = true;
    if (undo_have_clicked)
    {
        undo_have_clicked = false;
        set_board_for_undo();
        is = false;
    }
    else if (redo_have_clicked)
    {
        redo_have_clicked = false;
        set_board_for_redo();
        is = false;
    }
    return !is;
}
