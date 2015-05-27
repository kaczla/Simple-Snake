## Simple Snake: Client and Server

#### Testowane na:

Ubuntu 15.04

g++ (Ubuntu 4.9.2-10ubuntu13) 4.9.2


### Klient:

**Budowanie:**

Zbudować poleceniem **make** w katalogu **client**.

**Uruchomienie:**

Do uruchomienia programu wymagany jest *adres docelowy serwera* oraz *port na którym nasłuchuje*.

Dla *localhost* wystarczy wpisać 0.

np. ./client.out 0 8765

**Komendy** (wszystkie polecenia należy zatwierdzić klawiszem **ENTER**):

**w** - poruszanie się w górę

**s** - poruszanie się w dół

**a** - poruszanie się w lewo

**d** - poruszanie się w prawo

**Q** - wyjście

**n** - nowa gra

### Serwer:

**Budowanie:**

Zbudować poleceniem **make** w katalogu **server**.

**Uruchomienie:**

Do uruchomienia programu wymagany jest *port na którym będzie nasłuchiwał serwer*.

Dla *localhost* wystarczy wpisać 0.

np. ./server.out 8765
