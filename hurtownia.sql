SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

# zmienione kodowanie na UTF-8
# zmienione atrybuty: `vat`, `regon`

CREATE TABLE IF NOT EXISTS `Sklep` (
  `id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `regon` varchar(9) NOT NULL,
  `nazwa` varchar(30) NOT NULL,
  `upust` float DEFAULT NULL,
  `login` varchar(12) NOT NULL,
  `haslo` varchar(20) NOT NULL,
  `ulica` varchar(30) NOT NULL,
  `miejscowosc` varchar(20) NOT NULL,
  `kodPocztowy` varchar(5) NOT NULL,
  `telefon` varchar(9) NOT NULL,
  `fax` varchar(9) DEFAULT NULL,
  `email` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

CREATE TABLE IF NOT EXISTS `Towar` (
  `id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(50) NOT NULL,
  `opis` varchar(150) DEFAULT NULL,
  `cena` float NOT NULL,
  `ilosc` int(11) NOT NULL,
  `vat` enum('0','3','7','14','22') NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

CREATE TABLE IF NOT EXISTS `Zamowienie` (
  `id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `idSklepu` int(8) unsigned NOT NULL,
  `dataZlozenia` date NOT NULL,
  `dataRealizacji` date DEFAULT NULL,
  `upust` float DEFAULT NULL,
  `status` enum('oczekujace','anulowane','zrealizowane') NOT NULL,
  `nrFaktury` varchar(8) DEFAULT NULL,
  PRIMARY KEY (`id`),
  FOREIGN KEY (idSklepu) REFERENCES Sklep(id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;


CREATE TABLE IF NOT EXISTS `Pozycja_zamowienia` (
  `id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `idZamowienia` int(8) unsigned NOT NULL,
  `idTowaru` int(8) unsigned NOT NULL,
  `ilosc` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  FOREIGN KEY (idZamowienia) REFERENCES Zamowienie(id),
  FOREIGN KEY (idTowaru) REFERENCES Towar(id)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;
