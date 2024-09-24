#include<iostream>
#include<vector>
using namespace std;
//1. static variables are inherited
//and works among the parent class and the children classes too

// some instructions to work on it
// library --> parent--> static variable (count books)--> view library--> info book--> show info book as it is common
//(call the function that shows  weather ebooks printed)--> view virtual one as according to which one
// printed books --> child--> view them
// e-books --> child-->view them
// vector<ptrs of library>
//borrow -->erase from the vector
//return --> back again to the vector
// return and adding take care it is not here so overloading
// for operator of ==
// borrow take care from borrowing something it not valid by map
//view book  not virtual function

// the code
// functions of repeated validations
bool numeric(string s){
    for(auto ch: s){
        if(!isdigit(ch)){ return false; }
    }
    return true;
}



//classes
class library {
protected:
    string name, description,editor,writer;
    bool type;//ebook -->1 printed -->0
    int price;
    static int counter;
public:
    virtual void book_info()=0;
    void set_value(string n, string des,string edi,string writer,int price,bool type ){
        this->name=n;this->description=des;
        this->editor=edi;this->writer=writer;
        this->price=price;this->type=type;
        counter++;
    }
     friend istream& operator>>(istream& in, library& e);
};

int library::counter=0;

class EBook:public library{
    void book_info() override{
        cout<<"Name : "<<name<<'\n'
        <<"Type : E-book"<<'\n'
        <<"Editor : "<<editor<<'\n'
        <<"Writer : "<<writer<<'\n'
        <<"Price : "<<price<<'\n'<<"Description : "<<description<<"\n\n";
    }
    friend istream& operator>>(istream& in, EBook& e);
};

class PrintedBook:public library{
    void book_info() override{
        cout<<"Name : "<<name<<'\n'
            <<"Type : Printed-book"<<'\n'
            <<"Editor : "<<editor<<'\n'
            <<"Writer : "<<writer<<'\n'
            <<"Price : "<<price<<'\n'<<"Description : "<<description<<"\n\n";
    }
    friend istream& operator>>(istream& in, PrintedBook& p);
};
//functions of some  classes
istream& operator>>(istream& in, library& e){
    cout<<"Enter the name : ";cin>>e.name;cin.get();
    cout<<"Enter the description : "; getline(cin,e.description);
    cin.get();
    cout<<"Enter the editor name : ";cin>>e.editor;
    while (numeric(e.editor)){
        cout<<"Enter a valid name : ";
        cin>>e.editor;
    }
    cout<<"Enter the writer name : ";cin>>e.writer;
    while (numeric(e.writer)){
        cout<<"Enter a valid name : ";
        cin>>e.writer;
    }
    string price;
    cout<<"Enter the price : ";cin>>price;
    while (!numeric(price)){
        cout<<"Enter a valid price : ";cin>>price;
    }
    e.price=stoi(price);
e.type= true;
}

/*istream& operator>>(istream& in, PrintedBook& p){
    cout<<"Enter the name : ";cin>>p.name;
    cin.get();
    cout<<"Enter the description : "; getline(cin,p.description);
    cin.get();
    cout<<"Enter the editor name : ";cin>>p.editor;
    while (numeric(p.editor)){
        cout<<"Enter a valid name : ";
        cin>>p.editor;
    }
    cout<<"Enter the writer name : ";cin>>p.writer;
    while (numeric(p.writer)){
        cout<<"Enter a valid name : ";
        cin>>p.writer;
    }
    string price;
    cout<<"Enter the price : ";cin>>price;
    while (!numeric(price)){
        cout<<"Enter a valid price : ";cin>>price;
    }
    p.price=stoi(price);
    p.type= false;

}*/




int main()
{
    /*freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);*/

            cout<<"\n\n\n                    ############ Welcome to The library system ############ \n\n\n";
vector<library *>books;// carry the info of the library
    while (true){
        cout<<"##### The Menu #####\n\n";
        cout<<"1.Add a book\n2.Return a book\n";
        if(!books.empty()){
            cout<<"3.Borrow a book\n4.View a book's info\n5.View the library's info\n";
        }
        cout<<"6.Exit\n";
        cout<<"Please choose from the menu : ";
        string choice;cin>>choice;
        while (choice!="1"&&choice!="2"&&choice!="3"&&choice!="4"&&choice!="5"&&choice!="6"){
            cout<<"Please Enter a valid choice : ";
            cin>>choice;
        }
        if(choice=="1"){//add a book

           string type;
            cout<<"Choose from the following the type of the book :\n1.E-Book\n2.Printed-Book\n\n";
            cout<<"Enter the choice : ";cin>>type;
            while (type!="1"&&type!="2"){
                cout<<"Enter a valid choice : ";
                cin>>type;
            }
            if(type=="1")
            {
                library * e= new EBook() ; cin>> *e;
                books.push_back(e);
            }
            else {
                library * p;cin>>*p;
                books.push_back(p);
            }

        }else if(choice=="2"){// return a book

        }else if(choice=="3"){// borrow

        }else if(choice=="4"){// view book info

        }else if(choice=="5"){//view the library info

        }else{// close
            cout<<"\n\n      ######## Thanks for using that system :) ######## \n\n";
            break;
        }




    }



}