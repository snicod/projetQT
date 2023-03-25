// gamehandler.h

#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <QObject>
#include "target.h"
#include <QGraphicsScene>
#include <QGraphicsView>

class GameHandler : public QObject {
Q_OBJECT

public:
    GameHandler(QGraphicsScene &scene, QGraphicsView &view, int &targetsHitCount);
    Target *createRandomTarget(QGraphicsScene &scene, QGraphicsView &view);
    void targetClicked(Target *clickedTarget);

private:
    QGraphicsScene &m_scene;
    QGraphicsView &m_view;
    int &m_targetsHitCount;

    QPointF generateRandomTargetPosition(QGraphicsView &view, Target *target);
};

#endif // GAMEHANDLER_H
