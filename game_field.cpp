#include "game_field.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>

GameField::GameField(quint8 size, QWidget *parent)
    : QWidget(parent), field_size(size), timerStarted(false)
{
    //Max field size
    if (field_size > 10)
        field_size = 10;
    //Min field size
    if (field_size < 4)
        field_size = 4;

    layout = new QGridLayout;

    for (quint8 row = 0; row < field_size; row++)
        for (quint8 column = 0; column < field_size; column++)
        {
            qsrand (QDateTime::currentMSecsSinceEpoch() + row + column);
            int orientation =  qrand() % 2;
//            qDebug() << orientation;
            GFElement *el = new GFElement((GFElement::element_orientation) orientation);
            el->setFieldCoordinates(row, column);
            layout->addWidget(el, row, column);

            connect(el, &GFElement::signalElementPressed, this, &GameField::slotElementPressed);

            connect(el, &GFElement::rotateComplete, [=](){
                if (queue_left.isEmpty() && queue_right.isEmpty() && queue_top.isEmpty() && queue_bottom.isEmpty())
                {
                    GFElement::element_orientation base_orientation = GFElement::ORIENTATION_VERTICAL;
                    for (int row=0; row<field_size; row++){
                        for (int col=0; col<field_size; col++){
                            if (getElementAt(row, col)->getOrientation() != base_orientation)
                                return;
                        }
                    }
                    QMessageBox::warning(this ,"Congratulations", "You won the game!");
                }
            });
        }
    this->setLayout(layout);

    timer = new QTimer;

    connect(timer, &QTimer::timeout, [=](){
//        qDebug() << "timeout";
        if (!queue_left.isEmpty())
            queue_left.dequeue()->toggleOrientation();
        if (!queue_right.isEmpty())
            queue_right.dequeue()->toggleOrientation();
        if (!queue_top.isEmpty())
            queue_top.dequeue()->toggleOrientation();
        if (!queue_bottom.isEmpty())
            queue_bottom.dequeue()->toggleOrientation();

        if (queue_left.isEmpty() && queue_right.isEmpty() && queue_top.isEmpty() && queue_bottom.isEmpty())
        {
            timer->stop();
            timerStarted = false;
        }

    });
}

GameField::~GameField()
{
}

void GameField::slotElementPressed(quint8 row, quint8 col)
{
    if (timerStarted)
        return;

    //qDebug() << "pressed" << row << col;

    for (int r=row; r>=0; r--)
    {
        queue_top.enqueue(getElementAt(r,col));
    }

    for (int r=row; r<field_size; r++)
    {
        queue_bottom.enqueue(getElementAt(r,col));
    }

    for (int c=col; c>=0; c--)
    {
        queue_left.enqueue(getElementAt(row,c));
    }

    for (int c=col; c<field_size; c++)
    {
        queue_right.enqueue(getElementAt(row,c));
    }

    //dalay before next element will start moving
    timer->start(200);
    timerStarted = true;
}

GFElement *GameField::getElementAt(quint8 row, quint8 col)
{
    if (row >= field_size)
        return NULL;
    if (col >= field_size)
        return NULL;

    return qobject_cast<GFElement *>(layout->itemAtPosition(row, col)->widget());
}
