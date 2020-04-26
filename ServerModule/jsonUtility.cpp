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
            {"isBold", symbol.getStyle().isBold()},
            {"isItalic", symbol.getStyle().isItalic()},
            {"isUnderlined", symbol.getStyle().isUnderlined()},
            {"fontFamily", symbol.getStyle().getFontFamily()},
            {"fontSize", symbol.getStyle().getFontSize()},
            {"alignment", symbol.getStyle().getAlignment()},
            {"color", symbol.getStyle().getColor()}
    };
}

/* We need to use this 'to_json' to serialize std::vector<symbol> (see function to_json_symVector) */
void to_json(json& j, const symbol& s) {
    j = json{
            {"letter", s.getLetter()},
            {"id", s.getId()}, //std::pair
            {"pos", s.getPos()}, //std::vector<int>
            {"isBold", s.getStyle().isBold()},
            {"isItalic", s.getStyle().isItalic()},
            {"isUnderlined", s.getStyle().isUnderlined()},
            {"fontFamily", s.getStyle().getFontFamily()},
            {"fontSize", s.getStyle().getFontSize()},
            {"alignment", s.getStyle().getAlignment()},
            {"color", s.getStyle().getColor()}
    };
}

void jsonUtility::to_json_symVector(json &j, const std::string &op, const std::string &resp, const std::vector<symbol> &symVector) {
    j = json{
            {"operation", op},
            {"content", {
            {"response", resp},
            {"symVector", symVector} //use to_json previously defined
        }}
    };
}

void jsonUtility::to_json_cursor_change(json &j, const std::string &op, const std::string &username, const std::string &color, const int &pos) {
    j = json{
            {"operation", op},
            {"username", username},
            {"color", color},
            {"pos", pos}
    };
}

void jsonUtility::to_json_collab_colors_resp(json &j, const std::string &op, const std::string &resp, const std::map<std::string, std::pair<std::string,bool>> &collabColorsMap) {
    j = json{
            {"operation", op},
            {"response", resp},
            {"collabColorsMap", collabColorsMap}
    };
}

void jsonUtility::to_json_user_offline(json &j, const std::string &op, const std::string &resp, const std::string &username, const std::map<std::string, std::pair<std::string,bool>> &collabColorsMap) {
    j = json{
            {"operation", op},
            {"response", resp},
            {"username", username},
            {"collabColorsMap", collabColorsMap}
    };
}

void jsonUtility::to_json_symVectorAndFilename(json &j, const std::string &op, const std::string &resp, const std::vector<symbol> &symVector, const std::string &filename) {
    j = json{
            {"operation", op},
            {"content", {
                    {"response", resp},
                    {"filename", filename},
                    {"symVector", symVector}
            }}
    };
}

void jsonUtility::to_json_file(json &j, const File &file) {
    j = json{
            {"idfile", file.getidfile()},
            {"filename", file.getfilename()},
            {"owner", file.getowner()},
            {"timestamp",  file.gettimestamp()}
    };
}

void jsonUtility::to_json_fileVector(json &j, const std::string &op, const std::string &resp, const std::vector<json> &vectorFile) {
    j = json{
            {"operation", op},
            {"content", {
                  {"response", resp},
                  {"vectorFile", vectorFile} //JSON vector
            }}
    };
}

void jsonUtility::to_json_usernameLogin(json &j, const std::string &op, const std::string &resp, const std::string &usernameLogin, const std::string &colorLogin, const std::string &mail, const int &siteId) {
    j = json{
            {"operation", op},
            {"content", {
                {"response", resp},
                {"usernameLogin", usernameLogin},
                {"colorLogin", colorLogin},
                {"mailLogin", mail},
                {"siteId", siteId}
            }}
    };
}

void jsonUtility::to_json_newuri(json &j, const std::string &op, const std::string &resp, const std::string &uri) {
    j = json{
            {"operation", op},
            {"content", {
                  {"response", resp},
                  {"uri", uri}
            }}
    };
}

