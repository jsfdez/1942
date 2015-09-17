#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

private slots:
    void on_actionNewGame_triggered();

private:
    QScopedPointer<Ui::GameWindow> m_ui;
};

#endif // GAMEWINDOW_H
