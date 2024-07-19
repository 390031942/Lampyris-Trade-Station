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
 * 联想数据 基类
*/
struct AbstractSuggestionData {
public:
	virtual QString toString() { return QString(); }
};

/*
 * 在QListWidget的ItemQWidget，用于联想数据显示
*/
class AbstractSuggestionItemWidget :public QWidget {
public:
	             AbstractSuggestionItemWidget(QWidget* parent = nullptr):QWidget(parent){}
	virtual void setSuggestionData(const AbstractSuggestionData& data) = 0;
};

/*
 * 包含输入联想提示的LineEdit的抽象类，具体实现类需要实现getSuggestions方法
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
