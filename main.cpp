
#include "ProjectGenerator.h"
#include <cctype>
#include <cstring>
#include <sys/stat.h>

#ifdef USE_QT
#include "gui/Global.h"
#include "gui/MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
#include "joinpath.h"
#endif

std::string to_string(std::string_view const &v)
{
	return {v.data(), v.size()};
}

int main(int argc, char **argv)
{
#ifdef USE_QT
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
#else
	bool usage = false;
	
	char const *rule = nullptr;
	char const *srcpath = nullptr;
	char const *dstpath = nullptr;
	for (int argi = 1; argi < argc; argi++) {
		char const *arg = argv[argi];
		if (*arg == '-') {
			if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
				usage = true;
			} else {
				fprintf(stderr, "unknown option: %s\n", arg);
			}
		} else {
			if (!rule) {
				rule = arg;
			} else if (!srcpath) {
				srcpath = arg;
			} else if (!dstpath) {
				dstpath = arg;
			} else {
				fprintf(stderr, "syntax error: %s\n", arg);
			}
		}

	}
	std::string_view srcsym;
	std::string_view dstsym;
	if (!usage) {
		if (rule) {
			char const *p1 = strchr(rule, ':');
			if (p1) {
				srcsym = {rule, size_t(p1 - rule)};
				p1++;
				char const *p2 = strchr(p1, ':');
				if (!p2) {
					dstsym = p1;
				}
			}
			auto issymbol = [](std::string_view const &s){
				int n = s.size();
				if (n > 0) {
					if (isalnum((unsigned char)s[0])) {
						for (int i = 1; i < n; i++) {
							if (!isalnum((unsigned char)s[i]) && s[i] != '_') {
								return false;
							}
						}
						return true;
					}
				}
				return false;
			};
			if (!issymbol(srcsym)) {
				fprintf(stderr, "source symbol is not specified\n");
				exit(1);
			}
			if (!issymbol(dstsym)) {
				fprintf(stderr, "destination symbol is not specified\n");
				exit(1);
			}
		} else {
			fprintf(stderr, "rule is not specified\n");
			exit(1);
		}
		
		if (!srcpath) {
			fprintf(stderr, "source path is not specified\n");
			exit(1);
		}
		
		if (!dstpath) {
			fprintf(stderr, "destination path is not specified\n");
			exit(1);
		}
	}
	
	if (usage) {
		fprintf(stderr, "usage: projector <rule> <srcpath> <dstpath>\n");
		fprintf(stderr, "  rule: <srcsym>:<dstsym>\n");
		fprintf(stderr, "   - srcsym: source symbol\n");
		fprintf(stderr, "   - dstsym: destination symbol\n");
		fprintf(stderr, "  srcpath: source path\n");
		fprintf(stderr, "  dstpath: destination path\n");
		exit(1);
	}
	
	std::string dstpath2;
	std::string s = to_string(srcsym);
	std::string d = to_string(dstsym);
	ProjectGenerator gen(s, d);

	struct stat srcst;
	if (stat(srcpath, &srcst) != 0) {
		fprintf(stderr, "no such file or directory: %s\n", srcpath);
		exit(1);
	}

	dstpath2 = dstpath;
	struct stat dstst;
	if (stat(dstpath, &dstst) == 0) {
		if (S_ISDIR(dstst.st_mode)) {
			char const *p = strrchr(srcpath, '/');
			if (p) {
				p++;
			} else {
				p = srcpath;
			}
			dstpath2 += '/';
			dstpath2 += gen.replaceWords(p);
		} else {
			fprintf(stderr, "already existing: %s\n", dstpath);
			exit(1);
		}
	}

	gen.perform(srcpath, dstpath2);

	return 0;
#endif
}

