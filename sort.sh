#!/bin/bash

gcc sort.c

# ./a.out <input_case> <size>
# >> input_case = [asc, rand1, rand2, rand3, desc]
# >> size = [x, 2x, 4x, 8x]

# check one iteration (descending, input size x)
# ./a.out "2" "1" >> output.txt

# 5 input cases
for (( i=0; i<5; i++)) do
  # 4 sizes
  for (( j=1; j<=8; j=j*2)) do
    # 3 iterations/runs
    for (( k=0; k<3; k++)) do
      ./a.out "$i" "$j" >> output.txt
    done
    echo "" >> output.txt
  done
done