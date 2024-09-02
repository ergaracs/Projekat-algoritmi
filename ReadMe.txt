Projekat Hamiltonov ciklus i MST

Cilj projekta je da se napravi kružna mapa gde će se implementirati 
algoritmi za proveru postojanja minimalnog razapinjućeg stabla i Hamiltonovog ciklusa


Struktura Koda
Cvor: Struktura koja predstavlja čvor u grafu, sa atributima za vrh, težinu i pokazivač na sledeći
	čvor u listi povezanosti.
Graf: Struktura koja predstavlja graf, sa brojem vrhova i listom pokazivača na čvorove.
Grana: Struktura koja predstavlja granu u grafu, sa izvorom, ciljem i težinom.
Opis Funkcija
1. Cvor *kreirajCvor(int v, int tezina)
Funkcija kreira novi čvor za graf sa zadatim vrhom i težinom. I vraća novi čvor.

2. Graf *kreirajGraf(int vrhovi)
Funkcija kreira novi graf sa zadatim brojem vrhova. I vraća pokazivač grafa.

3. void dodajGrana(Graf *graf, int izvor, int cilj, int tezina)
Funkcija dodaje novu granu između dva čvora u grafu.

Ovaj projekat implementira Kruskalov algoritam za pronalaženje
Minimalnog Razapinjajućeg Stabla (MST) u neusmerenim, težinskim grafovima.
Funkcije uključene u implementaciju:

uporediIvice: Funkcija za poređenje dve grane po težini,
koristi se za sortiranje grana pre pokretanja Kruskalovog algoritma.

nadji: Funkcija za pronalaženje roditelja čvora u 
Union-Find strukturi, koristi se za detekciju ciklusa.

unija: Funkcija za spajanje dva podskupa u Union-Find 
strukturi, koristi se za održavanje podataka o komponentama grafa.

KruskalMST: Glavna funkcija koja implementira Kruskalov 
algoritam. Sortira grane po težini, a zatim dodaje grane 
u MST koristeći Union-Find strukturu, sve dok ne dobije minimalno razapinjajuće stablo.

Kruskalov algoritam koristi pohlepni pristup (greedy) i 
efikasno pronalazi MST sortirajući grane i dodajući najlakše grane koje ne formiraju ciklus.

Implementacija algoritma za pronalaženje Hamiltonovog ciklusa u 
grafu koristi backtracking tehniku.

Funkcije uključene u implementaciju:
jeBezbedno: Pomoćna funkcija koja proverava da li je bezbedno dodati 
	čvor u trenutnu putanju. Funkcija osigurava da postoji veza između
	trenutnog čvora i novog čvora, i da novi čvor još nije korišćen u putanji.

hamCiklusUtil: Rekurzivna funkcija koja pokušava da izgradi Hamiltonov 
	ciklus dodavanjem čvorova u putanju. Kada se posete svi čvorovi, proverava 
	se da li poslednji čvor povezuje sa prvim, čime se formira ciklus.

hamCiklus: Glavna funkcija koja inicijalizuje putanju i pokreće rekurzivnu 
	pretragu za Hamiltonovim ciklusom. Ako ciklus postoji, ispisuje se redosled 
	čvorova koji čine ciklus.

Ovaj algoritam koristi backtracking za sistematsko ispitivanje svih mogućih 
putanja kroz graf, u pokušaju da pronađe Hamiltonov ciklus.

generisi: Ova funkcija je pomoćna funkcija koja omogućava dodavanje 
	grane u graf i ažuriranje liste grana. Ova funkcija je korisna kada 
	je potrebno čuvati podatke o svim granama u posebnom nizu radi
	daljeg procesiranja ili analize.

Strahinja Ergarac 2014-2021
Aleksa Semenjuk 2047-2021