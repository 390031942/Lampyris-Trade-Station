/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// Project Include(s)
#include "PanelMainUIOneKeyTrade.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <cstdlib> // For std::stof

#pragma execution_character_set("utf-8")

PanelMainUIOneKeyTrade::PanelMainUIOneKeyTrade(QWidget* parent) :QWidget(parent) {
	this->m_ui.setupUi(this);

	// �������
	m_buttonGroupRatio.addButton(this->m_ui.RadioAll, 1);
	m_buttonGroupRatio.addButton(this->m_ui.Radio2, 2);
	m_buttonGroupRatio.addButton(this->m_ui.Radio3, 3);
	m_buttonGroupRatio.addButton(this->m_ui.Radio4, 4);

	QObject::connect(&m_buttonGroupRatio, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &PanelMainUIOneKeyTrade::OnClickRatioButton);

	// �Զ�ֹӯ
	m_buttonGroupSell.addButton(this->m_ui.RadioSellNone, 1);
	m_buttonGroupSell.addButton(this->m_ui.RadioSellOneDotFive, 2);
	m_buttonGroupSell.addButton(this->m_ui.RadioSellTwo, 3);
	m_buttonGroupSell.addButton(this->m_ui.RadioSellThree, 4);
	m_buttonGroupSell.addButton(this->m_ui.RadioSellFive, 5);
	m_buttonGroupSell.addButton(this->m_ui.RadioSellSeven, 6);

	QObject::connect(&m_buttonGroupSell, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &PanelMainUIOneKeyTrade::OnClickAutoSellButton);

	// ��ť��
	QObject::connect(this->m_ui.ButtonBuy, &QPushButton::clicked, this, &PanelMainUIOneKeyTrade::OnClickButtonBuy);
	QObject::connect(this->m_ui.ButtonSell, &QPushButton::clicked, this, &PanelMainUIOneKeyTrade::OnClickButtonSell);
	QObject::connect(this->m_ui.ButtonBuyEmpty, &QPushButton::clicked, this, &PanelMainUIOneKeyTrade::OnClickButtonBuyEmpty);
	QObject::connect(this->m_ui.ButtonSellEmpty, &QPushButton::clicked, this, &PanelMainUIOneKeyTrade::OnClickButtonSellEmpty);
	QObject::connect(this->m_ui.ButtonRefresh, &QPushButton::clicked, this, &PanelMainUIOneKeyTrade::OnClickButtonRefresh);

	// ��Ʊ��Ϣ
	QObject::connect(&m_stockInfoCaptureTimer, &QTimer::timeout, this, &PanelMainUIOneKeyTrade::CaptureStockInfo);

	this->RefreshStockTradeInfo();

	// ����Ϊ�ö�
	// this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint); // ���ô��ڱ�־Ϊʼ���ö�

	this->InitHaltedStockTableView();
	this->InitPreMarketTableView();

	// ��ťĬ��ֵ
	this->m_ui.Radio2->setChecked(true);
	this->m_ratio = 2;
	this->m_ui.RadioSellNone->setChecked(true);
	this->m_autoSellPercentage = 0;
}

PanelMainUIOneKeyTrade::~PanelMainUIOneKeyTrade() {

}

void PanelMainUIOneKeyTrade::OnClickButtonBuy() {
	//if (this->m_stockInfo.code != "") {
	//	float price = std::stof(this->m_stockInfo.price.toStdString()) + 0.01;
	//	price = std::round(price * 100) / 100.0f; // ����100�����������룬Ȼ�����100.0f������λС��
	//
	//	int count = (int)std::floor(this->m_maxCanBuy / this->m_ratio);
	//	// USmartTradeSystem::GetInstance()->ExecuteBuy(this->m_stockInfo.code.toStdString(),count, true, this->m_stockInfo.statusCode == 2);
	//
	//	// ֹӯ���߼�
	//	if (m_autoSellPercentage != 0.0f) {
	//		price = std::stof(this->m_stockInfo.price.toStdString()) * (1 + m_autoSellPercentage * 0.01);
	//		price = std::round(price * 100) / 100.0f; // ����100�����������룬Ȼ�����100.0f������λС��
	//		// USmartTradeSystem::GetInstance()->ExecuteSell(this->m_stockInfo.code.toStdString(), price, count, this->m_stockInfo.statusCode == 2);
	//	}
	//}
}

void PanelMainUIOneKeyTrade::OnClickButtonSell() {
	// if (this->m_stockInfo.code != "") {
	// 	float price = std::stof(this->m_stockInfo.price.toStdString()) - 0.01;
	// 	price = std::round(price * 100) / 100.0f; // ����100�����������룬Ȼ�����100.0f������λС��
	// 
	// 	int count = this->m_maxSellQty;
	// 	// USmartTradeSystem::GetInstance()->ExecuteAutoSell(this->m_stockInfo.code.toStdString(), 999.00, count, false, this->m_stockInfo.statusCode == 2);
	// }
}

