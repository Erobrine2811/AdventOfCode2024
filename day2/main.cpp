#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void read_file(string filename, vector<vector<int>> *reports) {
  fstream inputFile;
  inputFile.open(filename);
  if (!inputFile.is_open()) {
    return;
  }
  string line;
  while (getline(inputFile, line)) {
    if (line.length() == 0) {
      continue;
    }
    string numAsString;
    istringstream stream{line};
    vector<int> report = {};
    while (getline(stream, numAsString, ' ')) {
      report.push_back(stoi(numAsString));
    }
    reports->push_back(report);
  }
}

bool isSafe(vector<int> report) {
  bool descending = false;
  bool ascending = false;
  bool isSafe = true;
  for (int j = 0; j < report.size() - 1; j++) {
    int num = report[j];
    int nextNum = report[j + 1];
    int diff = nextNum - num;
    if (diff == 0) {
      isSafe = false;
      break;
    }

    if (abs(diff) > 3) {
      isSafe = false;
      break;
    }
    if (diff > 0) {
      ascending = true;
      if (descending) {
        isSafe = false;
        break;
      }
    } else if (diff < 0) {
      descending = true;
      if (ascending) {
        isSafe = false;
        break;
      }
    }
  }
  return isSafe;
}

int part1() {
  vector<vector<int>> reports = {};
  read_file("input.txt", &reports);
  int safe = 0;
  for (int i = 0; i < reports.size(); i++) {
    if (isSafe(reports[i])) {
      safe++;
    }
  }
  return safe;
}

bool isAdvancedSafe(vector<int> report) {
  for (int i = 0; i < report.size(); i++) {
    vector<int> copy(report);
    copy.erase(copy.begin() + i);
    if (isSafe(copy)) {
      return true;
    }
  }
  return false;
}

int part2() {
  vector<vector<int>> reports = {};
  read_file("input.txt", &reports);
  int safe = 0;
  for (int i = 0; i < reports.size(); i++) {
    if (isSafe(reports[i])) {
      safe++;
    } else if (isAdvancedSafe(reports[i])) {
      safe++;
    }
  }
  return safe;
}

int main() {
  std::cout << "Part 1: " << part1() << std::endl;
  std::cout << "Part 2: " << part2() << std::endl;
}
