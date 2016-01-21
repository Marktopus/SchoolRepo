del *.txt
del gcc0.exe

make

gcc0.exe 0 > myout0.txt
gcc0.exe 1 > myout1.txt
gcc0.exe 2 > myout2.txt
gcc0.exe 3 > myout3.txt
gcc0.exe 4 > myout4.txt
gcc0.exe 5 > myout5.txt
gcc0.exe 6 > myout6.txt
gcc0.exe 7 > myout7.txt
gcc0.exe 8 > myout8.txt
gcc0.exe 9 > myout9.txt
gcc0.exe 10 > myout10.txt
gcc0.exe 11 > myout11.txt
gcc0.exe 12 > myout12.txt
gcc0.exe 13 > myout13.txt
gcc0.exe 14 > myout14.txt
gcc0.exe 15 > myout15.txt

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
diff out14 myout14.txt --strip-trailing-cr
diff out15 myout15.txt --strip-trailing-cr

pause