#!/bin/bash

#sum of digits of number n

echo "Enter a number n: "
read num
sum=0
while [ $num -gt 0 ]
do
	mod=$((num % 10))
	sum=$((sum + mod))
	num=$((num / 10))
done

echo "Sum of digits is : $sum"
