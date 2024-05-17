#ifndef INITIATEDSTRATEGY_H
#define INITIATEDSTRATEGY_H

#include <QDialog>

namespace Ui {
class InitiatedStrategy;
}

class InitiatedStrategy : public QDialog
{
    Q_OBJECT

public:
    explicit InitiatedStrategy(QWidget *parent = nullptr);
    ~InitiatedStrategy();

private:
    Ui::InitiatedStrategy *ui;
};

#endif // INITIATEDSTRATEGY_H
