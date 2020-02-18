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

void jsonUtility::to_json_insertion(json &j, const std::string &op, const std::pair<int, wchar_t> &tuple, const symbolStyle &style) {
    j = json{
        {"operation", op},
        {"tuple", tuple},
        {"isBold", style.isBold()},
        {"isItalic", style.isItalic()},
        {"isUnderlined", style.isUnderlined()},
        {"fontFamily", style.getFontFamily()},
        {"fontSize", style.getFontSize()}
    };
}

void jsonUtility::to_json_removal(json &j, const std::string &op, const int &index) {
    j = json {
        {"operation", op},
        {"index", index}
    };
}

void jsonUtility::to_json_removal_range(json &j, const std::string &op, const int &startIndex, const int &endIndex) {
    j = json{
            {"operation", op},
            {"startIndex", startIndex},
            {"endIndex", endIndex}
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

void jsonUtility::to_json_inviteURI(json &j, const std::string &op, const std::string &invited, const std::string &applicant, const std::string &uri) {
    j = json{
            {"operation", op},
            {"invited", invited},
            {"applicant", applicant},
            {"uri", uri}
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

void jsonUtility::to_json_insertion_range(json &j, const std::string &op, const std::vector<json> &symVector) {
    j = json{
            {"operation", op},
            {"formattingSymVector", symVector} //JSON vector
    };
}


void jsonUtility::from_json(const json &j, std::string &op) {
    op = j.at("operation").get<std::string>();
}

void jsonUtility::from_json_inviteURI(const json &j, std::string &op) {
    op = j.at("content").at("response").get<std::string>();
}

void jsonUtility::from_json_resp(const json &j, std::string &resp) {
    resp = j.at("content").at("response").get<std::string>();
}

void jsonUtility::from_json_formatting_symbols(const json &j, std::vector<json>& jsonSymbols) {
    jsonSymbols = j.at("formattingSymVector").get<std::vector<json>>();
}

void jsonUtility::from_json_symbolsAndFilename(const json &j, std::vector<json>& jsonSymbols, std::string& filename) {
    filename = j.at("content").at("filename").get<std::string>();
    jsonSymbols = j.at("content").at("symVector").get<std::vector<json>>();
}

void jsonUtility::from_json_filename(const json &j, std::string& filename) {
    filename = j.at("content").at("filename").get<std::string>();
}

void jsonUtility::from_json_symbols(const json &j, std::vector<json>& jsonSymbols) {
    jsonSymbols = j.at("content").at("symVector").get<std::vector<json>>();
}

void jsonUtility::from_json_insertion_range(const json &j, int& firstIndex, std::vector<json>& jsonSymbols) {
    firstIndex = j.at("firstIndexRange").get<int>();
    jsonSymbols = j.at("symbols").get<std::vector<json>>();
}

void jsonUtility::from_json_rename_file(const json &j, std::string &resp, std::string& filename) {
    filename = j.at("content").at("filename").get<std::string>();
    resp = j.at("content").at("response").get<std::string>();
}


void jsonUtility::from_json_files(const json &j, std::vector<json>& jsonFiles) {
    jsonFiles = j.at("content").at("vectorFile").get<std::vector<json>>();
}

symbol* jsonUtility::from_json_symbol(const json &j) {
    wchar_t letter;
    std::pair<int,int> id;
    std::vector<int> pos;
    symbolStyle style;

    try {
        //get symbol values from json
        letter = j.at("letter").get<wchar_t>();
        id = j.at("id").get<std::pair<int, int>>();
        pos = j.at("pos").get<std::vector<int>>();
        style = {j.at("isBold").get<bool>(), j.at("isItalic").get<bool>(),j.at("isUnderlined").get<bool>(),
                 j.at("fontFamily").get<std::string>(), j.at("fontSize").get<int>()};
    } catch (json::exception& e) {
        // output exception information
        std::cerr << "message: " << e.what() << '\n'
                           << "exception id: " << e.id << std::endl;
        return nullptr;
    }

    //now create the symbol
    symbol *s = new symbol(letter, id, pos, style);
    return s;
}

symbolInfo* jsonUtility::from_json_formatting_symbol(const json &j) {

    //get symbol values from json
    int index = j.at("index").get<int>();
    wchar_t letter = j.at("letter").get<wchar_t>();
    symbolStyle style(j.at("isBold").get<bool>(), j.at("isItalic").get<bool>(),j.at("isUnderlined").get<bool>(),
                      j.at("fontFamily").get<std::string>(), j.at("fontSize").get<int>());

    //now create the symbol
    symbolInfo *s = new symbolInfo(index, letter, style);
    return s;
}

File* jsonUtility::from_json_file(const json &j) {
    std::string idfile;
    std::string filename;
    std::string owner;
    std::string timestamp;

    try {
        //get symbol values from json
        idfile = j.at("idfile").get<std::string>();
        filename = j.at("filename").get<std::string>();
        owner = j.at("owner").get<std::string>();
        timestamp = j.at("timestamp").get<std::string>();

    } catch (json::exception& e) {
        // output exception information
        std::cerr << "message: " << e.what() << '\n'
                           << "exception id: " << e.id << std::endl;
        return nullptr;
    }
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

void jsonUtility::from_json_insertion(const json &j, std::pair<int, wchar_t>& tuple, symbolStyle& style) {
    tuple = j.at("tuple").get<std::pair<int, wchar_t>>();
    style = {j.at("isBold").get<bool>(), j.at("isItalic").get<bool>(), j.at("isUnderlined").get<bool>(),
             j.at("fontFamily").get<std::string>(), j.at("fontSize").get<int>()};
}

void jsonUtility::from_json_removal(const json &j, int& index) {
    index = j.at("index").get<int>();
}

void jsonUtility::from_json_removal_range(const json &j, int& startIndex, int& endIndex) {
    startIndex = j.at("startIndex").get<int>();
    endIndex = j.at("endIndex").get<int>();
}

void jsonUtility::to_json_FormattingSymbol(json &j, const symbolInfo &symbol) {
    j = json{
            {"index", symbol.getIndex()},
            {"letter", symbol.getLetter()},
            {"isBold", symbol.getStyle().isBold()},
            {"isItalic", symbol.getStyle().isItalic()},
            {"isUnderlined", symbol.getStyle().isUnderlined()},
            {"fontFamily", symbol.getStyle().getFontFamily()},
            {"fontSize", symbol.getStyle().getFontSize()}
    };
}

std::vector<json> jsonUtility::fromFormattingSymToJson(const std::vector<symbolInfo>& symbols) {
    if(symbols.empty())
        return json::array();

    // Get jsons from symbols
    std::vector<json> jsons;
    for (auto const &sym: symbols) {
        json j;
        jsonUtility::to_json_FormattingSymbol(j, sym); //convert sym into json
        jsons.push_back(j);
    }
    return jsons;
}
