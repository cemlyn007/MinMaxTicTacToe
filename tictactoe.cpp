#include <iostream>
#include <vector>
#include <tuple>


class TicTacToe
{
public:

	int m;
	int n;
	int k;
	int BLANK = 0;
	int MAX = 1;
	int MIN = -1;
	std::vector<std::vector <int>> board;

	TicTacToe(int row, int col, int length)
	{
		m = row;
		n = col;
		k = length;
		std::cout << "Playing TicTacToe: " << m << "x" << n << std::endl;
		board = create_board(m, n);
	}

	std::vector<std::vector <int>> create_board(const int m, const int n)
	{
		std::vector<std::vector<int>> board;
		for (int i = 0; i < m; i++) {
			std::vector<int> temp(n, 0);
			board.push_back(temp);
		}
		return board;
	}

	void print_board()
	{
		char marker;
		std::cout << "Printing board" << std::endl;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				switch (board[i][j]) {
				case -1:
					marker = 'X';
					break;
				case 0:
					marker = '_';
					break;
				case 1:
					marker = 'O';
					break;
				default:
					marker = '?';
					break;
				}
				std::cout << marker << " ";
			}
			std::cout << std::endl;
		}
	}

	void mark_board(int i, int j, int marker)
	{
		if (board[i][j] == BLANK) {
			board[i][j] = marker;
		}
		else {
			throw; // Wanted to mark somewhere that is already marked... (mistake was made)
		}

	}

	void unmark_board(int i, int j)
	{
		board[i][j] = BLANK;
	}

	int end_test(int marker)
	{
		if (no_spaces()) {
			// All spaces are occupied
			return -1;
		}
		else if (check_win(marker)) {
			// This marker has won
			return 1;
		}
		else {
			// Game stil in play
			return 0;
		}

	}

	bool no_spaces()
	{
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (board[i][j] == 0) {
					return false;
				}
			}
		}
		return true;
	}

	bool check_verts(int marker)
	{
		// check when you have a brain
		for (int i = 0; i < n; i++) {
			int chain_length = 0;
			for (int j = 0; j < m; j++) {
				if (board[j][i] == marker) {
					chain_length++;
				}
				else {
					chain_length = 0;
				}
				if (chain_length == k) {
					return true;
				}
			}
		}
		return false;
	}

	bool check_horiz(int marker)
	{
		for (int i = 0; i < m; i++) {
			int chain_length = 0;
			for (int j = 0; j < n; j++) {
				if (board[i][j] == marker) {
					chain_length++;
				}
				else {
					chain_length = 0;
				}
				if (chain_length == k) {
					return true;
				}
			}
		}
		return false;
	}

	bool check_diag(int marker, int direction)
	{
		for (int c = -m; c < m; c++) {
			int chain_length = 0;
			for (int i = 0; i < n; i++) {
				if (0 <= direction * i + c && direction * i + c < m && 0 <= i && i < n) {
					if (board[direction * i + c][i] == marker) {
						chain_length++;
					}
					else {
						chain_length = 0;
					}
				}
				else {
					chain_length = 0;
				}
			}
			if (chain_length == k) {
				return true;
			}
		}
		return false;
	}

	bool check_win(int marker)
	{
		if (check_verts(marker) || check_horiz(marker)) {
			return true;
		}
		else if (check_diag(marker, 1) || check_diag(marker, -1)) {
			return true;
		}
		else {
			return false;
		}
	}

	std::tuple<int, int> get_user_input()
	{
		int a, b;
		std::cout << "Please input move: ";
		std::cin >> a >> b;
		std::cout << "Recieved: " << "(" << a << "," << b << ")" << std::endl;
		return std::tuple<int, int>{a, b};
	}

	void play()
	{
		std::tuple<int, int> move;
		bool game_over = false;

		int prev_player = MIN;
		int curr_player = MAX;

		print_board();

		do
		{
			move = get_user_input();
			mark_board(std::get<0>(move), std::get<1>(move), curr_player);
			print_board();
			std::swap(curr_player, prev_player);
			switch (end_test(prev_player))
			{
			case -1:
				std::cout << "Draw" << std::endl;
				game_over = true;
				break;
			case 0:
				std::cout << "Player: " << curr_player << std::endl;
				break;
			case 1:
				std::cout << "WON!" << std::endl;
				game_over = true;
				break;
			}
		} while (not(game_over));
	}
};



int main()
{
	// const int m = 3;
	// const int n = 3;

	TicTacToe game(4, 5, 4);
	game.play();




}
