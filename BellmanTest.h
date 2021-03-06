//
// Created by jcespinoza on 3/19/2017.
//

#ifndef AA_CLASSEXERCISES_BELLMANTEST_H
#define AA_CLASSEXERCISES_BELLMANTEST_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Edge.h"

#define INFINITY 999999
#define NONE -1

using namespace std;

class BellmanTest {
public:
    void initializeEdges(int** graph, int size, vector<Edge*>* edges){
        int edgeCount = 0;
        for (int source = 0; source < size; ++source) {
            for (int destination = 0; destination < size; ++destination) {
                int weight = graph[source][destination];
                if(weight != NONE){
                    edgeCount++;
                    edges->push_back(new Edge(source, destination, weight));
                    cout << "ADDING EDGE: " << source << " -> " << destination << " : " << weight << "\n";
                }
            }
        }
        cout << "Added " << edgeCount << " edges \n\n";
    }

    int* getShortestPath(int** graph, int size, int origin)
    {
        int* distances = new int[size];
        int* predecessors = new int[size];

        vector<Edge*> edges;
        initializeEdges(graph, size, &edges);

        initializeArrayWith(distances, size, INFINITY);
        initializeArrayWith(predecessors, size, 0);

        distances[origin] = 0;

        for (int i = 0; i < size - 1; ++i) {
            for (int index = 0; index < edges.size(); ++index) {
                if(shorterPathExist(distances, *edges[index])){
                    updateDistanceArray(distances, *edges[index]);
                    predecessors[edges[index]->destination] = edges[index]->source;
                }
            }
        }

        for (int index = 0; index < edges.size(); ++index) {
            if(shorterPathExist(distances, *edges[index])){
                throw std::runtime_error("Graph contains a negative-weight cycle");
            }
        }

        return predecessors;
    }

    void updateDistanceArray(int *distances, Edge edge) {
        distances[edge.destination] = distances[edge.source] + edge.weight;
    }

    bool shorterPathExist(const int *distances, Edge edge) {
        return distances[edge.source] != INFINITY
               && distances[edge.source] + edge.weight < distances[edge.destination];
    }

    int** _initGraph(int size)
    {
        int **answer = new int* [size];
        for(int i=0;i<size;i++)
        {
            answer[i]=new int[size];
            initializeArrayWith(answer[i], size, NONE);
        }
        return answer;
    }

    void initializeArrayWith(int* array, int size, int defaultValue){
        for (int i = 0; i < size; ++i) {
            array[i] = defaultValue;
        }
    }


    bool compare(int* a, int* b, int size) { for(int i=0;i<size;i++) if(a[i]!=b[i]) return false; return true; }


    void test()
    {
        int** g1 = _initGraph(5);
        g1[0][1]=2;
        g1[0][2]=6;
        g1[0][3]=7;

        g1[1][3]=3;
        g1[1][4]=6;

        g1[2][4]=1;

        g1[3][4]=5;

        static const int r1[] = {0,0,0,1,2};

        int** g2 = _initGraph(5);
        g2[0][1]=1;
        g2[0][2]=10;

        g2[1][3]=2;

        g2[2][3]=-10;

        g2[3][4]=3;

        static const int r2[] = {0,0,0,2,3};


        int* a1 = getShortestPath(g1, 5, 0);
        int* a2 = getShortestPath(g2, 5, 0);

        if(a1 && a2
           && compare(a1, (int*)r1, 5)
           && compare(a2, (int*)r2, 5)
                )
        {
            cout<<"Test: Pass"<<endl;
        }else
        {
            cout<<"Test: Fail"<<endl;
        }

    }
};


#endif //AA_CLASSEXERCISES_BELLMANTEST_H
