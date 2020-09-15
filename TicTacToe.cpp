//
// Created by cemlyn on 01/07/2020.
//

#include "TicTacToe.h"


TicTacToe::TicTacToe(int m, int n, int k, Player player1, Player player2) :
        m(m), n(n), k(k), PLAYER_MAX(std::move(player1)), PLAYER_MIN(std::move(player2)), board(m, n, 540) {}


int TicTacToe::endTest(char marker) {
    if (board.hasNoBlanks()) {
        // All spaces are occupied
        return -1;
    } else if (TicTacToe::checkWin(marker)) {
        // This marker has won
        return 1;
    } else {
        // Game still in play
        return 0;
    }

}


bool TicTacToe::checkVertical(int marker) {
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

bool TicTacToe::checkHoriz(int marker) {
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

bool TicTacToe::checkDiag(int marker, int direction) {
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

bool TicTacToe::checkWin(char marker) {
    if (checkVertical(marker) || checkHoriz(marker)) {
        return true;
    } else return checkDiag(marker, 1) || checkDiag(marker, -1);
}

std::tuple<int, int> TicTacToe::getUserInput() {
    // This is modifiable, TODO: Insert GUI connection here
    static int a, b;
    if (board.screen == Board::ON) {
        std::tuple<int, int> mouse_position = board.getMousePosition();
        int pos_x = std::get<0>(mouse_position);
        int pos_y = std::get<1>(mouse_position);
        return board.getCell(pos_x, pos_y);
    } else if (board.screen == Board::CONSOLE) {
        std::cout << "Please input move: ";
        std::cin >> a >> b;
        std::cout << "Received: " << "(" << a << "," << b << ")" << std::endl;
        return std::tuple<int, int>{a, b};
    }
}

void TicTacToe::play() {
    std::tuple<int, int> move;
    bool game_over = false;

    Player prev_player = PLAYER_MIN;
    Player curr_player = PLAYER_MAX;

    showBoard();

    do {
        move = getUserInput();
        board.markBoard(std::get<0>(move), std::get<1>(move), curr_player.getMarker());
        showBoard();
        std::swap(curr_player, prev_player);
        switch (endTest(prev_player.getMarker())) {
            case -1:
                std::cout << "Draw" << std::endl;
                game_over = true;
                break;
            case 0:
                std::cout << "Player: " << curr_player.getName() << std::endl;
                break;
            case 1:
                std::cout << "WON!" << std::endl;
                game_over = true;
                break;
        }
    } while (not(game_over));
}

void TicTacToe::showBoard() {
    switch (board.screen) {
        case Board::ON:
            board.drawBoard();
            board.showBoard();
            break;
        case Board::CONSOLE:
            board.printBoard();
            break;
        case Board::OFF:
            break;
    }
}
