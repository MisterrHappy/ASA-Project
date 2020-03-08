/* First ASA project               */
/* Authors: Andre Marinho 93687    */
/*          Joao Domingos 93726    */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*class Vertex {

    private:
        int grade;

    public:
        Vertex(int grade) {
            this->grade = grade;
        }

        void changeGrade(int g) {
            grade = g;
        }
}; */

class DirectedGraph {

    private:
        int vNumber;
        vector<int>* adj;

    public:
        DirectedGraph(int vNumber) {
            this->vNumber = vNumber;

            adj = new vector<int>[vNumber];
        }

        void addEdge(int vertex, int edge) {
            adj[vertex].push_back(edge);
        }

        void SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[], int* grades, int* SCCs) { 
        
            int time = 0, w = 0, x = 0, maxGrade = 0, y;

            disc[u] = low[u] = ++time; 
            st->push(u); 
            stackMember[u] = true; 
        
            vector<int>::iterator i; 
            for (i = adj[u].begin(); i != adj[u].end(); ++i) { 
                int v = *i;   
            
                if (disc[v] == -1) { 
                    SCCUtil(v, disc, low, st, stackMember, grades, SCCs); 
                    low[u]  = min(low[u], low[v]); 
                } 
    
                else if (stackMember[v] == true) 
                    low[u]  = min(low[u], disc[v]); 
            }   
            if (low[u] == disc[u]) {
                while (st->top() != u) { 
                    w = (int) st->top(); 
                    SCCs[x++] = w;
                    stackMember[w] = false;
                    st->pop(); 
                } 
                w = (int) st->top(); 
               
                stackMember[w] = false;
                SCCs[x++] = w;

                if (grades[w -1] > maxGrade)
                    maxGrade = grades[w - 1];

                st->pop(); 
            }
            // for (y = 0; )

           
            // while (y-- != -1)
            //     SCCs[y] = -1;

        }

        void SCC(int* grades) { 
            int *disc = new int[vNumber]; 
            int *low = new int[vNumber]; 
            bool *stackMember = new bool[vNumber]; 
            stack<int> *st = new stack<int>(); 
            int *SCCs = new int(vNumber);
    
            for (int x = 0; x < vNumber; x++) { 
                disc[x] = -1; 
                low[x] = -1; 
                stackMember[x] = false; 
                SCCs[x] = -1;
            }

            for (int x = 0; x < vNumber; x++) 
                if (disc[x] == -1) 
                    SCCUtil(x, disc, low, st, stackMember, grades, SCCs); 
            
            //delete?
        } 

};

int main(int argc, char* argv[]) {

    int vertexes, edges, mark, *grades, s1, s2, x = 0;

    scanf("%d,%d", &vertexes, &edges);

    DirectedGraph graph(vertexes);

    grades = new int[vertexes]; //fazer delete

    while (vertexes-- != 0) {
        scanf("%d", &mark);
        grades[x++] = mark;
    }

    while (edges-- != 0) {
        scanf("%d %d", &s1, &s2);
        graph.addEdge(s1, s2);
    }

    delete(grades); // loop?

    exit(EXIT_SUCCESS);
}