/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/
// Project Include(s)
#include "AbstractSuggestionLineEdit.h"

AbstractSuggestionLineEdit::AbstractSuggestionLineEdit(QWidget* parent) : QLineEdit(parent) {
	m_suggestionWidget = new QListWidget(this);
	m_suggestionWidget->setWindowFlags(Qt::ToolTip);
	m_suggestionWidget->setFocusPolicy(Qt::NoFocus);
	m_suggestionWidget->hide();

	QObject::connect(this, &QLineEdit::textEdited, this, &AbstractSuggestionLineEdit::onTextEdited);
	QObject::connect(m_suggestionWidget, &QListWidget::itemClicked, this, &AbstractSuggestionLineEdit::onSuggestionClicked);
}

void AbstractSuggestionLineEdit::keyPressEvent(QKeyEvent* event) {
	if (m_suggestionWidget->isVisible()) {
		auto suggestText = this->m_suggestionList[this->m_suggestIndex].toString();

		switch (event->key()) {
		case Qt::Key_Up:
			this->m_suggestIndex = std::clamp(this->m_suggestIndex - 1, 0, (int)this->m_suggestionList.size() - 1);
			m_suggestionWidget->setFocus();
			m_suggestionWidget->setCurrentRow(this->m_suggestIndex);
			return;
		case Qt::Key_Down:
			this->m_suggestIndex = std::clamp(this->m_suggestIndex + 1, 0, (int)this->m_suggestionList.size() - 1);
			m_suggestionWidget->setFocus();
			m_suggestionWidget->setCurrentRow(this->m_suggestIndex);
			return;
		case Qt::Key_Escape:
			m_suggestionWidget->hide();
			return;
		case Qt::Key_Return:
			this->setText(suggestText);
			emit suggestedTextChanged(suggestText);
			m_suggestionWidget->hide();
			return;
		default:
			break;
		}
	}
	QLineEdit::keyPressEvent(event);
}

void AbstractSuggestionLineEdit::onTextEdited(const QString& input) {
	if (input.isEmpty()) {
		m_suggestionWidget->hide();
		return;
	}

	// 文本不为空就重新计算联想词
	getSuggestions(input);

	if (m_suggestionList.empty()) {
		m_suggestionWidget->hide();
		return;
	}

	m_suggestionWidget->clear();
	
	// 设置Item列表
	for (int i = 0; i < this->m_suggestionList.size(); i++) {
		QListWidgetItem* item = new QListWidgetItem;
		AbstractSuggestionItemWidget* itemWidget = this->m_itemWidgetFactoryFunc(m_suggestionWidget);
		itemWidget->setSuggestionData(this->m_suggestionList[i]);
		m_suggestionWidget->addItem(item);
		m_suggestionWidget->setItemWidget(item, itemWidget);
	}

	// 恢复默认选中第0个
	m_suggestIndex = 0;
	m_suggestionWidget->setCurrentRow(0);

	QPoint pos = mapToGlobal(QPoint(0, height()));
	m_suggestionWidget->move(pos);
	m_suggestionWidget->show();
	m_suggestionWidget->setFixedWidth(this->width());
}

void AbstractSuggestionLineEdit::onSuggestionClicked(QListWidgetItem* item) {
	setText(item->text());
	m_suggestionWidget->hide();
}