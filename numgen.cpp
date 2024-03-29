// arg[1] = number of numbers to generate  		type: size_t         
// arg[2] = real numbers? 0 = lls, 1 = doubles  	type: bool
// arg[3] = lower bound of numbers to generate  	type: double
// arg[4] = upper bound of numbers to generate  	type: double
// arg[5] = type of distribution to generate		type: *char
// 		0 = uniform = uni
// 		1 = normal = gss
//		2 = exponential = exp
// 		3 = sorted = srt
// 		4 = reverse sorted = rev
// 		5 = almost sorted = alm
//		6 = normal with random mean and stddev  TO BE IMPLEMENTED (eta: never??)
// arg[6] = output file name				type: string

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>

void GenerateUniform(const size_t n, const bool real, const double lower, const double upper, std::ofstream &out)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	
	if (real) {
		std::uniform_real_distribution<double> dis(lower, upper);
		for (size_t i = 0; i < n; ++i) {
			out << dis(gen) << ' ';
		}
	} else {
		std::uniform_int_distribution<long long> dis(lower, upper);
		for (size_t i = 0; i < n; ++i) {
			out << dis(gen) << ' ';
		}
	}

	return;
}

void GenerateNormal(const size_t n, const bool real, const double lower, const double upper, std::ofstream &out)
{
	// Generated nums should generate a bell curve around the center of the range, but never exceed it

	std::random_device rd;
	std::mt19937 gen(rd());

	if (real) {
		std::uniform_real_distribution<double> dis(lower, upper);
		std::normal_distribution<double> dis2((lower + upper) / 2, (upper - lower) / 6);
		for (size_t i = 0; i < n; ++i) {
			double num = dis2(gen);
			while (num < lower || num > upper) {
				num = dis2(gen);
			}
			out << num << ' ';
		}
	} else {
		std::uniform_int_distribution<long long> dis(lower, upper);
		std::normal_distribution<double> dis2((lower + upper) / 2, (upper - lower) / 6);
		for (size_t i = 0; i < n; ++i) {
			long long num = dis2(gen);
			while (num < lower || num > upper) {
				num = dis2(gen);
			}
			out << num << ' ';
		}
	}
}

void GenerateNormalRandom(const size_t n, const bool real, const double lower, const double upper, std::ofstream &out)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// similar to the above functions, but the mean should be
	// a random number between lower and upper, and the stddev
	// should be a random number between 0 and (upper - lower) / 6
	// values should still not exceed the range

	if (real) {
		std::uniform_real_distribution<double> dis(lower, upper);
		std::uniform_real_distribution<double> dis2(0, (upper - lower) / 6);
		for (size_t i = 0; i < n; ++i) {
			double mean = dis(gen);
			double stddev = dis2(gen);
			std::normal_distribution<double> dis3(mean, stddev);
			double num = dis3(gen);
			while (num < lower || num > upper) {
				num = dis3(gen);
			}
			out << num << ' ';
		}
	} else {
		std::uniform_int_distribution<long long> dis(lower, upper);
		std::uniform_real_distribution<double> dis2(0, (upper - lower) / 6);
		for (size_t i = 0; i < n; ++i) {
			long long mean = dis(gen);
			long long stddev = dis2(gen);
			std::normal_distribution<double> dis3(mean, stddev);
			long long num = dis3(gen);
			while (num < lower || num > upper) {
				num = dis3(gen);
			}
			out << num << ' ';
		}
	}
	


	return;
}

void GenerateExponential(const size_t n, const bool real, const double lower, const double upper, std::ofstream &out)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	
	if (real) {
		std::exponential_distribution<double> dis(0.0005);
		for (size_t i = 0; i < n; ++i) {
			double num = dis(gen);
			while (num < lower || num > upper) {
				num = dis(gen);
			}
			out << num << ' ';
		}
	} else {
		std::exponential_distribution<double> dis(0.0005);
		for (size_t i = 0; i < n; ++i) {
			long long num = dis(gen);
			while (num < lower || num > upper) {
				num = dis(gen);
			}
			out << num << ' ';
		}
	}

	return;
}

