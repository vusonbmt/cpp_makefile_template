Installation
Gcovr is available as a Python package that can be installed via pip.

Install newest stable gcovr release from PyPI:

pip install gcovr
Install development version from GitHub:

pip install git+https://github.com/gcovr/gcovr.git


Follow https://github.com/gcovr/gcovr
GCC can instrument the executables to emit coverage data. You need to recompile your code with the following flags:

-fprofile-arcs -ftest-coverage -g -O0
Next, run your test suite. This will generate raw coverage files.

Finally, invoke gcovr. This will print a tabular report on the console.

gcovr -r .
You can also generate detailed HTML reports:

gcovr -r . --html --html-details -o coverage.html

Ex:
https://www.gcovr.com/en/stable/guide.html#getting-started
We compile example1.cpp with the GCC compiler as follows:
g++ -fprofile-arcs -ftest-coverage -fPIC -O0 example.cpp -o program

Note that we compile this program without optimization, because optimization may combine lines of code and otherwise change the flow of execution in the program. Additionally, we compile with the -fprofile-arcs -ftest-coverage -fPIC compiler options, which add logic to generate output files that can be processed by the gcov command.

The compiler generates the program executable. When we execute this command:

./program

the files example1.gcno and example1.gcda are generated. These files are processed with by gcov to generate code coverage statistics. The gcovr command calls gcov and summarizes these code coverage statistics in various formats. For example:

gcovr -r .

generates a text summary of the lines executed: