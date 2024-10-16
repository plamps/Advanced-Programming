#!/bin/bash

# Change to the directory containing p5.c
cd "$(dirname "$0")" || exit 1

# Compile p5.c
gcc -o p5 p5.c

# Run the program and capture its output
output=$(./p5)

# Expected output patterns
expected_patterns=(
    "hello world \(pid:[0-9]+\)"
    "x = 100 \(before fork\)"
    "hello I am child \(pid:[0-9]+\)"
    "x = 100 \(in child\)"
    "x = 200 \(in child after changing\)"
    "hello I am parent of [0-9]+ \(wc:[0-9]+\) \(pid:[0-9]+\)"
    "x = 100 \(in parent\)"
    "x = 300 \(in parent after changing\)"
)

# Check each expected pattern
for pattern in "${expected_patterns[@]}"; do
    if ! echo "$output" | grep -qE "$pattern"; then
        echo "Test failed: Output doesn't match pattern: $pattern"
        echo "Actual output:"
        echo "$output"
        exit 1
    fi
done

echo "All tests passed successfully!"

# Clean up
rm -f p5
