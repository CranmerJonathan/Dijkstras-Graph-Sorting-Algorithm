//Name: Jonathan Cranmer & ASU ID: 1221599600

struct VERTEX;
struct ADJLIST;

struct ADJLIST{
    int vertexName;
    int index;
    VERTEX *u;
    VERTEX *v;
    float w;
    ADJLIST *adjList;
};

struct VERTEX{
    int vertexName;
    char color[10];
    int index;
    VERTEX* pi;
    int position;
    float d;
    ADJLIST *adjList;
};

class Heap{
  private:
    int size;
    VERTEX** vertexes;
    
    int parent(int);
    int left(int);
    int right(int);
    void printVertex();
    void minHeapify(int, VERTEX** &arr);
  public:
    Heap(int);
    ~Heap();
    void insert(VERTEX*, float);
    void decreaseKey(int, float);
    int getSize();
    VERTEX** getVertexes();
    VERTEX* extractMin();
};