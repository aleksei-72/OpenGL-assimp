#include <src/logger/logger.h>

#include <iostream>

const string TAB = "    ";

Logger::Logger()
{
    stream.open("file.log", std::ios::app);
};

Logger::~Logger()
{
    stream.close();
};

void Logger::error(string msg, string description, string file, int line)
{
    string s = getLogMessage("error", msg, description, file, line);
    cerr << s;
    stream << s;
    stream.flush();
}

void Logger::info(string msg, string description, string file, int line)
{
    string s = getLogMessage("info", msg, description, file, line);
    cout << s;
    stream << s;
    stream.flush();
}


string Logger::getLogMessage(string type, string msg, string description, string file, int line)
{
    string str = type + ": " + msg + '\n';

    if (description.length())
    {
        str += TAB + description + '\n';
    }

    str += TAB + "file: " + file + '\n' + TAB + "line: " + to_string(line) + '\n';

    return str + '\n';
}
