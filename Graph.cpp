#include "Graph.h"


Graph::Graph()
{

    unknown = true;
    xcordinate = 0;
    ycordinate = 0;
    maxDistance = 0;
}

Graph::~Graph()
{
    //dtor
}

/*
Add information to the vertex
*/
void Graph::addData(unsigned int info,int i,int j)
{
    pixels[i][j].height = info;
    pixels[i][j].dist = INFINITY;
    pixels[i][j].known = 'F';
    pixels[i][j].path = 'U';

}

/*
get the cost of the Vertex
*/
float Graph::getCost(Vertex x,Vertex y)
{
    return sqrtf(1 + powf(x.height - y.height,2));
}

/*
Find the shortest path
*/
void Graph::dijkstra()
{

    int unknownVertex = 50000;

    //set coordinates to 0
    ycordinate = 0;
    xcordinate = 0;

    //set the distance to 0
    pixels[ycordinate][xcordinate].dist = 0;

    //there is an unknown vertex
    while(unknown)
    {
        //clear the adj list
        adj.clear();

        //smallest unknown distance vertex
        findMinimum();

         //the pixel is now known
        pixels[ycordinate][xcordinate].known = 'T';
        unknownVertex -= 1;
        std::cout << "Unknown Vertexes: " << unknownVertex << "\n";

        //every vertex is known
        if(unknownVertex == 0)
        {
            unknown = false;
        }

        //get adjacent vertex
        AdjVertices();

        //go through the adjacent list
        for(unsigned int k = 0; k < adj.size(); k++)
        {
            //The vertex is not known
            if(adj.at(k).known == 'F')
            {
                //find the cost
                float cost = getCost(pixels[ycordinate][xcordinate],adj.at(k));

                //find the minimum value for vertex
                if(pixels[ycordinate][xcordinate].dist + cost < adj.at(k).dist)
                {

                    //Adj Vertex is North
                    if(adj.at(k).path == 'N')
                    {
                        pixels[ycordinate-1][xcordinate].dist = pixels[ycordinate][xcordinate].dist + cost;
                        pixels[ycordinate-1][xcordinate].path = 'S';

                    }//Adj Vertex is South
                    else if(adj.at(k).path == 'S')
                    {
                        pixels[ycordinate+1][xcordinate].dist = pixels[ycordinate][xcordinate].dist + cost;
                        pixels[ycordinate+1][xcordinate].path = 'N';

                    }//Adj Vertex is West
                    else if(adj.at(k).path == 'W')
                    {
                        pixels[ycordinate][xcordinate-1].dist = pixels[ycordinate][xcordinate].dist + cost;
                        pixels[ycordinate][xcordinate-1].path = 'E';

                    }//Adj Vertex is East
                    else
                    {
                        pixels[ycordinate][xcordinate+1].dist = pixels[ycordinate][xcordinate].dist + cost;
                        pixels[ycordinate][xcordinate+1].path = 'W';
                    }

                }
            }
        }




    }
}

/*
print to the file of the directions
*/
void Graph::printDirections()
{
    //variables
    std::ofstream Dir;
    unsigned char direction[HEIGHT][WIDTH];

    //open the file
    Dir.open("Direction.raw",std::ios::binary);

    //go through the data
    for(int a = 0;a<HEIGHT;a++)
    {
        for(int b = 0;b<WIDTH;b++)
        {
            //set data to the direction
            if(pixels[a][b].path == 'N')
            {
                direction[a][b] = 50;
            }
            else if(pixels[a][b].path == 'S')
            {
                 direction[a][b] = 100;
            }
            else if(pixels[a][b].path == 'W')
            {
                direction[a][b] = 150;
            }
            else
            {
                direction[a][b] = 200;
            }

            Dir << direction[a][b];
        }
    }

    std::cout << "Direction Data has been inserted in Direction.raw\n";

    //close the file
    Dir.close();

}

/*
print to the file of the distances
*/
void Graph::printDistances()
{
    //variables
    std::ofstream Dist;
    unsigned char distances[HEIGHT][WIDTH];

    Dist.open("Distances.raw",std::ios::binary);

    //go through the data
    for(int i = 0;i <HEIGHT;i++)
    {
        for(int j = 0;j < WIDTH;j++)
        {
            distances[i][j] = (pixels[i][j].dist/maxDistance) * 255;
            Dist << distances[i][j];
        }
    }

    std::cout << "Distance Data has been inserted in Distance.raw\n";

    //close the file
    Dist.close();


}