void jsonUtility::to_json_rename_file(json &j, const std::string &op, const std::string &resp, const std::string &filename) {
    j = json{
            {"operation", op},
            {"content", {
                {"response", resp},
                {"filename", filename}
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

void jsonUtility::to_json_insertion(json &j, const std::string &op, const symbol &symbol, const int &indexInEditor) {
    j = json{
        {"operation", op},
        {"symbolId", symbol.getId()},
        {"symbolPos", symbol.getPos()},
        {"symbolLetter", symbol.getLetter()},
        {"isBold", symbol.getStyle().isBold()},
        {"isItalic", symbol.getStyle().isItalic()},
        {"isUnderlined", symbol.getStyle().isUnderlined()},
        {"fontFamily", symbol.getStyle().getFontFamily()},
        {"fontSize", symbol.getStyle().getFontSize()},
        {"alignment", symbol.getStyle().getAlignment()},
        {"color", symbol.getStyle().getColor()},
        {"indexInEditor", indexInEditor}
    };
}

void jsonUtility::to_json_removal_range(json &j, const std::string &op, const std::vector<std::pair<int,int>> &symbolsId) {
    j = json{
            {"operation", op},
            {"symbolsId", symbolsId}
    };
}

void jsonUtility::to_json_format_range(json &j, const std::string &op, const std::vector<sId> &symbolsId, const int &format) {
    j = json{
            {"operation", op},
            {"symbolsId", symbolsId},
            {"format", format}
    };
}

void jsonUtility::to_json_fontsize_change(json &j, const std::string &op, const std::vector<sId> &symbolsId, const int &fontSize) {
    j = json{
            {"operation", op},
            {"symbolsId", symbolsId},
            {"fontSize", fontSize}
    };
}

void jsonUtility::to_json_fontfamily_change(json &j, const std::string &op, const std::vector<sId> &symbolsId, const std::string &fontFamily) {
    j = json{
            {"operation", op},
            {"symbolsId", symbolsId},
            {"fontFamily", fontFamily}
    };
}

void jsonUtility::to_json_alignment_change(json &j, const std::string &op, const std::vector<sId> &symbolsId, const int &alignment) {
    j = json{
            {"operation", op},
            {"symbolsId", symbolsId},
            {"alignment", alignment}
    };
}

void jsonUtility::to_json_insertion_range(json &j, const std::string &op, const int &firstIndexRange, const std::vector<json> &symbols) {
    j = json{
            {"operation", op},
            {"firstIndexRange", firstIndexRange},
            {"symbols", symbols}
    };
}

void jsonUtility::from_json_insertion(const json& j, symbol& s, int &indexInEditor) {
    indexInEditor = j.at("indexInEditor").get<int>();
    wchar_t letter = j.at("symbolLetter").get<wchar_t>();
    std::pair<int,int> id = j.at("symbolId").get<std::pair<int,int>>();
    std::vector<int> pos = j.at("symbolPos").get<std::vector<int>>();
    symbolStyle style;
    style.setBold(j.at("isBold").get<bool>());
    style.setItalic(j.at("isItalic").get<bool>());
    style.setUnderlined(j.at("isUnderlined").get<bool>());
    style.setFontFamily(j.at("fontFamily").get<std::string>());
    style.setFontSize(j.at("fontSize").get<int>());
    style.setAlignment(j.at("alignment").get<int>());
    style.setColor(j.at("color").get<std::string>());
    s = symbol(letter, id, pos, style);
}

void jsonUtility::from_json(const json &j, std::string &op) {
    op = j.at("operation").get<std::string>();
}

void jsonUtility::from_json_resp(const json &j, std::string &resp) {
    resp = j.at("content").at("response").get<std::string>();
}

void jsonUtility::from_json(const json &j, std::string &user, std::string &pass) {
    user = j.at("content").at("username").get<std::string>();
    pass = j.at("content").at("password").get<std::string>();
}

void jsonUtility::from_json_inviteURI(const json &j, std::string &invited, std::string &applicant, std::string &uri) {
    invited = j.at("invited").get<std::string>();
    applicant = j.at("applicant").get<std::string>();
    uri = j.at("uri").get<std::string>();
}

void jsonUtility::from_json_filename(const json &j, std::string &user, std::string &filename) {
    user = j.at("content").at("username").get<std::string>();
    filename = j.at("content").at("filename").get<std::string>();
}

void jsonUtility::from_json_uri(const json &j, std::string &user, std::string &uri) {
    user = j.at("content").at("username").get<std::string>();
    uri = j.at("content").at("uri").get<std::string>();
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

std::vector<json> jsonUtility::fromSymToJson(const std::vector<symbol>& symbols) {
    if(symbols.empty())
        return json::array();

    // Get jsons from symbols
    std::vector<json> jsons;
    for (auto const &sym: symbols) {
        json j;
        jsonUtility::to_json_symbol(j, sym); //convert sym into json
        jsons.push_back(j);
    }
    return jsons;
}

std::vector<symbol> jsonUtility::fromJsonToSym(const std::vector<json>& jsons) {
    // Get symbols from json
    std::vector<symbol> symbols;
    for (auto const &j: jsons) {
       symbols.push_back(jsonUtility::from_json_symbol(j));
    }
    return symbols;
}

std::vector<symbol> jsonUtility::fromJsonToFormattingSym(const std::vector<json>& jsons) {
    // Get formatting symbols from json
    std::vector<symbol> symbols;
    for (auto const &j: jsons) {
        symbols.push_back(jsonUtility::from_json_symbol(j));
    }
    return symbols;
}

std::vector<json> jsonUtility::fromFileToJson(const std::vector<File>& files) {
    // Get jsons from symbols
    std::vector<json> jsons;
    for (auto const &f: files) {
        json j;
        jsonUtility::to_json_file(j, f); //convert sym into json
        jsons.push_back(j);
    }
    return jsons;
}

void jsonUtility::from_json_storedSymbols(const json& j, std::vector<json>& jsonSymbols) {
    jsonSymbols = j.get<std::vector<json>>();
}

symbol jsonUtility::from_json_symbol(const json &j) {
    //get symbol values from json
    std::pair<int,int> id = j.at("symbolId").get<std::pair<int,int>>();
    std::vector<int> pos = j.at("symbolPos").get<std::vector<int>>();
    wchar_t letter = j.at("symbolLetter").get<wchar_t>();
    symbolStyle style(j.at("isBold").get<bool>(), j.at("isItalic").get<bool>(),j.at("isUnderlined").get<bool>(),
                    j.at("fontFamily").get<std::string>(), j.at("fontSize").get<int>(), j.at("alignment").get<int>(),
                        j.at("color").get<std::string>());

    //now create the symbol
    symbol s(letter, id, pos, style);
    return s;
}

void jsonUtility::from_json_cursor_change_req(const json &j, int& index) {
    index = j.at("index").get<int>();
}

void jsonUtility::from_json_collab_colors(const json &j, std::string& uri) {
    uri = j.at("uri").get<std::string>();
}

void jsonUtility::from_json_removal_range(const json &j, std::vector<sId>& symbolsId) {
    symbolsId = j.at("symbolsId").get<std::vector<sId>>();
}

void jsonUtility::from_json_format_range(const json &j, std::vector<sId>& symbolsId, int& format) {
    symbolsId = j.at("symbolsId").get<std::vector<sId>>();
    format = j.at("format").get<int>();
}

void jsonUtility::from_json_fontsize_change(const json &j, std::vector<sId>& symbolsId, int& fontSize) {
    symbolsId = j.at("symbolsId").get<std::vector<sId>>();
    fontSize = j.at("fontSize").get<int>();
}

void jsonUtility::from_json_fontfamily_change(const json &j, std::vector<sId>& symbolsId, std::string& fontFamily) {
    symbolsId = j.at("symbolsId").get<std::vector<sId>>();
    fontFamily = j.at("fontFamily").get<std::string>();
}

void jsonUtility::from_json_alignment_change(const json &j, std::vector<sId>& symbolsId, int& alignment) {
    symbolsId = j.at("symbolsId").get<std::vector<sId>>();
    alignment = j.at("alignment").get<int>();
}

void jsonUtility::from_json_insertion_range(const json &j, std::vector<json>& symbols, int& startIndex) {
    symbols = j.at("formattingSymVector").get<std::vector<json>>();
    startIndex = j.at("startIndex").get<int>();
}

void jsonUtility::from_json_renameFile(const json &j, std::string &nameFile, std::string &urifile, std::string &username) {
    nameFile = j.at("content").at("newNameFile").get<std::string>();
    urifile = j.at("content").at("uri").get<std::string>();
    username = j.at("content").at("username").get<std::string>();
}
