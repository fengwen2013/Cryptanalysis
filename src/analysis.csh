set srcdir=/home/feng/WorkPlace/CSCI531HW/HW4/Cryptanalysis/file
		foreach f (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20)
			echo "==> m1.h$f"
			./hw4 histo -t=20 -i=$f $srcdir/mystery1.ct > m1.h$f
		end
