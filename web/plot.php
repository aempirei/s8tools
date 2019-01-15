<?php
header("Pragma: no-cache");
$samples = 12115;
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
height="100"
viewbox="0 -64 <?= $samples ?> 128" preserveAspectRatio="none"
>
<rect height="100%" width="100%" fill="whitesmoke" />
<rect height="256" y="-128" width="50%" fill="RGBA(255,0,0,0.25)" id='hl' />
<path d="M 0 0 L <?= $samples ?> 0" stroke="#f00" stroke-width="1" />
<?php

function mkticks($min,$max,$step) {
	$ticks = '';
	for($i = min; $i < $max; $i += $step)
		if($i % ($step * 10) != 0)
			$ticks .= sprintf("M %d -128 l 0 256 ", $i);
	return $ticks;
}

$vticks = '';

for($i = -128; $i < 128; $i += 16)
	$vticks .= sprintf("M 0 %d l $samples 0 ", $i);

$ticks1 = mkticks(0,$samples,80);
$ticks2 = mkticks(0,$samples,800);
$ticks3 = mkticks(0,$samples,8000);

?>
<path d="<?= $vticks ?>" stroke="#a88" stroke-width="1" />
<path d="<?= $ticks1 ?>" stroke="#a88" stroke-width="1" />
<path d="<?= $ticks2 ?>" stroke="#000" stroke-width="1" />
<path d="<?= $ticks3 ?>" stroke="#f00" stroke-width="1" />
<g stroke="blue" stroke-width="1" fill="none">
        <?php include "./envelope.txt" ?>
</g>
<g stroke="red" stroke-width="1" fill="none">
        <?php include "./waveform.txt" ?>
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
