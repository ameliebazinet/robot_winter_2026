# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes

Identification:

+ Travail    : Épreuve finale
+ Section #  : 2
+ Équipe #   : 2728
+ Correcteur : Laurent Bourgon

# LISIBILITÉ

## En-têtes en début de programme

| Pénalité par erreur                       | -1.5          |
| ----------------------------------------- | ------------- |
| Noms des auteurs                          |               |
| Description du programme                  |               |
| Identifications matérielles (Broches I/O) |               |
| Table des états ou autres s'il y a lieu   |               |
| __Résultat partiel__                      | __(1.5/1.5)__ |

## Identificateurs significatifs (Autodocumentation)

| Points importants                       | Poids         |
| --------------------------------------- | ------------- |
| Absence de *chiffres magiques*          | (0.0/0.5)     |
| Noms de variables décrivent l'intention | (0.3/0.5)     |
| Noms de fonctions décrivent l'intention | (0.5/0.5)     |
| __Résultat partiel__                    | __(0.8/1.5)__ |

+ (-0.5) : Beaucoup de nombres magiques dans `modes/execution.cpp`, `modes/instruction.cpp` et `modes/rapport.cpp`.

+ (-0.1) : Évitez d'appeler vos variables avec des abbréviations (comme `l`, `cl`, `ci`).
+ (-0.1) : Les noms de constantes `DELAI_1_SECONDE` ou `DELAI_2_SECONDES` ne sont pas significatifs. Choisissez à la place des noms qui décrivent l'intention/l'utilisation de la constante (comme `DELAI_CLIGNOTEMENT_AMBRE`).

## Commentaires pertinents

Bonnes raisons d'un commentaire

+ Explication d'un algorithme
+ Procédure peu évidente (ou *hack*)
+ Référence d'extraits de code copiés d'Internet
+ Détail du POURQUOI d'un extrait de code

| Pénalité par erreur  | -0.5          |
| -------------------- | ------------- |
| __Résultat partiel__ | __(0.0/1.0)__ |

+ (-0.5) : Commentaires dans `ecrireDepuisUART` (`ecriture.cpp`). Utilisez à la place des fonctions (qui pourraient être privées) comme `uint16_t obtenirTailleMessage` pour éviter d'avoir à expliquer ce que fait le code.
+ (-0.5) : Code mort dans `CapteurLigne.cpp`.

## Indentation

| Points importants                      | Poids         |
| -------------------------------------- | ------------- |
| Indentation structurée                 | (0.5/0.5)     |
| Indentation uniforme dans le programme | (0.5/0.5)     |
| __Résultat partiel__                   | __(1.0/1.0)__ |

# MODULARITÉ ET COMPRÉHENSION

## Fonctions bien définies

| Pénalité par erreur                  | -0.5          |
| ------------------------------------ | ------------- |
| Responsabilité unique d'une fonction |               |
| Maximum de 4 paramètres              |               |
| Absence de code dupliqué             |               |
| etc                                  |               |
| __Résultat partiel__                 | __(0.5/1.0)__ |

+ (-0.5) : Vous avez beaucoup de fonctions qui prennent beaucoup (6+) de paramètres (`faireExecution`, `sauvegarderRapport`, `lireRapport`, `genererRapport`).
  De plus, c'est généralement les mêmes paramètres. Il aurait été préférable de regrouper ces paramètres dans une structure (comme `struct DonneesRapport`)
  pour éviter d'avoir à passer autant de paramètres à vos fonctions (et éviter une erreur possible de passer les paramètres dans le mauvais ordre).

## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0          |
| -------------------------------------------- | ------------- |
| Utilisation appropriée des registres         |               |
| Machine à états codée clairement             |               |
| Délais et minuteries utilisés judicieusement |               |
| PWM bien établi                              |               |
| Scrutation et interruptions bien utilisées   |               |
| etc                                          |               |
| __Résultat partiel__                         | __(3.5/4.0)__ |

