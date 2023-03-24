#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QTime>
#include <QRandomGenerator>
#include <QTimer>

#include "target.h"

// Fonction pour afficher les règles du jeu
void showRules()
{
    QMessageBox rulesMessageBox;
    rulesMessageBox.setWindowTitle("Règles du jeu");
    rulesMessageBox.setText("Voici les règles du jeu:\n\n"
                            "1. Solo_easy : Des cibles vont apparaître une à une pendant 30 secondes. Le but du jeu et de tirer sur le plus de cibles possibles pendant le temps imparti.\n\n"
                            "2. Solo_difficile : Des  cibles vont apparaître une à une pendant 30 secondes. Contrairement au premier mode de jeu les cibles disparaissent au bout de 1 seconde et sont plus petites. Vous devez donc être réactif !\n\n"
                            "3. Multijoueur : Je sais pas encore trop\n\n"
                            "Amusez-vous bien!");
    rulesMessageBox.exec();
}

// Fonction pour passer au menu Solo
void switchToSoloMenu(QGraphicsScene &scene,
                      QGraphicsProxyWidget &easyButtonProxy,
                      QGraphicsProxyWidget &hardButtonProxy,
                      QGraphicsProxyWidget &backButtonProxy,
                      QGraphicsProxyWidget *soloButtonProxy,
                      QGraphicsProxyWidget *multiplayerButtonProxy,
                      QGraphicsProxyWidget *exitButtonProxy)
{
    // Supprimer les boutons existants de la scène
    scene.removeItem(soloButtonProxy);
    scene.removeItem(multiplayerButtonProxy);
    scene.removeItem(exitButtonProxy);

    // Ajouter les boutons "Facile", "Difficile" et "Retour" à la scène et les positionner
    easyButtonProxy.setPos(soloButtonProxy->pos());
    scene.addItem(&easyButtonProxy);

    hardButtonProxy.setPos(multiplayerButtonProxy->pos());
    scene.addItem(&hardButtonProxy);

    backButtonProxy.setPos(exitButtonProxy->pos());
    scene.addItem(&backButtonProxy);
}

//fct pour le bouton retour après avoir cliqué sur solo
void switchToMainMenu(QGraphicsScene &scene,
                      QGraphicsProxyWidget &easyButtonProxy,
                      QGraphicsProxyWidget &hardButtonProxy,
                      QGraphicsProxyWidget &backButtonProxy,
                      QGraphicsProxyWidget *soloButtonProxy,
                      QGraphicsProxyWidget *multiplayerButtonProxy,
                      QGraphicsProxyWidget *exitButtonProxy)
{
    // Supprimer les boutons "Facile", "Difficile" et "Retour" de la scène
    scene.removeItem(&easyButtonProxy);
    scene.removeItem(&hardButtonProxy);
    scene.removeItem(&backButtonProxy);

    // Ajouter les boutons "Solo", "Multijoueur" et "Quitter" à la scène
    scene.addItem(soloButtonProxy);
    scene.addItem(multiplayerButtonProxy);
    scene.addItem(exitButtonProxy);
}

//fct qui permet un retour au menu à la fin d'une partie
void resetToMainMenu(QGraphicsScene &scene, QGraphicsView &view, QPushButton &easyButton,
                     QPushButton &hardButton, QPushButton &backButton,
                     QPushButton &soloButton, QPushButton &multiplayerButton, QPushButton &exitButton,
                     QLabel &title, Target *target1, Target *target2) {
    // Réinitialisez tous les éléments du menu
    easyButton.show();
    hardButton.show();
    backButton.show();
    soloButton.show();
    multiplayerButton.show();
    exitButton.show();
    title.show();
    target1->show();
    target2->show();

    // Affichez le menu principal
    switchToMainMenu(scene, *scene.addWidget(&easyButton), *scene.addWidget(&hardButton), *scene.addWidget(&backButton),
                     scene.addWidget(&soloButton), scene.addWidget(&multiplayerButton), scene.addWidget(&exitButton));
}


// Génère une position aléatoire pour la cible
QPointF generateRandomTargetPosition(QGraphicsView &view, Target *target) {
    int x = QRandomGenerator::global()->bounded(view.width() - target->width());
    int y = QRandomGenerator::global()->bounded(view.height() - target->height());
    return QPointF(x, y);
}

//génère une target de manière random
Target* createRandomTarget(QGraphicsScene &scene, QGraphicsView &view) {
    Target *newTarget = new Target();
    QPointF randomPosition = generateRandomTargetPosition(view, newTarget);
    newTarget->setFixedSize(150, 150);
    scene.addWidget(newTarget)->setPos(randomPosition);
    return newTarget;
}

void onTargetClicked(QGraphicsScene &scene, QGraphicsView &view, Target *clickedTarget, int &targetsHitCount) {
    // Créez une nouvelle cible
    Target *newTarget = createRandomTarget(scene, view);

    // Connectez le signal clicked de la nouvelle cible à la fonction onTargetClicked
    QObject::connect(newTarget, &Target::clicked, [&scene, &view, newTarget, &targetsHitCount]() {
        onTargetClicked(scene, view, newTarget, targetsHitCount);
    });

    // Supprimez la cible cliquée
    scene.removeItem(scene.itemAt(clickedTarget->pos(), QTransform()));
    delete clickedTarget;
    targetsHitCount++;
}



