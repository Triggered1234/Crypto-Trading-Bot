#pragma once

#include <QString>
#include <QJsonObject>
#include <memory>
#include <cstdint>

namespace TechnicalIndicators
{

class TechnicalIndicator
{
public:
    virtual ~TechnicalIndicator() = default;

    uint32_t getImportanceIndex() const { return importanceIndex; }
    void setImportanceIndex(uint32_t index) { importanceIndex = index; }

    virtual QJsonObject toJson() const {
        QJsonObject obj;
        obj["type"] = getType();
        obj["importanceIndex"] = static_cast<int>(importanceIndex);
        return obj;
    }

    static std::shared_ptr<TechnicalIndicator> fromJson(const QJsonObject &json);

protected:
    TechnicalIndicator(uint32_t importanceIndex = 0) : importanceIndex(importanceIndex) {}
    virtual QString getType() const = 0;

private:
    uint32_t importanceIndex;
};

class MACD : public TechnicalIndicator
{
public:
    MACD(double macdBlueLineLowLimit, double macdBlueLineHighLimit,
         double macdRedLineLowLimit, double macdRedLineHighLimit,
         uint32_t importanceIndex = 0)
        : TechnicalIndicator(importanceIndex),
          macdBlueLineLowLimit(macdBlueLineLowLimit),
          macdBlueLineHighLimit(macdBlueLineHighLimit),
          macdRedLineLowLimit(macdRedLineLowLimit),
          macdRedLineHighLimit(macdRedLineHighLimit) {}

    QJsonObject toJson() const override {
        QJsonObject obj = TechnicalIndicator::toJson();
        obj["macdBlueLineLowLimit"] = macdBlueLineLowLimit;
        obj["macdBlueLineHighLimit"] = macdBlueLineHighLimit;
        obj["macdRedLineLowLimit"] = macdRedLineLowLimit;
        obj["macdRedLineHighLimit"] = macdRedLineHighLimit;
        return obj;
    }

    static std::shared_ptr<TechnicalIndicator> fromJson(const QJsonObject &json) {
        return std::make_shared<MACD>(
            json["macdBlueLineLowLimit"].toDouble(),
            json["macdBlueLineHighLimit"].toDouble(),
            json["macdRedLineLowLimit"].toDouble(),
            json["macdRedLineHighLimit"].toDouble(),
            static_cast<uint32_t>(json["importanceIndex"].toInt())
        );
    }

    double getMacdBlueLineLowLimit() const { return macdBlueLineLowLimit; }
    double getMacdBlueLineHighLimit() const { return macdBlueLineHighLimit; }
    double getMacdRedLineLowLimit() const { return macdRedLineLowLimit; }
    double getMacdRedLineHighLimit() const { return macdRedLineHighLimit; }
    void setMacdBlueLineLowLimit(double limit) { macdBlueLineLowLimit = limit; }
    void setMacdBlueLineHighLimit(double limit) { macdBlueLineHighLimit = limit; }
    void setMacdRedLineLowLimit(double limit) { macdRedLineLowLimit = limit; }
    void setMacdRedLineHighLimit(double limit) { macdRedLineHighLimit = limit; }

protected:
    QString getType() const override { return "MACD"; }

private:
    double macdBlueLineLowLimit;
    double macdBlueLineHighLimit;
    double macdRedLineLowLimit;
    double macdRedLineHighLimit;
};

class RSI : public TechnicalIndicator {
public:
    RSI(double rsiLineLowLimit, double rsiLineHighLimit, uint32_t importanceIndex = 0)
        : TechnicalIndicator(importanceIndex),
          rsiLineLowLimit(rsiLineLowLimit), rsiLineHighLimit(rsiLineHighLimit) {}

    QJsonObject toJson() const override {
        QJsonObject obj = TechnicalIndicator::toJson();
        obj["rsiLineLowLimit"] = rsiLineLowLimit;
        obj["rsiLineHighLimit"] = rsiLineHighLimit;
        return obj;
    }

