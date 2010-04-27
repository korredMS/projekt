<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
  "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="pl">
<head>
  <meta http-equiv="Content-type" content="application/xhtml+xml; charset=iso-8859-2" />
  <meta name="Description" content=" OSIV " />
  <meta name="Keywords" content=" [wstaw tu slowa kluczowe] " />
  <meta name="Author" content=" id 6.4 " />
  <meta name="Generator" content="kED" />

  <title> OSIV </title>
	<script type="text/javascript" src="menu.js"></script>
  <link rel="stylesheet" href="default.css" type="text/css" />
	<link rel="stylesheet" href="menu.css" type="text/css" />
</head>
<body>

<!-- naglowek -->

<div id="logo">
	<a href="index.html"><img src="images/logo.jpg" alt="" /></a>
</div>	

<div id="page">

	<!-- menu -->
	<div id="sidebar0" class="sidebar">
		<ul>
			<li>
				<h2><a id="glowna" href="index.php">STRONA GŁÓWNA</a></h2>
			</li>			
			<li>
				<h2>OFERTA</h2>
				<ul>										
					<dl id="menu0">
						<?php
							include 'oferta.php';									
						?>
					</dl>		
					
					<script type="text/javascript">
					// <![CDATA[
					new Menu('menu0');
					// ]]>
					</script>										
				</ul>
			</li>					
		</ul>
	</div>
	
	<!-- srodek-->
	<div id="content">
		<div id="kostka"><center><img src="images/kostka.jpg" alt="" width="500" height="250" /></center></div>
		<div class="post">
			<h1 class="title"><center>Witamy na stronie firmy <strong>OSIV</strong>!</center></h1>
			<div class="entry">
				<p><center>Zachęcamy do zapoznania się z naszą ofertą.</center></p>				
			</div>
		</div>
	</div>
	
	<!-- menu -->
	<div id="sidebar1" class="sidebar">
		<ul>
			<li>
				<h2>INFORMACJE</h2>
			</li>
			
			<ul>										
					<dl id="menu1">
						<dt><a onMouseOver="link()" href="javascript:info(0)">O FIRMIE</a></dt>
						<dt><a href="javascript:info(1)">JAK DOJECHAĆ</a></dt>
						<dt><a href="javascript:info(2)">KONTKAKT</a></dt>
					</dl>							
					
				</ul>
				
		</ul>
	</div>
	
	<div style="clear: both;">&nbsp;</div>
</div>
	
<div id="stopka">
	OSIV <br />
	Jan Kowalsky <br />
	01-132 Lublin <br />
	ul. Nadbystrzycka 32
</div>
	
<div id="footer">	
	<p class="copyright">&copy;&nbsp;&nbsp;ID 6.4A, 2010 &nbsp;&bull;&nbsp; </p>
</div>

</body>
</html>
