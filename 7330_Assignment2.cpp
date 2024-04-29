#include<bits/stdc++.h>
using namespace std;
   
set<vector<vector<int>>> occured_states;
map<vector<vector<int>>,vector<int>> my_map;
map<vector<vector<int>>,vector<int>> temp; 

//answer g=5
// vector<vector<int>> initial_state={{2,8,3},{1,6,4},{7,-1,5}};
// vector<vector<int>> goal_state={{1,2,3},{8,-1,4},{7,6,5}};

//answer g=2
// vector<vector<int>> initial_state={{2,8,3},{1,6,4},{7,-1,5}};
// vector<vector<int>> goal_state={{2,8,3},{-1,1,4},{7,6,5}};

//large answer
vector<vector<int>> initial_state={{1,2,3},{8,-1,4},{7,6,5}};
vector<vector<int>> goal_state={{2,8,1},{-1,4,3},{7,6,5}};

//large answer
// vector<vector<int>> goal_state={{1,2,3},{4,5,6},{7,8,-1}};
// vector<vector<int>> initial_state={{1,2,3},{-1,4,6},{7,5,8}};

vector<int> calculate_heuristics(vector<vector<int>> current_state, int g)
{
    int h=0;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if( goal_state[i][j]!=-1 &&goal_state[i][j]!=current_state[i][j]){
                h++;
            }
        }
    }
    int f=g+h;
    vector<int> my_vector= {g,h,f};
    if(my_map.find(current_state)==my_map.end())    my_map[current_state]=my_vector;
    occured_states.insert(current_state);

    return my_vector;
    //cout<<"f,g,h : "<<f<<" "<<g<<" "<<h<<endl;
}

pair<int,int> get_blank_location (vector<vector<int>> current_state){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(current_state[i][j]==-1){
                return make_pair(i,j);
            }
        }
    }
}

void transform(vector<vector<int>> current_state, char direction, int parent_level){
    vector<vector<int>> transformed_puzzle =current_state;
    pair<int,int> result_of_get_blank_location = get_blank_location(current_state);
    int row = result_of_get_blank_location.first;
    int column = result_of_get_blank_location.second;

    switch (direction)
    {
    case 'U' :
        swap(transformed_puzzle[row+1][column],transformed_puzzle[row][column]);
        break;
    
    case 'D':
        swap(transformed_puzzle[row-1][column],transformed_puzzle[row][column]);
        break;
    
    case 'L' :
        swap(transformed_puzzle[row][column+1],transformed_puzzle[row][column]);
        break;
    
    case 'R':
        swap(transformed_puzzle[row][column-1],transformed_puzzle[row][column]);
        break;
    
    default:
        break;
    }

    if(occured_states.find(transformed_puzzle)==occured_states.end())       temp[transformed_puzzle]=calculate_heuristics(transformed_puzzle,parent_level+1);

}

void print_current(map<vector<vector<int>>,vector<int>> temp){
	cout<<"Current chosen state is :\n";
	for(auto p : temp){
        vector<vector<int>>vxp=p.first;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cout<<vxp[i][j]<<" ";
            }
            //cout<<i<<endl;
            if(i==0)     cout<<"\t\tg = "<<p.second[0];
            if(i==1)    cout<<"\t\th = "<<p.second[1];
            if(i==2)    cout<<"\t\tf = "<<p.second[2];
            cout<<endl;
        }	
        cout<<endl;				
	}
}

void print_puzzle(map<vector<vector<int>>,vector<int>> temp){
	cout<<"possible transformed states are :\n";
	for(auto p : temp){
        vector<vector<int>>vxp=p.first;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cout<<vxp[i][j]<<" ";
            }
            //cout<<i<<endl;
            if(i==0)     cout<<"\t\tg = "<<p.second[0];
            if(i==1)    cout<<"\t\th = "<<p.second[1];
            if(i==2)    cout<<"\t\tf = "<<p.second[2];
            cout<<endl;
        }	
        cout<<endl;				
	}
}

int main(){
    int g=0, current_level_min_heuristic=0;
    vector<vector<int>> current_state = initial_state;
    occured_states.insert(current_state);

    queue<pair<vector<vector<int>>, int>> waiting_states;
    queue<pair<vector<vector<int>>, int>> current_level_puzzle;
    map<vector<vector<int>>,vector<int>> current_level_map; 
    //waiting_states.push({current_state,g});
    current_level_puzzle.push({current_state,g});

    pair<vector<vector<int>>, int> state_catcher;
    bool flag = false;
    
    while (!current_level_puzzle.empty())
    {
        //queue<pair<vector<vector<int>>, int>> new_queue;
        current_level_min_heuristic = INT_MAX;
        for(map<vector<vector<int>>,vector<int>> :: iterator it = current_level_map.begin(); it!=current_level_map.end(); ++it){
                current_level_min_heuristic=min(current_level_min_heuristic,it->second[2]);                
            }
        
        if(!current_level_map.empty()){
            while (!current_level_puzzle.empty()) {
                if (current_level_map[current_level_puzzle.front().first][2] != current_level_min_heuristic) {
                    current_level_puzzle.pop();
                } else {
                    waiting_states.push(current_level_puzzle.front());
                    current_level_puzzle.pop();
                }   
            }   
        }  
        else    waiting_states=current_level_puzzle;
        


        //waiting_states=new_queue;
        //current_level_puzzle.clear();
        current_level_map.clear();

        while (!waiting_states.empty())
        {        
            if(waiting_states.empty()){
                cout<<"Same states are repeating ahead"<<endl;
                break;
            }

            // Check if the current state is the goal state
            state_catcher = waiting_states.front();
            waiting_states.pop();
            current_state = state_catcher.first;

            //cout<<"Current state is \n";
            temp.clear();
            temp[current_state]=calculate_heuristics(current_state,state_catcher.second);
            my_map.insert(temp.begin(),temp.end());
            print_current(temp);
            
            
            if (current_state == goal_state)
            {
                cout << "Goal state reached!" << endl;
                break;
            }

            if(current_state == goal_state && flag)    break;

            // Generate possible moves and update the set and map
            temp.clear();
            pair<int, int> blank_location = get_blank_location(current_state);
            int row = blank_location.first;
            int column = blank_location.second;

            if (row < 2)
            {
                transform(current_state, 'U',state_catcher.second);
            }
            if (row > 0)
            {
                transform(current_state,  'D',state_catcher.second);
            }
            if (column < 2)
            {
                transform(current_state, 'L',state_catcher.second);
            }
            if (column > 0)
            {
                transform(current_state, 'R',state_catcher.second);
            }
            g++;
            print_puzzle(temp);
            
            map<vector<vector<int>>,vector<int>> :: iterator my_it;
            int current_min_heuristic = INT_MAX;
            for(map<vector<vector<int>>,vector<int>> :: iterator it = temp.begin(); it!=temp.end(); ++it){
                if(it->second[0]==100){
                    cout<<"Tooo many levels to handle\n";
                    return 0;
                }
                if(it->second[2]<current_min_heuristic){
                    current_min_heuristic=it->second[2];
                    my_it=it;
                }
            }
            
            //storing states with same heuristic
            for(map<vector<vector<int>>,vector<int>> :: iterator it = temp.begin(); it!=temp.end(); ++it){
                if(my_it->second[2]==it->second[2]){
                    if(it->first == goal_state){
                        flag = true;
                    } 
                    waiting_states.push({it->first, it->second[0]});
                    current_level_puzzle.push({it->first, it->second[0]});
                }
            }
            my_map.insert(temp.begin(),temp.end());
            current_level_map.insert(temp.begin(),temp.end());
        }
    }
}
