#include<iostream>
#include<stdlib.h>
#include<stack>
#include<queue>
using namespace std;

class node{
public:
    node *left, *right;
    int data;
};

class Breadthfs{
    public:
    node *insert(node *, int);
    void bfs(node *);
};


node *insert(node *root, int data){
    if(!root){
        root=new node;
        root->left=NULL;
        root->right=NULL;
        root->data=data;
        return root;
    }
    queue<node *> q;
    q.push(root);
    while(!q.empty()){
        node *temp=q.front();
        q.pop();
        if(temp->left==NULL){
            temp->left=new node;
            temp->left->left=NULL;
            temp->left->right=NULL;
            temp->left->data=data;
            return root;
        }
        else{
            q.push(temp->left);
        }
        if(temp->right==NULL){
            temp->right=new node;
            temp->right->left=NULL;
            temp->right->right=NULL;
            temp->right->data=data;
            return root;
        }
        else{
            q.push(temp->right);
        }
    }
}

void dfs(node *head){
    stack<node*> st;
    st.push(head);
    int stSize;
    while (!st.empty()){
        stSize = st.size();
        #pragma omp parallel for
        for (int i = 0; i < stSize; i++){
            node* currNode;
            #pragma omp critical
            {
            currNode = st.top();
            st.pop();
            cout<<" "<<currNode->data;
            }
            #pragma omp critical
            {
                if(currNode->right) st.push(currNode->right);
                if(currNode->left) st.push(currNode->left);
            }
        }
    }
}

int main(){
    node *root=NULL;
    int data;
    char ans;
    do{
        cout<<"\n enter node: ";
        cin>>data;
        root=insert(root,data);
        cout<<"do you want insert one more nodes?";
        cin>>ans;
    }while(ans=='y'||ans=='Y');
    cout << "DFS: ";
    dfs(root);

    return 0;
}