/*
print the path
*/
void Graph::printPath(unsigned char (&mapdata)[200][250],int endX, int endY)
{

    xcordinate = endX;
    ycordinate = endY;
    bool findpath = true;

    //make a variable to output to file
    std::ofstream Path;

    Path.open("path.raw",std::ios::binary);

    //start path
    mapdata[ycordinate][xcordinate] = 255;


    while(findpath)
    {

        if(pixels[ycordinate][xcordinate].path == 'N')
        {
            ycordinate -= 1;
            std::cout << "N\n";
        }
        else if(pixels[ycordinate][xcordinate].path == 'S')
        {
            ycordinate +=1;
             std::cout << "S\n";
        }
        else if(pixels[ycordinate][xcordinate].path == 'W')
        {
            xcordinate -=1;
             std::cout << "W\n";
        }
        else if(pixels[ycordinate][xcordinate].path == 'E')
        {
            xcordinate +=1;
            std::cout << "E\n";
        }
        else
        {
            findpath = false;
        }


         mapdata[ycordinate][xcordinate] = 255;


    }

    //output data to the path
    for(int k = 0; k < HEIGHT; k++)
    {
        for(int l = 0;l < WIDTH;l++)
        {
            //find the max distance
            if(pixels[k][l].dist > maxDistance)
            {
                maxDistance = pixels[k][l].dist;
            }

            Path << mapdata[k][l];
        }
    }

    std::cout << "Path Data has been inserted in Path.raw\n";
    Path.close();

}

/*
find the minimum distance vertex
*/
void Graph::findMinimum()
{


    float minimum = INFINITY;

    //go through the vertexes
    for(int a = 0; a < HEIGHT; a++)
    {
        for(int b = 0;b < WIDTH;b++)
        {
            //look at the vertex that is not known and has a distance
            if(pixels[a][b].known == 'F' && pixels[a][b].dist != INFINITY)
            {
                //The vertex distance is minimum
                if(pixels[a][b].dist <= minimum)
                {
                        minimum = pixels[a][b].dist;
                        xcordinate = b;
                        ycordinate = a;
                }
            }
        }
    }

}

/*
Find the Adjacent vertexes
*/
void Graph::AdjVertices()
{
     if(ycordinate == 0 && xcordinate == 0)
    {
        adj.push_back(pixels[ycordinate][xcordinate+1]);
        adj.push_back(pixels[ycordinate+1][xcordinate]);

        adj.at(0).path = 'E';
        adj.at(1).path = 'S';


    }
    else if(ycordinate == 0 && xcordinate == 249)
    {
        adj.push_back(pixels[ycordinate][xcordinate-1]);
        adj.push_back(pixels[ycordinate+1][xcordinate]);

        adj.at(0).path = 'W';
        adj.at(1).path = 'S';

    }
    else if(ycordinate == 199 && xcordinate == 0)
    {
        adj.push_back(pixels[ycordinate][xcordinate+1]);
        adj.push_back(pixels[ycordinate-1][xcordinate]);

        adj.at(0).path = 'E';
        adj.at(1).path = 'N';


    }
    else if(ycordinate == 199 && xcordinate == 249)
    {

        adj.push_back(pixels[ycordinate][xcordinate-1]);
        adj.push_back(pixels[ycordinate-1][xcordinate]);

        adj.at(0).path = 'W';
        adj.at(1).path = 'N';

    }
    else if(xcordinate == 0)
    {
        adj.push_back(pixels[ycordinate][xcordinate+1]);
        adj.push_back(pixels[ycordinate+1][xcordinate]);
        adj.push_back(pixels[ycordinate-1][xcordinate]);

        adj.at(0).path = 'E';
        adj.at(1).path = 'S';
        adj.at(2).path = 'N';




    }
    else if(ycordinate == 0)
    {
        adj.push_back(pixels[ycordinate][xcordinate+1]);
        adj.push_back(pixels[ycordinate][xcordinate-1]);
        adj.push_back(pixels[ycordinate+1][xcordinate]);

        adj.at(0).path = 'E';
        adj.at(1).path = 'W';
        adj.at(2).path = 'S';
    }
    else if(xcordinate == 249)
    {
        adj.push_back(pixels[ycordinate][xcordinate-1]);
        adj.push_back(pixels[ycordinate+1][xcordinate]);
        adj.push_back(pixels[ycordinate-1][xcordinate]);

        adj.at(0).path = 'W';
        adj.at(1).path = 'S';
        adj.at(2).path = 'N';
    }
    else if(ycordinate == 199)
    {
        adj.push_back(pixels[ycordinate][xcordinate+1]);
        adj.push_back(pixels[ycordinate][xcordinate-1]);
        adj.push_back(pixels[ycordinate-1][xcordinate]);

        adj.at(0).path = 'E';
        adj.at(1).path = 'W';
        adj.at(2).path = 'N';


    }
    else
    {
        adj.push_back(pixels[ycordinate][xcordinate+1]);
        adj.push_back(pixels[ycordinate][xcordinate-1]);
        adj.push_back(pixels[ycordinate-1][xcordinate]);
        adj.push_back(pixels[ycordinate+1][xcordinate]);

        adj.at(0).path = 'E';
        adj.at(1).path = 'W';
        adj.at(2).path = 'N';
        adj.at(3).path = 'S';

        // std::cout << adj.at(2).path << "Welcome";
    }


}



