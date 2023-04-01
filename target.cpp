#include "target.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

Target::Target(QWidget *parent) : QWidget(parent),
                                  mediaPlayer(new QMediaPlayer(this))
{
    setAttribute(Qt::WA_TranslucentBackground);

    audioFiles << "qrc:/sounds/duck-quack1.wav"
               << "qrc:/sounds/duck-quack2.wav";
    mediaPlayer->setMedia(QUrl(audioFiles[0]));

    // Connectez le signal mediaStatusChanged au nouveau slot
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &Target::onMediaStatusChanged);
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
        int randomIndex = QRandomGenerator::global()->bounded(audioFiles.size());
        mediaPlayer->setMedia(QUrl(audioFiles[randomIndex]));
        mediaPlayer->setPosition(0);

        // Supprimez mediaPlayer->play() d'ici

        qDebug() << "Playing sound:" << audioFiles[randomIndex];
        qDebug() << "Media status:" << mediaPlayer->mediaStatus();
        qDebug() << "Error:" << mediaPlayer->errorString();

        emit clicked();
    }
}

void Target::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia) {
        mediaPlayer->play();
    }
}

