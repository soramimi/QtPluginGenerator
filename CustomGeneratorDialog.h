#ifndef CUSTOMGENERATORDIALOG_H
#define CUSTOMGENERATORDIALOG_H

#include <QDialog>

namespace Ui {
class CustomGeneratorDialog;
}

class CustomGeneratorDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CustomGeneratorDialog(QWidget *parent = nullptr);
	~CustomGeneratorDialog();

private slots:
	void on_pushButton_source_path_clicked();

	void on_pushButton_destination_path_clicked();

	void on_pushButton_clicked();

private:
	Ui::CustomGeneratorDialog *ui;
};

#endif // CUSTOMGENERATORDIALOG_H
