
QT = core

CONFIG(release,debug|release):TARGET = helloworldplugin
CONFIG(debug,debug|release):TARGET = helloworldplugind
TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$PWD/_bin

unix:LIBS += -ldl
win32:LIBS += -lole32 -loleaut32

HEADERS += \
	src/HelloWorld.h \
	src/HelloWorldInterface.h \
	src/HelloWorldPlugin.h
SOURCES += \
	src/HelloWorld.cpp \
	src/HelloWorldInterface.cpp \
	src/HelloWorldPlugin.cpp

DISTFILES += \
	helloworldplugin.json
