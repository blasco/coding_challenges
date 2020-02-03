//! Hackerrank HRML Attribute Parser

//! This program reads from an input file that passes a HRML document as explained in
//! in the Hackerrank challenge "Attribute Parser".
//! The first line of the input file include n and q, where n is the number of lines
//! of the HRML documment that follows, and q is the number of querries that follow the
//! HRML documment

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>

int main() {
    std::ifstream ifile("input");

    std::smatch result; 

    if (ifile.is_open()) {
        int n,q;
        ifile >> n >> q;
        ifile.ignore();

        std::string document;
        for (;n>0;--n) {
            std::string line;
            std::getline(ifile, line);
            document.append(line);
        }

        std::regex tag_regex(R"(<[^>]*)");
        auto tag_matches_begin = std::sregex_iterator(document.begin(), document.end(), tag_regex);
        auto tag_matches_end = std::sregex_iterator();

        using Tag_name = std::string;
        using Attribute_name = std::string;
        std::unordered_map<Tag_name, std::unordered_map<Attribute_name, std::string>> tag_map;
        Tag_name tag_name{};
        for (auto tag_it = tag_matches_begin; tag_it != tag_matches_end; ++tag_it) {
            std::smatch match = *tag_it;
            auto match_string = match.str();

            // if beginig of tag <tag ...
            if (std::regex_search(match_string, result, std::regex(R"(<\s*([^/]\w*))"))) {
                std::string new_tag_name = result[1].str();
                if (tag_name.empty()) {
                    tag_name = new_tag_name;
                } else {
                    tag_name = tag_name + "." + new_tag_name;
                }
                std::string search_string = match_string;
                while (std::regex_search(search_string, result, std::regex(R"re(([^=\s]*)\s*=\s*"([^"]*))re"))) {
                    std::string attribute_name = result[1].str();
                    std::string attribute_value = result[2].str();

                    tag_map[tag_name][attribute_name] = attribute_value;

                    search_string = result.suffix();
                }
            }
            // if end of tag  </tag>
            else if (std::regex_search(match_string, result, std::regex(R"(</\s*(\w*))"))) {
                std::string end_tag_name = result[1].str();
                tag_name = std::regex_replace(tag_name, std::regex(end_tag_name), "");
                tag_name = std::regex_replace(tag_name, std::regex(R"(\.$)"), "");
            }
        }
        for (;q>0;--q) {
            std::string line;
            std::getline(ifile, line);

            std::regex_search(line, result, std::regex(R"((.*)~(.*))"));
            std::string tag_name = result[1].str();
            std::string attribute_name = result[2].str();
            if (tag_map[tag_name].count(attribute_name) > 0 ) {
                std::cout << tag_map[tag_name][attribute_name] << "\n";
            }
            else {
                std::cout << "Not Found!" << "\n";
            }
        }
        std::cout << std::flush;
    }
    else { 
        std::cout << "Unable to open input file" << std::endl;;
    }

    return 0;
}
