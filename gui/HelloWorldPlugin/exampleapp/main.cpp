#include "../src/HelloWorld.h"
#include "../src/HelloWorldInterface.h"
#include <QCoreApplication>
#include <QDebug>
#include <QPluginLoader>
#include <memory>


int main(int argc, char **argv)
{
	QCoreApplication a(argc, argv);

	QPluginLoader loader("helloworldplugin");
	HelloWorldInterface *plugin = dynamic_cast<HelloWorldInterface *>(loader.instance());
	if (plugin) {
		auto p = std::shared_ptr<HelloWorld>(plugin->create());
		QString s = p->func("Hello,", " world");
		qDebug() << s;
	} else {
		qDebug() << "failed to load the plugin";
	}

	return 0;
}



