#include "Board.hpp"

void Board::ShowPosibilitiesGrid()
{
    int Col = selectedCol, Row = selectedRow;
    if (board[Row][Col] == WP || board[selectedRow][selectedCol] == BP)
    {
        if (White_s_Turn == WHITEs_TURN)
        {
            if (isBlack(Row + 1, Col + 1))
                DrawSquereRing(Row + 1, Col + 1, 'r');
            if (isBlack(Row - 1, Col + 1))
                DrawSquereRing(Row - 1, Col + 1, 'r');
            if (board[Row][Col + 1] == EM)
                DrawSquereRing(Row, Col + 1, 'g');
            if (board[Row][3] == EM && Col == 1 && board[Row][2] == EM)
                DrawSquereRing(Row, 3, 'B');
        }
        else
        {
            if (isWhite(Row + 1, Col - 1))
                DrawSquereRing(Row + 1, Col - 1, 'r');
            if (isWhite(Row - 1, Col - 1))
                DrawSquereRing(Row - 1, Col - 1, 'r');
            if (board[Row][Col - 1] == EM)
                DrawSquereRing(Row, Col - 1, 'g');
            if (board[Row][6] == EM && Col == 7 && board[Row][5] == EM)
                DrawSquereRing(Row, 5, 'B');
        }
    }
    else if (board[Row][Col] == WN || board[selectedRow][selectedCol] == BN)
        DrawKnightPath(Row, Col);
    else if (board[Row][Col] == WR || board[selectedRow][selectedCol] == BR)
        DrawRookPath(Row, Col);
    else if (board[Row][Col] == WB || board[selectedRow][selectedCol] == BB)
        DrawBishopPath(Row, Col);
    else if (board[Row][Col] == WQ || board[selectedRow][selectedCol] == BQ)
        DrawQueenPath(Row, Col);
    else if (board[Row][Col] == WK || board[selectedRow][selectedCol] == BK)
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
