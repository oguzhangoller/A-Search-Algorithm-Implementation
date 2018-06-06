/*
Student Name: Oğuzhan Göller
Student Number: 2013400228
Project Number: 5
Operating System: Linux
Compile Status: Code compiles properly
Program Status: Code runs properly
Notes: Anything you want to say about your code that will be helpful in the grading process.

*/

#include <iostream>
#include <fstream>
#include "City.h"

using namespace std;


int main(int argc, char* argv[]) {

    long numOfCities , numOfRoads ;
    int sourceCity, destCity ;
    // below reads the input file
    // in your next projects, you will implement that part as well
    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }
    /*
     * below is file reader in c
     * i read the file with fscanf because it is much faster than ifstream
     */
    FILE * pFile;
    pFile = fopen (argv[1],"r");
    /*
     * i created the file with ofstream because only a single line of output is required
     */

    ofstream outputFile (argv[2]);

    rewind (pFile);                                 //for putting file reader at beginning of file
    fscanf (pFile, "%ld", &numOfCities);
    fscanf (pFile, "%ld", &numOfRoads);

    /*
     * below are reading loops from the file
     */
    for(long i=0 ; i<numOfCities ; i++){
        int distValue;
        fscanf (pFile, "%d", &distValue);
        City * ct = new City(i,distValue);      //create a new city with according straight line path
        City::cityVec.push_back(ct);            //and add it to city vector
    }

    for(long i=0 ; i<numOfRoads ; i++){
        int firstCity,secondCity,path ;
        fscanf (pFile, "%d", &firstCity);
        fscanf (pFile, "%d", &secondCity);
        fscanf (pFile, "%d", &path);
        //add related cities to each others related cities vector with according path value
        City::cityVec.at(firstCity)->relatedCities.push_back(std::make_pair(secondCity,path));
        City::cityVec.at(secondCity)->relatedCities.push_back(std::make_pair(firstCity,path));
    }

    fscanf (pFile, "%d", &sourceCity);
    fscanf (pFile, "%d", &destCity);

    City::destCity = destCity ;             //assign static variable goal city in city class to destination city

    City::cityVec[sourceCity]->visited = true ;     //indicate that source city is visited

    City::cityVec[sourceCity]->findShortestPath();      //find the shortest path from this city to the goal


    if (outputFile.is_open())               //create an output file and write the result to it
    {
        outputFile << City::shortestPath;           //write the result to it
        outputFile.close();
    }


    return 0;
}