void GenerateSorted(const size_t n, const bool real, const double lower, const double upper, std::ofstream &out)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// A random array between lower and upper will be generated,
	// then sorted with std::sort

	if (real) {
		std::uniform_real_distribution<double> dis(lower, upper);
		std::vector<double> nums;
		for (size_t i = 0; i < n; ++i) {
			nums.push_back(dis(gen));
		}
		std::sort(nums.begin(), nums.end());
		for (size_t i = 0; i < n; ++i) {
			out << nums[i] << ' ';
		}
	} else {
		std::uniform_int_distribution<long long> dis(lower, upper);
		std::vector<long long> nums;
		for (size_t i = 0; i < n; ++i) {
			nums.push_back(dis(gen));
		}
		std::sort(nums.begin(), nums.end());
		for (size_t i = 0; i < n; ++i) {
			out << nums[i] << ' ';
		}
	}



	return;
}

void GenerateReverseSorted(const size_t n, const bool real, const double lower, const double upper, std::ofstream &out)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// A random array between lower and upper will be generated,
	// then sorted with std::sort

	if (real) {
		std::uniform_real_distribution<double> dis(lower, upper);
		std::vector<double> nums;
		for (size_t i = 0; i < n; ++i) {
			nums.push_back(dis(gen));
		}
		std::sort(nums.begin(), nums.end(), std::greater<double>());
		for (size_t i = 0; i < n; ++i) {
			out << nums[i] << ' ';
		}
	} else {
		std::uniform_int_distribution<long long> dis(lower, upper);
		std::vector<long long> nums;
		for (size_t i = 0; i < n; ++i) {
			nums.push_back(dis(gen));
		}
		std::sort(nums.begin(), nums.end(), std::greater<long long>());
		for (size_t i = 0; i < n; ++i) {
			out << nums[i] << ' ';
		}
	}

	return;
}

// This function will generate a sorted array, then swap a random amount of elements, at random
// The array should be at least 75% sorted

void GenerateAlmostSorted(const size_t n, const bool real, const double lower, const double upper, std::ofstream &out)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	if (real) {
		std::uniform_real_distribution<double> dis(lower, upper);
		std::vector<double> nums;
		for (size_t i = 0; i < n; ++i) {
			nums.push_back(dis(gen));
		}
		std::sort(nums.begin(), nums.end());
		std::uniform_int_distribution<size_t> dis2(0, n / 4);
		size_t swaps = dis2(gen);
		for (size_t i = 0; i < swaps; ++i) {
			std::uniform_int_distribution<size_t> dis3(0, n - 1);
			size_t idx1 = dis3(gen);
			size_t idx2 = dis3(gen);
			std::swap(nums[idx1], nums[idx2]);
		}
		for (size_t i = 0; i < n; ++i) {
			out << nums[i] << ' ';
		}
	} else {
		std::uniform_int_distribution<long long> dis(lower, upper);
		std::vector<long long> nums;
		for (size_t i = 0; i < n; ++i) {
			nums.push_back(dis(gen));
		}
		std::sort(nums.begin(), nums.end());
		std::uniform_int_distribution<size_t> dis2(0, n / 4);
		size_t swaps = dis2(gen);
		for (size_t i = 0; i < swaps; ++i) {
			std::uniform_int_distribution<size_t> dis3(0, n - 1);
			size_t idx1 = dis3(gen);
			size_t idx2 = dis3(gen);
			std::swap(nums[idx1], nums[idx2]);
		}
		for (size_t i = 0; i < n; ++i) {
			out << nums[i] << ' ';
		}
	}

	return;
}

int main(int argc, char *argv[])
{
	if (argc < 7)
	{
		return 1;
	}

	size_t n = std::stoull(argv[1]);
	bool real = std::stoi(argv[2]);
	double lower = std::stod(argv[3]);
	double upper = std::stod(argv[4]);
	std::string dist = argv[5];
	std::string output_file = argv[6];

	std::ofstream out(output_file);

	out << n << ' ';

	if (dist == "uni") {
		GenerateUniform(n, real, lower, upper, out);
	} else if (dist == "gss") {
		GenerateNormal(n, real, lower, upper, out);
	} else if (dist == "exp") {
		GenerateExponential(n, real, lower, upper, out);
	} else if (dist == "srt") {
		GenerateSorted(n, real, lower, upper, out);
	} else if (dist == "rev") {
		GenerateReverseSorted(n, real, lower, upper, out);
	} else if (dist == "alm") {
		GenerateAlmostSorted(n, real, lower, upper, out);
	} else {
		return 1;
	}

	

	out.close();

	return 0;
}