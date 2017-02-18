#define TASKNAME ""
#include <bits/stdc++.h>
#include <unordered_map>

#define MAXN int(1e3 + 10)
#define INF int(1e9)
#define pb push_back
#define mp make_pair
#define sz(A) (int)(A).size()
#define pi 3.1415926535897932384626433832795
#define sqr(a) ((a) * (a))
#define out(x) cout<<(x)<<" " << "\n"
#define DB(x) cerr<<#x<<" = "<<(x)<<"\n"
#define DB2(a,b)   cerr<<#a<<"="<<(a)<<", "<<#b<<"="<<(b)<<"\n"

using namespace std;

const int SIZE_POPULATION = 10;
const int SIZE_SQUARE = 40;
const int NUMBER_VERTEX = 60;

struct point{
  int x, y;
};


class individual{
  public:
   int edge_number, vertex_number;
   unordered_map<int, point> nodes;
   vector<pair<int, int> >edges;
   vector<int> graph[NUMBER_VERTEX];
   double min_dist[NUMBER_VERTEX];
   double minimum_dist_sum = 0, min_dist_node = 0, min_edge = 0, deviation = 0, crossings = 0;
   individual(unordered_map<int, point>, vector<pair<int, int> >, vector<int>[60], int);
   long long fitness;
  private:
   double get_fitness(){
      minimum_node_distance_sum();
      minimum_node_distance();
      edge_length_deviation();
      number_crossings();
      double expr = 2 * minimum_dist_sum;
      expr += (-2) * deviation;
      expr += (-2.5) * (deviation/min_dist_node);
      expr += (0.25) * (vertex_number * min_dist_node * min_dist_node);
      expr -= (crossings * SIZE_SQUARE * SIZE_SQUARE);
      return expr;
   }

   void minimum_node_distance_sum();
   void minimum_node_distance();
   void edge_length_deviation();
   void number_crossings();
};

individual::individual(unordered_map<int, point> map_nodes, vector<pair<int, int> >new_edges, vector<int>new_graph[NUMBER_VERTEX], int cnt){
  nodes = map_nodes;
  edges = new_edges;
  for(int i = 0; i < NUMBER_VERTEX; i++)
    graph[i] = new_graph[i];
  vertex_number = cnt;
  edge_number = sz(edges);
}


double dist(point a, point b){
  return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// set double sum_min_dist 
void individual:: minimum_node_distance_sum(){
  double sum_min_dist = 0;
  double global_min_edge = INF;
  for(int i = 0; i < NUMBER_VERTEX; i++){
    double min_dist_node = INF;
    for(int j = 0; j < sz(graph[i]); j++){
      int u = graph[i][j];
      int v = i;
      point one, two;
      one.x = nodes[u].x;
      one.y = nodes[u].y;
      two.x = nodes[v].x;
      two.y = nodes[v].y;
      min_dist_node = min(min_dist_node, dist(one, two));
    }
    if(min_dist_node >= INF)  continue;
    else{ 
      sum_min_dist += min_dist_node;
      min_dist[i] = min_dist_node;
      global_min_edge = min(min_dist_node, global_min_edge);
    }
  }    
  minimum_dist_sum = sum_min_dist;
  min_edge = global_min_edge; 
}

void individual:: minimum_node_distance(){
  min_dist_node = vertex_number *  min_edge * min_edge; 
}


void individual::edge_length_deviation(){
  double sum = 0;
  for(int i = 0; i < sz(edges); i++){
    int u = edges[i].first, v = edges[i].second;
    point one, two;
    one.x = nodes[u].x;
    one.y = nodes[u].y;
    two.x = nodes[v].x;
    two.y = nodes[v].y;
    double length = dist(one, two);
    sum += (length - min_edge) *  (length - min_edge);
  }
  deviation = sqrt(sum * 1.0 / double(edge_number));
}   


inline int area (point a, point b, point c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
 
inline bool intersect_1 (int a, int b, int c, int d) {
  if (a > b)  swap (a, b);
  if (c > d)  swap (c, d);
  return max(a,c) <= min(b,d);
}
 
bool intersect (point a, point b, point c, point d) {
  return intersect_1 (a.x, b.x, c.x, d.x)
    && intersect_1 (a.y, b.y, c.y, d.y)
    && area(a,b,c) * area(a,b,d) <= 0
    && area(c,d,a) * area(c,d,b) <= 0;
}

void individual::number_crossings(){
   int cnt_crossings = 0;
   for(int i = 0; i < sz(edges); i++){
     for(int j = i + 1; j < sz(edges); i++){
        point p1, p2, p3, p4;
        int u = edges[i].first, v = edges[i].second;
        int u1 = edges[j].first, v1 = edges[j].second;
        p1 = {nodes[u].x, nodes[u].y};
        p2 = {nodes[v].x, nodes[v].y};
        p3 = {nodes[u1].x, nodes[u1].y};
        p4 = {nodes[v1].x, nodes[v1].y};
        cnt_crossings += intersect(p1, p2, p3, p4);
     }  
   }
   crossings = cnt_crossings;
}


int edge_number, vertex_number, num, x, y, u, v; 
bool nodes[NUMBER_VERTEX];
vector<individual> population;
vector<pair<int, int> >new_edges;
vector<int> g[NUMBER_VERTEX];

/* TODO
1) make points with different coords


*/


int main()
{
  freopen("output_finish.txt", "w", stdout);
  freopen("input.txt", "r", stdin);
  cin >> vertex_number;
  // read edges
  for(int i = 0; i < vertex_number; i++){
     cin >> u >> v;
     nodes[u] = 1;
     nodes[v] = 1;
     g[u].pb(v);
     new_edges.pb(mp(u, v));   
  }

  // first 10 individuals aka first population
  for(int i = 0; i < SIZE_POPULATION; i++){
    unordered_map<int, point>cur_map;
    for(int vertex = 1; vertex < NUMBER_VERTEX; vertex++){   
         int x = rand() % SIZE_SQUARE + 1, y = rand() % SIZE_SQUARE + 1;
         if(nodes[vertex])
            cur_map[vertex] = {x, y}; 
    }
    population.pb(individual(cur_map, new_edges, g,  vertex_number));
  }
  return 0;
}