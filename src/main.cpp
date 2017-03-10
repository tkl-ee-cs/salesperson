#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/program_options.hpp>
#include <boost/graph/simple_point.hpp>
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/algorithm/string.hpp>

namespace po = boost::program_options;
namespace bg = boost::geometry;

/**
 * Process program options usint boost
 */
int process_program_options(int ac, char** av, po::variables_map *vm)
{
	po::options_description desc("Usage: salepesrson [options] [input-file]");

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
	//TODO: create a graph for the positionvecs

	typedef std::vector<boost::simple_point<double> > PositionVec;

	std::ifstream file(filename.c_str());

	file.exceptions(std::ifstream::badbit);

	PositionVec position_vec;

	try
	{
		// store some points in a vector/graph here
		std::string str;
		int n(0);
		while (std::getline(file, str))
		{
			boost::algorithm::trim(str);
			boost::simple_point<double> vertex;

			size_t idx(str.find(' '));

			// TODO: replace with boost split
			std::string x(
				str.substr(idx+1,
				str.size() - ((idx+1) + (str.size()-(str.find(' ', idx+1))))
			));
			std::string y(
				str.substr(str.find(' ', idx+1)+1,
				str.size() - str.find(' ', idx+1))
			);

			std::cout << "line: " << str << "\n";
			std::cout << "x: " << x << ".\n";
			std::cout << "y: " << y << ".\n";

			vertex.x = boost::lexical_cast<double>(x);
			vertex.y = boost::lexical_cast<double>(y);

			position_vec.push_back(vertex);
			n++;
		}
		file.close();
	}
	catch(const std::ifstream::failure& e)
	{
		std::cout << e.what() << "\n";
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
