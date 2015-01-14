#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void solve(vector<vector<char> > &board) {
        if(board.size()<3||board[1].size()<3)
            return;
        for(int i=0; i<board.size(); i++)
        {
            for(int j=0; j<board[i].size(); j++)
            {
                if(board[i][j]=='0')
                {
                    if(left(board, i, j)&&right(board, i, j)&&up(board, i, j)&&down(board, i, j))
                        board[i][j]='X';
                }
            }
        }
    }
    bool left(vector<vector<char> > &board, int i, int j)
    {
        if(i>0)
        {
            if(board[j][i-1]=='0')
            {
                if(left(board, i-1, j)&&up(board, i-1, j)&&down(board, i-1, j))
                {
                    board[j][i-1]='X';
                    return true;
                }
                else
                    return false;
            }
            else
                return true;
        }
        return false;
    }
    bool right(vector<vector<char> > &board, int i, int j)
    {
        if(i<board[j].size()-1)
        {
            if(board[j][i+1]=='0')
            {
                if(right(board, i+1, j)&&up(board, i+1, j)&&down(board, i+1, j))
                {
                    board[j][i+1]='X';
                    return true;
                }
                else
                    return false;
            }
            else
                return true;
        }
        return false;
    }
    bool up(vector<vector<char> > &board, int i, int j)
    {
        if(j>0)
        {
            if(board[j-1][i]=='0')
            {
                if(up(board, i, j-1)&&left(board, i, j-1)&&right(board, i, j-1))
                {
                    board[j-1][i]='X';
                    return true;
                }
                else
                    return false;
            }
            else
                return true;
        }
        return false;
    }
    bool down(vector<vector<char> > &board, int i, int j)
    {
        if(j<board.size()-1)
        {
            if(board[j+1][i]=='0')
            {
                if(down(board, i, j+1)&&left(board, i, j+1)&&right(board, i, j+1))
                {
                    board[j+1][i]='X';
                    return true;
                }
                else
                    return false;
            }
            else
                return true;
        }
        return false;
    }
};


int main()
{
    vector<char> cvec1(3, 'X');
    vector<char> cvec2;
    cvec2.push_back('X');
    cvec2.push_back('0');
    cvec2.push_back('X');
    vector<vector<char> > vvec;
    vvec.push_back(cvec1);
    vvec.push_back(cvec2);
    vvec.push_back(cvec1);
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            std::cout<<vvec[i][j]<<" ";
        std::cout<<std::endl;
    }
    Solution s;
    s.solve(vvec);
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            std::cout<<vvec[i][j]<<" ";
        std::cout<<std::endl;
    }
    return 0;
}