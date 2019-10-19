# Changelog ClientModule

### Note
- Valutare la possibilità si spostare la connessione al server sol dopo il click sul pulsante accedi o registrati anzichè all'apertura della finestra di login.
  Il caricamento della finestra è molto rallentato a causa del tentativo di connessione
- Valutare la possibilità di rendere tutte le precedenti finestre con bordi arrotondati
### Todo
- Rimuovere immagini non usate dalla cartella "image"

## [v0.1.4a - Canary 1190] - 2019/10/18 @ 20:00
### Aggiunto
- Aggiornamento cumulativo v0.1.2a --> v0.1.4a
- Classe "StartWindow" - Racchiude Login, Registrazione e Menù iniziale in un unica window
- Distruttore (in debug) della finestra UserProfile
### Deprecato
- Classe "LoginWindow"
- Classe "RegWindow"
- Classe "StartMenu"
- Connessione al database SQLite

## [v0.1.3a - Nightly 1185] - 2019/10/17 @ 23:40
- Versione di test

## [v0.1.3a - Nightly 1184] - 2019/10/17 @ 23:40 - DELETED
- Versione eliminata a causa di una scelta progettuale più efficiente
  Abbandonata l'idea di una classe che switchasse le ui delle altre classi
  a favore dello Stacked Widget

## [v0.1.3a - Nightly 1183] - 2019/10/16 @ 23:30
### Cambiamenti
- aggiunto nomeutente nella userprofile window passato come argomento al costruttore
- aggiunta riga "delete this;" su startmenù per un test sul fix del bug del distruttore
- aggiunte istruzioni di qdebug per richiamo del distruttore

## [v0.1.3a - Nightly 1182] - 2019/10/16 @ 22:30
### Aggiunto
- Funzione che rende bordi rotondi della UserProfile Window
- Libreria QMessageBox dalla classe RegWindow (rimossa per errore nella build precedente)
### Cambiamenti
- Sistemata label della connessione

## [v0.1.3a - Nightly 1180] - 2019/10/16 @ 15:00
### Aggiunto
- Bottone per apertura text editor dallo start menù
### Rimosso
- Libreria QMessageBox dalla classe RegWindow

## [v0.1.3a - Nightly 1179] - 2019/10/16 @ 01:00
### Cambiamenti
- Funzione che permette al server di connettersi al database per recuperare le informazioni dell'utente

## [v0.1.3a - Nightly 1178] - 2019/10/15 @ 23:30
### Aggiunto
- Funzioni di gestione della connessione nella schermata di login
### Cambiamenti
- Fix della finestra di login

## [v0.1.3a - Nightly 1176] - 2019/10/15 @ 20:45
### Cambiamenti
- Sostituito pannello di controllo (di debug) per la connessione al server con funzione lanciata allo startup

## [v0.1.3a - Nightly 1175] - 2019/10/15 @ 00:10
### Aggiunto
- Classe "UserProfile" --> (una finestra popup con il profilo dell'utente)
- Placeholder per l'immagine dell'utente
### Cambiamenti
- Correzione di alcuni parametri e correzioni generali nel codice
### Rimosso
- Libreria QMessageBox dalla classe StartMenu

## [v0.1.3a - Nightly 1174] - 2019/10/14 @ 04:10
### Aggiunto
- Pulsante per l'accesso come superuser (administrator) usato per debug
- Pulsante per far disconnettere l'utente
### Cambiamenti
- La stringa username di "startmenu.h" adesso è un bottone (porterà l'utente nella sua pagina personale)
- Cambiati alcuni stylesheet

## [v0.1.3a - Nightly 1173] - 2019/10/13 @ 03:00  - MERGED BUILD
### Cambiamenti
- Merged con la build di Giovanni.
### NOTE
- Codice non testato, non pronto per una Canary, tuttavia costituisce la base per i prossimi update
- Aggiornamento v0.1.2 --> v0.1.3

## [v0.1.2a - Canary 1052] - 2019/10/09 @ 00:15  - LOST UPDATE
### Cambiamenti
- Pulizia codice
- Commenti sistemati e tradotti in inglese (metterli in italiano?)

## [v0.1.2a - Nighly 1051] - LOST UPDATE

## [v0.1.2a - Canary 1050] - 2019/10/08 @ 21:00  - LOST UPDATE
### Aggiunto
- Classe "StartMenu"
- Costruttore window con parametro nella StartMenu
### Cambiamenti
- Breve pulizia del codice della classe Login

## [v0.1.2a - Nightly 1047] - 2019/10/08 @ 18:00  - LOST UPDATE
### Cambiamenti
- Aggiunta connessione DB

## [v0.1.2a - Nighly 1046] - 2019/10/08 @ 17:00  - LOST UPDATE
### Cambiamenti
- BugFix della UI

## [v0.1.2a - Nighly 1045] - 2019/10/08 @ 16:00  - LOST UPDATE
### Cambiamenti
- Cambiamento radicale della UI

## [v0.1.2a - Nighly 1044] - LOST UPDATE
### Rimosso
- File texteditor_users.sqlite

## [v0.1.2a - Canary 1043] - 2019/10/05 @ 20:00
### Cambiamenti
- Switching tra finestre corretto
- BugFix vari

## [v0.1.1a - Daily 1042] - 2019/10/05 @ 18:50
### Cambiamenti
- Classe SingupWindow è stata ricreata col nome RegWindow
### Todo
- Correggere switching tra finestre

## [v0.1.1a - Daily 1031] - 2019/10/05 @ 17:00
### Aggiunto
- Classe SingupWindow
### Todo
- Correggere switching tra finestre

## [v0.1.1a - Daily 1021] - 2019/10/05 @ 15:15
### Aggiunto
- File texteditor_users.sqlite
- Handling del click sul bottone SingUp
- Handling del click sul bottone Login

## [v0.1.1a - Canary 1001] - 2019/10/05 @ 12:40
### Aggiunto
- Classe "LoginWindow"
- Classe "VersionInfo"
### Cambiamenti
- n/A
### Rimosso
- n/A
### Deprecato
- n/A
### Todo
- n/A
