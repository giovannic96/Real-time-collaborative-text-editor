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
private:
    bool DarkMode=false;
    bool FullScreen=false;
    bool CollaboratorBar=true;
    bool Toolbar=true;
};

#endif // EDITORSTATE_H
