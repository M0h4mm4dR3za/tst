#include <iostream>

using namespace std;

struct node
{
	int info;
	node *left;
	node *right;
	int Rchilds, Lchilds;
	int height;
};

typedef node *nodeptr;

class AvlTree
{
	public:
		void insert(int,nodeptr &);
		void del(int,nodeptr &);
		void find(int,nodeptr &);
		void counter(int,int,nodeptr);
		void SetNoOfChilds(nodeptr &);
		void preorder(nodeptr);
		void inorder(nodeptr);
		void postorder(nodeptr);
		int bsheight(nodeptr);
		nodeptr srl(nodeptr &);
		nodeptr drl(nodeptr &);
		nodeptr srr(nodeptr &);
		nodeptr drr(nodeptr &);
		int max(int,int);
		int nonodes(nodeptr);
};

int SubTreeSize(nodeptr p)
{
	if(p == NULL)
		return 0;
	else
		return (SubTreeSize(p->left) + 1 + SubTreeSize(p->right));
}

void AvlTree::SetNoOfChilds(nodeptr &p)
{
	if (p!=NULL)
	{
		p->Lchilds= SubTreeSize(p->left);
		p->Rchilds= SubTreeSize(p->right);
		SetNoOfChilds(p->left);
		SetNoOfChilds(p->right);
	}
}

void AvlTree::insert(int x, nodeptr &p)
{
	if (p == NULL)
	{
		p = new node;
		p->info = x;
		p->left = NULL;
		p->right = NULL;
	}
	else
	{
		if (x < p->info)
		{
			insert(x, p->left);
			if ((bsheight(p->left) - bsheight(p->right)) == 2)
			{
				if (x < p->left->info)
				{
					p = srl(p);//second p is the pivote
				}
				else
				{
					p = drl(p);
				}
			}
		}
		else if (x >= p->info)
		{
			insert(x, p->right);
			if ((bsheight(p->right) - bsheight(p->left)) == 2)
			{
				if (x > p->right->info)
				{
					p = srr(p);//second p is the pivote
				}
				else
				{
					p = drr(p);
				}
			}
		}
	}
	int l,r,d;
	l=bsheight(p->left);
	r=bsheight(p->right);
	d=max(l,r);
	p->height = d + 1;
}

void AvlTree::find(int x,nodeptr &p)
{
	if (p == NULL)
	{
		cout<< "Info not found!\n"<<endl;
	}
	else
	{
		if (x < p->info)
		{
			find(x,p->left);
		}
		else if (x>p->info)
		{
			find(x,p->right);
		}
		else
		{
			cout<<"Info found!\n"<<endl;
		}
	}
}

void AvlTree::del(int x, nodeptr &p)
{
	nodeptr d;
	if(p == NULL)
	{
		cout<<"Info not found!\n"<<endl;
	}
	else if(x < p->info)
	{
		del(x, p->left);
	}
	else if(x > p->info)
	{
		del(x, p->right);
	}
	else
	{
 		if((p->left == NULL) && (p->right == NULL))
		{
			d = p;
			p = NULL;
			free(d);
			cout<<"Info deleted successfully.\n"<<endl;
		}
		else if (p->left == NULL)
		{
			d = p;
			p = p->right;
			free(d);
			cout<<"Info deleted successfully.\n"<<endl;
		}
		else if (p->right == NULL)
		{
			d = p;
			p = p->left;
			free(d);
			cout<<"Info deleted successfully.\n"<<endl;
		}
		else
		{
			nodeptr parent= d= p;
			d= d->right;
			while(d->left != NULL)
			{
				if(d->left->left == NULL)
					parent= d;
				d= d->left;
			}
			if(parent == p)
				parent->right= NULL;
			else
				parent->left= NULL;
			p->info= d->info;
			free(d);
		}
	}
}

void AvlTree::counter(int k1, int k2, nodeptr root)
{
	nodeptr q= root;
	int i= 0;
	//RAHE HALLE AVVAL.....
	if(q != NULL)
	{
		if(k1 > q->info)
			counter(k1, k2, q->right);
		if(k1 <= q->info && k2 >= q->info)
		{
			counter(k1, k2, q->left);
			cout<< q->info<<endl;
			counter(k1, k2, q->right);
		}
		if(k2 < q->info)
			counter(k1, k2, q->left);
	}

	//BE ELLATE KAMBOODE VAGHT RAHE HALLE DOVVOM KAMEL NASHODE AST!!!
	/*
	L1:
	if(q != NULL)
	{
		if(k1 > q->info)
			q= q->right;
		if(k1 <= q->info && k2 >= q->info)
		{
			i++;
			if(q == root)
				goto L1;
			if(q->info > root->info)
			{
				i+= q->Lchilds;
				q= q->right;
				goto L1;
			}
			else if(q->info < root->info)
			{
				i+= q->Rchilds;
				q= q->left;
				goto L1;
			}
		}
		if(k2 < q->info)
			q= q->left;
	}
	cout<<i;
	*/
}

