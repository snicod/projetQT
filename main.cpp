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
#include <QTimer>
#include <QTime>
#include <QRandomGenerator>
#include <QElapsedTimer>

#include "target.h"

//variable globale
QTimer countdownTimer;

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

// Génère une position aléatoire pour la cible
QPointF generateRandomTargetPosition(QGraphicsView &view, Target *target) {
    int x = QRandomGenerator::global()->bounded(view.width() - target->width());
    int y = QRandomGenerator::global()->bounded(view.height() - target->height());
    return QPointF(x, y);
}


void startGameEasy(QGraphicsScene &scene, QGraphicsView &view, QLabel &countdownLabel,
                   QGraphicsProxyWidget *easyButtonProxy, QGraphicsProxyWidget *hardButtonProxy, QGraphicsProxyWidget *backButtonProxy,
                   QGraphicsProxyWidget *soloButtonProxy, QGraphicsProxyWidget *multiplayerButtonProxy, QGraphicsProxyWidget *exitButtonProxy,
                   QGraphicsProxyWidget *titleProxy, QGraphicsProxyWidget *target1Proxy, QGraphicsProxyWidget *target2Proxy) {
    // Retirer les boutons, les targets et le titre de la scène
    scene.removeItem(easyButtonProxy);
    scene.removeItem(hardButtonProxy);
    scene.removeItem(backButtonProxy);
    scene.removeItem(soloButtonProxy);
    scene.removeItem(multiplayerButtonProxy);
    scene.removeItem(exitButtonProxy);
    scene.removeItem(titleProxy);
    scene.removeItem(target1Proxy);
    scene.removeItem(target2Proxy);

    // Créer et configurer un QLabel pour afficher le compte à rebours
    countdownLabel.setAlignment(Qt::AlignCenter);
    countdownLabel.setFont(QFont("Arial", 96, QFont::Bold));
    countdownLabel.setStyleSheet("color: rgb(101, 67, 33);"); // mettre la police en blanc
    countdownLabel.setAttribute(Qt::WA_TranslucentBackground);

    // Ajouter le QLabel à la scène
    QGraphicsProxyWidget *countdownLabelProxy = scene.addWidget(&countdownLabel);
    countdownLabelProxy->setPos(view.width() / 2 - countdownLabel.width() / 2, view.height() / 2 - countdownLabel.height() / 2);

    countdownTimer.setInterval(1000); // Interval de 1000 ms (1 seconde)
    countdownTimer.setSingleShot(false); // Répéter le timer

    // Variables pour gérer le compte à rebours
    int countdownDuration = 5;
    int countdownCounter = 0;

    // Connecter le QTimer à une fonction lambda qui met à jour le QLabel
    QObject::connect(&countdownTimer, &QTimer::timeout, [&]() {
        countdownCounter++;
        countdownLabel.setText(QString::number(countdownDuration - countdownCounter));

        if (countdownCounter == countdownDuration) {
            countdownTimer.stop();
            // À ce stade, le compte à rebours est terminé.
            // Vous pouvez commencer le mode Solo Easy ici.
        }
    });

    // Démarrer le compte à rebours
    countdownLabel.setText(QString::number(countdownDuration));
    countdownTimer.start();}


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

    //déclaration d'un timer pour le jeu
    QLabel countdownLabel;
    countdownLabel.setAlignment(Qt::AlignCenter);
    countdownLabel.setFont(QFont("Arial", 96, QFont::Bold));
    countdownLabel.setStyleSheet("color: rgb(101, 67, 33);");
    countdownLabel.setAttribute(Qt::WA_TranslucentBackground);


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

    //connexion au solo easy
    QObject::connect(&easyButton, &QPushButton::clicked, [&]() {
        startGameEasy(scene, view, countdownLabel,
                      dynamic_cast<QGraphicsProxyWidget *>(easyButton.graphicsProxyWidget()),
                      dynamic_cast<QGraphicsProxyWidget *>(hardButton.graphicsProxyWidget()),
                      dynamic_cast<QGraphicsProxyWidget *>(backButton.graphicsProxyWidget()),
                      dynamic_cast<QGraphicsProxyWidget *>(soloButton.graphicsProxyWidget()),
                      dynamic_cast<QGraphicsProxyWidget *>(multiplayerButton.graphicsProxyWidget()),
                      dynamic_cast<QGraphicsProxyWidget *>(exitButton.graphicsProxyWidget()),
                      titleProxy, target1Proxy, target2Proxy);
    });




    // Ajouter la vue au layout principal
    layout.addWidget(&view);

    // Ajouter un espace en bas
    QSpacerItem *bottomSpacer = new QSpacerItem(0, 100);
    layout.addItem(bottomSpacer);

    window.show();
    return a.exec();
}
