#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "editorstate.h"

namespace Ui { class Settings;}

class Settings : public QWidget{
    Q_OBJECT

public:
    explicit Settings(EditorState& estate, QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_Save_clicked();
    void on_Default_clicked();
    void on_Abort_clicked();

    void on_ComboDay_currentIndexChanged(int index);

    void on_ComboDark_currentIndexChanged(int index);

signals:
    void closeSettings();

private:
    void LoadAndSetDefaultRadioButton();
    void WriteSettingOnFile();

private:
    Ui::Settings *ui;
    EditorState &estate;
};

#endif // SETTINGS_H
