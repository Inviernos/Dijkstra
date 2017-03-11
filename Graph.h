#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

#define WIDTH 250
#define HEIGHT 200

class Graph
{
    public:
        Graph();
        virtual ~Graph();
        void addData(unsigned int,int,int);
        void printPath(unsigned char (&mapdata)[HEIGHT][WIDTH],int,int);
        void printDirections();
        void printDistances();
        bool checkAll();
        void dijkstra();
        void findMinimum();
    protected:
    private:
        struct Vertex
        {
            float dist;
            float height;
            char path,known;
        };
        float getCost(Vertex ,Vertex);
        void AdjVertices();

        Vertex pixels[HEIGHT][WIDTH];
        bool unknown;
        int xcordinate;
        int ycordinate;
        std::vector<Vertex> adj;
        float maxDistance;

};

#endif // GRAPH_H
