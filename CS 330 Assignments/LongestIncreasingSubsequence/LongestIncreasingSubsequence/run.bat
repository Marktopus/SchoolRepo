del *.txt
del gnu.exe

make

gnu.exe 0 > myout0.txt
gnu.exe 1 > myout1.txt
gnu.exe 2 > myout2.txt
gnu.exe 3 > myout3.txt


diff out0 myout0.txt --strip-trailing-cr
diff out1 myout1.txt --strip-trailing-cr
diff out2 myout2.txt --strip-trailing-cr
diff out3 myout3.txt --strip-trailing-cr

pause