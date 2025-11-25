#include "Board.hpp"

bool Board::ifCaslingPossible(char ch, bool *up, bool *down)
{
    if (ch == 'w')
    {
        if (CanBlackAttackThisGrid(4, 0))
            return false;

        if (Casting_WK_with_DownRook && board[5][0] == EM && board[6][0] == EM && board[7][0] == EM && !CanBlackAttackThisGrid(5, 0) && !CanBlackAttackThisGrid(6, 0) && !CanBlackAttackThisGrid(8, 0))
            *down = true;

        if (board[3][0] == board[2][0] && board[2][0] == board[1][0] && Casting_WK_with_UpRook && !CanBlackAttackThisGrid(3, 0) && !CanBlackAttackThisGrid(2, 0) && !CanBlackAttackThisGrid(1, 0))
            *up = true;
    }
    else
    {
        if (CanWhiteAttackThisGrid(4, 8))
            return false;

        if (board[5][8] == EM && board[6][8] == EM && board[8][8] && Casting_BK_with_DownRook && !CanWhiteAttackThisGrid(5, 8) && !CanWhiteAttackThisGrid(6, 8) && !CanWhiteAttackThisGrid(8, 8))
            *down = true;

        if (board[3][8] == board[2][8] && board[2][8] == board[1][8] && Casting_BK_with_UpRook && !CanWhiteAttackThisGrid(3, 8) && !CanWhiteAttackThisGrid(2, 8) && !CanWhiteAttackThisGrid(1, 8))
            *up = true;
    }

    if (*up || *down)
        return true;
    else
        return false;
}

bool Board::CanBlackAttackThisGrid(int r, int c)
{

    if (r < 0 || r > 8 || c < 0 || c > 8)
        return true;

    if (c < 8 && r < 8 && r > 0 && (board[r + 1][c + 1] == BP || board[r - 1][c + 1] == BP)) // back pawn
        return true;
    // knight

    for (int rr = r - 2; rr <= r + 2; rr++)
    {
        if (rr < 0 || rr > 8)
            continue;
        for (int cc = c - 2; cc <= c + 2; cc++)
        {
            if (cc < 0 || cc > 8)
                continue;

            if (abs(cc - c) == 2)
            {
                if (abs(rr - r) == 2 || r == rr)
                {
                    if (board[rr][cc] == BN)
                        return true;
                }
            }
            else if (cc == c && abs(rr - r) == 1)
            {
                if (board[rr][cc] == BN)
                    return true;
            }
        }
    }

    // plus and cross.................

    bool UpForw = true, UpUp = true, UpBack = true, BackBack = true, BackDown = true, DownDown = true, DownForw = true, ForwForw = true;
    for (int x = 1; x < 8; x++)
    {
        if (c + x < 8 && board[r][c + x] != EM && ForwForw)
        {
            if (board[r][c + x] == BQ || board[r][c + x] == BR)
                return true;
            else
                ForwForw = false;
        }
        if (r - x >= 0 && c + x < 8 && board[r - x][c + x] != EM && UpForw)
        {
            if (board[r - x][c + x] == BQ || board[r - x][c + x] == BB)
                return true;
            else
                UpForw = false;
        }
        if (r - x >= 0 && board[r - x][c] != EM && UpUp)
        {
            if (board[r - x][c] == BQ || board[r - x][c] == BR)
                return true;
            else
                UpUp = false;
        }
        if (r - x >= 0 && c - x >= 0 && board[r - x][c - x] != EM && UpBack)
        {
            if (board[r - x][c - x] == BQ || board[r - x][c - x] == BB)
                return true;
            else
                UpBack = false;
        }
        if (c - x >= 0 && board[r][c - x] != EM && BackBack)
        {
            if (board[r][c - x] == BQ || board[r][c - x] == BR)
                return true;
            else
                BackBack = false;
        }
        if (r + x < 8 && c - x >= 0 && board[r + x][c - x] != EM && BackDown)
        {
            if (board[r + x][c - x] == BQ || board[r + x][c - x] == BB)
                return true;
            else
                BackDown = false;
        }
        if (r + x < 8 && board[r + x][c] != EM && DownDown)
        {
            if (board[r + x][c] == BQ || board[r + x][c] == BR)
                return true;
            else
                DownDown = false;
        }
        if (r + x < 8 && c + x < 8 && board[r + x][c + x] != EM && DownForw)
        {
            if (board[r + x][c + x] == BQ || board[r + x][c + x] == BB)
                return true;
            else
                DownForw = false;
        }
    }

    if ((r < 8 && c < 8 && board[r + 1][c + 1] == BK) || (c < 8 && board[r][c + 1] == BK) || (c < 8 && r > 0 && board[r - 1][c + 1] == BK) || (r > 0 && board[r - 1][c] == BK) || (r > 0 && c > 0 && board[r - 1][c - 1] == BK) || (c > 0 && board[r][c - 1] == BK) || (c > 0 && r < 8 && board[r + 1][c - 1] == BK) || (r < 8 && board[r + 1][c] == BK))
        return true;

    return false;
}

