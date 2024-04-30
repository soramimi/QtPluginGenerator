#ifndef HELLOWORLDINTERFACE_H
#define HELLOWORLDINTERFACE_H

#include <QtPlugin>
#include "HelloWorld.h"

class HelloWorldInterface {
public:
	HelloWorldInterface();
	virtual ~HelloWorldInterface() {}
	virtual HelloWorld *create() = 0;
};

Q_DECLARE_INTERFACE(HelloWorldInterface, "mynamespace.HelloWorldPlugin/1.0")

#endif // HELLOWORLDINTERFACE_H
