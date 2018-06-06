//
// Created by oguzhan on 12/17/16.
//

#ifndef PROJECT5_CITY_H
#define PROJECT5_CITY_H


#include <utility>
#include <vector>
#include <climits>
#include <queue>


struct cmpr ;

class City {


public:
    static std::vector<City *> cityVec ;        //vector that holds all cities
    static int destCity ;               //id of the goal city
    static long shortestPath ;          //value of shortest path from source city to the goal
    static std::priority_queue<City *, std::vector<City *>, cmpr> cities;       //priority queue that sorts all vector according to their undirected road value
    City(int id ,int straightDist);     //constructor for this class, taking id and straight line distance values as parameter
    int m_straightDist ;            //straight line distance of this city
    int m_id ;                      //id of this city
    long roadSum = 0 ;              //the value that holds sum of all bidirectional roads from source to this city
    long undirect_road = 0 ;        //sum of straight line distance and roadsum of this city
    bool visited = false ;          //indicates whether this node has been visited before
    bool valueUpdated = false ;             //indicates whether undirected road value of this city is updated


    std::vector<std::pair<int,int>> relatedCities ;     //vector that holds all cities related with this one
    void findShortestPath();                //function to find the shortest path value to destination city





};
/*
 * below is the comparator function for priority queue that holds pointers to Cities
 * with this comparator, priority is given to cities with less undirected road value
 */
struct cmpr
{
    bool operator()(const City * lhs, const City * rhs) const
    {
        return lhs->undirect_road > rhs->undirect_road;
    }
};


#endif //PROJECT5_CITY_H
