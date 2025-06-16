#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP

#include <QObject>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <functional>

class ScriptManager : public QObject
{
    Q_OBJECT

public:
    static ScriptManager& getInstance();

    void runScriptAsync(const QString& scriptName,
                        const QStringList& arguments = {},
                        std::function<void(const QStringList&)> onOutput = nullptr,
                        std::function<void(int, QProcess::ExitStatus)> onFinished = nullptr,
                        std::function<void(QProcess::ProcessError)> onError = nullptr);

    QStringList runScriptSync(const QString& scriptName,
                              const QStringList& arguments = {},
                              bool* ok = nullptr); // opțional: returnează succes/fail

private:
    explicit ScriptManager(QObject* parent = nullptr);
    ScriptManager(const ScriptManager&) = delete;
    ScriptManager& operator=(const ScriptManager&) = delete;
};

#endif // SCRIPTMANAGER_HPP
