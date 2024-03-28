// mainwindow.cpp

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , portfolioMenu(new PortfolioMenu(this)) // Initialize the PortfolioMenu instance
{
    ui->setupUi(this);
    connect(ui->portfolioButton, &QPushButton::clicked, this, &MainWindow::on_portfolioButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui; //delet
}
/**
 * Portfolio button action,
 * Shows the portfolio menu,
 * Hides the main menu
*/
void MainWindow::on_portfolioButton_clicked()
{
    if (portfolioMenu) {
        portfolioMenu->show(); // Show the PortfolioMenu
        centralWidget()->hide();
    } else {
        qDebug() << "PortfolioMenu is not initialized properly";
    }
}

