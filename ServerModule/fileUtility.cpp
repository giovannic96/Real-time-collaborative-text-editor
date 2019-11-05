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
        outputFile << j.dump().c_str(); //TODO: should I keep c_str() or only dump()??
        outputFile.close();
        std::cout << "File " << filename << "written correctly";
    } else
        std::cout << "Unable to open file";
}

std::vector<symbol> fileUtility::readFile(const std::string& filename) {
    /*
    std::vector<symbol> symbols;
    symbol sym = nullptr;
    */
    /* Read bytes from file */
    /*
    std::ifstream f(filename, std::ios::binary);
    std::vector<char> bytes((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));
    f.close();

    std::string str(bytes.begin(), bytes.end()); //convert from vector<char> to string
    */
    /* Construct symbols vector */
    /*
    for(int i = 0; i < str.length(); i+= sizeof(symbol)) {
        std::string sub_string = str.substr(i, i + sizeof(symbol)); //get substring (containing one symbol struct) TODO: maybe not working
        json jdata_in = json::parse(sub_string);
        jsonUtility::from_json_symbol(jdata_in, sym); //get symbol struct from json string
        symbols.push_back(sym);
    }

    return symbols;
    */
}
