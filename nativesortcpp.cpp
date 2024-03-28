#include <bits/stdc++.h>
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
	size_t n;
	std::vector<float> arr;
	ReadArray(arr, n, argv[1]);
	try {
		sort(arr.begin(), arr.end());
	} catch (const std::exception &e) {
		return -1;
	}
	PrintArray(arr, n, argv[2]);
	return 0;
}
