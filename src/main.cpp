#include <stdlib.h>
#include <chrono>
#include <thread>

#define GIGABYTES 1 

using namespace std;

size_t gigabytes_as_bytes(size_t value) {
	return value*1000000000;
}

int main (void) {
	size_t mem = gigabytes_as_bytes(GIGABYTES);

	int8_t *vector_to_simulate_usage = new int8_t[mem];

	this_thread::sleep_for(chrono::seconds(30));
	
	delete [] vector_to_simulate_usage;

	return 0;
}
