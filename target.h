#ifndef TARGET_H
#define TARGET_H

#include <QWidget>

class Target : public QWidget
{
Q_OBJECT

public:
    explicit Target(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif 
