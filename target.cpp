#include "target.h"
#include <QPainter>
#include <QMouseEvent>


Target::Target(QWidget *parent) : QWidget(parent)

{
    setAttribute(Qt::WA_TranslucentBackground);



}


void Target::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Dessiner les cercles de la cible
    QBrush brush(Qt::red, Qt::SolidPattern);
    painter.setBrush(brush);

    int centerX = width() / 2;
    int centerY = height() / 2;
    int radius = width() / 2;

    for (int i = 0; i < 3; ++i) {
        painter.drawEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
        radius -= 20;
        brush.setColor(brush.color() == Qt::red ? Qt::white : Qt::red);
        painter.setBrush(brush);
    }
}

void Target::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
                emit clicked();
    }
}



