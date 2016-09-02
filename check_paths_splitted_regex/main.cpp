#include <string>
#include <iostream>
#include "boost/regex.hpp"
#include "boost/algorithm/string.hpp"
using namespace std;
using namespace boost;


bool my_path_match(std::string line)
{
    bool ret = true;
    string drive = "([a-zA-Z]\\:)?";
    string pathElem = "(\\w|\\.|\\s)+";
    boost::regex re_pathElem(pathElem);
    boost::regex re_drive("(" + drive + "|" + pathElem + ")");

    vector<string> split_line;
    vector<string>::iterator it;

    if ((line.front() == '"') && (line.back() == '"'))
    {
        line.erase(0, 1); // erase the first character
        line.erase(line.size() - 1); // erase the last character
    }

    split(split_line, line, is_any_of("/\\"));

    if (regex_match(split_line[0], re_drive) == false)
    {
        ret = false;
    }
    else
    {
        for (it = (split_line.begin() + 1); it != split_line.end(); it++)
        {
            if (regex_match(*it, re_pathElem) == false)
            {
                ret = false;
                break;
            }
        }
    }
    return ret;
}

int main(int argc, char** argv)
{
    boost::regex re_comment("^.*#.*$");

    string shortComment = " #comment ";
    string longComment  = "#123456789012345678901234567890";
    vector<string> testpaths;
    vector<string> paths;
    vector<string>::iterator it;
    testpaths.push_back("C:/this/is.a/path.doc");
    testpaths.push_back("C:/this/is also .a/path.doc");
    testpaths.push_back("/this/is also .a/path.doc");
    testpaths.push_back("./this/is also .a/path.doc");
    testpaths.push_back("this/is also .a/path.doc");
    testpaths.push_back("this/is 1 /path.doc");

    bool ret;
    ret = regex_match(shortComment, re_comment);    //evaluates to true
    cout<<"should be true = "<<ret<<endl;
    ret = regex_match(longComment, re_comment);     //evaluates to true
    cout<<"should be true = "<<ret<<endl;

    string quotes;
    for (it = testpaths.begin(); it != testpaths.end(); it++)
    {
        paths.push_back(*it);
        quotes = "\"" + *it + "\""; // test quoted paths
        paths.push_back(quotes);
        std::replace(it->begin(), it->end(), '/', '\\'); // test backslash paths
        std::replace(quotes.begin(), quotes.end(), '/', '\\'); // test backslash quoted paths
        paths.push_back(*it);
        paths.push_back(quotes);
    }

    for (it = paths.begin(); it != paths.end(); it++)
    {
        ret = my_path_match(*it);             //evaluates to true
        cout<<"should be true = "<<ret<<"\t"<<*it<<endl;
    }

    ret = my_path_match(shortComment);       //evaluates to false
    cout<<"should be false = "<<ret<<endl;
    ret = my_path_match(longComment);        //evaluates to false
    cout<<"should be false = "<<ret<<endl;
}
