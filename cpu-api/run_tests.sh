#!/bin/bash

source test_framework.sh

run_test() {
    local program="$1"
    echo "Testing $program..."
    
    compile_program "$program"
    
    if [ -f "test_${program}.sh" ]; then
        source "test_${program}.sh"
        if [ $? -eq 0 ]; then
            echo "$program: All tests passed"
        else
            echo "$program: Test failed"
        fi
    else
        echo "No test file found for $program"
    fi
    
    cleanup "$program"
    echo
}

programs=(p1 p2 p3 p4 p5 p6 file_fork)

failed_tests=()

for program in "${programs[@]}"; do
    run_test "$program"
    if [ $? -ne 0 ]; then
        failed_tests+=("$program")
    fi
done

if [ ${#failed_tests[@]} -eq 0 ]; then
    echo "All tests completed successfully!"
else
    echo "The following tests failed:"
    for failed_test in "${failed_tests[@]}"; do
        echo "- $failed_test"
    done
    exit 1
fi
