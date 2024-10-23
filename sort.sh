#!/bin/bash

gcc sort.c -o sort

# ./a.out <char input_case> <int size> <char sort>
sort_algos=("isort" "shsort" "msort" "bsort" "ssort" "qsort" "qsort1" "hsort")
input_case=("asc" "desc" "rand1" "rand2" "rand3")
# size = [x, 2x, 4x, 8x]

# check one iteration (descending, input size x)
# ./sort desc 1 hsort >> output.txt

for sort in ${sort_algos[@]}; do
  echo $sort >> output.txt
  for case in ${input_case[@]}; do
    # echo input case: $case >> output.txt
    for (( j=1; j<=8; j=j*2)) do  # 4 sizes
      # echo x$j >> output.txt
      for (( k=0; k<3; k++)) do   # 3 iterations/runs
        ./sort $case 1 $sort>> output.txt
      done
      echo "" >> output.txt
    done
  done
  echo "" >> output.txt
done
