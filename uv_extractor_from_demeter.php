<?php

function loadUv($branche, &$ra, &$rp)
{
	$ra = array();
	$rp = array();
	
	$rawDataA = file_get_contents("uv_".$branche."_a.html");
	$rawDataP = file_get_contents("uv_".$branche."_p.html");

	preg_match_all("#<span class=\"(CS|TM)\".*>([A-Z][A-Z0-9]*)<\/span>#", $rawDataA, $resultA);
	//var_dump($resultA);
	preg_match_all("#<span class=\"(CS|TM)\".*>([A-Z][A-Z0-9]*)<\/span>#", $rawDataP, $resultP);

	$ra = $resultA[2];
	$rp = $resultP[2];
}

function makeUvRule($uv, $a, $p, &$bA, &$bP)
{
	$ret = false;
	if(in_array($uv, $a))
	{
		$bA = true;
		$ret = true;
	}
	if(in_array($uv, $p))
	{
		$bP = true;
		$ret = true;
	}
	
	return $ret;
}

loadUv("tc", $tcA, $tcP);
loadUv("hutech", $hutechA, $hutechP);
loadUv("gi", $giA, $giP);
//var_dump($giA);
loadUv("gm", $gmA, $gmP);
loadUv("gsm", $gsmA, $gsmP);
loadUv("gp", $gpA, $gpP);
loadUv("gsu", $gsuA, $gsuP);

$uvXml = new DomDocument();
$uvXml->load("donne_test.xml");

$allUv = $uvXml->getElementsByTagName("uv");

foreach($allUv as $uv)
{
	$branche = array();
	$automne = false;
	$printemps = false;
	foreach($uv->childNodes as $child)
	{
		if($child->nodeName == "code")
		{
			$code = $child->nodeValue;
			
			if(makeUvRule($code, $tcA, $tcP, $automne, $printemps))
				$branche[] = "TC";
			if(makeUvRule($code, $hutechA, $hutechP, $automne, $printemps))
				$branche[] = "HUTECH";
			if(makeUvRule($code, $giA, $giP, $automne, $printemps))
				$branche[] = "GI";
			if(makeUvRule($code, $gmA, $gmP, $automne, $printemps))
				$branche[] = "GM";
			if(makeUvRule($code, $gsmA, $gsmP, $automne, $printemps))
				$branche[] = "GSM";
			if(makeUvRule($code, $gpA, $gpP, $automne, $printemps))
				$branche[] = "GP";
			if(makeUvRule($code, $gsuA, $gsuP, $automne, $printemps))
				$branche[] = "GSU";
		}
		
		if($child->nodeName == "branche")
		{
			$uv->removeChild($child);
		}
	}
	
	foreach($branche as $br)
	{
		$brElem = $uvXml->createElement("branche", $br);
		$uv->appendChild($brElem);
	}
	
	if($automne)
		$uv->appendChild($uvXml->createElement("automne"));
	if($printemps)
		$uv->appendChild($uvXml->createElement("printemps"));
}

$uvXml->normalizeDocument();

echo $uvXml->saveXml();

?>
