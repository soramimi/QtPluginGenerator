#ifndef HELLOWORLDPLUGIN_H
#define HELLOWORLDPLUGIN_H

#include <QtCore/qplugin.h>
#include "HelloWorldInterface.h"

class HelloWorldPlugin : public QObject, public HelloWorldInterface {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "mynamespace.HelloWorldPlugin" FILE "helloworldplugin.json")
	Q_INTERFACES(HelloWorldInterface)
public:
	HelloWorld *create() override
	{
		return new HelloWorld();
	}
};

#endif // HELLOWORLDPLUGIN_H
