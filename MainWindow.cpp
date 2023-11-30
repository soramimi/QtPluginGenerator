#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Global.h"
#include "ProjectGenerator.h"
#include "joinpath.h"
#include "CustomGeneratorDialog.h"
#include <QDebug>
#include <QDirIterator>
#include <QFileDialog>
#include <QMessageBox>
#include <sys/stat.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_browse_destination_clicked()
{
	QString dir = QDir::current().dirName();
	dir = QFileDialog::getExistingDirectory(this, tr("Destination Directory"), dir);
	if (!dir.isEmpty()) {
		ui->lineEdit_destination_dir->setText(dir);
	}
}

void MainWindow::on_pushButton_generate_clicked()
{
	generate2();
}

void MainWindow::on_pushButton_close_clicked()
{
	close();
}

void MainWindow::generate2()
{
	QString template_dir = global->executable_dir / "HelloWorldPlugin";
	QString project_name = ui->lineEdit_project_name->text();
	QString dstdir = ui->lineEdit_destination_dir->text();
	if (!QFileInfo(dstdir).isDir()) return;
	if (QFileInfo(dstdir / project_name).exists()) return;
	if (project_name.isEmpty()) return;
	dstdir = dstdir / project_name + "Plugin";

	bool ok = ProjectGenerator("HelloWorld", project_name.toStdString()).perform(template_dir, dstdir);

	if (ok) {
		QMessageBox::information(this, "", tr("Generated Successfully"));
	} else {
		QMessageBox::critical(this, "", tr("Generation Failed"));
	}
}





void MainWindow::on_pushButton_custom_clicked()
{
	CustomGeneratorDialog dlg(this);
	if (dlg.exec() == QDialog::Accepted) {
		close();
	}
}

