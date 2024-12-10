#include <fstream>
#include <iostream>
using namespace std;

void read_2d_array(std::string filename, std::vector<std::vector<char>> *array,
                   unordered_map<char, vector<tuple<int, int>>> *antenas) {

  std::ifstream inputFile;
  inputFile.open(filename);
  if (!inputFile.is_open()) {
    return;
  }
  std::string line;
  int y = 0;
  while (getline(inputFile, line)) {
    std::vector<char> row = {};
    for (int x = 0; x < line.size(); x++) {
      char c = line.at(x);
      if (c != '.') {
        if (antenas->find(c) == antenas->end()) {
          antenas->insert({c, {{x, y}}});
        } else {
          antenas->at(c).push_back({x, y});
        }
      }
      row.push_back(c);
    }
    array->push_back(row);
    y++;
  }
}

bool is_out(vector<vector<char>> map, int x, int y) {
  return x < 0 || y < 0 || y >= map.size() || x >= map.at(y).size();
}

char get_char(vector<vector<char>> map, int x, int y) {
  return map.at(y).at(x);
}

void solve1(vector<vector<char>> *map,
            unordered_map<char, vector<tuple<int, int>>> antenas) {
  for (auto antena : antenas) {
    char c = antena.first;
    for (int i = 0; i < antena.second.size() - 1; i++) {
      for (int j = i + 1; j < antena.second.size(); j++) {
        int x1 = get<0>(antena.second.at(i));
        int y1 = get<1>(antena.second.at(i));
        int x2 = get<0>(antena.second.at(j));
        int y2 = get<1>(antena.second.at(j));
        int dx = x2 - x1;
        int dy = y2 - y1;
        if (!is_out(*map, dx + x2, dy + y2)) {
          char c1 = get_char(*map, dx + x2, dy + y2);
          map->at(dy + y2)[dx + x2] = '#';
        }
        if (!is_out(*map, x1 - dx, y1 - dy)) {
          map->at(y1 - dy)[x1 - dx] = '#';
        }
      }
    }
  }
}

void solve2(vector<vector<char>> *map,
            unordered_map<char, vector<tuple<int, int>>> antenas) {
  for (auto antena : antenas) {
    char c = antena.first;
    for (int i = 0; i < antena.second.size() - 1; i++) {
      for (int j = i + 1; j < antena.second.size(); j++) {
        int x1 = get<0>(antena.second.at(i));
        int y1 = get<1>(antena.second.at(i));
        int x2 = get<0>(antena.second.at(j));
        int y2 = get<1>(antena.second.at(j));
        int dx = x2 - x1;
        int dy = y2 - y1;
        int origdx = dx;
        int origdy = dy;
        while (!is_out(*map, dx + x2, dy + y2)) {
          map->at(dy + y2)[dx + x2] = '#';
          dx += origdx;
          dy += origdy;
        }
        dx = origdx;
        dy = origdy;
        while (!is_out(*map, x1 - dx, y1 - dy)) {
          map->at(y1 - dy)[x1 - dx] = '#';
          dx += origdx;
          dy += origdy;
        }
      }
    }
  }
}

int part1() {
  unordered_map<char, vector<tuple<int, int>>> antenas;
  vector<vector<char>> map = {};
  read_2d_array("input.txt", &map, &antenas);
  solve1(&map, antenas);
  int count = 0;
  for (auto row : map) {
    for (char c : row) {
      if (c == '#') {
        count++;
      }
    }
  }

  return count;
}

int part2() {
  unordered_map<char, vector<tuple<int, int>>> antenas;
  vector<vector<char>> map = {};
  read_2d_array("input.txt", &map, &antenas);
  solve2(&map, antenas);
  int count = 0;
  for (auto row : map) {
    for (char c : row) {
      if (c != '.') {
        count++;
      }
    }
  }

  return count;
}

int main() {
  cout << "Part 1: " << part1() << endl;
  cout << "Part 2: " << part2() << endl;
}
