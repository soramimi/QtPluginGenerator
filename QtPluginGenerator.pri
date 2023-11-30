
QT = core gui widgets
TEMPLATE = app
TARGET = QtPluginGenerator

SOURCES += main.cpp \
	CustomGeneratorDialog.cpp \
	Global.cpp \
	MainWindow.cpp \
	ProjectGenerator.cpp \
	joinpath.cpp

FORMS += \
	CustomGeneratorDialog.ui \
	MainWindow.ui

HEADERS += \
	CustomGeneratorDialog.h \
	Global.h \
	MainWindow.h \
	ProjectGenerator.h \
	joinpath.h