    static std::shared_ptr<TechnicalIndicator> fromJson(const QJsonObject &json) {
        return std::make_shared<RSI>(
            json["rsiLineLowLimit"].toDouble(),
            json["rsiLineHighLimit"].toDouble(),
            static_cast<uint32_t>(json["importanceIndex"].toInt())
        );
    }

    double getRsiLineLowLimit() const { return rsiLineLowLimit; }
    double getRsiLineHighLimit() const { return rsiLineHighLimit; }
    void setRsiLineLowLimit(double limit) { rsiLineLowLimit = limit; }
    void setRsiLineHighLimit(double limit) { rsiLineHighLimit = limit; }
protected:
    QString getType() const override { return "RSI"; }

private:
    double rsiLineLowLimit;
    double rsiLineHighLimit;
};

class ACUMDIST : public TechnicalIndicator {
public:
    ACUMDIST(double acumDistLowLimit, double acumDistHighLimit, uint32_t importanceIndex = 0)
        : TechnicalIndicator(importanceIndex),
          acumDistLowLimit(acumDistLowLimit), acumDistHighLimit(acumDistHighLimit) {}

    QJsonObject toJson() const override {
        QJsonObject obj = TechnicalIndicator::toJson();
        obj["acumDistLowLimit"] = acumDistLowLimit;
        obj["acumDistHighLimit"] = acumDistHighLimit;
        return obj;
    }

    static std::shared_ptr<TechnicalIndicator> fromJson(const QJsonObject &json) {
        return std::make_shared<ACUMDIST>(
            json["acumDistLowLimit"].toDouble(),
            json["acumDistHighLimit"].toDouble(),
            static_cast<uint32_t>(json["importanceIndex"].toInt())
        );
    }
    double getAcumDistLowLimit() const { return acumDistLowLimit; }
    double getAcumDistHighLimit() const { return acumDistHighLimit; }
    void setAcumDistLowLimit(double limit) { acumDistLowLimit = limit; }
    void setAcumDistHighLimit(double limit) { acumDistHighLimit = limit; }

protected:
    QString getType() const override { return "ACUMDIST"; }

private:
    double acumDistLowLimit;
    double acumDistHighLimit;
};

class CCI : public TechnicalIndicator {
public:
    CCI(double cciLowLimit, double cciHighLimit, uint32_t importanceIndex = 0)
        : TechnicalIndicator(importanceIndex),
          cciLowLimit(cciLowLimit), cciHighLimit(cciHighLimit) {}

    QJsonObject toJson() const override {
        QJsonObject obj = TechnicalIndicator::toJson();
        obj["cciLowLimit"] = cciLowLimit;
        obj["cciHighLimit"] = cciHighLimit;
        return obj;
    }

    static std::shared_ptr<TechnicalIndicator> fromJson(const QJsonObject &json) {
        return std::make_shared<CCI>(
            json["cciLowLimit"].toDouble(),
            json["cciHighLimit"].toDouble(),
            static_cast<uint32_t>(json["importanceIndex"].toInt())
        );
    }
    double getCciLowLimit() const { return cciLowLimit; }
    double getCciHighLimit() const { return cciHighLimit; }
    void setCciLowLimit(double limit) { cciLowLimit = limit; }
    void setCciHighLimit(double limit) { cciHighLimit = limit; }

protected:
    QString getType() const override { return "CCI"; }

private:
    double cciLowLimit;
    double cciHighLimit;
};

class MFI : public TechnicalIndicator {
public:
    MFI(double mfiLowLimit, double mfiHighLimit, uint32_t importanceIndex = 0)
        : TechnicalIndicator(importanceIndex),
          mfiLowLimit(mfiLowLimit), mfiHighLimit(mfiHighLimit) {}

    QJsonObject toJson() const override {
        QJsonObject obj = TechnicalIndicator::toJson();
        obj["mfiLowLimit"] = mfiLowLimit;
        obj["mfiHighLimit"] = mfiHighLimit;
        return obj;
    }

