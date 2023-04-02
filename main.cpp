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
<<<<<<< HEAD
=======
#include <QDebug>
>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7
#include <QFile>
#include <QTextStream>
#include <functional>
#include <QMediaPlayer>
<<<<<<< HEAD
=======

>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7

#include "target.h"
#include "gamehandler.h"

void onTargetClickedHard(QGraphicsScene &scene, QGraphicsView &view, Target *clickedTarget, int &targetsHitCount, GameHandler &gameHandler, QTimer &hardModeTimer);
void onTimeoutHard(QGraphicsScene &scene, QGraphicsView &view, Target *oldTarget, int &targetsHitCount, GameHandler &gameHandler, QTimer &hardModeTimer);

// Fonction pour afficher les règles du jeu
    void showRules()
    {
        QMessageBox rulesMessageBox;
        rulesMessageBox.setWindowTitle("Règles du jeu");
        rulesMessageBox.setText("Voici les règles du jeu:\n\n"
<<<<<<< HEAD
                                "1. Solo_easy : Des cibles vont apparaître une à une pendant 10 secondes. Le but du jeu et de tirer sur le plus de cibles possibles pendant le temps imparti.\n\n"
                                "2. Solo_difficile : Des  cibles vont apparaître une à une pendant 30 secondes. Contrairement au premier mode de jeu les cibles disparaissent rapidement    . Vous devez donc être réactif !\n\n"
                                "Essayez de cliquer sur  la cible de droite du menu pour faire apparaitre un canard et le faire chanter !\n\n"
=======
                                "1. Solo_easy : Des cibles vont apparaître une à une pendant 30 secondes. Le but du jeu et de tirer sur le plus de cibles possibles pendant le temps imparti.\n\n"
                                "2. Solo_difficile : Des  cibles vont apparaître une à une pendant 30 secondes. Contrairement au premier mode de jeu les cibles disparaissent au bout de 1 seconde et sont plus petites. Vous devez donc être réactif !\n\n"
>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7
                                "Amusez-vous bien!");
        rulesMessageBox.exec();
    }

// Fonction pour passer au menu Solo
void switchToSoloMenu(QPushButton &easyButton, QPushButton &hardButton, QPushButton &backButton,
                      QPushButton &soloButton, QPushButton &rulesButton, QPushButton &exitButton)
{
    // Masquer les boutons "Solo", "Règles" et "Quitter"
    soloButton.hide();
    rulesButton.hide();
    exitButton.hide();

    // Afficher les boutons "Facile", "Difficile" et "Retour"
    easyButton.show();
    hardButton.show();
    backButton.show();
}


//fct pour le bouton retour après avoir cliqué sur solo
void switchToMainMenu(QPushButton &easyButton,
                      QPushButton &hardButton,
                      QPushButton &backButton,
                      QPushButton &soloButton,
                      QPushButton &rulesButton,
                      QPushButton &exitButton)
{
    // Masquer les boutons "Facile", "Difficile" et "Retour"
    easyButton.hide();
    hardButton.hide();
    backButton.hide();

    // Afficher les boutons "Solo", "Règles" et "Quitter"
    soloButton.show();
    rulesButton.show();
    exitButton.show();
}


//fct qui permet un retour au menu à la fin d'une partie
void resetToMainMenu(QGraphicsScene &scene, QGraphicsView &view, QPushButton &easyButton,
                     QPushButton &hardButton, QPushButton &backButton,
                     QPushButton &soloButton, QPushButton &rulesButton, QPushButton &exitButton,
                     QLabel &title, Target *target1, Target *target2) {
    // Réinitialisez tous les éléments du menu
    soloButton.show();
    rulesButton.show();
    exitButton.show();
    title.show();
    target1->show();
    target2->show();

    // Masquer les boutons "Facile", "Difficile" et "Retour"
    easyButton.hide();
    hardButton.hide();
    backButton.hide();
<<<<<<< HEAD
}

void onTarget1Clicked(QGraphicsScene &scene, QGraphicsView &view, Target *target1) {
    QPixmap canardPixmap("canard.jpg");
    QGraphicsPixmapItem *canardItem = new QGraphicsPixmapItem(canardPixmap.scaled(QSize(500, 500), Qt::KeepAspectRatio));
    canardItem->setPos(target1->pos());
    scene.addItem(canardItem);

    // Créer et configurer QMediaPlayer pour jouer le son
    QMediaPlayer *mediaPlayer = new QMediaPlayer;
    mediaPlayer->setMedia(QUrl("qrc:/sounds/duck-quack2.wav"));
    mediaPlayer->setVolume(100);

    // Jouer le son
    mediaPlayer->play();

    // Supprimer le mediaPlayer lorsque le son est terminé
    QObject::connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, [mediaPlayer](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            mediaPlayer->deleteLater();
        }
    });
