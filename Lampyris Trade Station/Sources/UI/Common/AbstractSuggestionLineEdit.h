/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// QT Include(s)
#include <QApplication>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QStringList>
#include <QAbstractItemView>
#include <QKeyEvent>

/*
 * �������� ����
*/
struct AbstractSuggestionData {
public:
	virtual QString toString() { return QString(); }
};

/*
 * ��QListWidget��ItemQWidget����������������ʾ
*/
class AbstractSuggestionItemWidget :public QWidget {
public:
	             AbstractSuggestionItemWidget(QWidget* parent = nullptr):QWidget(parent){}
	virtual void setSuggestionData(const AbstractSuggestionData& data) = 0;
};

/*
 * ��������������ʾ��LineEdit�ĳ����࣬����ʵ������Ҫʵ��getSuggestions����
*/
class AbstractSuggestionLineEdit : public QLineEdit {
	Q_OBJECT
	using                 ItemWidgetFactoryFunc = std::function<AbstractSuggestionItemWidget*(QWidget* parent)>;
	using                 DataList = std::vector<AbstractSuggestionData>;
public:			          
	                      AbstractSuggestionLineEdit(QWidget* parent = nullptr);

	template<typename T>  requires std::is_base_of_v<AbstractSuggestionItemWidget,T>
	void                  registerItemWidgetType();
protected:		          
	void                  keyPressEvent(QKeyEvent* event) override;
	virtual void          getSuggestions(const QString& input) = 0;
protected slots:
	void                  onTextEdited(const QString& input);
	void                  onSuggestionClicked(QListWidgetItem* item);
protected:
	QListWidget*          m_suggestionWidget;
	int                   m_suggestIndex;
	DataList              m_suggestionList;
	ItemWidgetFactoryFunc m_itemWidgetFactoryFunc;
};

template<typename T> requires std::is_base_of_v<AbstractSuggestionItemWidget, T>
inline void AbstractSuggestionLineEdit::registerItemWidgetType() {
	this->m_itemWidgetFactoryFunc = std::move([](QWidget* parent = nullptr) {
		return new T(parent);
	});
}
