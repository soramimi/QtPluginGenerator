#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
private:
	Ui::MainWindow *ui;
private:
	void generate();
	void generate2();
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private slots:
	void on_pushButton_browse_destination_clicked();
	void on_pushButton_generate_clicked();
	void on_pushButton_close_clicked();
};

#endif // MAINWINDOW_H
