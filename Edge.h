//
// Created by jcespinoza on 3/7/2017.
//

#ifndef AA_CLASSEXERCISES_EDGE_H
#define AA_CLASSEXERCISES_EDGE_H

class Edge
{
public:
    int source;
    int destination;
    int weight;
    Edge(int source, int destination, int weight){
        this->source = source;
        this->destination = destination;
        this->weight = weight;
    }
    virtual ~Edge(){}
protected:
private:
};


#endif //AA_CLASSEXERCISES_EDGE_H
