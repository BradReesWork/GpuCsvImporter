
#include <iostream>

#include <boost/container/vector.hpp>
#include "csvgpureader/pair_reader.hpp"

using Table = boost::container::vector<std::pair<uint32_t, uint32_t>>;;


/**
 * This main file is just for testing.  The software is meant to be called programmatically and not via CLI
 */
int main(int argc, char** argv) {

	Table const& table = CsvGpu::UintPair::load(argv[1], '\t');

	int x = 0;
	for ( auto i : table) {
		std::cout << i.first << " --> " << i.second << std::endl;
		x++;

		if ( x > 10)
			exit(1);
	}



}



