#ifndef PROJECTGENERATOR_H
#define PROJECTGENERATOR_H

#include <string>
#include <vector>

class QString;

class ProjectGenerator {
public:
	bool perform(QString const &srcpath, QString const &dstpath, const std::string_view &srcname, const std::string_view &dstname);
};
#endif // PROJECTGENERATOR_H
