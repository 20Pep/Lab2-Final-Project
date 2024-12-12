#pragma once
#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include "Mapa.h"
#include "Collision.h"




class AStar {
private:
    struct Node {
        bool Obstacle = false;
        bool Visited = false;
        float GlobalGoal;
        float LocalGoal;
        int x;
        int y;
        std::vector<Node*> vecNeighbours;
        Node* Parent = nullptr;
    };
    Mapa _mapa;
    Node nodosmap[25][23];
    int _alto = 25;
    int _ancho = 23;


    

public:
    Node* StartN = nullptr;
    Node* GoalN = nullptr;
    Node* getNode(int y, int x);
    AStar();
    void setStart(int y, int x);
    void setGoal(int y, int x);
    void InitializeNodes(Mapa& mapa);
    bool Algoritmo(int& pathLength, int& stateG);
    int State(Node* a, Node* b);

};

