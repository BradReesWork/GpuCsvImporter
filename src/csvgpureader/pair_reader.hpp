

#pragma once

#include "csv_gpu_reader.hpp"
#include <stdint.h>



using TableUintPair  = boost::container::vector<std::pair<uint32_t, uint32_t>>;
using UintPairRecord = TableUintPair::value_type;

namespace   CsvGpu {  namespace UintPair {

	namespace UintPairParsing {

		using namespace boost::spirit::qi;
		using Iterator = char const*;

		static const rule<Iterator> ignore_header_row			= !uint_ >> *(char_ - eol) >> eol;
		static const rule<Iterator, UintPairRecord()> record	= uint_ >> '\t' >> uint_ >> eol;
		static const rule<Iterator, TableUintPair()> file		= omit [*ignore_header_row] >> *record >> eoi;
	};


	/**
	 * Parse a CSV file that consist of a pair of unsigned int values
	 */
	TableUintPair parse_pair_data(std::string const& fname) {

		boost::iostreams::mapped_file_source mfs(fname);

		TableUintPair table;
		//table.reserve(18*1000*1000);

		if (!parse(mfs.begin(), mfs.end(), UintPairParsing::file, table))
			throw std::runtime_error("Parse failed");

		return table;
	}

}
};


