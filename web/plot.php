<?php
header("Pragma: no-cache");
?>
<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink"
width="1280"
height="100"
viewbox="0 -128 1280 256" preserveAspectRatio="none"
>
<rect height="100%" width="100%" fill="whitesmoke" />
<path d="M 0 0 L 1280 0" stroke="grey" stroke-width="1" />
<g stroke="blue" stroke-width="1" fill="none" transform="translate(54,0)">
        <?php include "./envelope.txt" ?>
</g>
<g stroke="red" stroke-width="1" fill="none">
        <?php include "./waveform.txt" ?>
</g>
</svg>
