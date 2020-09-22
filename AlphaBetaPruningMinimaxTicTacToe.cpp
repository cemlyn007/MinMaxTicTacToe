//
// Created by cemlyn on 02/07/2020.
//

#include "AlphaBetaPruningMinimaxTicTacToe.h"

#include <utility>
#include <future>

AlphaBetaPruningMinimaxTicTacToe::AlphaBetaPruningMinimaxTicTacToe(int m, int n, int k,
                                                                   Player player1, Player player2) : TicTacToe(m, n, k,
                                                                                                               std::move(
                                                                                                                       player1),
                                                                                                               std::move(
                                                                                                                       player2)) {
}

Score AlphaBetaPruningMinimaxTicTacToe::getMiniMax(Board &board, const Player &player, const Player &prev_player,
                                                   int alpha, int beta) {
    GameState gameState = endTest(board, prev_player.getMarker());
    if (gameState == GameState::RUNNING) {
        Score best_score, score;
        Board::Marker marker = player.getMarker();
        if (marker == PLAYER_MAX.getMarker()) {
            best_score = getWorstCaseScore(PLAYER_MAX.getMarker());
            for (std::tuple<int, int> move: getOptions(board)) {
                board.markBoard(move, player.getMarker());
                score = getMiniMax(board, prev_player, player, alpha, beta);
                board.unmarkBoard(move);
                best_score = (Score) (std::max((int) score, (int) best_score));
                alpha = (int) (std::max((int) best_score, alpha));
                if (beta <= alpha) { break; }
            }
            return best_score;
        } else if (marker == PLAYER_MIN.getMarker()) {
            best_score = getWorstCaseScore(PLAYER_MIN.getMarker());
            for (std::tuple<int, int> move: getOptions(board)) {
                board.markBoard(move, player.getMarker());
                score = getMiniMax(board, prev_player, player, alpha, beta);
                board.unmarkBoard(move);
                best_score = (Score) (std::min((int) score, (int) best_score));
                beta = (int) (std::min((int) best_score, beta));
                if (beta <= alpha) { break; }
            }
            return best_score;
        }
    } else if (gameState == GameState::FINISHED) {
        return getScore(board, prev_player.getMarker());
    }
}

std::tuple<int, int>
AlphaBetaPruningMinimaxTicTacToe::getBestMove(const Player &curr_player, const Player &next_player) {
    std::vector<std::future<Score>> jobs;
    std::tuple<int, int> best_move;
    Score best_score, score;
    std::vector<std::tuple<int, int>> options = getOptions(main_board);
    Board::Marker marker = curr_player.getMarker();

//    // Fill boards
//    std::vector<Board> boards;
//    for (int i = 0; i < options.size(); ++i) {
//        boards.push_back(getMainBoard());
//    }

    if (marker == PLAYER_MAX.getMarker()) {
        best_score = getWorstCaseScore(PLAYER_MAX.getMarker());
        for (std::tuple<int, int> move: options) {
            Board board = getMainBoard();
            jobs.push_back(std::async(&AlphaBetaPruningMinimaxTicTacToe::getMiniMaxOfOption,
                                      this, move, std::ref(curr_player), std::ref(next_player)));
        }
        for (int i = 0; i < options.size(); i++) {
            std::tuple<int, int> move = options[i];
            auto job = &jobs[i];
            score = job->get();
            std::cout << "Move: (" << std::get<0>(move) << ", " << std::get<1>(move) << ") " << "Score: " << score
                      << std::endl;
            best_score = (Score) (std::max((int) score, (int) best_score));
            if (score == best_score) { best_move = move; }
        }

    } else if (marker == PLAYER_MIN.getMarker()) {
        best_score = getWorstCaseScore(PLAYER_MIN.getMarker());
        for (std::tuple<int, int> move: options) {
            Board board = getMainBoard();
            jobs.push_back(std::async(&AlphaBetaPruningMinimaxTicTacToe::getMiniMaxOfOption,
                                      this, move, std::ref(curr_player), std::ref(next_player)));
        }
        for (int i = 0; i < options.size(); i++) {
            std::tuple<int, int> move = options[i];
            auto job = &jobs[i];
            score = job->get();
            std::cout << "Move: (" << std::get<0>(move) << ", " << std::get<1>(move) << ") " << "Score: " << score
                      << std::endl;
            best_score = (Score) (std::min((int) score, (int) best_score));
            if (score == best_score) { best_move = move; }
        }
    }
    return best_move;
}


std::tuple<int, int>
AlphaBetaPruningMinimaxTicTacToe::getUserInput(const Player &curr_player, const Player &next_player) {
    if (curr_player.getMarker() == PLAYER_MIN.getMarker()) {
        std::tuple<int, int> move(getBestMove(curr_player, next_player));
        return move;
    }
    getBestMove(curr_player, next_player);
    static int a, b;
    if (main_board.screen == Board::ON) {
        std::tuple<int, int> mouse_position = main_board.getMousePosition();
        int pos_x = std::get<0>(mouse_position);
        int pos_y = std::get<1>(mouse_position);
        return main_board.getCell(pos_x, pos_y);
    } else if (main_board.screen == Board::CONSOLE) {
        std::cout << "Please input move: ";
        std::cin >> a >> b;
        std::cout << "Received: " << "(" << a << "," << b << ")" << std::endl;
        return std::tuple<int, int>{a, b};
    } else {
        throw;
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
        main_board.markBoard(std::get<0>(move), std::get<1>(move), curr_player.getMarker());
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

Score AlphaBetaPruningMinimaxTicTacToe::getMiniMaxOfOption(std::tuple<int, int> option,
                                                           const Player &curr_player, const Player &next_player) {
    int alpha = (int) getScore(PLAYER_MIN.getMarker());
    int beta = (int) getScore(PLAYER_MAX.getMarker());
    Board board = getMainBoard();
    board.markBoard(option, curr_player.marker);
    Score score = getMiniMax(board, next_player, curr_player, alpha, beta);
    board.unmarkBoard(option);
    return score;
}







