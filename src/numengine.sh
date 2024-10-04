#!/bin/bash

PYTHON="$(dirname $(dirname $(realpath $0)) )/src/venv/bin/python"
MAIN="$(dirname $(dirname $(realpath $0)) )/src/main.py"

"$PYTHON" "$MAIN"