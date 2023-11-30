#include "CustomGeneratorDialog.h"
#include "ui_CustomGeneratorDialog.h"
#include "ProjectGenerator.h"
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
	QString template_dir = ui->lineEdit_source_path->text();
	QString dstdir = ui->lineEdit_destination_path->text();
	QString keyword = ui->lineEdit_keyword->text();
	QString project_name = ui->lineEdit_target->text();
	if (!QFileInfo(dstdir).isDir()) return;
	if (QFileInfo(dstdir / project_name).exists()) return;
	if (project_name.isEmpty()) return;
	dstdir = dstdir / project_name;

	bool ok = ProjectGenerator().perform(template_dir, dstdir, keyword.toStdString(), project_name.toStdString());

	if (ok) {
		QMessageBox::information(this, "", tr("Generated Successfully"));
	} else {
		QMessageBox::critical(this, "", tr("Generation Failed"));
	}
}

