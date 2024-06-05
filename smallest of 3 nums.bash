echo "Enter three numbers:"
read a
read b
read c

if [ $a -le $b ] && [ $a -le $c ]; then
    echo "$a is the smallest"
elif [ $b -le $a ] && [ $b -le $c ]; then
    echo "$b is the smallest"
else
    echo "$c is the smallest"
fi
