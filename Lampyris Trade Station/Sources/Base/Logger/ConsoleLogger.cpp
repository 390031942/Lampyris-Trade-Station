/*
/* Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "ConsoleLogger.h"

void ConsoleLogger::logInfo(const char* message) {
    logMessage(LogLevel::Info, message);
}

void ConsoleLogger::logWarning(const char* message) {
    logMessage(LogLevel::Warning, message);
}

void ConsoleLogger::logError(const char* message) {
    logMessage(LogLevel::Error, message);
}

void ConsoleLogger::logException(const std::exception& exception) {
    logMessage(LogLevel::Error, exception.what());
}

void ConsoleLogger::logInfoFormat(const char* format, ...) {
    va_list args;
    va_start(args, format);
    QString message = QString::vasprintf(format, args);
    va_end(args);
    logInfo(message.toUtf8().constData());
}

void ConsoleLogger::logWarningFormat(const char* format, ...) {
    va_list args;
    va_start(args, format);
    QString message = QString().vasprintf(format, args);
    va_end(args);
    logWarning(message.toUtf8().constData());
}

void ConsoleLogger::logErrorFormat(const char* format, ...) {
    va_list args;
    va_start(args, format);
    QString message = QString().vasprintf(format, args);
    va_end(args);
    logError(message.toUtf8().constData());
}

ConsoleLogger::ConsoleLogger() {
    // ΪӦ�ó������һ���µĿ���̨����
    if (!::AllocConsole()) {
        std::cerr << "Failed to allocate console." << std::endl;
    }

    // ���ÿ���̨���Ϊ UTF-8 ����
    ::SetConsoleOutputCP(CP_UTF8);

    // ��ȡSTD������
    m_handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
}

ConsoleLogger::~ConsoleLogger() {

}

void ConsoleLogger::logMessage(LogLevel logLevel, const char* message) {
    // �ı���ɫ
    WORD color = 0;

    // ����
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

    // ���ÿ���̨����ı�����ɫ
    ::SetConsoleTextAttribute(m_handle, color);

    // �����
    QTextStream stream(stdout);
    stream << title << ": " << message << "\n";
}
