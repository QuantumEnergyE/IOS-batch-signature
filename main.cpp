#include "signature.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //style
    QString curdir = QApplication::applicationDirPath();
    QString strdir = QString("%1%2").arg(curdir).arg("/data/qss/white.css");
    QFile file(strdir);
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = file.readAll();
        qApp->setStyleSheet(styleSheet);
        file.close();
    }

    Signature w;
    w.show();

    return a.exec();
}
