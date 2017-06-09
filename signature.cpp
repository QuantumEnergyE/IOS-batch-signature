#include "signature.h"
#include "ui_signature.h"
#include "tablemodel.h"
#include "tabledelegate.h"
#include <QtDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QProcess>
#include <QApplication>
#include <QMutex>

static QMutex success_lock, error_lock;

Signature::Signature(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Signature)
{
    ui->setupUi(this);
    this->setFixedSize(1000, 680);
    this->TableInit();
    this->GetIdentity();
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &Signature::SignFileTimer);
}

Signature::~Signature()
{
    delete ui;
}

void Signature::TableInit()
{
    QStringList title;
    title << "Ipa文件" << "签名文件" << "provision" << "签名状态";
    model_ = new TableModel();
    model_->setHorizontalHeaderLabels(title);
    ui->tableView_main->setModel(model_);
    ui->tableView_main->verticalHeader()->hide();
    ui->tableView_main->setColumnWidth(0, 230);
    ui->tableView_main->setColumnWidth(1, 250);
    ui->tableView_main->setColumnWidth(2, 250);
    ui->tableView_main->setColumnWidth(3, 230);
    ui->tableView_main->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_main->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //delegate
    delegate_ = new TableDelegate();
    ui->tableView_main->setItemDelegate(delegate_);
}

void Signature::GetIdentity()
{
    QString program = "security find-identity -v -p codesigning";
    QProcess process;
    process.start(program);
    if (process.waitForFinished()) {
        QString identity = process.readAllStandardOutput();
        QStringList identity_list = identity.trimmed().split("\n");
        identity_list.pop_back();
        for (QString name:identity_list) {
            QString tmp_name = name.section('"', 1).trimmed();
            int length = tmp_name.length();
            QString real_name = tmp_name.remove(length - 1, 1);
            ui->comboBox_sign_file->addItem(real_name);
        }
    } else {
        QMessageBox::critical(this, "错误！", "<font color='#eb3f12'>签名文件获取失败！</font>");
    }
}


void Signature::on_pushButton_file_clicked()
{
    if (0 == ui->comboBox_sign_file->count()) {
        QMessageBox::warning(this, "提示！", "<font color='#eb3f12'>检测到未配置签名文件，请先配置签名文件！</font>");
        return;
    }
    QString sign_name = ui->comboBox_sign_file->currentText().trimmed();
    QString provision = ui->lineEdit_provision->text();
    QStringList file_names = QFileDialog::getOpenFileNames(this, "选择待签名的Ipa", "", "*ipa");
    int insert_row = model_->rowCount();
    for (auto file : file_names) {
        model_->setItem(insert_row, 0, new QStandardItem(QFileInfo(file).absoluteFilePath()));
        model_->setItem(insert_row, 1, new QStandardItem(sign_name));
        model_->setItem(insert_row, 2, new QStandardItem(provision));
        model_->setItem(insert_row, 3, new QStandardItem(QString::number(SIGN_WAIT)));
        insert_row += 1;
    }
}

void Signature::on_pushButton_start_clicked()
{
    if (!model_->rowCount())  {
        QMessageBox::information(this, "提示！", "<font color='#eb3f12'>没有选择任何文件！</font>");
        return;
    }

    if (ui->pushButton_start->text() == "开始签名") {
        ui->pushButton_start->setText("停止签名");
        timer_->start(5000);
    } else {
        ui->pushButton_start->setText("开始签名");
        timer_->stop();
    }
}

void Signature::SignFileTimer()
{
    int row_count = model_->rowCount();
    for (int row = 0; row < row_count; row++) {
        QString ipa_path = model_->item(row, 0)->data(Qt::DisplayRole).toString();
        QString sign_name = model_->item(row, 1)->data(Qt::DisplayRole).toString().trimmed();
        QString provision_path = model_->item(row, 2)->data(Qt::DisplayRole).toString().trimmed();
        int ipa_state = model_->item(row, 3)->data(Qt::DisplayRole).toInt();
        if (0 == ipa_state) {
            model_->setItem(row, 3, new QStandardItem(QString::number(SIGN_ON)));
            SignThread *sign_thread = new SignThread(row, sign_name, ipa_path, provision_path, this);
            connect(sign_thread, &SignThread::resultReady, this, &Signature::update_state);
            connect(sign_thread, &SignThread::finished, sign_thread, &SignThread::deleteLater);
            sign_thread->start();
        }
    }
}


void Signature::on_pushButton_provision_clicked()
{
    QString provision_file = QFileDialog::getOpenFileName(this, "选择provision文件", "", "");
    ui->lineEdit_provision->setText(QFileInfo(provision_file).absoluteFilePath());
}


void Signature::update_state(int row, bool result)
{
    if (result) {
        model_->setItem(row, 3, new QStandardItem(QString::number(SIGN_SUCCESS)));
    } else {
        model_->setItem(row, 3, new QStandardItem(QString::number(SIGN_FAIL)));
    }
}
//Worker Thread
SignThread::SignThread(int row, QString sign_name, QString ipa_path, QString provision, QWidget *parent) : QThread(parent),
    row_(row), sign_name_(sign_name), ipa_path_(ipa_path), provision_(provision) {
}

bool SignThread::SignWorker()
{
    QString out_dir = QFileInfo(ipa_path_).absoluteDir().absolutePath() + "/zm_signed_out";
    QProcess process;
    QString curdir = QApplication::applicationDirPath();
    QString program = QString("%1%2").arg(curdir).arg("/data/signature/resign");
    qDebug() << program;
    QStringList args;
    args << "-d" << out_dir << "-s" << sign_name_ << ipa_path_;
    if (!provision_.isEmpty()) {
        args << "-p" << provision_;
    }
    qDebug() << args;
    process.start(program, args);
    if (process.waitForFinished(1200000)) {
        if (process.exitCode() == 0) {
            success_lock.lock();
            QFile file(curdir + "/success.log");
            file.open(QIODevice::Append);
            file.write(process.readAllStandardOutput() + "\n" + process.readAllStandardError() + "\n");
            file.flush();
            file.close();
            success_lock.unlock();
            return true;
        } else {
            error_lock.lock();
            QFile file(curdir + "/error.log");
            file.open(QIODevice::Append);
            file.write(process.readAllStandardOutput() + "\n" + process.readAllStandardError() + "\n");
            file.flush();
            file.close();
            error_lock.unlock();
            return false;
        }
    }
    return false;
}
