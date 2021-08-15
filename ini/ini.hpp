#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
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

    bool deselialize(string data)
    {
        vector<string> list = split(data,0x0a);
        cout << list.size() << endl;
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
    std::map<string, map<string, string> > sections;
};