void PanelMainUIOneKeyTrade::OnClickButtonBuyEmpty() {

}

void PanelMainUIOneKeyTrade::OnClickButtonSellEmpty() {

}

void PanelMainUIOneKeyTrade::OnClickButtonRefresh() {
	// if (this->m_stockInfo.code != "") {
		// USmartTradeSystem::GetInstance()->ExecuteQueryMaxQuantity(this->m_stockInfo.code, this->m_stockInfo.price);
		// USmartTradeSystem::GetInstance()->ExecuteQueryShortMaxQuantity(this->m_stockInfo.code, this->m_stockInfo.price);
	// }
}

void PanelMainUIOneKeyTrade::OnClickRatioButton(int ratio) {
	this->m_ratio = ratio;
}

void PanelMainUIOneKeyTrade::OnClickAutoSellButton(int mode) {
	switch (mode) {
		case 1:this->m_autoSellPercentage = 0;break;
		case 2:this->m_autoSellPercentage = 1.5;break;
		case 3:this->m_autoSellPercentage = 2;break;
		case 4:this->m_autoSellPercentage = 3;break;
		case 5:this->m_autoSellPercentage = 5;break;
		case 6:this->m_autoSellPercentage = 7;break;
	}
}

void PanelMainUIOneKeyTrade::CaptureStockInfo() {
}

void PanelMainUIOneKeyTrade::RefreshStockTradeInfo() {
	// if (this->m_stockInfo.code == "") {
	// 	this->m_ui.LabelStockCode->setText("���޹�Ʊ��Ϣ");
	// 	return;
	// }
	// if (this->m_stockInfo.name.size() > 20) {
	// 	this->m_stockInfo.name = this->m_stockInfo.name.mid(0,20) + "...";
	// }
	// this->m_ui.LabelStockCode->setText(this->m_stockInfo.code + "(" + this->m_stockInfo.name + ")");
}

/*
void PanelMainUIOneKeyTrade::RefreshHaltedStockList(std::vector<StockTradeInfo>* list) {
	int size = 0;
	// �����������������
	for (int i = 0; i < list->size(); ++i) {
		const auto& data = list->at(i);
		if (data.statusCode == 6 && data.money > 0 ){ //&& Utilities::IsAfterTodayUSMarketOpenTime(data.timeStamp)) {
			QStandardItem* item1 = this->m_HaltedStockModel->item(size, 0);
			QStandardItem* item2 = this->m_HaltedStockModel->item(size, 1);
			QStandardItem* item3 = this->m_HaltedStockModel->item(size, 2);
			QStandardItem* item4 = this->m_HaltedStockModel->item(size, 3);

			if (!item1) {
				 item1 = new QStandardItem(data.code);
				 item2 = new QStandardItem(QString("%0").arg(data.percentage) + "%");
				 item3 = new QStandardItem(Utilities::GetMoneyString(data.money));
				 item4 = new QStandardItem(QString("%0").arg(data.turnOverRate) + "%");

				 this->m_HaltedStockModel->setItem(size, 0, item1);
				 this->m_HaltedStockModel->setItem(size, 1, item2);
				 this->m_HaltedStockModel->setItem(size, 2, item3);
				 this->m_HaltedStockModel->setItem(size, 3, item4);
			}
			else {
				item1->setText(data.code);
				item2->setText(QString("%0").arg(data.percentage) + "%");
				item3->setText(Utilities::GetMoneyString(data.money));
				item4->setText(QString("%0").arg(data.turnOverRate) + "%");
			}

			size++;
		}
	}
	this->m_HaltedStockModel->setRowCount(size);
}
*/

void PanelMainUIOneKeyTrade::InitHaltedStockTableView() {
	// ��������ģ��
	// QStandardItemModel* model = this->m_HaltedStockModel = new QStandardItemModel;
	// model->setColumnCount(4);
	// 
	// // �����еı���
	// model->setHorizontalHeaderLabels(QStringList() << "����" <<"�Ƿ�" << "���" << "����");
	// 
	// this->m_ui.TableHalted->setModel(model); // ����ͼ����ģ��
}

void PanelMainUIOneKeyTrade::InitPreMarketTableView() {
	// ��������ģ��
	// QStandardItemModel* model = this->m_preMarketModel = new TablePreMarketModel;
	// model->setColumnCount(5);
	// // �����еı���
	// model->setHorizontalHeaderLabels(QStringList() << "����" << "��ǰ��" << "��ǰ�Ƿ�" << "��ǰ��" << "ԭ��" <<  "");
	// this->m_ui.TablePreMarket->setItemDelegate(new TablePreMarketModelButtonDelegate());
	// this->m_ui.TablePreMarket->setModel(model); // ����ͼ����ģ��
}