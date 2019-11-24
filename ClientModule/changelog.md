# Changelog ClientModule

### TODO
- BUG --> Ridimensionamento finestre/bottoni al cambio di DPI -> HALF FIXED
          Vedi branch FramelessOrNot per una soluzione migliore

## [v0.1.9a - Daily 1255] - 2019/11/24 @ 13:00
### Cambiamenti
- Unificati messaggi d'errore - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/39]

## [v0.1.9a - Daily 1254] - 2019/11/24 @ 12:10 - MERGED
### Cambiamenti
- Merge manuale delle ultime build

## [v0.1.9a - Nightly 1253] - 2019/11/23 @ 18:10
### Aggiunto
- Corrette funzionalità di debug

## [v0.1.9a - Daily 1252] - 2019/11/23 @ 17:10
### Cambiamenti
- BugFix -> Corretto problema che si verificava quando si scriveva velocemente sull'editor

## [v0.1.9a - Daily 1251] - 2019/11/22 @ 19:10
### Cambiamenti
- Di default, l'icona AlignSX è cliccata
- Corretto Stylesheet bottoni
- Modificata funzione del KeyReleaseEvent
- Piccola correzione del qDebug

## [v0.1.9a - Canary 1250] - 2019/11/22 @ 16:40
### Cambiamenti
- Corretto Risorse.qrc e altri file legati alle immagini.
- Pulita cartella delle immagini

## [v0.1.9a - Daily 124F] - 2019/11/21 @ 02:15
### Aggiunto
- Introdotta soluzione tampone alla stringa json passata con accenti. - La soluzione testata nella build 124D non funziona più dalla 124E
- Ripristinata pagina 0 della startwindow
- BugFix - Messaggio di errore rinominando il documento con lo stesso nome di un altro

## [v0.1.9a - Daily 124E] - 2019/11/20 @ 14:20
### Cambiamenti
- Corretto il renaming del file dall'editor - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/20]

## [v0.1.9a - Nightly 124D] - 2019/11/19 @ 18:40
### Aggiunto
- Aggiunti controlli per la validazione dei form - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/20]
- Aggiunti stringhe sulla startwindow che appaiono nel caso in cui un form sia errato
### Rimosso
- Cancellato il database locale del client.

## [v0.1.9a - Nightly 124C] - 2019/11/18 @ 22:30
### Cambiamenti
- Lunghezza filename del testo portata da 15 a 25 (in menuWindow).
- Nella lista dei file, se la lunghezza è maggiore a 15, il filename viene troncato - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/33]

## [v0.1.9a - Nightly 124B] - 2019/11/18 @ 20:00
### Aggiunto
- BugFix --> Le unzioni per settare i colori del testo e dello sfondo adesso sono corrette - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/36]

## [v0.1.9a - Daily 124A] - 2019/11/18 @ 08:40
### Cambiamenti
- Fix della funzione di ricerca del testo  - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/34]

## [v0.1.9a - Canary 1249] - 2019/11/18 @ 00:10
### Aggiunto
- Funzione standalone per impostare lo stile dei bottoni grassetto/corsivo/sottolineato
- Funzione standalone per impostare lo stile dei bottoni di allineamento del testo
- Quattro funzioni standalone per l'handling del comportamento dei bottoni di allineamento del testo
- STEP 4 nella funzione del riposizionamento del cursore (set bottoni grassetto/corsivo/sottolineato a seconda della posizione del cursore)
- STEP 5 nella funzione del riposizionamento del cursore (set bottoni di allineamento del testo a seconda della posizione del cursore)
### Cambiamenti
- Adesso i bottoni grassetto/corsivo/sottolineato, quelli per l'allineamento del testo e quello per la DarkMode sono di tipo "checked"
- Riscritte totalmente le funzioni per grassetto/corsivo/sottolineato e quelle per l'allineamento del testo
- Riscritta parte della funzione per la DarkMode

## [v0.1.9a - Nightly 1248] - 2019/11/17 @ 03:00
### Cambiamenti
- Fix dell'inserimento del testo da parte di più client (multiclient)
- Test su multiclient

## [v0.1.9a - Daily 1247] - 2019/11/16 @ 20:00
### Aggiunto
- Aggiunte icone v2 per Grassetto, Corsivo e Sottolineato (DarkMode)
### Cambiamenti
- DarkMode migliorata

## [v0.1.9a - Daily 1246] - 2019/11/16 @ 19:30
### Rimosso
- DebugRoom ufficilamente rimossa
- BugFix generali