    static std::shared_ptr<TechnicalIndicator> fromJson(const QJsonObject &json) {
        return std::make_shared<MFI>(
            json["mfiLowLimit"].toDouble(),
            json["mfiHighLimit"].toDouble(),
            static_cast<uint32_t>(json["importanceIndex"].toInt())
        );
    }
    double getMfiLowLimit() const { return mfiLowLimit; }
    double getMfiHighLimit() const { return mfiHighLimit; }
    void setMfiLowLimit(double limit) { mfiLowLimit = limit; }
    void setMfiHighLimit(double limit) { mfiHighLimit = limit; }

protected:
    QString getType() const override { return "MFI"; }

private:
    double mfiLowLimit;
    double mfiHighLimit;
};

class MA : public TechnicalIndicator {
public:
    MA(double maLength, uint32_t importanceIndex = 0)
        : TechnicalIndicator(importanceIndex),
          maLength(maLength) {}

    QJsonObject toJson() const override {
        QJsonObject obj = TechnicalIndicator::toJson();
        obj["maLength"] = maLength;
        return obj;
    }

    static std::shared_ptr<TechnicalIndicator> fromJson(const QJsonObject &json) {
        return std::make_shared<MA>(
            json["maLength"].toDouble(),
            static_cast<uint32_t>(json["importanceIndex"].toInt())
        );
    }
    double getMaLength() const { return maLength; }
    void setMaLength(double length) { maLength = length; }

protected:
    QString getType() const override { return "MA"; }

private:
    double maLength;
};

class VOLUME : public TechnicalIndicator {
public:
    VOLUME(double volumeLowLimit, double volumeHighLimit, uint32_t importanceIndex = 0)
        : TechnicalIndicator(importanceIndex),
          volumeLowLimit(volumeLowLimit), volumeHighLimit(volumeHighLimit) {}

    QJsonObject toJson() const override {
        QJsonObject obj = TechnicalIndicator::toJson();
        obj["volumeLowLimit"] = volumeLowLimit;
        obj["volumeHighLimit"] = volumeHighLimit;
        return obj;
    }

    static std::shared_ptr<TechnicalIndicator> fromJson(const QJsonObject &json) {
        return std::make_shared<VOLUME>(
            json["volumeLowLimit"].toDouble(),
            json["volumeHighLimit"].toDouble(),
            static_cast<uint32_t>(json["importanceIndex"].toInt())
        );
    }
    double getVolumeLowLimit() const { return volumeLowLimit; }
    double getVolumeHighLimit() const { return volumeHighLimit; }
    void setVolumeLowLimit(double limit) { volumeLowLimit = limit; }
    void setVolumeHighLimit(double limit) { volumeHighLimit = limit; }

protected:
    QString getType() const override { return "VOLUME"; }

private:
    double volumeLowLimit;
    double volumeHighLimit;
};

class AROON : public TechnicalIndicator {
public:
    AROON(double aroonUpLowLimit, double aroonUpHighLimit, double aroonDownLowLimit, double aroonDownHighLimit, uint32_t importanceIndex = 0)
        : TechnicalIndicator(importanceIndex),
          aroonUpLowLimit(aroonUpLowLimit), aroonUpHighLimit(aroonUpHighLimit),
          aroonDownLowLimit(aroonDownLowLimit), aroonDownHighLimit(aroonDownHighLimit) {}

    QJsonObject toJson() const override {
        QJsonObject obj = TechnicalIndicator::toJson();
        obj["aroonUpLowLimit"] = aroonUpLowLimit;
        obj["aroonUpHighLimit"] = aroonUpHighLimit;
        obj["aroonDownLowLimit"] = aroonDownLowLimit;
        obj["aroonDownHighLimit"] = aroonDownHighLimit;
        return obj;
    }

