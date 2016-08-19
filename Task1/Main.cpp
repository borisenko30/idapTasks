//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#include <fstream>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;

TForm1 *Form1;
TPicture *picture, *check, *uncheck;

void saveToFile();// save the table into the file 'data.txt'
void loadFromFile();// load the table from the file 'data.txt'
AnsiString getRandString();// returns random string of 30 chars
void addLine();// add a row into the table
void delLine(int i);// delete a row from the table
void delChecked();// delete all checked rows
void sort();// sort all rows by a string (2nd column) in ascending order
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  picture = new TPicture();
  check = new TPicture();
  uncheck = new TPicture();
  picture->LoadFromFile("image.bmp");
  check->LoadFromFile("checked.bmp");
  uncheck->LoadFromFile("unchecked.bmp");
// initialize table's header
  StringGrid1->Cells[1][0] = "string data";
  StringGrid1->Cells[2][0] = "image";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
  TStringGrid *grid = StringGrid1;
// replace string data with an image: 1 - 'checked', 0 - 'unchecked'
  if (grid->Cells[ACol][ARow] == '1') {
    grid->Canvas->StretchDraw(Rect, check->Graphic);
  } else if (grid->Cells[ACol][ARow] == '0') {
    grid->Canvas->StretchDraw(Rect, uncheck->Graphic);
  } else if (grid->Cells[ACol][ARow] == "picture") {
    grid->Canvas->StretchDraw(Rect, picture->Graphic);
  }

  if (grid->RowCount > 1) {
    grid->FixedRows = 1;
  }

}

void saveToFile(){
  TStringList *List = new TStringList();
  TStringGrid *grid = Form1->StringGrid1;
  for (int i=1; i<grid->RowCount; i++) {
    for (int j=0; j<grid->ColCount; j++) {
      List->Add(grid->Cells[j][i]);
    }
  }
  List->SaveToFile("data.txt");
}

void loadFromFile(){
  TStringList *List = new TStringList();
  TStringGrid *grid = Form1->StringGrid1;
  ifstream f("data.txt");
  if (!f.good()) {
    for (int i = 0; i < 5; i++) {
        addLine();
    }
    return;
  }

  List->LoadFromFile("data.txt");

  int count = List->Count;
  grid->RowCount = count/3 + 1;

  int index = 0;
  for (int i=1; i<grid->RowCount; i++) {
    for (int j=0; j<grid->ColCount; j++) {
      grid->Cells[j][i] = List->Strings[index++];
    }
  }
}

AnsiString getRandString() {
  string s = "";
  for (int i = 0; i < 10; i++) {
    s += rand() % 26 + 'a';
    s += rand() % 26 + 'A';
    s += rand() % 10 + '0';
  }
  return s.c_str();
}

void addLine() {
  TStringGrid *grid = Form1->StringGrid1;
  int row = grid->RowCount;
  grid->Cells[0][row] = '0';
  grid->Cells[1][row] = getRandString();
  grid->Cells[2][row] = "picture";
  grid->RowCount++;
}

void delLine(int index) {
  TStringGrid *grid = Form1->StringGrid1;
  if (index >= grid->RowCount) return;
  if (index == grid->RowCount - 1) {
    grid->RowCount--;
    return;
  }
  for (int i = index + 1; i < grid->RowCount; i++) {
    for (int j = 0; j < grid->ColCount; j++) {
      grid->Cells[j][i-1] = grid->Cells[j][i];
    }
  }
  grid->RowCount--;
}

void delChecked() {
  TStringGrid *grid = Form1->StringGrid1;
    for (int i = 1; i < grid->RowCount; i++) {
      if (grid->Cells[0][i] == '1') {
        delLine(i--);
      }
    }
}

void sort() {
  TStringGrid *grid = Form1->StringGrid1;
  bool sorted = false;
  while (!sorted) {
    sorted = true;
    for(int i = 1; i < grid->RowCount - 1; i++) {
      if (grid->Cells[1][i] > grid->Cells[1][i+1]) {
        grid->Cols[0]->Exchange(i, i+1);
        grid->Cols[1]->Exchange(i, i+1);
        grid->Cols[2]->Exchange(i, i+1);
        sorted = false;
      }
    }
  }
}

void __fastcall TForm1::BitBtn4Click(TObject *Sender)
{
  delChecked();
}

void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
  addLine();
}

void __fastcall TForm1::StringGrid1Click(TObject *Sender)
{
  int ARow = StringGrid1->Row;
// check/uncheck a single row
  if (ARow > 0) {
    if (StringGrid1->Cells[0][ARow] == '1') {
      StringGrid1->Cells[0][ARow] = '0';
    } else {
      StringGrid1->Cells[0][ARow] = '1';
    }
  }
}

void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
//invert data in the first column 0=>1, 1=>0. So we can check/uncheck all rows.
  for(int i = 1; i < StringGrid1->RowCount; i++) {
    if (StringGrid1->Cells[0][i] == '1') {
      StringGrid1->Cells[0][i] = '0';
    } else {
      StringGrid1->Cells[0][i] = '1';
    }
  }
}


void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  saveToFile();
}


void __fastcall TForm1::FormCreate(TObject *Sender)
{
  loadFromFile();
}


void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
  sort();
}