## [v0.1.9a - Daily 1245] - 2019/11/16 @ 19:00
### Cambiamenti
- Aggiunte icone v2 per Grassetto, Corsivo e Sottolineato
### Cambiamenti
- Restyling grafico Editor

## [v0.1.9a - Daily 1244] - 2019/11/16 @ 18:30
### Aggiunto
- Funzione per inviare al server la posizione corrente del cursore e del carattere inserito da tastiera
- Funzione per ricevere dal server la tupla "carattere + posizione dove inserire"

## [v0.1.9a - Daily 1243] - 2019/11/16 @ 17:30
### Cambiamenti
- Fix di vari messaggi di dialogo

## [v0.1.9a - Daily 1242] - 2019/11/16 @ 16:30
### Cambiamenti
- BugFix --> Adesso cancellare tutto il testo nel texteditor non resetta il font e la sua dimensione a 0 - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/29]
- La X in MenuWindow chiude nuovamente l'applicazione
### Deprecato
- La DebugRoom "The Lobby" è stata disabilitata.

## [v0.1.9a - Daily 1241] - 2019/11/16 @ 13:20
### Aggiunto
- Creata la funzione che legge il vettore dei simboli dal server

## [v0.1.9a - Daily 1240] - 2019/11/15 @ 22:30
### Cambiamenti
- Fix bottone in MainWindow - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/28]

## [v0.1.9a - Daily 1239] - 2019/11/15 @ 17:00
### Cambiamenti
- BugFix --> Adesso cliccare su un qualsiasi pulsante chiude il Menù File (FileFrame)
- Migliorie alla DarkMode

## [v0.1.9a - Nightly 1238] - 2019/11/14 @ 16:10
### Cambiamenti
- BugFix --> Fix bug minori sulla MenuWindow

## [v0.1.9a - Daily 1237] - 2019/11/14 @ 15:00
### Cambiamenti
- BugFix --> Problemi con il titolo del testo risolti

## [v0.1.9a - Daily 1236] - 2019/11/14 @ 14:00
### Cambiamenti
- BugFix --> La lista dei file degli utenti adesso non viene più ripetuta alla riapertura della pagina - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/18]

## [v0.1.9a - Nightly 1235] - 2019/11/14 @ 02:45
### Cambiamenti
- BugFix --> La selezione di un testo formato da più font non rende più tutto il testo unificato - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/27]
- BugFix --> Adesso il cambio di font senza aver selezionato del testo avviene con successo - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/10]
- Fix --> Rimosso il bottone logout nella pagina openDocPage del MenuWindow - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/25]
- Pulizia del codice dell'EditorWindow ed sistemati alcuni commenti
- Pulizia Changelog e aggiunti link ad issues di github

## [v0.1.9a - Daily 1234] - 2019/11/13 @ 13:15
### Cambiamenti
- Fix Socket - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/22]

## [v0.1.9a - Canary 1233] - 2019/11/13 @ 02:15
- Aggiornamento v0.1.8a --> v0.1.9a
### Cambiamenti
- BugFix --> Il cambio del font del testo selezionato non rende nero il colore di sfondo del testo (per il font del testo non selezionato c'è ancora lavoro da fare)
- Aggiunte tutte le icone necessarie per la Dark Mode - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/23]
- Adesso il testo ha il colore di sfondo di default (cosa molto importante)
- Il fontSelectorBox è stato impostato a Times New Roman come il font di default (ma è da controllare bene).
- Il fontSelectorBox si aggiorna a seconda della posizione del cursore senza alcun problema - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/24]
- Aggiunto lo stile dinamico alla Dark Mode
- Aggiunto la possibilità di ritornare alla Day Mode
- Aggiunto lo stile dinamico alla Day Mode
- Fix del cursore che si sposta nel testo

## [v0.1.8a - Daily 1232] - 2019/11/12
### Cambiamenti
- Molti bug corretti nell'editor
- Il font di default è stato cambiato in Times New Roman

## [v0.1.8a - Daily 1231] - 2019/11/12 @ 18:15
### Cambiamenti
- Aggiornata interfaccia infoProfile
- Aggiornato bottone back e logout in MenuWindow
- Aggiornato testo "Cerca Documento"
- Rimossi bordi smussati nella finestra UserProfile

