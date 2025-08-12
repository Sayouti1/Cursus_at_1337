#!/usr/bin/env python3

import os
import sys

# Set upload directory
UPLOAD_DIR = "./html/uploads_cgi/"
os.makedirs(UPLOAD_DIR, exist_ok=True)

# Get content length (required to read binary POST body)
try:
    content_length = int(os.environ.get("CONTENT_LENGTH", 0))
except (ValueError, TypeError):
    content_length = 0

# Set content-type header
print("Content-Type: text/plain\n")

# If there's no data, return error
if content_length == 0:
    print("Error: No data received")
    sys.exit(1)

# Set the filename you want to save (you can customize this)
filename = "uploaded_video.mp4"
filepath = os.path.join(UPLOAD_DIR, filename)

# Read and write the binary content
with open(filepath, "wb") as f:
    f.write(sys.stdin.buffer.read(content_length))

print(f"Success: Uploaded to {filepath}")
