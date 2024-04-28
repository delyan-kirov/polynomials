#! /usr/bin/bash

# 1. Създайте празната директория day1
mkdir day1
cd ./day1
# Създайте празните файлове test1, test2, test3
touch test1 test2 test3

# 2. Сложете текстовете:
# - "Hello Bash" във файла test1 
echo Hello Bash > test1
# - текущата дата във файла test2
date > test2
# - името на текущата директория във файла test3.
pwd > test3

# 3. В директорията day1, създайте директорията testDir. 
mkdir testDir
# Копирайте в нея файловете test1, test2, test3.
cp ./{test1,test2,test3} ./testDir

# 5. Изтрийте файловете test1,test2,test3 от директорията day1.
rm ./{test1,test2,test3}

# 6. В директорията day1 - копирайте цялото съдържание на директорията testDir в новата директория testDirCopy.
cp -r ./testDir ./testDirCopy

# 7. Докато се намирате в директорията day1, изтрийте файла test1(от директорията testDir)
rm ./testDir/test1

# 8. Изтрийте цялото съдържание на директорията testDirCopy
rm -r testDirCopy
