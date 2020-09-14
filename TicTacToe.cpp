//
// Created by cemlyn on 01/07/2020.
//

#include "TicTacToe.h"


TicTacToe::TicTacToe(int m, int n, int k, Player player1, Player player2) :
        m(m), n(n), k(k), max(std::move(player1)), min(std::move(player2)), board(m, n) {}


int TicTacToe::end_test(char marker) {
    if (board.no_blanks()) {
        // All spaces are occupied
        return -1;
    } else if (TicTacToe::check_win(marker)) {
        // This marker has won
        return 1;
    } else {
        // Game still in play
        return 0;
    }

}


bool TicTacToe::check_verts(int marker) {
    // check when you have a brain
    for (int i = 0; i < n; i++) {
        int chain_length = 0;
        for (int j = 0; j < m; j++) {
            if (board.board[j][i] == marker) {
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

bool TicTacToe::check_horiz(int marker) {
    for (int i = 0; i < m; i++) {
        int chain_length = 0;
        for (int j = 0; j < n; j++) {
            if (board.board[i][j] == marker) {
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

bool TicTacToe::check_diag(int marker, int direction) {
    for (int c = -m; c < m; c++) {
        int chain_length = 0;
        for (int i = 0; i < n; i++) {
            if (0 <= direction * i + c && direction * i + c < m && 0 <= i && i < n) {
                if (board.board[direction * i + c][i] == marker) {
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

bool TicTacToe::check_win(char marker) {
    if (check_verts(marker) || check_horiz(marker)) {
        return true;
    } else return check_diag(marker, 1) || check_diag(marker, -1);
}

std::tuple<int, int> TicTacToe::get_user_input() {
    int a, b;
    std::cout << "Please input move: ";
    std::cin >> a >> b;
    std::cout << "Received: " << "(" << a << "," << b << ")" << std::endl;
    return std::tuple<int, int>{a, b};
}

void TicTacToe::play() {
    std::tuple<int, int> move;
    bool game_over = false;

    Player prev_player = min;
    Player curr_player = max;

    board.print_board();

    do {
        move = get_user_input();
        board.mark_board(std::get<0>(move), std::get<1>(move), curr_player.get_marker());
        board.print_board();
        std::swap(curr_player, prev_player);
        switch (end_test(prev_player.get_marker())) {
            case -1:
                std::cout << "Draw" << std::endl;
                game_over = true;
                break;
            case 0:
                std::cout << "Player: " << curr_player.get_name() << std::endl;
                break;
            case 1:
                std::cout << "WON!" << std::endl;
                game_over = true;
                break;
        }
    } while (not(game_over));
}