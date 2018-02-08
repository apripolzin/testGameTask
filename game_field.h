#ifndef GAMEFIELD
#define GAMEFIELD

#include <QWidget>
#include <QGridLayout>
#include <QPointer>
#include "game_field_element.h"

class GameField : public QWidget
{
    Q_OBJECT
public:
    GameField(quint8 size = 4, QWidget* parent = NULL);
    virtual ~GameField();

private:
    quint8 field_size;

private:
    QPointer<QGridLayout> layout;

private slots:
    void slotElementPressed(quint8 row, quint8 col);

private:
    GFElement *getElementAt(quint8 row, quint8 col);

private:
    QQueue<GFElement *> queue_left, queue_right, queue_top, queue_bottom;

private:
    QPointer<QTimer> timer;
    bool timerStarted;
};

#endif
