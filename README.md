# Przekształcanie drzew BST.

 **Opis programu:**
 Program tworzy 2 drzewa BST, a następnie przechodzi po nich jednocześnie DFSem wykrywając występujące w nich różnice i obiczając liczbę koniecznych operacji do ich zniwelowania.
 
  **Struktury danych:**
Ze względu na duży rozmiar danych wejściowych zdecydowałem się na rozwiązanie korzystające z dynamicznie alokowanych struktur danych i smart pointerów. Dostępna jest struktura Node reprezentująca węzeł drzewa oraz klasa Tree udostępniająca na niej operacje.

  **Złożoność:**
Ze względu na brak restrukturyzacji drzewa podczas insertów złożonośC programu w wersji pesymistycznej jest kwadratowa od liczby węzłów (np. dla danych ściśle rosnących). W przypadku otrzymania zbudowanych drzew jako wejścia do naszego programu, jego złożoność jest liniowa w zależności od liczby węzłów drzew.

   **Proces rozwiązania:**
Na początku zaimplementowałem wersję rekurencyjną operacji na grafie. (commit recursive implementation), która działą dla nie bardzo dużych danych.
Podczas testów wykryłem jednak problemy z pamięcią, ze względu na zbyt dużą głębokość rekursji (podczas testów warto ustawić ją w opjach kompilatora na maksymalną).
Zacząłem zmieniać moje rozwiązanie, na iteracyjne, jednak nie udało mi się dokończyć tego w wyznaczonym czasie - do rozwiązania z commitu iterative add and count należy dodać iteracyjną wersję size oraz je przetestować.

 **Uwagi:**
 1.Przyjąłem, że dodawanie wartości, która już znajduje się w drzewie nie zmienia zawartości drzewa.
 2.Zdecydowałem się na umieszczenie rozwiązania na githubie ze względu na możliwość obejrzenia 2 rozwiązanie: rekurencyjnego i iteracyjnego (niedokończonego).


