#include <stdlib.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <cstring>

#define DEFAULT_ACTIVE_CPU_TIME chrono::milliseconds(900)
#define DEFAULT_MEM kilobytes_as_bytes(512)

typedef int8_t byte;

using namespace std;

size_t gigabytes_as_bytes(size_t gigabytes) {
	return gigabytes*1024*1024*1024;
}

size_t megabytes_as_bytes(size_t megabytes) {
	return megabytes*1024*1024;
}

size_t kilobytes_as_bytes(size_t kilobytes) {
	return kilobytes*1024;
}

void parse_cli_args(
	int argc,
       	char** argv,
       	chrono::milliseconds &active_cpu_time, 
	chrono::milliseconds &inactive_cpu_time,
	size_t &mem
) {
	active_cpu_time = DEFAULT_ACTIVE_CPU_TIME;
	inactive_cpu_time = chrono::milliseconds(1000) - active_cpu_time;
	mem = DEFAULT_MEM;

	int i = 1;
	while (i < argc) {
		if (strcmp(argv[i], "--cpu") == 0) {
			i++;
			double cpu_pct = atof(argv[i]);
			active_cpu_time = chrono::milliseconds((unsigned long long)(1000*cpu_pct));
			inactive_cpu_time = chrono::milliseconds(1000) - active_cpu_time;
		} else if (strcmp(argv[i], "--kb") == 0) {
			i++;
			int kb = atoi(argv[i]);
			mem = kilobytes_as_bytes(kb);
		} else if (strcmp(argv[i], "--mb") == 0) {
			i++;
			int mb = atoi(argv[i]);
			mem = megabytes_as_bytes(mb);
		} else if (strcmp(argv[i], "--gb") == 0) {
			i++;
			int gb = atoi(argv[i]);
			mem = gigabytes_as_bytes(gb);
		} else {
			cout << "Argument " << argv[i] << " not recognized" << endl;
		}	
		i++;
	}

}

int main (int argc, char** argv) {
	random_device seeder;
	mt19937 random_engine(seeder());
	uniform_int_distribution<byte> generate_value(-20, 20);
	uniform_int_distribution<size_t> pick_index;
	size_t mem;
        byte *memory_array;
	byte a, b;
	size_t index;
	chrono::milliseconds active_cpu_time, inactive_cpu_time;

	parse_cli_args(argc, argv, active_cpu_time, inactive_cpu_time, mem);

	cout << "Attempting to allocate " << mem << " bytes" << endl;
	memory_array = new int8_t[mem];
	pick_index = uniform_int_distribution<size_t>(0, mem-1);

	cout << "Beginning CPU load, use CTRL+C to exit the process" << endl;

	while (true) {
		auto begin = chrono::high_resolution_clock::now();
		while (chrono::high_resolution_clock::now() - begin < active_cpu_time) {
			index = pick_index(random_engine);
			a = generate_value(random_engine);
			b = generate_value(random_engine);
			memory_array[index] = a*b;
		}
		this_thread::sleep_for(inactive_cpu_time);
	}
	
	delete [] memory_array;

	return 0;
}
