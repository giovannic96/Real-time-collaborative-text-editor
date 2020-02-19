//
// Created by giova on 26/10/2019.
//

#include <fstream>
#include <iostream>
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
    json jdata_in = json::parse(str);
    std::vector<json> jsonSymbols;
    jsonUtility::from_json_storedSymbols(jdata_in, jsonSymbols);
    symbols = jsonUtility::fromJsonToSym(jsonSymbols);

    return symbols;
}

bool fileUtility::is_empty(std::ifstream& pFile) {
    return pFile.peek() == std::ifstream::traits_type::eof();
}