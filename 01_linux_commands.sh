
#!/bin/bash

echo "===== INFORMATION COMMANDS ====="
echo "Current directory:"
pwd

echo "Current date:"
date

echo "Calendar:"
cal

echo "Current user:"
who

echo "Word count:"
wc README.md

echo "===== DIRECTORY COMMANDS ====="
ls
mkdir demo
cd demo
pwd
cd ..
rmdir demo

echo "===== FILE COMMANDS ====="
cat README.md
cp README.md copy.txt
mv copy.txt newfile.txt
cmp README.md newfile.txt
diff README.md newfile.txt
grep "OS" README.md
find . -name "*.sh"

echo "Practical completed!"
