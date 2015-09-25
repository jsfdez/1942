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

private:
    void loadSettings();
    void saveSettings();

    QScopedPointer<Ui::GameWindow> m_ui;
    quint32 m_highScore = 0;

private slots:
    void newGame();
    void showAbout();
    void showAboutQt();
    void toggleDisplayEnemyHealthBars(bool value);
	void toggleUseOpenGL(bool value);
};

#endif // GAMEWINDOW_H
