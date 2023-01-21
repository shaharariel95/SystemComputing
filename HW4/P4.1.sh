num1=$1
shift
num2=$1
shift
num2=$[$num2-1]
num1=$[$num1-1]
for ex in $@
do
	echo $(echo $ex) | egrep "^(.*)\1{$num1,$num2}$"
done
