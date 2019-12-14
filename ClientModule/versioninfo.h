//  CLASS VersionInfo
#pragma once
#include <QString>

//Class StartMenu --> This class handle and provide information of the current version of this software
class VersionInfo{
private:
    int Major;
    int Minor;
    int Patch;
    QString ReleaseType;
    QString BuildTypeAndNumber;
    QString str;
public:
    //CONSTRUCTOR WITHOUT PARAMETER (Default)
    VersionInfo(): Major(0), Minor(2), Patch(0), ReleaseType("a"), BuildTypeAndNumber("Daily 1280"){
        str = "v"+QString::number(Major)+"."+QString::number(Minor)+"."+QString::number(Patch)+ReleaseType+" - "+BuildTypeAndNumber;
    }

    //INLINE MEMBER FUNCTION
    int getMajor(){return Major;}
    int getMinor(){return Minor;}
    int getPatch(){return Patch;}
    QString getVersion(){return str;}

};


/*HS***************NOTE*****************
The software version is indicated by the American convention instead of SemVer (Semantic Version) therefore the resulting string follow the four digit scheme.

The version is in the "vA.B.CD - E F" form, where:
 - A is "Major Version" (or Major Number)
 - B is "Minor Version" (or Minor Number)
 - C is "Patch Version" (or Release Number)
 - D is "Release Type"
 - E is "Build Type"
 - F is "Build Number"

 - D can be one of this following symbol
 + 'a' stand for "Alpha Version"         -->  Software in development stage, functions not fully implemented / have bug to fix
 + 'b' stand for  "Beta"                 -->  Software tested in group
 + 'rc' stand for "Release Candidate"    -->  Semi-definitive version, candidate for final version
 + nothing/empty when is finished

 - E può essere
 + Nightly Build    --> Build released every night.
 + Daily Build      --> Build released when is necessary to another developer in the same day
 + Canary Build     --> Build stable, function finished and new feature fully implemented. If the Nightly/Daily is broken, this is the recovery point.
 + Vanilla Build    --> Build almost completed, not customized
 + nothing/empty when is finished

 - F is progressive number/letter format

Have some question? Follow the link.
http://www.computersemplice.it/i-numeri-di-versione-del-software/
https://softwareengineering.stackexchange.com/questions/55946/release-build-vs-nightly-build
https://it.wikipedia.org/wiki/Versione_alfa
https://it.wikipedia.org/wiki/Versione_beta
https://it.wikipedia.org/wiki/Release_candidate
https://en.wikipedia.org/wiki/Vanilla_software
https://en.wikipedia.org/wiki/Daily_build
*/
