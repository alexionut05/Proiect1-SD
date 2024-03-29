#!/bin/bash
#
# This script is used to generate tests for the sorting algorithms (RIP processor)
# usage: ./test_sortings.sh [number of runs]

#sorting_paths=("ShellSort")
sorting_paths=("BucketSort" "HeapSort" "MergeSort" "QuickSort" "RadixSort" "ShellSort")
distribs=("uni" "gss" "exp" "srt" "rev" "alm")

#######################################################################
# Generate batch of tests
# Arguments:
# 	$1: Number of tests to generate
# 	$2: Number of elements in each test
# 	$3: Boolean to determine if the elements are floats[1] or integers[0]
#	$4: Lower bound of the range of the elements
#	$5: Upper bound of the range of the elements
#	$6: Type of distribution of the elements
#	$7: Working directory
#######################################################################
generate_batch() {
	for i in $(seq 1 $1); do
		./numgen $2 $3 $4 $5 $6 $7/input_f$3-$i.txt
	done
}

#######################################################################
# Generate all the tests for the current run
# Arguments:
# 	$1: Working directory
#######################################################################
generate_tests() {
	# Batch 1: 6000 tests, 1000 elements
	# 	3/4 integers, 1/4 floats
	# 	12b range
	mkdir -p "$1/batch1"
	for distrib in "${distribs[@]}"; do
		generate_batch 750 1000 0 -2048 2047 $distrib "$1/batch1"
		generate_batch 250 1000 1 -2048 2047 $distrib "$1/batch1"
	done

	# Batch 2: 600 tests, 10000 elements
	# 	3/4 integers, 1/4 floats
	# 	32b range
	mkdir -p "$1/batch2"
	for distrib in "${distribs[@]}"; do
		generate_batch 75 10000 0 -2147483648 2147483647 $distrib "$1/batch2"
		generate_batch 25 10000 1 -2147483648 2147483647 $distrib "$1/batch2"
	done

	# Batch 3: 60 tests, 1000000 elements
	# 	3/4 integers, 1/4 floats
	# 	32b range
	mkdir -p "$1/batch3"
	for distrib in "${distribs[@]}"; do
		generate_batch 8 100000 0 -2147483648 2147483647 $distrib "$1/batch3"
		generate_batch 2 100000 1 -2147483648 2147483647 $distrib "$1/batch3"
	done

	# Batch 4: 6 tests, 10000000 elements
	# 	all ints
	# 	64b range
	mkdir -p "$1/batch4"
	for distrib in "${distribs[@]}"; do
		generate_batch 1 1000000 0 -9223372036854775808 9223372036854775807 $distrib "$1/batch4"
	done
}

#######################################################################
# Sort all the tests in the current run, then validate the results
# Arguments:
# 	$1: Executable to use
# 	$2: Run index
#######################################################################
call_sort() {
	mkdir -p "outputs/run$2/$1"
	mkdir -p "results/run$2/$1"
	touch "results/run$2/$1.txt"

	for batch in $(ls "inputs/run$2"); do
		mkdir -p "outputs/run$2/$1/$batch"
		echo "Batch $batch:" >> "results/run$2/$1.txt"
		echo "Sorting batch $batch with $1..."
		startbatch=$(date +%s)
		for inputfile in $(ls "inputs/run$2/$batch"); do
			start=$(date +%s)
			if [ "$1" != "nativesortpython.py" ]; then
				./$1 "inputs/run$2/$batch/$inputfile" "outputs/run$2/$1/$batch/$inputfile"
			else
				python3 $1 "inputs/run$2/$batch/$inputfile" "outputs/run$2/$1/$batch/$inputfile"
			fi

			end=$(date +%s)
			if [ $? -ne 0 ]; then
				echo "Error while sorting $inputfile" >> "results/run$2/$1.txt"
			elif [ "$1" != "nativesort" ] && [ "$1" != "nativesortpython.py" ]; then
				cmp --silent "outputs/run$2/nativesort/$batch/$inputfile" \ 
					"outputs/run$2/$1/$batch/$inputfile" && echo \
					"$inputfile sorted correctly by $1 in $((end-start)) seconds." \
					>> "results/run$2/$1.txt" || echo \
					"$inputfile sorted incorrectly by $1 in $((end-start)) seconds." \
					>> "results/run$2/$1.txt"
			else
				echo "$inputfile sorted in $((end-start)) seconds." >> "results/run$2/$1.txt"
			fi
		done
		endbatch=$(date +%s)
		echo "Batch $batch sorted in $((endbatch-startbatch)) seconds."
	done
}

# Compile all the .cpp files
# Comile built in cpp sort
g++ -O3 -o nativesort nativesortcpp.cpp

# Compile all custom sorting algorithms
for dir in "${sorting_paths[@]}"; do
	for cpp_file in $dir/*.cpp; do
		g++ -O3 -o ${cpp_file%.cpp} $cpp_file
	done
done

# Compile number generator
g++ -O3 -o numgen numgen.cpp

# Run the script argv[1] times
run_cnt=1
if [ "$#" != 1 ]; then
	run_cnt=$1
fi

for run in $(seq 1 $run_cnt); do
	echo "Initializing run $run..."
	mkdir -p "inputs/run$run"
	mkdir -p "outputs/run$run"
	mkdir -p "results/run$run"

	echo "Generating tests for run $run..."
	start=$(date +%s)
	generate_tests "inputs/run$run"
	end=$(date +%s)
	echo "Tests generated in $((end-start)) seconds."

	echo "Sorting with the built-in C++ sort..."
	start=$(date +%s)
	call_sort "nativesort" $run
	end=$(date +%s)
	echo "Built-in C++ sort completed in $((end-start)) seconds."

	echo "Sorting with the built-in Python sort..."
	start=$(date +%s)
	call_sort "nativesortpython.py" $run
	end=$(date +%s)
	echo "Built-in Python sort completed in $((end-start)) seconds."

	for dir in "${sorting_paths[@]}"; do
		for cpp_file in $dir/*.cpp; do
			echo "Sorting with $cpp_file..."
			start=$(date +%s)
			call_sort ${cpp_file%.cpp} $run
			end=$(date +%s)
			echo "$cpp_file completed in $((end-start)) seconds."
		done
	done
done

# Delete all the executables
for dir in "${sorting_paths[@]}"; do
	find $dir -type f ! -name "*.*" -delete
done
rm numgen
rm nativesort