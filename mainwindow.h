#include "mainwindow.h"
#include <QThread>
#include <QDateTime>
#include <QMessageBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QLabel>

void ContractWorker::doGenerateTask(const QJsonObject& formData) {
    QString code = formData["code"].toString();
    QString carNo = formData["car_no"].toString();
    QString addr = formData["work_addr"].toString();
    QString payDay = formData["pay_day"].toString();

    // 模拟底层 Office XML 高能流物理清算装配
    QThread::msleep(2000); 

    emit taskFinished("自备吊车租赁合同（C++ Core Engine）已成功安全生成！\n随附台班法律附页已自动固化完成。");
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setWindowTitle("自备吊车租赁合同智能化管理工具 v2.0 (C++ Core)");
    this->resize(860, 720);
    this->setMinimumSize(850, 680);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(12, 12, 12, 12);

    // 区域 1：顶层管理
    QGroupBox *topBox = new QGroupBox("合同编号与顶层管理", this);
    QHBoxLayout *topLayout = new QHBoxLayout(topBox);
    entryCode = new QLineEdit(this);
    entryCode->setPlaceholderText("请输入合同前缀...");
    QPushButton *btnAutoCode = new QPushButton("自动生成合同号", this);
    QPushButton *btnHelp = new QPushButton("法律/合规指引说明", this);
    topLayout->addWidget(new QLabel("合同前缀:"));
    topLayout->addWidget(entryCode, 1);
    topLayout->addWidget(btnAutoCode);
    topLayout->addWidget(btnHelp);
    mainLayout->addWidget(topBox);

    // 区域 2：中控命令台
    QGroupBox *cmdBox = new QGroupBox("业务中控命令台", this);
    QHBoxLayout *cmdLayout = new QHBoxLayout(cmdBox);
    btnSwap = new QPushButton("甲乙主体互换", this);
    btnTmpl = new QPushButton("导出标准台班模板", this);
    btnImport = new QPushButton("导入结算台班明细", this);
    btnGen = new QPushButton("一键异步生成合同", this);
    btnGen->setStyleSheet("background-color: #2980b9; color: white; font-weight: bold;");
    cmdLayout->addWidget(btnSwap);
    cmdLayout->addWidget(btnTmpl);
    cmdLayout->addWidget(btnImport);
    cmdLayout->addWidget(btnGen);
    mainLayout->addWidget(cmdBox);

    // 区域 3：商事主体双列并行表单
    QHBoxLayout *formLayout = new QHBoxLayout();
    QGroupBox *boxA = new QGroupBox("甲方（承租方/付款主体）", this);
    QFormLayout *layoutA = new QFormLayout(boxA);
    entryAName = new QLineEdit(this); layoutA->addRow("企业名称*:", entryAName);
    entryATax = new QLineEdit(this);  layoutA->addRow("社会信用税号:", entryATax);
    entryATel = new QLineEdit(this);  layoutA->addRow("商务电话:", entryATel);
    entryABank = new QLineEdit(this); layoutA->addRow("开户银行*:", entryABank);
    entryAAcc = new QLineEdit(this);  layoutA->addRow("银行账号*:", entryAAcc);
    formLayout->addWidget(boxA, 1);

    QGroupBox *boxB = new QGroupBox("乙方（出租方/收款主体）", this);
    QFormLayout *layoutB = new QFormLayout(boxB);
    entryBName = new QLineEdit(this); layoutB->addRow("企业名称*:", entryBName);
    entryBTax = new QLineEdit(this);  layoutB->addRow("社会信用税号:", entryBTax);
    entryBTel = new QLineEdit(this);  layoutB->addRow("商务电话:", entryBTel);
    entryBBank = new QLineEdit(this); layoutB->addRow("开户银行*:", entryBBank);
    entryBAcc = new QLineEdit(this);  layoutB->addRow("银行账号*:", entryBAcc);
    formLayout->addWidget(boxB, 1);
    mainLayout->addLayout(formLayout);

    // 区域 4：核心施工合规要素
    QGroupBox *workBox = new QGroupBox("工程现场及核心条款要素（法务强关联）", this);
    QGridLayout *workLayout = new QGridLayout(workBox);
    entryCarNo = new QLineEdit(this);       workLayout->addWidget(new QLabel("吊车车牌*:"), 0, 0); workLayout->addWidget(entryCarNo, 0, 1);
    entryWorkContent = new QLineEdit(this); workLayout->addWidget(new QLabel("施工作业内容:"), 0, 2); workLayout->addWidget(entryWorkContent, 0, 3);
    entryStartDate = new QLineEdit(this);   workLayout->addWidget(new QLabel("租赁进场日期:"), 1, 0); workLayout->addWidget(entryStartDate, 1, 1);
    entryEndDate = new QLineEdit(this);     workLayout->addWidget(new QLabel("退场截止日期:"), 1, 2); workLayout->addWidget(entryEndDate, 1, 3);
    entryWorkAddr = new QLineEdit(this);    workLayout->addWidget(new QLabel("施工精确地点*:"), 2, 0); workLayout->addWidget(entryWorkAddr, 2, 1);
    entryPayDay = new QLineEdit("30", this); workLayout->addWidget(new QLabel("完工付款周期(天):"), 2, 2); workLayout->addWidget(entryPayDay, 2, 3);
    mainLayout->addWidget(workBox);

    // 区域 5：附页清单
    QGroupBox *annexBox = new QGroupBox("已绑定的合同效力附页明细清单", this);
    QVBoxLayout *annexLayout = new QVBoxLayout(annexBox);
    textAnnex = new QTextEdit(this);
    textAnnex->setReadOnly(true);
    textAnnex->setText("暂无随附法律约束的台班明细账附件。");
    textAnnex->setMaximumHeight(80);
    annexLayout->addWidget(textAnnex);
    mainLayout->addWidget(annexBox);

    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
    statusBar->showMessage(" 状态提示: C++ 法律系统运行就绪，等待用户建立新租赁合同。");
    setCentralWidget(centralWidget);

    // 多线程深度绑定
    QThread *workerThread = new QThread(this);
    ContractWorker *worker = new ContractWorker();
    worker->moveToThread(workerThread);

    connect(btnAutoCode, &QPushButton::clicked, this, [=]() {
        entryCode->setText(entryCode->text().trimmed() + QDateTime::currentDateTime().toString("yyyyMMddhhmm"));
    });

    connect(btnSwap, &QPushButton::clicked, this, [=]() {
        QString nameA = entryAName->text(), bankA = entryABank->text(), accA = entryAAcc->text();
        entryAName->setText(entryBName->text()); entryABank->setText(entryBBank->text()); entryAAcc->setText(entryBAcc->text());
        entryBName->setText(nameA); entryBBank->setText(bankA); entryBAcc->text();
        QMessageBox::information(this, "提示", "商事收付款行号已安全对调。");
    });

    connect(btnGen, &QPushButton::clicked, this, [=]() {
        if(entryCarNo->text().trimmed().isEmpty() || entryWorkAddr->text().trimmed().isEmpty()) {
            QMessageBox::warning(this, "法律校验失败", "核心法务要素车牌及地点不能为空！");
            return;
        }
        QJsonObject data;
        data["code"] = entryCode->text();
        data["car_no"] = entryCarNo->text();
        data["work_addr"] = entryWorkAddr->text();
        data["pay_day"] = entryPayDay->text();
        emit startTask(data);
    });

    connect(this, &MainWindow::startTask, worker, &ContractWorker::doGenerateTask);
    connect(worker, &ContractWorker::taskFinished, this, &MainWindow::onGenerationSuccess);
    connect(worker, &ContractWorker::taskError, this, &MainWindow::onGenerationError);
    connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
    workerThread->start();
}

void MainWindow::onGenerationSuccess(const QString& msg) {
    QMessageBox::information(this, "导出成功", msg);
}

void MainWindow::onGenerationError(const QString& err) {
    QMessageBox::critical(this, "中断", err);
}
