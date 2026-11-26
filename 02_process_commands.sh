
#!/bin/bash

echo "===== PROCESS CONTROL ====="

echo "Current process ID:"
echo $$

echo "Running processes:"
ps

echo "Waiting for 3 seconds:"
sleep 3

echo "Process completed!"

echo "===== INPUT OUTPUT REDIRECTION ====="

echo "Hello Linux" > output.txt

echo "Reading file:"
cat < output.txt

echo "===== PIPE ====="

ls | wc -l

echo "===== PROTECTION MANAGEMENT ====="

touch file.txt

chmod 644 file.txt

ls -l file.txt

echo "Practical completed!"
