#!/bin/bash

compile_program() {
    gcc -o "$1" "$1.c" -Wall
}

run_program() {
    ./"$1"
}

check_output() {
    local output="$1"
    shift
    local patterns=("$@")

    for pattern in "${patterns[@]}"; do
        if ! echo "$output" | grep -qE "$pattern"; then
            echo "Test failed: Output doesn't match pattern: $pattern"
            echo "Actual output:"
            echo "$output"
            return 1
        fi
    done
    return 0
}

cleanup() {
    rm -f "$1"
}

