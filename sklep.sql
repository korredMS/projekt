SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

CREATE TABLE IF NOT EXISTS `Faktura` (
  `idFaktury` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `nrFaktury` varchar(8) NOT NULL,
  PRIMARY KEY (`idFaktury`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

CREATE TABLE IF NOT EXISTS `Hurtownia` (
  `idHurtowni` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `REGON` varchar(9) NOT NULL,
  `upust` float DEFAULT NULL,
  `ulica` varchar(30) NOT NULL,
  `miejscowosc` varchar(20) NOT NULL,
  `kodPocztowy` varchar(5) NOT NULL,
  `telefon` varchar(9) NOT NULL,
  `fax` varchar(9) DEFAULT NULL,
  `email` varchar(30) DEFAULT NULL,
  `nazwa` varchar(30) NOT NULL,
  PRIMARY KEY (`idHurtowni`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;


CREATE TABLE IF NOT EXISTS `Kategoria` (
  `idKategorii`  int(8) unsigned NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(50) NOT NULL,
  PRIMARY KEY (`idKategorii`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `Klient` (
  `idKlienta` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `REGON` varchar(9) NOT NULL,
  `ulica` varchar(30) NOT NULL,
  `miejscowosc` varchar(20) NOT NULL,
  `kodPocztowy` varchar(5) NOT NULL,
  `telefon` varchar(9) NOT NULL,
  `nazwa` varchar(30) NOT NULL,
  PRIMARY KEY (`idKlienta`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `Pracownik` (
  `idPracownika`  int(8) unsigned NOT NULL AUTO_INCREMENT,
  `nazwisko` varchar(40) NOT NULL,
  `PESEL` varchar(11) NOT NULL,
  `NIP` varchar(10) NOT NULL,
  `posada` enum('Kierownik','Sprzedawca','Magazynier') DEFAULT NULL,
  `dataZatrudnienia` date NOT NULL,
  `stawka` float NOT NULL,
  `ulica` varchar(30) NOT NULL,
  `miejscowosc` varchar(20) NOT NULL,
  `kodPocztowy` varchar(5) NOT NULL,
  `telefon` varchar(9) NOT NULL,
  `email` varchar(30) NOT NULL,
  `login` varchar(20) NOT NULL,
  `haslo` varchar(20) NOT NULL,
  PRIMARY KEY (`idPracownika`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `Towar` (
  `idTowaru`  int(8) unsigned NOT NULL AUTO_INCREMENT,
  `Nazwa` varchar(50) NOT NULL,
  `opis` varchar(150) DEFAULT NULL,
  `cena` float NOT NULL,
  `ilosc` int(11) NOT NULL,
  `idKategorii` int(8) unsigned NOT NULL,
  FOREIGN KEY (idKategorii) REFERENCES Kategoria(idKategorii),
  `stawkaVAT` enum('0','3','7','14','22') NOT NULL,
  `cenaZakupu` float NOT NULL,
  PRIMARY KEY (`idTowaru`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `Sprzedaz` (
  `idSprzedazy`  int(8) unsigned NOT NULL AUTO_INCREMENT,
  `dataRealizacji` date DEFAULT NULL,
  `status` enum('oczekujace','anulowane','zrealizowane') NOT NULL,
  `potwierdzenie` enum('paragon','faktura') NOT NULL,
  `nrParagonu` varchar(8) NOT NULL,
  `idFaktury` int(8) unsigned DEFAULT NULL,
  `idKlienta` int(8) unsigned DEFAULT NULL,
  `idPracownika` int(8) unsigned NOT NULL,
  FOREIGN KEY (idPracownika) REFERENCES Pracownik(idPracownika),
  FOREIGN KEY (idKlienta) REFERENCES Klient(idKlienta),
  FOREIGN KEY (idFaktury) REFERENCES Faktura(idFaktury),
  PRIMARY KEY (`idSprzedazy`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `Zamowienie` (
  `idZamowienia` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `idHurtowni` int(8) unsigned NOT NULL,
  `dataZlozenia` date NOT NULL,
  `dataRealizacji` date DEFAULT NULL,
  `status` enum('oczekujace','anulowane','zrealizowane') NOT NULL,
  `nrFaktury` varchar(8) DEFAULT NULL,
  `idPracownika` int(8) unsigned NOT NULL,
  FOREIGN KEY (idPracownika) REFERENCES Pracownik(idPracownika),
  FOREIGN KEY (idHurtowni) REFERENCES Hurtownia(idHurtowni),
  PRIMARY KEY (`idZamowienia`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `Pozycja_sprzedazy` (
  `idPozycjiSprzedazy` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `idSprzedazy` int(8) unsigned NOT NULL,
  FOREIGN KEY (idSprzedazy) REFERENCES Sprzedaz(idSprzedazy),
  `idTowaru` int(8) unsigned NOT NULL,
  FOREIGN KEY (idTowaru) REFERENCES Towar(idTowaru),
  `ilosc` int(11) NOT NULL,
  `cena` float NOT NULL,
  `stawkaVAT` enum('0','3','7','14','22') NOT NULL,
  PRIMARY KEY (`idPozycjiSprzedazy`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `Pozycja_zamowienia` (
  `idPozycjiZamowienia` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `idZamowienia` int(8) unsigned NOT NULL,
  FOREIGN KEY (idZamowienia) REFERENCES Zamowienie(idZamowienia),
  `idTowaru` int(8) unsigned NOT NULL,
  FOREIGN KEY (idTowaru) REFERENCES Towar(idTowaru),
  `ilosc` int(11) NOT NULL,
  PRIMARY KEY (`idPozycjiZamowienia`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;
