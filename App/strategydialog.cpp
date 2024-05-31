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
        ui->strategyRefreshRate->setCurrentText(strategy->getRefreshRate());
        ui->takeProfitStatus->setChecked(strategy->getTakeProfitStatus());
        ui->hasMA->setChecked(strategy->getHasMA());
        ui->hasRSI->setChecked(strategy->getHasRSI());
        ui->hasAD->setChecked(strategy->getHasAD());
        ui->hasMACD->setChecked(strategy->getHasMACD());
        ui->hasMFI->setChecked(strategy->getHasMFI());
        ui->hasCCI->setChecked(strategy->getHasCCI());
        ui->hasSTOOCH->setChecked(strategy->getHasSTOOCH());
        ui->hasVOLUME->setChecked(strategy->getHasVOLUME());
        ui->hasAROON->setChecked(strategy->getHasAROON());
        ui->takeProfitPercentage->setText(QString::number(strategy->getTakeProfitPercentage()));
        ui->prefeeredBuyIndex->setText(QString::number(strategy->getPrefeeredBuyIndex()));
        ui->prefeeredSellIndex->setText(QString::number(strategy->getPrefeeredSellIndex()));
        ui->macdBlueLineLowLimit->setText(QString::number(strategy->getMACDBlueLineLowLimit()));
        ui->macdBlueLineHighLimit->setText(QString::number(strategy->getMACDBlueLineHighLimit()));
        ui->macdRedLineLowLimit->setText(QString::number(strategy->getMACDRedLineLowLimit()));
        ui->macdRedLineHighLimit->setText(QString::number(strategy->getMACDRedLineHighLimit()));
        ui->rsiLineLowLimit->setText(QString::number(strategy->getRSILineLowLimit()));
        ui->rsiLineHighLimit->setText(QString::number(strategy->getRSILineHighLimit()));
        ui->acumDistLowLimit->setText(QString::number(strategy->getACUMDISTLowLimit()));
        ui->acumDistHighLimit->setText(QString::number(strategy->getACUMDISTHighLimit()));
        ui->maLength->setText(QString::number(strategy->getMALength()));
        ui->mfiLowLimit->setText(QString::number(strategy->getMFILowLimit()));
        ui->mfiHighLimit->setText(QString::number(strategy->getMFIHighLimit()));
        ui->cciLowLimit->setText(QString::number(strategy->getCCILowLimit()));
        ui->cciHighLimit->setText(QString::number(strategy->getCCIHighLimit()));
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
    QString refreshRate = ui->strategyRefreshRate->currentText();
    bool takeProfitStatus = ui->takeProfitStatus->isChecked();
    bool hasMa = ui->hasMA->isChecked();
    bool hasRSI = ui->hasRSI->isChecked();
    bool hasAD = ui->hasAD->isChecked();
    bool hasMACD = ui->hasMACD->isChecked();
    bool hasMFI = ui->hasMFI->isChecked();
    bool hasCCI = ui->hasCCI->isChecked();
    bool hasSTOOCH = ui->hasSTOOCH->isChecked();
    bool hasVOLUME = ui->hasVOLUME->isChecked();
    bool hasAROON = ui->hasAROON->isChecked();
    int takeProfitPercentage = ui->takeProfitPercentage->text().toInt();
    int prefeeredBuyIndex = ui->prefeeredBuyIndex->text().toInt();
    int prefeeredSellIndex = ui->prefeeredSellIndex->text().toInt();
    int macdBlueLineLowLimit = ui->macdBlueLineLowLimit->text().toInt();
    int macdBlueLineHighLimit = ui->macdBlueLineHighLimit->text().toInt();
    int macdRedLineLowLimit = ui->macdRedLineLowLimit->text().toInt();
    int macdRedLineHighLimit = ui->macdRedLineHighLimit->text().toInt();
    int rsiLineLowLimit = ui->rsiLineLowLimit->text().toInt();
    int rsiLineHighLimit = ui->rsiLineHighLimit->text().toInt();
    int acumDistLowLimit = ui->acumDistLowLimit->text().toInt();
    int acumDistHighLimit = ui->acumDistHighLimit->text().toInt();
    int maLength = ui->maLength->text().toInt();
    int mfiLowLimit = ui->mfiLowLimit->text().toInt();
    int mfiHighLimit = ui->mfiHighLimit->text().toInt();
    int cciLowLimit = ui->cciLowLimit->text().toInt();
    int cciHighLimit = ui->cciHighLimit->text().toInt();

    strategy = std::make_shared<Strategy>(name, timeFrame, refreshRate, takeProfitStatus, hasMa, hasRSI, hasAD, hasMACD,
                                          hasMFI, hasCCI, hasSTOOCH, hasVOLUME, hasAROON, takeProfitPercentage,
                                          prefeeredBuyIndex, prefeeredSellIndex, macdBlueLineLowLimit, macdBlueLineHighLimit,
                                          macdRedLineLowLimit, macdRedLineHighLimit, rsiLineLowLimit, rsiLineHighLimit,
                                          acumDistLowLimit, acumDistHighLimit, maLength, mfiLowLimit, mfiHighLimit,
                                          cciLowLimit, cciHighLimit);

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

