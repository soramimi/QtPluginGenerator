#ifndef PROJECTGENERATOR_H
#define PROJECTGENERATOR_H

#include <string>
#include <vector>

class QString;

class ProjectGenerator {
private:
	std::vector<std::string> srcwords_;
	std::vector<std::string> dstwords_;
	static std::vector<char> internalReplaceWords(const std::string_view &srctext, const std::vector<std::string> &srcwords, const std::vector<std::string> &dstwords);
	static void convertFile(const QString &srcpath, const QString &dstpath, const std::vector<std::string> &srcwords, const std::vector<std::string> &dstwords);
public:
	ProjectGenerator(const std::string_view &srcname, const std::string_view &dstname);
	QString replaceWords(const QString &s);
	bool perform(QString const &srcpath, QString const &dstpath);
};
#endif // PROJECTGENERATOR_H
