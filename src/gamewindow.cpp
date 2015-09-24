#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QDebug>
#include <QTimer>
#include <QString>
#include <QSettings>
#include <QMessageBox>
#include <QOpenGLWidget>

#include "gamescene.h"

const auto k_currentGameObjectName = QStringLiteral("currentGame");

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::GameWindow)
{
    m_ui->setupUi(this);
    m_ui->graphicsView->setViewport(new QOpenGLWidget(this));

    loadSettings();

    setWindowTitle(QString("1942").arg(m_highScore));

    metaObject()->invokeMethod(this, "newGame");
}

GameWindow::~GameWindow()
{
}

void GameWindow::loadSettings()
{
    const QSettings settings;
    m_highScore = settings.value("highScore", 0).toUInt();
    auto displayEnemyHealthBars = settings.value(
        "displayEnemyHealth", m_ui->actionDisplayEnemyHealthBars->isChecked());
    m_ui->actionDisplayEnemyHealthBars->setChecked(
        displayEnemyHealthBars.toBool());
    toggleDisplayEnemyHealthBars(displayEnemyHealthBars.toBool());
}

void GameWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("highScore", m_highScore);
    settings.setValue("displayEnemyHealth",
        m_ui->actionDisplayEnemyHealthBars->isChecked());
}

void GameWindow::newGame()
{
    qDebug() << "Starting a new game";
    statusBar()->showMessage(QString("High score: %1. Press P to pause")
        .arg(m_highScore));

    auto scene = new GameScene(this);
    scene->setObjectName(k_currentGameObjectName);
    m_ui->graphicsView->setScene(scene);
    m_ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    connect(scene, &GameScene::gameFinished, this, [&](quint32 score)
    {
        if(score > m_highScore)
        {
            m_highScore = score;
            saveSettings();
            statusBar()->showMessage(QString("Game finished (Click to restart) "
                "- NEW HIGH SCORE: %1").arg(m_highScore));
            setWindowTitle(QString("1942 - Game finished - NEW HIGH SCORE: "
                "%1 (Click to restart)").arg(m_highScore));
        }
        else
        {
            statusBar()->showMessage(QString("Game finished (Click to restart) "
                "- High score: %1").arg(m_highScore));
        }
    });
    connect(scene, &GameScene::restart, this, [&]()
    {
        metaObject()->invokeMethod(this, "newGame");
    });
}

void GameWindow::showAbout()
{
    QMessageBox::about(this, "1942", "A 1942 remake using QGraphicsView");
}

void GameWindow::showAboutQt()
{
    qApp->aboutQt();
}

void GameWindow::toggleDisplayEnemyHealthBars(bool value)
{
    qApp->setProperty("displayEnemyHealthBars", value);
}
