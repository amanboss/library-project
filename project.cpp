
#include <iostream>
#include <queue>
#include <string>
using namespace std;
class student
{
public:
  string name;
  string department;
  bool status;
  int member_id;
  int no_of_books_issued;
  int fine;
};

class book
{
public:
  string name_book;
  string subject;
  string auther;
  int accsession_no;
  int no_of_copies;
  int year_of_publish;
  bool is_available;
};
class node : public student, public book
{
public:
  int data, height;
  node *left;
  node *right;
  node(int d)
  {
    data = d;
    height = 1;
    left = NULL;
    right = NULL;
  }
};

int height(node *N)
{
  if (N == NULL)
    return 0;
  return N->height;
}
node *leftrotate(node *root)
{
  node *temp = root->right;
  node *temp2 = root->right->left;
  root->right = temp2;
  temp->left = root;
  root->height = 1 + max(height(root->left), height(root->right));
  temp->height = 1 + max(height(temp->left), height(temp->right));
  return temp;
}

node *rightrotate(node *root)
{
  node *temp = root->left;
  node *temp2 = root->left->right;
  root->left = temp2;
  temp->right = root;
  root->height = 1 + max(height(root->left), height(root->right));
  temp->height = 1 + max(height(temp->left), height(temp->right));
  return temp;
}
node *insert_AVL(node *root, node *curr, int d)
{
  if (root == NULL)
  {
    // node * temp=new node(d);
    return curr;
  }
  else if (root->data > d)
  {
    root->left = insert_AVL(root->left, curr, d);
  }
  else if (root->data < d)
    root->right = insert_AVL(root->right, curr, d);
  else
    return root;
  root->height = 1 + max(height(root->left), height(root->right));
  int balance = (height(root->left) - height(root->right));
  if (balance > 1)
  {
    if (root->left->data > d)
      return rightrotate(root);
    else
    {
      root->left = leftrotate(root->left);
      return rightrotate(root);
    }
  }
  else if (balance < -1)
  {
    if (root->right->data < d)
      return leftrotate(root);
    else
    {
      root->right = rightrotate(root->right);
      return leftrotate(root);
    }
  }
  return root;
}
bool search_data(node *root, int d)
{
  if (root == NULL)
    return false;
  if (root->data == d)
    return true;
  else if (root->data < d)
    return search_data(root->right, d);
  else
    return search_data(root->left, d);
}
node *show_data(node *root, int d)
{
  if (search_data(root, d))
  {
    if (root->data == d)
      return root;
    else if (root->data > d)
      return show_data(root->left, d);
    else
      return show_data(root->right, d);
  }
  else
    return NULL;
}
node *find_min(node *root)
{
  node *temp = root;
  while (temp != NULL)
    temp = temp->left;
  return temp;
}
node *find_max(node *root)
{
  node *temp = root;
  while (temp != NULL)
    temp = temp->right;
  return temp;
}

int countnode(node *root)
{
  if (root == NULL)
    return 0;
  int leftcount = countnode(root->left);
  int rightcount = countnode(root->right);
  return 1 + leftcount + rightcount;
}

node *delete_node(node *root, int d)
{
  if (root == NULL)
    return NULL;
  if (root->data == d)
  {
    if (root->left == NULL && root->right == NULL)
    {
      delete root;
      return NULL;
    }
    else if (root->left == NULL && root->right != NULL)
    {
      node *temp = root->right;
      delete root;
      return temp;
    }
    else if (root->left != NULL && root->right == NULL)
    {
      node *temp = root->left;
      delete root;
      return temp;
    }
    else
    {
      int mini = find_min(root->right)->data;
      root->data = mini;
      root->right = delete_node(root->right, mini);
      return root;
    }
  }
  else if (root->data > d)
  {
    root->left = delete_node(root->left, d);
  }
  else
  {
    root->right = delete_node(root->right, d);
  }
  root->height = 1 + max(height(root->left), height(root->right));
  int balance = (height(root->left) - height(root->right));
  if (balance > 1)
  {
    if (root->left->data > d)
      return rightrotate(root);
    else
    {
      root->left = leftrotate(root->left);
      return rightrotate(root);
    }
  }
  else if (balance < -1)
  {
    if (root->right->data < d)
      return leftrotate(root);
    else
    {
      root->right = rightrotate(root->right);
      return leftrotate(root);
    }
  }
  return root;
}

