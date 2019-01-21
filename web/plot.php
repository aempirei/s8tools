<?php
header("Pragma: no-cache");
$samples = 5000;
?>
<html><head>
<style>
div#pp {
font-family: monospace;
}
div.content {
display: block;
padding: 0.25in;
text-align:center;
}
#hl {
	visibility: hidden;
};
</style>
</head><body>
<div class='content'>
<svg id='s' xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink"
width="1280"
height="500"
viewbox="0 -128 <?= $samples ?> 520" preserveAspectRatio="none"
>
<rect height="100%" y="-128" fill="RGBA(255,0,0,0.25)" id='hl' />
<?php

function mkticks($min,$max,$step,$tick_sz) {
	$s = sprintf("M %d %d l %d %d", $min, -$tick_sz, 0, 2 * $tick_sz);
	for($i = min; $i < $max; $i += $step)
		$s .= sprintf(" m %d %d l 0 %d", $step, -2 * $tick_sz, 2 * $tick_sz);
	return $s;
}


function vkticks($min,$max,$xstep,$ystep,$tick_sz) {
	$s = '';
	for($i = -128; $i < 128; $i += $ystep)
		for($j = $min; $j < $max; $j += $xstep)
			$s .= sprintf("M %d %d l %d 0", $j - $tick_sz, $i, 2 * $tick_sz);
	return $s;
}

?>
<g>
	<path d="M 0 0 L <?= $samples ?> 0" stroke="#f00" stroke-width="1" />
	<path d="<?= vkticks(0,$samples,400,25.5,16) ?>" stroke="#a88" stroke-width="1" />
	<path d="<?= mkticks(0,$samples,40,8) ?>" stroke="#a88" stroke-width="1" />
	<path d="<?= mkticks(0,$samples,400,128) ?>" stroke="#000" stroke-width="1" />

	<g stroke="red" stroke-width="1" fill="none"><?php include "./r1.txt" ?></g>
	<g stroke="green" stroke-width="2" fill="none"><?php include "./g1.txt" ?></g>
	<g stroke="blue" stroke-width="1" fill="none"><?php include "./b1.txt" ?></g>
</g>

<g transform="translate(0 264)">
	<path d="M 0 0 L <?= $samples ?> 0" stroke="#f00" stroke-width="1" />
	<path d="<?= vkticks(0,$samples,400,25.5,16) ?>" stroke="#a88" stroke-width="1" />
	<path d="<?= mkticks(0,$samples,40,8) ?>" stroke="#a88" stroke-width="1" />
	<path d="<?= mkticks(0,$samples,400,128) ?>" stroke="#000" stroke-width="1" />

	<g stroke="red" stroke-width="1" fill="none"><?php include "./r2.txt" ?></g>
	<g stroke="green" stroke-width="2" fill="none"><?php include "./g2.txt" ?></g>
	<g stroke="blue" stroke-width="1" fill="none"><?php include "./b2.txt" ?></g>
</g>
</svg>
</div>
<div id='pp'>
</div>
<script>
var pos = {
	x1: 0,
	x2: 0,
	x: function() { return Math.min(this.x1,this.x2); },
	w: function() { return Math.abs(this.x1-this.x2); },

};
var isactive = false;
function toSample(n) {
	return Math.round(<?= $samples ?> * n / s.clientWidth);
}
function updateStatus(e) {
	pp.innerHTML = '';
	pp.innerHTML += '[' + (isactive ? '*' : ' ') + '] ';
	pp.innerHTML += '#' + toSample(e.offsetX) + ' ';
	pp.innerHTML += '[' + toSample(pos.x()) + ',' + toSample(pos.x()+pos.w()) + ']';
};
function updatePos(e) {
	if(isactive) {
		pos.x2 = e.offsetX;
		hl.style.x = toSample(pos.x());
		hl.style.width = toSample(pos.w());
	}
};
function updateAll(e) {
	updatePos(e);
	updateStatus(e);
};
s.onmousemove = updateAll;
s.onmouseup = function(e) {
	isactive = false;
	updateAll(e);
};
s.onmousedown = function(e) {
	hl.style.visibility = 'visible';
	pos.x1 = e.offsetX;
	isactive = true;
	updateAll(e);
};

</script>
</body></html>
