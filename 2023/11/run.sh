exec=$1

echo "2 $(./a.out 2 < $exec)"
echo "10 $(./a.out 10 < $exec)"
echo "100 $(./a.out 100 < $exec)"
echo "1000000 $(./a.out 1000000 < $exec)"
