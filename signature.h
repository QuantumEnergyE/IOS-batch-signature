#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class Signature;
}


enum em_sign_state {
    SIGN_WAIT,
    SIGN_ON,
    SIGN_SUCCESS,
    SIGN_FAIL
};
class TableModel;
class TableDelegate;
class QTimer;

class Signature : public QMainWindow
{
    Q_OBJECT

public:
    explicit Signature(QWidget *parent = 0);
    ~Signature();

private slots:

    void on_pushButton_file_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_provision_clicked();

    void update_state(int row, bool result);

private:
    Ui::Signature *ui;
    TableModel *model_;
    TableDelegate *delegate_;
    QTimer *timer_;

    //func
    void TableInit();
    void GetIdentity();
    void SignFileTimer();
};


class SignThread : public QThread
{
    Q_OBJECT
public:
    SignThread(int row, QString sign_name, QString ipa_path, QString provision, QWidget *parent=0);
    int row_;
    QString sign_name_, ipa_path_, provision_;
    bool SignWorker();
protected:
    void run() {
        bool result = SignWorker();
        emit resultReady(row_, result);
    }
signals:
    void resultReady(int row, bool result);
};
#endif // SIGNATURE_H
