#include "mainWindow.h"

#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    setFixedSize(800, 600);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu(tr("Fichier"));

    QAction *exitAction = new QAction(tr("Quitter"), this);
    fileMenu->addAction(exitAction);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
}
