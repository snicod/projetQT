#ifndef TARGET_H
#define TARGET_H

#include <QWidget>
#include <QRandomGenerator>
#include <QStringList>

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

};

#endif // TARGET_H
