Joc: Snake

Hardware folosit:
-Arduino Uno
-Matrice 8x8
-LCD display
-driver MAX7219
-Joystick
-3 breadboard-uri

Am folosit o structura de puncte in care memorez coordonatele x si y ale unui punct pentru o aprindere cat mai usoara si o intelegere mai usoara a codului.
Modul in care functioneaza jocul este unul simplist, fara pereti sau alte lucruri in special, ci pur si simplu un joc simplu de snake ce are in plus niste tier-uri predefinite, pentru a da jocului un sentiment de end goal.
Dificultatea jocului consta in faptul ca pe masura ce creste nivelul ( pe masura ce jucatorul face un scor din ce in ce mai mare) snake-ul va creste in lungime si de asemenea va creste si viteza jocului.
Jocul porneste cu input de la player (da click pe joystick). La sfarsitul jocului se vor afisa pe lcd scorul, tier-ul si dupa se va da optiunea de a reveni in meniu ( de a reincepe un nou joc).
Player-ul vede scorul pe parcursul jocului, acesta fiind updatat in timp real pe LCD.
Am folosit delay in program, deoarece snake-ul nu are nevoie de o cronometrare speciala si nu conteaza daca fac pauza la intregul program. De asemenea, acest lucru face, in opinia mea , comenzile sa fie mai precise.
Codul are comentarii minime, intrucat consider ca acesta este codat in asa fel incat se poate intelege destul de usor la ce foloseste fiecare variabila si functie.