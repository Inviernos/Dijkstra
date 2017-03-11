#include <iostream>
#include <fstream>
#include "Graph.h"

#define WIDTH 250
#define HEIGHT 200

int main()
{
    //use a 2d array to input map data
    unsigned char MapData[HEIGHT][WIDTH];
    unsigned int info[HEIGHT][WIDTH];

    //variable to take data to store values in map
    std::ifstream myMap;

    //variables
    int x;
    int y;
    bool pick = false;
    char temp;

    //make a graph object
    Graph greedy;

    //open the files to use to get data
    myMap.open("map1.raw",std::ios::binary);


    //store data into 2d array
    for(int i = 0;i < HEIGHT;i++)
    {
        for(int j = 0;j < WIDTH;j++)
        {
            temp = myMap.get();
            MapData[i][j] = temp;
            info[i][j] = MapData[i][j];
            greedy.addData(info[i][j],i,j);

        }
    }

    //close the file
    myMap.close();

    std::cout << "Map data has been inserted\n";
    //do the greedy algorithm
    greedy.dijkstra();

    //pick coordinates to stop at a destination.
    while(!pick)
    {
        //Enter X:249 Y:199
        std::cout << "Enter Coordinates of X(0-249) and Y(0-199) to a destination.\n\n";
        std::cout << "X: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;

        if(x < 250 && x > -1 && y > -1 && y < 200)
        {
            pick = true;
        }
    }

    //print to the files of Path,Directions, and Distances
    greedy.printPath(MapData,x,y);
    greedy.printDirections();
    greedy.printDistances();





}
