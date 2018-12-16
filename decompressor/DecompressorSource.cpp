#include <iostream>
#include <fstream>
#include <string>
#include "strutils.h"
using namespace std;

int main(){
	string db[4096];  // this is our string array 
	
	int i=0;
	while (i<256){   // it inserts characters
		char c = char(i);
		string t(1,c);
		db[i]= t;
		i++;
	}


	ifstream deneme("compout.txt");  // it will read from compout.txt
	string docu="";
	while(!deneme.eof()) //eof returns true if next character
	{

		
                    char ch;
					deneme.get(ch); //get command reads next character
					string c(1,ch);
					docu= docu + c;
	
	}

	docu.pop_back();
	deneme.close();
	

	int before;
	int after;

	int space=docu.find(" ");    // this finds space in code

	
    ofstream sonuc("decompout.txt");  // this is where we print the output
	after = atoi(docu.substr(0,space));
	docu= docu.substr(space+1,docu.length());
	
	
	string a;
	
	sonuc << db[after];
	before = after;

	int aa = 256;
	while(true) {  // this is algorithm
		int space=docu.find(" ");
				after= atoi(docu.substr(0,space));
				docu= docu.substr(space+1,docu.length());
			

		if(db[after] == "") {
			a = db[before] + db[before].substr(0,1);
			db[aa] = a;
			sonuc << db[aa];
			if(after>aa)
			before = aa;
			else
				before = after;
			aa++;
		}
		else {
			a = db[before] + db[after].substr(0,1);
			db[aa] = a;
			sonuc << db[after];
			before = after;
			aa++;
		}
			if(space==-1)
					break;
	
	}
	
		
		sonuc.close();   // this close sonuc
	system("pause");
	return 0;
}