    static std::shared_ptr<TechnicalIndicator> fromJson(const QJsonObject &json) {
        return std::make_shared<AROON>(
            json["aroonUpLowLimit"].toDouble(),
            json["aroonUpHighLimit"].toDouble(),
            json["aroonDownLowLimit"].toDouble(),
            json["aroonDownHighLimit"].toDouble(),
            static_cast<uint32_t>(json["importanceIndex"].toInt())
        );
    }
    double getAroonUpLowLimit() const { return aroonUpLowLimit; }
    double getAroonUpHighLimit() const { return aroonUpHighLimit; }
    double getAroonDownLowLimit() const { return aroonDownLowLimit; }
    double getAroonDownHighLimit() const { return aroonDownHighLimit; }
    void setAroonUpLowLimit(double limit) { aroonUpLowLimit = limit; }
    void setAroonUpHighLimit(double limit) { aroonUpHighLimit = limit; }
    void setAroonDownLowLimit(double limit) { aroonDownLowLimit = limit; }
    void setAroonDownHighLimit(double limit) { aroonDownHighLimit = limit; }

protected:
    QString getType() const override { return "AROON"; }

private:
    double aroonUpLowLimit;
    double aroonUpHighLimit;
    double aroonDownLowLimit;
    double aroonDownHighLimit;
};

class STOCH : public TechnicalIndicator {
public:
    STOCH(double stochRedLineLowLimit, double stochRedLineHighLimit, double stochBlueLineLowLimit, double stochBlueLineHighLimit, uint32_t importanceIndex = 0)
        : TechnicalIndicator(importanceIndex),
          stochRedLineLowLimit(stochRedLineLowLimit), stochRedLineHighLimit(stochRedLineHighLimit),
          stochBlueLineLowLimit(stochBlueLineLowLimit), stochBlueLineHighLimit(stochBlueLineHighLimit) {}

    QJsonObject toJson() const override {
        QJsonObject obj = TechnicalIndicator::toJson();
        obj["stochRedLineLowLimit"] = stochRedLineLowLimit;
        obj["stochRedLineHighLimit"] = stochRedLineHighLimit;
        obj["stochBlueLineLowLimit"] = stochBlueLineLowLimit;
        obj["stochBlueLineHighLimit"] = stochBlueLineHighLimit;
        return obj;
    }

    static std::shared_ptr<TechnicalIndicator> fromJson(const QJsonObject &json) {
        return std::make_shared<STOCH>(
            json["stochRedLineLowLimit"].toDouble(),
            json["stochRedLineHighLimit"].toDouble(),
            json["stochBlueLineLowLimit"].toDouble(),
            json["stochBlueLineHighLimit"].toDouble(),
            static_cast<uint32_t>(json["importanceIndex"].toInt())
        );
    }
    double getStochRedLineLowLimit() const { return stochRedLineLowLimit; }
    double getStochRedLineHighLimit() const { return stochRedLineHighLimit; }
    double getStochBlueLineLowLimit() const { return stochBlueLineLowLimit; }
    double getStochBlueLineHighLimit() const { return stochBlueLineHighLimit; }
    void setStochRedLineLowLimit(double limit) { stochRedLineLowLimit = limit; }
    void setStochRedLineHighLimit(double limit) { stochRedLineHighLimit = limit; }
    void setStochBlueLineLowLimit(double limit) { stochBlueLineLowLimit = limit; }
    void setStochBlueLineHighLimit(double limit) { stochBlueLineHighLimit = limit; }

    protected:
    QString getType() const override { return "STOOCH"; }

    private:
    double stochRedLineLowLimit;
    double stochRedLineHighLimit;
    double stochBlueLineLowLimit;
    double stochBlueLineHighLimit;
};

inline std::shared_ptr<TechnicalIndicator> TechnicalIndicator::fromJson(const QJsonObject &json) {
    const QString type = json["type"].toString();

    if (type == "MACD") return MACD::fromJson(json);
    if (type == "RSI") return RSI::fromJson(json);
    if (type == "ACUMDIST") return ACUMDIST::fromJson(json);
    if (type == "CCI") return CCI::fromJson(json);
    if (type == "MFI") return MFI::fromJson(json);
    if (type == "MA") return MA::fromJson(json);
    if (type == "VOLUME") return VOLUME::fromJson(json);
    if (type == "AROON") return AROON::fromJson(json);
    if (type == "STOCH") return STOCH::fromJson(json);

    return nullptr;
}

} // namespace TechnicalIndicators
