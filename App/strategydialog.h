#ifndef STRATEGYDIALOG_H
#define STRATEGYDIALOG_H

#include <QDialog>
#include <memory>
#include "strategy.h"

namespace Ui {
class StrategyDialog;
}

class StrategyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StrategyDialog(QWidget *parent = nullptr);
    explicit StrategyDialog(const Strategy *strategy, QWidget *parent = nullptr);
    ~StrategyDialog();
    void setIsEditingAnExistingStrategy(bool status);
    bool getIsEditingAnExistingStrategy();

private slots:
    void on_applyButton_clicked();

    void on_saveButton_clicked();

    void on_cancelButton_clicked();

signals:
    void strategySaved();

private:
    Ui::StrategyDialog *ui;
    std::shared_ptr<Strategy> strategy;
    bool isEditingAnExistingStrategy;

};

#endif // STRATEGYDIALOG_H
