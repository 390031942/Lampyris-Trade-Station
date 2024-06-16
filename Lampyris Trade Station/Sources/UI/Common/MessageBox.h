/*
 * Copyright (c) HongJin Investment Ltd. All rights reserved.
*/

// QT Include(s)
#include <QMessageBox>

// Project Include(s)
#include <Base/Singleton.h>

namespace SingletonImpl {

class MessageBoxClass:public Singleton<MessageBoxClass> {
public:
	void info(const QString& info);

	void warning(const QString& warn);

	void error(const QString& error);
};

} // end of namespace "SingletonImpl" 

#ifdef MessageBox
#undef MessageBox
#endif // !MessageBox

#define MessageBox SingletonImpl::MessageBoxClass::getInstance()
