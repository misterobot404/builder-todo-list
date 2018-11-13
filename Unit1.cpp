//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream>
#include <fstream>
#include <string>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
using namespace std;

TForm1 *Form1;
int count;
int pointer;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
   std::ifstream in("dataBase.txt");
  std::string  x;
  TListItem * item=0;

  bool flag=false;
  while(!std::getline(in,x).fail()){
	if(!x.size()) {item=0;flag=false;continue;}
	if(x.size()&&'"'==x[x.size()-1]) x.resize(x.size()-1);
	if(x.size()&&'"'==x[0]) x.erase(0,1);
	if(!item) item=ListView1->Items->Add();
	if(!flag){ item->Caption=x.c_str(); flag=true;
	++count;}
	else item->SubItems->Add(x.c_str());
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
	Form2->ShowModal();

	ListView1->Items->Add();
	ListView1->Items->Item[count]->Caption = Form2->Edit1->Text;
	ListView1->Items->Item[count]->SubItems->Add(Form2->DateTimePicker1->DateTime);
	++count;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListView1Change(TObject *Sender, TListItem *Item, TItemChange Change)

{
   pointer = Item->Index;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
	if(pointer != 0){
	ListView1->Items->Delete(pointer);
	--count;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
 std::ofstream out("dataBase.txt",std::ios_base::out|std::ios_base::trunc);
  for(size_t i=0;i<(size_t)ListView1->Items->Count;++i){
	if(i) out<<std::endl;

	AnsiString a;
	a = ListView1->Items->Item[i]->Caption.c_str();

	out<<"\""<<a.c_str()<<"\""<<std::endl;
	for(size_t j=0;j<(size_t)ListView1->Items->Item[i]->SubItems->Count;++j)
	{
	  AnsiString b;
	  b = ListView1->Items->Item[i]->SubItems->Strings[j].c_str();

	  out<<"\""<<b.c_str()<<"\""<<std::endl;
	}
  }
}
//---------------------------------------------------------------------------

