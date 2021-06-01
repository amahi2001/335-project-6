#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include "binary_heap.h"

#include <iostream>
#include <limits.h>
#include <iomanip>
#include <vector>
#include <list>
using namespace std;

class graph
{
public:
    // constructor
    graph(const int size = 10) : graphVertices(size),
                                 vertexCount{size}
    {

        // Setting identities
        for (int i = 0; i < size; i++)
        {
            graphVertices[i] = Vertex(i + 1);
        }
    }

    void addEdge(const int from, const int to, float edgeWeight)
    {
        //checking for valid input
        if (!isValidVertex(from) || !isValidVertex(to) || 0.0 > edgeWeight)
        {
            cout << "Invalid input: Please provide vertex selections between 1 and " << vertexCount << " and positive weight." << endl;
            return;
        }

        //checking to see if an edge exists already
        if (isConnected(from, to) != -1.0 || from == to)
        {
            return;
        }

        // adding edge properties
        graphVertices[from - 1].adjVert.push_back(&(graphVertices[to - 1]));
        graphVertices[from - 1].eW.push_back(edgeWeight);
    }

    float isConnected(const int from, const int to)
    {
        float weight = -1.0;

        //checking to see if input is valid
        if (!isValidVertex(from) || !isValidVertex(to))
        {
            cout << "Invalid vertex selections:  Please provide vertex between 1 and " << vertexCount << endl
                 << endl;
            return weight;
        }

        auto count = graphVertices[from - 1].adjVert.begin();
        auto count2 = graphVertices[from - 1].eW.begin();

        while (count != graphVertices[from - 1].adjVert.end())
        {
            if ((*count)->id == to)
            {
                weight = *count2;
                break;
            }

            count++;
            count2++;
        }

        return weight;
    }

    void dijkstra(const int from)
    {
        //checking for valid input
        if (isValidVertex(from) == false)
        {
            cout << "Invalid vertex selection: Please vertex with between 1 and " << vertexCount << endl
                 << endl;
            return;
        }

        dijkstraAlgorithm(from);

        //out the results
        for (int i = 0; i < vertexCount; i++)
        {
            cout << graphVertices[i].id << ": ";
            PathPrint(graphVertices[i]);
            cout << ", Cost: " << fixed << setprecision(1)
                 << graphVertices[i].distance << endl;
        }
    }

    void outDegInfo()
    {
        //checking to see if graph is empty
        if (vertexCount == 0)
        {
            cout << "Graph is empty." << endl;
            return;
        }

        int totalDegrees(0), largestDegree(0),
            smallestDegree(vertexCount - 1);

        //for every vertex in graph
        for (int i = 0; i < vertexCount; i++)
        {
            int currentDegree =
                static_cast<int>(graphVertices[i].adjVert.size());

            //updating total degree of graph
            totalDegrees += currentDegree;

            //updating largest degree if possible
            if (currentDegree > largestDegree)
            {
                largestDegree = currentDegree;
            }

            //updating smallest degree if possible
            if (currentDegree < smallestDegree)
            {
                smallestDegree = currentDegree;
            }
        }

        //calculating the number of edges and average degree of vertex
        int numEdges = (totalDegrees / 2);
        float avgDegree = (totalDegrees / vertexCount);

        cout << "Number of Edges: " << numEdges << endl
             << "Smallest Degree: " << smallestDegree << endl
             << "Largest Degree: " << largestDegree << endl
             << "Average Degree: " << setprecision(1) << avgDegree
             << endl
             << endl;
    }

private:
    struct Vertex
    {
        //variables
        int id;
        bool known;
        float distance;
        list<Vertex *> adjVert;
        list<float> eW;
        Vertex *prevVert;

        //constructor
        Vertex() : id{0}, known{false}, distance{0.0},
                   prevVert{nullptr} {}

        //parameterized constructor
        Vertex(int id) : id{id}, known{false}, distance{0.0},
                         prevVert{nullptr} {}

        //operator overload for < for vertex
        bool operator<(const Vertex &rhs) const
        {
            bool lessThan = distance < rhs.distance;
            return lessThan;
        }

        //destructor
        ~Vertex()
        {
            prevVert = nullptr;
        }
    };

    vector<Vertex> graphVertices;
    int vertexCount = 0;

    void dijkstraAlgorithm(const int from)
    {
        BinaryHeap<Vertex> queue;

        for (int i = 0; i < vertexCount; i++)
        {
            graphVertices[i].distance = INT_MAX;
            graphVertices[i].known = false;
        }

        graphVertices[from - 1].distance = 0.0;
        queue.insert(graphVertices[from - 1]);

        while (true)
        {
            int id = 0;
            bool success = false;
            while ((queue.isEmpty() == false) && (success == false))
            {
                id = (queue.findMin()).id;
                queue.deleteMin();

                if (!graphVertices[id - 1].known)
                {
                    success = true;
                }
            }

            if (success == false)
            {
                break;
            }

            Vertex &vOp = graphVertices[id - 1];

            vOp.known = true;

            auto count = vOp.adjVert.begin();
            auto count2 = vOp.eW.begin();

            while (count != vOp.adjVert.end())
            {
                if (((*count)->known) == false)
                {
                    float VwCost = *count2;

                    if ((vOp.distance + VwCost) < (*count)->distance)
                    {
                        (*count)->distance = vOp.distance + VwCost;
                        (*count)->prevVert = &vOp;
                        queue.insert(*(*count));
                    }
                }

                count++;
                count2++;
            }
        }
    }

    void PathPrint(Vertex &v)
    {
        if (v.prevVert == nullptr)
        {
            cout << v.id << endl;
        }
        else
        {
            PathPrint(*(v.prevVert));
            cout << ", ";
        }
    }

    bool isValidVertex(const int id)
    {
        if ((1 > id) || (vertexCount < id))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};

#endif