void startGameEasy(QGraphicsScene &scene, QGraphicsView &view, QPushButton &easyButton,
                   QPushButton &hardButton, QPushButton &backButton,
                   QPushButton &soloButton, QPushButton &multiplayerButton, QPushButton &exitButton,
                   QLabel &title, Target *target1, Target *target2,  QTimer &gameTimer, int &targetHitCount) {
    // Masquez tous les éléments du menu
    easyButton.hide();
    hardButton.hide();
    backButton.hide();
    soloButton.hide();
    multiplayerButton.hide();
    exitButton.hide();
    title.hide();
    target1->hide();
    target2->hide();

    Target *newTarget = createRandomTarget(scene, view);
    QObject::connect(newTarget, &Target::clicked, [&scene, &view, newTarget, &targetHitCount]() {
        onTargetClicked(scene, view, newTarget, targetHitCount);
    });

    // Démarrez le QTimer pour une durée de 20 secondes
    gameTimer.setSingleShot(true);
    gameTimer.start(5000);
}
void endGameEasy(QGraphicsScene &scene, QGraphicsView &view, int targetsHitCount, std::function<void()> callback) {
    // Supprimez tous les éléments de la scène
    QList<QGraphicsItem *> items = scene.items();
    for (QGraphicsItem *item : items) {
        scene.removeItem(item);
    }

    // Affichez la pop-up
    QMessageBox endGameMessageBox;
    endGameMessageBox.setWindowTitle("Jeu terminé");
    endGameMessageBox.setText(QString("La partie est terminée !\n\nCibles touchées : %1").arg(targetsHitCount));
    endGameMessageBox.addButton(QMessageBox::Ok);

    QObject::connect(endGameMessageBox.button(QMessageBox::Ok), &QPushButton::clicked, callback);

    endGameMessageBox.exec();

    // Ici, vous pouvez ajouter des instructions pour réinitialiser la scène, si nécessaire.
}





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

    //déclaration variable utile pour les parties
    QTimer gameTimer;
    int targetsHitCount = 0;

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

    //test clic target
    QObject::connect(target1, &Target::clicked, showRules);

    // Créer la deuxième cible à gauche des boutons
    Target *target2 = new Target();
    target2->setFixedSize(150, 150);
    QGraphicsProxyWidget *target2Proxy = scene.addWidget(target2);
    target2Proxy->setPos(view.width() / 2 - target2->width() / 2 - 600, view.height() / 2 - target2->height() / 2 - 100);

    QObject::connect(target2, &Target::clicked, [&scene, &view](){
        createRandomTarget(scene, view);
    });

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

    // Créer les boutons "Facile", "Difficile" et "Retour"
    QPushButton easyButton("Facile");
    easyButton.setFont(QFont("Arial", 48));
    easyButton.setStyleSheet("color: rgb(85, 85, 85); border: 2px solid white ; width: 540px ; height: 110px;");

    QPushButton hardButton("Difficile");
    hardButton.setFont(QFont("Arial", 48));
    hardButton.setStyleSheet("color: rgb(85, 85, 85); border: 2px solid white ; width: 540px ; height: 110px;");

    QPushButton backButton("Retour");
    backButton.setFont(QFont("Arial", 48));
    backButton.setStyleSheet("color: rgb(85, 85, 85); border: 2px solid white ; width: 540px ; height: 110px;");


    // Ajouter les boutons "Facile", "Difficile" et "Retour" à la scène
    QGraphicsProxyWidget *easyButtonProxy = scene.addWidget(&easyButton);
    easyButtonProxy->setPos(soloButtonProxy->pos());
    easyButtonProxy->setVisible(false);

    QGraphicsProxyWidget *hardButtonProxy = scene.addWidget(&hardButton);
    hardButtonProxy->setPos(multiplayerButtonProxy->pos());
    hardButtonProxy->setVisible(false);

    QGraphicsProxyWidget *backButtonProxy = scene.addWidget(&backButton);
    backButtonProxy->setPos(exitButtonProxy->pos());
    backButtonProxy->setVisible(false);

// Connexion du signal "clicked" du bouton Solo
    QObject::connect(&soloButton, &QPushButton::clicked, [&]() {
        switchToSoloMenu(scene, *easyButtonProxy, *hardButtonProxy, *backButtonProxy, soloButtonProxy, multiplayerButtonProxy, exitButtonProxy);
        easyButtonProxy->setVisible(true);
        hardButtonProxy->setVisible(true);
        backButtonProxy->setVisible(true);
    });

    QObject::connect(&backButton, &QPushButton::clicked, [&]() {
        switchToMainMenu(scene, *easyButtonProxy, *hardButtonProxy, *backButtonProxy, soloButtonProxy, multiplayerButtonProxy, exitButtonProxy);
        easyButtonProxy->setVisible(false);
        hardButtonProxy->setVisible(false);
        backButtonProxy->setVisible(false);
    });

    QObject::connect(&easyButton, &QPushButton::clicked, [&](){
        startGameEasy(scene, view, easyButton, hardButton, backButton, soloButton, multiplayerButton, exitButton, title, target1, target2, gameTimer, targetsHitCount);
        targetsHitCount = 0; // Réinitialisez le compteur de cibles touchées au début de chaque partie
    });


    QObject::connect(&gameTimer, &QTimer::timeout, [&scene, &view, &targetsHitCount, &easyButtonProxy, &hardButtonProxy, &backButtonProxy, &soloButtonProxy, &multiplayerButtonProxy, &exitButtonProxy](){
        endGameEasy(scene, view, targetsHitCount, [&]() {
            switchToMainMenu(scene, *easyButtonProxy, *hardButtonProxy, *backButtonProxy, soloButtonProxy, multiplayerButtonProxy, exitButtonProxy);
            easyButtonProxy->setVisible(false);
            hardButtonProxy->setVisible(false);
            backButtonProxy->setVisible(false);
        });
    });



    // Ajouter la vue au layout principal
    layout.addWidget(&view);

    // Ajouter un espace en bas
    QSpacerItem *bottomSpacer = new QSpacerItem(0, 100);
    layout.addItem(bottomSpacer);

    window.show();
    return a.exec();
}
