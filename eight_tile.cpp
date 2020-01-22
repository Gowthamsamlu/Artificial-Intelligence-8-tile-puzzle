#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define n 3
using namespace std;
int goal_state[n][n] = {{1,2,3},{4,5,6},{7,8,0}};
int zero_pos[2] = {-1,-1};
int compare_tiles(int matrix1[n][n], int matrix2[n][n]){
    int cnt=0;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            if(matrix1[i][j]!=matrix2[i][j] && matrix2[i][j]!=0)
                cnt++;
        }
    }
    return cnt;
}
int check_tile_equality(int matrix1[n][n], int matrix2[n][n]){
    int cnt=0;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            if(matrix1[i][j]==matrix2[i][j])
                cnt++;
        }
    }
    return cnt;
}
void print_matrix(int matrix[n][n]){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            if(matrix[i][j]==0)
                cout<<"   ";
            else
                cout<<matrix[i][j]<<"  ";
        }
        cout<<"\n";
    }
}
struct Node{
    int matrix[n][n];
    int score;
    int level;
};
void find_zero(int matrix[n][n]){
    //int pos[2]={-1,-1};
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            if(matrix[i][j]==0){
                zero_pos[0] = i;
                zero_pos[1] = j;
            }
        }
    }
}
Node open[1000], closed[1000];
int open_score[1000], closed_score[1000];
int open_top = 0, closed_top = 0;
bool check_in_open_and_closed(Node nod){
    bool return_value = false;
    for(int i = 0 ; i < open_top ; i++){
        if(check_tile_equality(nod.matrix, open[i].matrix)==9){
            return_value = true;
            break;
        }
    }
    if(!return_value){
        for(int i = 0 ; i < closed_top ; i++){
            if(check_tile_equality(nod.matrix, closed[i].matrix)==9){
                return_value = true;
                break;
            }
        }
    }
    return return_value;
}
void sort_open(){
    for(int i = 0 ; i < open_top ; i++){
        for(int j = i+1 ; j < open_top ; j++){
            if( open_score[i] < open_score[j] ){
                Node temp;
                int temp_int;
                temp = open[i];
                temp_int = open_score[i];
                open_score[i] = open_score[j];
                open[i] = open[j];
                open[j] = temp;
                open_score[j] = temp_int;
            }
        }
    }
}
void generate_child_nodes(Node root_node){
    //zero_pos =
    find_zero(root_node.matrix);
    int i = zero_pos[0], j = zero_pos[1];
  //  cout<<"\ni: "<<i<<"\tj: "<<j;
    if( i < n-1 ){
            Node bottom_node;
            for(int i1 = 0 ; i1 < n ; i1++){
                for(int j1 = 0 ; j1 < n ; j1++)
                    bottom_node.matrix[i1][j1] = root_node.matrix[i1][j1];
            }
            bottom_node.matrix[i][j] = bottom_node.matrix[i+1][j];
            bottom_node.matrix[i+1][j] = 0;
            bottom_node.score = compare_tiles(bottom_node.matrix, goal_state);
            bottom_node.level = root_node.level + 1;
            if(!check_in_open_and_closed(bottom_node)){
                open[open_top] = bottom_node;
                open_score[open_top] = bottom_node.level + bottom_node.score;
                open_top++;
                sort_open();
            }
        }
    if( i != -1 && j != -1 ){
        if(j>0){
            Node left_node;
            for(int i1 = 0 ; i1 < n ; i1++){
                for(int j1 = 0 ; j1 < n ; j1++)
                    left_node.matrix[i1][j1] = root_node.matrix[i1][j1];
            }
            left_node.matrix[i][j] = left_node.matrix[i][j-1];
            left_node.matrix[i][j-1] = 0;
            left_node.score = compare_tiles(left_node.matrix, goal_state);
            left_node.level = root_node.level+1;
            if(!check_in_open_and_closed(left_node)){
                open[open_top] = left_node;
                open_score[open_top] = left_node.level + left_node.score;
                open_top++;
                sort_open();
            }
        }
        if(j < n-1){
            Node right_node;
            for(int i1 = 0 ; i1 < n ; i1++){
                for(int j1 = 0 ; j1 < n ; j1++)
                    right_node.matrix[i1][j1] = root_node.matrix[i1][j1];
            }
            right_node.matrix[i][j] = right_node.matrix[i][j+1];
            right_node.matrix[i][j+1] = 0;
            right_node.score = compare_tiles(right_node.matrix, goal_state);
            right_node.level = root_node.level + 1;
            if(!check_in_open_and_closed(right_node)){
                open[open_top] = right_node;
                open_score[open_top] = right_node.level + right_node.score;
                open_top++;
                sort_open();
            }
        }
        if( i > 0 ){
            Node top_node;
            for(int i1 = 0 ; i1 < n ; i1++){
                for(int j1 = 0 ; j1 < n ; j1++)
                    top_node.matrix[i1][j1] = root_node.matrix[i1][j1];
            }
            top_node.matrix[i][j] = top_node.matrix[i-1][j];
            top_node.matrix[i-1][j] = 0;
            top_node.score = compare_tiles(top_node.matrix, goal_state);
            top_node.level = root_node.level + 1;
            if(!check_in_open_and_closed(top_node)){
                open[open_top] = top_node;
                open_score[open_top] = top_node.level + top_node.score;
                open_top++;
                sort_open();
            }
        }
    }
}
int main(){
    int current_state[n][n] = {{1,2,3},{4,8,5},{7,6,0}};
    system("cls");
    cout<<"Initial State:-\n";
    print_matrix(current_state);
    struct Node head;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++)
            head.matrix[i][j] = current_state[i][j];
    }
    head.score  = compare_tiles(head.matrix,goal_state);
    head.level = 0;
    open[open_top] = head;
    open_score[open_top] = head.score + head.level;
    open_top++;
    int ite_cnt=1;
    while( open_top > 0 ){
        struct Node nd;
        int node_score;
        open_top--;
        nd = open[open_top];
        node_score = open_score[open_top];
        cout<<"\n\n\nIteration("<<ite_cnt<<") : \n";
        print_matrix(nd.matrix);
        cout<<"Node_level - "<<nd.level<<"\tOpen count - "<<open_top<<"\tClosed count - "<<closed_top;
        closed[closed_top] = nd;
        closed_score[closed_top] = node_score;
        closed_top++;
        if(nd.score==0){
            cout<<"\n\n\nHurray!  Reached Goal\n\n";
            //print_matrix(nd.matrix);
            return 0;
        }else{
            generate_child_nodes(nd);
        }
        //cout<<"\nOpen cnt: "<<open_top;
        /*if(ite_cnt==2){
            while(open_top > 0){
                struct Node nd2;
                open_top--;
                nd2 = open[open_top];
                int nd2_score = open_score[open_top];
                cout<<"\nOpen - "<<(open_top+1)<<"\tNode_score - "<<nd2.score<<"\tNode_level - "<<nd2.level<<"\tScore: "<<nd2_score<<endl;
                print_matrix(nd2.matrix);
            }
            while(closed_top > 0){
                struct Node nd2;
                closed_top--;
                nd2 = closed[closed_top];
                int nd2_score = closed_score[closed_top];
                cout<<"\nClosed - "<<(closed_top+1)<<"\tNode_score - "<<nd2.score<<"\tNode_level - "<<nd2.level<<"\tScore: "<<nd2_score<<endl;
                print_matrix(nd2.matrix);
            }
        }/* d*/
        ite_cnt++;
        if(ite_cnt%50==0){
            cout<<"\n\nALERT: Program executing for long time. Wish to continue[Y/N]: ";
            fflush(stdin);
            char ch = getchar();
            if( ch!='Y' && ch != 'y' )
                return 0;
        }
        else if(ite_cnt==500){
            cout<<"\n\nALERT: Terminating as the program executing for longer time";
            return 0;
        }
    }
    cout<<"We are sorry! Unable to reach goal";
    return 0;
}
