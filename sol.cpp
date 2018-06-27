//car_fuel
#include <stdio.h>
#include <stdlib.h>

int min = 10000;

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Findsteps(int *arr, int *ind, int n, int pos, int diesel, int gasoline, int steps, int i){

	if (steps > min){
		return;
	}
	if (i == n){
		if (steps < min)
			min = steps;
		return;
	}

	if (arr[ind[i]] == 1){
		if (gasoline){
			if (ind[i] > pos)
				steps += ind[i] - pos;
			else
				steps += pos - ind[i];
			gasoline--;

			//if(gasoline == 1)
			//   Findsteps(arr,ind,n,n,1,1,steps+n-ind[i],i+1);
			//Findsteps(arr,ind,n,n,2,0,steps+n-ind[i],i+1);
		}
		else{
			steps += pos + 1 + ind[i] + 1;
			gasoline += 2;
			diesel = 0;
			gasoline--;

		}
		pos = ind[i];
	}
	else{
		if (diesel){
			if (ind[i] > pos)
				steps += ind[i] - pos;
			else
				steps += pos - ind[i];
			diesel--;
		}
		else{
			steps += n - pos;
			gasoline = 0;
			diesel += 2;
			steps += n - ind[i];
			diesel--;
			//if(diesel == 1)
			//   Findsteps(arr,ind,n,-1,1,1,steps+ind[i]+1,i+1);
			//Findsteps(arr,ind,n,-1,0,2,steps+ind[i]+1,i+1);
		}
		pos = ind[i];
	}
	Findsteps(arr, ind, n, pos, diesel, gasoline, steps, i + 1);
	Findsteps(arr, ind, n, -1, 0, 2, steps + ind[i] + 1, i + 1);
	Findsteps(arr, ind, n, n, 2, 0, steps + n - ind[i], i + 1);
}

void permute(int *arr, int *ind, int first, int last){
	if (first == last){
		Findsteps(arr, ind, last + 1, -1, 0, 2, 0, 0);
		return;
	}
	for (int i = first; i <= last; i++){
		swap(ind + first, ind + i);
		permute(arr, ind, first + 1, last);
		swap(ind + first, ind + i);
	}
}


int main() {
	int n;
	scanf("%d", &n);
	int *arr = (int *)malloc(sizeof(int)*n);
	int *ind = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i<n; i++){
		ind[i] = i;
		scanf("%d", &arr[i]);
	}
	permute(arr, ind, 0, n - 1);
	printf("%d", min);
	return 0;
}


//shooting balloon

#include<iostream>
using namespace std;
int balloon[100];

int getmaxpoint(int l,int r,int n)
{
  int maxscore=0;
  for(int i=l+1;i<r;i++)
  {
    int current_sum=0;
    current_sum=getmaxpoint(l,i,n)+getmaxpoint(i,r,n);
    if(l==0 && r==n+1)
    current_sum=current_sum+balloon[i];
    else
    current_sum=current_sum+balloon[l]*balloon[r];
    if(current_sum>maxscore)
    maxscore=current_sum;
  }
  return maxscore;
}



int main()
{
  int t,n;
  cin>>t;
  while(t--)
  {
    cin>>n;
    balloon[0]=1;
    balloon[n+1]=1;
    for(int i=1;i<=n;i++)
    {
      cin>>balloon[i];
    }
    
    int ans=getmaxpoint(0,n+1,n);
    cout<<ans<<endl;
  }
  return 0;
  
  
}


//airplane

#include<iostream>
using namespace std;
int arr[13][5];
int b[5][5];


void detonate(int row)
{
	for (int i = row; i > row - 5; i--)
	{
		for (int j = 0; j < 5; j++)
		{
			b[row - i][j] = 0;
			if (arr[i][j] == 2 && i >= 0)
			{
				b[row - i][j] = 2;
				arr[i][j] = 0;
			}
		}
	}
}

void undetonate(int row)
{
	for (int i = row; i > row - 5; i--)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i >= 0 && b[row - i][j] == 2)
			{
				arr[i][j] = 2;
			}
		}
	}
}

void getmaxcoins(int pos, int coins, int n, int &maxcoins)
{
	if (pos<0 || pos>4 || coins < 0)
		return;
	if (arr[n - 1][pos] == 2)
		coins--;
	else if (arr[n - 1][pos] == 1)
		coins++;
	if (n == 1)
	{
		if (coins>maxcoins)
			maxcoins = coins;
	}
	else
	{
		getmaxcoins(pos - 1, coins, n - 1, maxcoins);
		getmaxcoins(pos + 1, coins, n - 1, maxcoins);
		getmaxcoins(pos, coins, n - 1, maxcoins);
	}

}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int maxcoins = -1;
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 5; j++)
				cin >> arr[i][j];
		}
		for (int i = 0; i < 5; i++)
			arr[n][i] = 0;
		arr[n][2] = 3;
		int coins;
		for (int i = n - 1; i>0; i--)
		{
			coins = -1;
			detonate(i);
			getmaxcoins(2, 0, n, coins);
			if (coins > maxcoins)
				maxcoins = coins;
			undetonate(i);
		}

		if (maxcoins < 0)
			cout << -1 << endl;
		else
			cout << maxcoins << endl;

	}



}

//bipartite cities

#include<iostream>
#include<string.h>

using namespace std;
int arr[100][2];
int matrix[100][100];
int colors[100];
int flag;
int n;
void bipartite(int index,int color)
{
  if(colors[index]==0)
    colors[index]=color;
  else if(colors[index]==color)
    return;
  else if(colors[index]!=color)
    {cout<<"not bpartite";
      flag=1;
      return;
    }
  for(int i=1;i<=n;i++)
    { int temp;
      if(matrix[index][i])
      { if(color==1)
        temp=2;
        else
        temp=1;
        bipartite(i,temp);
      }
    }
}





int main()
{ flag=0;
  int m;
  cin>>n>>m;
  memset(colors,0,n*sizeof(int));
  memset(matrix,false,n*n*sizeof(int));
  for(int i=0;i<m;i++)
  cin>>arr[i][0];
  for(int i=0;i<m;i++)
  cin>>arr[i][1];
  for(int i=0;i<m;i++)
  {
    matrix[arr[i][0]][arr[i][1]]=true;
  }
  for(int i=1;i<=n;i++)
  {
    if(colors[i]==0)
    {
      bipartite(i,1);
    }
  
  }
  for(int i=1;i<=n;i++)
  {
    if(colors[i]==1)
    cout<<i<<" ";
  }
  cout<<endl;
  for(int i=1;i<=n;i++)
  {
    if(colors[i]==2)
    cout<<i<<" ";
  }
  
  return 0;
  
}
//shopping mall

#include<iostream>
using namespace std;
int message_length[3];
int discount[3];
int customer_entry[50];
int customer_exit[50];
int min_entry_time;
int max_exit_time;
int current_start[3];
int current_end[3];
int perm[3];
int customer_discount[51];

