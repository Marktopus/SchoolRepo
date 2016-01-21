del *.txt
del gnu.exe

make

gnu.exe 0 > myout0.txt
gnu.exe 1 > myout1.txt
gnu.exe 2 > myout2.txt
gnu.exe 3 > myout3.txt
gnu.exe 4 > myout4.txt
gnu.exe 5 > myout5.txt
gnu.exe 6 > myout6.txt
gnu.exe 7 > myout7.txt
gnu.exe 8 > myout8.txt
gnu.exe 9 > myout9.txt
gnu.exe 10 > myout10.txt
gnu.exe 11 > myout11.txt
gnu.exe 12 > myout12.txt
gnu.exe 13 > myout13.txt

diff out0 myout0.txt --strip-trailing-cr
diff out1 myout1.txt --strip-trailing-cr
diff out2 myout2.txt --strip-trailing-cr
diff out3 myout3.txt --strip-trailing-cr
diff out4 myout4.txt --strip-trailing-cr
diff out5 myout5.txt --strip-trailing-cr
diff out6 myout6.txt --strip-trailing-cr
diff out7 myout7.txt --strip-trailing-cr
diff out8 myout8.txt --strip-trailing-cr
diff out9 myout9.txt --strip-trailing-cr
diff out10 myout10.txt --strip-trailing-cr
diff out11 myout11.txt --strip-trailing-cr
diff out12 myout12.txt --strip-trailing-cr
diff out13 myout13.txt --strip-trailing-cr

pause