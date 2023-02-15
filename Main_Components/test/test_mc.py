import pytest
import subprocess
from os import path


def test_mc():

    inputfile_content = """
set temperature  72.43 
"""

    expected_read_content = """\
{
	 "cmds" : [
		{"ID": 103, "length":  10, "value":  72.43}
	]
}
"""

    # Define the input and output txt files
    input_filname = "input.txt"
    output_filename = "output.txt"
    print(inputfile_content)

    # Open the input file in write mode
    with open(input_filname, 'w') as fd:
        fd.write(inputfile_content)

    # Calling a executable
    mc_filename = path.join(
        path.curdir,
        '../..',
        'build/Main_Components/main_component'
    )

    # Fix for file writing because in the main functions it is append
    with open(output_filename, "w") as fd:
        pass

    # Subprocess executes external command, captures output.
    mc_process = subprocess.run(
        args=[mc_filename, input_filname, output_filename],
        capture_output=True
    )

    # This function is used to get rid ob the firt b and the new line symbyls int the test terminal output
    captured_output = mc_process.stdout.decode()
    print(captured_output)

    # Reading the file content
    read_output = ""
    with open(output_filename) as fd:
        read_output = fd.read()

    # Debug printing
    # print(f'_{read_output}_')
    # print(f'_{expected_read_content}_')

    # Comparing the output file with the expected content
    assert read_output == expected_read_content

    """Running this command for the pytest

    python3 -m pytest -rA -vv test_mc.py
    
    """
