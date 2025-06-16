#include "../include/strategydialog.hpp"
#include "ui/ui_strategydialog.h"
#include "../include/mainwindow.hpp"
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
        QMap<QString, std::shared_ptr<TechnicalIndicators::TechnicalIndicator>> indicators = strategy->getIndicators();
        ui->strategyNameInput->setText(strategy->getName());
        ui->strategyTimeFrame->setCurrentText(strategy->getTimeFrame());
        ui->strategyRefreshRate->setCurrentText(strategy->getRefreshRate());
        ui->takeProfitStatus->setChecked(strategy->getTakeProfitStatus());
        ui->hasMA->setChecked(indicators.contains("MA"));
        ui->hasRSI->setChecked(indicators.contains("RSI"));
        ui->hasAD->setChecked(indicators.contains("ACUMDIST"));
        ui->hasMACD->setChecked(indicators.contains("MACD"));
        ui->hasMFI->setChecked(indicators.contains("MFI"));
        ui->hasCCI->setChecked(indicators.contains("CCI"));
        ui->hasSTOOCH->setChecked(indicators.contains("STOOCH"));
        ui->hasVOLUME->setChecked(indicators.contains("VOLUME"));
        ui->hasAROON->setChecked(indicators.contains("AROON"));
        ui->takeProfitPercentage->setText(QString::number(strategy->getTakeProfitPercentage()));
        ui->preferredBuyIndex->setText(QString::number(strategy->getPreferredBuyIndex()));
        ui->preferredSellIndex->setText(QString::number(strategy->getPreferredSellIndex()));
        if (indicators.contains("MACD")) {
            auto macdIndicator = dynamic_cast<TechnicalIndicators::MACD *>(indicators["MACD"].get());
            if (macdIndicator) {
                ui->macdBlueLineLowLimit->setText(QString::number(macdIndicator->getMacdBlueLineLowLimit()));
                ui->macdBlueLineHighLimit->setText(QString::number(macdIndicator->getMacdBlueLineHighLimit()));
                ui->macdRedLineLowLimit->setText(QString::number(macdIndicator->getMacdRedLineLowLimit()));
                ui->macdRedLineHighLimit->setText(QString::number(macdIndicator->getMacdRedLineHighLimit()));
            }
        }
        if (indicators.contains("RSI")) {
            auto rsiIndicator = dynamic_cast<TechnicalIndicators::RSI *>(indicators["RSI"].get());
            if (rsiIndicator) {
                ui->rsiLineLowLimit->setText(QString::number(rsiIndicator->getRsiLineLowLimit()));
                ui->rsiLineHighLimit->setText(QString::number(rsiIndicator->getRsiLineHighLimit()));
            }
        }
        if (indicators.contains("ACUMDIST")) {
            auto acumDistIndicator = dynamic_cast<TechnicalIndicators::ACUMDIST *>(indicators["ACUMDIST"].get());
            if (acumDistIndicator) {
                ui->acumDistLowLimit->setText(QString::number(acumDistIndicator->getAcumDistLowLimit()));
                ui->acumDistHighLimit->setText(QString::number(acumDistIndicator->getAcumDistHighLimit()));
            }
        }
        if (indicators.contains("MA")) {
            auto maIndicator = dynamic_cast<TechnicalIndicators::MA *>(indicators["MA"].get());
            if (maIndicator) {
                ui->maLength->setText(QString::number(maIndicator->getMaLength()));
            }
        }
        if (indicators.contains("MFI")) {
            auto mfiIndicator = dynamic_cast<TechnicalIndicators::MFI *>(indicators["MFI"].get());
            if (mfiIndicator) {
                ui->mfiLowLimit->setText(QString::number(mfiIndicator->getMfiLowLimit()));
                ui->mfiHighLimit->setText(QString::number(mfiIndicator->getMfiHighLimit()));
            }
        }
        if (indicators.contains("CCI")) {
            auto cciIndicator = dynamic_cast<TechnicalIndicators::CCI *>(indicators["CCI"].get());
            if (cciIndicator) {
                ui->cciLowLimit->setText(QString::number(cciIndicator->getCciLowLimit()));
                ui->cciHighLimit->setText(QString::number(cciIndicator->getCciHighLimit()));
            }
        }
    }
}

StrategyDialog::~StrategyDialog()
{
    delete ui;
}

void StrategyDialog::on_applyButton_clicked()
{
    QMap<QString, std::shared_ptr<TechnicalIndicators::TechnicalIndicator>> indicators;
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
    int preferredBuyIndex = ui->preferredBuyIndex->text().toInt();
    int preferredSellIndex = ui->preferredSellIndex->text().toInt();
    if(ui->hasMACD->isChecked()) {
        indicators["MACD"] = std::make_shared<TechnicalIndicators::MACD>(
            ui->macdBlueLineLowLimit->text().toInt(),
            ui->macdBlueLineHighLimit->text().toInt(),
            ui->macdRedLineLowLimit->text().toInt(),
            ui->macdRedLineHighLimit->text().toInt()
        );
    }
    if(ui->hasRSI->isChecked()) {
        indicators["RSI"] = std::make_shared<TechnicalIndicators::RSI>(
            ui->rsiLineLowLimit->text().toInt(),
            ui->rsiLineHighLimit->text().toInt()
        );
    }
    if(ui->hasAD->isChecked()) {
        indicators["ACUMDIST"] = std::make_shared<TechnicalIndicators::ACUMDIST>(
            ui->acumDistLowLimit->text().toInt(),
            ui->acumDistHighLimit->text().toInt()
        );
    }
    if(ui->hasMA->isChecked()) {
        indicators["MA"] = std::make_shared<TechnicalIndicators::MA>(
            ui->maLength->text().toInt()
        );
    }
    if(ui->hasMFI->isChecked()) {
        indicators["MFI"] = std::make_shared<TechnicalIndicators::MFI>(
            ui->mfiLowLimit->text().toInt(),
            ui->mfiHighLimit->text().toInt()
        );
    }
    if(ui->hasCCI->isChecked()) {
        indicators["CCI"] = std::make_shared<TechnicalIndicators::CCI>(
            ui->cciLowLimit->text().toInt(),
            ui->cciHighLimit->text().toInt()
        );
    }


    strategy = std::make_shared<Strategy>(
        name, timeFrame, refreshRate, takeProfitStatus, takeProfitPercentage, preferredBuyIndex, preferredSellIndex,
        std::move(indicators)
    );

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

