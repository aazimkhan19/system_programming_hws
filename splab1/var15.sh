#! /bin/bash 
lines=$(grep -e 'HTTP/1.1" 3' -e 'HTTP/1.0" 3' $1 | cut -f1 -d" " | sort | uniq -c | sort -k1 -rn | head | cut -d" " -f6);
total=0;
for i in $lines; do
	total=$((total+i))
done

lines=$(grep -e 'HTTP/1.1" 3' -e 'HTTP/1.0" 3' $1 | cut -f1 -d" " | sort | uniq -c | sort -k1 -rn | head);
for i in $lines;
   do if [[ $i =~ ^[0-9]+$ ]]; then
	 printf "$i -  $(echo "scale=1; $i*100 / $total" | bc)%%" ;
   else printf " - $i \n"; fi  
done
