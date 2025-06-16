#include "ScriptManager.hpp"
#include <QDebug>

ScriptManager::ScriptManager(QObject* parent) : QObject(parent) {}

ScriptManager& ScriptManager::getInstance()
{
    static ScriptManager instance;
    return instance;
}

void ScriptManager::runScriptAsync(const QString& scriptName,
                                   const QStringList& arguments,
                                   std::function<void(const QStringList&)> onOutput,
                                   std::function<void(int, QProcess::ExitStatus)> onFinished,
                                   std::function<void(QProcess::ProcessError)> onError)
{
    QProcess* process = new QProcess(this);
    QString program = "python";

    QStringList fullArgs = arguments;
    fullArgs.prepend(scriptName);

    process->setProgram(program);
    process->setArguments(fullArgs);

    QObject::connect(process, &QProcess::readyReadStandardOutput, [=]() {
        QByteArray output = process->readAllStandardOutput();
        QStringList lines = QString::fromUtf8(output).split('\n', Qt::SkipEmptyParts);
        if (onOutput) onOutput(lines);
    });

    QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                     [=](int exitCode, QProcess::ExitStatus exitStatus) {
        if ((exitCode != 0) || (exitStatus != QProcess::NormalExit)) {
            if (onFinished) onFinished(exitCode, exitStatus);
        }
        process->deleteLater();
    });

    QObject::connect(process, &QProcess::errorOccurred, [=](QProcess::ProcessError error) {
        if (onError) onError(error);
        process->deleteLater();
    });

    process->start();
}

QStringList ScriptManager::runScriptSync(const QString& scriptName,
                                         const QStringList& arguments,
                                         bool* ok)
{
    QProcess process;
    QString program = "python";

    QStringList fullArgs = arguments;
    fullArgs.prepend(scriptName);

    process.setProgram(program);
    process.setArguments(fullArgs);

    process.start();
    if (!process.waitForStarted() || !process.waitForFinished(-1)) {
        if (ok) *ok = false;
        qDebug() << "[ScriptManager] Script failed to run:" << scriptName;
        return {};
    }

    if (ok) *ok = true;
    QByteArray output = process.readAllStandardOutput();
    return QString::fromUtf8(output).split('\n', Qt::SkipEmptyParts);
}
