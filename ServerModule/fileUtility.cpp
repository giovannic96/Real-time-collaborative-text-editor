//
// Created by giova on 26/10/2019.
//

#include <fstream>
#include <iostream>
#include <chrono>
#include "header_files/fileUtility.h"
#include "header_files/json.hpp"
#include "header_files/jsonUtility.h"

using json = nlohmann::json;

void fileUtility::writeFile(const std::string& filename, const std::vector<symbol>& symbols) {
    json j = jsonUtility::fromSymToJson(symbols);

    // Write json string on file
    std::ofstream outputFile(filename);
    if(outputFile.is_open()) {
        outputFile << j;
        outputFile.close();
        std::cout << "File " << filename << " written correctly" << std::endl;
    } else
        std::cout << "Unable to open file";
}

std::vector<symbol> fileUtility::readFile(const std::string& filepath) {
    std::vector<symbol> symbols;

    /* Read bytes from file */
    std::ifstream f(filepath);
    std::string str;
    if(f.is_open()) {
        if(fileUtility::is_empty(f))
            return std::vector<symbol>();

        std::string line;
        while(getline(f, line)) {
            str.append(line);
        }
        f.close();
    }

    /* Construct symbols vector */
    auto t_start1 = std::chrono::high_resolution_clock::now();
    json jdata_in = json::parse(str);
    auto t_end1 = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms1 = std::chrono::duration<double, std::milli>(t_end1-t_start1).count();
    std::cout << "READ FILE PARSE - ELAPSED (ms): " << elapsed_time_ms1 << std::endl;
    std::vector<json> jsonSymbols;
    auto t_start = std::chrono::high_resolution_clock::now();
    jsonUtility::from_json_storedSymbols(jdata_in, jsonSymbols);
    symbols = jsonUtility::fromJsonToSym(jsonSymbols);
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    std::cout << "READ FILE PT2 - ELAPSED (ms): " << elapsed_time_ms << std::endl;
    return symbols;
}

bool fileUtility::is_empty(std::ifstream& pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}