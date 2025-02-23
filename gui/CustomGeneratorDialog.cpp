#include "CustomGeneratorDialog.h"
#include "ui_CustomGeneratorDialog.h"
#include "Projector.h"
#include "joinpath.h"
#include <QFileDialog>
#include <QMessageBox>
#include <string_view>

CustomGeneratorDialog::CustomGeneratorDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CustomGeneratorDialog)
{
	ui->setupUi(this);
}

CustomGeneratorDialog::~CustomGeneratorDialog()
{
	delete ui;
}

void CustomGeneratorDialog::on_pushButton_source_path_clicked()
{
	QString dir;
    dir = QFileDialog::getExistingDirectory(this, tr("Source Path"), dir);
	if (!dir.isEmpty()) {
		ui->lineEdit_source_path->setText(dir);
	}
}

void CustomGeneratorDialog::on_pushButton_destination_path_clicked()
{
	QString dir;
    dir = QFileDialog::getExistingDirectory(this, tr("Destination Path"), dir);
	if (!dir.isEmpty()) {
		ui->lineEdit_destination_path->setText(dir);
	}
}

void CustomGeneratorDialog::on_pushButton_clicked()
{
	QString source_dir = ui->lineEdit_source_path->text();
	QFileInfo info(source_dir);
	if (!info.exists()) return;

	QString dstdir = ui->lineEdit_destination_path->text();

	QString keyword = ui->lineEdit_keyword->text();
	QString project_name = ui->lineEdit_target->text();
	if (!QFileInfo(dstdir).isDir()) return;
	if (project_name.isEmpty()) return;

	Projector gen(keyword.toStdString(), project_name.toStdString());
	dstdir = dstdir / gen.replaceWords(info.fileName());
	if (QFileInfo(dstdir).exists()) return;

	bool ok = gen.perform(source_dir, dstdir);

	if (ok) {
		QMessageBox::information(this, "", tr("Generated Successfully"));
	} else {
		QMessageBox::critical(this, "", tr("Generation Failed"));
	}
}
