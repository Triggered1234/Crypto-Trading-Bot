#include "strategydialog.h"
#include "ui_strategydialog.h"
#include "mainwindow.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

StrategyDialog::StrategyDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::StrategyDialog), strategy(nullptr), isEditingAnExistingStrategy(false) // Initialize editingExistingStrategy to false
{
    ui->setupUi(this);
}
StrategyDialog::StrategyDialog(const Strategy *strategy, QWidget *parent)
    : QDialog(parent), ui(new Ui::StrategyDialog), strategy(std::make_shared<Strategy>(*strategy)), isEditingAnExistingStrategy(true)
{
    ui->setupUi(this);

    // Initialize the dialog with the provided strategy data
    if (strategy) {
        ui->strategyNameInput->setText(strategy->getName());
        ui->strategyTimeFrame->setCurrentText(strategy->getTimeFrame());
        ui->hasMA->setChecked(strategy->getHasMA());
        ui->hasRSI->setChecked(strategy->getHasRSI());
        ui->hasAD->setChecked(strategy->getHasAD());
        ui->hasMACD->setChecked(strategy->getHasMACD());
        ui->hasMFI->setChecked(strategy->getHasMFI());
        ui->hasCCI->setChecked(strategy->getHasCCI());
        ui->hasSTOOCH->setChecked(strategy->getHasSTOOCH());
        ui->hasVOLUME->setChecked(strategy->getHasVOLUME());
        ui->hasAROON->setChecked(strategy->getHasAROON());
        ui->prefeeredBuyIndex->setText(QString::number(strategy->getPrefeeredBuyIndex()));
        ui->prefeeredSellIndex->setText(QString::number(strategy->getPrefeeredSellIndex()));
        ui->macdBlueLineLowLimit->setText(QString::number(strategy->getMACDBlueLineLowLimit()));
        ui->macdBlueLineHighLimit->setText(QString::number(strategy->getMACDBlueLineHighLimit()));
        ui->macdRedLineLowLimit->setText(QString::number(strategy->getMACDRedLineLowLimit()));
        ui->macdRedLineHighLimit->setText(QString::number(strategy->getMACDRedLineHighLimit()));
        ui->rsiLineLowLimit->setText(QString::number(strategy->getRSILineLowLimit()));
        ui->rsiLineHighLimit->setText(QString::number(strategy->getRSILineHighLimit()));
        // Populate other fields similarly
    }
}

StrategyDialog::~StrategyDialog()
{
    delete ui;
}

void StrategyDialog::on_applyButton_clicked()
{
    QString name = ui->strategyNameInput->text();
    QString timeFrame = ui->strategyTimeFrame->currentText();
    bool hasMa = ui->hasMA->isChecked();
    bool hasRSI = ui->hasRSI->isChecked();
    bool hasAD = ui->hasAD->isChecked();
    bool hasMACD = ui->hasMACD->isChecked();
    bool hasMFI = ui->hasMFI->isChecked();
    bool hasCCI = ui->hasCCI->isChecked();
    bool hasSTOOCH = ui->hasSTOOCH->isChecked();
    bool hasVOLUME = ui->hasVOLUME->isChecked();
    bool hasAROON = ui->hasAROON->isChecked();
    int prefeeredBuyIndex = ui->prefeeredBuyIndex->text().toInt();
    int prefeeredSellIndex = ui->prefeeredSellIndex->text().toInt();
    int macdBlueLineLowLimit = ui->macdBlueLineLowLimit->text().toInt();
    int macdBlueLineHighLimit = ui->macdBlueLineHighLimit->text().toInt();
    int macdRedLineLowLimit = ui->macdRedLineLowLimit->text().toInt();
    int macdRedLineHighLimit = ui->macdRedLineHighLimit->text().toInt();
    int rsiLineLowLimit = ui->rsiLineLowLimit->text().toInt();
    int rsiLineHighLimit = ui->rsiLineHighLimit->text().toInt();

    strategy = std::make_shared<Strategy>(name, timeFrame, hasMa, hasRSI, hasAD, hasMACD, hasMFI,
                                          hasCCI, hasSTOOCH, hasVOLUME, hasAROON, prefeeredBuyIndex,
                                          prefeeredSellIndex, macdBlueLineLowLimit, macdBlueLineHighLimit,
                                          macdRedLineLowLimit, macdRedLineHighLimit, rsiLineLowLimit, rsiLineHighLimit);
    qDebug() << strategy->toString();
}
void StrategyDialog::on_saveButton_clicked()
{
    // Apply changes to the strategy object before saving
    on_applyButton_clicked();

    if (strategy) {
        bool result = false;
        if (isEditingAnExistingStrategy) {
            // Update the strategy in the JSON file
            result = Strategy::updateStrategy(*strategy, "settings.json");
        } else {
            // Add new strategy to the JSON file
            result = Strategy::addNewStrategy(*strategy, "settings.json");
        }

        if (result) {
            emit strategySaved();
        } else {
            qDebug() << "Failed to save strategy to the JSON file.";
        }
    }

    // Close the dialog
    close();
}

void StrategyDialog::setIsEditingAnExistingStrategy(bool status)
{
    this->isEditingAnExistingStrategy = status;
}
bool StrategyDialog::getIsEditingAnExistingStrategy()
{
    return this->isEditingAnExistingStrategy;
}


void StrategyDialog::on_cancelButton_clicked()
{
    close();
}