void dfs(int &ans,int customer)
{
//	cout << "dfs " << endl;

	
	for (int i = min_entry_time; i <= max_exit_time; i++)
	{
		for (int j = i + message_length[perm[0]]; j <= max_exit_time; j++)
		{
			for (int k = j + message_length[perm[1]]; k <= max_exit_time; k++)
			{
				for (int a = 0; a < 3; a++)
				{
					current_start[a] = -1;
					current_end[a] = -1;
				}
				if (i + message_length[perm[0]] <= max_exit_time)
				{
					current_start[perm[0]] = i;
					current_end[perm[0]] = i + message_length[perm[0]];
				}
				if (j + message_length[perm[1]] <= max_exit_time)
				{
					current_start[perm[1]] = j;
					current_end[perm[1]] = j + message_length[perm[1]];
				}
				if (k + message_length[perm[2]] <= max_exit_time)
				{
					current_start[perm[2]] = k;
					current_end[perm[2]] = k + message_length[perm[2]];
				}
				int max_ans = 0;
				for (int b = 0; b < customer; b++)
				{
					customer_discount[b] = 0;
					for (int a = 0; a < 3; a++)
					{
						if (current_end[a] <= customer_exit[b] && customer_entry[b] <= current_start[a] && current_start[a] != -1 && current_end[a] != -1 && discount[a]>customer_discount[b])
						{	
							customer_discount[b] = discount[a];
						//	cout << customer_discount[b] << " "<<b<<endl;
						}
					}
					max_ans = max_ans + customer_discount[b];
				}
				
				if (max_ans > ans)
					ans = max_ans;
			/*	cout << "printing values";
				for (int b = 0; b < customer; b++)
					cout << customer_discount[b] << " " << endl;*/
			}
		}
	}
}




int main()
{
	int t,customer;
	cin >> t;
	while (t--)
	{
		min_entry_time = 60;
		max_exit_time = 0;
		cin >> customer;
		for (int i = 0; i < 3; i++)
			cin >> message_length[i];
		for (int i = 0; i < 3; i++)
			cin >> discount[i];
		for (int i = 0; i < customer; i++)
		{
			cin >> customer_entry[i];
			if (customer_entry[i] < min_entry_time)
				min_entry_time = customer_entry[i];
			int temp;
			cin >> temp;
			customer_exit[i] = temp + customer_entry[i];
			if (customer_exit[i]>max_exit_time)
				max_exit_time = customer_exit[i];
		}
		int ans = 0;
		perm[0] = 0;
		perm[1] = 1;
		perm[2] = 2;

		dfs(ans, customer);
		perm[0] = 1;
		perm[1] = 2;
		perm[2] = 0;

		dfs(ans, customer);
		perm[0] = 1;
		perm[1] = 0;
		perm[2] = 2;

		dfs(ans, customer);
		perm[0] = 0;
		perm[1] = 2;
		perm[2] = 1;

		dfs(ans, customer);
		perm[0] = 2;
		perm[1] = 1;
		perm[2] = 0;

		dfs(ans, customer);
		perm[0] = 2;
		perm[1] = 0;
		perm[2] = 1;

		dfs(ans, customer);
		cout << ans << endl;
	}
	return 0;


}

//samsung_mobile
#include<iostream>
using namespace std;
int starti,endi;
int n;
int arr[100000];
void push(int x)
{
  arr[endi]=x;
  endi++;
}
int pop()
{
  starti++;
  return arr[starti-1];
}
int size()
{
  return endi-starti;
}

int maxi(int countall[5])
{
  int minindex;
  int min=0;
  for(int i=0;i<5;i++)
  {
    if(countall[i]>=min)
    {
      min=countall[i];
      minindex=i;
    }
    cout<<countall[i]<<" ";
    
  }
  return minindex+1;
}

void dfs1(int ** matrix,int **visited,int value,int x,int y)
{
  visited[x][y]=1;
  if(x-1>=0 && visited[x-1][y]==0 && matrix[x-1][y]==matrix[x][y])
      {
        dfs1(matrix,visited,value,x-1,y);
      }
      if(x+1<n && visited[x+1][y]==0 && matrix[x+1][y]==matrix[x][y])
      {
       dfs1(matrix,visited,value,x+1,y);
      }
      if(y-1>=0 && visited[x][y-1]==0 && matrix[x][y-1]==matrix[x][y])
      {
        dfs1(matrix,visited,value,x,y-1);
      }
      if(y+1<n && visited[x][y+1]==0 && matrix[x][y+1]==matrix[x][y])
      {
        dfs1(matrix,visited,value,x,y+1);
      }
}
void dfs(int **matrix,int **visited,int x,int y,int value)
{
  matrix[x][y]=value;
  visited[x][y]=1;
    
      if(x-1>=0 && visited[x-1][y]==0 && matrix[x-1][y]==0)
      {
        dfs(matrix,visited,x-1,y,value);
      }
      if(x+1<n && visited[x+1][y]==0 && matrix[x+1][y]==0)
      {
        dfs(matrix,visited,x+1,y,value);
      }
      if(y-1>=0 && visited[x][y-1]==0 && matrix[x][y-1]==0)
      {
        dfs(matrix,visited,x,y-1,value);
      }
      if(y+1<n && visited[x][y+1]==0 && matrix[x][y+1]==0)
      {
        dfs(matrix,visited,x,y+1,value);
      }
}

int bfs(int **matrix,int **visited,int x,int y)
{ int countall[4];
  for(int i=0;i<5;i++)
  countall[i]=0;
  push(x);
  push(y);
  visited[x][y]=1;
  while(size()>0)
  {
    x=pop();
    y=pop();
    if(matrix[x][y]==0)
    {
      if(x-1>=0 && visited[x-1][y]==0)
      {
        push(x-1);
        push(y);
        visited[x-1][y]=1;
      }
      if(x+1<n && visited[x+1][y]==0)
      {
        push(x+1);
        push(y);
        visited[x+1][y]=1;
      }
      if(y-1>=0 && visited[x][y-1]==0)
      {
        push(x);
        push(y-1);
        visited[x][y-1]=1;
      }
      if(y+1<n && visited[x][y+1]==0)
      {
        push(x);
        push(y+1);
        visited[x][y+1]=1;
      }
    }
    else
    { cout<<"ekse";
      countall[matrix[x][y]-1]++;
      if(x-1>=0 && visited[x-1][y]==0 && matrix[x-1][y]==matrix[x][y])
      {
        push(x-1);
        push(y);
        visited[x-1][y]=1;
      }
      if(x+1<n && visited[x+1][y]==0 && matrix[x+1][y]==matrix[x][y])
      {
        push(x+1);
        push(y);
        visited[x+1][y]=1;
      }
      if(y-1>=0 && visited[x][y-1]==0 && matrix[x][y-1]==matrix[x][y])
      {
        push(x);
        push(y-1);
        visited[x][y-1]=1;
      }
      if(y+1<n && visited[x][y+1]==0 && matrix[x][y+1]==matrix[x][y])
      {
        push(x);
        push(y+1);
        visited[x][y+1]=1;
      }
      
      
    }
    
  }
  return maxi(countall);
}



int main()
{
  int t;
  cin>>t;
  while(t--)
  {
    cin>>n;
    int **matrix;
    int **visited;
    starti=0;
    endi=0;
    matrix=new int*[n];
    visited=new int*[n];
   for(int i=0;i<n;i++)
   {
     matrix[i]=new int [n];
     visited[i]=new int[n];
     for(int j=0;j<n;j++)
     {
       cin>>matrix[i][j];
       visited[i][j]=0;
    }
   }
   for(int i=0;i<n;i++)
   {
     for(int j=0;j<n;j++)
     {
       if(matrix[i][j]==0)
       {
         int temp=bfs(matrix,visited,i,j);
         cout<<temp<<"replace"<<endl;
         for(int a=0;a<n;a++)
          for(int b=0;b<n;b++)
          visited[a][b]=0;
          dfs(matrix,visited,i,j,temp+5);
          for(int a=0;a<n;a++)
          for(int b=0;b<n;b++)
          visited[a][b]=0;
        }
     }
   }
   
   for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      if(matrix[i][j]>5)
      matrix[i][j]=matrix[i][j]-5;
    }
  }
  
  int count=0;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      if(visited[i][j]==0)
      { count++;
      cout<<matrix[i][j]<<" "<<i<<" "<<j<<endl;
        dfs1(matrix,visited,matrix[i][j],i,j);
      }
    }
  }
   cout<<count<<endl;
   
  }
  
  
}
//interstellar

