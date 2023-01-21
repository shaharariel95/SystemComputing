echo -n "Enter parameters in the format file-num1-num2:c1-c2:d1-d2: "
read x
echo $x > tmp
file=$(cut -d- -f1 tmp)
num1=$(cut -d- -f2 tmp)
num2=$(cut -d- -f3 tmp | cut -d: -f1)
c1=$(cut -d: -f2 tmp | cut -d- -f1)
c2=$(cut -d: -f2 tmp | cut -d- -f2)
d1=$(cut -d: -f3 tmp | cut -d- -f1)
d2=$(cut -d: -f3 tmp | cut -d- -f2)


for line in $(seq $num1 $num2)
do
	echo -n $(cat $file | head -$line | tail -1 | cut -c$c1-$c2)
	echo " "  $(cat $file | head -$line | tail -1 | cut -d" " -f$d1-$d2)
done
rm tmp