+ (-0.5) : Vous accédez à votre librairie avec la syntaxe `"../../lib/Communication.hpp"` dans vos fichiers de `app`.
  De plus, le Makefile de celui-ci inclut déjà le chemin vers la librairie (`-I../lib`), donc vous auriez pu simplement faire `#include <Communication.hpp>`.

# FONCTIONNALITÉS

## Git

| Points importants            | Poids         |
| ---------------------------- | ------------- |
| Fichiers aux bons endroits   | (1.5/1.5)     |
| Absence de fichiers inutiles | (1.5/1.5)     |
| __Résultat partiel__         | __(3.0/3.0)__ |

## Compilation

| Points importants                            | Poids         |
| -------------------------------------------- | ------------- |
| Absence de messages d'erreurs de compilation | (1.5/1.5)     |
| Absence de messages d'attention (*warning*)  | (0.0/0.5)     |
| __Résultat partiel__                         | __(1.5/2.0)__ |

+ (-0.5) : Warnings lors de la compilation de `app`.

## Évaluation boîte noire

| Points importants            | Poids         |
| ---------------------------- | ------------- |
| Cas normal de fonctionnement | (2.5/2.5)     |
| Cas limites observables      | (2.5/2.5)     |
| __Résultat partiel__         | __(5.0/5.0)__ |

# Résultat

__Total des points: 16.8/20__

# Basé sur le commit suivant

```
commit a412b435b067d7722ab31e22b86367dc8180a5c1
Author: ameliebazinet <amelie.bazinet2@gmail.com>
Date:   Mon Apr 20 13:28:46 2026 -0400

    Push final
```

# Fichiers indésirables pertinents

Aucun

# Tous les fichiers indésirables

Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `projet/lib`

```
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c can.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c CapteurInfra.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c CapteurLigne.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c Communication.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c Del.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c InterruptionExterne.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c memoire_24.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c Minuterie.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c PontH.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c Son.cpp
avr-ar rcs libstatique.a can.o CapteurInfra.o CapteurLigne.o Communication.o Del.o InterruptionExterne.o memoire_24.o Minuterie.o PontH.o Son.o
```

## Sortie de `make` dans `projet/app`

```
avr-gcc -I. -I../lib -MMD -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c main.cpp -o main.o
avr-gcc -I. -I../lib -MMD -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c modes/execution.cpp -o modes/execution.o
avr-gcc -I. -I../lib -MMD -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c modes/instruction.cpp -o modes/instruction.o
avr-gcc -I. -I../lib -MMD -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c modes/rapport.cpp -o modes/rapport.o
avr-gcc -I. -I../lib -MMD -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c lecture/lecture.cpp -o lecture/lecture.o
In file included from lecture/lecture.cpp:9:
lecture/lecture.hpp: In constructor 'Lecture::Lecture()':
lecture/lecture.hpp:68:9: warning: 'Lecture::del_' will be initialized after [-Wreorder]
   68 |     Del del_;
      |         ^~~~
lecture/lecture.hpp:64:10: warning:   'bool Lecture::programmeFini_' [-Wreorder]
   64 |     bool programmeFini_;
      |          ^~~~~~~~~~~~~~
lecture/lecture.cpp:15:1: warning:   when initialized here [-Wreorder]
   15 | Lecture::Lecture() : adresse_(0x0000), donnee_(0), instruction_(0b00),
      | ^~~~~~~
lecture/lecture.cpp: In member function 'void Lecture::lireMemoire()':
lecture/lecture.cpp:111:10: warning: unused variable 'estDebutTrouve' [-Wunused-variable]
  111 |     bool estDebutTrouve = false;
      |          ^~~~~~~~~~~~~~
avr-gcc -I. -I../lib -MMD -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c ecriture/ecriture.cpp -o ecriture/ecriture.o
avr-gcc -Wl,-Map,main.elf.map -mmcu=atmega324pa -o main.elf main.o modes/execution.o modes/instruction.o modes/rapport.o lecture/lecture.o ecriture/ecriture.o ../lib/libstatique.a -lm
avr-objcopy -j .text -j .data -O ihex main.elf main.hex
```
