#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <QObject>

class HelloWorld : public QObject {
	Q_OBJECT
public:
	HelloWorld();
	~HelloWorld();

	virtual QString func(QString const &a, QString const &b);
};

#endif // HELLOWORLD_H
