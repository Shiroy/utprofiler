<?php

$f = fopen("UV_UTC.txt", "r");

while(!feof($f))
{
	$code = stream_get_line($f, 10000, "\r\n");
	$name = stream_get_line($f, 10000, "\r\n");
	$credit = stream_get_line($f, 10000, "\r\n");
	$cat = stream_get_line($f, 10000, "\r\n");
	
	echo "\t<uv>\n".
	"\t\t<code>$code</code>\n".
	"\t\t<nom>$name</nom>\n".
	"\t\t<credit type=\"$cat\">$credit</credit>\n".
	"\t\t<branche>Unk</branche>\n".
	"\t</uv>\n";
}
	