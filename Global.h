#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

class Global {
public:
	QString organization_name = "soramimi.jp";
	QString application_name = "QtPluginGenerator";
	QString executable_dir;
	QString generic_config_dir;
	QString app_config_dir;
	QString config_file_path;
};

extern Global *global;

#endif // GLOBAL_H
