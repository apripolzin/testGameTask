#ifndef GAMEMAINWINDOW
#define GAMEMAINWINDOW

#include <QMainWindow>
#include <QPointer>
#include "game_field.h"

class GameMainWindow : public QWidget
{
    Q_OBJECT
public:
    GameMainWindow(QWidget *parent = NULL);
    virtual ~GameMainWindow();

private:
    QPointer<GameField> game_field;
};

#endif
