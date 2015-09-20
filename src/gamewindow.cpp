#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QDebug>
#include <QTimer>
#include <QString>
#include <QOpenGLWidget>

#include "gamescene.h"

const auto k_currentGameObjectName = QStringLiteral("currentGame");

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::GameWindow)
{
    m_ui->setupUi(this);
    m_ui->graphicsView->setViewport(new QOpenGLWidget(this));

    QTimer::singleShot(0, this, &GameWindow::on_actionNewGame_triggered);
}

GameWindow::~GameWindow()
{
}

void GameWindow::on_actionNewGame_triggered()
{
    qDebug() << "Starting a new game";
    auto scene = new GameScene(this);
    scene->setObjectName(k_currentGameObjectName);
    m_ui->graphicsView->setScene(scene);
}