bool Board::CanWhiteAttackThisGrid(int r, int c)
{

    if (r < 0 || r > 8 || c < 0 || c > 8)
        return true;

    if (c >= 1 && r < 8 && r >= 1 && (board[r + 1][c - 1] == WP || board[r - 1][c - 1] == WP))
        return true;

    // knight
    for (int rr = r - 2; rr <= r + 2; rr++)
    {
        if (rr < 0 || rr > 8)
            continue;
        for (int cc = c - 2; cc <= c + 2; cc++)
        {
            if (cc < 0 || cc > 8)
                continue;

            if (abs(cc - c) == 2)
            {
                if (abs(rr - r) == 2 || r == rr)
                {
                    if (board[rr][cc] == WN)
                        return true;
                }
            }
            else if (cc == c && abs(rr - r) == 1)
            {
                if (board[rr][cc] == WN)
                    return true;
            }
        }
    }

    // plus and cross.................

    bool UpForw = true, UpUp = true, UpBack = true, BackBack = true, BackDown = true, DownDown = true, DownForw = true, ForwForw = true;
    for (int x = 1; x < 8; x++)
    {
        if (c + x < 8 && board[r][c + x] != EM && ForwForw)
        {
            if (board[r][c + x] == WQ || board[r][c + x] == WR)
                return true;
            else
                ForwForw = false;
        }
        if (r - x >= 0 && c + x < 8 && board[r - x][c + x] != EM && UpForw)
        {
            if (board[r - x][c + x] == WQ || board[r - x][c + x] == WB)
                return true;
            else
                UpForw = false;
        }
        if (r - x >= 0 && board[r - x][c] != EM && UpUp)
        {
            if (board[r - x][c] == WQ || board[r - x][c] == WR)
                return true;
            else
                UpUp = false;
        }
        if (r - x >= 0 && c - x >= 0 && board[r - x][c - x] != EM && UpBack)
        {
            if (board[r - x][c - x] == WQ || board[r - x][c - x] == WB)
                return true;
            else
                UpBack = false;
        }
        if (c - x >= 0 && board[r][c - x] != EM && BackBack)
        {
            if (board[r][c - x] == WQ || board[r][c - x] == WR)
                return true;
            else
                BackBack = false;
        }
        if (r + x < 8 && c - x >= 0 && board[r + x][c - x] != EM && BackDown)
        {
            if (board[r + x][c - x] == WQ || board[r + x][c - x] == WB)
                return true;
            else
                BackDown = false;
        }
        if (r + x < 8 && board[r + x][c] != EM && DownDown)
        {
            if (board[r + x][c] == WQ || board[r + x][c] == WR)
                return true;
            else
                DownDown = false;
        }
        if (r + x < 8 && c + x < 8 && board[r + x][c + x] != EM && DownForw)
        {
            if (board[r + x][c + x] == WQ || board[r + x][c + x] == WB)
                return true;
            else
                DownForw = false;
        }
    }

    if ((r < 8 && c < 8 && board[r + 1][c + 1] == WK) || (c < 8 && board[r][c + 1] == WK) || (c < 8 && r > 0 && board[r - 1][c + 1] == WK) || (r > 0 && board[r - 1][c] == WK) || (r > 0 && c > 0 && board[r - 1][c - 1] == WK) || (c > 0 && board[r][c - 1] == WK) || (c > 0 && r < 8 && board[r + 1][c - 1] == WK) || (r < 8 && board[r + 1][c] == WK))
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
