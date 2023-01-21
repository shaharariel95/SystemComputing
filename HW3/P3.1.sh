z=$(wc -c *.txt | sort -n | tail -4 |head -3 | tr " " "\n" | grep .txt | tr " " "\n")
rm $z



