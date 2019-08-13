#include <stdlib.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <random>

#define GIGABYTES 1 

using namespace std;

size_t gigabytes_as_bytes(size_t value) {
	return value*1024*1024*1024;
}

int main (void) {
	random_device seeder;
	mt19937 random_engine(seeder());
	uniform_int_distribution<int8_t> generate_value(-10, 10);
	size_t mem = gigabytes_as_bytes(GIGABYTES);
	uniform_int_distribution<size_t> pick_index(0, mem);

	cout << "Attempting to allocate " << GIGABYTES << " GB" << endl;

	int8_t *vector_to_simulate_usage = new int8_t[mem];

	cout << "Beginning CPU load, use CTRL+C to exit the process" << endl;
	int8_t a, b;
	size_t index;
	while (true) {
		index = pick_index(random_engine);
		a = generate_value(random_engine);
		b = generate_value(random_engine);
		vector_to_simulate_usage[index] = a*b;
		//this_thread::sleep_for(chrono::microseconds(5));
	}
	
	delete [] vector_to_simulate_usage;

	return 0;
}
