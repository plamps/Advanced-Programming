import pytest
import subprocess
import re

def compile_program(program_name):
    subprocess.run(["gcc", "-o", program_name, f"{program_name}.c", "-Wall"], check=True)

def cleanup_program(program_name):
    subprocess.run(["rm", "-f", program_name], check=True)

@pytest.fixture(scope="function")
def compiled_program(request):
    program_name = request.param
    compile_program(program_name)
    yield program_name
    cleanup_program(program_name)

def run_program(program_name):
    result = subprocess.run(f"./{program_name}", capture_output=True, text=True, check=True)
    return result.stdout

@pytest.mark.parametrize("compiled_program", ["p1", "p2", "p3", "p4"], indirect=True)
def test_program_output(compiled_program):
    output = run_program(compiled_program)
    
    if compiled_program == "p1":
        assert re.search(r"hello world \(pid:\d+\)", output)
        assert re.search(r"hello, I am child \(pid:\d+\)", output)
        assert re.search(r"hello, I am parent of \d+ \(pid:\d+\)", output)
    
    elif compiled_program == "p2":
        assert re.search(r"hello world \(pid:\d+\)", output)
        assert re.search(r"hello, I am child \(pid:\d+\)", output)
        assert re.search(r"hello, I am parent of \d+ \(wc:\d+\) \(pid:\d+\)", output)
    
    elif compiled_program == "p3":
        assert re.search(r"hello world \(pid:\d+\)", output)
        assert re.search(r"\d+\s+\d+\s+\d+\s+p3\.c", output)  # wc output
        assert re.search(r"hello, I am parent of \d+ \(wc:\d+\) \(pid:\d+\)", output)
        assert "hello, I am child" not in output
        assert "this shouldn't print out" not in output
    
    elif compiled_program == "p4":
        assert output.strip() == ""  # p4 redirects output to a file
        with open("p4.output", "r") as f:
            file_content = f.read()
        assert re.search(r"\d+\s+\d+\s+\d+\s+p4\.c", file_content)  # wc output in file
        cleanup_program("p4.output")

def test_p4_file_creation():
    compile_program("p4")
    run_program("p4")
    assert subprocess.run(["test", "-f", "p4.output"]).returncode == 0
    cleanup_program("p4")
    cleanup_program("p4.output")
