#include "game_field_element.h"
#include <QDebug>
#include <QPainter>
#include <QRectF>

GFElement::GFElement(GFElement::element_orientation start_orientation, QWidget *parent)
    : QWidget(parent),
      current_angle(0.0), m_row(0), m_column(0)
{
    timer = new QTimer(this);
    this->setFixedSize(50,50);

    switch (start_orientation) {
    case ORIENTATION_HORIZONTAL:
        orientation = ORIENTATION_HORIZONTAL;
        current_angle = 90;
        break;
    case ORIENTATION_VERTICAL:
        orientation = ORIENTATION_VERTICAL;
        current_angle = 0;
    default:
        break;
    }

    connect(timer, &QTimer::timeout,
            [=](){
        if (current_angle > 90){
            timer->stop();
            current_angle = 90;
            orientation = ORIENTATION_HORIZONTAL;
            emit rotateComplete();
        }
        else if ((current_angle < 0)){
            timer->stop();
            current_angle = 0;
            orientation = ORIENTATION_VERTICAL;
            emit rotateComplete();
        }

        if (orientation == ORIENTATION_VERTICAL){
            current_angle += 1;
        }
        else if (orientation == ORIENTATION_HORIZONTAL){
            current_angle -= 1;
        }
        this->update();
    });
}

GFElement::~GFElement()
{
}

void GFElement::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(this->width()/2, this->height()/2);

    //Set pen for red solid line
    painter.setPen(QPen(Qt::red, 2));
    painter.drawPoint(0,0);

    //Draw rectangle
    painter.save();
    QPointF topLeft(-5, -20);
    QPointF bottomRight(5, 20);
    QRectF rect(topLeft, bottomRight);
    painter.rotate(current_angle);
    painter.drawRect(rect);
    painter.restore();
}

void GFElement::mousePressEvent(QMouseEvent *)
{
    //timer->start(10);
    emit signalElementPressed(m_row, m_column);
}

void GFElement::setFieldCoordinates(quint8 row, quint8 column)
{
    m_row = row;
    m_column = column;
}

void GFElement::toggleOrientation()
{
    timer->start(10);
}

GFElement::element_orientation GFElement::getOrientation()
{
    return orientation;
}

