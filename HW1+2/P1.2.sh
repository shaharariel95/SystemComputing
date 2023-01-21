echo -n "Enter first number: "
read x
echo -n "Enter second number: "
read y
echo -n "Enter third number: "
read z
if [[ $x -gt $y ]] 
then
	big=$x
else
	big=$y
fi
if [[ $z -gt $big ]]
then
	big=$z
fi
echo  "The maximum of the three numbers" $x $y $z" is: " $big


