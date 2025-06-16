#include <QtTest/QtTest>
#include "ScriptManager.hpp"

class ScriptManagerTests : public QObject {
    Q_OBJECT
private slots:
    void testRunScriptSync_success();
    void testRunScriptSync_fail();
};

void ScriptManagerTests::testRunScriptSync_success() {
    ScriptManager& manager = ScriptManager::getInstance();

    // This test assumes you have a simple script "test_script.py" in your PATH or working directory.
    // Example content for test_script.py:
    //   print("hello")
    QString scriptName = "test_script.py";
    bool ok = false;
    QStringList output = manager.runScriptSync(scriptName, {}, &ok);

    QVERIFY(ok);
    QVERIFY(output.contains("hello"));
}

void ScriptManagerTests::testRunScriptSync_fail() {
    ScriptManager& manager = ScriptManager::getInstance();

    // Try to run a non-existent script
    QString scriptName = "non_existent_script.py";
    bool ok = true;
    QStringList output = manager.runScriptSync(scriptName, {}, &ok);

    QVERIFY(!ok);
    QVERIFY(output.isEmpty());
}

QTEST_MAIN(ScriptManagerTests)
#include "ScriptManagerTests.moc"