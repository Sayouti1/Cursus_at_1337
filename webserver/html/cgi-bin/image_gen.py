#!/usr/bin/env python3
import os
import sys
from io import BytesIO
from PIL import Image, ImageDraw

# Grid and cell settings
grid_width = 30
grid_height = 30
cell_size = 20

img_width = grid_width * cell_size
img_height = grid_height * cell_size

# Example snake path (longer for more pixels)
snake = [
    (5, 5), (6, 5), (7, 5), (8, 5), (9, 5), (10, 5), (11, 5),
    (11, 6), (11, 7), (11, 8), (10, 8), (9, 8), (8, 8), (7, 8),
    (6, 8), (5, 8), (4, 8), (3, 8), (2, 8), (1, 8), (1, 9),
    (1, 10), (2, 10), (3, 10), (4, 10), (5, 10), (6, 10),
]

# Food position
food = (14, 12)

# Create image
img = Image.new("RGB", (img_width, img_height), color="black")
draw = ImageDraw.Draw(img)

# Draw background grid
for i in range(grid_width):
    for j in range(grid_height):
        x1 = i * cell_size
        y1 = j * cell_size
        x2 = x1 + cell_size
        y2 = y1 + cell_size
        draw.rectangle([x1, y1, x2, y2], outline=(40, 40, 40))

# Draw snake body
for segment in snake:
    x, y = segment
    x1 = x * cell_size
    y1 = y * cell_size
    x2 = x1 + cell_size
    y2 = y1 + cell_size
    draw.rectangle([x1, y1, x2, y2], fill="lime")

# Draw snake head
head = snake[-1]
hx1 = head[0] * cell_size
hy1 = head[1] * cell_size
hx2 = hx1 + cell_size
hy2 = hy1 + cell_size
draw.rectangle([hx1, hy1, hx2, hy2], fill="yellow")

# Draw food
fx, fy = food
fx1 = fx * cell_size
fy1 = fy * cell_size
fx2 = fx1 + cell_size
fy2 = fy1 + cell_size
draw.ellipse([fx1+3, fy1+3, fx2-3, fy2-3], fill="red")

# Save image to buffer
buffer = BytesIO()
img.save(buffer, format="PNG")
image_data = buffer.getvalue()

# Output HTTP headers and image data
print("Content-Type: image/png")
print(f"Content-Length: {len(image_data)}")
print()
sys.stdout.flush()
sys.stdout.buffer.write(image_data)
