
QT = core gui widgets
TEMPLATE = app

SOURCES += \
	ProjectGenerator.cpp \
	gui/CustomGeneratorDialog.cpp \
	gui/Global.cpp \
	gui/MainWindow.cpp \
	main.cpp \
	joinpath.cpp

HEADERS += \
	gui/CustomGeneratorDialog.h \
	gui/Global.h \
	gui/MainWindow.h \
	gui/ProjectGenerator.h \
	joinpath.h

FORMS += \
	gui/CustomGeneratorDialog.ui \
	gui/MainWindow.ui

