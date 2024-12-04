#include <fstream>
#include <iostream>
#include <regex>
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

int part1() {
  vector<string> lines = {};
  read_file("input.txt", &lines);
  smatch match;
  regex e(R"(mul\((\d+),(\d+)\))");
  int sum = 0;
  for (string line : lines) {
    while (regex_search(line, match, e)) {
      int num1 = stoi(match[1].str());
      int num2 = stoi(match[2].str());
      sum += num1 * num2;
      line = match.suffix().str();
    }
  }
  return sum;
}

int part2() {
  vector<string> lines = {};
  read_file("input.txt", &lines);
  smatch match;
  int sum = 0;
  regex e(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
  bool enabled = true;
  for (string line : lines) {
    while (regex_search(line, match, e)) {
      if (match.str() == "do()") {
        enabled = true;
      } else if (match.str() == "don't()") {
        enabled = false;
      } else if (enabled) {
        int num1 = stoi(match[1].str());
        int num2 = stoi(match[2].str());
        sum += num1 * num2;
      }
      line = match.suffix().str();
    }
  }
  return sum;
}

int main() {
  cout << "Part 1: " << part1() << endl;
  cout << "Part 2: " << part2() << endl;
}
