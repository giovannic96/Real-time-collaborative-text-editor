# Changelog ClientModule

## [v0.1.3a - Nightly 1180] - 2019/10/16 @ 15:00
### Aggiunto
- Bottone per apertura text editor dallo start menù
### Rimosso
- Libreria QMessageBox dalla classe RegWindow
### Note
- Valutare la possibilità si spostare la connessione al server sol dopo il click sul pulsante accedi o registrati anzichè all'apertura della finestra di login.
### Todo
- Rimuovere immagini non usate dalla cartella "image"

## [v0.1.3a - Nightly 1178] - 2019/10/16 @ 01:00
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
- Codice unito con il lavoro di Giovanni.
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
### Build note
- Cambiare Path DB locale
### Todo
- Aggiungere classe DBManager per gestire meglio connessione con DB e distruttore db

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
