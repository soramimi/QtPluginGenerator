
TARGET = QtPruginGenerator
TEMPLATE = app
QT = core gui widgets

DEFINES += USE_QT

SOURCES += \
	joinpath.cpp \
	ProjectGenerator.cpp \
	gui/CustomGeneratorDialog.cpp \
	gui/Global.cpp \
	gui/MainWindow.cpp \
	main.cpp

HEADERS += \
	joinpath.h \
	ProjectGenerator.h \
	gui/CustomGeneratorDialog.h \
	gui/Global.h \
	gui/MainWindow.h \
	gui/ProjectGenerator.h

FORMS += \
	gui/CustomGeneratorDialog.ui \
	gui/MainWindow.ui