#include<iostream>
#include<climits>
using namespace std;
int k;

int mindistance(int dist[], bool mst[])
{
	int min = INT_MAX;
	int min_index ;
	for (int i = 0; i < k; i++)
	{
		if (dist[i] < min && mst[i] == false)
		{
			min = dist[i];
			min_index = i;

		}

	}
	return min_index;
}

int abs(int a)

{
	if (a < 0)
		return -1 * a;
	else
		return a;
}
int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}
void printsolution(int dist[])
{ 
	cout << dist[1] << endl;
}




void dijkstra(int graph[101][101], int source)
{
	int dist[101];
	bool mst[101];
	for(int i = 0; i < k; i++)
	{
		dist[i] = INT_MAX;
		mst[i] = false;
	}
	dist[source] = 0;
	for (int i = 0; i < k; i++)
	{
		int index = mindistance(dist, mst);
		mst[index] = true;
		for (int j = 0; j < k; j++)
		{
			if (mst[j] == false && dist[index] != INT_MAX && graph[index][j] && (dist[index] + graph[index][j] < dist[j]))
				dist[j] = graph[index][j] + dist[index];
		}
	}
	printsolution(dist);
}




int x[101];
int y[101];
int p[101];
int graph[101][101];
int main()
{


	int t,n;
	cin >> t;
	while (t--)
	{
		cin >> n;
		cin >> x[0] >> y[0] >> x[1] >> y[1];
		 k = 2;
		for (int i = 0; i < n; i++)
		{
			cin >> x[k] >> y[k];
			k++;
			

			cin >> x[k] >> y[k];
			cin>>p[k-1];
			k++;
		}
		for (int i = 0; i < k; i++)
		{
			//cout << "agya";
			for (int j = i + 1; j < k; j++)
			{
				graph[i][j] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
				graph[j][i] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
				if (i % 2 == 0 && j == i + 1 && i != 0)
				{
					graph[i][j] = min(graph[i][j], p[i]);
					graph[j][i] = min(graph[j][i], p[i]);
				}
			}
		}
		dijkstra(graph, 0);
	}
	
	return 0;
}


//digit jump
#include<iostream>
using namespace std;
char input[100002];
	int dp[100002];
int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}


int main()
{
	
	int t;
	cin >> t;
	while (t--)
	{
		int k = 0;
		char temp;
		cin>>input;
		for(k=0;k<10;k++)
		{
		  cout<<input[k]<<endl;
		}
		cout<<input[3]<<"sad"<<endl;
		
		int len = k;
		dp[0] = 0;
	  cout<<len<<"length"<<endl;
		int i,j;
		for ( i = 1; i < len; i++)
		{
			int flag=0;
			for ( j = 0; j <= i-1; j++)
				{ if (input[i] == input[j])
				  { flag=1;
				    break;
				   
				  }
				   cout<<input[i]<<" "<<input[j]<<endl;
				}
				if(flag==1)
				dp[i]=min(dp[j],dp[i-1])+1;
				else
				dp[i]=min(dp[j-1],dp[i-1])+1;		//cout<<dp[i]<<" i "<<dp[j]<<" j "<<dp[i-1]<<" i-1 "<<min(dp[j],dp[i-1])<<" j "<<j<<endl;
				cout<<dp[i]<<"this is dp for"<<i<<"which is "<<input[i]<<endl;
		}
		cout << dp[len-1] <<"ans"<< endl;



	}

	return 0;


}

//printing cycles
#include<iostream>
using namespace std;
int visited[101]={0};
int graph[101][101]={0};
int flag=0;
struct stacknode
{
  int value;
  struct stacknode* next;
};
typedef struct stacknode Node;




struct stack{
  
  Node* head;
};
typedef struct stack Stack;

void push(int x,Stack* s)
{
  Node* newnode=(Node*)malloc(sizeof(Node));
  newnode->value=x;
  //cout<<newnode->value;
  newnode->next=s->head;
  s->head=newnode;
  //cout<<s->head;

}
int pop(Stack* s)
{
  if(s->head==NULL)
  return -1;
  else
  {
    int y=s->head->value;
    s->head=s->head->next;
    return y;
  }
  
}
bool empty(Stack* s)
{
  if(s->head==NULL)
  return true;
  return false;
}
int temp[100];
void func(Stack* s,int until)
{ //cout<<"   kardo print until "<<until<<endl;
  
  //cout<<"Asaass";
  
 // cout<<"khali stack"<<endl;
  int y=pop(s);
 //cout<<y<<"pehla ";
  temp[y]=1;

  
  while(y!=until)
  { 
    y=pop(s);
  // cout<<y<<" y";
    temp[y]=1;
    
  }
  temp[y]=1;
  
   for(int i=0;i<100;i++)
    if(temp[i]==1)
    cout<<i<<" ";
    return;

}

void dfs(int start,int n,Stack* s)
{
 // cout<<start<<"start"<<endl;
  visited[start]=1;
  push(start,s);
  
  while(!empty(s))
  {
    int top=pop(s);
    push(top,s);
   // cout<<top<<"top"<<endl;
  for(int i=1;i<=n;i++)
  if(graph[top][i]==1)
  { if(visited[i]!=1)
    {push(i,s);
   // cout<<"pushed"<<i<<endl;
    visited[i]=1;
    }    
    else
    { if(empty(s))
  //  cout<<"kahli h starting se";
      cout<<top<<" "<<i<<endl;
      //cout<<"printing";
      func(s,i);
      flag=1;
      return;
    }
  }
  }
  
}

int main()
{
  
  
  Stack* s=(Stack*)malloc(sizeof(Stack));
  s->head=NULL;
  int n,edge;
  cin>>edge>>n;
 // cout<<edge<<n<<endl;
  for(int i=0;i<edge;i++)
  {
    int temp1,temp2;
    cin>>temp1>>temp2;
   // cout<<temp1<<temp2<<endl;
    graph[temp1][temp2]=1;
  }
  push(2,s);
int temp2=pop(s);
//cout<<temp2<<endl;
  for(int i=1;i<=n;i++)
  {//cout<<"as"<<endl;
    dfs(i,n,s);
    if(flag==1)
    return 0;
    for(int j=1;j<=100;j++)
      visited[j]=0;
      while(!empty(s))
      int y1=pop(s);
  }
  
  
  return 0;
  
}
//cpu selling

#include<iostream>
using namespace std;
int m[8][4];
int dp[100][100][100]={-1};

