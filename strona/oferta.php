<?php
	$username="root";
	$password="";
	$database="sklep";
	
	mysql_connect('localhost',$username,$password);
	define('MYSQL_DEF_ENCODE',"latin2");
	mysql_set_charset(MYSQL_DEF_ENCODE);
	@mysql_select_db($database);
	
	$kategoria=mysql_query("SELECT * FROM Kategoria") or die("Brak bazy danych. Strona wisi.");	
	$iloscKategoria=mysql_numrows($kategoria);

	$i=0;
	while ($i < $iloscKategoria) 
	{	 
		while($rowKategoria=mysql_fetch_object($kategoria))
		{
			echo "<dt>$rowKategoria->nazwa</dt>";
			
			$pozycja=mysql_query("SELECT * FROM Towar");
			while($rowPozycja=mysql_fetch_object($pozycja))
			{
				if($rowPozycja->idKategorii == $rowKategoria->id)
				echo "<dd><a href='javascript:wyswietl($rowPozycja->id, \"$rowPozycja->nazwa\", \"$rowPozycja->opis\", $rowPozycja->cena, $rowPozycja->ilosc, $rowPozycja->vat)'>$rowPozycja->nazwa</a></dd>";
			}						
		}	
		$i++;
	}
 	mysql_close();
?>

<HTML>
<HEAD>
<META HTTP-EQUIV="Content-type" CONTENT="text/html; charset=iso-8859-2">
</HEAD>
<BODY>
</BODY>
</HTML>