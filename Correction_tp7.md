# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes

Identification:
+ Travail    : Mise en commun du code et formation de librairies
+ Section #  : 2
+ Équipe #   : 2728
+ Correcteur : Tristan Rioux

# CODE

| Points importants                                        | Poids       |
| -------------------------------------------------------- | ----------- |
| La qualités et le choix de vos portions de code choisies | (4.0/5.0)      |
| La qualités de vos modifications aux Makefiles           | (4.0/5.0)      |
| __Résultat partiel__                                     | __(8.0/10.0)__ |

# RAPPORT

| Points importants                                                           | Poids      |
| --------------------------------------------------------------------------- | ---------- |
| Explications cohérentes par rapport au code retenu pour former la librairie | (1.6/2.0)     |
| Explications cohérentes par rapport aux Makefiles modifiés                  | (1.8/2.0)     |
| Explications claires avec un bon niveau de détails                          | (1.0/2.0)     |
| Bon français                                                                | (1.0/1.0)     |
| __Résultat partiel__                                                        | __(5.4/7.0)__ |

# GÉNÉRALITÉS
## Bonne soumission de l'ensemble du code et du rapport selon le format demandé

| Pénalité par erreur      | -0.5       |
| ------------------------ | ---------- |
| compilation sans erreurs |            |
| etc                      |            |
| __Résultat partiel__     | __(3.0/3.0)__ |


# Résultat

__Total des points: 16.4/20__

# Commentaires du correcteur :

## Code:

- Pas de code de debounce ou de scrutation de bouton.

### Communication:
- Active la réception sans avoir de fonction de réception

### Del:
- `allumerCouleur`, utiliser un switch-case pour ce genre de comparaison, surtout
  lorsque la variable est un enum

### InterruptionExterne:
- `changerDetectionInterruption` n'est pas utile
- `estActiveeBroche` n'est pas en rapport au interruption

### Minuterie:
- Aligner les énoncés ensembles dans la déclaration de enum
- Les classes ne devraient pas être static, ce n'est pas pertinent
- Manque un peu de cohérence entre les 3 classes avec `partirPWM`
- `Minuterie0::partirPWM` ne fonctionne pas comme prévu, on passe un % à `activerComparateurA`
- Il serait pratique d'avoir une méthode pour changer les % sans avoir à reconfigurer toujours

### PontH:
- Les classes ne devraient pas être static, ce n'est pas pertinent
- Ne devrait pas utiliser des `int` pour configurer qui demande des `bool` en paramètre
- Commentaire `Avance/Recule` inutile, modifier le code à la place pour le rendre plus
  explicite (par exemple en ajoutant une variable `bool` pour la condition)


## Makefile:

### Exec:
- Devrait inclure la librairie avec `-l` plutôt que directement comme objet
- Ne devrait pas avoir `-B 10` comme argument à `avrdude`

### Lib:
- `AVRDUDE_PROGRAMMERID`, `HEXFORMAT` inutilisés


## Rapport:

- Une classe n'est pas une librairie, mais plutôt une partie de celle-ci
- Beaucoup de répétitions inutiles: contient deux fichiers... C'est normal
  en C++, pas besoin d'en parler

### Can:
- Le can n'est pas relié au microcontroleur, il est intégré
- N'est pas assez spécifique pour la contrainte du port A
- Ne parle pas du retour sur 10bits

### Communication:
- Pas assez explicite que toutes les méthodes de transmission sont bloquantes

### Debug:
- "activée par le debug du Makefile", pas assez précis: "par la commande `debug` dans le Makefile"
- Pas besoin de reparler des caractéristiques du usart, seulement dire qu'il l'utilise est suffisant

### Del:
- Couleur n'est pas une classe, c'est un enum
- Ne spécifie pas qu'il faut appeler `allumerCouleurAmbre` dans une boucle pour que la couleur
  soit visible
  
### InterruptionExterne:
- `interruptionEnAttente()` n'existe pas
- `estEnAttente` n'est pas une méthode de scrutation, utiliser PINx pour déterminer ça
  (ou bien `estActiveeBroche`, dont on ne parle pas malheureusement)
- `effacerFlag` devrait être utilisé à la fin des ISR correspondant

### Memoire24:
- Ne spécifie pas que l'écriture de 1 octet doit avoir un délais entre les écritures
- Ne spécifie pas le domaine des paramètres
- Va trop dans les détails d'implémentations inutilement

### Minuterie:
- Manque de justification quant au design des 3 classes
- Va un peu trop dans les détails d'implémentation
- Ne parle pas de la limitation de `activerComparateurA/B`
- "Ces méthodes permettent de déclencher les routines d’interruption (ISR)", lesquelles?
- Pourquoi pas `partirPWM` dans `Minuterie1`?
- Pourquoi seulement `Minuterie2` désactive les interruptions?
- Ne spécifie pas les broches obligatoires pour le fonctionnement de la classe

### PontH:
- Manque de cohérence dans le rapport avec `tournerDroite`/`tournerGauche`

### Makefile:
- Incohérence entre le code et le rapport: retrait des règles pour les .c dans la lib
- Ne parle pas de comment le `make debug` fonctionne (relation makefile vs code)



# Basé sur le commit suivant
```
commit 2f8ccb7abe1db0137dc1a103b03953c795e58deb
Author: Félix Tétreault <felix-2.tetreault@etud.polymtl.ca>
Date:   Mon Mar 16 00:40:08 2026 -0400

    ok LA c'est fini
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp7/lib`
```
make: Entering directory '/home/tristan/Documents/Poly/inf1900/inf1900-grader-H2026/correction_tp7/2728/tp/tp7/lib'
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c can.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c Communication.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c Del.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c InterruptionExterne.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c memoire_24.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c Minuterie.cpp
avr-gcc -MMD -I. -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall --param=min-pagesize=0 -fno-exceptions -c PontH.cpp
avr-ar rcs libstatique.a can.o Communication.o Del.o InterruptionExterne.o memoire_24.o Minuterie.o PontH.o
make: Leaving directory '/home/tristan/Documents/Poly/inf1900/inf1900-grader-H2026/correction_tp7/2728/tp/tp7/lib'

```

## Sortie de `make` dans `tp/tp7/exec`
```
make: Entering directory '/home/tristan/Documents/Poly/inf1900/inf1900-grader-H2026/correction_tp7/2728/tp/tp7/exec'
avr-gcc -I. -I../lib -MMD -g -mmcu=atmega324pa -Os -std=c++14 -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c main.cpp -o main.o
avr-gcc -Wl,-Map,main.elf.map -mmcu=atmega324pa -o main.elf main.o ../lib/libstatique.a -lm
avr-objcopy -j .text -j .data -O ihex main.elf main.hex
make: Leaving directory '/home/tristan/Documents/Poly/inf1900/inf1900-grader-H2026/correction_tp7/2728/tp/tp7/exec'

```