## [v0.1.8a - Canary 1230] - 2019/11/12 @ 00:15
- Aggiornamento v0.1.7a --> v0.1.8a
### Aggiunto
- Bottone e Funzionalità per la ricerca del testo
- Bottone (in menù di debug) per attivare la "Dark Mode"
- Creata la funzione inversa di lambda1 per poter risalire all'indice data la dimensione del font
- Funzione che al cambio della posizione del cursore aggiorna il Combobox della dimensione del font - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/9]
- Funzione che al cambio della posizione del cursore mi informa del font utilizzato

## [v0.1.7a - Nightly 122F] - 2019/11/11 @ 02:00
### Aggiunto
- La UserProfile mostra il vero nome dell'utente loggato
### Cambiamenti
- Debug Room "The Lobby" aggiornata alla versione v3.
    Alcuni link sono stati disabilitati con un frame trasparente (it's a cool effect!)
- BugFix --> Ripristinati bordi smussati nella finestra UserProfile - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/17]


## [v0.1.7a - Canary 122E] - 2019/11/10 @ 20:30
### Cambiamenti
- BugFix --> Ora Grassetto/Corsivo/Sottolineato funzionano al primo click - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/11]
- Nell'editor, la disconnessione dell'utente è demandata ad una funzione standalone
- Nel MenuWindow, la X in alto disconnette l'utente e poi chiude l'intera applicazione - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/16]

## [v0.1.7a - Daily 122D] - 2019/11/10 @ 18:10
### Cambiamenti
- BugFix --> Ora StartWindow parte correttamente dalla LoginPage - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/21]
- BugFix --> All'apertura di StartWindow il focus della tastiera è sul campo "username" - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/15]

