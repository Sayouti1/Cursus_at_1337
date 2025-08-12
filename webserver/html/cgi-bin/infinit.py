#!/usr/bin/env python3

import signal
import sys

def handle_sigint(signum, frame):
    sys.exit(0)

signal.signal(signal.SIGINT, handle_sigint)

while True:
    pass
