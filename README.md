snake_server

## Přeložení:
Překlad se provádí pomocí nástroje Cmake
1. Vygenerování Cmake cache příkazem: "cmake ./"
2. Sestavení přojektu: "make"

## Spuštění:
Server se spouští standartním způsobem pro konkrétní platformu.
 - Windows: spuštění exe souboru snake_server.exe
 - Linux: spuštění binárního souboru "./snake_server"

## Argumenty programu:
 - port: Číslo portu, na kterém bude server poslouchat. Parametr je povinný.
 - players: Maximální počet hráčů v jedné hře. Parametr je povinný. Není implementováno
 - width/w: Šířka herní mapy. Parametr je nepovinný. Výchozí hodnota je 600.
 - height/h: Výška herní mapy. parametr je nepovinný. Výchozí hodnota je 600.
 
## Konzole serveru:
Není implementováno.
Pro bezpečné ukončení serveru se zmáčkne libovolné číslo a potvrdí Enterem. (dočasné řešení)

## Přenosový protokol:
Identifikátor a obsah jsou odděleny znakem: ":". 
Obsah pokud potřebuje rozdělit, tak je rozdělen znakem: "|"
Každé "dato" musí být ukončeno ukončovacím znakem: ";"

identifikátor | obsah
------------- | -----
login | username
logout | -
changedir | x\|y

Příklad přihlašování: login:stechy1;
Příklad změny směru: changedir:-0.2675|0.5672;
Příklad odhlášení: logout;