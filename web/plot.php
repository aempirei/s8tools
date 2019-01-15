<?php
header("Pragma: no-cache");
?>
<html><head>
<style>
#hl {
	visibility: hidden;
};
</style>
</head><body>
<svg id='s' xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink"
width="1280"
height="100"
viewbox="0 -64 10240 128" preserveAspectRatio="none"
>
<rect height="100%" width="100%" fill="whitesmoke" />
<rect height="256" y="-128" width="50%" fill="RGBA(255,0,0,0.25)" id='hl' />
<path d="M 0 0 L 10240 0" stroke="grey" stroke-width="1" />
<?php

$ticks='';

for($i = 0; $i < 10240; $i += 160)
	$ticks .= sprintf("M %d -128 l 0 256 ", $i);

for($i = -128; $i < 128; $i += 16)
	$ticks .= sprintf("M 0 %d l 10240 0 ", $i);

?>
<path d="<?= $ticks ?>" stroke="grey" stroke-width="1" />
<g stroke="blue" stroke-width="1" fill="none">
        <?php include "./envelope.txt" ?>
</g>
<g stroke="red" stroke-width="1" fill="none">
        <?php include "./waveform.txt" ?>
</g>
</svg>
<div id='pp'>
</div>
<script>
var pos = [];
var isactive = false;
function toSample(n) {
	return Math.round(10240 * n / 1280);
}
function updatePos(e) {
	if(isactive) {
		pos[1] = e.offsetX;
		hl.style.width = toSample(pos[1] - pos[0]);
	}
	pp.innerHTML = '#' + toSample(e.offsetX);
};
s.onmouseover = updatePos;
s.onmouseup = function(e) {
	isactive=false;
	pos[1] = e.offsetX;
	hl.style.width = toSample(pos[1] - pos[0]);
};
s.onmousedown = function(e) {
	hl.style.visibility = 'visible';
	pos[0] = pos[1] = e.offsetX;
	hl.style.x = toSample(pos[0]);
	hl.style.width = toSample(pos[1] - pos[0]);
};

</script>
</body></html>