void AvlTree::preorder(nodeptr p)
{
	if (p!=NULL)
	{
		cout<<p->info<<"\t";
		preorder(p->left);
		preorder(p->right);
	}
}

void AvlTree::inorder(nodeptr p)
{
	if (p!=NULL)
	{
		inorder(p->left);
		cout<<p->info<<"\t";
		inorder(p->right);
	}
}

void AvlTree::postorder(nodeptr p)
{
	if (p!=NULL)
	{
		postorder(p->left);
		postorder(p->right);
		cout<<p->info<<"\t";
	}
}

int AvlTree::max(int value1, int value2)
{
	return ((value1 > value2) ? value1 : value2);
}

int AvlTree::bsheight(nodeptr p)
{
	if (p == NULL)
	{
		return -1;
	}
	else
	{
		return p->height;
	}
}

nodeptr AvlTree::srl(nodeptr &p1)
{
	nodeptr p2;
	p2 = p1->left;
	p1->left = p2->right;
	p2->right = p1;
	p1->height = max(bsheight(p1->left), bsheight(p1->right)) + 1;
	p2->height = max(bsheight(p2->left), p1->height) + 1;
	return p2;
}

nodeptr AvlTree::srr(nodeptr &p1)
{
	nodeptr p2;
	p2 = p1->right;
	p1->right = p2->left;
	p2->left = p1;
	p1->height = max(bsheight(p1->left), bsheight(p1->right)) + 1;
	p2->height = max(p1->height, bsheight(p2->right)) + 1;
	return p2;
}

nodeptr AvlTree::drl(nodeptr &p1)
{
	p1->left = srr(p1->left);
	return srl(p1);
}

nodeptr AvlTree::drr(nodeptr &p1)
{
	p1->right = srl(p1->right);
	return srr(p1);
}

int main()
{
	nodeptr root;
	int a,choice,findele,delele;
	AvlTree avl;
	root = NULL;
	do
	{
		cout<< "\t\t\t\tAVL TREE"<<endl;
		cout<< "\t\t\t\t--------\n";
		cout<< "\n\t1.Insert a new node"<<endl;
		cout<< "\t2.Search a value"<<endl;
		cout<< "\t3.Delete a value"<<endl;
		cout<< "\t4.K1< x <K2"<<endl;
		cout<< "\t5.Display Preorder"<<endl;
		cout<< "\t6.Display Inorder"<<endl;
		cout<< "\t7.Display Postorder"<<endl;
		cout<< "\t8.Display the height of the tree"<<endl;
		cout<< "\t0.Exit"<<endl;
		cout<< "\n\t::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl;
		cout<< "\n\tEnter the choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"\nADDING NEW NODE"<<endl;
				cout<<"---------------"<<endl;
				cout<<"Enter a new value: ";
				cin>>a;
				avl.insert(a, root);
				avl.SetNoOfChilds(root);
				cout<<"\nThe New Node Have Been Added To The AVL Tree Successfully.\n"<<endl;
				break;
			case 2:
				cout<< "\nSEARCHING A VALUE"<<endl;
				cout<< "-----------------"<<endl;
				cout<< "Enter node to search: ";
				cin>> findele;
				if (root != NULL)
				{
					avl.find(findele,root);
				}
				break;
			case 3:
				cout<< "\nDELETING A NODE"<<endl;
				cout<< "-----------------"<<endl;
				cout<< "\nEnter value to delete: ";
				cin>> delele;
				avl.del(delele, root);
				avl.SetNoOfChilds(root);
				avl.inorder(root);
				cout<< endl;
				break;
			case 4:
				int k1,k2;
				cout<< "\nK1< x <K2"<<endl;
				cout<< "----------"<<endl;
				cout<< "\nEnter k1: ";
				cin>> k1;
				cout<< "\nEnter k2: ";
				cin>> k2;
				cout<<"\nValues between k1 and k2:\n";
				avl.counter(k1, k2, root);
				cout<< endl;
				break;
			case 5:
				cout<< "\nPRE-ORDER TRAVERSAL"<<endl;
				cout<< "-----------------"<<endl;
				avl.preorder(root);
				cout<< endl;
				break;
			case 6:
				cout<< "\nIN-ORDER TRAVERSAL"<<endl;
				cout<< "-----------------"<<endl;
				avl.inorder(root);
				cout<< endl;
				break;
			case 7:
				cout<<"\nPOST-ORDER TRAVERSAL"<<endl;
				cout<< "-----------------"<<endl;
				avl.postorder(root);
				cout<< endl;
				break;
			case 8:
				cout<< "\nHEIGHT OF THE TREE"<<endl;
				cout<< "-----------------"<<endl;
				cout<< "The height of the tree is: "<<avl.bsheight(root)<<endl;
				break;
			case 0:
				break;
			default:
				cout<<"Wrong input!\n"<<endl;
				break;
		}
	system("pause");
	system("cls");
	}while(choice != 0);
	return 0;
}