#pragma once

#include <algorithm>
#include <assert.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <unordered_set>

#include "string_utils.h"

namespace fs = std::filesystem;

struct DirectoryInfo {
    char* dir_path{nullptr};
    std::vector<std::basic_string<char>> file_paths;

    DirectoryInfo(char* dir_path) {
        for (const auto& entry : fs::directory_iterator(dir_path)) {
            if (entry.is_regular_file()) {
                file_paths.push_back(entry.path().string());
            }
        }
    }
};

class DirectoryComparator {
public:
    DirectoryComparator(char* dir_1_path, char* dir_2_path)
        : m_dir_1_info(dir_1_path)
        , m_dir_2_info(dir_2_path) {
    }

    struct PairOfFiles {
        int file_1_index{-1};
        int file_2_index{-1};
        double similarity{0};
    };

    void analyze(double percent) const {
        std::vector<PairOfFiles> identical_files;
        std::vector<PairOfFiles> similar_files;
        std::unordered_set<int> identical_file_index_from_dir_1;
        std::unordered_set<int> identical_file_index_from_dir_2;

        for (int i = 0; i < m_dir_1_info.file_paths.size(); ++i) {
            std::string data_1 = read_data_from_file(m_dir_1_info.file_paths[i]);
            for (int j = 0; j < m_dir_2_info.file_paths.size(); ++j) {
                std::string data_2 = read_data_from_file(m_dir_2_info.file_paths[j]);
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

        print_result(identical_files, similar_files, identical_file_index_from_dir_1, identical_file_index_from_dir_2);
    }

private:
    std::string read_data_from_file(const std::basic_string<char>& file_path) const {
        std::ifstream fin;
        fin.open(file_path);
        size_t file_size = fs::file_size(file_path);
        std::string file_data(file_size, '\0');
        fin.read(&file_data[0], file_size);
        fin.close();
        return file_data;
    }

    void print_result(const std::vector<PairOfFiles>& identical_files,
                      const std::vector<PairOfFiles>& similar_files,
                      const std::unordered_set<int>& identical_file_index_from_dir_1,
                      const std::unordered_set<int>& identical_file_index_from_dir_2) const {
        std::cout << "Identical files:\n";
        for (auto& pair: identical_files) {
            std::cout << m_dir_1_info.file_paths[pair.file_1_index] << " - " << m_dir_2_info.file_paths[pair.file_2_index] << '\n';
        }
        std::cout << '\n';

        std::cout << "Similar files:\n";
        for (auto& pair: similar_files) {
            std::cout << m_dir_1_info.file_paths[pair.file_1_index] << " - " << m_dir_2_info.file_paths[pair.file_2_index] << " - " << pair.similarity << '%' << '\n';
        }
        std::cout << '\n';

        std::cout << "Unique files from the first directory:\n";
        for (int i = 0; i < m_dir_1_info.file_paths.size(); ++i) {
            if (identical_file_index_from_dir_1.find(i) == identical_file_index_from_dir_1.end()) {
                std::cout << m_dir_1_info.file_paths[i] << '\n';
            }
        }
        std::cout << '\n';

        std::cout << "Unique files from the second directory:\n";
        for (int j = 0; j < m_dir_2_info.file_paths.size(); ++j) {
            if (identical_file_index_from_dir_2.find(j) == identical_file_index_from_dir_2.end()) {
                std::cout << m_dir_2_info.file_paths[j] << '\n';
            }
        }
        std::cout << '\n';
    }

private:
    DirectoryInfo m_dir_1_info;
    DirectoryInfo m_dir_2_info;
};