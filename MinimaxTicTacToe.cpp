//
// Created by cemlyn on 02/07/2020.
//

#include "MinimaxTicTacToe.h"

#include <utility>

MinimaxTicTacToe::MinimaxTicTacToe(int m, int n, int k,
                                   Player player1, Player player2) : TicTacToe(m, n, k, std::move(player1),
                                                                               std::move(player2)) {

}

TicTacToe::Score MinimaxTicTacToe::getMiniMax(const Player &player, const Player &prev_player) {
    TicTacToe::GameState gameState = endTest(prev_player.getMarker());
    if (gameState == TicTacToe::GameState::RUNNING) {
        Score best_score;
        double (*optimiser)(double, double);
        Board::Marker marker = player.getMarker();
        std::vector<std::tuple<int, int>> options = getOptions();

        // This code gets the optimiser and sets the initial best score (the worst case)
        if (marker == PLAYER_MAX.getMarker()) {
            best_score = getScore(PLAYER_MIN.getMarker());
            optimiser = fmax;
        } else if (marker == PLAYER_MIN.getMarker()) {
            best_score = getScore(PLAYER_MAX.getMarker());
            optimiser = fmin;
        }

        // Now find best score
        for (std::tuple<int, int> move: options) {
            board.markBoard(move, player.getMarker());
            best_score = (Score)(optimiser((int)getMiniMax(prev_player, player), (int)best_score));
            board.unmarkBoard(move);
        }
        return best_score;
    } else if (gameState == TicTacToe::GameState::FINISHED) {
        return getScore(prev_player.getMarker());
    }
}

std::tuple<int, int> MinimaxTicTacToe::getBestMove(const Player &curr_player, const Player &next_player) {
    std::tuple<int, int> best_move;
    Score best_score, score;
    double (*optimiser)(double, double);
    std::vector<std::tuple<int, int>> options = getOptions();
    Board::Marker marker = curr_player.getMarker();

    // This code gets the optimiser and sets the initial best score (the worst case)
    if (marker == PLAYER_MAX.getMarker()) {
        best_score = getWorstCaseScore(PLAYER_MAX.getMarker());
        optimiser = fmax;
    } else if (marker == PLAYER_MIN.getMarker()) {
        best_score = getWorstCaseScore(PLAYER_MIN.getMarker());
        optimiser = fmin;
    }

    std::cout << best_score << std::endl;
    for (std::tuple<int, int> move: options) {
        board.markBoard(move, curr_player.getMarker());
        score = getMiniMax(next_player, curr_player);
        std::cout << "Move: (" << std::get<0>(move) <<", " << std::get<1>(move) << ") " << "Score: " << score << std::endl;
        best_score = (Score)optimiser(score, best_score);
        if (score == best_score) {
            best_move = move;
        }
        board.unmarkBoard(move);
    }
    return best_move;
}

std::tuple<int, int> MinimaxTicTacToe::getUserInput(const Player &curr_player, const Player &next_player) {

    if (curr_player.getMarker() == PLAYER_MIN.getMarker()) {
        return getBestMove(curr_player, next_player);
    }

    getBestMove(curr_player, next_player);
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

void MinimaxTicTacToe::play() {
    std::tuple<int, int> move;
    Score end_score;
    Player prev_player = PLAYER_MIN;
    Player curr_player = PLAYER_MAX;

    showBoard();

    while (true) {
        move = getUserInput(curr_player, prev_player);
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






