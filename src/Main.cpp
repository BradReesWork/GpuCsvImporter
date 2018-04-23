
#include <iostream>

#include <boost/container/vector.hpp>
#include "csvgpureader/pair_reader.hpp"

using Table = TableUintPair;


/**
 *
 */
int main(int argc, char** argv) {

	TableUintPair const& table = CsvGpu::UintPair::parse_pair_data("./test/10M.csv");

	int x = 0;
	for ( auto i : table) {
		std::cout << i.first << " --> " << i.second << std::endl;
		x++;

		if ( x > 10)
			exit(1);
	}



}



