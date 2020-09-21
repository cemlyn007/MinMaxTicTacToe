//
// Created by cemlyn on 02/07/2020.
//

#include "AlphaBetaPruningMinimaxTicTacToe.h"

#include <utility>

AlphaBetaPruningMinimaxTicTacToe::AlphaBetaPruningMinimaxTicTacToe(int m, int n, int k,
                                                                   Player player1, Player player2) : TicTacToe(m, n, k,
                                                                                                               std::move(
                                                                                                                       player1),
                                                                                                               std::move(
                                                                                                                       player2)) {
}

TicTacToe::Score AlphaBetaPruningMinimaxTicTacToe::getMiniMax(const Player &player, const Player &prev_player,
                                                              int alpha, int beta) {
    TicTacToe::GameState gameState = endTest(prev_player.getMarker());
    if (gameState == TicTacToe::GameState::RUNNING) {
        Score best_score, score;
        Board::Marker marker = player.getMarker();

//        std::cout << "n_options: " << getOptions().size() << std::endl;

        // This code gets the optimiser and sets the initial best score (the worst case)
        if (marker == PLAYER_MAX.getMarker()) {
            best_score = getWorstCaseScore(PLAYER_MAX.getMarker());
            for (std::tuple<int, int> move: getOptions()) {
                board.markBoard(move, player.getMarker());
                score = getMiniMax(prev_player, player, alpha, beta);
                best_score = (Score)(std::max((int) score, (int) best_score));
                alpha = (int)(std::max((int) best_score, alpha));
                board.unmarkBoard(move);
                if (beta <= alpha) { break; }
            }

        } else if (marker == PLAYER_MIN.getMarker()) {
            best_score = getWorstCaseScore(PLAYER_MIN.getMarker());
            for (std::tuple<int, int> move: getOptions()) {
                board.markBoard(move, player.getMarker());
                score = getMiniMax(prev_player, player, alpha, beta);
                best_score = (Score)(std::min((int) score, (int) best_score));
                beta = (int)(std::min((int) best_score, beta));
                board.unmarkBoard(move);
                if (beta <= alpha) { break; }
            }
        }
        return best_score;
    } else if (gameState == TicTacToe::GameState::FINISHED) {
//        showBoard();
        return getScore(prev_player.getMarker());
    }
}

std::tuple<int, int>
AlphaBetaPruningMinimaxTicTacToe::getBestMove(const Player &curr_player, const Player &next_player) {
    std::tuple<int, int> best_move;
    Score best_score, score;
    int alpha, beta;
    std::vector<std::tuple<int, int>> options = getOptions();
    Board::Marker marker = curr_player.getMarker();

    alpha = (int)getScore(PLAYER_MIN.getMarker());
    beta = (int)getScore(PLAYER_MAX.getMarker());

    // This code gets the optimiser and sets the initial best score (the worst case)
    if (marker == PLAYER_MAX.getMarker()) {
        best_score = getWorstCaseScore(PLAYER_MAX.getMarker());
        for (std::tuple<int, int> move: options) {
            board.markBoard(move, curr_player.getMarker());
            score = getMiniMax(next_player, curr_player, alpha, beta);
            board.unmarkBoard(move);
            std::cout << "Move: (" << std::get<0>(move) <<", " << std::get<1>(move) << ") " << "Score: " << score << std::endl;
            best_score = (Score)(std::max((int) score, (int) best_score));
            if (score == best_score) { best_move = move; }
//            alpha = (int)(std::max((int) best_score, (int) alpha));
//            if (beta <= alpha) { break; }
        }

    } else if (marker == PLAYER_MIN.getMarker()) {
        best_score = getWorstCaseScore(PLAYER_MIN.getMarker());
        for (std::tuple<int, int> move: options) {
            board.markBoard(move, curr_player.getMarker());
            score = getMiniMax(next_player, curr_player, alpha, beta);
            board.unmarkBoard(move);
            std::cout << "Move: (" << std::get<0>(move) <<", " << std::get<1>(move) << ") " << "Score: " << score << std::endl;
            best_score = (Score)(std::min((int) score, (int) best_score));
            if (score == best_score) { best_move = move; }
//            beta = (int)(std::min((int) best_score, (int) beta));
//            if (beta <= alpha) { break; }
        }
    }
    return best_move;
}

std::tuple<int, int>
AlphaBetaPruningMinimaxTicTacToe::getUserInput(const Player &curr_player, const Player &next_player) {

    if (curr_player.getMarker() == PLAYER_MIN.getMarker()) {
        std::tuple<int, int> move(getBestMove(curr_player, next_player));
//        showBoard();
        return move;
    }

    getBestMove(curr_player, next_player);

//    showBoard();

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

void AlphaBetaPruningMinimaxTicTacToe::play() {
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






