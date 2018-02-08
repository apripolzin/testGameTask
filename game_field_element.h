#ifndef GAMEFIELDELEMENT
#define GAMEFIELDELEMENT

#include <QWidget>
#include <QTimer>
#include <QPointer>
#include <QQueue>
#include <QTimer>

class GFElement: public QWidget
{
    Q_OBJECT
public:
    enum element_orientation {
        ORIENTATION_HORIZONTAL = 0,
        ORIENTATION_VERTICAL = 1
    };
    GFElement(element_orientation start_orientation = ORIENTATION_VERTICAL, QWidget *parent = NULL);
    virtual ~GFElement();

protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);

private:
    QPointer<QTimer> timer;
    float current_angle;
    element_orientation orientation;

public:
    void setFieldCoordinates(quint8 row, quint8 column);

private:
    quint8 m_row;
    quint8 m_column;

signals:
    void signalElementPressed(quint8 row, quint8 column);

public slots:
    void toggleOrientation();

public:
    element_orientation getOrientation();

signals:
    void rotateComplete();
};

#endif
