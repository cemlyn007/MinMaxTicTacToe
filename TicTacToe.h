//
// Created by cemlyn on 01/07/2020.
//

#ifndef MINIMAXTICTACTOE_TICTACTOE_H
#define MINIMAXTICTACTOE_TICTACTOE_H


#include <iostream>
#include <utility>
#include <vector>
#include <tuple>
#include "Player.h"


class TicTacToe {
public:

    int m;
    int n;
    int k;
    char BLANK = '_';
    Player max;
    Player min;


    std::vector<std::vector<char>> board;

    TicTacToe(int row, int col, int length, Player player1, Player player2) {
        m = row;
        n = col;
        k = length;
        max = std::move(player1);
        min = std::move(player2);
        std::cout << "Playing TicTacToe: " << m << "x" << n << std::endl;
        board = create_board(m, n);
    }

    [[nodiscard]] std::vector<std::vector<char>> create_board(const int row_length, const int column_width) const {
        std::vector<std::vector<char>> new_board;
        for (int i = 0; i < row_length; i++) {
            std::vector<char> temp(column_width, BLANK);
            new_board.push_back(temp);
        }
        return new_board;
    }

    void print_board() {
        char marker;
        std::cout << "Printing board" << std::endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void mark_board(int i, int j, char marker) {
        if (board[i][j] == BLANK) {
            board[i][j] = marker;
        } else {
            throw; // Wanted to mark somewhere that is already marked... (mistake was made)
        }

    }

    void unmark_board(int i, int j) {
        board[i][j] = BLANK;
    }

    int end_test(char marker) {
        if (no_spaces()) {
            // All spaces are occupied
            return -1;
        } else if (check_win(marker)) {
            // This marker has won
            return 1;
        } else {
            // Game stil in play
            return 0;
        }

    }

    bool no_spaces() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == BLANK) {
                    return false;
                }
            }
        }
        return true;
    }

    bool check_verts(int marker) {
        // check when you have a brain
        for (int i = 0; i < n; i++) {
            int chain_length = 0;
            for (int j = 0; j < m; j++) {
                if (board[j][i] == marker) {
                    chain_length++;
                } else {
                    chain_length = 0;
                }
                if (chain_length == k) {
                    return true;
                }
            }
        }
        return false;
    }

    bool check_horiz(int marker) {
        for (int i = 0; i < m; i++) {
            int chain_length = 0;
            for (int j = 0; j < n; j++) {
                if (board[i][j] == marker) {
                    chain_length++;
                } else {
                    chain_length = 0;
                }
                if (chain_length == k) {
                    return true;
                }
            }
        }
        return false;
    }

    bool check_diag(int marker, int direction) {
        for (int c = -m; c < m; c++) {
            int chain_length = 0;
            for (int i = 0; i < n; i++) {
                if (0 <= direction * i + c && direction * i + c < m && 0 <= i && i < n) {
                    if (board[direction * i + c][i] == marker) {
                        chain_length++;
                    } else {
                        chain_length = 0;
                    }
                } else {
                    chain_length = 0;
                }
            }
            if (chain_length == k) {
                return true;
            }
        }
        return false;
    }

    bool check_win(char marker) {
        if (check_verts(marker) || check_horiz(marker)) {
            return true;
        } else return check_diag(marker, 1) || check_diag(marker, -1);
    }

    std::tuple<int, int> get_user_input() {
        int a, b;
        std::cout << "Please input move: ";
        std::cin >> a >> b;
        std::cout << "Received: " << "(" << a << "," << b << ")" << std::endl;
        return std::tuple<int, int>{a, b};
    }

    void play() {
        std::tuple<int, int> move;
        bool game_over = false;

        Player prev_player = min;
        Player curr_player = max;

        print_board();

        do {
            move = get_user_input();
            mark_board(std::get<0>(move), std::get<1>(move), curr_player.get_marker());
            print_board();
            std::swap(curr_player, prev_player);
            switch (end_test(prev_player.marker)) {
                case -1:
                    std::cout << "Draw" << std::endl;
                    game_over = true;
                    break;
                case 0:
                    std::cout << "Player: " << curr_player.name << std::endl;
                    break;
                case 1:
                    std::cout << "WON!" << std::endl;
                    game_over = true;
                    break;
            }
        } while (not(game_over));
    }
};


#endif //MINIMAXTICTACTOE_TICTACTOE_H
