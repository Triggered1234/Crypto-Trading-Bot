#include "initiatedstrategy.h"
#include "ui_initiatedstrategy.h"

InitiatedStrategy::InitiatedStrategy(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InitiatedStrategy)
{
    ui->setupUi(this);
}

InitiatedStrategy::~InitiatedStrategy()
{
    delete ui;
}
