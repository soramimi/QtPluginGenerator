
TARGET = QtPruginGenerator
TEMPLATE = app
QT = core gui widgets

DEFINES += USE_QT

SOURCES += \
	Projector.cpp \
	joinpath.cpp \
	gui/CustomGeneratorDialog.cpp \
	gui/Global.cpp \
	gui/MainWindow.cpp \
	main.cpp

HEADERS += \
	Projector.h \
	joinpath.h \
	gui/CustomGeneratorDialog.h \
	gui/Global.h \
	gui/MainWindow.h

FORMS += \
	gui/CustomGeneratorDialog.ui \
	gui/MainWindow.ui

