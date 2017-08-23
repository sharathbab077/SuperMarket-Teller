

//#include<iomanip>
#include<iostream>
#include<fstream>
using namespace std;

//***************************************************************

 //CLASS USED IN PROJECT

//****************************************************************

class product
{
  int pno;

  char name[50];

  float price, qty, tax, dis;

public:

  void getdata ()  //admin -reads the product details
  {

    cout << "\nPlease Enter The Product No. of The Product ";

    cin >> pno;

    cout << "\n\nPlease Enter The Name of The Product ";

    cin >> name;

    cout << "\nPlease Enter The Price of The Product ";

    cin >> price;

    cout << "\nPlease Enter The Discount (%) ";

    cin >> dis;

  }

  void showdata ()//admin & customer -to display the product details
  {
    cout << "\nThe Product No. of The Product : " << pno;
    cout << "\nThe Name of The Product : ";
    cout << name;
    cout << "\nThe Price of The Product : " << price;
    cout << "\nDiscount : " << dis;
  }
  friend void intro ();		//friend function
  int retpno () //returns product no
  {
    return pno;
  }

  float retprice () //returns price of the product
  {
    return price;
  }

  char *retname () //returns  product name
  {
    return name;
  }

  int retdis () //returns discount
  {
    return dis;
  }
//***************************************************************

// global declaration for stream object, object

//****************************************************************
  void write_product ();	//write the record in binary file

  void display_all ();		//read all records from binary file

  void display_sp (int);	//accept productno and read record from binary file

  void modify_product (int);	//accept product no and update record of binary file
  void show_tabular ();

  void delete_product (int);	//accept productno and delete selected records from binary file
  void admin_menu ();
  void intro ();		//display welcome screen
};

fstream fp;
product pr;

void
product::show_tabular ()
{
  cout << pno << "\t\t" << name << "\t\t" << price << endl;
}

//***************************************************************

// function to write in file

//***************************************************************
void
write_product ()
{

  product st;

  ofstream outFile;		//to write to the file

  outFile.open ("prod.dat", ios::binary | ios::app);//obj.open("filename",mode)

  st.getdata ();

  outFile.write ((char *) &st, sizeof (product));	//entries of object is written to file and size is calculated  

  outFile.close ();

  cout << "\n\nrecord Has Been Created ";

  cin.ignore ();//reads and discards characters from input stream

}

//***************************************************************

// function to read all records from file

//****************************************************************

void
display_all ()
{

  product st;

  ifstream inFile; //used to read from the file

  inFile.open ("prod.dat", ios::binary);

  if (!inFile)			//if file is not created

    {

      cout << "File could not be open !! Press any Key...";

      return;

    }

  cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";

  while (inFile.read ((char *) &st, sizeof (product)))

    {

      st.showdata ();

      cout << "\n\n====================================\n";

    }

  inFile.close ();

}

//***************************************************************

// function to read specific record from file

//****************************************************************
void
display_sp (int n)
{

  product st;

  ifstream inFile;

  inFile.open ("prod.dat", ios::binary);

  if (!inFile)

    {

      cout << "File could not be open !! Press any Key...";



      return;

    }

  int flag = 0;			//used to check whether the id is present or not

  while (inFile.read ((char *) &st, sizeof (product)))

    {

      if (st.retpno () == n)	// put id here


	{

	  st.showdata ();

	  flag = 1;

	}

    }

  inFile.close ();

  if (flag == 0)

    cout << "\n\nrecord not exist";



}

//***************************************************************

// function to modify record of file

//****************************************************************
void
modify_product (int n)
{

  int found = 0;

  product st;

  fstream File;//used to read and write

  File.open ("prod.dat", ios::binary | ios::in | ios::out);

  if (!File)

    {

      cout << "File could not be open !! Press any Key...";

      return;

    }



  while (File.read ((char *) &st, sizeof (product)) && found == 0)

    {

      if (st.retpno () == n)	//id here

	{

	  st.showdata ();

	  cout << "\n\nPlease Enter The New Details of product" << endl;

	  st.getdata ();

	  int pos = (-1) * sizeof (st);

	  File.seekp (pos, ios::cur);	// to indicate current positon in a file

	  File.write ((char *) &st, sizeof (product));

	  cout << "\n\n\t Record Updated";

	  found = 1;

	}

    }

  File.close ();

  if (found == 0)

    cout << "\n\n Record Not Found ";

}




//***************************************************************

// function to delete record of file

//****************************************************************
void
delete_product (int n)
{

  product st;

  ifstream inFile;

  inFile.open ("prod.dat", ios::binary);

  if (!inFile)

    {

      cout << "File could not be open !! Press any Key...";

      return;

    }

  ofstream outFile;

  outFile.open ("Temp.dat", ios::out);

  inFile.seekg (0, ios::beg);//indicates the beginning of the file

  while (inFile.read ((char *) &st, sizeof (product)))

    {

      if (st.retpno () != n)//since it is used to modify 

	{

	  outFile.write ((char *) &st, sizeof (product));

	}

    }

  outFile.close ();

  inFile.close ();

  remove ("prod.dat");

  rename ("Temp.dat", "product.dat");

  cout << "\n\n\tRecord Deleted ..";



}




//***************************************************************

// function to display all products price list 

//****************************************************************