## [v0.1.7a - Daily 122C] - 2019/11/10 @ 15:15
### Cambiamenti
- BugFix --> I form della startwindow ora sono connessi al relativo pulsante accedi/registrati - [https://github.com/giovannic96/Real-time-collaborative-text-editor/issues/7]

## [v0.1.7a - Nightly 122B] - 2019/11/10 @ 04:10
### Cambiamenti
- Piccole correzioni minori
- Aggiornamento e correzione changelog
- Test della connessione tra client e server

## [v0.1.7a - Nightly 122A] - 2019/11/09 @ 00:10
### Cambiamenti
- Grosse correzioni per l'interfacciamento tra client e server
- Merged build

## [v0.1.7a - Nightly 1229] - 2019/11/08 @ 03:10
### Cambiamenti
- Minor Fix
- Apertura di branch per confronto soluzione della Finestra Senza Bordi

## [v0.1.7a - Nightly 1228] - 2019/11/08 @ 00:00
### Aggiunto
- tryOpenFile con URI

## [v0.1.7a - Nightly 1227] - 2019/11/07 @ 22:15
### Cambiamenti
- fix sulla socket

## [v0.1.7a - Daily 1226] - 2019/11/07 @ 16:30
### Aggiunto
- Classe "File"
- altri fix minori

## [v0.1.7a - Canary 1225] - 2019/11/06 @ 4:30
- Aggiornamento v0.1.6 --> v0.1.7
### Aggiunto
- Bottone e funzione per giustificare il testo
- Funzione di chiusura dell'editor nel menu File
- Azioni e relative scorciatoie da tastiera (che non funzionano per qualche bug di Qt?)
### Cambiamenti
- Correzioni delle funzioni di debug
- L'editor cambia da FramelessWindowHint a CustomizeWindowHint
- Riposizionamento bottone e menu di debug dell'editor
- Le funzioni della classe EditorWindow sono state riordinate
- La funzione per rinominare il testo è stata aggiornata
- La funzione per salvare il testo in PDF è stata aggiornata (v1 -> v2)
### Rimosso
- Bottoni di ZoomIn e ZoomOut dell'editor
### Deprecato
- Funzione di salvare il testo in PDF (v1)

## [v0.1.6a - Nightly 1223] - 2019/11/05 @ 18:00
### Aggiunto
- Menù a tendina al click di "file" su editor
### Cambiamenti
- Aggiornamento infoWindow

## [v0.1.6a - Nightly 1222] - 2019/11/05 @ 02:10
### Aggiunto
- Funzioni di test/debug nell'editor

## [v0.1.6a - Nightly 1221] - 2019/11/04 @ 04:00
### Cambiamenti
- BugFix --> Sfondo del testo diventava nero al cambio di font (adesso corretto)
- BugFix --> Dimensione del font non corretto per valore 72 (adesso corretto)
- Sfondo del documento cambiato da #F5F5F5 a #FFFFFF
- I bottoni _ [] X nell'editor hanno adesso la freccia come puntatore al passaggio del mouse (come in Windows) anzichè avere la manina.

## [v0.1.6a - Nightly 1220] - 2019/11/03 @ 17:15
### Aggiunto
- Funzione provvisioria e buggata che determina la dimensione del font a seconda della posizione del cursore
- Assegnazione della dimensione del font anche nel costruttore dell'editor in modo da assegnare un valore iniziale di default.

## [v0.1.6a - Nightly 1219] - 2019/11/03 @ 04:45
### Cambiamenti
- Ottimizzazione funzione per cambiare la dimensione del testo selezionato (tramite funzione lambda)
- Ottimizzazione funzione per cambiare il font del testo selezionato (tramite salvataggio stato su variabili locali)

## [v0.1.6a - Nightly 1218] - NOT RELEASED
### Cambiamenti
- Modifiche alla funzione per cambiare il font del testo selezionato
- Modifiche alla funzione per cambiare la dimensione del testo selezionato

## [v0.1.6a - Nightly 1217] - 2019/11/02 @ 02:00
### Aggiunto
- Funzione per cambiare il font del testo selezionato
- Funzione per cambiare la dimensione del testo selezionato
- "Combobox font" e "Combobox dimensione font"
###Cambiamenti
- Correzione stile dei bottoni

## [v0.1.6a - Daily 1216] - 2019/11/01 @ 19:15
### Aggiunto
- Icona "Salva come PDF"
- Icona "Salva come URI"
- Piccoli cambiamenti grafici nell'editor

## [v0.1.6a - Daily 1215] - 2019/11/01 @ 17:00
### Aggiunto
- Link to infoWindow
- Restyling infoWindow
- infoWindow image
- Debug Room "The Lobby" aggiornata alla versione v2.2. Adesso linka anche a infoWindow
- Correzione di una entry nel Changelog

## [v0.1.6a - Daily 1214] - 2019/11/01 @ 16:15
### Cambiamenti
- Bugfix UI Editor
- Ritorno del focus all'editor di testo al click di un bottone
- Bugfix posizione nome testo nell'editor
- Bugfix stile icone dell'editor

## [v0.1.6a - Canary 1213] - 2019/10/31 @ 18:30
- Aggiornamento v0.1.5 --> v0.1.6
### Cambiamenti
- Restyling grafico Editor
- Aggiornamento icone editor
- Aggiunto stile grafico ai bottoni

## [v0.1.5a - Nightly 1212] - 2019/10/31 @ 17:45
### Aggiunto
- Classe "infoWindow" --> mostrerà l'informazioni sul software in uso
### IMPORTANTE
Richiamare tale classe ha causato un paio di errori. L'ultimo è stato: FTH: (5580): *** Fault tolerant heap shim applied to current process. This is usually due to previous crashes. ***.

## [v0.1.5a - Nightly 1211] - 2019/10/31 @ 09:30
### Aggiunto
- Funzione per ridurre a icona l'editor
- Funzione per minimizzare l'editor
- Tab "View" nell'editor
- Funzione per portare l'editor in "Fullscreen"

## [v0.1.5a - Nightly 1210] - 2019/10/30 @ 03:00
- Aggiornamento v0.1.4 --> v0.1.5
### Cambiamenti
- Funzioni per la modifica del testo riscritte da capo e migliorate notevolmente
- Debug Room "The Lobby" aggiornata alla versione v2.1. Adesso mostra la versione del client
### Aggiunto
- Bottone e funzionalità per evidenziare il testo
- Funzione per sottolineare il testo
- Bottoni e funzioni per aumentare e diminuire il font nell'editor
- Bottone provvisorio per ridurre a icona l'editor
- Bottone provvisorio per minimizzare l'editor
- Serie di icone provvisorie per l'editor

## [v0.1.4a - Nightly 120D] - 2019/10/29 @ 16:15
### Deprecato
- Funzione per rinominare il documento
### Aggiunto
- Nuovo bottone/funzione per rinominare un documento
### Cambiamenti
- Correzione di un bug nella finestra startWindow

## [v0.1.4a - Nightly 120C] - 2019/10/29 @ 02:00
### Aggiunto
- Icona ufficiale dell'applicazione in formato .ico
- Collegamento a "menuWindow" introdotto nella Debug Room
### Cambiamenti
- Correzione di alcune entry nel changelog

## [v0.1.4a - Nightly 120B] - 2019/10/28 @ 03:00
### Aggiunto
- Funzioni differenziate tra exit() e quit() nel menù a tendina e nella barra in alto dell'editor
- Aggiunte icone provvisorie ai bottoni
- Aggiunte alcune shortcut da tastiera azionabili nell'editor
- Aggiunte alcune action nell'editor
### Cambiamenti
- Customizzazione provvisoria della UI dell'editor

## [v0.1.4a - Canary 120A] - 2019/10/27 @ 19:30
### Aggiunto
- Nuova funzione per esportare in PDF
- menuWindow customizzata con bottoni interattivi

## [v0.1.4a - Daily 1206] - 2019/10/27 @ 12:50
### Aggiunto
- Nuova finestra menuWindow al posto del frame per l'accesso
- Funzionalità di testo corsivo
- Bottone e funzionalità per cambiare colore del testo

## [v0.1.4a - Nightly 1205] - 2019/10/27 @ 02:50
### Aggiunto
- Bottone e funzionalità per copiare il testo
- Bottone e funzionalità per tagliare il testo
- Bottone e funzionalità per incollare il testo
- Bottone e funzionalità di redo
- Bottone e funzionalità di undo
- Bottone e funzionalità per allineare il testo a destra
- Bottone e funzionalità per allineare il testo a centro
- Bottone e funzionalità per allineare il testo a sinistra
- Bottone per sottolineare il testo
- Bottone per inclinare il testo

## [v0.1.4a - Nightly 1203] - 2019/10/25 @ 03:10
### Aggiunto
- Bottone per rendere grassetto il testo
### Cambiamenti
- Sostituito booleano del grassetto con opzione checked

## [v0.1.4a - Nightly 1202] - 2019/10/25 @ 03:10
### Aggiunto
- Bottone per rendere grassetto il testo
### Cambiamenti
- Funzionalità grassetto dinamica tramite booleano

## [v0.1.4a - Canary 1201] - 2019/10/23 @ 12:30
### Aggiunto
- Parametro username dopo login
- Funzionalità newfile sincronizzata tra server-side e client-side

## [v0.1.4a - Canary 1200] - 2019/10/20 @ 20:00
### Aggiunto
- Debug Room ("The Lobby") per facilitare il test e il debug del software
- Finestra principale dell'editor di testo
- Area per la videoscrittura
### Cambiamenti
- Aggiornamento e revisione delle funzioni per la gestione dei documenti
- Modifica delle funzioni per rinominare un documento

## [v0.1.4a - Daily 1198] - 2019/10/20 @ 17:30
### Aggiunto
- Funzione per apertuna di un nuovo documento

## [v0.1.4a - Nightly 1197] - 2019/10/20 @ 18:00
### Cambiamenti
- Ottimizzazione dell'interfaccia

## [v0.1.4a - Nightly 1196] - 2019/10/20 @ 02:32
### Cambiamenti
- Half BugFix: Aumentare DPI continua a tagliare i bottoni, ma decrementarli non taglia più la finestra

## [v0.1.4a - Daily 1195] - 2019/10/19 @ 19:00
### Aggiunto
- New File Query
### Cambiamenti
- Ridemnsionamento finestra StartWindow (ingrandita)
- BugFix: permessi sui file .ui

## [v0.1.4a - Daily 1194] - 2019/10/19 @ 18:25
### Cambiamenti
- BugFix: Corretto errore dello sfondo di UserProfile
- BugFix: BorderRadius corretto
- BugFix: Ordine dei Tab dei LineForm corretto
- Arrotondamento dell'immagine della UserProfile

## [v0.1.4a - Daily 1193] - 2019/10/19 @ 17:40
### Cambiamenti
- BugFix: Corretto errore dello sfondo di UserProfile
- BugFix: BorderRadius corretto
- BugFix: Ordine dei Tab dei LineForm corretto
- Arrotondamento dell'immagine della UserProfile

## [v0.1.4a - Daily 1192] - 2019/10/19 @ 16:20
### Cambiamenti
- Aggiornamento interfaccia grafica

## [v0.1.4a - Daily 1191] - 2019/10/19 @ 13:00
### Aggiunto
- Connessione al DB
- Funzionalità di registrazione

## [v0.1.4a - Canary 1190] - 2019/10/18 @ 20:00
### Aggiunto
- Aggiornamento cumulativo v0.1.3a --> v0.1.4a
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