void leveltraversal(node *root)
{
  cout << endl;
  queue<node *> q;
  q.push(root);
  q.push(NULL);
  while (!q.empty())
  {
    node *temp = q.front();
    q.pop();
    if (temp == NULL)
    {
      cout << endl;
      if (!q.empty())
        q.push(NULL);
    }
    else
    {
      cout << temp->data << " ";
      if (temp->left)
      {
        q.push(temp->left);
      }
      if (temp->right)
      {
        q.push(temp->right);
      }
    }
  }
}
void menu_display()
{
  cout << "=======================================================================" << endl;
  cout << "Hello thank's for visiting our library  " << endl;
  cout << "You can perform following operation in our library" << endl;
  cout << "press 1 : for Registration of a member into the library" << endl;
  cout << "press 2 : for adding a new book into library" << endl;
  cout << "press 3 : for searching the book presernt  in the library" << endl;
  cout << "press 4 : for searching the details of student registered in the library" << endl;
  cout << "press 5 : for checking all available books in library" << endl;
  cout << "press 6 : for checking all registered students in the library" << endl;
  cout << "press 7 : for issuing an available book" << endl;
  cout << "press 0 : exit " << endl;
  cout << "=======================================================================" << endl;
}

void add_book(node *&kitab)
{
  int number;
  cout << "Please Enter the book number" << endl;
  cin >> number;
  
  node *curr = new node(number);
  curr->accsession_no = number;
  string s1, s2, a1;
  int y;
  cout << "Please Enter book name then subject name and then auther name all are space separated " << endl;
  cin >> s1 >> s2 >> a1;
  curr->name_book = s1;
  curr->subject = s2;
  curr->auther = a1;
  // cout << "Please enter year of publish " << endl;
  // cin >> y;
  // curr->year_of_publish = y;
  cout << "Please enter the copies of book" << endl;
  cin >> curr->no_of_copies;
  kitab = insert_AVL(kitab, curr, number);
  // }

  cout << "Book has been added succesfully in our library" << endl;
}
void book_details(node *&kitab)
{
  int d1;
  cout << "please enter the book no" << endl;
  cin >> d1;
  if (show_data(kitab, d1) != NULL)
  {
    cout << "Displaying the details of book" << endl;
    node *curr = show_data(kitab, d1);
    cout << "Book name is " << curr->name_book << endl;
    cout << "Subject name is " << curr->subject << endl;
    cout << "Auther name is " << curr->auther << endl;
    cout << " book number is " << curr->accsession_no << endl;
    // cout << "Year of publish is " << curr->year_of_publish << endl;
  }
  else
  {
    cout << "No such book is present in the library" << endl;
  }
}
void add_new_member(node *&mem)
{

  int d;
  cout <<"Please Enter your id number"<< endl;
  cin >> d;
  node *curr = new node(d);
  curr->accsession_no = d;
  curr->status = true;
  curr->member_id = d;
  cout << "please Enter your name" << endl;
  cin >> curr->name;
  cout << "Please Enter your department" << endl;
  cin >> curr->department;
  curr->no_of_books_issued = 0;
  curr->fine = 0;
  mem = insert_AVL(mem, curr, d);

  cout << "Your Registration is completed" << endl;
}

void student_details(node *&mem)
{
  int d;
  cout << "Please enter your id number" << endl;
  cin >> d;
  if (show_data(mem, d) != NULL)
  {
    cout << "Displaying the details of student" << endl;
    node *curr = show_data(mem, d);
    cout << "Name of student is " << curr->name << endl;
    cout << "Department is " << curr->department << endl;
    cout << "No of books issued is " << curr->no_of_books_issued << endl;
  }
  else
  {
    cout << "No such student is here with given id number" << endl;
  }
}
void pre_order_traversal(node *root)
{
  if (root == NULL)
    return;
  if (root->left)
    pre_order_traversal(root->left);
  if (root->data != -1 && root->no_of_copies > 0)
  {
    cout << "book name    "
         << "accession numer     "
         << "books available" << endl;
    cout << root->name_book << "     " << root->data << "       " << root->no_of_copies;
  }
  if (root->right)
    pre_order_traversal(root->right);
}
void pre_order_traversal1(node *root)
{
  if (root == NULL)
    return;
  if (root->left)
    pre_order_traversal1(root->left);
  if (root->data != -1)
  {
    cout << root->name << "   " << root->data << "     " << root->no_of_books_issued << "      " << root->fine << endl;
  }
  if (root->right)
    pre_order_traversal1(root->right);
}
void all_books_data(node *kitab)
{
  cout << " Displaying the details of all available books" << endl;
  pre_order_traversal(kitab);
}
void all_students_data(node *mem)
{
  cout << "Displaying the details of all registered students" << endl;
  cout << "name       "
       << "user id     "
       << "no of books issued"
       << " fine" << endl;
  pre_order_traversal1(mem);
}