int func(int cpu,int memory,int board,int cpu_price,int memory_price,int models)
{
  int temp2=0;
  if(dp[cpu][memory][board]!=-1)
  return dp[cpu][memory][board];
  else
  {
    int temp1=cpu*cpu_price+memory*memory_price;
    for(int i=0;i<models;i++)
    {
      if(cpu-m[i][0]>=0 && memory-m[i][1]>=0 && board-m[i][2]>=0)
      {temp2=max(temp2,func(cpu-m[i][0],memory-m[i][1],board-m[i][2],cpu_price,memory_price,models)+m[i][3]);
      }
      
    }
  dp[cpu][memory][board]=max(temp1,temp2);
  return dp[cpu][memory][board];
  }
}
int main()
{
  int t;
  cin>>t;
  int cpu,memory,board,cpu_price,memory_price,models;
 
  while(t--)
  {
      cin>>cpu>>memory>>board>>cpu_price>>memory_price>>models;
      for(int i=0;i<models;i++)
      {
        cin>>m[i][0]>>m[i][1]>>m[i][2]>>m[i][3];
      }
      for(int i=0;i<=cpu;i++)
      {
        for(int j=0;j<=memory;j++)
        {
          for(int k=0;k<=board;k++)
          dp[i][j][k]=-1;
        }
      }
      cout<<func(cpu,memory,board,cpu_price,memory_price,models)<<endl;
    
  }
  return 0;
  
}

//robot
#include<iostream>
using namespace std;
long int alllines[100][5];
//vertical-1 horizontal-0
long long int current_x, current_y;

bool findverticalcollision(int index)
{
	long int*current = alllines[index];
	for (int i = 0; i < index; i++)
	{
		if (alllines[i][4] == 1)
		{
			if (alllines[i][0] == current[0])
			{
				if (current[1]<alllines[i][1] && current[1]>alllines[i][1])
				{
					//cout << "vertical overlap case 1 with " <<i<<" bcoz "<<current[1]<<" "<<current[3]<<" "<<alllines[i][1]<<" "<<alllines[i][3]<< endl;
					return true;
				}
				else if (current[1]>alllines[i][1] && current[1] < alllines[i][3])
				{
					//cout << "vertical overlap case 2" << endl;
					return true;
				}
				else if (current[3]>alllines[i][1] && current[3] < alllines[i][3])
				{
					//cout << "vertical overlap case 3" << endl;
					return true;
				}
				else if (current[1]<alllines[i][1] && current[3]>alllines[i][3])
				{
					//cout << "vertical overlap case 4" << endl;
					return true;
				}
			}
		}
		else
		{
			if (current[0]<alllines[i][2] && current[0]>alllines[i][0])
			{
				if (alllines[i][1]>current[1] && alllines[i][1] < current[3])
				{
					//cout << "vertical intersection with horizontal line" << endl;
					return true;
				}
			}
		}
	}
	return false;
}

bool findhorizontalcollision(int index)
{
	long int*current = alllines[index];
	for (int i = 0; i < index; i++)
	{
		if (alllines[i][4] == 0)
		{
			if (alllines[i][1] == current[1])
			{
				if (current[0]<alllines[i][0] && current[0]>alllines[i][0])
				{
					//cout << "horizontal overlap case 1"<<endl;
					return true;
				}
				else if (current[0]>alllines[i][0] && current[0] < alllines[i][2])
				{
					//cout << "horizontal overlap case 2" << endl;
					return true;
				}
				else if (current[2]>alllines[i][0] && current[2] < alllines[i][2])
				{
					//cout << "horizontal overlap case 3" << endl;
					return true;
				}
				else if (current[0]<alllines[i][0] && current[2]>alllines[i][2])
				{
					//cout << "horizontal overlap case 4" << endl;
					return true;
				}
			}
		}
		else
		{
			if (current[1]<alllines[i][3] && current[1]>alllines[i][1])
			{
				if (alllines[i][0] > current[0] && alllines[i][0] < current[2])
				{
					//cout << "horizontal with vertical intersection" << endl;
					return true;
				}
			}
		}
	}
	return false;
}





bool markandfindcollision(int direction, int distance, int index)
{
	switch (direction)
	{
		case 1://north
			alllines[index][0] = current_x;
			alllines[index][1] = current_y;
			alllines[index][2] = current_x;

			alllines[index][3] = current_y + distance;
			alllines[index][4] = 1;
			current_y = current_y + distance;
			break;
		case 2://south
			alllines[index][0] = current_x;
			alllines[index][1] = current_y - distance;
			alllines[index][2] = current_x;
			alllines[index][3] = current_y;
			alllines[index][4] = 1;
			current_y = current_y - distance;
			break;
		case 3://east
			alllines[index][0] = current_x;
			alllines[index][1] = current_y;
			alllines[index][2] = current_x + distance;
			alllines[index][3] = current_y;
			alllines[index][4] = 0;
			current_x = current_x + distance;
			break;
		case 4://west
			alllines[index][0] = current_x - distance;
			alllines[index][1] = current_y;
			alllines[index][2] = current_x;
			alllines[index][3] = current_y;
			alllines[index][4] = 0;
			current_x = current_x - distance;
			break;
	}
	if (direction > 2)
		return findhorizontalcollision(index);
	else return findverticalcollision(index);
}

int main()
{
	int t,steps,direction,distance;
	int firstfound;
	bool foundcollision;
	cin >> t;
	while (t--)
	{	
		current_x = 0;
		current_y = 0;
		firstfound = -1;
		foundcollision = false;
		cin >> steps;
		for (int i = 0; i < steps; i++)
		{
			cin >> direction >> distance;
			if (!foundcollision)
			{
				if (markandfindcollision(direction, distance, i))
				{
					foundcollision = true;
					firstfound = i + 1;

				}

			}
		}
		cout << firstfound << endl;
	}
	for (int i = 0; i < steps; i++)
	{
		cout << alllines[i][0] << " " << alllines[i][1] << " " << alllines[i][2] << " " << alllines[i][3] << " " << alllines[i][4] << endl;

	}

	return 0;

}
//research centre 


#include<iostream>
#include<time.h>
using namespace std;

struct q{
  int a[10000];
  int first;
  int last;
};
typedef struct q Q;
void push(Q* q,int x)
{ int *arr=q->a;
  arr[q->last]=x;
  q->last=q->last+1;
}
int pop(Q* q)
{ int *arr=q->a;
  q->first=q->first+1;
  return arr[q->first-1];
}
int size(Q* q)
{
  return q->last-q->first;
}

void bfs(int x,int y,int n,int m,int **matrix,Q* q,int** ans,int** visited)
{ //cout<<"bfs starting"<<endl;
  push(q,x);
  push(q,y);
  visited[x][y]=1;
  push(q,-1);
  int depth=0;
  while(size(q)>1)
  { 
    depth++;
    x=pop(q);
    while(x!=-1)
    {//cout<<x<<endl;
    //cout<<depth<<"printing depth"<<endl;
     y=pop(q);
     //cout<<x<<" x "<<y<<" y "<<endl;
     if(x-1>=0 && visited[x-1][y]==0 && matrix[x-1][y]==1)
     {
       push(q,x-1);
       push(q,y);
       visited[x-1][y]=1;
       ans[x-1][y]=depth;
     }
     if(x+1<m && visited[x+1][y]==0 && matrix[x+1][y]==1)
     {
       push(q,x+1);
       push(q,y);
       visited[x+1][y]=1;
       ans[x+1][y]=depth;
     }
     if(y-1>=0 && visited[x][y-1]==0 && matrix[x][y-1]==1)
     {
       push(q,x);
       push(q,y-1);
       visited[x][y-1]=1;
       ans[x][y-1]=depth;
     }
     if(y+1<m && visited[x][y+1]==0 && matrix[x][y+1]==1)
     {
       push(q,x);
       push(q,y+1);
       visited[x][y+1]=1;
       ans[x][y+1]=depth;
     }
      
      x=pop(q);
      
    }
    push(q,-1);
    
  }

}
int max(int a,int b)
{
  if(a>b)
  return a;
  else return b;
  
}

