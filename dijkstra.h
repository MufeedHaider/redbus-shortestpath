#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<stack>
using namespace std;


#define inf 999999999


struct path{
  
   int distance=0;
  
   stack <string> busstops;

};

class graph;

class adjlist {
  public:
  
  string name;
  
  int dis;
  
  adjlist * n;
  
  adjlist(string a,int b){
  
    // name = "";
    // dis =0;
  
    n=NULL;

    name=a;
  
    dis=b;
  
  }
  
//   void add(string a,int b){
//     name=a;
//     dis=b;
//   }

};

class node {
  
   public:
  
    string name;         //name
  
    bool v;              //visited
  
    int  dis;            // distance
  
    node *pre;          // previous node 
  
    node *n;             //next stop
  
    adjlist *als,*all;  //start and last of the adjacent list
  
    node (){}
  
    node (string a):name(a), v(0), dis(inf), pre(NULL){
  
         n=NULL;
         als=NULL;
         all=NULL;
  
    }

    void addlist(string a,int b)
    {
    
        adjlist *t;
    
        t=new adjlist(a,b);
    
        if(als==NULL){
    
            als=t;
    
            all=als;        
    
        }
        else {
    
           all->n=t;
    
           all=t;
    
        }

    }

    ~node(){
    
        adjlist *t=als;
    
        while(t!=NULL){
    
           als=als->n; 
           delete (t);
           t=als;
    
        }
    
    }




};

class linkedlist{
    
    node *stops,*last;

    int total=0;

    public:
    
    linkedlist (){
    
        stops=NULL; 
        last =NULL;
    
        }
    
    void addstop(string a) {
   
        total++;
   
        node *t;
   
        t=new node(a);
    
        if(stops==NULL){
           
            stops=t;
            last=stops;        
       
        }

        else {
       
           last->n=t;
           last=t;
       
        }

    }

    void reset(){
       
        node *t=stops;
       
        while (t!=NULL)
        {
       
            t->v=0;
            t->dis = inf;
            t->pre = NULL;
            t=t->n;
       
        }
    }
    
    ~linkedlist(){
        
        node *t=stops;
        
        while(t!=NULL){
           stops=stops->n; 
           delete (t);
           t=stops;
        
        }

    }

     
     
     void input(int a,int b,int c){
     
        string t1;
     
        node *t2=stops,*t3=stops;

        for(int c=0;c<b;c++)t2=t2->n;  //adress of node b
     
     
        for(int c=0;c<a;c++)t3=t3->n;  //adress of node a
     
        t1=t2->name;
     
        t3->addlist(t1,c);
     
        t1=t3->name;
     
        t2->addlist(t1,c);
      

    }  

    friend class graph; 
    
    friend int main();


};

class graph{

  


   linkedlist bus;
  
   public:

    graph(){};

    graph(int n){
       
       int a,b,dis;

     //  matrix = vector<vector<int>>(n, vector<int>(n, 0));
       string ans;
      
       for(int c=0;c<n;c++){
        cout<<"enter name of node "<<c+1<<endl;
        cin>>ans;
        bus.addstop(ans);
       }
      
       // ***********************************
      
       cout<<"\nEnter the connected bus stops as (1 2) : ";
	   do
	   {
	
    	l1:
		cout<<"\nEnter the bus stops : ";
		cin>>a>>b;
		if(a<0 || a>bus.total-1 || b<0|| b>bus.total-1)
		{
			cout<<"\n** Invalid Input, Re-enter the vertices **\n";
			goto l1;
		}

        cout<<"\nEnter the distance in kms : ";
		cin>>dis;

		//linking the nodes of the graph
        bus.input(a,b,dis);
        
        cout<<"\ny to add more .... n to exit : ";
		cin>>ans;

		
	}  while(ans=="y");
        } 


    void readfromfile(){
        
    fstream inputFile("pathinfo.txt");
    int a,b,c;

    if (!inputFile.is_open()) {
        cerr << "Error opening file for reading." << endl;
    }

    string line;
	getline(inputFile, line);
    a=stoi(line);
    
	for(int cc=0;cc<a;cc++){

        getline(inputFile, line);
        bus.addstop(line);

    }

	
    getline(inputFile, line);
    
    int aa=stoi(line);
	
    for(int cc=0;cc<aa;cc++){

        getline(inputFile, line);
        a=stoi(line);
        
        getline(inputFile, line);
        b=stoi(line);
        
        getline(inputFile, line);
        c=stoi(line);

        bus.input(a,b,c);
    }


    // Close the file

    inputFile.close();
    
    }    



   
   path shortestpath(int a,int b)
   {
    
    
    //reset all the nodes (visited to false and distance to inf)
    
    bus.reset();
     
     // a and b are sourse and destination
     
     node *t1=bus.stops,*t2=bus.stops;
     
     for(int c=0;c<a;c++)t1=t1->n;
     
     //distance from source to source is 0
     
     t1->dis=0;


     
      
     for(int c=1;c<bus.total;c++){
        
        int loc=normalize();
       
        //set visited flag to true
       
        t1=bus.stops; t2=bus.stops;

        for(int c=0;c<loc;c++)t1=t1->n;
       
        t1->v=1;   // t1 pointing to curr location node
        
        for(int i=0;i<bus.total;i++){
       
        //bool check=1;
        
        int dis=0; 
        
        t2=bus.stops;
        
        // node should not already be normalized
        
        for(int c=0;c<i;c++)t2=t2->n;
        
        adjlist *ptr=t1->als;

        //path should exist
        
        while(ptr!=NULL)
        {
            if(ptr->name==t2->name)
            {
              dis=ptr->dis;
              break;
            }
            else ptr=ptr->n;
        }
        
        if(!t2->v && dis && t1->dis != inf && (t1->dis + dis)<t2->dis){

          t2->dis=(t1->dis + dis);
          t2->pre=t1;

        }
        }
     }

     t1=bus.stops;
     
     
     for(int c=0;c<b;c++)t1=t1->n;

      path path;
      if(t1->dis==inf)return path;
      else {
        path.distance=t1->dis;
        
        path.busstops.push(t1->name);

        node * t=t1->pre;
        
        while(t!=NULL)
        {
        path.busstops.push(t->name);
        t=t->pre;
        }
        
        return path;

      }
    
   }


   int normalize(){
    //find bus stop with min distance to normalize it
    int min=inf , mindex=0;
    node *t=bus.stops;
    for (int c=0;c<bus.total;c++){
       if(t->v==0 && t->dis <= min){
        min = t->dis;
        mindex=c;
       } 
	   t=t->n;       
    }
    return mindex;
   }


friend int main();

};



//int main (){
//
//    graph a;
//    a.readfromfile();
//    path b=a.shortestpath(0,2);
//    
//    cout<<b.distance<<endl;
//     cout<<b.busstops.top()<<" "; b.busstops.pop();
//     cout<<b.busstops.top()<<" "; b.busstops.pop();
//     cout<<b.busstops.top()<<" "; b.busstops.pop();
//
//   // cout<<a.bus.stops->n->pre->name<<" "<<a.bus.stops->n->n->pre->name;
//
//    
//    //cout<<"\n\n"<<a.bus.stops->pre<<"  "<<a.bus.stops->n->pre<<"  "<<a.bus.stops->n->n->pre;
//
//   //cout<<a.bus.stops->name<<"  "<<a.bus.stops->als->name<<"  "<<a.bus.stops->als->dis;
//   
//}




