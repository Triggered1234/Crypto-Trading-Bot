// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_portfolioButton_clicked();
    void on_analysisButton_clicked();
    void on_strategiesButton_clicked();
    void on_riskManagementButton_clicked();
    void on_portfolioBackButton_clicked();
    void on_analysisBackButton_clicked();
    void on_riskManagementBackButton_clicked();
    void on_strategiesBackButton_clicked();
    void on_exitButton_clicked();

    void on_apiLoginButton_clicked();

    void on_demoModeToggleButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