int main()
{
  int t;
  cin>>t;
  int start_time=clock();
  
  while(t--)
  {
    int r,c;
    cin>>r>>c;
    int **matrix;
    int **ans;
    int **temp;
    int **visited;
    matrix=new int*[r];
    ans=new int*[r];
    visited=new int*[r];
    temp=new int*[r];
    int x[c];
    int y[c];
    Q* q=new Q();
    q->first=0;
    q->last=0;
    for(int i=0;i<c;i++)
    {
      cin>>x[i]>>y[i];
      //cout<<x[i]<<" "<<y[i]<<endl;
    }
    for(int i=0;i<r;i++)
    {
      matrix[i]=new int[r];
      ans[i]=new int[r];
      visited[i]=new int[r];
      temp[i]=new int[r];
      for(int j=0;j<r;j++)
      {
        cin>>matrix[i][j];
        visited[i][j]=0;
        ans[i][j]=0;
        temp[i][j]=0;
        
      }
    }
    int min=10000;
    for(int i=0;i<c;i++)
    {//cout<<"agya"<<i<<" "<<endl;
      bfs(x[i]-1,y[i]-1,r,r,matrix,q,ans,visited);
      int z=pop(q);
        for(int j=0;j<r;j++)
        {
          for(int k=0;k<r;k++)
          { //cout<<ans[j][k]<<" "<<temp[j][k]<<endl;
            temp[j][k]=max(temp[j][k],ans[j][k]);
            //cout<<temp[j][k]<<" ";
            ans[j][k]=0;
            visited[j][k]=0;
          }
        }
    }
    
    for(int j=0;j<r;j++)
    {
      for(int k=0;k<r;k++)
        {
          if(temp[j][k]>0)
          min=min>temp[j][k]?temp[j][k]:min;
        }
      
    }
    
    cout<<min<<endl;
    }
  int end=clock();
  cout<<(double)(end-start_time)/(double)CLOCKS_PER_SEC;
  return 0;
}
// base station

#include<iostream>
using namespace std;
int n,m;

bool isvalidindex(int x,int y)
{
  if(x<n && x>=0 && y<m && y>=0)
  return true;
  return false;
}


void dfs(int x,int y,int ** matrix,int ** visited,int score,int depth,int &maxscore)
{
  visited[x][y]=1;
  score=score+matrix[x][y];
  if(depth==4)
  { visited[x][y]=0;
    if(score>maxscore)
    maxscore=score;
    return;
  }
  
  if(y%2==0)
  {
    if(isvalidindex(x-1,y) && visited[x-1][y]==0)
    dfs(x-1,y,matrix,visited,score,depth+1,maxscore);
    if(isvalidindex(x+1,y) && visited[x+1][y]==0)
    dfs(x+1,y,matrix,visited,score,depth+1,maxscore);
    if(isvalidindex(x,y-1) && visited[x][y-1]==0)
    dfs(x,y-1,matrix,visited,score,depth+1,maxscore);
    if(isvalidindex(x,y+1) && visited[x][y+1]==0)
    dfs(x,y+1,matrix,visited,score,depth+1,maxscore);
    if(isvalidindex(x-1,y-1) && visited[x-1][y-1]==0)
    dfs(x-1,y-1,matrix,visited,score,depth+1,maxscore);
    if(isvalidindex(x-1,y+1) && visited[x-1][y+1]==0)
    dfs(x-1,y+1,matrix,visited,score,depth+1,maxscore);
  
  }
  else
  {
    if(isvalidindex(x-1,y) && visited[x-1][y]==0)
    dfs(x-1,y,matrix,visited,score,depth+1,maxscore);
    if(isvalidindex(x+1,y) && visited[x+1][y]==0)
    dfs(x+1,y,matrix,visited,score,depth+1,maxscore);
    if(isvalidindex(x,y-1) && visited[x][y-1]==0)
    dfs(x,y-1,matrix,visited,score,depth+1,maxscore);
    if(isvalidindex(x,y+1) && visited[x][y+1]==0)
    dfs(x,y+1,matrix,visited,score,depth+1,maxscore);
    if(isvalidindex(x+1,y-1) && visited[x+1][y-1]==0)
    dfs(x+1,y-1,matrix,visited,score,depth+1,maxscore);
    if(isvalidindex(x+1,y+1) && visited[x+1][y+1]==0)
    dfs(x+1,y+1,matrix,visited,score,depth+1,maxscore);
    
  }
  
 visited[x][y]=0;
}
int y(int **matrix,int x,int y)
{
  if(y%2!=0)
  {
    if(isvalidindex(x,y-1) && isvalidindex(x,y+1) && isvalidindex(x+1,y))
      return matrix[x][y-1]+matrix[x][y+1]+matrix[x+1][y]+matrix[x][y];
    else 
    return 0;
  }
  else
  {
    if(isvalidindex(x-1,y-1) && isvalidindex(x-1,y+1) && isvalidindex(x+1,y))
      return matrix[x-1][y-1]+matrix[x-1][y+1]+matrix[x+1][y]+matrix[x][y];
    else
    return 0;
  }
}

int iy(int **matrix,int x,int y)
{
  if(y%2!=0)
  {
    if(isvalidindex(x+1,y-1) && isvalidindex(x+1,y+1) && isvalidindex(x-1,y))
      return matrix[x+1][y-1]+matrix[x+1][y+1]+matrix[x-1][y]+matrix[x][y];
    else 
    return 0;
  }
  else
  {
    if(isvalidindex(x,y-1) && isvalidindex(x,y+1) && isvalidindex(x-1,y))
      return matrix[x][y-1]+matrix[x][y+1]+matrix[x-1][y]+matrix[x][y];
    else
    return 0;
  }

}

int main()
{
  int t;
  cin>>t;
  while(t--)
  {
    cin>>n>>m;
    int **matrix;
    int **visited;
    matrix=new int*[n];
    visited=new int*[n];
    for(int i=0;i<n;i++)
    {matrix[i]=new int[m];
    visited[i]=new int[m];
    for(int j=0;j<m;j++)
    {
      cin>>matrix[i][j];
      visited[i][j]=0;
    }
    }
    int maxscore=0;
    for(int i=0;i<n;i++)
    {
      for(int j=0;j<m;j++)
      {
        dfs(i,j,matrix,visited,0,1,maxscore);
        int y1=y(matrix,i,j);
        if(y1>maxscore)
        maxscore=y1;
        int y2=iy(matrix,i,j);
        if(y2>maxscore)
        maxscore=y2;
      }
    }
    
    cout<<maxscore<<endl;
    
  }
  
  return 0;
  
}

//marble game

#include<iostream>

using namespace std;
int arr[5][5];
int temp[5][5];

int direction[5][4] = {
	{ 2, 0, 3, 1 }, { 3, 0, 1, 2 }, { 1, 3, 0, 2 }, { 1, 2, 3, 0 }, { 1, 0, 3, 2 } };


