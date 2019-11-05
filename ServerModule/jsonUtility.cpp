//
// Created by giova on 05/10/2019.
//

#include "header_files/jsonUtility.h"

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

void jsonUtility::to_json_symVector(json &j, const std::string &op, const std::string &resp, const std::string &symVector) {
    j = json{
            {"operation", op},
            {"content", {
                {"response", resp},
                {"symVector", symVector} //JSON string
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

json jsonUtility::fromSymToJson(const std::vector<symbol>& symbols) {

    // Get jsons from symbols
    std::vector<json> jsons;
    for (auto const &sym: symbols) {
        json j;
        jsonUtility::to_json_symbol(j, sym); //convert sym into json
        jsons.push_back(j);
    }

    // Get all jsons merged into one single json
    json json_merged;
    for (auto const &j: jsons) {
        json_merged = jsonUtility::merge(json_merged, j);
    }
    return json_merged;
}