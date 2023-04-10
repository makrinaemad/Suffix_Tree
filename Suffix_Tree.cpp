#include <iostream>
#include <cstring>
#define ARR_SIZE 256

using namespace std;


class Suffix_Node
{
public:
int start;
int* end;
int index;
Suffix_Node *children[ARR_SIZE];
Suffix_Node *link;

void print(){
cout<<start<<endl;
cout<<*end<<endl;
cout<<index<<endl;

}

Suffix_Node(int s,int *e)
{
this->start = s;
this->end = e;
this->index = -1;
for(int i=0;i<ARR_SIZE;i++)
{
this->children[i] = nullptr;
}
}


~Suffix_Node(){

}
};


class     SuffixTree
{
public:
Suffix_Node *Root ;
Suffix_Node *PreviousNode;
char* txt_input =new char[1000];
int sizeOfSubStr ;

int remaining ;
Suffix_Node *ACTIVE;
int active_edge,active_len;

int END ;
int *root_end,*split;
int size;      //1000

int * listOfIndex = new int[1000];

SuffixTree( char* txt_input)//constructor to initialize varibles
{
this->txt_input = txt_input;
Root = NULL;

remaining =0;

active_len = 0;
active_edge = -1;
ACTIVE = nullptr;

END =-1;
sizeOfSubStr=-1;
size=-1;

PreviousNode = NULL;
root_end = nullptr;
split= nullptr;

build();
delete[] listOfIndex;            //destructor


}

SuffixTree( char* file, char* query)
{
int lenf = strlen(file);
file[lenf] = '@';

int lenq = strlen(query);              //add unique sympol $ when search about query
file[lenq] = '$';


this->txt_input = strcat(file,query);
this->sizeOfSubStr = strlen(file);
Root = nullptr;

remaining =0;

active_len = 0;
active_edge = -1;
ACTIVE = nullptr;

END =-1;
sizeOfSubStr=-1;
size=-1;

PreviousNode = nullptr;
root_end = nullptr;
split= nullptr;

//build();

delete[] listOfIndex;            //destructor
int * listOfIndex = new int[1000];


}


int len_Edge (Suffix_Node* Node)
{
if(Node == Root)
{
return 0;
}
else return *((Node->end)-(Node->start))+1;
}

Suffix_Node* createNewNode(int s,int *e)
{
Suffix_Node *Node = new Suffix_Node(s,e);
Node->link =Root ;

return Node;
}

bool Walk_down(Suffix_Node *node)
{
if(active_len >= len_Edge(node))
{
/*if the active length >edge length
we walk down the current node to update the active node**/
active_edge += len_Edge(node);
active_len-= len_Edge(node);
ACTIVE = node;
return 1;
}
return 0;
}

void StartIteration(int i)
{
remaining ++;//increse the remaing nodes when we find path between chracter and active point
END = i;//set end equal to number of iteration

PreviousNode = NULL;//swt the previous node to null before every iteration
while (remaining>0)
{//if active length equals zero we look for current chracter from root
if(active_len== 0) active_edge = i;//if current character from root is null ->we create anew leaf node with current chracter from leaf

if(ACTIVE->children[txt_input[active_edge]] != NULL)//if current character from root is null ->>we increment active length by one
{
Suffix_Node * NextNode;
NextNode = ACTIVE->children[txt_input[active_edge]];
if (Walk_down(NextNode))
continue;
if(txt_input[NextNode->start + active_len] == txt_input[i])
{
if(PreviousNode != NULL && ACTIVE !=Root)//if another internal node was created in last extension of this phase then suffix link of that
//node will be this node.
{
PreviousNode->link = ACTIVE;
PreviousNode =NULL;
}
active_len++;
break;
}

split = new int; //end of split
*split = NextNode->start + active_len -1;

Suffix_Node *SPLIT = createNewNode(NextNode->start,split);

ACTIVE->children[txt_input[active_edge]]=SPLIT;
SPLIT->children[txt_input[i]]= createNewNode(i,&END);

NextNode->start += active_len;
//set this as previous Node and if new internalNode is created in next extension of this iteration
//then point suffix of this node to that node. set suffix of this node to root.
SPLIT->children[txt_input[NextNode->start]]=NextNode;

if(PreviousNode != NULL)
//if another internal node was created in last extension of this phase then suffix link of that
//node will be this node.

{
PreviousNode->link = SPLIT;
}
PreviousNode =SPLIT;


}
else
{
ACTIVE -> children[txt_input[active_edge]] = createNewNode(i, &END);
if(PreviousNode != NULL)
{
PreviousNode->link = ACTIVE;
PreviousNode =NULL;
}

}
remaining--;
if(ACTIVE == Root && active_len>0)    //if active node is root then increase active index by one and decrease active length by 1

{
active_len--;
active_edge= i -remaining+1;//if active node is root then increase active index by one and decrease active length by 1


}
else if(ACTIVE != Root)//if active node is not root then follow suffix link
{
ACTIVE = ACTIVE->link;
}


}




}

void Set_Indeces(Suffix_Node* Curr_Node, int value) {
int i;

if (Curr_Node == NULL) return;

for (i = 0; i < ARR_SIZE; i++) {
    if (Curr_Node->children[i] != NULL) {
        int edge_len = *(Curr_Node->children[i]->end) - (Curr_Node->children[i]->start) + 1;

        Set_Indeces(Curr_Node->children[i], value + edge_len);
    }
}
Curr_Node->index = size - value;

/*int j;
for (j = Curr_Node->start; j < strlen(txt_input); j++) {
    if (j != -1)
    {
        cout << txt_input[j];
    }

}
if (j <= strlen(txt_input))
    cout << "(" << Curr_Node->index << ")" << endl;*/

}
void build()
{
size = strlen(txt_input);//set size equal to input size
root_end = new int;
*root_end = - 1;

Root = createNewNode(-1, root_end);//create root and set its start equal to -1

ACTIVE = Root;
for (int i=0; i<size; i++)//loop through string to start each new iteration
StartIteration(i);
int h=0;
Set_Indeces(Root,h);//walk through tree to set indicies

}
void Search(char* sub)
{
check(sub);
}
int t_edge(char* str, int idx, int start, int end)
{
int k = 0;
for (k = start; k <= end && str[idx] != '\0'; k++, idx++)
{
if (txt_input[k] != str[idx])
return -1;  // mo match
}
if (str[idx] == '\0')
return 1;  // match
return 0;  // more characters yet to match
}
int d_T_Cleaf(Suffix_Node* n)
{
if (n == NULL)
return 0;
if (n->index > -1)
{
cout << "\nposition: " << n->index << " inx\n";
return 1;
}
int count = 0;
//  int i = 0;
for (int i = 0; i < ARR_SIZE; i++)
{
if (n->children[i] != NULL)
{
count += d_T_Cleaf(n->children[i]);
}
}
// cout<<"\ncount= "<< count<<;
return count;
}

int Cleaf(Suffix_Node* n)
{
if (n == NULL)
return 0;
return  d_T_Cleaf(n);
}
int d_T(Suffix_Node* n, char* str, int idx)
{
if (n == NULL)
{
return -1; // no match
}
int res = -1;
if (n->start != -1)
{
res = t_edge(str, idx, n->start, *(n->end));
if (res == -1)  //no match
return -1;
if (res == 1) //match
{

Cleaf(n);
return 1;
}
}

idx = idx + len_Edge(n);
if (n->children[str[idx]] != NULL)
return d_T(n->children[str[idx]], str, idx);
else
return -1;

}
void check(char* str)
{
int res = d_T(Root, str, 0);
if (res == 1)
printf("\nPattern <%s> is a Substring\n", str);
else
printf("\nPattern <%s> is NOT a Substring\n", str);
}

~    SuffixTree(){//destructor of tree

}

};





int main()
{
// Construct a suffix tree containing all suffixes of "bananabanaba$"

//            0123456789012
SuffixTree t("bananabanaba$");

t.Search("n");
t.Search("a");
t.Search("na");
t.Search("bana");


return 0;
}