#!/usr/bin/env php
<?php
header("Content-Type: text/plain");

// Get frame from query string
parse_str($_SERVER["QUERY_STRING"], $params);
$frame = isset($params["frame"]) ? intval($params["frame"]) : 0;

// Grid size
$width = 30;
$height = 10;
$snake_length = 5;
$y = 4;

// Calculate snake head X position
$head_x = $frame % ($width - $snake_length);

// Initialize empty grid
$grid = array_fill(0, $height, str_repeat(" ", $width));

// Draw snake
for ($i = 0; $i < $snake_length; $i++) {
    $x = $head_x + $i;
    if ($x < $width) {
        $char = ($i === $snake_length - 1) ? "O" : "*";
        $grid[$y][$x] = $char;
    }
}
echo "Content-Type: text/plain\r\n\r\n";
// Output as ASCII
echo "+".str_repeat("-", $width)."+\n";
foreach ($grid as $line) {
    echo "|" . $line . "|\n";
}
echo "+".str_repeat("-", $width)."+\n";

echo "\nFrame: $frame\n";
?>
