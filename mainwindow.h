#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QStatusBar>
#include <QJsonObject>

// 异步后台清算引擎
class ContractWorker : public QObject {
    Q_OBJECT
public slots:
    void doGenerateTask(const QJsonObject& formData);
signals:
    void taskFinished(const QString& msg);
    void taskError(const QString& err);
};

// 智能化法务主窗体
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
signals:
    void startTask(const QJsonObject& formData);
private slots:
    void onGenerationSuccess(const QString& msg);
    void onGenerationError(const QString& err);
private:
    QLineEdit *entryCode, *entryAName, *entryATax, *entryATel, *entryABank, *entryAAcc;
    QLineEdit *entryBName, *entryBTax, *entryBTel, *entryBBank, *entryBAcc;
    QLineEdit *entryCarNo, *entryWorkContent, *entryStartDate, *entryEndDate, *entryWorkAddr, *entryPayDay;
    QPushButton *btnSwap, *btnTmpl, *btnImport, *btnGen;
    QTextEdit *textAnnex;
    QStatusBar *statusBar;
};

#endif // MAINWINDOW_H
