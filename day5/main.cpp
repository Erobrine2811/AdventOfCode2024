#include <fstream>
#include <iostream>
#include <set>
using namespace std;

void read_file(string filename, vector<vector<int>> *updates,
               set<tuple<int, int>> *rules) {
  fstream inputFile;
  inputFile.open(filename);
  if (!inputFile.is_open()) {
    return;
  }
  string line;
  bool rulesReading = true;
  while (getline(inputFile, line)) {
    if (line == "") {
      rulesReading = false;
      continue;
    }
    if (rulesReading) {
      int index = line.find('|');
      int first = stoi(line.substr(0, index));
      int second = stoi(line.substr(index + 1, line.length()));
      tuple<int, int> rule = {first, second};
      rules->insert(rule);
    } else {
      int pos = 0;
      vector<int> pages = {};
      while ((pos = line.find(',')) != std::string::npos) {
        pages.push_back(stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);
      }
      pages.push_back(stoi(line.substr(pos + 1, line.length())));
      updates->push_back(pages);
    }
  }
}

bool updateIsValid(vector<int> update, set<tuple<int, int>> rules) {
  for (int i = 0; i < update.size() - 1; i++) {
    for (int j = i + 1; j < update.size(); j++) {
      tuple<int, int> pagePair = {update.at(i), update.at(j)};

      if (rules.count({get<1>(pagePair), get<0>(pagePair)})) {
        return false;
      }
    }
  }
  return true;
}

int part1() {
  vector<vector<int>> updates = {};
  set<tuple<int, int>> rules = {};
  read_file("input.txt", &updates, &rules);
  int count = 0;
  for (vector<int> update : updates) {
    if (updateIsValid(update, rules)) {
      count += update.at(update.size() / 2);
    }
  }
  return count;
}

void fixUpdate(vector<int> *update, set<tuple<int, int>> rules) {
  while (!updateIsValid(*update, rules)) {
    for (int i = 0; i < update->size() - 1; i++) {
      for (int j = i + 1; j < update->size(); j++) {
        tuple<int, int> pagePair = {update->at(i), update->at(j)};
        if (rules.count({get<1>(pagePair), get<0>(pagePair)})) {
          int tmp = update->at(i);
          update->at(i) = update->at(j);
          update->at(j) = tmp;
        }
      }
    }
  }
}

int part2() {
  vector<vector<int>> updates = {};
  set<tuple<int, int>> rules = {};
  read_file("input.txt", &updates, &rules);
  int count = 0;
  for (vector<int> update : updates) {
    if (!updateIsValid(update, rules)) {
      fixUpdate(&update, rules);
      count += update.at(update.size() / 2);
    }
  }
  return count;
}

int main() {
  cout << "Part 1: " << part1() << endl;
  cout << "Part 2: " << part2() << endl;
}
