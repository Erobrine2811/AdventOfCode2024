#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void read_file(string filename, string *line) {
  fstream inputFile;
  inputFile.open(filename);
  if (!inputFile.is_open()) {
    return;
  }
  getline(inputFile, *line);
}

void proccess_line(string line, vector<vector<int>> *system) {
  int fileIndex = 0;
  bool readingFile = true;
  for (int i = 0; i < line.size(); i++) {
    char c = line.at(i);
    if (readingFile) {
      system->push_back({fileIndex, c - '0'});
      fileIndex++;
    } else {
      system->push_back({-1, c - '0'});
    }
    readingFile = !readingFile;
  }
}

void moveList(vector<int> *system) {
  int selected = -1;
  int endSelected = -1;
  int startSelected = -1;
  int startFree = -1;
  int endFree = -1;
  for (int i = system->size() - 1; i > 0; i--) {
    int num = system->at(i);
    if (selected == -1) {
      if (num != -1) {
        selected = num;
        endSelected = i + 1;
      }
      continue;
    }
    if (num == -1 || selected != num) {
      startSelected = i + 1;
      for (int low = 0; low < startSelected; low++) {
        int lowNum = system->at(low);
        if (lowNum == -1 && startFree == -1) {
          startFree = low;
          continue;
        } else if (low - startFree == endSelected - startSelected &&
                   lowNum != -1 && startFree != -1) {
          endFree = low;
          break;
        } else if ((startFree != -1 && lowNum == -1 &&
                    endSelected - startSelected == 1 + low - startFree)) {
          endFree = 1 + low;
          break;
        }
        if (lowNum != -1 && startFree != -1) {
          startFree = -1;
        }
      }
      if (endFree != -1 && endFree - startFree == endSelected - startSelected) {
        for (int j = startSelected; j < endSelected; j++) {
          system->at(j) = -1;
        }
        for (int j = startFree; j < endFree; j++) {
          system->at(j) = selected;
        }
      }
      selected = -1;
      endSelected = -1;
      startSelected = -1;
      startFree = -1;
      endFree = -1;
      i++;
    }
  }
}

long long calculate(vector<int> system) {
  long long count = 0;
  int last = system.size();
  for (int i = 0; i < system.size(); i++) {
    if (i >= last) {
      break;
    }
    if (system.at(i) == -1) {
      for (int end = last - 1; end > i; end--) {
        if (system.at(end) != -1) {
          count += i * system.at(end);
          last = end;
          break;
        }
      }
    } else {
      count += i * system.at(i);
    }
  }
  return count;
}

long long linear_calculate(vector<int> system) {
  long long count = 0;
  for (int i = 0; i < system.size(); i++) {
    if (system.at(i) == -1) {
      continue;
    }
    count += i * system.at(i);
  }
  return count;
}

long long part1() {
  string line;
  read_file("input.txt", &line);
  vector<vector<int>> system = {};
  proccess_line(line, &system);
  vector<int> systemList = {};
  int count = 0;
  for (auto v : system) {
    if (v.at(0) == -1) {
      for (int i = 0; i < v.at(1); i++) {
        systemList.push_back(-1);
      }
    } else {
      for (int i = 0; i < v.at(1); i++) {
        systemList.push_back(v.at(0));
      }
    }
  }
  return calculate(systemList);
}

long long part2() {
  string line;
  read_file("input.txt", &line);
  vector<vector<int>> system = {};
  proccess_line(line, &system);
  vector<int> systemList = {};
  for (auto v : system) {
    if (v.at(0) == -1) {
      for (int i = 0; i < v.at(1); i++) {
        systemList.push_back(-1);
      }
    } else {
      for (int i = 0; i < v.at(1); i++) {
        systemList.push_back(v.at(0));
      }
    }
  }
  moveList(&systemList);
  return linear_calculate(systemList);
}

int main() {
  cout << "Part 1: " << part1() << endl;
  cout << "Part 2: " << part2() << endl;
}
