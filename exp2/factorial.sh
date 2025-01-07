#!/bin/bash

#prints facotiral of a number n
echo "Enter a number: "
read n

f=1
i=$n
while [ $i -gt 0 ]
do
	f=$((f * i)) 
	i=$((i -1))
done

echo "Factorial of number $n is : $f"

