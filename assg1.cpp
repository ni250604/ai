#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> arr;

struct Node {
	int data;
	struct Node *left, *right;
	Node(int data)
	{
		this->data = data;
		left = right = NULL;
	}
};

void print_tree(Node* root) {
    if(root == NULL)		return;
	
    queue<Node*> q; 
    q.push(root); 

    while(!q.empty()) {
        int size = q.size(); 
        for(int i = 0;i<size;i++) {
            Node *node = q.front(); 
            q.pop(); 
            if(node->left != NULL) q.push(node->left); 
            if(node->right != NULL) q.push(node->right); 
            cout<<node->data<<" "; 
        }
		cout<<endl; 
    } 
}

int BFS_iter(Node* root, int elem) {
    if(root == NULL)		return 0;
	
    queue<Node*> q; 
    q.push(root); 
    int j=1;

    while(!q.empty()) {
        int size = q.size(); 
        vector<int> temp;
        for(int i = 0;i<size;i++) 
        {
            Node *node = q.front(); 
            q.pop(); 
            if(node->left != NULL) q.push(node->left); 
            if(node->right != NULL) q.push(node->right);
            if(node->data == elem)	return j; 
         }
		j++;
    } 
}

void Postorder(Node* node){
	if (node == NULL)		return;

	Postorder(node->left);
	Postorder(node->right);
	cout << node->data << " ";
}

void Inorder(Node* node){
	if (node == NULL)		return;

	Inorder(node->left);
	cout << node->data << " ";
	Inorder(node->right);
}

bool DLS(Node* root, int lvl, int val, int height, vector<int>& path) {
    if (root == NULL)        return false;

    path.push_back(root->data);

    if (height > lvl)        return false;

    if (root->data == val)        return true;

    bool leftResult = DLS(root->left, lvl, val, height + 1, path);
    bool rightResult = DLS(root->right, lvl, val, height + 1, path);

    if (leftResult || rightResult)        return true;

    path.pop_back();

    return false;
}


bool BFS_Recursive(Node* node, int val) {
    if (node == NULL)        return false;

    if (node->data == val)        return true;

    bool leftResult = BFS_Recursive(node->left, val);
    bool rightResult = BFS_Recursive(node->right, val);

    return leftResult || rightResult;
}

bool BFS(Node* root, int val) {
    if (root == NULL)        return false;

    if (root->data == val)        return true;

    return BFS_Recursive(root, val);
}



int main(){

	struct Node* root = new Node(1);

	root->left = new Node(2);
	root->right = new Node(3);
	root->left->left = new Node(4);
	root->left->right = new Node(5);
	root->right->left = new Node(6);
	root->right->right = new Node(7);
    	root->right->left->left = new Node(8);
    	root->right->left->right = new Node(9);
    /*
    	int no_of_nodes,data,direction;
    	cout<<"Enter no of nodes:" ;
    	cin>>no_of_nodes;
    	struct Node* Root=NULL;
    	Node* temp = Root;
    	Node* temp1= Root;
    	for(int i=0; i<no_of_nodes; i++)
    	{
    		cout<<"Enter data:" ;
    		cin>>data;
    		if(i==0)	Root->data = data;
    		else
    		{
    			cout<<"1.Left\t2.Right of "<<temp1->data;
    			cin>>direction;
    			if(direction==1)	{
    				temp->data=data;
    				temp1->left=temp;
    			}
    			else
    			{
    				temp->data=data;
    				temp1->right=temp;
    			}
    		}
    		
    	}
*/
	cout << "\n Binary tree is \n";
	print_tree(root);

	cout << "\nInorder traversal of binary tree is \n";
	Inorder(root);

	cout << "\nPostorder traversal of binary tree is \n";
	Postorder(root);

	int choice;
	cout<<"\n \n1. DLS Search \n2. BFS Search";
	cout<<"\n\nEnter your choice : ";
	cin>>choice;


	if (choice == 1){
		int val, lvl, start;
        vector<int> path;
        vector<int> ans;

		cout<<"\n\nEnter the value you want to search : ";
		cin>>val;
		cout<<"Enter the depth limit : ";
		cin>>lvl;
		
		if (DLS(root, lvl, val, 1, path)){
			cout<<"\nElement found";
			cout<<"\nEnter start depth : ";
			cin>>start;
			/*
			for(int i=start-1; i<arr.size(); i++)
			{
				for(int j= 0; j<arr[i].size(); j++)
				{
					for(int k=0; k<path.size(); k++)
					{
						if(path[k]==arr[i][j])	ans.push_back(path[k]);
					}
				}
			}
			*/
			
	cout<<"The path to the goal is :";
	
            for (int node : path)             
            {
            
            	if(start<=BFS_iter(root,node))  cout << node << " ";
            	
            	
            }
            //for (int node : ans)             cout << node << " ";
        
        cout << endl;
		}
		else{
			cout<<"\nElement Not found";
		}
	}
	else if (choice == 2){
		int val;

		cout<<"\n\nEnter the value you want to search : ";
		cin>>val;
	
		if (BFS(root, val)){
			cout<<"\nElement Found\n";
		}
		else{
			cout<<"\nElement Not Found\n";
		}

	}
	else{
		cout<<"\nInvalid choice!!!\n";
	}

	return 0;
}
