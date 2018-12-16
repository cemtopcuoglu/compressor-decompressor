#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

template <class HashedObj>
class HashTable{

public:
	explicit HashTable( const HashedObj & notFound, int size = 4096 ,int i = 0);
		HashTable( const HashTable & rhs )
		: NotFound( rhs.NotFound ),
		 array( rhs.array ), currentSize( rhs.currentSize ) { }

	int findPos(const HashedObj & x) const;
	
	void insert(const HashedObj & x);  // this is insert function
	enum EntryType{ACTIVE,EMPTY,DELETED};
	bool operator ==(HashTable & x);
	const HashedObj & find( const HashedObj & x )const; 
 int getIndex(const HashedObj & x) const;  // this is returning index of HashedObj
private:
	struct HashEntry{  // this is hash entry struct
		HashedObj element;
		EntryType info;
		int index;
		HashEntry(const HashedObj & e = HashedObj() ,EntryType i=EMPTY,int index=-1):element(e),info(i),index(index){}
	};
   
	int i;
	const HashedObj NOT_FOUND;  // this is NOT_FOUND HashedObj
	vector<HashEntry> array;  // this is array that holds hashEntries
	bool isActive(int currentPos) const;   // this checks if that position is active or not
   

};

 int hasha(const string &key, int size){  // this is hash function
     int hashVal = 0;

   			for(int i = 0; i < key.length(); i++) {
				hashVal = 2*hashVal + int(key[i]);
			}
			hashVal = hashVal % size;
			if(hashVal < 0) {
				hashVal = hashVal + size;
			}

	   return hashVal;
    }

 int hasha( int & key, int size){  
     int hashVal = key % size;

	  return hashVal;
}

template<class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj& NotFound , int size,int i): NOT_FOUND(NotFound),array(size),i(i)  // constructor
{
	
}

template<class HashedObj>
int HashTable<HashedObj>::getIndex(const HashedObj & x) const{   // this is returning index of HashedObj
	int position=findPos(x);
	return array[position].index;
}

template<class HashedObj>
bool HashTable<HashedObj>::operator==(HashTable &x){   // this is == operator
    
	 if(this->array.size()== x.array.size()){
		for(int i=0; i< this->array.size();i++){
			if(this->array.at(i)!= x.array.at(i)){
				return false;
			}
			
		}
		return true;
	 }
	 else{
		return true;
	 }
	  
}


template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find( const HashedObj & x )const // this finds that object and check is there an object
{
int currentPos = findPos( x );
if (isActive( currentPos ))
return array[ currentPos ].element;

return NOT_FOUND;  // if it cannot find it returns NOT_FOUND
}



template<class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj&x) const  // this is finding position
{
	int collisionNum = 0;
	int currentPos = hasha( x, array.size( ) );
	while( array[ currentPos ].info != EMPTY && array[ currentPos ].element != x )

{
	currentPos += 2 * ++collisionNum - 1; // add the difference
		if( currentPos >= array.size( ) ) // perform the mod
		currentPos -= array.size( ); // if necessary
		}
return currentPos;
}

template<class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const  // this checks if they are active
{
	return array[currentPos].info == ACTIVE;


}

template<class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj & x)  // this inserts hashedObj to table
{
	
	int currentPos= findPos(x);
	if(isActive(currentPos))
		return;
	array[currentPos]= HashEntry(x,ACTIVE,i);
	i++;
	
}


int main(){

	
	string a="notfound";  // this is not found string 
	HashTable<string> has(a,4096,0);  // this is creating hash table
	string fin;
	int i=0;
	while (i<256){   // this inserts first 0-255 character
		char c = char(i);
		string t(1,c);
		has.insert(t);
		i++;
	}

	ifstream deneme("compin.txt");  // this is our txt file
	string docu="";
	while(!deneme.eof()) //eof returns true if next character
	{

		
                    char ch;
					deneme.get(ch); //get command reads next character
					string c(1,ch); // this changes char to string
					docu= docu + c;
	
	}

	docu.pop_back();
	deneme.close();  
	

	
	string before="";  
	string after="";

	ofstream sonuc("compout.txt");  // this is where we print the output

  for(int i =0; i < docu.length(); ){   // this is algorithm 


		after=docu.at(i);
		if(has.find(before+after)!=a){
			before=before+after;
		}
		else {
			string added= before+after;
            sonuc << has.getIndex(before) << " ";
			has.insert(added);
			before=after;
		}
		i++;
	}
  	if(before == after)
		sonuc << has.getIndex(before);
		
	sonuc.close();   // this close sonuc



	

	system("pause");
	return 0;
}