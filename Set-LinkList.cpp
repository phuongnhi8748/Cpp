#include <iostream>

using namespace std;
struct Node
{
	int data;
	Node* next;
};
typedef struct Node* pNode;
class Set
{
	protected:
		int n;
		int max;
		pNode Head;
	public:
		Set();
		Set(int max);
		Set(const Set& X);
		~Set();
		void InsertHead(int);
		void InsertTail(int);
		void DelHead();
		void operator+ (int x);
        void operator- (int x);
        const Set operator+ (const Set &X);
        const Set operator- (const Set &X);
        const Set operator* (const Set &X);
        void operator= (const Set &X);
        bool isExist(int x);
        friend ostream& operator<< (ostream& os, const Set &X);
        bool operator() (int x);
};

Set::Set()
{
	max = 0;
	n = 0;
	Head = NULL;
}
Set::Set(int max)
{
	this->max = max;
	this->n = 0;
	this->Head = NULL;
}
Set::Set(const Set& X)
{
	this->max = X.max;
	this->n = X.n;
	this->Head = NULL;
	pNode p = X.Head;
	while (p != NULL)
	{
		this->InsertTail(p->data);
		p = p->next;
	}
}
Set::~Set()
{
	while (Head != NULL) 
	{
		DelHead();
	}
}

void Set::InsertHead(int x)
{
	pNode p = new Node;
	p->data = x;
	p->next = Head;
	this->Head = p;
}

void Set::InsertTail(int x){
	if (Head == NULL) InsertHead(x);
	else
	{
		pNode p = Head;
		while (p->next != NULL)
		{
			p = p->next;
		}
		pNode temp = new Node;
		temp->data = x;
		p->next = temp;
		temp->next = NULL;
	}
}

void Set::DelHead(){
	if (Head != NULL)
	{
		pNode p = Head;
		Head = p->next;
		delete p;
	}
}

bool Set::isExist(int x)
{
	pNode p = Head;
	while (p!=NULL)
	{
		if (p->data == x) return true;
		p = p->next;
	}
	return false;
}

void Set::operator+(int x)
{
	if (this->n+1 <= this->max && !this->isExist(x))
	{
		if (this->n==0)
		{
			this->InsertHead(x);
			this->n++;
		}
		else
		{
			pNode p = Head;
			if (p->data > x)
			{
				InsertHead(x);
				this->n++;
			}
			else
			{
				bool isInsert = false;
				while (p!=NULL)
				{
					if (p->next == NULL && p->data < x)
					{
						InsertTail(x);
						this->n++;
						isInsert = true;
					}
					p = p->next;
				}
				if (!isInsert)
				{
					pNode temp = new Node, q=NULL;
					p=Head;
					while(p!=NULL)
					{
						q=p->next;
						if (q->data > x)
						{
							temp->data = x;
							temp->next = p->next;
							p->next = temp;
							break;
						}
						p=p->next;
					}
					this->n++;
				}
			}
		}
	}
}

void Set::operator- (int x)
{
	if (Head != NULL) 
	{
		pNode p = Head, q = NULL;
		if (p->data == x)
		{
			DelHead();
			this->n--;
		}
		else
		{
			while (p != NULL)
			{
				q = p->next;
				if (q!=NULL)
				if (q->data == x)
				{
					p->next = q->next;
					delete q;
					this->n--;
					break;
				}
				p = p->next;
			}
		}
		
    }
}

void Set::operator= (const Set&X)
{
	if (this!=&X)
	{
		this->max = X.max;
		this->n = X.n;
		pNode p = X.Head;
		this->Head = p;
		pNode q = this->Head;
		while (p!=NULL)
		{
			q->data = p->data;
			q = q->next;
			p = p->next;
		}
	}
}

const Set Set::operator* (const Set &X)
{
	Set result(this->max);
	pNode p = this->Head;
	while (p!=NULL)
	{
		pNode q = X.Head;
		while (q!=NULL)
		{
			if (p->data == q->data)
			{
				result+p->data;
				break;
			}
			q = q->next;
		}
		p = p->next;
	}
	return result;
}

const Set Set::operator+ (const Set &X)
{
	Set result(this->max + X.max);
	pNode p = this->Head;
	while (p!=NULL)
	{
		result+p->data;
		p=p->next;
	}
	pNode q = X.Head;
	while(q!=NULL)
	{
		if (!result(q->data)) result+q->data;
		q = q->next;
	}
	return result;
}

const Set Set::operator- (const Set &X)
{
	Set result(this->max);
	result = *this;
	pNode q = X.Head;
	while (q!=NULL)
	{
		result - q->data;
		q=q->next;
	}
	return result;
}

bool Set::operator() (int x)
{
	pNode p = Head;
	while (p!=NULL)
	{
		if (p->data == x) return true;
		p = p->next;
	}
	return false;
}


ostream& operator<< (ostream& os, const Set &X)
{
	pNode p = X.Head;
	if (p == NULL) os<<"Empty";
	else
	while (p != NULL) 
	{
		os<<p->data<<" ";
		p = p->next;
	}
    return os;
}

int main() 
{
    int max, x;
	string c;
	cout<<"Nhap gioi han tap hop: "; cin>>max;
	Set A(max), B(max);
	cout<<"Nhap tap hop A: "<<endl;
    while (true)
	{
		cout<<"Nhap 1 phan tu can them vao tap hop: "; cin>>x;
        A+x;
        cout<<"A = "<<A<<endl;
        cout<<"Tiep? (y/n): "; cin>>c;
        if (c=="n") break;
	}
	cout<<endl;

	cout<<"Nhap tap hop B: "<<endl;
    while (true)
	{
		cout<<"Nhap 1 phan tu can them vao tap hop: "; cin>>x;
        B+x;
        cout<<"B = "<<B<<endl;
        cout<<"Tiep? (y/n): "; cin>>c;
        if (c=="n") break;
	}
	cout<<endl;

	cout<<"Xoa 1 phan tu trong tap hop A: "<<endl;
    while(true)
    {
        cout<<"Nhap 1 phan tu can xoa: "; cin>>x;
        A-x;
        cout<<"A = "<<A<<endl;
        cout<<"Tiep? (y/n): "; cin>>c;
        if (c=="n") break;
    }
	cout<<endl;

	cout<<"Xoa 1 phan tu trong tap hop B: "<<endl;
    while(true)
    {
        cout<<"Nhap 1 phan tu can xoa: "; cin>>x;
        B-x;
        cout<<"B = "<<B<<endl;
        cout<<"Tiep? (y/n): "; cin>>c;
        if (c=="n") break;
    }
	cout<<endl;

    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;
    cout<<"A giao B = A * B = "<<A*B<<endl;
    cout<<"A hop B = A + B = "<<A+B<<endl;
    cout<<"A tru B = A - B = "<<A-B<<endl;
    cout<<endl;

    cout<<"Kiem tra phan tu co thuoc tap hop"<<endl;
    cout<<"Nhap phan tu: "; cin>>x;
    if (A(x)) cout<<x<<" co trong tap A"<<endl;
    else cout<<x<<" khong co trong tap A"<<endl;

    if (B(x)) cout<<x<<" co trong tap B"<<endl;
    else cout<<x<<" khong co trong tap B"<<endl;

	return 0;
}
