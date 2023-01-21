cat $1 | sed -E '/([^ ]+) \1/!d'
