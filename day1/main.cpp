#include <fstream>
#include <iostream>

void read_from_file(std::vector<int> *left_data,
                    std::unordered_map<int, int> *right_data) {
  std::fstream inputFile;
  inputFile.open("input.txt");
  std::string line;

  int left_num;
  int right_num;
  for (int i = 0; i < 1000; i++) {
    inputFile >> left_num;
    left_data->push_back(left_num);
    inputFile >> right_num;
    if (right_data->count(right_num)) {
      right_data->at(right_num)++;
    } else {
      right_data->insert(std::make_pair(right_num, 1));
    }
  }
  inputFile.close();
}

void read_from_file(std::vector<int> *left_data, std::vector<int> *right_data) {
  std::fstream inputFile;
  inputFile.open("input.txt");
  std::string line;

  int left = true;
  int left_num;
  int right_num;
  for (int i = 0; i < 1000; i++) {
    inputFile >> left_num;
    left_data->push_back(left_num);
    inputFile >> right_num;
    right_data->push_back(right_num);
  }
  inputFile.close();
}

int part1() {
  std::vector<int> left_data;
  std::vector<int> right_data;
  read_from_file(&left_data, &right_data);
  sort(left_data.begin(), left_data.end());
  sort(right_data.begin(), right_data.end());
  int distance = 0;
  for (int i = 0; i < 1000; i++) {
    distance += abs(right_data[i] - left_data[i]);
  }
  return distance;
}

int part2() {
  std::vector<int> left_data;
  std::unordered_map<int, int> right_data;
  read_from_file(&left_data, &right_data);
  sort(left_data.begin(), left_data.end());
  int distance = 0;
  for (int i = 0; i < 1000; i++) {
    int num = left_data[i];
    if (right_data.count(num)) {
      distance += num * right_data.at(num);
    }
  }
  return distance;
}

int main() {
  std::cout << "Part 1: " << part1() << std::endl;
  std::cout << "Part 2: " << part2() << std::endl;
  return 0;
}
