make
./keyg ../../file/mystery1.ct 5 > m1.invkey
./hw4 crypt -k=m1.invkey ../../file/mystery1.ct > m1.p1
