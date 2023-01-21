echo -n "Enter number: "
read x
echo "I went to sleep for $x seconds at: "
date
sleep $x
echo "I woke up at: "
date
