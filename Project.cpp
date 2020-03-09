/* First ASA project               */
/* Authors: Andre Marinho 93687    */
/*          Joao Domingos 93726    */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class DirectedGraph {

    private:
        int vNumber;
        vector<int>* adj;
        vector<int>* SCCs;

    public:
        DirectedGraph(int Number) 
        : vNumber(Number), adj(new vector<int>[Number]), SCCs(new vector<int>[Number]) {}

        ~DirectedGraph() {
            delete[]adj;
            delete[]SCCs;
        }

        void addEdge(int vertex, int edge) {
            adj[vertex - 1].push_back(edge - 1);
        }

        void SCCSubBuild(int u, int disc[], int low[], stack<int> &st, bool stackMember[], int grades[], int &SCCPos) { 
        
            static int time = 0;
            int w = 0, maxGrade = 0;

            disc[u] = low[u] = ++time; 
            st.push(u); 
            stackMember[u] = true; 
        
            vector<int>::iterator i; 
            for (i = adj[u].begin(); i != adj[u].end(); ++i) { 
                int v = *i;   
            
                if (disc[v] == -1) { 
                    SCCSubBuild(v, disc, low, st, stackMember, grades, SCCPos);
                    low[u]  = min(low[u], low[v]); 
                } 
    
                else if (stackMember[v] == true) 
                    low[u] = min(low[u], disc[v]);

                else if (disc[v] != -1) 
                    grades[u] = (grades[u] < grades[v]) ? grades[v] : grades[u];
                    
            }

            if (low[u] == disc[u]) {
                while (st.top() != u) { 
                    
                    w = (int) st.top(); 

                    stackMember[w] = false;
                    SCCs[SCCPos].push_back(w);

                    maxGrade = (grades[w] > maxGrade) ? grades[w] : maxGrade;

                    st.pop(); 
                } 
                w = (int) st.top(); 
               
                stackMember[w] = false;

                SCCs[SCCPos].push_back(w);

                maxGrade = (grades[w] > maxGrade) ? grades[w] : maxGrade;

                st.pop(); 
            }
        
            for (i = SCCs[SCCPos].begin(); i != SCCs[SCCPos].end(); ++i) {
                int g = *i;
                grades[g] = maxGrade;
            }

            if (st.empty() == false && grades[(int) st.top()] < maxGrade)
                grades[(int) st.top()] = maxGrade;

            ++SCCPos;
        }

        void SCCBuild(int* grades) { 
            int SCCPos = 0, *disc = new int[vNumber], *low = new int[vNumber]; 
            bool *stackMember = new bool[vNumber]; 
            stack<int> st; 
    
            for (int x = 0; x < vNumber; x++) { 
                disc[x] = -1; 
                low[x] = -1; 
                stackMember[x] = false; 
            }

            for (int x = 0; x < vNumber; x++) {
                if (disc[x] == -1) 
                    SCCSubBuild(x, disc, low, st, stackMember, grades, SCCPos);
            }
            delete[]disc;
            delete[]low;
            delete[]stackMember;
        } 

};

int main(int argc, char* argv[]) {

    int vertexes, edges, mark, *grades, s1, s2, x = 0;
    int graphSize;

    scanf("%d,%d", &vertexes, &edges);
    graphSize = vertexes;

    DirectedGraph graph(vertexes);

    grades = new int[vertexes];

    while (vertexes-- != 0) {
        scanf("%d", &mark);
        grades[x++] = mark;
    }

    while (edges-- != 0) {
        scanf("%d %d", &s1, &s2);
        graph.addEdge(s1, s2);
    }

    graph.SCCBuild(grades);

    for (x = 0; x < graphSize; x++)
        cout << grades[x] << "\n";

    delete[]grades;

    exit(EXIT_SUCCESS);
}