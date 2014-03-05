make
./keyg ../../file/mystery2.ct 11 > m2.invkey
./hw4 crypt -k=m2.invkey ../../file/mystery2.ct > m2.p2
