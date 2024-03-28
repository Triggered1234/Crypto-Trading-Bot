// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "portfoliomenu.h"
#include "analysisMenu.h"

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

private:
    Ui::MainWindow *ui;
    PortfolioMenu *portfolioMenu;
    AnalysisMenu *analysisMenu;
};
#endif // MAINWINDOW_H
