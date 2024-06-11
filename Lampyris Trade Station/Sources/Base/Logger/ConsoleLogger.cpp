/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "ConsoleLogger.h"

void ConsoleLogger::LogInfo(const char* message) {
    LogMessage(LogLevel::Info, message);
}

void ConsoleLogger::LogWarning(const char* message) {
    LogMessage(LogLevel::Warning, message);
}

void ConsoleLogger::LogError(const char* message) {
    LogMessage(LogLevel::Error, message);
}

void ConsoleLogger::LogException(const std::exception& exception) {
    LogMessage(LogLevel::Error, exception.what());
}

void ConsoleLogger::LogInfoFormat(const char* format, ...) {
    va_list args;
    va_start(args, format);
    QString message = QString::vasprintf(format, args);
    va_end(args);
    LogInfo(message.toUtf8().constData());
}

void ConsoleLogger::LogWarningFormat(const char* format, ...) {
    va_list args;
    va_start(args, format);
    QString message = QString().vasprintf(format, args);
    va_end(args);
    LogWarning(message.toUtf8().constData());
}

void ConsoleLogger::LogErrorFormat(const char* format, ...) {
    va_list args;
    va_start(args, format);
    QString message = QString().vasprintf(format, args);
    va_end(args);
    LogError(message.toUtf8().constData());
}

ConsoleLogger::ConsoleLogger() {
    // 为应用程序分配一个新的控制台窗口
    if (!::AllocConsole()) {
        std::cerr << "Failed to allocate console." << std::endl;
    }

    // 设置控制台输出为 UTF-8 编码
    ::SetConsoleOutputCP(CP_UTF8);

    // 获取STD输出句柄
    m_handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
}

ConsoleLogger::~ConsoleLogger() {

}

void ConsoleLogger::LogMessage(LogLevel logLevel, const char* message) {
    // 文本颜色
    WORD color = 0;

    // 标题
    QString title = "";

    switch (logLevel) {
    case LogLevel::Info:
        color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
        title = "[INFO]";
        break;
    case LogLevel::Warning:
        color = FOREGROUND_RED | FOREGROUND_GREEN;
        title = "[WARN]";
        break;
    case LogLevel::Error:
        title = "[ERROR]";
        color = FOREGROUND_RED;
        break;
    }

    // 设置控制台输出文本的颜色
    ::SetConsoleTextAttribute(m_handle, color);

    // 输出流
    QTextStream stream(stdout);
    stream << title << ": " << message << "\n";
}
