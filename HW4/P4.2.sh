i=$1
shift
f=$1
shift

touch tmp

for word in $(cat $f)
do
	flag=0
	for c in $@
	do
		if [ $(echo $word | egrep -o $c | wc -l) -ne $i ]
		then
			flag=1
			break
		fi
	done
	if [ $flag -eq 0 ]
	then
		echo $word >> tmp
	fi
done
sort -u tmp
rm tmp
