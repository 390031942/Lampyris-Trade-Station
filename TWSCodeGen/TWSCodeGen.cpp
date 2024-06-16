// TWSCodeGen.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// 函数用于将函数名转换为Qt信号名
std::string generateSignalName(const std::string& functionName) {
    std::string a("onRes");
    char b = ((char)functionName[0] - 'a' + 'A');
    std::string c = functionName.substr(1);
    return a + b + c;
}

// 函数用于生成Qt信号声明
std::string generateSignalDeclaration(const std::string& functionSignature) {
    std::string returnType = "void";
    std::string functionName = "";
    std::string parameters = "";
    size_t startPos = functionSignature.find("virtual void") + std::string("virtual void").length() +1;
    size_t endPos = functionSignature.find('(', startPos);

    // 提取函数名
    functionName = functionSignature.substr(startPos, endPos - startPos);
    functionName = generateSignalName(functionName);

    // 提取参数列表
    startPos = endPos;
    endPos = functionSignature.find(')', startPos);
    parameters = functionSignature.substr(startPos, endPos - startPos + 1);

    // 生成Qt信号声明
    return "\tvoid " + functionName + parameters;
}

int main(){
    std::ifstream ifs("code.txt");
    std::string line;
    std::vector<std::string> inputLines;
    std::vector<std::string> outputLines;

    while (std::getline(ifs, line)) {
        inputLines.push_back(line); // 将读取的行添加到数组中
    }

    auto str = generateSignalDeclaration(inputLines[0]);

    std::string eventManagerCode = std::string() +
        "class EventManager:public SingletonQObject<EventManager> {\n"
        "    Q_OBJECT\n"
        "Q_SIGNALS:\n";

    for (const std::string& line: inputLines) {
        eventManagerCode += generateSignalDeclaration(line) + ";\n";
    }
     
    eventManagerCode += "};\n";

    return 0;
}