#ifndef DEBUGROOM_H
#define DEBUGROOM_H

#include <QMainWindow>

namespace Ui {
class DebugRoom;
}

class DebugRoom : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebugRoom(QWidget *parent = nullptr);
    ~DebugRoom();

private slots:
    void on_StartButton_clicked();

    void on_UserProfileButton_clicked();

    void on_EditorButton_clicked();

    void on_MenuWindowButton_clicked();

private:
    Ui::DebugRoom *ui;
};

#endif // DEBUGROOM_H
