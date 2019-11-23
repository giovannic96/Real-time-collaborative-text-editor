//
// Created by giova on 05/10/2019.
//

#include "jsonUtility.h"

void jsonUtility::to_json(json &j, const std::string &op, const std::string &resp) {
    j = json{
            {"operation", op},
            {"content", {
                {"response", resp}
            }}
    };
}

void jsonUtility::to_json(json &j, const std::string &op, const std::string &user, const std::string &pass) {
    j = json{
            {"operation", op},
            {"content", {
                {"username", user},
                {"password", pass}
            }}
    };
}

void jsonUtility::to_json_insertion(json &j, const std::string &op, const std::pair<int, char> &tuple) {
    j = json {
        {"operation", op},
        {"tuple", tuple}
    };
}

void jsonUtility::to_json_removal(json &j, const std::string &op, const int &index) {
    j = json {
        {"operation", op},
        {"index", index}
    };
}

void jsonUtility::to_jsonFilename(json &j, const std::string &op, const std::string &user, const std::string &filename) {
    j = json{
            {"operation", op},
            {"content", {
                {"username", user},
                {"filename", filename}
            }}
    };
}

void jsonUtility::to_jsonRenamefile(json &j, const std::string &op, const std::string &nameFile, const std::string &uri, const std::string &username) {
    j = json{
            {"operation", op},
            {"content", {
                {"newNameFile", nameFile},
                {"uri", uri},
                {"username", username}
            }}
    };
}

void jsonUtility::to_jsonUri(json &j, const std::string &op, const std::string &user, const std::string &uri) {
    j = json{
            {"operation", op},
            {"content", {
                {"username", user},
                {"uri", uri}
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

void jsonUtility::to_jsonUser(json &j, const std::string &op, const std::string &user) {
    j = json{
            {"operation", op},
            {"content", {
                {"username", user}
            }}
    };
}

void jsonUtility::from_json(const json &j, std::string &op) {
    op = j.at("operation").get<std::string>();
}

void jsonUtility::from_json_resp(const json &j, std::string &resp) {
    resp = j.at("content").at("response").get<std::string>();
}

void jsonUtility::from_json_symbols(const json &j, std::vector<json>& jsonSymbols) {
    jsonSymbols = j.at("content").at("symVector").get<std::vector<json>>();
}

void jsonUtility::from_json_symbolsAndFilename(const json &j, std::vector<json>& jsonSymbols, std::string& filename) {
    filename = j.at("content").at("filename").get<std::string>();
    jsonSymbols = j.at("content").at("symVector").get<std::vector<json>>();
}

void jsonUtility::from_json_rename_file(const json &j, std::string &resp, std::string& filename) {
    filename = j.at("content").at("filename").get<std::string>();
    resp = j.at("content").at("response").get<std::string>();
}


void jsonUtility::from_json_files(const json &j, std::vector<json>& jsonFiles) {
    jsonFiles = j.at("content").at("vectorFile").get<std::vector<json>>();
}

symbol* jsonUtility::from_json_symbol(const json &j) {

    //get symbol values from json
    char letter = j.at("letter").get<char>();
    std::pair<int,int> id = j.at("id").get<std::pair<int, int>>();
    std::vector<int> pos = j.at("pos").get<std::vector<int>>();
    bool isBold = j.at("isBold").get<bool>();
    bool isItalic = j.at("isItalic").get<bool>();

    //now create the symbol
    symbol *s = new symbol(letter, id, pos);
    s->setBold(isBold);
    s->setItalic(isItalic);
    return s;
}

File* jsonUtility::from_json_file(const json &j) {

    //get symbol values from json
    std::string idfile = j.at("idfile").get<std::string>();
    std::string filename = j.at("filename").get<std::string>();
    std::string owner = j.at("owner").get<std::string>();
    std::string timestamp = j.at("timestamp").get<std::string>();

    //now create the file
    File *f = new File(idfile, filename, owner, timestamp);
    return f;
}

void jsonUtility::from_json_usernameLogin(const json &j, std::string &name) {
    name = j.at("content").at("usernameLogin").get<std::string>();
}

void jsonUtility::from_json(const json &j, std::string &user, std::string &pass) {
    user = j.at("content").at("username").get<std::string>();
    pass = j.at("content").at("password").get<std::string>();
}

void jsonUtility::from_json(const json &j, std::string &user, std::string &pass, std::string &email) {
    user = j.at("content").at("username").get<std::string>();
    pass = j.at("content").at("password").get<std::string>();
    email = j.at("content").at("email").get<std::string>();
}

void jsonUtility::from_jsonUri(const json &j, std::string &uri) {
    uri = j.at("content").at("uri").get<std::string>();
}

void jsonUtility::from_json_insertion(const json &j, std::pair<int, char>& tuple) {
    tuple = j.at("tuple").get<std::pair<int, char>>();
}

void jsonUtility::from_json_removal(const json &j, int& index) {
    index = j.at("index").get<int>();
}
