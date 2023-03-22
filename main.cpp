#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QDesktopWidget>
#include "target.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window;
    window.setWindowState(Qt::WindowFullScreen);
    window.setStyleSheet("background-color: hsl(120, 70%, 90%);");

    QVBoxLayout layout(&window);

    // Créer une scène et une vue pour afficher les éléments du jeu
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view.setFixedSize(QApplication::desktop()->screenGeometry().width(), QApplication::desktop()->screenGeometry().height());
    view.setStyleSheet("background-color: transparent; border: none;");


    // Ajouter un espace en haut
    QSpacerItem *topSpacer = new QSpacerItem(0, 100);
    layout.addItem(topSpacer);


    // Créer le titre
    QLabel title("CoinCoinShooter");
    title.setAlignment(Qt::AlignCenter);
    title.setFont(QFont("Arial", 96, QFont::Bold));
    title.setStyleSheet("color: rgb(101, 67, 33);");  // mettre la police en blanc
    title.setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsProxyWidget *titleProxy = scene.addWidget(&title);
    titleProxy->setPos(view.width() / 2 - title.width() / 2, 100);

    // Créer la première cible à droite du titre
    Target *target1 = new Target();
    target1->setFixedSize(150, 150);
    QGraphicsProxyWidget *target1Proxy = scene.addWidget(target1);
    target1Proxy->setPos(titleProxy->pos().x() + title.width() + 50, titleProxy->pos().y());

    // Créer la deuxième cible à gauche des boutons
    Target *target2 = new Target();
    target2->setFixedSize(150, 150);
    QGraphicsProxyWidget *target2Proxy = scene.addWidget(target2);
    target2Proxy->setPos(view.width() / 2 - target2->width() / 2 - 600, view.height() / 2 - target2->height() / 2 - 100);

    // Créer le bouton "Solo"
    QPushButton soloButton("Solo");
    soloButton.setFont(QFont("Arial", 48));
    soloButton.setStyleSheet("color: rgb(85, 85, 85); border: 2px solid white ; width: 540px ; height: 110px;");

    // Ajouter le bouton Solo à la scène
    QGraphicsProxyWidget *soloButtonProxy = scene.addWidget(&soloButton);
    soloButtonProxy->setPos(view.width() / 2 - soloButton.width() / 2, view.height() / 2 - soloButton.height() / 2 - 50);

    // Créer le bouton "Multijoueur"
    QPushButton multiplayerButton("Multijoueur");
    multiplayerButton.setFont(QFont("Arial", 48));
    multiplayerButton.setStyleSheet("color: rgb(85, 85, 85); border: 2px solid white ; width: 540px ; height: 110px ;");

    // Ajouter le bouton Multijoueur à la scène
    QGraphicsProxyWidget *multiplayerButtonProxy = scene.addWidget(&multiplayerButton);
    multiplayerButtonProxy->setPos(view.width() / 2 - multiplayerButton.width() / 2, view.height() / 2 - multiplayerButton.height() / 2 + 50);

    // Créer le bouton "Quitter"
    QPushButton exitButton("Quitter");
    exitButton.setFont(QFont("Arial", 48));
    exitButton.setStyleSheet("color: rgb(85, 85, 85);border: 2px solid white ; width: 540px ; height: 110px ; ");
    QObject::connect(&exitButton, &QPushButton::clicked, &a, &QApplication::quit);

    // Ajouter le bouton Quitter à la scène
    QGraphicsProxyWidget *exitButtonProxy = scene.addWidget(&exitButton);
    exitButtonProxy->setPos(view.width() / 2 - exitButton.width() / 2, view.height() / 2 - exitButton.height() / 2 + 150);

    // Ajouter la vue au layout principal
    layout.addWidget(&view);

    // Ajouter un espace en bas
    QSpacerItem *bottomSpacer = new QSpacerItem(0, 100);
    layout.addItem(bottomSpacer);

    window.show();
    return a.exec();
}
