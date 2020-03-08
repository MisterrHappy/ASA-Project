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

        void SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]) { 
        
            int time = 0; 
    
            disc[u] = low[u] = ++time; 
            st->push(u); 
            stackMember[u] = true; 
        
            vector<int>::iterator i; 
            for (i = adj[u].begin(); i != adj[u].end(); ++i) { 
                int v = *i;   
            
                if (disc[v] == -1) { 
                    SCCUtil(v, disc, low, st, stackMember); 

                    low[u]  = min(low[u], low[v]); 
                } 
    
                else if (stackMember[v] == true) 
                    low[u]  = min(low[u], disc[v]); 
            } 
            int w = 0;   
            if (low[u] == disc[u]) { 
                while (st->top() != u) { 
                    w = (int) st->top(); 
                    cout << w << " "; 
                    stackMember[w] = false; 
                    st->pop(); 
                } 
                w = (int) st->top(); 
                cout << w << "\n"; 
                stackMember[w] = false; 
                st->pop(); 
            } 
        }

        void SCC() { 
            int *disc = new int[vNumber]; 
            int *low = new int[vNumber]; 
            bool *stackMember = new bool[vNumber]; 
            stack<int> *st = new stack<int>(); 
    
            for (int i = 0; i < vNumber; i++) { 
            disc[i] = -1; 
            low[i] = -1; 
            stackMember[i] = false; 
        } 
            for (int i = 0; i < vNumber; i++) 
                if (disc[i] == -1) 
                    SCCUtil(i, disc, low, st, stackMember); 
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

    exit(EXIT_SUCCESS);
}