=======
>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7
}

void onTarget1Clicked(QGraphicsScene &scene, QGraphicsView &view, Target *target1) {
    QPixmap canardPixmap("canard.jpg");
    QGraphicsPixmapItem *canardItem = new QGraphicsPixmapItem(canardPixmap.scaled(QSize(500, 500), Qt::KeepAspectRatio));
    canardItem->setPos(target1->pos());
    scene.addItem(canardItem);

    // Créer et configurer QMediaPlayer pour jouer le son
    QMediaPlayer *mediaPlayer = new QMediaPlayer;
    mediaPlayer->setMedia(QUrl("qrc:/sounds/duck-quack2.wav"));
    mediaPlayer->setVolume(100);

    // Jouer le son
    mediaPlayer->play();

    // Supprimer le mediaPlayer lorsque le son est terminé
    QObject::connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, [mediaPlayer](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            mediaPlayer->deleteLater();
        }
    });
}



void onTargetClicked(QGraphicsScene &scene, QGraphicsView &view, Target *clickedTarget, int &targetsHitCount, GameHandler &gameHandler) {
    // Supprimez la cible cliquée
    scene.removeItem(scene.itemAt(clickedTarget->pos(), QTransform()));
    delete clickedTarget;
    targetsHitCount++;

    // Créez une nouvelle cible après une courte pause
    QTimer::singleShot(50, [&scene, &view, &targetsHitCount, &gameHandler]() {
        Target *newTarget = gameHandler.createRandomTarget(scene, view);

        // Connectez le signal clicked de la nouvelle cible à la fonction onTargetClicked
        QObject::connect(newTarget, &Target::clicked, [&scene, &view, newTarget, &targetsHitCount, &gameHandler]() {
            onTargetClicked(scene, view, newTarget, targetsHitCount, gameHandler);
        });
    });
}

void onTargetClickedHard(QGraphicsScene &scene, QGraphicsView &view, Target *clickedTarget, int &targetsHitCount, GameHandler &gameHandler, QTimer &hardModeTimer) {
<<<<<<< HEAD
=======
    // Créez une nouvelle cible
    Target *newTarget = gameHandler.createRandomTarget(scene, view);

    // Connectez le signal clicked de la nouvelle cible à la fonction onTargetClickedHard
    QObject::connect(newTarget, &Target::clicked, [&scene, &view, newTarget, &targetsHitCount, &gameHandler, &hardModeTimer]() {
        onTargetClickedHard(scene, view, newTarget, targetsHitCount, gameHandler, hardModeTimer);
    });

>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7
    // Supprimez la cible cliquée
    scene.removeItem(scene.itemAt(clickedTarget->pos(), QTransform()));
    delete clickedTarget;
    targetsHitCount++;

<<<<<<< HEAD
    // Créez une nouvelle cible après une courte pause
    QTimer::singleShot(50, [&scene, &view, &targetsHitCount, &gameHandler, &hardModeTimer]() {
        Target *newTarget = gameHandler.createRandomTarget(scene, view);

        // Connectez le signal clicked de la nouvelle cible à la fonction onTargetClickedHard
        QObject::connect(newTarget, &Target::clicked, [&scene, &view, newTarget, &targetsHitCount, &gameHandler, &hardModeTimer]() {
            onTargetClickedHard(scene, view, newTarget, targetsHitCount, gameHandler, hardModeTimer);
        });

        // Redémarrer le timer
        hardModeTimer.stop();
        hardModeTimer.setSingleShot(true);
        hardModeTimer.disconnect();
        QObject::connect(&hardModeTimer, &QTimer::timeout, [&scene, &view, newTarget, &targetsHitCount, &gameHandler, &hardModeTimer]() {
            onTimeoutHard(scene, view, newTarget, targetsHitCount, gameHandler, hardModeTimer);
        });
        hardModeTimer.start(1000);
    });
    hardModeTimer.stop();
}

