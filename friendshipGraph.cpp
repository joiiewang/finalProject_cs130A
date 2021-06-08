#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include "friendshipGraph.h"

using namespace std;

//helper function for friend queries
Node* findPerson(string name, Node* r){
    if(!r) return NULL;
    else if(name.compare(r->name)==0) return r;
    else if(name.compare(r->name)<0) return findPerson(name, r->left);
    return findPerson(name,r->right);

}

string friendshipGraph::pointQuery(string name){
    Node* n = findPerson(name, root);
    std::ifstream is ("profileData.txt",std::ifstream::in);
    string answer;
    if(is) is.seekg(n->index);
    getline(is,answer);
    return answer;
}

string friendshipGraph::friendQuery(string name){
    Node* n = findPerson(name, root);
    std::ifstream is ("profileData.txt", std::ifstream::in);
    vector<string> f = n->friends;
    string answer;
    for(int i=0;i<f.size();i++){
        Node* fren = findPerson(f[i],root);
        if(is){
            is.seekg(fren->index);
        }
        string temp;
        getline(is, temp);
        answer+= temp + "\n";
    }
    return answer;
}


string friendshipGraph::occupationFriendQuery(string name){
    Node* n = findPerson(name, root);
    std::ifstream is ("profileData.txt", std::ifstream::in);
    vector<string> f = n->friends;
    string answer;
    for(int i=0;i<f.size();i++){
        Node* fren = findPerson(f[i],root);
        if(is){
            is.seekg(fren->index+25);
        }
        string occupation;
        getline(is, occupation);
        answer+= fren->name + ": " + occupation + "\n";
    }
    return answer;
}

string friendshipGraph::ageFriendQuery(string name){
    Node* n = findPerson(name, root);
    std::ifstream is ("profileData.txt", std::ifstream::in);
    vector<string> f = n->friends;
    string answer="";
    for(int i=0;i<f.size();i++){
        Node* fren = findPerson(f[i], root);
        if(is){
            is.seekg(fren->index+21);
        }
        string age;
        getline(is, age,',');
        answer+= fren->name + ": " + age + "\n";
    }
    return answer;
}

string friendshipGraph::nameFriendQuery(string name){
    Node* n = findPerson(name, root);
    string answer="";
    for(int i=0;i<n->friends.size();i++){
        answer+=n->friends[i]+", ";
    }
    return answer;
}

//helper function for range query
void range(string& answer, Node* r, string firstName, string secondName){
    if(!r) return;
    range(answer, r->left, firstName, secondName);
    if(r->name.compare(firstName)>=0&&r->name.compare(secondName)<=0){
        std::ifstream is ("profileData.txt", std::ifstream::in);
        if(is){
            is.seekg(r->index);
        }
        string temp;
        getline(is, temp);
        answer+= temp+"\n";
    }
    range(answer, r->right, firstName, secondName);
}

string friendshipGraph::rangeQuery(string firstName, string secondName){
    string answer;
    range(answer, root, firstName, secondName);
    return answer;
}

//helper function for occupation range query
void occupationRange(string& answer, Node* r, string firstName, string secondName){
    if(!r) return;
    occupationRange(answer, r->left, firstName, secondName);
    if(r->name.compare(firstName)>=0&&r->name.compare(secondName)<=0){
        std::ifstream is ("profileData.txt", std::ifstream::in);
        if(is){
            is.seekg(r->index+25);
        }
        string occupation;
        getline(is, occupation);
        answer+= r->name + ": "+ occupation+"\n";
    }
    occupationRange(answer, r->right, firstName, secondName);
}

string friendshipGraph::occupationRangeQuery(string firstName, string secondName){
    string answer;
    occupationRange(answer, root, firstName, secondName);
    return answer;

}

//helper function for age range query
void ageRange(string& answer, Node* r, string firstName, string secondName){
    if(!r) return;
    ageRange(answer, r->left, firstName, secondName);
    if(r->name.compare(firstName)>=0&&r->name.compare(secondName)<=0){
        std::ifstream is ("profileData.txt", std::ifstream::in);
        if(is){
            is.seekg(r->index+21);
        }
        string age;
        getline(is, age, ',');
        answer+= r->name + ": "+ age+"\n";
    }
    ageRange(answer, r->right, firstName, secondName);
}

string friendshipGraph::ageRangeQuery(string firstName, string secondName){
    string answer;
    ageRange(answer, root, firstName, secondName);
    return answer;

}

//helper function for name range query
void nameRange(string& answer, Node* r, string firstName, string secondName){
    if(!r) return;
    nameRange(answer, r->left, firstName, secondName);
    if(r->name.compare(firstName)>=0&&r->name.compare(secondName)<=0){
        answer+= r->name +", ";
    }
    nameRange(answer, r->right, firstName, secondName);
}

string friendshipGraph::nameRangeQuery(string firstName, string secondName){
    string answer;
    nameRange(answer, root, firstName, secondName);
    return answer;

}



