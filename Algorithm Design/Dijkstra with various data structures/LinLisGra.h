#include <iostream>
using namespace std;
#define INF 999999999
/*
 * Link
 */ 
struct Link
{
    int to;
    int attribute;           // attribute could be weight, distance, etc.
    struct Link* nextLink;
};
 

// Last Link List
  
struct LastList
{
    struct Link *head;
};
 
class LinLisGra
{
    private:
        string INFs;
        int VERT;              // number of vertices
        struct LastList* le;  // Last Link List

    public:
        /*
         * Constructors
         */
        LinLisGra(){}
        LinLisGra(int VERT)
        {
            this->INFs = "INF";
            this->VERT = VERT;
            this->le = new LastList[VERT];
            for (int i = 0; i < this->VERT; ++i)
                this->le[i].head = NULL;
        }

        /*
         * Destructors
         */
        ~LinLisGra()
        {
            // delete le;
        }

        /*
         * Creating New Link
         */ 
        Link* newLink(int to, int attribute)
        {
            Link* e = new Link;
            e->to = to;
            e->attribute = attribute;
            e->nextLink = NULL;
            return e;
        }

        /*
         * Adding Undirected Link (<->) to Graph 
         * with default attribute/weight value
         */
        void addUndirectedLink(int from, int to)
        {
            // Adding the Link to the destination vertix
            addLink(from, to, 1);
            // Adding the Link to the source vertix
            addLink(to, from, 1);
        }

        /*
         * Adding Undirected Link (<->) to Graph 
         * with a specific attribute/weight value
         */
        void addUndirectedLink(int from, int to, int attribute)
        {
            // Adding the Link to the destination vertix
            addLink(from, to, attribute);
            // Adding the Link to the source vertix
            addLink(to, from, attribute);
        }

        // Adding a  Link (->) to Graph with default attribute/weight value
         
        void addLink(int from, int to)
        {
            addLink(from, to, 1);
        }

        //Adding a Link (->) to Graph with a specific attribute/weight value
        void addLink(int from, int to, int attribute)
        {
            {
                
                Link* e = newLink(to, attribute);
                e->nextLink = this->le[from].head;
                le[from].head = e;
            }
        }

	    // Obtaining Weight of a specific Link
	    
        int getAttribute(int from, int to)
        {
            if(from == to) return 0; // link with itself.
            
            for(Link* e = this->le[from].head; e != NULL; e = e->nextLink)
            {
                if(e->to == to)
                    return e->attribute;
            }
            return INF;
        }

        // Setting Weight of a specific Link
        
        void setAttribute(int from, int to, int attribute)
        {
            bool done = false;
            if(from == to) return; // none link with itself.
            
            for(Link* e = le[from].head; e != NULL; e = e->nextLink)
            {
                if(e->to == to){
                    e->attribute = attribute;
                    done = true;
                }
            }
            if(!done){
                addUndirectedLink(from, to, attribute);
                done = true;
            }

            for(Link* e = le[to].head; e != NULL; e = e->nextLink)
            {
                if(e->to == from)
                    e->attribute = attribute;
            }
        }

        /*
         * Print the graph
         */
        void printWeight()
        {
            printWeight(false);
        }
        void printWeight(bool all)
        {
            for (int i = 0; i < this->VERT; ++i)
            {
                Link* e = this->le[i].head;
                cout << "V" << i + 1 << ": ";
                bool pv = false, has_child = false;

                while (e != NULL)
                {
                    if(all && !pv && i < e->to){
                        cout << i + 1 << "(0) - ";
                        pv = true;
                    }
                    cout << e->to + 1 << "(";
                    if(e->attribute == INF)
                        cout << this->INFs;
                    else
                        cout << e->attribute;
                    cout << ")";
                    e = e->nextLink;
                    if(e != NULL) cout << " - ";
                    if(!has_child) has_child = true;
                }
                if(all && !pv)
                {
                    if(has_child)
                        cout << " - ";
                    cout << i + 1 << "(0)";
                    pv = true;
                }
                cout << endl;
            }
        }

        /*
         * copy this Linked List Graph to another one
         */
        LinLisGra* copy() 
        { 
            LinLisGra* graph = new LinLisGra(this->VERT);

            for (int i = 0; i < graph->VERT; ++i)
            {
                Link* e = this->le[i].head;
                copyLinkReverse(graph, i, e);
            }

            return graph;
        }

        /* 
         * Recursive Function to copy all vertix's Links in reverse way
         */
        void copyLinkReverse(LinLisGra* graph, int v, struct Link* e)
        {
            // Base case  
            if (e == NULL) return;
         
            copyLinkReverse(graph, v, e->nextLink);
            graph->addLink(v, e->to, e->attribute);
        }

        const LastList* getLastLinks() const
        {
            return le;
        }
};
