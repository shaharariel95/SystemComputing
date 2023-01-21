echo -n "Enter parameters in the format d1@d1: "
read x
echo $x > tmp
f1=$(cut -d@ -f1 tmp)
echo $x > tmp
f2=$(cut -d@ -f2 tmp)
echo $(ls $f1) > tmp
while read x;do
	echo "$x" | tr " " "\n"
done < tmp > d1
echo $(ls $f2) > tmp2
while read x;do
	echo "$x" | tr " " "\n"
done < tmp2 > d2


while read x;do
	while read y;do
		if [ $y == $x ]
		then
			rm ./$f2/$y
		fi
	done < d2
done < d1
rm tmp
rm d1
rm tmp2
rm d2

