import os

Executable = "Optimize_2/optimize.exe" # input("Enter the executble file name: ")
Folder = "testcase" # input("Enter the test case folder name: ")
Cases = "7" # input("Enter the amount of test cases: ")
Validator = "AssemblyCompiler/asmc"

for i in range(7, int(Cases) + 1):
    os.system(f"cat {Folder}/test{str(i)}.in")
    print("\n")
    os.system(f"./{Executable} < {Folder}/test{str(i)}.in > out")
    os.system(f"cat out")
    os.system(f"./{Validator} 2 3 5 < out")
    print("\n")

os.system("rm out")
