# README #

# Opis krok po kroku jak wygląda algorytm.

## krok 1.
	
- krok 1 metody wegeirskiej.
	- jeśli w wierszach nie ma po 1 zerze, znaleść minimum w każdej kolumnie i odjąć od całego wiersza minimum
- krok 2 metody wegierskiej.
	- to samo co 1 krok metody węgierskiej, tylko robimy to dla kolumn, znajdujemy minimum dla każdej kolumny;
- wyznaczamy ograniczenie dolne
	- dodajemy do siebie wszystkie minima w wierszach i kolumnach;

## krok 2.
	
- Po kolei dla każdego zera ij. patrzymy na wiersz i kolumne w którym zero się znajduje.
Znajdujemy minimum w tym wiersu "i" i kolumnie "j" i dodajemy te 2 wartości minimalne do siebie.
```
  A B C
A|0 2 3| - zero w 1 wierszu i 1 kolumnie, minima to "2" dla wiersza i "0" dla kolumny, liczy się zero w 3 wierszu. 
B|3 0 4| - zero w 2 wierszu i 2 kolumnie, min dla wiersza: "3", dla kolumny: "2" 
C|0 5 2| - zero w 3 wierszu i 1 kolumnie, min dla wiersza: "2", dla kolumny: "0"
tylko przykład
```
- Robimy to dla każdego zera ale nie bierzemy pod uwagę samego zera na przecieciu.
- teraz gdy mamy te wartości, sumujemy je dla każdego zera:
```
[1,1] = 2 + 0 = 2
[2,2] = 3 + 2 = 5
[3,1] = 2 + 0 = 2
```
- wyznaczamy max z wyliczonych liczb, czyli tutaj max{2,5,2} = 5.
- wyliczamy 2 ograniczenie dodając nasze max do ograniczenia dolnego,mamy teraz ograniczenie i ograniczenie z *.

## krok 3.

- tworzymy graf/drzewo, pierwszy element 0 ma w sobie ograniczenie, nie ma on oznaczenia.
- dokładamy kolejne 2 elementy, jeden z ograniczeniem* i drugi z normalnym ograniczeniem.
- w tej tablicy bez gwiazdki usuwamy kolumne i wiersz gdzie bylo max 5. Cos takiego:
```
  A C
A|0 3| - mamy taka tablice
C|0 2| 
	- elementy grafu oznaczamy nwierszem i kolumna tablicy ktora usunelismy np:

XX	- pierwszy element
|  \
CA*  CA	- element z * i element bez * bez kolumny i wiersza
```

## krok 4

- powtarzamy wszystko to samo od poczatku dla tej pomniejszonej tablicy i dopisujemy kolejne elementy grafu

## krok 5

- kiedy tablica ma rozmiar 2x2 i mamy w niej zera, jak w książce to dopisujemy do grafu te elementy które zostały - (STOP)
```
  A C
A|9 0| - nastepny nowy element to AC a potem CA w tym przypadku.
C|0 9| 
```
## krok 6

- Jeżeli nie ma takiej macierzy 2 x 2 to sprawdzamy który wcześniejszy element grafu ma mniejsze ograniczenie. Jeżeli ten z * to w tym miejscu(wiersz i kolumna) wstawiamy nieskonczonosc i zapętlamy do 1 kroku.
- jeżeli mniejsze ograniczenie ma to bez *, to zapetlamy do kroku 2.
	
