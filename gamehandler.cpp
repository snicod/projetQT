// gamehandler.cpp

#include "gamehandler.h"
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QRandomGenerator>

GameHandler::GameHandler(QGraphicsScene &scene, QGraphicsView &view, int &targetsHitCount)
        : m_scene(scene), m_view(view), m_targetsHitCount(targetsHitCount) {
}

Target *GameHandler::createRandomTarget(QGraphicsScene &scene, QGraphicsView &view) {
    Target *newTarget = new Target();
    QPointF randomPosition = generateRandomTargetPosition(view, newTarget);
    newTarget->setFixedSize(150, 150);
    scene.addWidget(newTarget)->setPos(randomPosition);
    return newTarget;
}

QPointF GameHandler::generateRandomTargetPosition(QGraphicsView &view, Target *target) {
    int x_min = target->width() / 2;
    int x_max = view.width() - target->width() / 2;
    int y_min = target->height() / 2;
    int y_max = view.height() - target->height() / 2;

    int x = QRandomGenerator::global()->bounded(x_min, x_max);
    int y = QRandomGenerator::global()->bounded(y_min, y_max);

    return QPointF(x, y);
}