void
product_result ()
{

  product st;

  ifstream inFile;

  inFile.open ("prod.dat", ios::binary);

  if (!inFile)

    {

      cout << "File could not be open !! Press any Key...";



      return;

    }

  cout << "\n\n\t\t PRODUCTS AVAILABLE IN OUR SUPER MARKET\n\n";

  cout << "==========================================================\n";

  cout << "PNO\t\tNAME\t\tPRICE" << endl;

  cout << "==========================================================\n";

  while (inFile.read ((char *) &st, sizeof (product)))

    {

      st.show_tabular ();

    }



  inFile.close ();

}


//***************************************************************

// function to place order and generating bill for Products

//****************************************************************

void
place_order () //used to generate bill
{
  int order_arr[50], quan[50], c = 0;

  float amt, damt, total = 0;

  char ch = 'Y';

  product_result ();
  cout << "\n\t\t============================";

  cout << "\n\t\t PLACE YOUR ORDER";

  cout << "\n\t\t============================\n";

  do
    {

      cout << "\n\nEnter The Product No. Of The Product : ";

      cin >> order_arr[c];

      cout << "\nQuantity in number : ";

      cin >> quan[c];

      c++;

      cout << "\nDo You Want To Order Another Product ? (y/n)";

      cin >> ch;

    }
  while (ch == 'y' || ch == 'Y');

  cout << "\n\nThank You For Placing The Order";

  cout <<
    "\n\n********************************INVOICE************************\n";

  cout <<
    "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";

  for (int x = 0; x <= c; x++)

    {

      product pr;

      ifstream inFile;

      inFile.open ("prod.dat", ios::binary);

      if (!inFile)

	{

	  cout << "File could not be open !! Press any Key...";
	  return;
	}

      int flag = 0;

      while (inFile.read ((char *) &pr, sizeof (product)))

	{

	  if (pr.retpno () == order_arr[x])

	    {

	      amt = pr.retprice () * quan[x];

	      damt = amt - (amt * pr.retdis () / 100);

	      cout << "\n" << order_arr[x] << "\t" << pr.
		retname () << "\t" << quan[x] << "\t\t" << pr.
		retprice () << "\t" << amt << "\t\t" << damt;

	      total += damt;

	    }
	  flag = 1;
	}
      inFile.close ();
    }
  cout << "\n\n\t\t\t\t\tTOTAL = " << total;
  cout << "\n\nThank You For Placing The Order in our super market";
}

//***************************************************************

// INTRODUCTION FUNCTION

//****************************************************************
void
intro ()
{

  cout << "\n\n\t\t  RAASS SUPERMARKET ";
  cout << "\n  \t\tSHOP NO.00001,ORION Mall,Bangalore";
  cout << "\n\tPRESENTED BY:     ";
  cout << "\n\n\t                  ABHILASH.R";
  cout << "\n\n\t                 APOORVA.V.GOWDA";
  cout << "\n\n\t	  	    SHARATH BABU.S";
  cout << "\n\n\t		    SHAMILI.B.SHETTY ";
  cout << "\n\n\t		    RAJESHWARI KAKDE.K.V";
}



//***************************************************************

// ADMINSTRATOR MENU FUNCTION

//****************************************************************
void
admin_menu ()
{

  char ch;
  int password;
  int num;
  cout << "enter administrator password please \n";
  cin >> password;
  if (password == 12345)
    {
      cout << "\n\n\n\tENTERING ADMINSTRATOR  MENU";

      cout << "\n\n\t1.CREATE PRODUCT RECORD";

      cout << "\n\n\t2.DISPLAY ALL PRODUCTS RECORDS";

      cout << "\n\n\t3.SEARCH PRODUCT RECORD ";

      cout << "\n\n\t4.MODIFY PRODUCT RECORD";

      cout << "\n\n\t5.DELETE PRODUCT RECORD";

      cout << "\n\n\t6.BACK TO MAIN MENU";

      cout << "\n\n\tPlease Enter Your Choice (1-6) ";

      cin >> ch;

      switch (ch)

	{

	case '1':
	  write_product ();
	  break;

	case '2':
	  display_all ();
	  break;

	case '3':
	  cout << "\n\n\tPlease Enter The product number ";
	  cin >> num;

	  display_sp (num);
	  break;

	case '4':
	  cout << "\n\n\tPlease Enter The product number ";
	  cin >> num;

	  modify_product (num);
	  break;
	case '5':
	  cout << "\n\n\tPlease Enter The number ";
	  cin >> num;

	  delete_product (num);
	  break;

	case '6':
	  break;

	default:
	  cout << "\a";
	  admin_menu ();

	}
    }
  else
    {
      cout << "wrong password entered \n";
    }
}


//***************************************

// THE MAIN FUNCTION OF PROGRAM

//****************************************************************
int
main ()
{

  char ch;

  intro ();

  while (1)
    {
      cout << "\n\n\n\tMAIN MENU";

      cout << "\n\n\t01. CUSTOMER";

      cout << "\n\n\t02. ADMINISTRATOR";

      cout << "\n\n\t03. EXIT";

      cout << "\n\n\tPlease Select Your Option (1-3) ";

      cin >> ch;

      switch (ch)

	{

	case '1':
	  place_order ();

	  break;

	case '2':
	  admin_menu ();

	  break;

	case '3':
	  return 0;

	default:
	  cout << "invalid choice \n";

	}

    }
  return 0;

}

//***************************************************************

// END OF PROJECT

//***************************************************************

