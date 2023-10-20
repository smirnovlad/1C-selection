#include <assert.h>
#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>
#include "fft.h"
#include <algorithm>
#include <unordered_set>

namespace fs = std::filesystem;

size_t get_max_common_chars_count(const std::string& text, const std::string& pattern) {
    size_t n = text.size();
    size_t m = pattern.size();
    std::vector<size_t> common_chars_count(text.size() - pattern.size() + 1, 0);
    for (char c{' '}; c <= '~'; ++c) {
        std::vector<int32_t> R(n);
        for (int32_t i = 0; i < n; ++i) {
            R[i] = (text[i] == c);
        }
        std::vector<int32_t> S(m);
        for (int32_t i = 0; i < m; ++i) {
            S[i] = (pattern[m - 1 - i] == c);
        }

        uint32_t deg = 1;
        while (deg <= n + m) {
            deg *= 2;
        }

        R.resize(deg);
        for (uint32_t i = n; i < deg; ++i) {
            R[i] = 0;
        }

        S.resize(deg);
        for (uint32_t i = m; i < deg; ++i) {
            S[i] = 0;
        }

        std::vector<int32_t> res(deg, 0);
        FFT::multiply(R, S, res);

        for (size_t i = 0; i < common_chars_count.size(); ++i) {
            common_chars_count[i] += res[pattern.size() - 1 + i];
        }

    }
    size_t result = 0;
    for (auto count: common_chars_count) {
        result = std::max(result, count);
    }
    return result;
}

void get_files_in_directory(char* dir_path, std::vector<std::basic_string<char>>& file_paths) {
    for (const auto& entry : fs::directory_iterator(dir_path)) {
        if (entry.is_regular_file()) {
            file_paths.push_back(entry.path().string());
        }
    }
}

std::string read_data_from_file(std::basic_string<char>& file_path) {
    std::ifstream fin;
    fin.open(file_path);
    size_t file_size = fs::file_size(file_path);
    std::string file_data(file_size, '\0');
    fin.read(&file_data[0], file_size);
    fin.close();
    return file_data;
}

void solve(char* dir_1_path, char* dir_2_path, double percent) {
    assert(fs::is_directory(dir_1_path));
    assert(fs::is_directory(dir_2_path));

    std::vector<std::basic_string<char>> dir_1_file_paths;
    std::vector<std::basic_string<char>> dir_2_file_paths;

    get_files_in_directory(dir_1_path, dir_1_file_paths);
    get_files_in_directory(dir_2_path, dir_2_file_paths);

    struct PairOfFiles {
        int file_1_index{-1};
        int file_2_index{-1};
        double similarity{0};
    };

    std::vector<PairOfFiles> identical_files;
    std::vector<PairOfFiles> similar_files;
    std::unordered_set<int> identical_file_index_from_dir_1;
    std::unordered_set<int> identical_file_index_from_dir_2;

    for (int i = 0; i < dir_1_file_paths.size(); ++i) {
        std::string data_1 = read_data_from_file(dir_1_file_paths[i]);
        for (int j = 0; j < dir_2_file_paths.size(); ++j) {
            std::string data_2 = read_data_from_file(dir_2_file_paths[j]);
            size_t max_size = std::max(data_1.size(), data_2.size());
            size_t max_common_chars_count = data_1.size() == max_size ?
                                            get_max_common_chars_count(data_1, data_2) : get_max_common_chars_count(data_2, data_1);
            if (max_common_chars_count == max_size) {
                identical_files.push_back({i, j, 100});
                identical_file_index_from_dir_1.insert(i);
                identical_file_index_from_dir_2.insert(j);
            } else if (max_common_chars_count >= max_size * percent) {
                similar_files.push_back({i, j, double(max_common_chars_count) / max_size * 100});
            }
        }
    }

    std::cout << "Identical files:\n";
    for (auto& pair: identical_files) {
        std::cout << dir_1_file_paths[pair.file_1_index] << " - " << dir_2_file_paths[pair.file_2_index] << '\n';
    }
    std::cout << '\n';

    std::cout << "Similar files:\n";
    for (auto& pair: similar_files) {
        std::cout << dir_1_file_paths[pair.file_1_index] << " - " << dir_2_file_paths[pair.file_2_index] << " - " << pair.similarity << '%' << '\n';
    }
    std::cout << '\n';

    std::cout << "Unique files from the first directory:\n";
    for (int i = 0; i < dir_1_file_paths.size(); ++i) {
        if (identical_file_index_from_dir_1.find(i) == identical_file_index_from_dir_1.end()) {
            std::cout << dir_1_file_paths[i] << '\n';
        }
    }
    std::cout << '\n';

    std::cout << "Unique files from the second directory:\n";
    for (int j = 0; j < dir_1_file_paths.size(); ++j) {
        if (identical_file_index_from_dir_2.find(j) == identical_file_index_from_dir_2.end()) {
            std::cout << dir_2_file_paths[j] << '\n';
        }
    }
    std::cout << '\n';
}

int main(int argc, char* argv[]) {
    assert(argc == 4);
    char* dir_1_path = argv[1];
    char* dir_2_path = argv[2];
    double percent = std::stod(std::string(argv[3]));
    solve(dir_1_path, dir_2_path, percent);

    return 0;
}