=======
    // Redémarrer le timer
    hardModeTimer.stop();
    hardModeTimer.setSingleShot(true);
    hardModeTimer.disconnect();
    QObject::connect(&hardModeTimer, &QTimer::timeout, [&scene, &view, newTarget, &targetsHitCount, &gameHandler, &hardModeTimer]() {
        onTimeoutHard(scene, view, newTarget, targetsHitCount, gameHandler, hardModeTimer);
    });
    hardModeTimer.start(1000);
}



>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7
int readBestScore(const QString &fileName, const QString &gameMode) {
    QFile file(fileName + "_" + gameMode + ".txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0;
    }

    QTextStream in(&file);
    int bestScore = in.readLine().toInt();
    file.close();
    return bestScore;
}

void saveBestScore(const QString &fileName, int bestScore, const QString &gameMode) {
    QFile file(fileName + "_" + gameMode + ".txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << bestScore;
    file.close();
}
<<<<<<< HEAD
=======

>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7

void startGameEasy(QGraphicsScene &scene, QGraphicsView &view, QPushButton &easyButton,
                   QPushButton &hardButton, QPushButton &backButton,
                   QPushButton &soloButton, QPushButton &rulesButton, QPushButton &exitButton,
                   QLabel &title, Target *target1, Target *target2,  QTimer &gameTimer, int &targetHitCount, GameHandler &gameHandler) {

    // Masquez tous les éléments du menu
    easyButton.hide();
    hardButton.hide();
    backButton.hide();
    soloButton.hide();
    rulesButton.hide();
    exitButton.hide();
    title.hide();
    target1->hide();
    target2->hide();

    // Créez la première cible
    Target *newTarget = gameHandler.createRandomTarget(scene, view);

    // Connectez le signal clicked de la nouvelle cible à la fonction onTargetClicked
    QObject::connect(newTarget, &Target::clicked, [&scene, &view, newTarget, &targetHitCount, &gameHandler]() {
        onTargetClicked(scene, view, newTarget, targetHitCount, gameHandler);
    });

    // Démarrez le QTimer pour une durée de 20 secondes
    gameTimer.setSingleShot(true);
<<<<<<< HEAD
    gameTimer.start(10000);
=======
    gameTimer.start(20000);
>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7
}

void onTimeoutHard(QGraphicsScene &scene, QGraphicsView &view, Target *oldTarget, int &targetsHitCount, GameHandler &gameHandler, QTimer &hardModeTimer) {
    // Supprimez l'ancienne cible
    scene.removeItem(scene.itemAt(oldTarget->pos(), QTransform()));
    delete oldTarget;

    // Créez une nouvelle cible
    Target *newTarget = gameHandler.createRandomTarget(scene, view);

    // Connectez le signal clicked de la nouvelle cible à la fonction onTargetClickedHard
    QObject::connect(newTarget, &Target::clicked, [&scene, &view, newTarget, &targetsHitCount, &gameHandler, &hardModeTimer]() {
        onTargetClickedHard(scene, view, newTarget, targetsHitCount, gameHandler, hardModeTimer);
    });

    // Configurez le timer pour supprimer la cible après 1 seconde si elle n'a pas été cliquée
    hardModeTimer.setInterval(500);
    hardModeTimer.setSingleShot(true);

    // Déconnectez les signaux précédents avant de reconnecter
    hardModeTimer.disconnect();
    QObject::connect(&hardModeTimer, &QTimer::timeout, [&scene, &view, newTarget, &targetsHitCount, &gameHandler, &hardModeTimer]() {
        onTimeoutHard(scene, view, newTarget, targetsHitCount, gameHandler, hardModeTimer);
    });

    // Démarrez le timer
    hardModeTimer.start();
}

<<<<<<< HEAD
=======

>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7
void startGameHard(QGraphicsScene &scene, QGraphicsView &view, QPushButton &easyButton,
                   QPushButton &hardButton, QPushButton &backButton,
                   QPushButton &soloButton, QPushButton &rulesButton, QPushButton &exitButton,
                   QLabel &title, Target *target1, Target *target2,  QTimer &gameTimer, int &targetsHitCount, GameHandler &gameHandler, QTimer &hardModeTimer) {

    // Masquez tous les éléments du menu
    easyButton.hide();
    hardButton.hide();
    backButton.hide();
    soloButton.hide();
    rulesButton.hide();
    exitButton.hide();
    title.hide();
    target1->hide();
    target2->hide();

    // Créez une nouvelle cible
    Target *newTarget = gameHandler.createRandomTarget(scene, view);

    // Connectez le signal clicked de la nouvelle cible à la fonction onTargetClickedHard
    QObject::connect(newTarget, &Target::clicked, [&scene, &view, newTarget, &targetsHitCount, &gameHandler, &hardModeTimer]() {
        onTargetClickedHard(scene, view, newTarget, targetsHitCount, gameHandler, hardModeTimer);
    });

    // Configurez le timer pour supprimer la cible après 1 seconde si elle n'a pas été cliquée
    hardModeTimer.setInterval(500);
    hardModeTimer.setSingleShot(true);

    // Déconnectez les signaux précédents avant de reconnecter
    hardModeTimer.disconnect();
    QObject::connect(&hardModeTimer, &QTimer::timeout, [&scene, &view, newTarget, &targetsHitCount, &gameHandler, &hardModeTimer]() {
        onTimeoutHard(scene, view, newTarget, targetsHitCount, gameHandler, hardModeTimer);
    });

    // Démarrez le QTimer pour une durée de 20 secondes
    gameTimer.setSingleShot(true);
<<<<<<< HEAD
    gameTimer.start(10000);
=======
    gameTimer.start(5000);
>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7

    // Démarrez le timer
    hardModeTimer.start();


}

<<<<<<< HEAD
=======



>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7
void endGameEasy(QGraphicsScene &scene, QGraphicsView &view, QPushButton &easyButton,
                 QPushButton &hardButton, QPushButton &backButton,
                 QPushButton &soloButton, QPushButton &rulesButton, QPushButton &exitButton,
                 QLabel &title, Target *target1, Target *target2,  QTimer &gameTimer, int &targetsHitCount, GameHandler &gameHandler, const QString &scoreFileName) {

    // Supprimez la dernière cible créée
    if (gameHandler.getLastCreatedTarget()) {
        scene.removeItem(scene.itemAt(gameHandler.getLastCreatedTarget()->pos(), QTransform()));
        delete gameHandler.getLastCreatedTarget();
        gameHandler.setLastCreatedTarget(nullptr);
    }

    // Lisez le meilleur score actuel
    int bestScore = readBestScore(scoreFileName, "easy");

    // Mettez à jour le meilleur score si nécessaire
    if (targetsHitCount > bestScore) {
        bestScore = targetsHitCount;
        saveBestScore(scoreFileName, bestScore, "easy");
    }

    // Affichez la pop-up
    QMessageBox endGameMessageBox;
    endGameMessageBox.setWindowTitle("Jeu terminé");
    endGameMessageBox.setText(QString("La partie est terminée !\n\nCibles touchées : %1\n\nMeilleur score : %2").arg(targetsHitCount).arg(bestScore));
    endGameMessageBox.addButton(QMessageBox::Ok);

    // Exécutez la boîte de dialogue
    endGameMessageBox.exec();

    resetToMainMenu(scene, view, easyButton, hardButton, backButton, soloButton, rulesButton, exitButton, title, target1, target2);

<<<<<<< HEAD

}

void endGameHard(QGraphicsScene &scene, QGraphicsView &view, QPushButton &easyButton,
                 QPushButton &hardButton, QPushButton &backButton,
                 QPushButton &soloButton, QPushButton &rulesButton, QPushButton &exitButton,
                 QLabel &title, Target *target1, Target *target2, int &targetsHitCount, GameHandler &gameHandler, QTimer &hardModeTimer, const QString &scoreFileName) {

    // Arrêtez le timer hardMode
    hardModeTimer.stop();

    // Supprimez la dernière cible créée
    if (gameHandler.getLastCreatedTarget()) {
        scene.removeItem(scene.itemAt(gameHandler.getLastCreatedTarget()->pos(), QTransform()));
        delete gameHandler.getLastCreatedTarget();
        gameHandler.setLastCreatedTarget(nullptr);
=======
    // Parcourir tous les éléments de la scène et les afficher dans la console
    for (QGraphicsItem *item : scene.items()) {
        qDebug() << "Element:" << item
                 << "Type:" << item->type()
                 << "Position:" << item->pos();
>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7
    }
}

void endGameHard(QGraphicsScene &scene, QGraphicsView &view, QPushButton &easyButton,
                 QPushButton &hardButton, QPushButton &backButton,
                 QPushButton &soloButton, QPushButton &rulesButton, QPushButton &exitButton,
                 QLabel &title, Target *target1, Target *target2, int &targetsHitCount, GameHandler &gameHandler, QTimer &hardModeTimer, const QString &scoreFileName) {

    // Arrêtez le timer hardMode
    hardModeTimer.stop();

    // Supprimez la dernière cible créée
    if (gameHandler.getLastCreatedTarget()) {
        scene.removeItem(scene.itemAt(gameHandler.getLastCreatedTarget()->pos(), QTransform()));
        delete gameHandler.getLastCreatedTarget();
        gameHandler.setLastCreatedTarget(nullptr);
    }

    // Lisez le meilleur score actuel
    int bestScore = readBestScore(scoreFileName, "hard");

    // Mettez à jour le meilleur score si nécessaire
    if (targetsHitCount > bestScore) {
        bestScore = targetsHitCount;
        saveBestScore(scoreFileName, bestScore, "hard");
    }

    // Affichez un message de fin de partie avec le nombre de cibles touchées
    QMessageBox endGameMessageBox;
    endGameMessageBox.setWindowTitle("Jeu terminé");
    endGameMessageBox.setText(QString("La partie est terminée !\n\nCibles touchées : %1\n\nMeilleur score : %2").arg(targetsHitCount).arg(bestScore));
    endGameMessageBox.addButton(QMessageBox::Ok);

    // Exécutez la boîte de dialogue
    endGameMessageBox.exec();

    resetToMainMenu(scene, view, easyButton, hardButton, backButton, soloButton, rulesButton, exitButton, title, target1, target2);

    // Lisez le meilleur score actuel
    int bestScore = readBestScore(scoreFileName, "hard");

    // Mettez à jour le meilleur score si nécessaire
    if (targetsHitCount > bestScore) {
        bestScore = targetsHitCount;
        saveBestScore(scoreFileName, bestScore, "hard");
    }

    // Affichez un message de fin de partie avec le nombre de cibles touchées
    QMessageBox endGameMessageBox;
    endGameMessageBox.setWindowTitle("Jeu terminé");
    endGameMessageBox.setText(QString("La partie est terminée !\n\nCibles touchées : %1\n\nMeilleur score : %2").arg(targetsHitCount).arg(bestScore));
    endGameMessageBox.addButton(QMessageBox::Ok);

    // Exécutez la boîte de dialogue
    endGameMessageBox.exec();

    resetToMainMenu(scene, view, easyButton, hardButton, backButton, soloButton, rulesButton, exitButton, title, target1, target2);

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

<<<<<<< HEAD
    //déclaration variable utile pour les parties (utilisées dans les fonctions)
=======
    //déclaration variable utile pour les parties
>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7
    QTimer gameTimerEasy;
    QTimer gameTimerHard;
    int targetsHitCount = 0;
    GameHandler gameHandler(scene, view, targetsHitCount);
    QString scoreFileName = "best_score";
    QTimer hardModeTimer;
    hardModeTimer.setSingleShot(true);

    // Ajouter un espace en haut
    QSpacerItem *topSpacer = new QSpacerItem(0, 100);
    layout.addItem(topSpacer);

    // Créer le titre
    QLabel title("CoinCoinShooter");
    title.setAlignment(Qt::AlignCenter);
    title.setFont(QFont("Arial", 96, QFont::Bold));
    title.setStyleSheet("color: rgb(101, 67, 33);");
    title.setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsProxyWidget *titleProxy = scene.addWidget(&title);
    titleProxy->setPos(view.width() / 2 - title.width() / 2, 100);

    // Créer la première cible à droite du titre
    Target *target1 = new Target();
    target1->setFixedSize(150, 150);
    QGraphicsProxyWidget *target1Proxy = scene.addWidget(target1);
    target1Proxy->setPos(titleProxy->pos().x() + title.width() + 50, titleProxy->pos().y());

<<<<<<< HEAD
    QObject::connect(target1, &Target::clicked, [&scene, &view, target1]() {
        onTarget1Clicked(scene, view, target1);
    });
=======
    //test clic target
    QObject::connect(target1, &Target::clicked, [&scene, &view, target1]() {
        onTarget1Clicked(scene, view, target1);
    });

>>>>>>> 4f765d01cd6a26da89baea1baab603fdbcc33bc7

    // Créer la deuxième cible à gauche des boutons
    Target *target2 = new Target();
    target2->setFixedSize(150, 150);
    QGraphicsProxyWidget *target2Proxy = scene.addWidget(target2);
    target2Proxy->setPos(view.width() / 2 - target2->width() / 2 - 600, view.height() / 2 - target2->height() / 2 - 100);

    QObject::connect(target2, &Target::clicked, [&scene, &view, &gameHandler](){
        gameHandler.createRandomTarget(scene, view);
    });

    // Créer le bouton "Solo"
    QPushButton soloButton("Solo");
    soloButton.setFont(QFont("Arial", 48));
    soloButton.setStyleSheet("color: rgb(85, 85, 85); border: 2px solid white ; width: 540px ; height: 110px;");

    // Ajouter le bouton Solo à la scène
    QGraphicsProxyWidget *soloButtonProxy = scene.addWidget(&soloButton);
    soloButtonProxy->setPos(view.width() / 2 - soloButton.width() / 2, view.height() / 2 - soloButton.height() / 2 - 50);

    // Créer le bouton "Règles"
    QPushButton rulesButton("Règles");
    rulesButton.setFont(QFont("Arial", 48));
    rulesButton.setStyleSheet("color: rgb(85, 85, 85); border: 2px solid white ; width: 540px ; height: 110px ;");

    // Ajouter le bouton Règles à la scène
    QGraphicsProxyWidget *rulesButtonProxy = scene.addWidget(&rulesButton);
    rulesButtonProxy->setPos(view.width() / 2 - rulesButton.width() / 2, view.height() / 2 - rulesButton.height() / 2 + 50);

    //Connexion du signal clicked du bouton Règles
    QObject::connect(&rulesButton, &QPushButton::clicked, &a, [&]() { showRules(); });

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
    hardButtonProxy->setPos(rulesButtonProxy->pos());
    hardButtonProxy->setVisible(false);

    QGraphicsProxyWidget *backButtonProxy = scene.addWidget(&backButton);
    backButtonProxy->setPos(exitButtonProxy->pos());
    backButtonProxy->setVisible(false);

    // Connexion du signal "clicked" du bouton Solo
    QObject::connect(&soloButton, &QPushButton::clicked, [&]() {
        switchToSoloMenu(easyButton, hardButton, backButton, soloButton, rulesButton, exitButton);
    });


    // Connexion du signal "clicked" du bouton retour
    QObject::connect(&backButton, &QPushButton::clicked, [&]() {
        switchToMainMenu(easyButton, hardButton, backButton, soloButton, rulesButton, exitButton);
    });


    // Connexion du signal "clicked" du bouton easy
    QObject::connect(&easyButton, &QPushButton::clicked, [&](){
        startGameEasy(scene, view, easyButton, hardButton, backButton, soloButton, rulesButton, exitButton, title, target1, target2, gameTimerEasy, targetsHitCount, gameHandler);
        targetsHitCount = 0; // Réinitialisez le compteur de cibles touchées au début de chaque partie
    });

    // Connexion du signal "clicked" du bouton de la pop up en fin de partie
    QObject::connect(&gameTimerEasy, &QTimer::timeout, [&](){
        endGameEasy(scene, view, easyButton, hardButton, backButton, soloButton, rulesButton, exitButton, title, target1, target2, gameTimerEasy, targetsHitCount, gameHandler, scoreFileName);
    });

    QObject::connect(&hardButton, &QPushButton::clicked, [&]() {
        startGameHard(scene, view, easyButton, hardButton, backButton, soloButton, rulesButton, exitButton, title, target1, target2, gameTimerHard, targetsHitCount, gameHandler, hardModeTimer);
        targetsHitCount = 0; // Réinitialisez le compteur de cibles touchées au début de chaque partie
    });

    QObject::connect(&gameTimerHard, &QTimer::timeout, [&]() {
        endGameHard(scene, view, easyButton, hardButton, backButton, soloButton, rulesButton, exitButton, title, target1, target2, targetsHitCount, gameHandler, hardModeTimer, scoreFileName);
    });




    // Ajouter la vue au layout principal
    layout.addWidget(&view);

    // Ajouter un espace en bas
    QSpacerItem *bottomSpacer = new QSpacerItem(0, 100);
    layout.addItem(bottomSpacer);

    window.show();
    return a.exec();
}