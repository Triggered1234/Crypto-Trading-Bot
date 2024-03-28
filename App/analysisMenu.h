#ifndef ANALYSISMENU_H
#define ANALYSISMENU_H

#include <QWidget>

namespace Ui {
class Form;
}

class AnalysisMenu : public QWidget
{
    Q_OBJECT

public:
    explicit AnalysisMenu(QWidget *parent = nullptr);
    ~AnalysisMenu();

private:
    Ui::Form *ui; // Correct the type of ui member
};

#endif // ANALYSISMENU_H
