# tema1-SDA

Aceasta este implementarea mea pentru Tema 1. Am ales sa modularizez cat mai 
mult codul pentru o mai usoara citire a codului, o mai buna organizare, si
pentru a lucra intr-un mediu mai curat. Prin aceasta tehnica am reusit sa impart
fiecare parte a codului cu metodele si structurile de date aferente lui.

Tema mi s-a parut usoara, ar fi fost mai distractiv sa fie putin mai challenging.
Functia search a fost cea mai interesanta si am abordat-o astfel: am decis sa caut prima
litera din cuvant pentru a decide daca e posibil sa avem cuvantul cautat in lista, daca
prima litera nu exista in lista inseamna ca nu exista acel cuvant in lista, altfel,
voi cauta in continuare litera cu litera inca strlen(cuvant) - 1 litere deoarece pe prima
am gasit-o. Aici am avut primul bug din program deoarece eu daca aveam match la 3/4 liere sa zicem,
dar nu ajungeam inca la mecanic programul meu imi marca cuvantul drept negasit fara a mai cauta
pana la mecanic, deci ca sa rezolv acest bug am decis sa marchez toata cautarea de la prima litera
cu un 'retry' mark astfel incat cand nu gasesc un potential cuvant si nu am ajuns nici la
mecanic sa reincep cautarea.
Aceeasi abrodare a fost si pentru search-left/right.

Restul metodelor sunt chestii de baza cu lucrul de liste, nu cred ca e nevoie sa intru in detaliu.

Overall tema mi s-a parut draguta insa mi-ar fi placut sa aiba o dificultate mult mai mare,
poate pe viitor se va tine cont de acest aspect.