#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <climits>
#include <random>
#include <utility>
#include <ctime>
#include <cmath>

#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>	
#include <boost/iostreams/stream.hpp>	
#include <boost/graph/simple_point.hpp> 
#include <boost/graph/metric_tsp_approx.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>

typedef std::vector<boost::simple_point<double> > PositionVec;
typedef boost::adjacency_matrix<boost::undirectedS, boost::no_property,
        boost::property <boost::edge_weight_t, double> > Graph;
		
template<typename PositionVec>		
int distance(PositionVec a,PositionVec b){
    using std::pow;
    using std::sqrt;
	
    double distance = sqrt(
		pow(static_cast<double>(b.x - a.x), 2.0) +
		pow(static_cast<double>(b.y - a.y), 2.0)) + 0.5;
	
	return static_cast<int>(distance);
}

/*
void swap(int i,int j, int arr[])
{
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}
*/
/*
int getTourLength(std::vector<int> tour){

    vector<int>:: iterator it=tour.begin(); //
    int pcity1=*it,ncity;
    //cout<<"\n the pcity is "<<pcity1<<"\n";
    int tourLength=distance(0,pcity1);
	//find distance from start to finish
    for(it=tour.begin()+1;it!=tour.end();it++)
    {
        ncity=*it;
        tourLength+=distance(pcity1,ncity);
        pcity1=ncity;
    }
    tourLength+=distance(pcity1,0); //adding the distance back to the source path
    return tourLength;
}
*/
/********************************************
* Function: Nearest Neighbor Heuristic
* Description: A greedy approximation of a TSP tour. Findes the nearest neighbor and adds to tour 
* Parameters: position vectors, number of cities, tour vector
* Preconditions: The graph exists and a tour has been created
* Postconditions: Route has been determined and tour calculated
*********************************************/
template<typename PositionVector>
int nearneighbor(PositionVector *position_vec, int numVertices, PositionVector *tour) {
//int nearneighbor(int numVertices, int *arr, std::vector<int> cities, std::vector<int> tour){ 
	
	bool visited[numVertices];
	int i,j; 
    for(i=0;i<numVertices;i++){ visited[i]=0;} // initialize as bool as unvisited
	srand((unsigned)time(NULL)); 
	int rand_start = rand() % numVertices; // randomly select a start 
	boost::simple_point<double>  curVertex = position_vec[rand_start]; // assign that vertex as the current
	visited[rand_start] = 1; // mark the node as visited 
	tour.push_back(curVertex);
	
    int best,closeneighbor,dist;
	int hike = 0; 
	// nested for-loop that orders by nearest neighbor
    for(i=0;i<numVertices;i++) 
    {
        best=INT_MAX; //initialize best to max
        for(j=0;j<numVertices;j++)
        {
			dist = distance(position_vec[i],position_vec[j]);
            if((dist<best) && (visited[j] == 0))
            {
                best=dist;
                closeneighbor = j;
            }
        }
		if(visited[closeneighbor]==0){
			hike += best;
			tour.push_back(position_vec[closeneighbor]);
			visited[closeneighbor] = 1;
		}
    }
	
	hike = distance(tour.end(),tour.beginning);
    tour.push_back(tour.beginning);
	
    return hike;
}

/********************************************
* Function: 2-Optimal Improvement Heuristic 
* Description: 2-optimal heuristic, removes two edges and then swaps them if it is better.
* Parameters: The graph g, the start vertex start, number of vertices numVertices, the tour arr 
* Preconditions: The graph exists and a tour has been created
* Postconditions: Route has been adjusted and length of tour calculated
*********************************************/
/*
int TwoOpt(//stuff//){ 

return 0;
}*/

int main() {
		
	PositionVec cities;
	PositionVec tour;
		
	int neartour = nearneighbor(static_cast<PositionVec>(cities),3,static_cast<PositionVec>(tour));
	
	std::cout << neartour << std::endl;
	
	return 0;
}

