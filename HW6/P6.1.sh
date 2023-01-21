words=$(echo $@ | cut -d"-" -f1)
dir=$(echo $@ | cut -d"-" -f2)
folders=$(echo $@ | cut -d"-" -f2 | cut -d" " -f2-)



for word in $words;do
	echo $word
	for folder in $folders;do	
	       	find $folder -type f -exec grep -H -m 1 -o -w $word {} \; | wc -l
		
	done
done