void printAllHelper(Node* root){
    if(!root) return;
    printAllHelper(root->left);
    std::ifstream is ("profileData.txt", std::ifstream::in);
    if(is){
        is.seekg(root->index);
    }
    string info;
    getline(is, info);
    cout<<info<<", friends: ";
    for(int i=0;i<root->friends.size();i++){
        cout<<root->friends[i]<<",";
    }
    cout<<endl;
    printAllHelper(root->right);
}

void friendshipGraph::printAll(){
    printAllHelper(root);
}

void printTreeHelper(Node* n){
    if(!n) return;
    printTreeHelper(n->left);
    cout << n->name << endl;
    printTreeHelper(n->right);
}

void friendshipGraph::printTree(){
    printTreeHelper(root);
    cout << endl << endl;
}


void friendshipGraph::leftRotate(Node* x){
    Node* y = x->right;
    x->right = y->left;
    if(y->left!=NULL) y->left->parent = x;
    y->parent = x->parent;
    if(x->parent==nullptr) root=y;
    else if(x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void friendshipGraph::rightRotate(Node* x){
    Node* y = x->left;
    x->left = y->right;
    if(y->right!=NULL) y->right->parent = x;
    y->parent = x->parent;
    if(x->parent==nullptr) root=y;
    else if(x==x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void friendshipGraph::rbInsert(Node* n){
    //a normal bst insert
    Node* currNode = root;
    Node* prevNode = NULL;
    while(currNode != NULL){
        prevNode = currNode;
        if(n->name.compare(currNode->name)<0) currNode = currNode->left;
        else if(n->name.compare(currNode->name) == 0){
            cout << "Error: non unique name" << endl;
            return;
        }
        else currNode = currNode->right;
    }
    n->parent=prevNode;
    if(prevNode==NULL){
        root = n;
        root->color = false;
        return;
    }
    else if(n->name.compare(prevNode->name)<0) prevNode->left = n;
    else prevNode->right = n;
    //bst insert ends
    if(n->parent->parent == nullptr) return;
    while(n!=root&&n->parent->color){

        Node* uncle;
        if(n->parent->parent->left==n->parent){ 
            uncle=n->parent->parent->right;
            if(uncle && uncle->color){
                n->parent->color = false;
                uncle->color = false;
                n->parent->parent->color = true;
                n = n->parent->parent;
            }
            else{ 
                if(n == n->parent->right){
                    n = n->parent;
                    leftRotate(n);
                }
                n->parent->color= false;
                n->parent->parent->color = true;
                rightRotate(n->parent->parent);
            }
        }
        else{
            uncle=n->parent->parent->left;
            if(uncle && uncle->color){
                n->parent->color = false;
                uncle->color = false;
                n->parent->parent->color = true;
                n = n->parent->parent;
            }
            else{
                if(n == n->parent->left){
                    n = n->parent;
                    rightRotate(n);
                }
                n->parent->color= false;
                n->parent->parent->color = true;
                leftRotate(n->parent->parent);
            }
        }
    } 
    root->color=false;
        
    

}

void friendshipGraph::insert(string name, int age, string occupation){
    Node* n = new Node();
    n->index=currIndex;
    currIndex+=56;
    n->name = name;
    n->color = true;
    ofstream output;
    output.open("profileData.txt", ios::app);
    if(output.is_open()){
        output<<setw(20);
        output<<name;
        output<<setw(1);
        output<<",";
        output<<setw(3);
        output<<to_string(age);
        output<<setw(1);
        output<<",";
        output<<setw(30);
        output<<occupation<<endl;
    }
    rbInsert(n);

}


void friendshipGraph::addFriend(string name1, string name2){
    Node* n1 = findPerson(name1, root);
    Node* n2 = findPerson(name2,root);
    if(!n1||!n2) cout<<"One of the names entered is not in the data base!"<<endl;
    else{
        n1->friends.push_back(name2);
        n2->friends.push_back(name1);
    }
}

void friendshipGraph::initialize(string fileName){
    std::ifstream is (fileName, std::ifstream::in);
    string name;
    string s;
    getline(is,s);
    while(getline(is,name, ',')){
        string ageS;
        getline(is,ageS, ',');
        //cout<<ageS<<endl;
        int age = stoi(ageS);
        string occupation;
        getline(is,occupation,',');
        string friendsS;
        getline(is,friendsS);
        vector<string> friends;
        string temp;
        for(int i=1;i<friendsS.size();i++){
            if(friendsS[i]==','){
                friends.push_back(temp);
                temp="";
            }
            else temp+=friendsS[i];
        }

        Node* n = new Node();
        n->parent= nullptr;
        n->left = nullptr;
        n->right = nullptr;
        n->index=currIndex;
        currIndex+=56;
        n->name = name;
        n->color = true;
        n->friends = friends;
        ofstream output;
        output.open("profileData.txt", ios::app);
        if(output.is_open()){
            output<<setw(20);
            output<<name;
            output<<setw(1);
            output<<",";
            output<<setw(3);
            output<<to_string(age);
            output<<setw(1);
            output<<",";
            output<<setw(30);
            output<<occupation<<endl;
        }
        rbInsert(n);
    }
}