#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPainter>
#include <QKeyEvent>


class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0):QWidget(parent)
    {
        this->setFixedSize(601,401);
        Ughankyun = new QRect* [8];
                for(int i=0; i<8; i++)
                    Ughankyun[i]= new QRect [12];

        for(int i=0; i<8; i++)
            for(int j=0; j<12; j++)
                Ughankyun[i][j]= QRect(j*50,i*50,50,50);
        this->grabKeyboard();

        kghziner = new int* [8];
                for(int i=0; i<8; i++)
                   kghziner[i]= new int [12];

        for(int i=0; i<8; i++)
            for(int j=0; j<12; j++)
                kghziner[i][j]=0;

        kghziner[2][1]=1;
        kghziner[3][2]=1;
        kghziner[4][2]=1;
        kghziner[5][1]=1;
        kghziner[7][2]=1;
        kghziner[1][3]=1;
        kghziner[1][6]=1;
        kghziner[4][5]=1;
        kghziner[5][7]=1;
        kghziner[2][8]=1;
        kghziner[2][9]=1;
        kghziner[4][10]=1;
        kghziner[5][10]=1;
        kghziner[0][0]=2;



        nerkadirq_x=0;
        nerkadirq_y=0;


    }

    void paintEvent(QPaintEvent *)
    {
        nkarogh = new QPainter(this);
        for(int i=0; i<8; i++)
            for(int j=0; j<12; j++){
                if(kghziner[i][j]==1)
                    nkarogh->setBrush(Qt::lightGray);
               else if(kghziner[i][j]==0)
                {
                    nkarogh->setBrush(Qt::darkGray);

                }
               else if(kghziner[i][j]==2)
                {
                   nkarogh->setBrush(Qt::darkRed);

                }
                nkarogh->drawRect(Ughankyun[i][j]);
            }



    }



    void mousePressEvent(QMouseEvent *event)
    {
        int x, y;
        for(int i=0; i<8; i++)
            for(int j=0; j<12; j++)
                if(event->button()==Qt::LeftButton &&
                        Ughankyun[i][j].contains(event->x(), event->y(), true))
                {
                    x=i; y=j;
                    break;
                }

        if(((x==nerkadirq_x &&(y==nerkadirq_y-1 || y==nerkadirq_y+1))||
            (y==nerkadirq_y &&(x==nerkadirq_x-1 || x==nerkadirq_x+1)))&&
                kghziner[x][y]!=1)
        {
            kghziner[x][y]=2;
            nerkadirq_x=x;
            nerkadirq_y=y;
        }
        this->repaint();

        if(check())
            Message();


    }
    void Move(int x, int y)
    {

        if(((x==nerkadirq_x &&(y==nerkadirq_y-1 || y==nerkadirq_y+1))||
            (y==nerkadirq_y &&(x==nerkadirq_x-1 || x==nerkadirq_x+1)))&&
                kghziner[x][y]!=1 && kghziner[x][y]!=2)
        {
            kghziner[x][y]=2;
            nerkadirq_x=x;
            nerkadirq_y=y;
        }

        this->repaint();
    }

    void keyPressEvent(QKeyEvent *event)
        {
            if(event->key()==Qt::Key_Left)
               if(nerkadirq_y > 0)
               {
                   Move(nerkadirq_x, nerkadirq_y-1);
                   this->repaint();
               }

            if(event->key()==Qt::Key_Right)
               if(nerkadirq_y < 11)
               {
                   Move(nerkadirq_x, nerkadirq_y+1);
                   this->repaint();
               }

            if(event->key()==Qt::Key_Up)
               if(nerkadirq_x > 0 )
               {
                   Move(nerkadirq_x-1, nerkadirq_y);
                   this->repaint();
               }

            if(event->key()==Qt::Key_Down)
               if(nerkadirq_x < 7 )
               {
                   Move(nerkadirq_x+1, nerkadirq_y);
                   this->repaint();
               }
            if(check())
                Message();

        }


public slots:
    void Restart()
    {

        for(int i=0; i<8; i++)
            for(int j=0; j<12; j++)
                kghziner[i][j]=0;

        kghziner[2][1]=1;
        kghziner[3][2]=1;
        kghziner[4][2]=1;
        kghziner[5][1]=1;
        kghziner[7][2]=1;
        kghziner[1][3]=1;
        kghziner[1][6]=1;
        kghziner[4][5]=1;
        kghziner[5][7]=1;
        kghziner[2][8]=1;
        kghziner[2][9]=1;
        kghziner[4][10]=1;
        kghziner[5][10]=1;
        kghziner[0][0]=2;



        nerkadirq_x=0;
        nerkadirq_y=0;
        this->grabKeyboard();
        this->repaint();
    }


private:
    QRect **Ughankyun;
    QPainter *nkarogh;
    int **kghziner;
    int nerkadirq_x;
    int nerkadirq_y;

    bool check()
    {
        int n=0;
        for(int i=0; i<8; i++)
            for(int j=0; j<12; j++)
                if(kghziner[i][j]==2)
                    n++;
        if(n==83 && nerkadirq_x==7 && nerkadirq_y==11)
            return true;
        return false;
    }

    void Message()
    {
        this->releaseKeyboard();
        QMessageBox m;
        m.setText("<h1>You won!</h1>");
        m.exec();
    }

signals:

public slots:


};

#endif // MYWIDGET_H
