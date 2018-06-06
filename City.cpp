//
// Created by oguzhan on 12/17/16.
//

#include "City.h"
#include <iostream>

using namespace std;




std::vector<City *> City::cityVec ;
std::priority_queue<City *, std::vector<City *>, cmpr> City::cities ;
int City::destCity = -1 ;
long City::shortestPath = LONG_MAX ;

City::City(int id ,int straightDist)
{
    m_id = id ;
    m_straightDist = straightDist ;
}

/*
 * function to find the shortest path from the source to dest city
 */
void City::findShortestPath(){
    long smallest = LONG_MAX ;          //set smallest path from source city to destination for incoming compares


    //iterate each related city to find shortest paths as stated at A* algorithm

    for(auto pair : relatedCities){

        int idx = pair.first ;
        City * next = cityVec[idx] ;        //get a pointer to point to current related city

        if(next->visited && next->roadSum < this->roadSum + pair.second)        //if related city is already visited and there is no need to update its value, continue the loop
            continue ;
        else
            next->valueUpdated = true ;         //indicate that the roadsum and undirected road values are updated

        next->roadSum = this->roadSum + pair.second;        //update total of the paths from source to this node


        next->undirect_road = next->m_straightDist + next->roadSum ;        //update undirected road value from source to this node

        if(idx != destCity && !next->visited && next->valueUpdated) {       //if related city is not visited and it is not the destination city-
            cities.push(next);          //--push it to the priority queue

        }
        next->valueUpdated = false ;        //valueUpdated bool is already checked , so set it to false again
        next->visited = true;           //set related city to visited

        if(idx == destCity){        //if one of the cities is the destination city
            if(shortestPath > next->undirect_road) {        //update shortestPath from source to dest if current value is less
                shortestPath = next->undirect_road;

            shortestPath = shortestPath - next->m_straightDist;     //if goal city is reached, subtract straight line distance value from shortest path value

            }
        }
        //update smallest path if current city has a lesser value
        if(smallest > next->undirect_road) {
            smallest = next->undirect_road;

        }

    }
    //get city with lowest undirected road value and apply findShortestpath function to it, then pop it from queue
    if(!cities.empty()) {
        City * temp = cities.top();
        cities.pop();
        temp->findShortestPath();
    }
}
