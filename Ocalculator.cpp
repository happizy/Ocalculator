#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <regex>
#include <vector>

struct functionAttributes
{
    std::string name;
    uint16_t start;
    uint16_t stop;
    std::string content;
};

std::vector<functionAttributes> parseFileFunctions(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Error while opening the file" << '\n';
        return {};
    }

    std::string line;
    std::vector<functionAttributes> functions;
    std::regex functionRegex(R"(\b(\w+)\s+(\w+)\s*\(([^)]*)\)\s*)");
    int lineNumber = 0;
    bool inFunction = false;
    functionAttributes currentFunction;
    std::string currentFunctionContent = "";
    int braceCount = 0;

    while (std::getline(file, line))
    {
        lineNumber++;
        std::smatch match;

        if (std::regex_search(line, match, functionRegex))
        {
            if (inFunction)
            {
                currentFunction.stop = lineNumber - 1;
                functions.push_back(currentFunction);
            }
            currentFunction.name = match[2].str();
            currentFunction.start = lineNumber;
            inFunction = true;
            braceCount = 0;
        }

        if (inFunction)
        {
            currentFunctionContent.append(line);
            for (char ch : line)
            {
                if (ch == '{')
                {
                    braceCount++;
                }
                else if (ch == '}')
                {
                    braceCount--;
                    if (braceCount == 0)
                    {
                        currentFunction.stop = lineNumber;
                        currentFunctionContent.erase(std::remove(currentFunctionContent.begin(), currentFunctionContent.end(), ' '), currentFunctionContent.end());
                        currentFunction.content = currentFunctionContent;
                        functions.push_back(currentFunction);
                        currentFunctionContent = "";
                        inFunction = false;
                        break;
                    }
                }
            }
        }
    }

    if (inFunction)
    {
        currentFunction.stop = lineNumber;
        functions.push_back(currentFunction);
    }

    file.close();
    return functions;
}

int main(int argc, char const *argv[])
{
    const std::string filePath = "fib.cpp";
    std::vector<functionAttributes> functions = parseFileFunctions(filePath);
    for (const auto &function : functions)
    {
        std::printf("name : %s\nstart : %u\nstop : %u\n\n %s\n-----------------------------\n", function.name.c_str(), function.start, function.stop, function.content.c_str());
    }

    return 0;
}
