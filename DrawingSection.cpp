#include "Board.hpp"

void Board::DrawKnightPath(int Row, int Col)
{
    if (White_s_Turn)
    {
        for (int r = Row - 2; r <= Row + 2; r++)
        {
            for (int c = Col - 2; c <= Col + 2; c++)
            {
                if (abs(selectedCol - c) == 2)
                {
                    if (abs(selectedRow - r) == 2 || r == selectedRow)
                    {
                        if (isWhite(r, c))
                            DrawSquereRing(r, c, 'r');
                        else if (!isBlack(r, c))
                            DrawSquereRing(r, c, 'g');
                    }
                }
                else if (selectedCol == c && abs(selectedRow - r) == 1)
                {
                    if (isWhite(r, c))
                        DrawSquereRing(r, c, 'r');
                    else if (!isBlack(r, c))
                        DrawSquereRing(r, c, 'g');
                }
            }
        }
    }
    else
    {
        for (int r = Row - 2; r <= Row + 2; r++)
        {
            for (int c = Col - 2; c <= Col + 2; c++)
            {
                if (abs(selectedCol - c) == 2)
                {
                    if (abs(selectedRow - r) == 2 || r == selectedRow)
                    {
                        if (isBlack(r, c))
                            DrawSquereRing(r, c, 'r');
                        else if (!isWhite(r, c))
                            DrawSquereRing(r, c, 'g');
                    }
                }
                else if (selectedCol == c && abs(selectedRow - r) == 1)
                {
                    if (isBlack(r, c))
                        DrawSquereRing(r, c, 'r');
                    else if (!isWhite(r, c))
                        DrawSquereRing(r, c, 'g');
                }
            }
        }
    }
}