int cal_fine(int date1,int month1,int year1,int date2,int month2,int year2)  {
  if (year1>year2)
  return 0;
  if (year1==year2) {
    if (month1==month2) {
      if (date2-date1>=0)
      return date2-date1;
      else 
      return 0;
    }
    else if (month1>month2)
    return 0;
  }
}
void issue_book(node *mem, node *kitab)
{
  int d;
  cout << "please enter your id number" << endl;
  cin >> d;
  if (show_data(mem, d) != NULL)
  {
    node *curr = show_data(mem, d);
    cout << "Please enter book number" << endl;
    int d1;
    cin >> d1;
    if (show_data(kitab, d1) != NULL)
    {
      node *temp = show_data(kitab, d1);
      if (temp->no_of_copies > 0)
      {
        curr->no_of_books_issued++;
        cout << "enter date of issuing of book then month and then year all are space separated"<<endl;
        int date1,month1,year1;
        cin>>date1>>month1>>year1;
        cout<<"enter the date when you will return the book then month and then year all are space separated"<<endl;
        int date2,month2,year2;
        cin>>date2>>month2>>year2;
        curr->fine=cal_fine(date1,month1,year1,date2,month2,year2);
        cout << "Successfully you have issued " << temp->name_book<<endl;
        temp->no_of_copies--;
      }
      else
      {
        cout << "currently book is not in library " << endl;
      }
    }
    else
    {
      cout << "no such book is available in our library" << endl;
    }
  }
  else
  {
    cout << "You have not yet registered or you entered wrong id no" << endl;
  }
}
int main()
{
  node *kitab = new node(-1);
  node *mem = new node(-1);

  int choice = 11;
  while (choice != 0)
  {
    menu_display();
    cout << "enter the choice" << endl;
    cin >> choice;
    if (choice == 1)
    {
      add_new_member(mem);
    }
    else if (choice == 2)
    {
      add_book(kitab);
    }
    else if (choice == 3)
    {
      book_details(kitab);
    }
    else if (choice == 4)
    {
      student_details(mem);
    }
    else if (choice == 5)
    {
      all_books_data(kitab);
    }
    else if (choice == 6)
    {
      all_students_data(mem);
    }
    else if (choice == 7)
    {
      issue_book(mem, kitab);
    }
    else if (choice == 0)
    {
      break;
    }
    else
    {
      cout << "Your choice is unappropriate. please try again" << endl;
    }
  }
  cout << "Thanks for visiting. Have a nice day " << endl;
  //  root=insert_AVL(root,10);
  //  root=insert_AVL(root,20);
  //  // leveltraversal(root);
  //  root=insert_AVL(root,30);
  //  cout<<countnode(root);
  //  root=insert_AVL(root,40);
  //  // leveltraversal(root);
  //  root=insert_AVL(root,45);
  //  // leveltraversal(root);
  //  leveltraversal(root);
  //  root=delete_node(root,45);
  //  root=insert_AVL(root,50);
  //   leveltraversal(root);
  //  root=delete_node(root,10);
  //  leveltraversal(root);
  //  cout<<countnode(root);
  // node * root=NULL;
  // root=insert_AVL(root,20);
  // root=insert_AVL(root,39);
  // root=insert_AVL(root,9);
  // root=insert_AVL(root,129);
  // root=insert_AVL(root,34);
  // root=insert_AVL(root,459);
  // if (show_data(root,129)!=NULL) {
  //   cout<<"data is present"<<endl;
  // }
  // else {
  //   cout<<"No such data is present"<<endl;
  // }
  // leveltraversal(mem);

  return 0;
}