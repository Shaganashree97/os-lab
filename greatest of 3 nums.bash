echo "Enter three numbers:"
read a
read b
read c

if [ $a -ge $b ] && [ $a -ge $c ]; then
    echo "$a is the greatest"
elif [ $b -ge $a ] && [ $b -ge $c ]; then
    echo "$b is the greatest"
else
    echo "$c is the greatest"
fi