int marble(int i,int j,int arr[5][5],int n,int m,int dir)
{
  int nochange=0;
  int ans=0;
  while(nochange<6)
  {
    if(i==-1)
      i=n-1;
    if(j==-1)
    j=m-1;
    if(i==n)
    i=0;
    if(j==m)
    j=0;
    if(arr[i][j]==0)
    {
      nochange=nochange+1;
      if(dir==0)
      j=j-1;
      else if(dir==1)
      j=j+1;
      else if(dir==2)
      i=i-1;
      else if(dir==3)
      i=i+1;
    }
    else
    {
      nochange=0;
      int temp=arr[i][j]/10;
      int temp2=arr[i][j]%10;
      if(direction[temp-1][dir]==0)
      {
        arr[i][j]=temp*10+temp2-1;
        j=j-1;
        dir=0;
        if(temp2-1==0)
          {arr[i][j+1]=0;
          ans++;
          }
      }
      else if(direction[temp-1][dir]==1)
      {
        arr[i][j]=temp*10+temp2-1;
        j=j+1;
        dir=1;
        if(temp2-1==0)
          {arr[i][j-1]=0;
          ans++;
          }
      }
      else if(direction[temp-1][dir]==2)
      {
        arr[i][j]=temp*10+temp2-1;
        i=i-1;
        dir=2;
        if(temp2-1==0)
          {arr[i+1][j]=0;
          ans++;
          }
      }
      else if(direction[temp-1][dir]==3)
      {
        arr[i][j]=temp*10+temp2-1;
        i=i+1;
        dir=3;
        if(temp2-1==0)
          {arr[i-1][j]=0;
          ans++;
          }
      }
      
      
      
    }}
    return ans;
}
    


int main()

{
  int n,m,dir;
  int final=0;
  int e;
  cin>>n>>m;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
      {cin>>arr[i][j];
      temp[i][j]=arr[i][j];}
  }
   for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
      {if(arr[i][j]==0){
        for(int k=0;k<4;k++)
        {e=marble(i,j,arr,n,m,k);
        final=max(final,e);
          for(int c=0;c<n;c++)
            for(int v=0;v<m;v++)
              arr[c][v]=temp[c][v];
          
        }
        
      }
        
      }
  }
  
  
 cout<<final<<endl;
 return 0;
}
//jumping game

#include<iostream>
#include<climits>
using namespace std;
char input[50][50];
int n,m;
bool visited[50][50];

bool isvalidindex(int x,int y)
{
  if(x<n && x>=0 && y<m && y>=0)
  return true;
  return false;
  
  
}

void dfs(int &ans,int start_x,int start_y,int n,int m,int coin_x,int coin_y,int temp)
{// cout<<start_x<<" "<<start_y<<endl;
  visited[start_x][start_y]=true;
  if((start_x==coin_x-1) && (start_y==coin_y-1))
    {
      if(temp<ans)
      ans=temp;
      return;
    }
    
  else
  {
    if(input[start_x][start_y+1]=='X' && isvalidindex(start_x,start_y+1) && !visited[start_x][start_y+1])
      {dfs(ans,start_x,start_y+1,n,m,coin_x,coin_y,temp);
        visited[start_x][start_y+1]=false;
      }
    if(input[start_x][start_y-1]=='X' && isvalidindex(start_x,start_y-1) && !visited[start_x][start_y-1])
      {dfs(ans,start_x,start_y-1,n,m,coin_x,coin_y,temp);
        visited[start_x][start_y-1]=false;
      }
   if (input[start_x-1][start_y]=='X' && isvalidindex(start_x-1,start_y)  && !visited[start_x-1][start_y])
      { if(temp<1)
        {dfs(ans,start_x-1,start_y,n,m,coin_x,coin_y,1);
          visited[start_x-1][start_y]=false;
        }
        else
        {dfs(ans,start_x-1,start_y,n,m,coin_x,coin_y,temp);
          visited[start_x-1][start_y]=false;
        }
      }
    else
    { int i;
    int flag=0;
      for( i=start_x-1;i>=0;i--)
        {
          if(input[i][start_y]=='X' && !visited[i][start_y])
          { flag=1;
            break;}
          
        }
        if(start_x-i>temp && flag==1)
        {dfs(ans,i,start_y,n,m,coin_x,coin_y,start_x-i);
          visited[i][start_y]=false;
        }
        else if(flag==1)
        {dfs(ans,i,start_y,n,m,coin_x,coin_y,temp);
          visited[i][start_y]=false;
        }
    }
    if (input[start_x+1][start_y]=='X' && isvalidindex(start_x+1,start_y) && !visited[start_x+1][start_y])
      { if(temp<1)
        {dfs(ans,start_x+1,start_y,n,m,coin_x,coin_y,1);
          visited[start_x+1][start_y]=false;
        }
        else
        {dfs(ans,start_x+1,start_y,n,m,coin_x,coin_y,temp);
          visited[start_x+1][start_y]=false;
        }
      }
    else
    { int j;
    int flag1=0;
      for( j=start_x+1;j<n;j++)
        {
          if(input[j][start_y]=='X' && !visited[j][start_y])
          { flag1=1;
            break;}
          
        }
        if(j-start_x>temp && flag1==1)
        {dfs(ans,j,start_y,n,m,coin_x,coin_y,j-start_x);
          visited[j][start_y]=false;
        }
        else if(flag1==1)
        {dfs(ans,j,start_y,n,m,coin_x,coin_y,temp);
          visited[j][start_y]=false;
        }
    }
    
        
    
    
    
  }
  
  return;
  
}


int main()
{
  
  int t;
  cin>>t;
  for(int i=0;i<t;i++)
  {
    cin>>n>>m;
    for(int j=0;j<n;j++)
      {cin>>input[j];
        cout<<input[j]<<endl;
      }
      for(int j=0;j<n;j++)
        {
          for(int k=0;k<m;k++)
            visited[j][k]=false;
          
        }
    int coin_x,coin_y;
    cin>>coin_x>>coin_y;
    int start_x=n-1;
    int start_y=0;
    int ans=INT_MAX;
    int temp=0;
    dfs(ans,start_x,start_y,n,m,coin_x,coin_y,temp);
    cout<<ans<<endl;
    
  }
  
  return 0;
  
  
  
}
//palindrome

#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int count1;
bool palindrom(int ans[100],int j){
  for(int i=0;i<j/2;i++){
    if(ans[i]!=ans[j-i-1])return false;
  }
  return true;
}
void permute(int ans[100],int value,int point,int* count, int * array,int n,int j){
    
  if(point==4){
    for(int i=0;i<n;i++){
      if(count[i]==0){return;}
    }
    if(palindrom(ans,j))count1++;
    return;
  }
  for(int i=0;i<n;i++){
    if(count[i]!=2)
    {
      int value1=value*10+array[i];
      count[i]++;
      ans[j]=array[i];
      if(value1<256){permute(ans,0,point+1,count,array,n,j+1); }
      if(value1!=0 && value1<256)permute(ans,value1,point,count,array,n,j+1);
      count[i]--;
    }
    
  }
}
int main(){
  int test;
  cin>>test;
  while(test--){
    count1=0;
    int ans[100];
    for(int i=0;i<100;i++){ans[i]=0;}
    int n;
    cin>>n;
    int arr[n];
    int count[n];
    for(int i=0;i<n;i++){cin>>arr[i];count[i]=0;}
    permute(ans,0,0,count,arr,n,0);
    cout<<count1<<endl;
  }
  return 0;
}


//pipes

