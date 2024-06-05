sum=0

for (( i=1; i<=10; i+=2 ))
do
    sum=$((sum + i))
done

echo "The sum of odd numbers between 1 to 10 is $sum"
