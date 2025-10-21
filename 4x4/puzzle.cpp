#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool is_solution(const vector<int>& board) {
    for (int i = 0; i < 15; ++i) {
        if (board[i] != i + 1) return false;
    }
    return board[15] == 0;
}

vector<int> read_board(const string& filename) {
    ifstream fin(filename);
    vector<int> board;
    int val;
    while (fin >> val) {
        board.push_back(val);
    }
    return board;
}

void check_file(const string& filename) {
    auto board = read_board(filename);
    if (board.size() != 16) {
        cout << filename << ": Formato non valido\n";
        return;
    }
    if (is_solution(board)) {
        cout << filename << ": Soluzione corretta\n";
    } else {
        cout << filename << ": Non è la soluzione\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: puzzle file1.txt [file2.txt ...]\n";
        return 1;
    }
    for (int i = 1; i < argc; ++i) {
        check_file(argv[i]);
    }
    return 0;
}