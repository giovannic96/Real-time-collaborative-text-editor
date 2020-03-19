#ifndef EDITORSTATE_H
#define EDITORSTATE_H

class EditorState{
public:
    EditorState();
    bool GetDarkMode(){return DarkMode;}
    void SetDarkMode(bool value){DarkMode=value;}
    bool GetFullScreen(){return FullScreen;}
    void SetFullScreen(bool value){FullScreen=value;}
    bool GetCollaboratorBar(){return CollaboratorBar;}
    void SetCollaboratorBar(bool value){CollaboratorBar=value;}
    bool GetToolbar(){return Toolbar;}
    void SetToolbar(bool value){Toolbar=value;}
    int GetTitlebar(){return Titlebar;}
    void SetTitlebar(int value){Titlebar=value;}
    int GetThemeDay(){return DayMode_Theme;}
    void SetThemeDay(int value){DayMode_Theme=value;}
    int GetThemeDark(){return DarkMode_Theme;}
    void SetThemeDark(int value){DarkMode_Theme=value;}

private:
    bool DarkMode;              // true=enabled / false=disabled
    bool FullScreen;            // true=enabled / false=disabled
    bool CollaboratorBar;       // true=show    / false=hide
    bool Toolbar;               // true=show    / false=hide
    int Titlebar;               // [1]=ProgName / [2]=DocName / [3]=Prog+Doc / [4]=Alternate
    int DayMode_Theme;          // [1]=Classic  / [2]=Plain   / [3]=HighColor
    int DarkMode_Theme;         // [1]=Classic  / [2]=Plain   / [3]=HighColor
};

#endif // EDITORSTATE_H
