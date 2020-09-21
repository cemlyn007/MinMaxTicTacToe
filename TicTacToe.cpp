//
// Created by cemlyn on 01/07/2020.
//

#include "TicTacToe.h"


TicTacToe::TicTacToe(int m, int n, int k, Player player1, Player player2) :
        m(m), n(n), k(k), PLAYER_MAX(std::move(player1)), PLAYER_MIN(std::move(player2)), board(m, n, 540) {}


TicTacToe::GameState TicTacToe::endTest(Board::Marker marker) {
    if (hasNoBlanks() || checkWin(marker)) {
        return GameState::FINISHED;
    } else {
        return GameState::RUNNING;
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

bool TicTacToe::checkDiag(Board::Marker marker, int direction) {
    int chain_length;
    for (int c = -n; c < n; c++) {
        for (int i = -n; i < n; i++) {
            if (not(0 <= direction * i + c & direction * i + c < n & 0<=i & i < m)) {
                chain_length = 0;
                continue;
            }
            if (board.board[i][direction * i + c] == marker) {
                chain_length++;
                if (chain_length == k) {
                    return true;
                }
            } else {
                chain_length = 0;
            }
        }
    }
//    for (int c = -m; c < m; c++) {
//        chain_length = 0;
//        for (int i = 0; i < n; i++) {
//            if (0 <= direction * i + c && direction * i + c < m && 0 <= i && i < n) {
//                if (board.board[direction * i + c][i] == marker) {
//                    chain_length++;
//                    if (chain_length == k) {
//                        return true;
//                    }
//                } else {
//                    chain_length = 0;
//                }
//            } else {
//                chain_length = 0;
//            }
//        }
//    }
    return false;
}

bool TicTacToe::checkWin(Board::Marker marker) {
    if (checkVertical(marker) || checkHoriz(marker)) {
        return true;
    } else return checkDiag(marker, 1) || checkDiag(marker, -1);
}

std::tuple<int, int> TicTacToe::getUserInput() {
    // This is modifiable
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
    Score end_score;
    Player prev_player = PLAYER_MIN;
    Player curr_player = PLAYER_MAX;

    showBoard();

    while (true) {
        move = getUserInput();
        board.markBoard(std::get<0>(move), std::get<1>(move), curr_player.getMarker());
        showBoard();
        switch (endTest(curr_player.getMarker())) {
            case GameState::RUNNING:
                std::swap(curr_player, prev_player);
                std::cout << "Player: " << curr_player.getName() << std::endl;
                break;
            case GameState::FINISHED:
                std::cout << "Finished" << std::endl;
                end_score = getScore(curr_player.getMarker());
                switch (end_score) {
                    case Score::DRAW:
                        std::cout << "Draw!" << std::endl;
                        break;
                    default:
                        std::cout << "Player: " << curr_player.name << " wins!" << std::endl;
                        break;
                }
                return;
        }
    }
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

TicTacToe::Score TicTacToe::getScore(Board::Marker marker) {
    if (hasNoBlanks() & not checkWin(marker)) { return Score::DRAW; }
    switch (marker) {
        case Board::Marker::X:
            return Score::X;
        case Board::Marker::O:
            return Score::O;
        case Board::Marker::BLANK:
            std::cout << "You wanted the score for the blank marker?" << std::endl;
            throw;
    }
}


bool TicTacToe::hasNoBlanks() {
    for (int i = 0; i < board.M; i++) {
        for (int j = 0; j < board.N; j++) { if (board.board[i][j] == Board::BLANK) { return false; }}
    }
    return true;
}

std::vector<std::tuple<int, int>> TicTacToe::getOptions() {
    std::vector<std::tuple<int, int>> options;
    for (int i = 0; i < board.M; i++) {
        for (int j = 0; j < board.N; j++) {
            if (board.board[i][j] == Board::BLANK) {
                options.emplace_back(std::tuple(i, j));
            }
        }
    }
    return options;
}

TicTacToe::Score TicTacToe::getWorstCaseScore(Board::Marker marker) {
    switch (marker) {
        case Board::Marker::X:
            return Score::O;
        case Board::Marker::O:
            return Score::X;
        case Board::Marker::BLANK:
            std::cout << "You wanted the score for the blank marker?" << std::endl;
            throw;
    }
}