#include<iostream>
using namespace std;
int start_x,start_y;
int arr[50][50];
bool visited[50][50];
int connection[8][8];
int direction[8][4];
int answer[50][50];
int n,m;
bool isvalidindex(int x,int y)
{
  if(x<n && x>=0 && y<m && y>=0)
    return true;
  else
  return false;
}
void connectionmaking()
{
  direction[0][0]=0;
  direction[0][1]=0;
  direction[0][2]=0;
  direction[0][3]=0;
  direction[1][0]=1;
  direction[1][1]=1;
  direction[1][2]=1;
  direction[1][3]=1;
  direction[2][0]=0;
  direction[2][1]=1;
  direction[2][2]=0;
  direction[2][3]=1;
  direction[3][0]=1;
  direction[3][1]=0;
  direction[3][2]=1;
  direction[3][3]=0;
  direction[4][0]=0;
  direction[4][1]=1;
  direction[4][2]=1;
  direction[4][3]=0;
  direction[5][0]=0;
  direction[5][1]=0;
  direction[5][2]=1;
  direction[5][3]=1;
  direction[6][0]=1;
  direction[6][1]=0;
  direction[6][2]=0;
  direction[6][3]=1;
  direction[7][0]=1;
  direction[7][1]=1;
  direction[7][2]=0;
  direction[7][3]=0;

}

void dfs(int start_x,int start_y,int l,int n,int m,int temp)
{  
  //cout<<" x "<<start_x<<" y "<<start_y<<" temp value "<<temp<<endl;
  visited[start_x][start_y]=true;
 answer[start_x][start_y]=1;
  if(temp==l)
  return;
  else
  {
    if(direction[arr[start_x][start_y]][2]==1 && direction[arr[start_x][start_y+1]][0]==1 && !visited[start_x][start_y+1] && isvalidindex(start_x,start_y+1))
    {dfs(start_x,start_y+1,l,n,m,temp+1);
      visited[start_x][start_y+1]=false;
    }
    if(direction[arr[start_x][start_y]][1]==1 && direction[arr[start_x-1][start_y]][3]==1 && !visited[start_x-1][start_y] && isvalidindex(start_x-1,start_y))
    {dfs(start_x-1,start_y,l,n,m,temp+1);
      visited[start_x-1][start_y]=false;
    }
    if(direction[arr[start_x][start_y]][3]==1 && direction[arr[start_x+1][start_y]][1]==1 && !visited[start_x+1][start_y] && isvalidindex(start_x+1,start_y))
    {dfs(start_x+1,start_y,l,n,m,temp+1);
      visited[start_x+1][start_y]=false;
    }
    if(direction[arr[start_x][start_y]][0]==1 && direction[arr[start_x][start_y-1]][2]==1 && !visited[start_x][start_y-1] && isvalidindex(start_x,start_y-1))
    {dfs(start_x,start_y-1,l,n,m,temp+1);
      visited[start_x][start_y-1]=false;
    }
  }
  
  
  
  
}


int main()
{
  int t,l;
  cin>>t;
  connectionmaking();
  for(int i=0;i<t;i++)
  {
    cin>>n>>m;
    cin>>start_x>>start_y>>l;
    for(int j=0;j<n;j++)
    {
      for(int k=0;k<m;k++)
      {
       visited[j][k]=false;
      }
    }
    for(int j=0;j<n;j++)
    {
      for(int k=0;k<m;k++)
      {
       answer[j][k]=0;
      }
    }
    for(int j=0;j<n;j++)
    {
      for(int k=0;k<m;k++)
      {
        cin>>arr[j][k];
      }
    }
    
    int ans=0;
    int temp=0;
    if(arr[start_x][start_y]!=0)
    {dfs(start_x,start_y,l,n,m,temp+1);
    for(int j=0;j<n;j++)
    {
      for(int k=0;k<m;k++)
      {
       ans=ans+answer[j][k];
      }
    }
      cout<<ans<<endl;
    }
    else
    cout<<ans<<endl;
    
  }
  
}


//marathon

#include<iostream>
#include<climits>
using namespace std;
int time1[5];
int enrgy_spent[5];

int main()
{
  int t,energy,distance,minutes,seconds;
  cin>>t;
  for(int i=0;i<t;i++)
  { cin>>energy>>distance;
    for(int j=0;j<5;j++ )
      {
        cin>>minutes>>seconds>>enrgy_spent[j];
        time1[j]=minutes*60+seconds;
      }
     int arr[distance+1][energy+1];
      for(int j=0;j<distance+1;j++)
        {
          for(int k=0;k<energy+1;k++)
          {
            if(j==0)
            arr[j][k]=0;
            else
            arr[j][k]=INT_MAX;
            
          }
        }
        
        for(int j=1;j<distance+1;j++)
        {
          for(int k=1;k<energy+1;k++)
          {int min1=INT_MAX;
            for(int q=0;q<5;q++)
            { if(k-enrgy_spent[q]<0)
            continue;
            
            int temp;
           // cout<<arr[j-1][k-enrgy_spent[q]]<<" "<<time1[q]<<" "<<j<<" "<<k-enrgy_spent[q]<<" "<<arr[j-1][k-enrgy_spent[q]]+time1[q]<<" ";
           if(arr[j-1][k-enrgy_spent[q]]!=INT_MAX)
           { temp=arr[j-1][k-enrgy_spent[q]]+time1[q];
            min1=min(temp,min1);}
              
             // cout<<arr[j][k]<<"value"<<endl;
            }
            arr[j][k]=min1;
          }
        }
        
        int ans=INT_MAX ;
        for(int j=0;j<energy+1;j++)
          ans=min(ans,arr[distance][j]);
          cout<<ans/60<<" "<<ans%60<<endl;
    
  }
  
  
  
}
///laser

#include<iostream>
using namespace std;
int arr[100][20];
int refrow[20];
int sumrow[100];


int maxamp(int refrowindex,int n,int m,int k)
{   int count=0;
    for(int i=0;i<m;i++)
    {
      if(arr[refrowindex][i]==0)
        refrow[i]=1;
      else
        refrow[i]=0;
    }
    
    for(int i=0;i<n;i++)
    {
      int sum=0;
      for(int j=0;j<m;j++)
      {
        if(refrow[j]==1)
          {
            if(arr[i][j]==0)
            sum++;
          }
          else
          sum=sum+arr[i][j];
      }
      if(sum==m)
      count++;
    }
  
  return count;
  
  
}



int findmax(int n,int m,int k)
{
  int maxoutput=0;
  for(int i=k;i>=0;i=i-2)
  {
   for(int j=0;j<n;j++)
   {
     if(i+sumrow[j]==m)
      {int val=maxamp(j,n,m,k);
        if(val>maxoutput)
          maxoutput=val;
      }
     
   }
    
  }
  return maxoutput;
}





int main()
{
  int t,n,m,k;
  cin>>t;
  for(int i=0;i<t;i++)
    { 
      cin>>n>>m>>k;
     
      for(int j=0;j<n;j++)
      {int sum=0;
        for(int k=0;k<m;k++)
        {
          cin>>arr[j][k];
          sum=sum+arr[j][k];
        }
        sumrow[j]=sum;
      }
      int answer=findmax(n,m,k);
      cout<<answer<<endl;
      
    }
  return 0;
  
}
//fishery

#include<iostream>
#include<ctime>

using namespace std;
clock_t start, end;
double cpu_time_used;
int mini;

