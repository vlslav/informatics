#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <vector>
#include <cmath>
using namespace std;

template <typename T>
class Tree{
public:
    Tree(): high(0), root(NULL){};
    ~Tree();
    struct Leaf{
        T element;
        Leaf *Right;
        Leaf *Left;
        Leaf *parent;
    };
    Leaf *root;
    int high;
    void Del(Leaf *kot);
    void insert(T& d);
    void print_inorder();
    void beginascendinground();
	void inorder(Leaf*);
	T* findtheleast();
	int Search(Leaf* root);
    bool isEmpty() const { return root==NULL; }

protected:
    void ascendinground(Leaf* L);
};
template <class T>
void Tree<T>::insert(T& d)
{
	Leaf* t = new Leaf;
	t->element = d;
	t->Left = NULL;
	t->Right = NULL;
	t->parent = NULL;
	//
	if (isEmpty())
	{
		root = t;
	}
	else
	{
		Leaf* curr;
		curr = root;
		while(curr)
		{
			t->parent = curr;
			if(t->element > curr->element) curr = curr->Right;
			else curr = curr->Left;
		}

		if(t->element < t->parent->element)
			t->parent->Left = t;
		else
			t->parent->Right = t;
	}
}

template <class T>
T* Tree<T> :: findtheleast()
{
	if(root == NULL)
		return NULL;

	Leaf* ptr = root;
	while(ptr->Left!=NULL)
	{
		ptr=ptr->Left;
	}
	return &ptr->element;
}
template <typename T>
void Tree <T> :: Del(Leaf *kot){
    if (kot!=NULL)
    {
        Del(kot->Left);
        Del(kot->Right);
        delete kot;
    }
}
template<class T>
void Tree<T>::print_inorder()
{
	inorder(root);
}
template<class T>
void Tree<T>::inorder(Leaf* p)
{
	if(p != NULL)
	{
		if(p->Left) inorder(p->Left);
		cout<<" "<<p->element<<" ";
		if(p->Right) inorder(p->Right);
	}
	else return;
}

template <class T>
void Tree <T>::beginascendinground()
{
    if (root)
    {
        ascendinground(root);
    }
    else
        cout<<"  Tree is empty"<<endl;
}

template <class T>
void Tree <T>::ascendinground(Leaf* L)
{
    if (L->Left)
        ascendinground(L->Left);
    if (L->Right)
        ascendinground(L->Right);
    cout<<" "<<L->element;
}
template <class T>
int Tree<T>::Search(Leaf* root){
	Leaf *pv = root, *prev;
	bool found = false;
	T element1;
	cout << "Enter the student/professor to search for:" << endl;
	cin >> element1;
	while (pv && !found)
	{
		prev = pv;
		if (element1 == pv->element) found = true;
		else if (element1 < pv->element) pv = pv->Left;
		else pv = pv->Right;
	}
	if (found) return 1;
	else return 0;
}

class Student{
    public:
    string surname;
    string name;
    string patronymic;
    string group;
    bool operator<(Student& p1)
    {
        if(strcmp(surname.c_str(),p1.surname.c_str())<0) return 1;
        else return 0;
    }
    bool operator>(Student& p1)
    {
        if(strcmp(surname.c_str(),p1.surname.c_str())<0)return 0;
        else return 1;
    }
	bool operator==(Student& p1)
	{
		if (strcmp(surname.c_str(), p1.surname.c_str()) == 0) return 1;
		else return 0;
	}

    friend ostream& operator<<(ostream& os, Student& petr){
        os << petr.surname << " " << petr.name << " " << petr.patronymic << " " << petr.group << endl;
        return os;
    }
    friend istream& operator>>(istream& is, Student& petr){
        is >> petr.surname;
        is >> petr.name;
        is >> petr.patronymic;
        is >> petr.group;
        return is;
    }
};
class Professors{
    public:
    string surname;
    string name;
    string patronymic;
    string subject;
    bool operator<(Professors& p1){
        if(strcmp(surname.c_str(),p1.surname.c_str())<0)return 1;
        else return 0;
        }
     bool operator>(Professors& p1){
        if(strcmp(surname.c_str(),p1.surname.c_str())<0)return 0;
        else return 1;
    }
    friend ostream& operator<<(ostream& os, Professors& petr){
        os << petr.surname << " " << petr.name << " " << petr.patronymic << " " << petr.subject << endl;
        return os;
    }
    friend istream& operator>>(istream& is, Professors& petr){
        is >> petr.surname;
        is >> petr.name;
        is >> petr.patronymic;
        is >> petr.subject;
        return is;
    }

};

template <typename T>
Tree <T> :: ~Tree(){
    this->Del(root);
}


int main(){
    Tree <Student> Stud1;
	int ch;

	Student petr;
	while(1)
	{
		cout<<endl<<endl;
		cout<<" Binary Search Tree Operations "<<endl;
		cout<<" ----------------------------- "<<endl;
		cout<<" 1. Insertion/Creation "<<endl;
		cout<<" 2. Show In-Order "<<endl;
		cout<<" 3. Find the least element"<<endl;
		cout<<" 4. Ascending bypass"<<endl;
		cout<<" 5. The search element to the entry" << endl;
		cout<<" 6. Exit "<<endl;
		cout<<" Enter your choice : ";
		cin>>ch;
		switch(ch)
		{
		case 1 : cout<<" Enter data to be inserted : ";
			cin.ignore(1);
			cin >> petr;
			Stud1.insert(petr);
			break;
		case 2 : cout<<endl;
			cout<<" In-Order Traversal "<<endl;
			cout<<" -------------------"<<endl;
			Stud1.print_inorder();
			break;
		case 3 : cout<<endl;
		{
		 	 Student* minStud = Stud1.findtheleast();
		 	 if ( minStud == NULL)
		 	 	cout<<"Tree is empty"<<endl;
		 	 else
		 	 {
		 	 	cout<<"The least element is";
		 	 	cout<<"	"<<*minStud<<endl;
		 	 }
		 	break;
		 }
		case 4 : cout<<endl;
            cout<<" ascending bypass "<<endl;
            cout<<" *****************"<<endl;
            Stud1.beginascendinground();
            break;
		case 5:
			cout << endl;
			if (Stud1.Search(Stud1.root) == 1){
				cout << "The student was found";
			}
			else cout << "The student is not found";
			break;
		case 6 : system("pause");
				return 0;
				break;

		}
	}
}
