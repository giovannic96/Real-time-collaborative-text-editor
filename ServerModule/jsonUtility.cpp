//
// Created by giova on 05/10/2019.
//

#include <iostream>
#include "header_files/jsonUtility.h"
#include <iomanip>

void jsonUtility::to_json(json &j, const std::string &op, const std::string &resp) {
    j = json{
        {"operation", op},
        {"content", {
            {"response", resp}
        }}
    };
}

void jsonUtility::to_json_symbol(json &j, const symbol &symbol) {
    j = json{
            {"letter", symbol.getLetter()},
            {"id", symbol.getId()}, //std::pair
            {"pos", symbol.getPos()}, //std::vector<int>
            {"isBold", symbol.isBold()},
            {"isItalic", symbol.isItalic()},
    };
}

void jsonUtility::to_json_symVector(json &j, const std::string &op, const std::string &resp, const std::vector<json> &symVector) {
    j = json{
            {"operation", op},
            {"content", {
                {"response", resp},
                {"symVector", symVector} //JSON vector
            }}
    };
}

void jsonUtility::to_json_usernameLogin(json &j, const std::string &op, const std::string &resp, const std::string &usernameLogin) {
    j = json{
            {"operation", op},
            {"content", {
                {"response", resp},
                {"usernameLogin", usernameLogin}
            }}
    };
}

void jsonUtility::to_json(json &j, const std::string &op,const std::string &user, const std::string &pass) {
    j = json{
        {"operation", op},
        {"content", {
              {"username", user},
              {"password", pass}
        }}
    };
}

void jsonUtility::to_json(json &j, const std::string &op, const std::string &user, const std::string &pass, const std::string &email) {
    j = json{
        {"operation", op},
        {"content", {
              {"username", user},
              {"password", pass},
              {"email", email}
        }}
    };
}

void to_json(json& j, const File& file){
    j = json{
            {"idfile", file.getidfile()},
            {"filename", file.getfilename()},
            {"owner", file.getowner()},
            {"timestamp",  file.gettimestamp()}
    };
}

void jsonUtility::to_json_vector_file(json &j, const std::string &op, const std::string &resp, const std::vector <File> &vectorFile) {

    //DEBUG
    //std::vector<File> vfile;
    //vfile.emplace_back(File{"cipolla", "patate", "meloni", "angurie"});
    //vfile.emplace_back(File{ "capre", "mucche", "meloni", "angurie" });

    json local = vectorFile;
    //std::cout << std::setw(2) << jlocal << std::endl;

    j = json{
            {"operation", op},
            {"content", {
                {"response", resp},
                {"vectorFile", local}
            }}
    };
    std::cout << std::setw(2) << j << std::endl;
}

void jsonUtility::from_json(const json &j, std::string &op) {
    op = j.at("operation").get<std::string>();
}

void jsonUtility::from_json_symbol(const json &j, symbol &s) {

    //get symbol values from json
    char letter = j.at("letter").get<char>();
    std::pair<int,int> id = j.at("id").get<std::pair<int, int>>();
    std::vector<int> pos = j.at("pos").get<std::vector<int>>();
    bool isBold = j.at("isBold").get<bool>();
    bool isItalic = j.at("isItalic").get<bool>();

    //now create the symbol
    s.setLetter(letter);
    s.setId(id);
    s.setPos(pos);
    s.setBold(isBold);
    s.setItalic(isItalic);
}

void jsonUtility::from_json_resp(const json &j, std::string &resp) {
    resp = j.at("content").at("response").get<std::string>();
}

void jsonUtility::from_json(const json &j, std::string &user, std::string &pass) {
    user = j.at("content").at("username").get<std::string>();
    pass = j.at("content").at("password").get<std::string>();
}

void jsonUtility::from_json_filename(const json &j, std::string &user, std::string &filename) {
    user = j.at("content").at("username").get<std::string>();
    filename = j.at("content").at("filename").get<std::string>();
}
void jsonUtility::from_json_username(const json &j, std::string &user) {
    user = j.at("content").at("username").get<std::string>();
}

void jsonUtility::from_json(const json &j, std::string &user, std::string &pass, std::string &email) {
    user = j.at("content").at("username").get<std::string>();
    pass = j.at("content").at("password").get<std::string>();
    email = j.at("content").at("email").get<std::string>();
}

json jsonUtility::merge(const json &a, const json &b) {
    json result = a.flatten();
    json tmp = b.flatten();

    for (json::iterator it = tmp.begin(); it != tmp.end(); ++it) {
        result[it.key()] = it.value();
    }
    return result.unflatten();
}

std::vector<json> jsonUtility::fromSymToJson(std::vector<symbol> symbols) {

    //TODO: delete this initialization of symbols
    std::vector<int> v; //pos vector
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    symbol s1('C', std::make_pair(0,1), v);
    symbol s2('I', std::make_pair(0,2), v);
    symbol s3('A', std::make_pair(1,1), v);
    symbols.push_back(s1);
    symbols.push_back(s2);
    symbols.push_back(s3);

    // Get jsons from symbols
    std::vector<json> jsons;
    for (auto const &sym: symbols) {
        json j;
        jsonUtility::to_json_symbol(j, sym); //convert sym into json
        jsons.push_back(j);
    }
    return jsons;
}