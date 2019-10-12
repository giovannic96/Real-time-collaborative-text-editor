#1 Passi preliminari
1) Aggiungere alla variabile d'ambiente PATH la stringa "C:\Qt\Qt5.13.1\Tools\mingw730_64\bin" senza apici
2) Ordinarla come prima rispetto alle altre stringhe

#2 Installazione
1) Clicca qui --> https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.7z
2) Estrailo su D:\Download\
3) Apri CMD in modalità amministratore
4) Scrivi --> D:
5) Scrivi --> cd Download\boost_1_66_0\tools\build (o era solo boost_1_66_0 ?????)
6) Scrivi --> bootstrap.bat gcc
7) Aspetta che compaia "adesso lancia b2... ecc..."
8) Scrivi --> b2 install --prefix="D:\Boost" toolset=gcc
9) Scrivi --> cd .. 
10) ripeti (9) fino ad arrivare alla cartella Download\boost_1_66_0
11) Scrivi --> b2 install --prefix="D:\Boost" toolset=gcc link=shared threading=multi variant=release --without-mpi address-model=64 architecture=x86

#3 Risultato
Hai due cartelle:
1) D:\Boost --> contiene 3 cartelle (bin, boost, share)
2) C:\Boost --> contiene 2 cartelle (include, lib)

#4 Continua con la guida di Giovanni

#5 Note:
1 - Ho qualche dubbio sulla cartella dove lanciare il comando e sui parametri
2 - Il passo (11) potrebbe non contenere "install"
