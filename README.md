Qt-pohjainen shakkipeli, jossa toteutettu nappuloiden perusliikkeet.  
Peli toimii graafisessa käyttöliittymässä (Qt), ja pelaajat tekevät siirtoja klikkaamalla nappuloita ja ruutuja.

## Ominaisuudet
- Kaikkien nappuloiden normaalit siirrot toteutettu (kuningas, kuningatar, torni, lähetti, ratsu, sotilas).
- Käyttöliittymä Qt:n avulla: lauta 8x8, värit ja nappuloiden ikonit.
- Pelaajat vuorottelevat automaattisesti (valkoinen–musta).
- Pelin vuoro korostaa lailliset siirrot valitulle nappulalle.

## Rajoitukset
Tässä versiossa **ei ole toteutettu**:
- shakki- ja mattitarkistusta (peli päättyy kun kuningas syödään)
- linnoitusta
- en passant -sääntöä
- sotilaan promootiota

## Käyttöohjeet
- Käynnistä peli Qt Creatorista.
- Klikkaa nappulaa → sen lailliset siirrot korostetaan sinisellä.
- Klikkaa korostettua ruutua → nappula siirtyy.
- Jos valitset oman nappulan uudestaan, valinta perutaan.
- Peli jatkuu, kunnes toinen kuningas syödään.

## Kääntäminen ja ajaminen
1. Avaa projekti Qt Creatorissa ('.pro'-tiedosto tai 'CMakeLists.txt').
2. Paina **Run** (tai 'Ctrl+R' / 'Cmd+R').

Tekijä: Tiina Salmi
Kurssi: COMP.CS.115, Tampereen yliopisto
Päivämäärä: 6.4.2025
