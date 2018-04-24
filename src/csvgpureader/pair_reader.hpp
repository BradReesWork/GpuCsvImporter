

#pragma once

#include "csv_gpu_reader.hpp"

#include <boost/container/vector.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <stdint.h>





namespace CsvGpu {
namespace UintPair {

	using namespace boost::spirit;

	using qi::uint_;
	using qi::char_;
	using boost::phoenix::ref;

	// private stuff
	namespace {
		using TableUintPair  	= boost::container::vector<std::pair<uint32_t, uint32_t>>;
		using UintPairRecord 	= TableUintPair::value_type;
		using UintPairIterator 	= char const*;

	};


	/**
	 * Parse a CSV file that consist of a pair of unsigned int values
	 */
	TableUintPair load(std::string const& fname, const char delim) {

		auto dlm 	= qi::lit(delim);

		qi::rule<UintPairIterator> ignore_header_row = !uint_ >> *(char_ - eol) >> eol;
		qi::rule<UintPairIterator, UintPairRecord()> record	= uint_ >> dlm  >> uint_ >> eol;
		qi::rule<UintPairIterator, TableUintPair()> file = omit [*ignore_header_row] >> *record >> eoi;


		boost::iostreams::mapped_file_source mfs(fname);

		TableUintPair table;
		//table.reserve(18*1000*1000);

		if (!qi::parse(mfs.begin(), mfs.end(), file, table))
			throw std::runtime_error("Qi Parser failed");

		return table;
	}


}
};


