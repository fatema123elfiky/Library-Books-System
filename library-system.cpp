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
bool person(string s){
    for(auto ch :s){
        if(isdigit(ch))
            return false;
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
    friend istream& operator>>(istream& in, library& e);
    bool operator== ( library & l );
    ~library(){
        counter--;
    }
    static void view_lib(const vector<library*> & v,bool target) ;
    string name_book(){
     return name;
    }
};

int library::counter=0;

class EBook:public library{
public:
    void book_info() override{
        cout<<"Name : "<<name<<'\n'
        <<"Type : E-book"<<'\n'
        <<"Editor : "<<editor<<'\n'
        <<"Writer : "<<writer<<'\n'
        <<"Price : "<<price<<'\n'<<"Description : "<<description<<"\n\n";
    }
      EBook() {
        type=true;
     counter++;
    }
};

class PrintedBook:public library{
public:
    void book_info() override{
        cout<<"Name : "<<name<<'\n'
            <<"Type : Printed-book"<<'\n'
            <<"Editor : "<<editor<<'\n'
            <<"Writer : "<<writer<<'\n'
            <<"Price : "<<price<<'\n'<<"Description : "<<description<<"\n\n";
    }
    PrintedBook(){
        type=false;
        counter++;
    }
};
//functions of some  classes
istream& operator>>(istream& in, library& e){
    in.ignore();
    cout<<"Enter the name : ";getline(in,e.name) ;//in.ignore();
    cout<<"Enter the description : "; getline(in,e.description);

    cout<<"Enter the editor name : ";getline(in,e.editor);
    while (!person(e.editor)){
        cout<<"Enter a valid name : ";
        getline(in,e.editor);
    }
    cout<<"Enter the writer name : ";getline(in,e.writer);
    while (!person(e.writer)){
        cout<<"Enter a valid name : ";
        getline(in,e.writer) ;
    }
    string price;
    cout<<"Enter the price : ";getline(in,price);
    while (!numeric(price)){
        cout<<"Enter a valid price : ";getline(in,price);
    }
    e.price=stoi(price);
    return  in;

}

bool library:: operator== ( library&  l){
return (l.type==type&&l.name==name&&l.price==price&&l.writer==writer&&l.editor==editor&&
  l.description==description);

}

void library::view_lib(const vector<library*> & v,bool target) {
    int cntr=1;
    cout<<"\n\n==============================\n\n";
     for (int i = 0; i < v.size(); ++i) {
         if(v[i]->type==target){
             cout<<cntr<<"."<<v[i]->name<<'\n';
             cntr++;
         }
     }
     if(cntr==1)
         cout<<"The library now is empty of that type :(\n";
    cout<<"\n\n==============================\n\n";
    return ;
}





int main()
{

cout<<"\n\n\n                    ############ Welcome to The library system ############ \n\n\n";
vector<library *>books;// carry the info of the library
vector<library*>borrow;
    while (true){
        cout<<"##### The Menu #####\n\n";
        cout<<"1.Add a book\n";
        if(!borrow.empty()){
            cout<<"2.Return a book\n"; }
        if(!books.empty()){
            cout<<"3.Borrow a book\n4.View a book's info\n5.View the library's info\n";
        }
        cout<<"6.Exit\n";
        cout<<"Please choose from the menu : ";
        string choice;cin>>choice;
        //validation part
        if(!books.empty()){
            if(!borrow.empty()){
                while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" &&
                       choice != "6") {
                    cout << "Please Enter a valid choice : ";
                    cin >> choice;
                }
            }else{
                while (choice != "1"  && choice != "3" && choice != "4" && choice != "5" &&
                       choice != "6") {
                    cout << "Please Enter a valid choice : ";
                    cin >> choice;
                }

            }
        }else{
            if(borrow.empty()){
                while (choice != "1" && choice != "6") {
                    cout << "Please Enter a valid choice : ";
                    cin >> choice;
                }
            }else{
                while (choice != "1"&&choice!="2" && choice != "6") {
                    cout << "Please Enter a valid choice : ";
                    cin >> choice;
                }
            }
        }
        if(choice=="1"){//add a book
            repeat:
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
                for (int i = 0; i < books.size(); ++i) {

                    if(*(books[i])==*e){
                      cout<<"This book is already in the library!\n "
                            "Please Enter a new book\n\n";
                      delete e;
                     goto repeat;

                    }
                }
                books.push_back(e);
            }
            else {
                library * p=new PrintedBook();cin>>*p;
                for (int i = 0; i < books.size(); ++i) {
                    if(*(books[i])==*p){
                        cout<<"This book is already in the library!\n "
                              "Please Enter a new book\n\n";
                       delete p;
                        goto repeat;
                    }
                }
                books.push_back(p);
            }

        }
        else if(choice=="2"){// return a book

        }
        else if(choice=="3"){// borrow
           cout<<"Which Book you want to borrow ?\n";
            for (int i = 0; i < books.size(); ++i) {
                cout<<i+1<<"."<<books[i]->name_book()<<'\n';
            }
            cout<<"Enter your choice : ";
            string choose;
            again2:
            cin>>choose;
            if(!numeric(choose)) {
                cout<<"Please Enter a valid choice : ";
                goto again2;
            }
            if (stoi(choose)<1||stoi(choose)>books.size()){
                cout<<"Please Enter a valid choice : ";
                goto again2;
            }
            borrow.push_back(books[stoi(choose)-1]);
           delete books[stoi(choose)-1];
            books.erase(stoi(choose)-1+books.begin());

        }
        else if(choice=="4"){// view book info
         cout<<"Which Book do you Want ?\n\n";
            for (int i = 0; i < books.size(); ++i) {
                cout<<i+1<<"."<<books[i]->name_book()<<'\n';
            }
            cout<<"Enter your choice : ";
            again:
            string choose;cin>>choose;
            if(!numeric(choose)) {
                cout<<"Please Enter a valid choice : ";
                goto again;
            }
           if (stoi(choose)<1||stoi(choose)>books.size()){
                cout<<"Please Enter a valid choice : ";
                goto again;
            }
            books[stoi(choose)-1]->book_info();
        }
        else if(choice=="5"){//view the library info
          cout<<"Which section you want to see ?\n1.E-books\n2.Printed-books\nEnter your choice : ";
          string choose;cin>>choose;
          //validation part
            while (choose!="1"&& choose!="2"){
                cout<<"Please Enter a valid choice : ";cin>>choose;
            }
            //implementation part
            if(choose=="1"){
                library::view_lib(books,true);
            }else{
               library::view_lib(books,false);
            }
        }
        else{// close
            cout<<"\n\n      ######## Thanks for using that system :) ######## \n\n";
            break;
        }




    }



}