#include "AStar.h"

AStar::AStar() {
    InitializeNodes();
}

void AStar::setStart(int y, int x) { //alto, ancho
    StartN = getNode(y, x);
}

void AStar::setGoal(int y, int x) {
    GoalN = getNode(y, x);
}

AStar::Node* AStar::getNode(int y, int x) {
    return &nodosmap[y][x];
}

void AStar::InitializeNodes() {
    for (int x = 0; x < _ancho; ++x) {
        for (int y = 0; y < _alto; ++y) {
            nodosmap[y][x].x = x;
            nodosmap[y][x].y = y;
            nodosmap[y][x].Obstacle = (_mapa.getMapa(y, x) == 1 || _mapa.getMapa(y, x) == 4);


            if (y > 0) nodosmap[y][x].vecNeighbours.push_back(&nodosmap[y - 1][x]);
            if (y < _alto - 1) nodosmap[y][x].vecNeighbours.push_back(&nodosmap[y + 1][x]);
            if (x > 0) nodosmap[y][x].vecNeighbours.push_back(&nodosmap[y][x - 1]);
            if (x < _ancho - 1) nodosmap[y][x].vecNeighbours.push_back(&nodosmap[y][x + 1]);
        }
    }
}

bool AStar::Algoritmo(int& pathLength, int& stateG) {
    for (int x = 0; x < _ancho; ++x) {
        for (int y = 0; y < _alto; ++y) {
            nodosmap[y][x].Visited = false;
            nodosmap[y][x].GlobalGoal = INFINITY;
            nodosmap[y][x].LocalGoal = INFINITY;
            nodosmap[y][x].Parent = nullptr;
        }
    }

    auto distance = [](Node* a, Node* b) {
        return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
        };

    auto heuristic = [distance](Node* a, Node* b) {
        return distance(a, b);
        };

    Node* Current = StartN;
    StartN->LocalGoal = 0.0f;
    StartN->GlobalGoal = heuristic(StartN, GoalN);

    std::list<Node*> listNotTestedNodes;
    listNotTestedNodes.push_back(StartN);

    while (!listNotTestedNodes.empty() && Current != GoalN) {
        listNotTestedNodes.sort([](const Node* lhs, const Node* rhs) {
            return lhs->GlobalGoal < rhs->GlobalGoal;
            });

        while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->Visited)
            listNotTestedNodes.pop_front();

        if (listNotTestedNodes.empty())
            break;

        Current = listNotTestedNodes.front();
        Current->Visited = true;

        for (auto nodeNeighbour : Current->vecNeighbours) {
            if (!nodeNeighbour->Visited && nodeNeighbour->Obstacle == false)
                listNotTestedNodes.push_back(nodeNeighbour);

            float PossiblyLowerGoal = Current->LocalGoal + distance(Current, nodeNeighbour);

            if (PossiblyLowerGoal < nodeNeighbour->LocalGoal) {
                nodeNeighbour->Parent = Current;
                nodeNeighbour->LocalGoal = PossiblyLowerGoal;
                nodeNeighbour->GlobalGoal = nodeNeighbour->LocalGoal + heuristic(nodeNeighbour, GoalN);
            }
        }
    }

    pathLength = 0;

    if (Current == GoalN)
    {
        Node* antesP = StartN;
        Node* p = GoalN;
        while (p->Parent != nullptr) {
            pathLength++;
            if (pathLength > 0) {
                antesP = p;
            }
            p = p->Parent;

        }
        stateG = State(p, antesP);
    }


    //   std::cout << pathLength << "  ";

    return true;
}

int AStar::State(Node* a, Node* b)
{
    
    if (a->x < b->x) return 4;
    if (a->x > b->x) return 3;
    if (a->y > b->y) return 1;
    if (a->y < b->y) return 2;
    return 0;
   
}
