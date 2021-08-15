#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
using namespace std;

vector<string> split(const string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
        // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}

class ini
{
public:
    static string read_file(string ini_file_path)
    {
        ifstream ifs(ini_file_path);
        if (!ifs)
        {
            throw("file cant open.");
            return "";
        }
        return string(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    }

    static bool is_section_line(string line)
    {
        if (line.front() != '[')
            return false;
        if (line.back() != ']')
            return false;
        return true;
    }

    static string fix_section_line(string line)
    {
        return line.substr(1, line.length() - 2);
    }

    static tuple<string, string> get_key_value(string line)
    {
        size_t pos = line.find("=");
        string key = line.substr(0, pos - 1);
        string value = line.substr(pos + 1, line.length() - pos);
        return forward_as_tuple(key, value);
    }

    static bool is_key_line(string line)
    {
        return (line.find("=") != string::npos);
    }

    bool deselialize(string data)
    {
        vector<string> list = split(data, 0x0a);
        string current_section;
        current_section.clear();
        for (string s : list)
        {
            cout << s << endl;

            // section判定
            bool is_sec = is_section_line(s);
            printf(is_sec ? "section¥n" : "key¥n");
            if (is_sec)
            {
                // sectionの文字列を保存用の文字列に変更する。
                current_section = fix_section_line(s);
                sections[current_section] = map<string, string>();
                continue;
            }

            // key判定
            bool is_key = is_key_line(s);
            if (is_key)
            {
                // keyの行をkeyとvalueに分ける
                string key, value;
                tie(key, value) = get_key_value(s);
                printf("key:%S¥n", key);
                printf("value:%S¥n", value);
                sections[current_section][key] = value;
            }
        }
        return true;
    }

    ini(string ini_file_path)
    {
        m_ini_file_path = ini_file_path;
        string raw = read_file(ini_file_path);
        deselialize(raw);
    }

private:
    string m_ini_file_path;
    std::map<string, map<string, string>> sections;
public:
    map<string, string> & operator [](string n) { return sections[n];}
};