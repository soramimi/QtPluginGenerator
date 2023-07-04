
#include "MainWindow.h"
#include "Global.h"

#include <QApplication>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDir>
#include "joinpath.h"

int main(int argc, char **argv)
{
	Global g;
	global = &g;
	global->executable_dir = QFileInfo(argv[0]).absoluteDir().absolutePath();
	global->generic_config_dir = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
	global->app_config_dir = global->generic_config_dir / global->organization_name / global->application_name;
	global->config_file_path = global->app_config_dir / (global->application_name + ".ini");
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

