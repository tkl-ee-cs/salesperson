#include <iostream>
#include <fstream>
#include <string>
#include <boost/iostreams/stream.hpp>
#include <boost/program_options.hpp>
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

namespace po = boost::program_options;
namespace bg = boost::geometry;

/**
 * Process program options usint boost
 */
int process_program_options(int ac, char** av, po::variables_map *vm)
{
	po::options_description desc("Usage: saleperson [options] [input-file]");

	po::positional_options_description p;

	p.add("input-file", -1);

	desc.add_options()
		("help", "produce help message")
		("input-file", po::value<std::string>(), "supply problem input file")
	;

	po::store(po::command_line_parser(ac, av)
			.options(desc).positional(p).run(), *vm);

	po::notify(*vm);

	if (vm->count("help") || ac < 2)
	{
		std::cout << desc << "\n";
		return 1;
	}

	return 0;
}

/**
 * Process a problem file
 */
int process_problem_file(std::string filename)
{
	//TODO: Needs to take a file, and iterate line by line, adding a point
	//to a vector of nodes.
	std::ifstream file(filename.c_str());

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// store some points in a vector/graph here
		for(std::string str; std::getline(file, str); )
			std::cout << str << "\n";
	}
	catch(const std::ifstream::failure& e)
	{
		std::cout <<  "\n";
	}

	// Create one point
	bg::model::d2::point_xy<double> point(1, 2);

	// Print the coordinates std::cout << "point: " << bg::get<0>(point) << ", " << bg::get<1>(point) << "\n";

	return 0;
}

int main (int ac, char** av)
{
	po::variables_map vm;

	int r = 0;

	if ((r=process_program_options(ac, av, &vm)))
		return r;

	if (vm.count("input-file"))
	{
		process_problem_file(vm["input-file"].as<std::string>());
		std::cout << "Input file: " << vm["input-file"].as<std::string>() << "\n";
	}

	return 0;
}
