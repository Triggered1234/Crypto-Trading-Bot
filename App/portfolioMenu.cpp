#include "portfolioMenu.h"
#include "./ui_portfolioMenu.h"

PortfolioMenu::PortfolioMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form) // Initialize with Ui::Form
{
    ui->setupUi(this);
}


PortfolioMenu::~PortfolioMenu()
{
    delete ui;
}
