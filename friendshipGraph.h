#include <vector>
#include <string>
#ifndef FRIENDSHIP_GRAPH_H
#define FRIENDSHIP_GRAPH_H

class Node{
    public: 
        Node(){};
        ~Node();
        std::string name;
        std::vector<std::string> friends;
        int index;
        Node* left;
        Node* right;
        Node* parent;
        bool color; //true: red, false: black
};


class friendshipGraph{
    public:
        Node* root;
        int currIndex;
        friendshipGraph(){
            currIndex=0;
        }
        std::string nameFriendQuery(std::string name);
        std::string ageFriendQuery(std::string name);
        std::string occupationFriendQuery(std::string name);
        std::string nameRangeQuery(std::string firstName, std::string secondName);
        std::string ageRangeQuery(std::string firstName, std::string secondName);
        std::string occupationRangeQuery(std::string firstName, std::string secondName);
        void printAll();
        void printTree();
        void initialize(std::string fileName);
        void insert(std::string name, int age, std::string occupation);
        void addFriend(std::string name1, std::string name2);
        void rbInsert(Node* n);
        void leftRotate(Node* x);
        void rightRotate(Node*x);

};

#endif