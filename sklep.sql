SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

# zmienione kodowanie na UTF-8
# zmienione atrybuty: `vat`, `nazwa` (tylko w 'Towar'), `regon`, `pesel`, `nip`

CREATE TABLE IF NOT EXISTS `Faktura` (
  `id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `nrFaktury` varchar(8) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

CREATE TABLE IF NOT EXISTS `Hurtownia` (
  `id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `regon` varchar(9) NOT NULL,
  `upust` float DEFAULT NULL,
  `ulica` varchar(30) NOT NULL,
  `miejscowosc` varchar(20) NOT NULL,
  `kodPocztowy` varchar(5) NOT NULL,
  `telefon` varchar(9) NOT NULL,
  `fax` varchar(9) DEFAULT NULL,
  `email` varchar(30) DEFAULT NULL,
  `nazwa` varchar(30) NOT NULL,
  `login` varchar(20) NOT NULL,
  `haslo` varchar(20) NOT NULL,
  `host` varchar(30) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;


CREATE TABLE IF NOT EXISTS `Kategoria` (
  `id`  int(8) unsigned NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(50) NOT NULL,
  PRIMARY KEY (`id`)

) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Kategoria` (`id`, `nazwa`) VALUES
(1, 'Art. spożywcze'),
(2, 'Sprzęt'),
(3, 'Broń');

CREATE TABLE IF NOT EXISTS `Klient` (
  `id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `regon` varchar(9) NOT NULL,
  `ulica` varchar(30) NOT NULL,
  `miejscowosc` varchar(20) NOT NULL,
  `kodPocztowy` varchar(5) NOT NULL,
  `telefon` varchar(9) NOT NULL,
  `nazwa` varchar(30) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `Pracownik` (
  `id`  int(8) unsigned NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(25) NOT NULL,
  `pesel` varchar(11) NOT NULL,
  `nip` varchar(10) NOT NULL,
  `posada` enum('Kierownik','Sprzedawca','Magazynier') NOT NULL,
  `dataZatrudnienia` date NOT NULL,
  `stawka` float NOT NULL,
  `ulica` varchar(30) NOT NULL,
  `miejscowosc` varchar(20) NOT NULL,
  `kodPocztowy` varchar(5) NOT NULL,
  `telefon` varchar(9) NOT NULL,
  `email` varchar(30) NOT NULL,
  `haslo` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `Towar` (
  `id`  int(8) unsigned NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(50) NOT NULL,
  `opis` varchar(150) DEFAULT NULL,
  `cena` float NOT NULL,
  `ilosc` int(11) NOT NULL,
  `idKategorii` int(8) unsigned NOT NULL,
  FOREIGN KEY (idKategorii) REFERENCES Kategoria(id),
  `vat` enum('0','3','7','14','22') NOT NULL,
  `cenaZakupu` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `Towar` (`id`, `Nazwa`, `opis`, `cena`, `ilosc`, `idKategorii`, `vat`, `cenaZakupu`) VALUES
(1, 'Wódka', '0.5L', '22.45', '66', '1', '7' , '22.45'),
(2, 'Ogórki', '1L', '5', '10', '1', '22' , '5'),
(3, 'Myszka', 'Logitech', '69.50', '8', '2', '22' , '69.50'),
(4, 'Klawiatura', 'Genius', '30.15', '12', '2', '22', '30.15'),
(5, 'Glośniki', 'Microlab', '399', '3', '2', '14', '399'),
(6, 'Wiatrówka', 'Ceska Zbrojovka', '459', '2', '3', '0', '459');

CREATE TABLE IF NOT EXISTS `Sprzedaz` (
  `id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `dataRealizacji` date DEFAULT NULL,
  `status` enum('oczekujace','anulowane','zrealizowane') NOT NULL,
  `potwierdzenie` enum('paragon','faktura') NOT NULL,
  `nrParagonu` varchar(8) NOT NULL,
  `idFaktury` int(8) unsigned DEFAULT NULL,
  `idKlienta` int(8) unsigned DEFAULT NULL,
  `idPracownika` int(8) unsigned NOT NULL,
  FOREIGN KEY (idPracownika) REFERENCES Pracownik(id),
  FOREIGN KEY (idKlienta) REFERENCES Klient(id),
  FOREIGN KEY (idFaktury) REFERENCES Faktura(id),
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `Zamowienie` (
  `id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `idHurtowni` int(8) unsigned NOT NULL,
  `dataZlozenia` date NOT NULL,
  `dataRealizacji` date DEFAULT NULL,
  `status` enum('oczekujace','anulowane','zrealizowane') NOT NULL,
  `nrFaktury` varchar(8) DEFAULT NULL,
  `idPracownika` int(8) unsigned NOT NULL,
  FOREIGN KEY (idPracownika) REFERENCES Pracownik(id),
  FOREIGN KEY (idHurtowni) REFERENCES Hurtownia(id),
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `Pozycja_sprzedazy` (
  `id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `idSprzedazy` int(8) unsigned NOT NULL,
  FOREIGN KEY (idSprzedazy) REFERENCES Sprzedaz(id),
  `idTowaru` int(8) unsigned NOT NULL,
  FOREIGN KEY (idTowaru) REFERENCES Towar(id),
  `ilosc` int(11) NOT NULL,
  `cena` float NOT NULL,
  `vat` enum('0','3','7','14','22') NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `Pozycja_zamowienia` (
  `id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `idZamowienia` int(8) unsigned NOT NULL,
  FOREIGN KEY (idZamowienia) REFERENCES Zamowienie(id),
  `idTowaru` int(8) unsigned NOT NULL,
  FOREIGN KEY (idTowaru) REFERENCES Towar(id),
  `ilosc` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;
