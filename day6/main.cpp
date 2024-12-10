#include <fstream>
#include <iostream>
#include <set>
using namespace std;

class Pos {
private:
  tuple<int, int> dir;
  tuple<int, int> coords;

public:
  Pos() : dir({0, 1}), coords({0, 0}) {}
  tuple<int, int> getDir() { return dir; }
  tuple<int, int> getCoords() { return coords; }
  void setDir(tuple<int, int> dir) { this->dir = dir; }
  void setCoords(tuple<int, int> coords) { this->coords = coords; }
  void rotate() {
    int dx = get<0>(dir);
    int dy = get<1>(dir);
    if (dx == 1) {
      dir = {0, 1};
    } else if (dy == 1) {
      dir = {-1, 0};
    } else if (dx == -1) {
      dir = {0, -1};
    } else if (dy == -1) {
      dir = {1, 0};
    }
  }

  void log() {
    cout << "Direction: (" << get<0>(dir) << ", " << get<1>(dir) << ")" << endl;
    cout << "Coords: (" << get<0>(coords) << ", " << get<1>(coords) << ")"
         << endl;
  }

  bool isAtEdge(vector<vector<char>> map) {
    return get<0>(coords) == 0 ||
           get<0>(coords) + 1 == map.at(0).size() && get<1>(coords) == 0 ||
           get<1>(coords) + 1 == map.size();
  }

  bool canMove(vector<vector<char>> map) {
    return map.at(get<1>(coords) + get<1>(dir))
               .at(get<0>(coords) + get<0>(dir)) != '#';
  }

  void move() {
    coords = {get<0>(coords) + get<0>(dir), get<1>(coords) + get<1>(dir)};
  }
};

class Map {
private:
  vector<vector<char>> grid;
  Pos start;
  vector<Pos> visited = {};

public:
  Map() : grid({}), start() {}
  vector<vector<char>> getGrid() { return grid; }
  Pos getStart() { return start; }
  void setGrid(vector<vector<char>> grid) { this->grid = grid; }
  void setStart(Pos start) { this->start = start; }
  int width() { return grid.at(0).size(); }
  int height() { return grid.size(); }
  void populate(tuple<int, int> coords) {
    grid.at(get<1>(coords)).at(get<0>(coords)) = 'X';
  }
  void addRow(vector<char> row) {
    grid.push_back(vector<char>(row.begin(), row.end()));
  }
  void visit(Pos p) { this->visited.push_back(p); }
  vector<Pos> getVisited() { return visited; }
  char at(int x, int y) { return grid.at(y).at(x); }
  bool inVisited(Pos p) {
    for (auto v : visited) {
      if (v.getCoords() == p.getCoords() && v.getDir() == p.getDir()) {
        return true;
      }
    }
    return false;
  }
  int getHashTags() {
    int s = 0;
    for (int y = 0; y < this->height(); y++) {
      for (int x = 0; x < this->width(); x++) {
        if (this->at(x, y) == '#') {
          s++;
        }
      }
    }
    return s;
  }
};

vector<int> getDir(char c) {
  switch (c) {
  case '<':
    return {-1, 0};

  case '>':
    return {1, 0};

  case '^':
    return {0, -1};

  case 'v':
    return {0, 1};
  }
  return {};
}

void read_2d_array(std::string filename, Map *map) {
  ifstream inputFile;
  inputFile.open(filename);
  if (!inputFile.is_open()) {
    return;
  }
  string line;
  vector<vector<char>> grid = {};
  int y = 0;
  while (getline(inputFile, line)) {
    vector<char> row = {};
    for (int i = 0; i < line.size(); i++) {
      if (line.at(i) == '<' || line.at(i) == '>' || line.at(i) == 'v' ||
          line.at(i) == '^') {
        vector<int> dir = getDir(line.at(i));
        Pos start;
        start.setDir({dir.at(0), dir.at(1)});
        start.setCoords({i, y});
        map->setStart(start);
      }
      row.push_back(line.at(i));
    }
    map->addRow(row);
    y++;
  }
}

void solve1(Map *map) {
  Pos p = map->getStart();
  while (!p.isAtEdge(map->getGrid())) {
    if (!p.canMove(map->getGrid())) {
      p.rotate();
    }
    p.move();
    map->populate(p.getCoords());
  }
}

int part1() {
  Map map = {};
  read_2d_array("input.txt", &map);
  solve1(&map);
  int count = 0;
  return count;
}

bool isFewOf(Map map, Pos p) {
  p.rotate();
  int i = 0;
  while (!p.isAtEdge(map.getGrid())) {
    if (!map.inVisited(p)) {
      p.move();
    } else {
      return true;
    }
  }
  return false;
}

void solve2(Map *map) {
  Pos p = map->getStart();
  while (!p.isAtEdge(map->getGrid())) {
    if (!p.canMove(map->getGrid())) {
      p.rotate();
    }
    p.log();
    p.move();
    Pos clone = p;
    clone.log();
    cout << 'a' << endl;
    map->visit(clone);
  }
}

int part2() {
  Map map = {};
  read_2d_array("input.txt", &map);
  solve2(&map);
  for (auto v : map.getVisited()) {
    v.log();
  }
}

int main() {
  cout << "Part 1: " << part1() << endl;
  cout << "Part 2: " << part2() << endl;
}
