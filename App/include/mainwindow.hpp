// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "strategy.hpp"
#include <QMainWindow>
#include "initiatedstrategy.hpp"
#include "SettingsManager.hpp"
#include "ScriptManager.hpp"

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
    void loadStrategies();
    void editStrategy(const Strategy &selectedStrategy);

private slots:
    void on_portfolioButton_clicked();
    void on_marketsButton_clicked();
    void on_strategiesButton_clicked();
    void on_portfolioBackButton_clicked();
    void on_marketsMenuBackButton_clicked();
    void on_strategiesBackButton_clicked();
    void openTransactionMenu();
    void executeTrade(const QString &coinName, const QString &tradeType);
    void on_exitButton_clicked();
    void updatePriceEvolution();
    void on_apiLoginButton_clicked();
    void on_demoModeToggleButton_toggled(bool checked);
    void on_evolutionBox_currentIndexChanged(int);
    void on_buyButton_clicked();
    void on_sellButton_clicked();
    void on_addStrategyButton_clicked();
    void on_transactionMenuBackButton_clicked();
    void on_deployStrategyButton_clicked();
    void on_quantity_valueChanged(double arg1);
    void on_sellQuantity_valueChanged(double arg1);
    void initiateStrategy(const Strategy &selectedStrategy);

    void on_settingsBackButton_clicked();
    void on_settingsButton_clicked();

    void on_applyButton_clicked();

private:
    std::shared_ptr<InitiatedStrategy> initiatedStrategyDialog;
    Ui::MainWindow *ui;
    QString currentCoinId;
    void clearPortfolioLayout();
    QVector<Strategy> strategies;
    double usdtBalance;
    double currentCoinBalance;
};
#endif // MAINWINDOW_H
