#include <iostream>
using namespace std;
#include "friendshipGraph.h"

void cin_clear(){
    cin.clear();
    cin.ignore(1000, '\n');
}

int main(){
    friendshipGraph friendships;
    cout<<"Friendships! Please provide input file:"<<endl;
    string input;
    cin>>input;
    cin_clear();
    friendships.initialize(input);
    int option;
    while(1){
        cout<<"Friendship graph initialized! Choose option below:"<<endl;
        cout<<"Press one to insert new person."<<endl;
        cout<<"Press two to insert new friendship"<<endl;
        cout<<"Press three to query information"<<endl;
        cout<<"Press four to print all information"<<endl;
        cout<<"Press five to exit"<<endl;
        cin>>option;
        cin_clear();
        if(option==1){
            string name;
            int age;
            string occupation;
            cout<<"Insert name"<<endl;
            getline(cin, name, '\n');
            cout<<"Insert age"<<endl;
            cin>>age;
            cin_clear();
            cout<<"Insert occupation"<<endl;
            getline(cin, occupation, '\n');
            friendships.insert(name, age, occupation);
        }
        else if(option==2){
            string name1;
            string name2;
            cout<<"Insert friend 1:"<<endl;
            getline(cin, name1, '\n');
            cout<<"Insert friend 2:"<<endl;
            getline(cin, name2, '\n');
            friendships.addFriend(name1, name2);
        }
        else if(option==3){
            cout<<"Insert 1 for information between two names, Insert 2 for information of all friends of a user:"<<endl;
            cin>>option;
            cin_clear();
            cout<<"Insert 1 for names, 2 for ages, 3 for occupations: "<<endl;
            if(option==1){
                cin>>option;
                cin_clear();
                string name1;
                string name2;
                cout<<"Insert name1"<<endl;
                getline(cin, name1, '\n');
                cout<<"Insert name2"<<endl;
                getline(cin, name2, '\n');
                if(option==1){
                    cout<<friendships.nameRangeQuery(name1, name2)<<endl;
                }
                else if(option==2){
                    cout<<friendships.ageRangeQuery(name1, name2)<<endl;
                }
                else{
                    cout<<friendships.occupationRangeQuery(name1, name2)<<endl;
                } 
            }
            else{
                cin>>option;
                cin_clear();
                string user;
                cout<<"Insert user name:"<<endl;
                getline(cin, user, '\n');
                if(option==1){
                    cout<<friendships.nameFriendQuery(user)<<endl;
                }
                else if(option==2){
                    cout<<friendships.ageFriendQuery(user)<<endl;
                }
                else{
                    cout<<friendships.occupationFriendQuery(user)<<endl;
                }
            }
        }
        else if(option==4){
            friendships.printAll();
        }
        else break;
    }
    return 0;
}