void Board::DrawRookPath(int Row, int Col)
{
    if (White_s_Turn == WHITEs_TURN)
    {
        for (int i = Col + 1; i < 9; i++)
        {
            if (board[Row][i] == EM)
                DrawSquereRing(Row, i, 'g');
            else
            {
                if (board[Row][i] >= 6)
                    DrawSquereRing(Row, i, 'r');
                break;
            }
        }

        for (int i = Col - 1; i >= 0; i--)
        {
            if (board[Row][i] == EM)
                DrawSquereRing(Row, i, 'g');
            else
            {
                if (board[Row][i] >= 6)
                    DrawSquereRing(Row, i, 'r');
                break;
            }
        }

        for (int i = Row + 1; i < 9; i++)
        {
            if (board[i][Col] == EM)
                DrawSquereRing(i, Col, 'g');
            else
            {
                if (board[i][Col] >= 6)
                    DrawSquereRing(i, Col, 'r');
                break;
            }
        }

        for (int i = Row - 1; i >= 0; i--)
        {
            if (board[i][Col] == EM)
                DrawSquereRing(i, Col, 'g');
            else
            {
                if (board[i][Col] >= 6)
                    DrawSquereRing(i, Col, 'r');
                break;
            }
        }
    }
    else
    {
        for (int i = Col + 1; i < 9; i++)
        {
            if (board[Row][i] == EM)
            {
                DrawSquereRing(Row, i, 'g');
            }
            else
            {
                if (board[Row][i] < 6)
                    DrawSquereRing(Row, i, 'r');
                break;
            }
        }

        for (int i = Col - 1; i >= 0; i--)
        {
            if (board[Row][i] == EM)
            {
                DrawSquereRing(Row, i, 'g');
            }
            else
            {
                if (board[Row][i] < 6)
                    DrawSquereRing(Row, i, 'r');
                break;
            }
        }

        for (int i = Row + 1; i < 9; i++)
        {
            if (board[i][Col] == EM)
            {
                DrawSquereRing(i, Col, 'g');
            }
            else
            {
                if (board[i][Col] < 6)
                    DrawSquereRing(i, Col, 'r');
                break;
            }
        }

        for (int i = Row - 1; i >= 0; i--)
        {
            if (board[i][Col] == EM)
            {
                DrawSquereRing(i, Col, 'g');
            }
            else
            {
                if (board[i][Col] < 6)
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
        for (int j = Col + 1, i = Row + 1; i < 9 && j < 9; i++, j++)
        {
            if (board[i][j] == EM)
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j] >= 6)
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
        for (int j = Col - 1, i = Row + 1; i < 9 && j >= 0; i++, j--)
        {
            if (board[i][j] == EM)
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j] >= 6)
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
        for (int j = Col - 1, i = Row - 1; i >= 0 && j >= 0; i--, j--)
        {
            if (board[i][j] == EM)
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j] >= 6)
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
        for (int j = Col + 1, i = Row - 1; i >= 0 && j < 9; i--, j++)
        {
            if (board[i][j] == EM)
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j] >= 6)
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
    }
    else
    {
        for (int j = Col + 1, i = Row + 1; i < 9 && j < 9; i++, j++)
        {
            if (board[i][j] == EM)
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j] < 6)
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
        for (int j = Col - 1, i = Row + 1; i < 9 && j >= 0; i++, j--)
        {
            if (board[i][j] == EM)
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j] < 6)
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
        for (int j = Col - 1, i = Row - 1; i >= 0 && j >= 0; i--, j--)
        {
            if (board[i][j] == EM)
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j] < 6)
                    DrawSquereRing(i, j, 'r');
                break;
            }
        }
        for (int j = Col + 1, i = Row - 1; i >= 0 && j < 9; i--, j++)
        {
            if (board[i][j] == EM)
            {
                DrawSquereRing(i, j, 'g');
            }
            else
            {
                if (board[i][j] < 6)
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
    if (Row < 0 || Row > 8 || Colunm < 0 || Colunm > 8)
        return;
    SDL_Rect rect1 = {Colunm * TileSize + 6, Row * TileSize + 6, 98, 6};
    SDL_Rect rect2 = {Colunm * TileSize + 6, Row * TileSize + 12, 6, 86};
    SDL_Rect rect3 = {Colunm * TileSize + 98, Row * TileSize + 12, 6, 86};
    SDL_Rect rect4 = {Colunm * TileSize + 6, Row * TileSize + 98, 98, 6};

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
    SDL_Color dark{0x30, 0x50, 0x50, 0xff};  // Dark tile color
    bool isDark;

    SDL_Rect Side{960 + 30, 0, 600, 960 + 30};
    {
        SDL_SetRenderDrawColor(renderer, 0x0, 0x6e, 0x67, 0xff);
        SDL_RenderFillRect(renderer, &Side);

        Side.x += 5;
        Side.y += 5;
        Side.w -= 10;
        Side.h -= 10;
        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
        SDL_RenderDrawRect(renderer, &Side);

        Side.x += 5;
        Side.y += 5;
        Side.w -= 10;
        Side.h -= 10;

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xfa);
        SDL_RenderFillRect(renderer, &Side);

        SDL_Texture *temp = IMG_LoadTexture(renderer, "pic/ChessNeo.png");

        SDL_Rect tem_rect = {Side.x, Side.y, Side.w, Side.w};
        SDL_RenderCopy(renderer, temp, nullptr, &tem_rect);
        SDL_DestroyTexture(temp);
    }

    for (int row = 0; row < 9; ++row)
        for (int col = 0; col < 9; ++col)
        {
            tile.x = col * TileSize;
            tile.y = row * TileSize;
            tile.w = tile.h = TileSize;

            isDark = (row + col) & 1 ? 0 : 1;

            SDL_SetRenderDrawColor(renderer, isDark ? dark.r : light.r, isDark ? dark.g : light.g, isDark ? dark.b : light.b, 0xff); // -----------just making grids ------6.2.2

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
        SDL_SetRenderDrawColor(renderer, 20, 220, 245, 255); // Green translucent-----------------------6.2.4

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
    for (int row = 0; row < 9; ++row)
    { //                         ------------6.2.6.2 ----setting all pieces
        for (int col = 0; col < 9; ++col)
        {
            if (board[row][col] == EM)
                continue;

            dest.x = col * TileSize; //-----------------6.2.6.3 ------
            dest.y = row * TileSize;
            dest.w = dest.h = TileSize;

            SDL_RenderCopy(renderer, pieceTextures[board[row][col]], nullptr, &dest); //-----------------------6.2.6.4-----
        }
    }
}

// here to ----------------------------------------

void Board::rectangleSides(SDL_Rect &re)
{
    // SDL_Rect rect{x, y, w, h};
    // SDL_Color color{0xff, 0xff, 0xff, 0xff};

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderFillRect(renderer, &re);
}
