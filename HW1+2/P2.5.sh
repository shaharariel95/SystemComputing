echo -n "Enter file or directory names: " 
read -a arr
for i in "${arr[@]}"
do
	if [ -d $i ]
	then
		echo $i "is a directory"
	elif [ -f $i ] 
	then
		echo -n $i "is a file of size: "
		wc -c < $i
	else
		echo $i "is not a file or directory"
	fi
done
