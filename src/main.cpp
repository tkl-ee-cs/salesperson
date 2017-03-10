/* vim: set tabstop=4 shiftwidth=4 */

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
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>

namespace po = boost::program_options;
namespace bg = boost::geometry;

template<typename VertexListGraph, typename PointContainer, typename WeightMap,
	typename VertexIndexMap>
void connect_vertex_map(VertexListGraph& g, const PointContainer& points,
		WeightMap wmap,
		VertexIndexMap vmap,
		int /*size*/)
{
	using std::pow;
	using std::sqrt;
	typedef typename boost::graph_traits<VertexListGraph>::edge_descriptor
		Edge;

	typedef typename boost::graph_traits<VertexListGraph>::vertex_iterator
		VIter;

	Edge e;
	bool inserted;

	std::pair<VIter, VIter> verts(vertices(g));
	for (VIter src(verts.first); src != verts.second; src++)
	{
		for (VIter dest(src); dest != verts.second; dest++)
		{
			if (dest != src)
			{
				double weight(sqrt(
					pow(static_cast<double>(points[vmap[*src]].x -
						points[vmap[*dest]].x), 2.0) +
					pow(static_cast<double>(points[vmap[*dest]].y -
						points[vmap[*src]].y), 2.0)));

				boost::tie(e, inserted) = boost::add_edge(*src, *dest, g);

				wmap[e] = weight;
			}
		}
	}
}
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
	//TODO:
	// - needs to error check for double spaces, see todo about boost::split
	// - use some namespaces.

	typedef std::vector<boost::simple_point<double> > PositionVec;
	typedef boost::adjacency_matrix<boost::undirectedS, boost::no_property,
		boost::property <boost::edge_weight_t, double> > Graph;

	typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
	typedef std::vector<Vertex> VertexContainer;

	typedef boost::property_map<Graph, boost::edge_weight_t>::type WeightMap;
	typedef boost::property_map<Graph, boost::vertex_index_t>::type VertexMap;

	std::ifstream file(filename.c_str());

	file.exceptions(std::ifstream::badbit);

	PositionVec position_vec;

	int n(0);
	try
	{
		std::string str;
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

	VertexContainer c;
	Graph g(position_vec.size());
	WeightMap weight_map(get(boost::edge_weight, g));
	VertexMap v_map = get(boost::vertex_index, g);

	connect_vertex_map(g, position_vec, weight_map, v_map, n);
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
