#include <fstream>
#include <vector>
#include <cmath>

void RunInsertionSort(std::vector<float> &arr, const size_t &n)
{
	float cur_item;

	for (size_t i = 0; i < n; ++i) {
		cur_item = arr[i];
		int j = static_cast<int>(i);

		while (j >= 0 && arr[j] > cur_item) {
			arr[j + 1] = arr[j];
			--j;
		}
		
		arr[j + 1] = cur_item;
	}

	return;
}

void RunBucketSort(std::vector<float> &arr, const size_t &n, const float &max)
{
	// Create sqrt(n) empty buckets
	int bucket_count = static_cast<int>(sqrt(n));
	std::vector<float> buckets[bucket_count];

	// Create index multiplier
	const float multiplier = static_cast<float>(bucket_count) / max;

	// Distribute elements into buckets
	for (size_t i = 0; i < n; ++i) {
		const size_t idx = static_cast<const size_t>(arr[i] * multiplier);
		const size_t idx2 = (idx >= bucket_count) ? idx - 1 : idx;
		buckets[idx2].push_back(arr[i]);
	}

	// Sort each bucket
	for (size_t i = 0; i < bucket_count; ++i) {
		RunInsertionSort(buckets[i], static_cast<const size_t>(buckets[i].size()));
	}

	// Concatenate all the buckets
	arr.clear();

	for (size_t i = 0; i < bucket_count; ++i) {
		size_t bucket_size = buckets[i].size();
		for (size_t j = 0; j < bucket_size; ++j) {
			arr.push_back(buckets[i][j]);
		}
	}

	return;
}

void SortArray(std::vector<float> &arr, const size_t &n)
{
	// Initialize two arrays for both positive and negative numbers
	std::vector<float> negative_array;
	std::vector<float> positive_array;

	float min = 0.f;
	float max = 0.f;
	float x;

	// Distribute the array elements into the two new arrays
	for (size_t i = 0; i < n; ++i) {
		x = arr[i];
		if (x < 0.f) {
			min = (x < min) * x + !(x < min) * min;
			negative_array.push_back(-1.f * x);
		} else {
			max = (x > max) * x + !(x > max) * max;
			positive_array.push_back(x);
		}
	}

	// Call the two sorts
	min = -1.f * min;
	const size_t negative_array_size = static_cast<const size_t>(negative_array.size());
	const size_t positive_array_size = static_cast<const size_t>(positive_array.size());
	RunBucketSort(negative_array, negative_array_size, min);
	RunBucketSort(positive_array, positive_array_size, max);

	// Store negative numbers
	// Since after multiplying by -1, we will have a descending order array,
	// We will access the array the other way around
	const size_t neg_idx = negative_array_size - 1;
	for (size_t i = 0; i < negative_array_size; ++i) {
		arr[i] = -1.f * negative_array[neg_idx - i];
	}

	// Store positive numbers;
	for (size_t i = negative_array_size; i < n; ++i) {
		arr[i] = positive_array[i - negative_array_size];
	}

	return;
}

void ReadArray(std::vector<float> &arr, size_t &n, char *input_file)
{
	std::ifstream in(input_file);

	in >> n;
	arr.resize(n);

	for (size_t i = 0; i < n; ++i) {
		in >> arr[i];
	}

	in.close();
	return;
}

void PrintArray(std::vector<float> &arr, size_t &n, char *output_file)
{
	std::ofstream out(output_file);

	for (size_t i = 0; i < n; ++i) {
		out << arr[i] << ' ';
	}
	
	out.close();
	return;
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		return 1;
	}
	
	size_t n;
	std::vector<float> array;

	ReadArray(array, n, argv[1]);

	SortArray(array, n);

	PrintArray(array, n, argv[2]);

	return 0;
}