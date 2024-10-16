#!/bin/bash

# Compile p6
make p6

# Number of times to run the test
NUM_TESTS=1000

# Run p6 multiple times and check the output
for ((i=1; i<=NUM_TESTS; i++))
do
    output=$(./p6)
    if [[ "$output" != $'hello\ngoodbye' ]]; then
        echo "Test failed on iteration $i"
        echo "Output was:"
        echo "$output"
        exit 1
    fi
done

echo "All $NUM_TESTS tests passed successfully!"
