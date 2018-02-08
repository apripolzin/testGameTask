#include "mainwindow.h"
#include <QDoubleSpinBox>
#include <QLabel>
#include <QDebug>

GameMainWindow::GameMainWindow(QWidget *parent)
    : QWidget(parent)
{
    QDoubleSpinBox *fieldsize = new QDoubleSpinBox;
    fieldsize->setMaximum(10);
    fieldsize->setMinimum(4);
    fieldsize->setDecimals(0);

    QHBoxLayout *hbxLayout = new QHBoxLayout;
    hbxLayout->addWidget(new QLabel("Field size"));
    hbxLayout->addWidget(fieldsize);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hbxLayout);
    game_field = new GameField((quint8)fieldsize->value());
    mainLayout->addWidget(game_field);
    mainLayout->addStretch();

    this->setLayout(mainLayout);

    connect(fieldsize, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
          [=](double new_val){
//        game_field->hide();
        mainLayout->removeWidget(game_field);
        game_field->deleteLater();
        game_field = new GameField((quint8)new_val);
        mainLayout->addWidget(game_field);
        this->resize(this->sizeHint());
    });
}

GameMainWindow::~GameMainWindow()
{
}
