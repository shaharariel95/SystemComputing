echo -n "Enter number: "
read x
i=$x
j=0
k=0
while [ $i -gt 1 ]
do
	while [ $k -lt $[$x-$i] ]
	do
		echo -n " "
		k=$[$k+1]
	done
	while [ $j -lt $[$i*2] ]
       	do
		echo -n "*"
		j=$[$j+1]
	done
	echo
       	k=0	
	j=0
	i=$[$i-1]
done
i=1
k=$[$x-1]
while [ $i -lt $[$x+1] ]
do
	while [ $k -gt $[$i-1] ]
	do
		echo -n " "
		k=$[$k-1]
	done
	while [ $j -lt $[$i*2] ]
       	do
		echo -n "*"
		j=$[$j+1]
	done
	echo
	k=$[$x-1]
	j=0
	i=$[i+1]
done

