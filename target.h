#ifndef TARGET_H
#define TARGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QRandomGenerator>
#include <QStringList>
#include <QMediaPlaylist>

class Target : public QWidget
{
Q_OBJECT

public:
    explicit Target(QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots: // Ajoutez cette ligne
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    QMediaPlayer *mediaPlayer;
    QStringList audioFiles;
};

#endif // TARGET_H
