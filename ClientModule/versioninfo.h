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
    VersionInfo(): Major(0), Minor(1), Patch(3), ReleaseType("a"), BuildTypeAndNumber("Nightly 1180"){
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

Man, I know is hard and is a boring work that take time, but this instruction is so clear and can really help if we done constantly upgrade and update to this project.
Imagine that all the stuff implemented is f****d up, I mean, we can recovery from a stable version, or maybe we can take the functionality individually implemented
in a Nightly and paste on a Canary, or take a customization and apply to a vanilla! Is a function done, and we never touch it again? Well, put a 'rc' and we are
sure that the project is working fine enaugh! I know you're going to hate me, but trust me, you will hate most your future boss than me, and this bad version thing
can help you to be "not-fired"! Trust me, i'm an Engineer! (and this comment will end in "The HOF of comment" someday!)

Have some question? Follow the link.
http://www.computersemplice.it/i-numeri-di-versione-del-software/
https://softwareengineering.stackexchange.com/questions/55946/release-build-vs-nightly-build
https://it.wikipedia.org/wiki/Versione_alfa
https://it.wikipedia.org/wiki/Versione_beta
https://it.wikipedia.org/wiki/Release_candidate
https://en.wikipedia.org/wiki/Vanilla_software
https://en.wikipedia.org/wiki/Daily_build
*/
