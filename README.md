snake_server

## Přeložení:
Překlad se provádí pomocí nástroje Cmake
 1. Vygenerování Cmake cache příkazem: "cmake ./"
 2. Sestavení projektu: "make"

## Spuštění:
Server se spouští standartním způsobem pro konkrétní platformu.
 - Windows: spuštění exe souboru snake_server.exe
 - Linux: spuštění binárního souboru "./snake_server"
 
Výchozí číslo portu: 10000

## Argumenty programu:
Zatím jsou všechny parametry nastavené natvrdo. 
 - port: Číslo portu, na kterém bude server poslouchat. Parametr je povinný.
 - players: Maximální počet hráčů v jedné hře. Parametr je povinný. Není implementováno
 - width/w: Šířka herní mapy. Parametr je nepovinný. Výchozí hodnota je 800.
 - height/h: Výška herní mapy. parametr je nepovinný. Výchozí hodnota je 600.
 
## Konzole serveru:
Není implementováno.
Pro bezpečné ukončení serveru se zmáčkne libovolné číslo a potvrdí Enterem. (dočasné řešení)

## Přenosový protokol:
 - Identifikátor a obsah jsou odděleny znakem: ":"
 - Obsah pokud potřebuje rozdělit, tak je rozdělen znakem: "|"
 - Každé "dato" musí být ukončeno ukončovacím znakem: ";"

identifikátor | obsah | typ
------------- | ----- | -----
login | username | input
logout | - | input
changedir | x&#124;y | input
init | init:{[UID&#124;X&#124;Y&#124;X&#124;Y]}size:{[W&#124;H]}players:{[UID&#124;X&#124;Y&#124;X&#124;Y],[UID&#124;X&#124;Y&#124;X&#124;Y]...}food:{[X&#124;Y],[X&#124;Y]...}; | output
addsnake | uid&#124;pos_x&#124;pos_y&#124;dir_x&#124;dir_y | output
remsnake | uid | output
changedir | uid&#124;dir_x&#124;dir_y | output

 - Příklad přihlašování: login:stechy1;
 - Příklad změny směru: changedir:-0.2675|0.5672;
 - Příklad odhlášení: logout;
