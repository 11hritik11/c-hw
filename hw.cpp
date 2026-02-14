




#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

struct LibraryBook
{
    string szTitle;     // Title of the book
    string szAuthor;    // Author of the book
    int iPageCount;     // # of pages in the book
    int iTimesBorrowed; // # of times the book has been borrowed
};

/*___________________________________________________________
Function :replace character
Purpose :Replace all occurance of one character in a string with another.
Params :szText  -input Text
cTarget -character to replace
cReplacement - replacement character
Return : modified string;
______________________________________________________________
*/
string replaceCharacter(string szText, char cTarget, char cReplacement)
{
	for  (size_t i = 0; i<szText.length(); i++){
		if ( szText[i] == cTarget){
			szText[i]=  cReplacement;
		}
	}
	return szText;
}

/*
---------------------------------------------------------------
Function: loadFromfile
purpose : loads book records from a file into an array.
Params: booksARR -array to fill
iCapacity: max number of book array can hold
szFilename: file loads from (default books.txt)
Returns: number of book loaded or -1 if if file cannot be opened or is empty/invalid
Notes: No consoles I/O here (only file operations).

*/

int loadFromFile (LibraryBook booksArr[], int iCapacity, string szFilename = "books.txt"){
	ifstream inFile(szFilename);

if (!inFile.is_open())
{
	return -1;
}

int iNumBooksInFile = 0;
inFile >>iNumBooksInFile;

if (inFile.fail() || iNumBooksInFile<=0){
	return -1;
}
int iCountLoaded = 0;
while (iCountLoaded < iCapacity && iCountLoaded < iNumBooksInFile)
{
	string szTitleUnderscore;
	string szAuthorUnderscore;
	int iPages = 0;
	int iBorrowed = 0;

	inFile >> szTitleUnderscore >> szAuthorUnderscore >> iPages >> iBorrowed;
	if (inFile.fail())
	{
		break;
	} 

	booksArr[iCountLoaded].szTitle = replaceCharacter(szTitleUnderscore, '_', ' ');
	booksArr[iCountLoaded].szAuthor = replaceCharacter(szAuthorUnderscore, '_', ' ');
	booksArr[iCountLoaded].iPageCount = iPages;
	booksArr[iCountLoaded].iTimesBorrowed = iBorrowed;

	iCountLoaded++;

}

if (iCountLoaded == 0){
	return -1;


}

return iCountLoaded;

}

void showCatalog(const LibraryBook booksArr[], int iCount){

// Display formatting code for showCatalog
cout << left
    << setw(3)  << "#"
    << setw(25) << "Title"
    << setw(20) << "Author"
    << setw(8)  << "Pages"
    << setw(10) << "Borrowed"
    << endl;


for (int i = 0; i<iCount; i++)
	{
		cout << left
			 << setw(3)  << i
			 << setw(25) <<booksArr[i].szTitle
			 << setw(20) << booksArr[i].szAuthor
			 << setw(8)  << booksArr[i].iPageCount
			 << setw(10) << booksArr[i].iTimesBorrowed
			 << endl;
	}

}

int findByTitle(const LibraryBook booksArr[], int iCount, const string& szSearchTitle)
{
	for (int i =0; i<iCount; i++)
	{
		if (booksArr[i].szTitle == szSearchTitle){
			return i;
		}
	}
	return -2;
}
/*
Function : checkoutByTitle
Purpose : Increments times borrowed for a book with matching title 
params : booksArr 
*/

bool checkoutByTitle( LibraryBook booksArr[],int iCount, const string& szSearchTitle ){
	
	int iIndex = findByTitle(booksArr, iCount, szSearchTitle);
	if (iIndex == -2){
		return false;
	}
	booksArr[iIndex].iTimesBorrowed++;
	return true;
}
int totalPages(const LibraryBook booksArr[], int iCount)
{
	int iSum = 0;
	for (int i = 0; i< iCount; i++){
		iSum += booksArr[i].iPageCount;
	}
	return iSum;
}

 
double averagePages ( const LibraryBook booksArr[], int iCount)
{
	if (iCount <= 0)
	{
		return 0.0;
	}
	int iSum = totalPages (booksArr, iCount);
	return static_cast <double>(iSum) / static_cast <double>(iCount);

}
int main() 
{
    const int I_MAX_BOOKS = 200;
    LibraryBook booksArr[I_MAX_BOOKS];


	string szFilename;
	cout << "Enter a filename: ";
	getline (cin, szFilename);
	int iCount  = loadFromFile( booksArr, I_MAX_BOOKS, szFilename);

	if (iCount == -1)
	{
		cout<<"File not found or empty. Exiting program"<<endl;
		return 1;
	}

	while (true)
	{
		showCatalog(booksArr, iCount);
		cout << "Enter a title to check out (or QUIT to stop): ";
		string szTitle; 
		getline (cin, szTitle);

		if (szTitle == "QUIT")
		{
			break; 
		} 
		if (szTitle.length() == 0){

			cout<< "Empty title entered. Try again"<< endl;
			continue;
		}

		bool bSuccess = checkoutByTitle(booksArr, iCount, szTitle);
		if (bSuccess)
		{
			cout << "Checked out: " << szTitle << endl;

		}
		else 
		{
			cout << "Title not found." <<endl;
		}
	}

	int iTotal = totalPages( booksArr, iCount);
	cout << "Total pages of all books: " << iTotal << endl;

	double dAvg = averagePages (booksArr, iCount);
	cout<< fixed << setprecision (1);
	cout << "Average pages per book: "<< dAvg << endl;


    return 0;
}

