#include "ProjectGenerator.h"
#include "ui_MainWindow.h"
#include "joinpath.h"
#include <QDirIterator>
#include <QMessageBox>

static inline bool is_upper(char c)
{
	return std::isupper((unsigned char)c);
}

static inline bool is_lower(char c)
{
	return std::islower((unsigned char)c);
}

enum CaseStyle {
	DefaultCase,
	TitleCase,
	UpperCase,
	LowerCase,
};

struct JoinPolicy {
	CaseStyle case_style = DefaultCase;
	char separator = 0;
	JoinPolicy(CaseStyle cs = DefaultCase, char sep = 0)
		: case_style(cs)
		, separator(sep)
	{
	}
};

/**
 * @brief 指定された文字列を単語に分割してリストとして返す
 * @param s 分割する文字列
 * @return 単語のリスト
 */
std::vector<std::string> split(std::string_view const &s)
{
    std::vector<std::string> words;
	char const *p = s.data();
    while (*p != 0) {
        int i = 1;
        while (1) {
            char c = p[i];
            if (c == 0 || (is_upper(c) && is_lower(p[i + 1]))) {
                break;
            }
            i++;
        }
        std::string word(p, i);
        words.push_back(word);
        p += i;
    }
    return words;
}

/**
 * @brief 大文字小文字変換
 * @param s
 * @param cp
 * @return
 */
std::string convert(std::string_view const &s, CaseStyle cp)
{
	std::string ret(s);
	switch (cp) {
	case LowerCase:
		std::transform(ret.cbegin(), ret.cend(), ret.begin(), tolower);
		break;
	case UpperCase:
		std::transform(ret.cbegin(), ret.cend(), ret.begin(), toupper);
		break;
	case TitleCase:
		if (s.size() > 0) {
			std::transform(ret.cbegin(), ret.cend(), ret.begin(), tolower);
			*ret.begin() = toupper(*ret.begin());
		}
		break;
	}
	return ret;
}

#ifdef _WIN32
int strncasecmp(char const *l, const char *r, int n)
{
	return strnicmp(l, r, n);
}
#endif

std::vector<char> ProjectGenerator::internalReplaceWords(std::string_view const &srctext, std::vector<std::string> const &srcwords, std::vector<std::string> const &dstwords)
{
	std::vector<char> newtext;

	auto AppendS = [&](std::string_view const &s){
		newtext.insert(newtext.end(), s.begin(), s.end());
	};

	auto AppendC = [&](char c){
		newtext.push_back(c);
	};

	auto CaseFind = [](std::string_view const &source, std::string_view const &pattern, int pos){
		int n = source.size();
		int m = pattern.size();
		if (m <= n) {
			n -= m;
			for (int i = pos; i <= n; i++) {
				if (strncasecmp(source.data() + i, pattern.data(), m) == 0) {
					return i;
				}
			}
		}
		return -1;
	};

	int pos = 0;
	while (1) {
		int next = CaseFind(srctext, srcwords[0], pos);
		if (next >= pos) {
			int match = 1;
			std::vector<int> vec;
			vec.push_back(next);
			int s = next;
			for (int i = 1; i < srcwords.size(); i++) {
				int end = next + srcwords[i - 1].size();
				int next2 = CaseFind(srctext, srcwords[i], next);
				if (next2 == end || next2 == end + 1) {
					vec.push_back(next2);
					next = next2;
					match++;
				} else {
					next += srcwords[i - 1].size();
					AppendS(srctext.substr(pos, next - pos));
					break;
				}
			}
			if (match == srcwords.size()) {
				AppendS(srctext.substr(pos, s - pos));
				char sep = 0;
				CaseStyle cp = TitleCase;
				for (int i = 0; i < vec.size(); i++) {
					int n = srcwords[i].size();
					int p = vec[i];
					char c = srctext[p];
					char d = srctext[p + 1];
					if (is_upper(c)) {
						if (is_upper(d)) {
							cp = UpperCase;
						}
						if (is_lower(d)) {
							cp = TitleCase;
						}
					} else if (is_lower(c)) {
						if (is_lower(d)) {
							cp = LowerCase;
						}
					}
					if (i < dstwords.size()) {
						AppendS(convert(dstwords[i], cp));
					}
					next = vec[i] + n;
					if (i + 1 < vec.size()) {
						int r = p + n;
						if (r + 1 == vec[i + 1]) {
							sep = srctext[r];
							switch (sep) {
							case ' ':
							case '-':
							case '_':
								break; // ok
							default:
								sep = 0; // invalidate
								break;
							}
							if (sep != 0 && i + 1 < dstwords.size()) {
								AppendC(sep);
							}
						}
						next++;
					}
				}
				for (int i = vec.size(); i < dstwords.size(); i++) {
					if (sep != 0) {
						AppendC(sep);
					}
					AppendS(convert(dstwords[i], cp));
				}
			}
			pos = next;
		} else {
			AppendS(srctext.substr(pos));
			break;
		}
	}

	return newtext;
}

void ProjectGenerator::convertFile(QString const &srcpath, QString const &dstpath, std::vector<std::string> const &srcwords, std::vector<std::string> const &dstwords)
{
	QFile infile(srcpath);
	if (infile.open(QFile::ReadOnly)) {
		auto i = dstpath.lastIndexOf('/');
		if (i > 0) {
			QDir().mkpath(dstpath.mid(0, i));
		}
		QByteArray ba = infile.readAll();
		QFile outfile(dstpath);
		if (outfile.open(QFile::WriteOnly)) {
			auto vec = internalReplaceWords(std::string_view(ba.begin(), ba.size()), srcwords, dstwords);
			outfile.write(vec.data(), vec.size());
		}
	}
}

ProjectGenerator::ProjectGenerator(std::string_view const &srcname, std::string_view const &dstname)
{
	srcwords_ = split(srcname);
	dstwords_ = split(dstname);
}

struct FileItem {
	QString srcpath;
	QString dstpath;
	FileItem() = default;
	FileItem(QString const &srcpath, QString const &dstpath)
		: srcpath(srcpath)
		, dstpath(dstpath)
	{
	}
};

void scandir(QString const &basedir, QString const &absdir, std::vector<FileItem> *out)
{
	QDirIterator it(basedir / absdir);
	while (it.hasNext()) {
		it.next();
		auto info = it.fileInfo();
		auto filename = info.fileName();
		if (filename.startsWith('.')) continue;
		if (info.isDir()) {
			scandir(basedir, absdir / filename, out);
		} else if (info.isFile()) {
			if (filename.endsWith(".user")) continue;
			QString path = absdir / filename;
			// "_."で始まるファイルは、先頭の"_"を削除
			QString dpath = absdir / (filename.startsWith("_.") ? filename.mid(1) : filename);
			out->push_back({path, dpath});
		}
	}
}

QString ProjectGenerator::replaceWords(QString const &s)
{
	std::string t = s.toStdString();
	auto vec = internalReplaceWords(t, srcwords_, dstwords_);
	return QString::fromUtf8(vec.data(), vec.size());
}

bool ProjectGenerator::perform(QString const &srcpath, QString const &dstpath)
{
	std::vector<FileItem> files;
	scandir(srcpath, {}, &files);


	if (QFileInfo::exists(dstpath)) {
		QMessageBox::warning(nullptr, "", "Already existing:\n" + dstpath);
		return false;
	}

	for (FileItem const &item : files) {
		QString s = srcpath / item.srcpath;
		QString d = dstpath / replaceWords(item.dstpath);
		convertFile(s, d, srcwords_, dstwords_);
	}

	return true;
}

