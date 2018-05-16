#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include "mywidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *win = new QWidget;
    win->setFixedSize(700,500);
    MyWidget *mywid= new MyWidget(win);
    mywid->setGeometry(50,50,600,400);


    QPushButton *pb=new QPushButton ("REPLAY");

    QObject::connect(pb,SIGNAL(clicked()),mywid, SLOT(Restart()));
    QHBoxLayout *shert = new QHBoxLayout;
    shert->addWidget(mywid);
    shert->addWidget(pb);

    win->setLayout(shert);



    win->show();

    return a.exec();
}
