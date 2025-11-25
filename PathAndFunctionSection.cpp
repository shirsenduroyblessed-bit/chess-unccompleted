#include "Board.hpp"

bool Board::isWhite(int targetRow, int targetCol)
{
    if (targetCol < 0 || targetCol > 8 || targetRow < 0 || targetRow > 8)
        return false;
    if (board[targetRow][targetCol] < 6 && board[targetRow][targetCol] != EM)
        return true;
    else
        return false;
}

bool Board::isBlack(int targetRow, int targetCol)
{
    if (targetCol < 0 || targetCol > 8 || targetRow < 0 || targetRow > 8)
        return false;
    if (board[targetRow][targetCol] >= 6)
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
                if (board[r][i] != EM)
                    return false;
            }
        }
        else
        {
            for (int i = selectedCol + 1; i < c; i++)
            {
                if (board[r][i] != EM)
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
                if (board[i][c] != EM)
                    return false;
            }
        }
        else
        {
            for (int i = selectedRow + 1; i < r; i++)
            {
                if (board[i][c] != EM)
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
            if (board[selectedRow][selectedCol] < 6)
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

            if (board[selectedRow][selectedCol] < 6)
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
    if (abs(selectedCol - c) == 2)
    {
        if (abs(selectedRow - r) == 2 || r == selectedRow)
        {
            return true;
        }
    }
    else if (selectedCol == c && abs(selectedRow - r) == 1)
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
            if (board[y][x] != EM)
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
            if (board[y][x] != EM)
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
            if (board[y][x] != EM)
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
            if (board[y][x] != EM)
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
    std::string temp;
    PIECES targe;
    int castled = 0;

    if (board[targetRow][targetCol] != EM)
        if ((board[selectedRow][selectedCol] < 6 && board[targetRow][targetCol] < 6) || (board[selectedRow][selectedCol] >= 6 && board[targetRow][targetCol] >= 6))
            return true;

    // forPawn()
    if (board[selectedRow][selectedCol] == WP) // White pawn//-------------------4.4.3_II_2.2
    {
        if (selectedCol == 1 && (targetCol == 3 && targetRow == selectedRow && board[selectedRow][2] == EM && board[targetRow][3] == EM)) // First move
        {
            // Move forward 2
        }
        else if (targetCol == selectedCol + 1 && targetRow == selectedRow && board[targetRow][targetCol] == EM)
        {
            // Move forward 1
        }
        else if (targetCol - 1 == selectedCol && (targetRow == selectedRow + 1 || targetRow == selectedRow - 1) && isBlack(targetRow, targetCol))
        {
            // Diagonal capture
        }
        else
            return true;
    }

    else if (board[selectedRow][selectedCol] == BP) // Black pawn//-------------------4.4.3_II_2.3
    {
        if (selectedCol == 7 && (targetCol == 5 && targetRow == selectedRow && board[selectedRow][6] == EM && board[targetRow][5] == EM)) // First move
        {
            // Move forward 2
        }
        else if (targetCol == selectedCol - 1 && targetRow == selectedRow && board[targetRow][targetCol] == EM)
        {
            // Move forward 1
        }
        else if (targetCol == selectedCol - 1 && (targetRow == selectedRow + 1 || targetRow == selectedRow - 1) && isWhite(targetRow, targetCol)) // isWhite
        {
            // Diagonal capture
        }
        else
            return true;
    }

    // for Rook()
    else if (board[selectedRow][selectedCol] == WR || board[selectedRow][selectedCol] == BR) //-------------------4.4.3_II_2.4
    {
        if (AnyPieaceAtPlusPath(targetRow, targetCol))
        {
            if (White_s_Turn == WHITEs_TURN)
            {
                if (Casting_WK_with_UpRook && selectedCol == 0 && selectedRow == 0)
                    Casting_WK_with_UpRook = false;
                else if (Casting_WK_with_DownRook && selectedCol == 0 && selectedRow == 8)
                    Casting_WK_with_DownRook = false;
            }
            else
            {
                if (Casting_BK_with_UpRook && selectedCol == 8 && selectedRow == 0)
                    Casting_BK_with_UpRook = false;
                else if (Casting_BK_with_DownRook && selectedCol == 8 && selectedRow == 8)
                    Casting_BK_with_DownRook = false;
            }
        }
        else
            return true;
    }
    // for Knight()

    else if (board[selectedRow][selectedCol] == BN || board[selectedRow][selectedCol] == WN) //-------------------4.4.3_II_2.5
    {
        if (KnightPath(targetRow, targetCol))
        {
        }
        else
            return true;
    }

    // for Bishop()
    else if (board[selectedRow][selectedCol] == WB || board[selectedRow][selectedCol] == BB) //-------------------4.4.3_II_2.6
    {
        if (AnyPieaceAtCrossPath(targetRow, targetCol))
        {
        }
        else
            return true;
    }

    // for Queen()
    else if (board[selectedRow][selectedCol] == WQ || board[selectedRow][selectedCol] == BQ) //-------------------4.4.3_II_2.7
    {
        if (QueenPath(targetRow, targetCol))
        {
        }
        else
            return true;
    }

    // for King()
    else if (board[selectedRow][selectedCol] == BK || board[selectedRow][selectedCol] == WK) //-------------------4.4.3_II_2.8
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
                        board[0][0] = EM;
                        board[3][0] = WR;
                        White_King_positionAtCol = targetCol;
                        White_King_positionAtRow = targetRow;
                        doesCastlingOccured = true;
                        castled = 1;
                        // targe = WK;
                    }
                    else if (nowYouHave_wk_caslingWithDownWR && targetRow == 6 && Casting_WK_with_DownRook)
                    {
                        flag = false;
                        IsWhiteKingHaveCastlingChance = Casting_WK_with_UpRook = Casting_WK_with_DownRook = false;
                        board[8][0] = EM;
                        board[5][0] = WR;
                        White_King_positionAtCol = targetCol;
                        White_King_positionAtRow = targetRow;
                        doesCastlingOccured = true;
                        castled = 2;
                        // targe = WK;
                    }
                }
            }

            else
            {
                if (IsBlackKingHaveCastlingChance && targetCol == 8)
                {
                    if (nowYouHave_bk_caslingWithDownBR && targetRow == 6 && Casting_BK_with_DownRook)
                    {
                        flag = false;
                        IsBlackKingHaveCastlingChance = Casting_BK_with_DownRook = Casting_BK_with_UpRook = false;
                        board[8][8] = EM;
                        board[5][8] = BR;
                        Black_King_positionAtCol = targetCol;
                        Black_King_positionAtRow = targetRow;
                        doesCastlingOccured = true;
                        castled = 2;
                        // targe = BK;
                    }
                    else if (nowYouHave_bk_caslingWithUpBR && targetRow == 2 && Casting_BK_with_UpRook)
                    {
                        flag = false;
                        IsBlackKingHaveCastlingChance = Casting_BK_with_DownRook = Casting_BK_with_UpRook = false;
                        board[0][8] = EM;
                        board[3][8] = BR;
                        Black_King_positionAtCol = targetCol;
                        Black_King_positionAtRow = targetRow;
                        doesCastlingOccured = true;
                        castled = 1;
                        // targe = BK;
                    }
                }
            }

            if (flag)
                return true;
        }
    }

    if (board[targetRow][targetCol] != EM)
        isToken = true;

    {
        if (flag)
        {
            if (isToken)
                temp = " captured ";
            else
                temp = " moved at ";
            targe = board[targetRow][targetCol];
        }
        else
        {
            temp = " castled with ";
            if (White_s_Turn)
                targe = WR;
            else
                targe = BR;
        }

        switch (board[selectedRow][selectedCol])
        {
        case WK:
            temp = " WK " + temp;
            break;
        case WP:
            temp = " WP " + temp;
            break;
        case WN:
            temp = " WN " + temp;
            break;
        case WQ:
            temp = " WQ " + temp;
            break;
        case WR:
            temp = " WR " + temp;
            break;
        case WB:
            temp = " WB " + temp;
            break;
        case BK:
            temp = " BK " + temp;
            break;
        case BP:
            temp = " BP " + temp;
            break;
        case BN:
            temp = " BN " + temp;
            break;
        case BQ:
            temp = " BQ " + temp;
            break;
        case BR:
            temp = " BR " + temp;
            break;
        case BB:
            temp = " BB " + temp;
            break;
        default:
            break;
        }

        switch (targe)
        {
        case WP:
            temp += " WP ";
            break;
        case WN:
            temp += " WN ";
            break;
        case WQ:
            temp += " WQ ";
            break;
        case WR:
            temp += " WR ";
            break;
        case WB:
            temp += " WB ";
            break;
        case BP:
            temp += " BP ";
            break;
        case BN:
            temp += " BN ";
            break;
        case BQ:
            temp += " BQ ";
            break;
        case BR:
            temp += " BR ";
            break;
        case BB:
            temp += " BB ";
            break;
        default:
            break;
        }

        temp = ("[" + std::to_string(selectedRow) + "," + std::to_string(selectedCol) + "]" + temp + " [" + std::to_string(targetRow) + "," + std::to_string(targetCol) + "]");

        event *ptr = new event(selectedRow, selectedCol, targetRow, targetCol, castled, board[selectedRow][selectedCol], targe, temp);
        Events.emplace_back(ptr);
    }

    board[targetRow][targetCol] = board[selectedRow][selectedCol];
    board[selectedRow][selectedCol] = EM;

    std::cout << temp << std::endl;
    ismoved = true;
    return false;
}
