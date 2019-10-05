//  CLASSE LoginWindow - v 0.1.1a
//  LastEdit = 2019/10/05 @ 17:00

#pragma once
#include <QString>

/*HS************Classe VersionInfo*******************************************
* Questa classe contiene le informazioni sulla versione del software sviluppato
* Per maggiori informazioni vedere note in fondo
*****************************************************************************/
class VersionInfo{
private:
    int Major;
    int Minor;
    int Patch;
    QString ReleaseType; //a=Alpha - b=Beta - rc=ReleaseCandidate ' '=Vanilla/Milestone
    QString BuildTypeAndNumber;
    QString str;
public:
    //Costruttore senza parametri (di default)
    VersionInfo(): Major(0), Minor(1), Patch(1), ReleaseType("a"), BuildTypeAndNumber("Daily 1031"){
        str= "v"+QString::number(Major)+"."+QString::number(Minor)+"."+QString::number(Patch)+ReleaseType+" - "+BuildTypeAndNumber;
    }

    //Funzioni membro inline
    int getMajor(){return Major;}
    int getMinor(){return Minor;}
    int getPatch(){return Patch;}
    QString getVersion(){return str;}

};


/*HS***************NOTE*****************
La versione del software è scritta secondo la convenzione angloamericana, anzichè la SemVer (Semantic Version)
pertanto la stringa risultante segue lo schema a quattro numeri.
Spiego la convenzione in sintesi,

La stringa è nel formato "vA.B.CD - E F" dove:
 - A è la "Major Version" (o Major Number)      --> aumenta in seguito a cambiamenti radicali del software
 - B è la "Minor Version" (o Minor Number)      --> aumenta con l'introduzione di grosse funzionalità
 - C è la "Patch Version" (o Release Number)    --> aumenta con l'introduzione di piccoli cambiamenti e funzionalità
 - D è il "Release Type"                        --> Indica il tipo di release del software
 - E è il "Build Type"                          --> Indica il tipo di Build
 - F è il "Build Number"                        --> Indica il numero di Build

 - D può assumere 4 valori (a, b, rc o 'niente')
 + a indica "Alpha" -->  Software in fase di sviluppo, le cui funzionalità non sono ancora state completamente implementate / presenta bug da risolvere
 + b indica "Beta"  -->  Software non definitvo ma testato in gruppo
 + rc indica "Release Candidate" --> "versione quasi definitiva, candidata ad essere pronta per il rilascio"
 + niente si usa quando si arriva al rilascio finale

 - E può essere
 + Nightly Build    --> Build rilasciata con cadenza quasi serale, nelle tarde ore della notte.
 + Daily Build      --> Come la precedente, ma rilasciata per essere modificata da un altro sviluppatore (possibilmente nello stesso giorno)
 + Canary Build     --> Build rilasciata quasi settimanalmente, di solito porta a compimento le feature introdotte
 + Vanilla Build    --> Build quasi completa, a rilascio anticipato, senza customizzazioni
 + vuoto

 - F è il numero di Build progressivo

Per maggiori informazioni, visionare i seguenti link
http://www.computersemplice.it/i-numeri-di-versione-del-software/
https://softwareengineering.stackexchange.com/questions/55946/release-build-vs-nightly-build
https://it.wikipedia.org/wiki/Versione_alfa
https://it.wikipedia.org/wiki/Versione_beta
https://it.wikipedia.org/wiki/Release_candidate
https://en.wikipedia.org/wiki/Vanilla_software
https://en.wikipedia.org/wiki/Daily_build
*/
