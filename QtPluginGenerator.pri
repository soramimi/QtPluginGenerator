
QT = core gui widgets
TEMPLATE = app
TARGET = QtPluginGenerator

SOURCES += main.cpp \
	Global.cpp \
	MainWindow.cpp \
	ProjectGenerator.cpp \
	joinpath.cpp

FORMS += \
	MainWindow.ui

HEADERS += \
	Global.h \
	MainWindow.h \
	ProjectGenerator.h \
	joinpath.h
