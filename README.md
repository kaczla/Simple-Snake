## Simple Snake: Client and Server

### Opis:

Klient + Serwer prostej gry Snake.
</br>
Stworzone w 2015 roku.
</br>
</br>

#### Testowane na:

Ubuntu 15.04
</br>
g++ (Ubuntu 4.9.2-10ubuntu13) 4.9.2
</br>
</br>

### Klient:

**Budowanie:**
</br>
Zbudować poleceniem **make** w katalogu **client**.
</br>
</br>

**Uruchomienie:**
</br>
Do uruchomienia programu wymagany jest *adres docelowy serwera* oraz *port na którym nasłuchuje*.
</br>
Dla *localhost* wystarczy wpisać 0.
</br>
np. ./client.out 0 8765
</br>
</br>

**Komendy** (wszystkie polecenia należy zatwierdzić klawiszem **ENTER**):
</br>
**w** - poruszanie się w górę
</br>
**s** - poruszanie się w dół
</br>
**a** - poruszanie się w lewo
</br>
**d** - poruszanie się w prawo
</br>
**Q** - wyjście
</br>
**n** - nowa gra
</br>
</br>

### Serwer:

**Budowanie:**
</br>
Zbudować poleceniem **make** w katalogu **server**.
</br>
</br>

**Uruchomienie:**
</br>
Do uruchomienia programu wymagany jest *port na którym będzie nasłuchiwał serwer*.
</br>
Dla *localhost* wystarczy wpisać 0.
</br>
np. ./server.out 8765
</br>
</br>
