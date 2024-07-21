/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "Application.h"
#include <Utility/MemoryUtil.h>
#include <Core/TWSMessageWrapper.h>
#include <Core/TWSEventDispatcher.h>
#include <Base/Localization.h>

// QT Include(s)
#include <QWidget>
#include <QDataStream>
#include <QtNetwork/qlocalsocket.h>
#include <QDateTime>
#include <QIcon>

QApplication*  Application::ms_qtApp;
EWrapper*      Application::ms_wrapper;
EClientSocket* Application::ms_clientSocket;
EReaderSignal* Application::ms_signal;
EReader*       Application::ms_reader;
QSharedMemory  Application::ms_sharedMemory;
QLocalServer   Application::ms_server;
QString        Application::ms_uniqueKey;
QWidget*       Application::ms_topWidget;
QTimer         Application::ms_tickTimer;
long           Application::ms_serverTimestamp;
long           Application::ms_timeStampDiff;
bool           Application::ms_timeStampDiffRecorded;
TickFuncList   Application::ms_tickFuncList;
int            Application::ms_requestId = 0;

bool Application::connect(const QString& ip, int port, int clientId) {
	if (ms_clientSocket == nullptr) {
		return false;
	}
    if (ms_clientSocket->eConnect(ip.toUtf8().constData(), port, clientId)) {
        if (ms_reader == nullptr) {
            ms_reader = new EReader(ms_clientSocket, ms_signal);
        }
        else {
            // 使用 placement new 构造 EReader 对象
            ms_reader = new (ms_reader)EReader(ms_clientSocket, ms_signal);
        }
        return true;
    }
    else {
        return false;
    }
}

void Application::disconnect() {
	if (ms_clientSocket->isConnected()) {
		ms_clientSocket->eDisconnect();
	}
}

ConnectState Application::connectState() {
	if (ms_clientSocket == nullptr) {
		return ConnectState::Disconnected;
	}

	return ms_clientSocket->isConnected() ? ConnectState::Connected : ConnectState::Disconnected;
}

int Application::mainLoop() {
	return ms_qtApp->exec();
}

Application::Application(int argc, char* argv[]) {
    ms_qtApp = new QApplication(argc, argv);

    // TWS initialize
    ms_wrapper = new TWSMessageWrapper();
    ms_signal = new EReaderOSSignal();
    ms_clientSocket = new EClientSocket(ms_wrapper, ms_signal);

    // Timer
    ms_tickTimer.setInterval(1);
    QObject::connect(&ms_tickTimer, &QTimer::timeout, []() {
        // 处理TWS 消息
        Application::tickTwsMessage();

        // 处理TickFunc
        for (int i = 0; i < ms_tickFuncList.size(); i++) {
            ms_tickFuncList[i]();
        }
    });
    ms_tickTimer.start();

    // 绑定监听事件
    TWSEventBind(TWSEventType::onResCurrentTime, [=](long time) {
        ms_serverTimestamp = time;
        // 本地时间戳与服务器时间戳之差
        if (!ms_timeStampDiffRecorded) {
            ms_timeStampDiff = QDateTime::currentDateTime().toTime_t() - time;
            ms_timeStampDiffRecorded = true;
        }
    });

    // App Icon
    setAppIcon(QIcon(":/Resources/Image/Comm/Comm_0001.png"));
}

Application::~Application() {
    LAMPYRIS_SAFE_DELETE(ms_qtApp);
}

void Application::readConfigFromFile() {

}

void Application::tickTwsMessage() {
    if (ms_clientSocket->isConnected() && ms_reader != nullptr) {
        // ms_signal->waitForSignal();
        ms_reader->processMsgs();
    }
}

int Application::getNextRequestId() {
    const int round = 100000;
    if (connectState() != Connected) {
        return 0;
    }

    // 请求ID = 客户端*round + ms_requestId, 其中ms_requestId会自增
    ms_requestId = ms_requestId == (round - 1) ? round + 1 : 1;
    return round * ms_clientSocket->clientId() + round;
}

long Application::getSeverTimestamp() {
    // 不必再向服务器询问时间，只需要根据 本地和服务器时间的差 减去对应偏移 就可以了
    return QDateTime::currentDateTime().toTime_t() - ms_timeStampDiff;
}

QDateTime Application::getSeverDateTime() {
    return QDateTime::fromTime_t(getSeverTimestamp());
}

void Application::addTickFunc(TickFunc func) {
    ms_tickFuncList.push_back(func);
}

bool Application::createAppInstanceMutex() {
    ms_sharedMemory.setKey("lampyris_trade_station");

    // 创建共享内存并且成功，表示是第一个实例
    bool isFirstInstance = ms_sharedMemory.attach() && ms_sharedMemory.create(1);

    // 向共享内存中写入数据,并处理窗口的显示
    if (isFirstInstance) {
        *(static_cast<char*>(ms_sharedMemory.data())) = 1;

        // 监听来自其他实例的消息
        QLocalServer::removeServer("lampyris_trade_station");
        ms_server.listen("lampyris_trade_station");

        QObject::connect(&ms_server, &QLocalServer::newConnection, [=]() {
            // 对于第二实例的Socket连接，无需处理消息发送与接收，直接显示当前实例的窗口就行
            QLocalSocket* client = ms_server.nextPendingConnection();
            if (ms_topWidget != nullptr) {
                ms_topWidget->show();
            }
        });

        return true;
    }
    else {
        // 连接 第一个实例的LocalSocket，如果成功连接就退出当前实例
        QLocalSocket socket;
        socket.connectToServer("lampyris_trade_station");
        if (socket.waitForConnected(1000)) {
            return false;
        }

        return true;
    }
}

QString Application::getAppName() {
    return Localization->format("ApplicationName",LTS_COMPILE_TIME,getVersion());
}

QString Application::getVersion() {
    return Localization->get("ApplicationVerson");
}

void Application::setAppIcon(const QIcon& icon) {
    ms_qtApp->setWindowIcon(icon);
}

