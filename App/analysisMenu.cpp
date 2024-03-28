#include "analysisMenu.h"
#include "./ui_analysisMenu.h"

AnalysisMenu::AnalysisMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form) // Initialize with Ui::Form
{
    ui->setupUi(this);
}

AnalysisMenu::~AnalysisMenu()
{
    delete ui;
}
