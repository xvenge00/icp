# Projekt na ICP 2k18

| Autori | Meno         | Login    | Email                      |
|--------+--------------+----------+----------------------------|
|        | Matej Kastak | xkasta02 | xkasta02@stud.fit.vutbr.cz |
|        | Adam Venger  | xvenge00 | xvenge00@stud.fit.vurbr.cz |

## Moznosti programu

### Editovanie schemy

Je mozne hybat s blokmi ktore su vlozene do schemy.
Schema je identifikovana menom suboru do ktoreho bude ulozena.
Program umoznuje pridavane u odoberanie blokov pomocou tlacitka v lavom hornom toolbare.
Prepojenia medzi blokmi sa vytvaraju v poradi blok s vystupom a blok so vstupom.

### Editovanie konstantnych blokov

Konstantne bloky je mozne editovat pomocou dvojiteho kliknutia na dany blok.

### Krokovanie

Krokovanie je mozne az po staceni tlacika reset(vpravo od tlacidla krokovania), ktore pripravi
danu schemu na krokovanie. Tymto tlacidlom je mozne aj resetnutie(vymazanie) vsetkych hodnot suboru.

## Preklad(Make)

### debug

Prelozenie programu s debugovacimi vypismy. Tie su vypisane na stderr a su obsiahnute vo vyslednej binarke
len v pripade prelozenia tohto cielu.

### merlin

Odosle potrebne subory a prelozi na skolskom servery merlin(merlin.fit.vutbr.cz) a nasledne vytvori shell, z
ktoreho je mozne projekt spustit. Ako pouzivatel bude vybrany obsah premennej AUTHOR.

### eva

Podobne ako ciel merlin, ale server prekladu je eva(eva.fit.vutbr.cz)

### pack

Vytvori archiv podla pokynov pre odovzdanie.

### format

Naformatuje codebase podla dohodnutych pravidiel.