void calculate(int j, int*perm,int *gate,int * visited,int * people,int dist,int n){
  if(j==3){
    if(dist<mini)mini=dist;
    return;
  }
  
  int i=perm[j];
  int left=gate[i];
  int right =gate[i]+1;
  int k=people[i];
  
    for(int z=0;z<k;z++){
      while( left>=0 && visited[left]==1){
        left--;
        if(left==-1){
          break;
        }
      }
      while(right<n && visited[right]==1){
        right++;
        if(right==n) break;
      }
      if(left==-1 && right==n){
        return;
      }
      
      if(left==-1 ){
        dist=dist+right-gate[i]+1;
        right++;
        visited[right-1]=1;
        
      }
      else if(right==n ){
        dist=dist+gate[i]-left+1,
        left--;
        visited[left+1]=1;
        
      }
      else if(z == k-1 && gate[i] - left == right - gate[i]){
        int * visited1= new int[100];
          for(int d=0;d<100;d++){
            visited1[d]=visited[d]; 
          }
          dist=dist+right-gate[i]+1;right++;
          visited[right-1]=1;
          calculate(j+1,perm,gate,visited,people,dist,n);
          right--;
          dist=dist-right+gate[i]-1;
          dist=dist+gate[i]-left+1,
          left--;
          visited1[left+1]=1;
          calculate(j+1,perm,gate,visited1,people,dist,n);
      }
      else if(gate[i]-left<right-gate[i]){
        dist=dist+gate[i]-left+1,
        left--;
        visited[left+1]=1;
        
      }
      else if(gate[i]-left>=right-gate[i]){
      dist=dist+right-gate[i]+1;
      right++;
      visited[right-1]=1;
      }
      
    }
    calculate(j+1,perm,gate,visited,people,dist,n);
}

int main(){
  int test;
  int start_s = clock();
  cin>>test;
  while(test--){
    int n;
    cin>>n;
    int * gate = new int[3];
    int * people = new int[3];
    
    for(int i=0;i<3;i++){
      cin>>gate[i]>>people[i];
      gate[i]--;
    }
    
    mini=10000;
    int * visited = new int[n];
    
    for(int i=0;i<n;i++){
      visited[i]=0;
    }
    
    int * perm =new int[3];

    perm[0]=0;perm[1]=1;perm[2]=2;
    calculate(0,perm,gate,visited,people,0,n);
    for(int i=0;i<n;i++){
      visited[i]=0;
    }
    
    perm[0]=0;perm[1]=2;perm[2]=1;
    calculate(0,perm,gate,visited,people,0,n);
    for(int i=0;i<n;i++){visited[i]=0;}
    
    perm[0]=1;perm[1]=0;perm[2]=2;
    calculate(0,perm,gate,visited,people,0,n);
    for(int i=0;i<n;i++){visited[i]=0;}
    
    perm[0]=1;perm[1]=2;perm[2]=0;
    calculate(0,perm,gate,visited,people,0,n);
    for(int i=0;i<n;i++){visited[i]=0;
    }
    
    perm[0]=2;perm[1]=0;perm[2]=1;
    calculate(0,perm,gate,visited,people,0,n);
    for(int i=0;i<n;i++){
      visited[i]=0;
    }
    
    perm[0]=2;perm[1]=1;perm[2]=0;
    calculate(0,perm,gate,visited,people,0,n);
    
    cout<<mini<<endl;
  }
  int stop_s = clock();
	//cout << "clocks per sec " << stop_s <<" start "<<start_s << " diff " << stop_s-start_s <<endl;
	cout << "time: " << 50*(stop_s - start_s) / (double(CLOCKS_PER_SEC)) << endl;
  return 0;
}


//tunelling


#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
#define MAX_N 5
#define MAX_V 15
#define MAX_H 500
#define getmin(a,b) (a>b?b:a)
int t,N, H, V, c1, c2, r1, r2, m1, m2,arr[500],solution[16],data[15],finalans=INT_MAX,gmin=INT_MAX,movingcost=0;
vector<int> si;
int findall(int l,int r,int prev,int cost){
    if (cost > gmin)
        return cost;
    if (l > r){
        if (cost < gmin)
            gmin = cost;
        return cost;
    }
    return getmin(findall(l + 1, r, 1, cost + arr[l] * c1 + ((prev == 1) ? r1 : 0)), findall(l, r - 1, 2, cost + arr[r] * c2 + ((prev == 2) ? r2 : 0)));
}
void find_comb(int TOTAL, int LAST,int cost){
    if (cost>gmin)
        return;
    if (TOTAL == N){
        if (cost < gmin)
            gmin = cost;
        return;
    }
    for (int i = LAST; i < V; i++){
        if (TOTAL == 0){
            find_comb(TOTAL + 1, i, cost + solution[i]);
        }
        else if(i-LAST>=2){
            find_comb(TOTAL + 1, i, cost + movingcost*(i - LAST) + solution[i]);
        }
    }
}


int main(){
    cin >> t;
    while (t-- > 0){
        cin >> N >> V >> H >> c1 >> r1 >> m1 >> c2 >> r2 >> m2;
        movingcost = m1*m1 + m2*m2;
        for (int i = 0; i < V; i++){
            solution[i] = 0;
            for (int j = 0; j < H; j++)
                cin >> arr[j];
            gmin = INT_MAX;
            solution[i] = findall(0,H-1,-1,0);
            //cout << solution[i] << endl;
        }
    }
    gmin = INT_MAX;
    find_comb(0, 0,0);
    cout << gmin << endl;
    return 0;
}

// toll gate

#include <stdio.h>
#include <stdlib.h>

int min = 10000;

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Findsteps(int *arr, int *ind, int n, int pos, int diesel, int gasoline, int steps, int i){

	if (steps > min){
		return;
	}
	if (i == n){
		if (steps < min)
			min = steps;
		return;
	}

	if (arr[ind[i]] == 1){
		if (gasoline){
			if (ind[i] > pos)
				steps += ind[i] - pos;
			else
				steps += pos - ind[i];
			gasoline--;

			//if(gasoline == 1)
			//   Findsteps(arr,ind,n,n,1,1,steps+n-ind[i],i+1);
			//Findsteps(arr,ind,n,n,2,0,steps+n-ind[i],i+1);
		}
		else{
			steps += pos + 1 + ind[i] + 1;
			gasoline += 2;
			diesel = 0;
			gasoline--;

		}
		pos = ind[i];
	}
	else{
		if (diesel){
			if (ind[i] > pos)
				steps += ind[i] - pos;
			else
				steps += pos - ind[i];
			diesel--;
		}
		else{
			steps += n - pos;
			gasoline = 0;
			diesel += 2;
			steps += n - ind[i];
			diesel--;
			//if(diesel == 1)
			//   Findsteps(arr,ind,n,-1,1,1,steps+ind[i]+1,i+1);
			//Findsteps(arr,ind,n,-1,0,2,steps+ind[i]+1,i+1);
		}
		pos = ind[i];
	}
	Findsteps(arr, ind, n, pos, diesel, gasoline, steps, i + 1);
	Findsteps(arr, ind, n, -1, 0, 2, steps + ind[i] + 1, i + 1);
	Findsteps(arr, ind, n, n, 2, 0, steps + n - ind[i], i + 1);
}

void permute(int *arr, int *ind, int first, int last){
	if (first == last){
		Findsteps(arr, ind, last + 1, -1, 0, 2, 0, 0);
		return;
	}
	for (int i = first; i <= last; i++){
		swap(ind + first, ind + i);
		permute(arr, ind, first + 1, last);
		swap(ind + first, ind + i);
	}
}


int main() {
	int n;
	scanf("%d", &n);
	int *arr = (int *)malloc(sizeof(int)*n);
	int *ind = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i<n; i++){
		ind[i] = i;
		scanf("%d", &arr[i]);
	}
	permute(arr, ind, 0, n - 1);
	printf("%d", min);
	return 0;
}
