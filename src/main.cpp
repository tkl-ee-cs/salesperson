#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

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
int process_problem_file()
{
	return 0;
}

int main (int ac, char** av)
{
	po::variables_map vm;

	int r = 0;

	if ((r=process_program_options(ac, av, &vm)))
		return r;

	if (vm.count("input-file"))
		std::cout << "Input file: " << 
			vm["input-file"].as<std::string>() << "\n";

	return 0;
}
