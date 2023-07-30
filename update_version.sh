#!/bin/sh

find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i'' -e 's/2022\ Sven\ Lukas/2023\ Sven\ Lukas/g' {} +

