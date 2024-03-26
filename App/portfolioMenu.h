#ifndef PORTFOLIOMENU_H
#define PORTFOLIOMENU_H

#include <QWidget>

namespace Ui {
class Form;
}

class PortfolioMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PortfolioMenu(QWidget *parent = nullptr);
    ~PortfolioMenu();

private:
    Ui::Form *ui; // Correct the type of ui member
};

#endif // PORTFOLIOMENU_H
