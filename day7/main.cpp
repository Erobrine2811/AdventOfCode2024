#include <fstream>
#include <iostream>
#include <string>
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

void split(std::string str, std::string delimiter,
           std::vector<std::string> *result) {
  size_t pos = 0;
  while ((pos = str.find(delimiter)) != std::string::npos) {
    result->push_back(str.substr(0, pos));
    str.erase(0, pos + delimiter.length());
  }
  result->push_back(str);
}

long calculate(string operators, vector<int> nums) {
  long sum = nums[0];
  string sum_s = "";
  for (int i = 0; i < operators.size(); i++) {
    if (operators[i] == '+') {
      sum += nums[i + 1];
    } else if (operators[i] == '*') {
      sum *= nums[i + 1];
    } else {
      sum_s = to_string(sum);
      sum = stol(sum_s + to_string(nums[i + 1]));
    }
  }
  return sum;
}

bool recursion(string operators, int i, vector<int> nums, long res,
               bool part2) {
  long calc = calculate(operators, nums);
  if (i == operators.size()) {
    return calc == res;
  }
  operators[i] = '+';
  if (recursion(operators, i + 1, nums, res, part2)) {
    return true;
  }
  operators[i] = '*';
  if (recursion(operators, i + 1, nums, res, part2)) {
    return true;
  }
  if (part2) {
    operators[i] = '|';
    if (recursion(operators, i + 1, nums, res, part2)) {
      return true;
    }
  }
  return false;
}

bool is_valid(vector<int> nums, long res, bool part2) {
  string operators = "";
  for (int i = 0; i < nums.size() - 1; i++) {
    operators += '+';
  }
  if (recursion(operators, 0, nums, res, part2)) {
    return true;
  }
  return false;
}

long long part1() {
  vector<string> calibrations = {};
  read_file("input.txt", &calibrations);
  long long count = 0;
  int i = 0;
  for (string calibration : calibrations) {
    vector<string> parts = {};
    split(calibration, ": ", &parts);
    long res = stol(parts[0]);
    vector<string> nums_as_s = {};
    split(parts[1], " ", &nums_as_s);
    vector<int> nums = {};
    for (string num : nums_as_s) {
      nums.push_back(stoi(num));
    }
    if (is_valid(nums, res, false)) {
      count += res;
    }
  }
  return count;
}

long long part2() {
  vector<string> calibrations = {};
  read_file("input.txt", &calibrations);
  long long count = 0;
  int i = 0;
  for (string calibration : calibrations) {
    vector<string> parts = {};
    split(calibration, ": ", &parts);
    long res = stol(parts[0]);
    vector<string> nums_as_s = {};
    split(parts[1], " ", &nums_as_s);
    vector<int> nums = {};
    for (string num : nums_as_s) {
      nums.push_back(stoi(num));
    }
    if (is_valid(nums, res, true)) {
      count += res;
    }
  }
  return count;
}

int main() {
  cout << "Part 1: " << part1() << endl;
  cout << "Part 2: " << part2() << endl;
}
