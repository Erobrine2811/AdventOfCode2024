#include <fstream>
#include <iostream>
using namespace std;

void read_file(string filename, vector<string> *lines) {
  fstream inputFile;
  inputFile.open(filename);
  if (!inputFile.is_open()) {
    return;
  }
  string line;
  while (getline(inputFile, line)) {
    lines->push_back(line);
  }
}

void canExpand(int x, int y, int *count, vector<vector<int>> directions,
               vector<string> lines) {
  string word = "XMAS";
  for (vector<int> direction : directions) {
    bool found = true;
    for (int i = 1; i < word.size(); i++) {
      if (lines[y + direction[1] * i][x + direction[0] * i] != word[i]) {
        found = false;
        break;
      }
    }
    if (found) {
      (*count)++;
    }
  }
}

void getPossibleNodes(int x, int y, vector<vector<int>> *directions,
                      vector<string> lines) {
  if (x + 3 < lines[0].size()) {
    directions->push_back({1, 0});
  }
  if (y + 3 < lines.size()) {
    directions->push_back({0, 1});
  }
  if (x - 3 >= 0) {
    directions->push_back({-1, 0});
  }
  if (y - 3 >= 0) {
    directions->push_back({0, -1});
  }
  if (x + 3 < lines[0].size() && y + 3 < lines.size()) {
    directions->push_back({1, 1});
  }
  if (x - 3 >= 0 && y - 3 >= 0) {
    directions->push_back({-1, -1});
  }
  if (x + 3 < lines[0].size() && y - 3 >= 0) {
    directions->push_back({1, -1});
  }
  if (x - 3 >= 0 && y + 3 < lines.size()) {
    directions->push_back({-1, 1});
  }
}

int part1() {
  vector<string> lines = {};
  read_file("input.txt", &lines);
  int count = 0;
  for (int y = 0; y < lines.size(); y++) {
    string line = lines[y];
    for (int x = 0; x < line.size(); x++) {
      char c = line[x];
      if (c == 'X') {
        vector<vector<int>> directions = {};
        getPossibleNodes(x, y, &directions, lines);
        canExpand(x, y, &count, directions, lines);
      }
    }
  }
  return count;
}

bool doesContainX(int x, int y, vector<string> lines) {
  if (0 < x && x + 1 < lines[0].size() && 0 < y && y + 1 < lines.size()) {
    if ((lines[y - 1][x - 1] != 'M' || lines[y + 1][x + 1] != 'S') &&
        (lines[y - 1][x - 1] != 'S' || lines[y + 1][x + 1] != 'M')) {
      return false;
    }
    if ((lines[y + 1][x - 1] != 'M' || lines[y - 1][x + 1] != 'S') &&
        (lines[y + 1][x - 1] != 'S' || lines[y - 1][x + 1] != 'M')) {
      return false;
    }
    return true;
  }
  return false;
}

int part2() {
  vector<string> lines = {};
  read_file("input.txt", &lines);
  int count = 0;
  for (int y = 0; y < lines.size(); y++) {
    string line = lines[y];
    for (int x = 0; x < line.size(); x++) {
      char c = line[x];
      if (c == 'A') {
        if (doesContainX(x, y, lines)) {
          count++;
        }
      }
    }
  }
  return count;
}

int main() {
  cout << "Part 1: " << part1() << endl;
  cout << "Part 2: " << part2() << endl;
}
