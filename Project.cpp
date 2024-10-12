#include<iostream>
#include<string>
using namespace std;
struct Book{
    int id;
    string title;
    string author;
    bool isAvailable;
};
struct issuedPerson{
    int bookId;
    string name;
    string number;
};
class library{
    private:
    Book books[100]={
        {110,"A Time to Kill","John grisham",true},
        {114,"The House of Mirth","Edith Wharton",true},
        {118,"Inheritance","Elizabeth Acadova",false},
        {122,"The Girl on the Train","Ruskin Bond",true},
        {126,"Kabuliwala","Rabindranath Tagore",false}
    };
    issuedPerson issue_arr[100];
    int count=5;
    int issue_count=0;
    public:
    int getcount(){
        return count;
    }
    int issueCount(){
        return issue_count;
    }
    int binarySearch(int id){
        int low=0;
        int high=count-1;
        while(low<=high){
            int mid=(low+high)/2;
            if(books[mid].id==id){
                return mid;
            }else if(books[mid].id<id){
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return -1;
    }
    void addBook(){
        Book obj;
        cout<<"Enter book id: ";
        cin>>obj.id;
        if(binarySearch(obj.id)!=-1){
            cout<<"Book with ID "<<obj.id<<" already exists"<<endl;
            return;
        }
        cout<<"Enter the Title of the book: ";
        cin.ignore();
        getline(cin,obj.title);
        cout<<"Enter the Author of the book: ";
        getline(cin,obj.author);
        obj.isAvailable=true;
        books[count]=obj;
        count++;
        mergeSort(0,getcount()-1);
    }
    void mergeSort(int low, int high) {
        if (low < high) {
            int mid = (low + high) / 2;
            mergeSort(low, mid);
            mergeSort(mid + 1, high);
            merge(low, mid, high);
        }
    }
    void merge(int low, int mid, int high) {
        Book left[mid - low + 1];
        Book right[high - mid];
        int i, j, k;
        for (i = 0; i < mid - low + 1; i++) {
            left[i] = books[low + i];
        }
        for (j = 0; j < high - mid; j++) {
            right[j] = books[mid + 1 + j];
        }
        i =j = 0;
        k = low;
        while (i < mid - low + 1 && j < high - mid) {
            if (left[i].id <= right[j].id) {
                books[k] = left[i];
                i++;
            } else {
                books[k] = right[j];
                j++;
            }
            k++;
        }
        while (i < mid - low + 1) {
            books[k] = left[i];
            i++;
            k++;
        }
        while (j < high - mid) {
            books[k] = right[j];
            j++;
            k++;
        }
    }
    void display(){
        for(int i=0;i<count;i++){
            cout<<"Book ID: "<<books[i].id<<endl;
            cout<<"Title: "<<books[i].title<<endl;
            cout<<"Author: "<<books[i].author<<endl;
            cout<<endl;
        }
    }
    void search(int id){
        if(binarySearch(id)!=-1){
            cout<<"Book ID: "<<books[binarySearch(id)].id<<endl;
            cout<<"Book Title: "<<books[binarySearch(id)].title<<endl;
            cout<<"Book Author: "<<books[binarySearch(id)].author<<endl;
            if(books[binarySearch(id)].isAvailable){
                cout<<"Books are Available"<<endl;
            }else{
                cout<<"Books are not available"<<endl;
            }
        }else{
            cout<<"Book not found!"<<endl;
        }
    }
    void issueBook(int id){
        for(int i=0;i<count;i++){
            if(books[i].id==id){
                if(books[i].isAvailable){
                    issuedPerson obj1;
                    books[i].isAvailable=false;
                    cout<<"Issue person details: "<<endl;
                    cout<<"Book Id: ";
                    cin>>obj1.bookId;
                    cout<<"Name: ";
                    cin.ignore();
                    getline(cin,obj1.name);
                    cout<<"Phone Number: ";
                    getline(cin,obj1.number);
                    issue_arr[issue_count]=obj1;
                    issue_count++;
                    cout<<endl;
                    cout<<".....BOOK ISSUED !....."<<endl;
                }else
                    cout<<"Book is already issued!"<<endl;
                return;
            }
        }
        cout<<"Book not found!"<<endl;
    }
    void returnBook(int id){
        for(int i=0;i<count;i++){
            if(books[i].id == id){
                if(!books[i].isAvailable){
                    books[i].isAvailable = true;
                    for(int j=0;j<issue_count;j++){
                        if(issue_arr[j].bookId == id){
                            for(int k=j;k<issue_count-1;k++){
                                issue_arr[k] = issue_arr[k+1];
                            }
                            issue_count--;
                            break;
                        }
                    }
                    cout<<"....Book Returned Successfully......"<<endl;
                } else
                    cout<<"Book is already available."<<endl;
                return;
            }
        }
        cout<<"Book not found."<<endl;
    }
     void deleteBook(int id){
        for(int i=0;i<count;i++){
            if(books[i].id == id){
                for(int j=i;j<count-1;j++){
                    books[j] = books[j+1];
                }
                count--;
                for(int j=0;j<issue_count;j++){
                    if(issue_arr[j].bookId == id){
                        for(int k=j;k<issue_count-1;k++){
                            issue_arr[k] = issue_arr[k+1];
                        }
                        issue_count--;
                        break;
                    }
                }
                cout<<"....Book Deleted...."<<endl;
                return;
            }
        }
        cout<<"Book not found."<<endl;
    }
};
int main(){
    library lib;
    int choice;
    int id;
    // string personName, phoneNumber;
    cout<<"....... WELCOME IN THE LIBRARY..........."<<endl;
    cout<<"Please maintain silence inside the library and follow the below instructions......"<<endl;
    while(true){
        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Issue Book" << endl;
        cout << "5. Return Book" << endl;
        cout << "6. Delete Book" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1:
                lib.addBook();
                break;
            case 2:
                lib.display();
                break;
            case 3:
                cout << "Enter book ID: ";
                cin >> id;
                lib.search(id);
                break;
            case 4:
                cout << "Enter book ID: ";
                cin >> id;
                lib.issueBook(id);
                break;
            case 5:
                cout << "Enter book ID: ";
                cin >> id;
                lib.returnBook(id);
                break;
            case 6:
                cout << "Enter book ID: ";
                cin >> id;
                lib.deleteBook(id);
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        cout<<"..........................................................................................."<<endl;
    }
    return 0;
}




