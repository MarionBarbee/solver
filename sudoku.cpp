
// solve.cpp : Defines the entry point for the console application.
//
//
//==========================================================  
//   
//
// 
//
//        
//   version: 1.0 r1                                      
//
//   
//
//   Designed and executed by:  Marion Barbee Jr.
//   Completed:  August 20, 2018
//  
//   Description: This program will solve any Sudoku puzzle of any degree of difficulty, including puzzles at the "solvability with unique solution"
//   theoretical limit of 17 clues as well as the top 10 hardest puzzles in the world (see AI sudoku site).
//
//   Puzzles can be manually created or scraped off WebSudoku site.  To scrape a puzzle from that site, pick difficulty level and save frame.  From command prompt,
//   type solve and the puzzle will be solved.  To manually input a file, create it in the format below and save. From command prompt, type solveit.  This 
//   program should be compile in Microsoft Virtual Studio.  A linux version also exists.
//
//           example input file:
//       
//           0 0 0 0 0 6 0 2 0 
//           0 0 1 0 0 8 5 0 0 
//           0 5 8 0 0 0 0 3 0 
//           0 0 0 0 3 4 8 0 7 
//           0 0 0 0 6 0 0 0 0 
//           4 0 5 8 1 0 0 0 0 
//           0 7 0 0 0 0 4 9 0 
//           0 0 3 7 0 0 6 0 0 
//           0 1 0 2 0 0 0 0 0 
//
//          
// 
//
//           C:\Users\youruser\Desktop\> solve.exe
//   
//  
//  Puzzle will be solved. Output res to the screen:
//  
//   @@@col checksums @@@@@@@@@
//   row[1].checksum=45
//   row[2].checksum=45
//   row[3].checksum=45
//   row[4].checksum=45
//   row[5].checksum=45
//   row[6].checksum=45
//   row[7].checksum=45
//   row[8].checksum=45
//   row[9].checksum=45
//   @@@@@@col checksums @@@@@@@@@
//   col[1].checksum=45
//   col[2].checksum=45
//   col[3].checksum=45
//   col[4].checksum=45
//   col[5].checksum=45
//   col[6].checksum=45
//   col[7].checksum=45
//   col[8].checksum=45
//   col[9].checksum=45
//   @@@@@@box checksums @@@@@@@@@
//   box[1].checksum=45
//   box[2].checksum=45
//   box[3].checksum=45
//   box[4].checksum=45
//   box[5].checksum=45
//   box[6].checksum=45
//   box[7].checksum=45
//   box[8].checksum=45
//   box[9].checksum=45   
//  
//   Sudoku Puzzle                                        
//                                                        
//   347 156 928                                          
//   961 328 574                                          
//   258 479 136                                          
//                                                        
//   126 934 857                                          
//   789 562 341                                          
//   435 817 269                                          
//                                                        
//   572 681 493                                          
//   893 745 612                                          
//   614 293 785                                          ffff
//                                                        
//Solution is verified by observing  all checksums = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 = 45
//
//========================================================== 
#include "stdafx.h"        
#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <random>


//==========================================================  
using namespace std;
//==========================================================  
// constants
//==========================================================  
int const noerr = 0;
int  const rmax = 10;
int  const cmax = 10;
int  const zboxsize = 4;
int  const zrow = 1;
int  const zcol = 2;
int  const zbox = 3;
int  const zall = 3;

int  const zunit = 3;
int  const zfailed = 0;
bool const zfalse = false;
bool const ztrue = true;
bool const done = true;
bool const empty = true;
bool const notempty = false;
int  const zno = 0;
int  const zyes = 1;

int  const zfirst = 1;
int  const zsecond = 2;
int  const zthird = 3;
//================================






int const zcol1 = 4;
int const zcol2 = 5;
int const zcol3 = 6;


int const zinitial = 1;
int const znoerrors = 0;
int const zunknownerror = 15;
int const zlocal = 0;



 

//==========================================================  
// puzzle input file name
//==========================================================  
fstream file("input");
//==========================================================  
//========================================================== 
string puzzletype = "none";       //default from websudoku site.
int fnc = 0;


int  const  inrow = 1;
int  const  incol = 2;
int  const  inbox = 3;
int  const  gerr = 4;
int  const  badr = 5;
int  const  badc = 6;
int  const  badv = 7;
int  const  overwrite = 8;
int  const  started = 1;
int  const  zinrow = 1;
int  const  zincol = 2;
int  const  zinbox = 3;
 
//for debug set to true

bool debug = false;
bool rowflag = false;
int insertedcnt = 0;




//=========================
//global variables
//=========================
int mrow[10] = {};
int mcol[10] = {};
int mbox[10] = {};
//=========================
int blrow[10] = {};
int blcol[10] = {};
int blbox[10] = {};

int etype = zrow;
int   doonce = 1;
int   gcbl = 0;
int   gcnum = 0;
//time_t gelapsedtime = 0;
int   gindex = 0;
 bool  gfirstprint = true;
 int glastcolunit = 1;
 int glastnum = 0;
 int glastrowunit = 1;
 int glastunittype = zrow;
int   glerr = 0;
 auto start_time = chrono::high_resolution_clock::now();
bool gfirstguess = true;
auto gltime1 = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
  
int   lzcnt = 0;

bool  pdone = false;
int   errorcode = 0;

int   zcnt = 0;
int   gnum = 0;
string glastwrite = " ";

 
bool  ranonce = false;

const int  idle = 0;
//time_t start_time;
//==========================================================
//initial states - extrapolation functionality 
//==========================================================
int  saveonce = 1;

//========================================================== 
//data type structs  
//==========================================================  
struct row_type{
	int  col[cmax];
	int  loc[cmax];
	int  blpos[cmax];
	int  nc[cmax];
	int  bcnt;
	int  mcnt;
	int  firstbl;
	int  lastbl;
	int  targbl;
	int  targrow;
	int  targcol;
	int  targbox;
	int  checksum;
	bool done;

};
row_type row[rmax] {};
//========================================================== 
struct col_type{
	
	int  row[rmax];
	int  loc[rmax];
	int  blpos[rmax];
	int  nc[rmax];
	int  bcnt;
	int  mcnt;
	int  firstbl;
	int  lastbl;
	int  targbl;
	int  targrow;
	int  targbox;
	int  targcol;
	int  checksum;
	bool done;

};
col_type col[cmax] = {};
//========================================================== 
struct row_unit{

	int nc[cmax];
	int tried1[cmax];
	int tried2[cmax];
	int tried3[cmax];
	int triedcnt[cmax];
	int bcnt;
	int targbox[cmax];
	int targrow[cmax];
	int firsttry[cmax];
	bool udone;

};
row_unit rowunit[4] = {};
//========================================================== 
struct col_unit{
	int  nc[rmax];
	int  bcnt;
	int tried1[cmax];
	int tried2[cmax];
	int tried3[cmax];
	int triedcnt[cmax];
	int  targbox[rmax];
	int  targcol[rmax];
	int firsttry[cmax];
	bool udone;
};
col_unit colunit[4] = {};
//========================================================== 
struct box_type{
	
	int  val[10];
	int  hash[10];
	int  blpos[rmax];
	int  bcnt;
	int  mcnt;
	bool done;
	int  r1[4], r2[4], r3[4];
	bool r1done, r2done, r3done;
	bool r1empty, r2empty, r3empty;
	bool c1empty, c2empty, c3empty;
	int  c1[4], c2[4], c3[4];
	bool c1done, c2done, c3done;
	int  checksum;
	int  firstbl;
	int  lastbl;

};
box_type box[10] = {};


struct gtype{
	int r;
	int c;
	int v;
	int AorB;
	int gptr;
	int zcnt;
	bool valid;
	int lasttried;
	int active;
	int listptr;
	int errortype;
};
 gtype badlist[100];
 gtype glist[1000] = {};
 gtype Arow[100] = {};
int ptrArow = 0;
gtype Brow[100] = {};
int ptrBrow = 0;
gtype Acol[100] = {};
int ptrAcol = 0;
gtype Bcol[100] = {};
int ptrBcol = 0;


gtype lastwrite[4] = {};
int ABptr = 0;
int blptr = 0;



struct choicetype{
	int n;
	int chA;
	int chB;
	int chAtried;
	int chAnum;
	int chBtried;
	int chBnum;
	int ABptr;
};

struct row2choices{
	choicetype num[10];
};

row2choices r2ch[10];

struct col2choices{
	choicetype num[10];
};

col2choices c2ch[10];

struct chstacktype{
	int runitsave;
	int rowsave;
	int currcol;
	int chAsave;
	int chBsave;
	int vsave;
	int zcntsave;
};
chstacktype chstack[81]; 
 
int puzzle[rmax][cmax] = {};
int dummy =65535;
int spuzzle[100][rmax][cmax] = {};
int ipuzzle[rmax][cmax] = {};
int gtable[rmax][cmax] = {};
int g2table[rmax][cmax];
int btable[rmax][cmax];
int b2table[rmax][cmax];
bool gfirstpassrow = true;
bool gfirstpasscol = true;
int guessmax = 0;
 
int guessmaxrow = 0;
int guessmaxcol = 0;
int top  = 0;
int currg2cnt = 0;
int guesscntrow = 0;
int guesscntcol = 0;
int pairindex = 0;
int ghighestcolnum = 0;   //product of col number and number
int grow = 1;
int ghighestrownum = 0;   //product of row number and number

int s2zcnt[4];
int s2puzzle[4][10][10];
bool s2saved = false;
bool s2rlded = false;
int oldtop = 0;
int gunit = 0;
bool thisisaguess = false;
int lastwritecnt = 0;
int savezcnt = 0;
int stop = 0;
int stackptr = 0;
int gptr = 0;
int glastrow = 0;
int nonguesscounter = 0;
struct rowtries{
	int r[10][10];
	int numtries;
};
rowtries rt[10];
int glastcol = 0;
int fillerrorcntcol = 0;
bool growinserted = false;
bool ginserted = false;
bool gfirstguessAB = true;
int ginsertedrow = 0;
int ginsertedcol = 0;
int ginsertedAcount = 0;
int ginsertedBcount = 0;
int gtotalinsertedcount = 0;
int guesscount = 0;
struct wltype{
   char *  r;
	int c;
	int v;
	int zcnt;
	bool guess;

};
wltype order[100] {};
//wltype lastwrite[1]={};
int gwi = 0;
int savegwi = 0;
int initzcnt = 0;
 //==========================================
int insertcol();

bool rowmatch(int r);
void initrt();
int insert5050();
int insert5050col();

int insert5050row();

void restorefromgtable(int listptr);
int insgtable(int r, int c, int v, int AorB, int tgptr, int lasttried);
 
void clearbtable();
void reinsertglist();
int   findinglist(int r, int c, int v);
void printglist();
bool popp();
void pushp();
int purgeAB();
void delbadlist(int listptr);
int  insbadlist(int r, int c, int v);
void pBadlist();
void cleargtable();
void insbtable(int glindex);
int forcerror();
int findinglist(int r, int c, int v);

void pushstack(int runit, int r, int currcol, int value, int chA, int chB);
int collectpairsrow(int runit, int num);
int collectpairscol(int cunit, int n);
bool findinbadlist(int r, int c, int v);
int solveAB();
int checkcnts();
int insArow(int r, int c, int v);
int insBrow(int r, int c, int v);
int insAcol(int r, int c, int v);
int insBcol(int r, int c, int v);
 

void delArow(int listptr);
void delBrow(int listptr);
void delAcol(int listptr);
void delBcol(int listptr);

int procrowlists();
int proccollists();
int pushArow();
int pushBrow();
int pushAcol();
int pushBcol();
void checkreinit();
int insertrow();
void swapAlist();
void swapBlist();
int insertA();
//==========================================================  
//==========================================================
//function forward declarations
//========================================================== 

int   box2elimcol(int b);
int   box2elimrow(int b);
int   box3elim(int b);
int   box3elimcol(int b);
int   box4cancelbls(int b);
int   box5elim(int b);
int   boxandcolelim3row(int r);
int   boxandrowelim3col(int c);
int   boxcol3done4(int b);
int   boxelimc1done(int b);
int   boxelimc2done(int b);
int   boxelimc3done(int b);
int   boxelimr1done(int b);
int   boxelimr2done(int b);
int   boxelimr3done(int b);
int   boxrow3done3(int b);
int   boxrow3done4(int b);
int   boxsubtract2c1(int b);
int   boxsubtract2c2(int b);
int   boxsubtract2c3(int b);
int   boxsubtract2r1(int b);
int   boxsubtract2r2(int b);
int   boxsubtract2r3(int b);
int   c1bl(int b);
int   c3bl(int b);
int   checkboxes();
int   checkcols();
int   checkgtable();
void  creategtable();
int   checkrows();
void  checksumall();
int   col3elim(int c);
int   col5elim(int c);
int   colelimdouble(int c);
int   colelimtriple(int c);
int   colinsertcheckelim(int c);
int   colunitelim();
int   elimdiagc1bl(int b);
int   eliminateinbox(int b);
void  initemptyboxrowsandcols(int b);
int   fboxfromrow(int r, int pos);
int   finbox(int b, int value);
int   fincol(int c, int value);
int   finrow(int r, int value);
int   gallblsinbox(int b, int &b1, int &b2, int &b3, int &b4, int &b5, int &b6, int &b7, int &b8, int &b9);
int   gallblsincol(int c, int &b1, int &b2, int &b3, int &b4, int &b5, int &b6, int &b7, int &b8, int &b9);
int   gallblsinrow(int r, int &b1, int &b2, int &b3, int &b4, int &b5, int &b6, int &b7, int &b8, int &b9);
int   gallminbox(int b, int &m1, int &m2, int &m3, int &m4, int &m5, int &m6, int &m7, int &m8, int &m9);
int   gallmincol(int c, int &m1, int &m2, int &m3, int &m4, int &m5, int &m6, int &m7, int &m8, int &m9);
int   gallminrow(int r, int &m1, int &m2, int &m3, int &m4, int &m5, int &m6, int &m7, int &m8, int &m9);
int   gboxfromcolandpos(int c, int pos);
int   gboxfromrowandcol(int r, int c);
int   gboxfromrowandpos(int r, int pos);
int   gcolfromboxandpos(int b, int pos);
int   gcolfromboxandrow(int b, int r);
int   gcolfromrowandpos(int r, int pos);
void  gcolsfromtargboxandtargrow(int targbox, int targrow, int &c1, int &c2, int &c3);
int getfullestrow();
int getfullestcol();
int   getpuzzleandeditmask();
int   gfb(int inwhat, int where);
int   glastbl(int inwhat, int where);
int   gminbox(int b, int &m1, int &m2, int &m3);
int   gmincol(int c, int &m1, int &m2, int &m3);
int   gminrow(int r, int &m1, int &m2, int &m3);
int   gnb(int inwhat, int where, int cb);
int   gncolunittarg(int ccu, int ctargnum, int &newtargnum, int &newtargcol, int &newtargbox, int &newcu, int &newtargrow);
int   gnrowunittarg(int cru, int ctargnum, int &newtargnum, int &newtargrow, int &newtargbox, int &newru, int &newtargcol);
int   gprevbl(int inwhat, int where, int cb);
int   gprevnum(int etype, int x, int cnum);
int   growfromboxandcol(int b, int c);
int   growfromboxandpos(int b, int pos);
int   growfromcolandpos(int c, int pos);
void  growsfromtargboxandtargcol(int targbox, int targcol, int &c1, int &c2, int &c3);
void  gprocrowunit(int runit);
void  gproccolunit(int cunit);
int   predictpath();
int predictpath2();
int   heavylogic();
void  init_box(int b);
int   insert_m(int inwhat, int where);
int   inspuzzle(int r, int c, int v);
int   moreboxprocing(int b);
void  printgbtables();
void  prunegtable(int glindex);
void  addgtabletopuzzle();
void  printpuzzle();
int   procallnumbersbox(int b);
int   procallnumberscol(int c);
int   procallnumbersrow(int r);
void  proccolunit(int cunit);
void  procrowunit(int runit);
int   procextrapolate(int r);
int   procextrapolatecol(int c);
int   procextrapolatebox(int b);
void  readbox(int b);
void  readboxes();
void  readpuzzle();
void  rldsaved();
void  rldpuzzle(int etype, int i);
int   row3elim(int r);
int   row5elim(int r);
void  saveinitialpuzzle();
void  updp();
void  writeblposbox(int b);
void  writeblposcol(int c);
void  writeblposrow(int r);
void  writecolunittargbox(int cunit, int num);
void  writecolunittargcol(int cunit, int num);
void  printcolunittargets(int cunit, int num);
void  printrowunittargets(int runit, int num);
void  writenccolunit(int cunit);
void  writencrowunit(int runit);                          
void  writerowunittargbox(int runit, int num);
void  writerowunittargrow(int runit, int num);
int    col456(int c, int v);
int    col123(int c, int v);
int    col789(int c, int v);
void   insertboxinpuzzle(int b,int i,int v);
int    cornercancel(int b, int v);
int    newalgorithm(int r, int v);
void  procpuzzle();
void  pArow(int ptrA);
void  pBrow(int ptrB);
void  pAcol(int ptrA);
void  pBcol(int ptrB);
int MergeAB();
int pruneBside();
int getlowrow();
int pickrow(int r);
int pickcol(int c);
//===================================================================================
void worder(int r, int c, int v){
	gwi++;
	switch (r){
	case 1: order[gwi].r = "A"; break;
	case 2: order[gwi].r = "B"; break;
	case 3: order[gwi].r = "C"; break;
	case 4: order[gwi].r = "D"; break;
	case 5: order[gwi].r = "E"; break;
	case 6: order[gwi].r = "F"; break;
	case 7: order[gwi].r = "G"; break;
	case 8: order[gwi].r = "H"; break;
	case 9: order[gwi].r = "I"; break;
	}
	order[gwi].c = c;
	order[gwi].v = v;
	order[gwi].zcnt = zcnt;
	if (thisisaguess){ order[gwi].guess = true; }
	else{ order[gwi].guess =false; }
	//cout << order[gwi].r << order[gwi].c << order[gwi].v << "," << endl;

}
//=====================================
void dumporder(){
	cout << "Solution order =" << endl;
	cout << "* = successful guess" << endl;
	for (int i = 1; i < gwi; i++){
		if (top > 0){
			for (int j = 1; j <= top; j++){
				if (glist[j].zcnt == order[i].zcnt){
					if (order[i].guess){
						cout << order[i].r << order[i].c << order[i].v << "*" << ",";
					}
				}
			}
		}
		if (order[i].guess == false){
			cout << order[i].r << order[i].c << order[i].v << ",";
		}
		if (i % 5 == 0){ cout << endl; }
	}
	cout << order[gwi].r << order[gwi].c << order[gwi].v << endl;

}

 
 
//=======================================================================================
bool popp(){
	cleargtable();
	gwi = savegwi;
	//debug = true;
	if (debug){ cout << "IN POPP. STACKPTR=" << stackptr << "GLERR=" << glerr << endl;
	cout << "BEFORE PRINTPUTZZLE=" << endl; printpuzzle();
	}
	glerr = false;
	growinserted = false;
	ginsertedrow = 0;
	ginsertedcol = 0;
	glastrow = 0;
	int ginsertedAcount = 0;
	int ginsertedBcount = 0;
	int gtotalinsertedcount = 0;

	rowflag = false;
	int num = 0;
	zcnt = 0;
	if (debug){ cout << "poppING STACK=" << stackptr << endl; }
	if (stackptr > 0){ stackptr--; }
	if (debug){ cout << "poppED STACK  STACKPTR==" << stackptr << endl; }
	if (stackptr < 0){
		cout << "KKKKKKKKKKKKKKKKKKK"<<endl; exit(0); }
	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			puzzle[x][y] = spuzzle[stackptr][x][y];
		//	cout << spuzzle[0][x][y];
		//	if (y == 9){ cout << endl; }

			num = puzzle[x][y];
			row[x].col[y] = num;
			col[y].row[x] = num;
			box[x].hash[y] = num;
			row[x].loc[num] = y;
			col[y].loc[num] = x;
			if (num == 0){ zcnt++; }

		}
	}
	 
	//for (int i = 1; i <= top; i++){ insbtable(i); }
//	cleargtable();
	pdone = false;
	lzcnt = zcnt;
	rowunit[1].udone = false;
	rowunit[2].udone = false;
	rowunit[3].udone = false;
	colunit[1].udone = false;
	colunit[2].udone = false;
	colunit[3].udone = false;
	updp();
//	debug = false;
	lastwritecnt = 0;
	if (stackptr == 0){ return true; }

	return false;
}
//==========================================================
void pushp(){
	//glerr = false;
	cout << "XXXXXXXXXXXXXXXXXXX" << endl;
	//exit(0);
	stackptr++;
	if (debug){ cout << "pushing stackptr=" << stackptr << endl; }
	for (int x = 1; x <=9; ++x) {
		for (int y = 1; y <= 9; ++y){
			spuzzle[stackptr][x][y] = puzzle[x][y];
		//	cout << spuzzle[0][x][y];
		//	if (y == 9){ cout << endl; }

		}
	}
	return;
}
//==========================================================



//============================================================================
void pushstack(int runit, int r, int currcol, int value, int chA, int chB){
	stop++;
	chstack[stop].runitsave = runit;
	chstack[stop].rowsave = r;
	chstack[stop].currcol = currcol;
	chstack[stop].vsave = value;
	chstack[stop].zcntsave = zcnt;
	chstack[stop].chAsave = chA;
	chstack[stop].chBsave = chB;
	if (debug){
		cout << "************************************************************" << endl;
		cout << runit << r << currcol << value << zcnt << chA << chB << endl;
		cout << "************************************************************" << endl;
	}
	return;
}
//========================================================== 
int checkinsert(int r, int c, int v);

void initp();
void checkfin();
void procp();


int   gm(int etype, int i);
int   gbls(int etype, int i);
void  initex(int etype, int i);
void  setexstart(int etype, int i);



int first(int etype, int x);
int last(int etype, int x);



int  checkcnt(int etype, int i);

int checkcnts();
int checkunits();



void initrow(int i);
void initcol(int i);
void initbox(int i);
void delbtable(int glindex);
void delgtable(int glindex);
void printgbtables();
void insbtable(int glindex);
void cleargtable();
void createtrytables();
int getfirstrowfrombox(int b);
int getfirstcolfrombox(int b);
void storepuzzlewithfirstguess(int i,int r,int c, int v);
void c2chinit();
void r2chinit();
int  insertr2choices(int runit);
int  insectr2choices(int cunit);
int pickrowchoice(int r);
int pickcolchoice(int c);
void checkglist();
int pickrowchoice2(int r);
int  gprocall(int r);
int pickrand2();
int pickrandunbounded();
int finishrow(int r);
int finishcol(int c);
int getlowcol();
int finishbox();
int getlowbox();
int checkglist(int r);
//=====================================================================
void delgtable(int glindex){
	thisisaguess = false;
	int r, c, v;
	r = glist[glindex].r;
	c = glist[glindex].c;
	v = glist[glindex].v;
	//gtable[r][c] = 0;
	glist[glindex].r = 0;
	glist[glindex].c = 0;
	glist[glindex].v = 0;
	int i = glindex;
	while (i < top){
		if (top > 1){
			glist[i].r = glist[i + 1].r;
			glist[i].c = glist[i + 1].c;
			glist[i].v = glist[i + 1].v;
			glist[i].zcnt = glist[i + 1].zcnt;
			glist[i].AorB = glist[i + 1].AorB;
			glist[i].gptr = glist[i + 1].gptr;
			glist[i].lasttried = glist[i + 1].lasttried;

			i++;
			if (i == 0){ break; }

		}
	}
	top--;
	if (guesscount > 0){ guesscount--; }
	return;
}
//==========
//==================================================================
int checkglist(int r){
	int res = 0;
	for (int i = 1; i <= top; i++){
		if (glist[i].r == r){
			res = i; break;
		}
	}
	return res;
}
 
 
 
//=====================================================
void r2chinit(){
	//=================================================
	int no = 0;
//	mt19937_64 generator(gseed);
	for (int r = 1; r <= 9; r++){
		for (int v = 1; v <= 9; v++){
			//int ABptr = generator() % 2;
			r2ch[r].num[v].chA = 0;
			r2ch[r].num[v].chB = 0;
			r2ch[r].num[v].chAtried = no;
			r2ch[r].num[v].chAnum = v;
			r2ch[r].num[v].chBtried = no;
			r2ch[r].num[v].chBnum = v;
			r2ch[r].num[v].ABptr = 0 ;
		}
	}
	return;
}

//=====================================================
void c2chinit(){
	//=================================================
	int no = 0;
//	mt19937_64 generator(gseed);
	//pre-randomize AB choices
	 
	for (int c = 1; c <= 9; c++){
		for (int v = 1; v <= 9; v++){
	//		int ABptr = generator() % 2;
			c2ch[c].num[v].chA = 0;
			c2ch[c].num[v].chB = 0;
			c2ch[c].num[v].chAtried = no;
			c2ch[c].num[v].chAnum = v;
			c2ch[c].num[v].chBnum = v;
			c2ch[c].num[v].chBtried = no;
			c2ch[c].num[v].ABptr =0;
		}

	}
	return;
}
//==========================================================    
int  insertr2choices(int runit){
	//========================================================== 
	return 0;
}

 		 
//==============================================================
void initlastwrite(){
	//1=gprocrow
	//2=gproccol
	//3=predictpath
	for (int i = 1; i <= 3; i++){
		lastwrite[i].r = 0;
		lastwrite[i].c = 0;
		lastwrite[i].v = 0;
		lastwrite[i].valid = false;
	}
	
	return;
}
	//==========================================================

 

 



//==========================================================
void readinitialpuzzle(){
	//==========================================================

	file.close();
	ifstream file;
	file.open("i.txt");
	zcnt = 0;
	int num = 0;
	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			file >> puzzle[x][y];
			num = puzzle[x][y];
			//ipuzzle[x][y] = num;
			if (num == 0){ ++zcnt; }
			row[x].col[y] = num;
			col[y].row[x] = num;
			box[x].hash[y] = num;
			row[x].loc[num] = y;
			col[y].loc[num] = x;
		}
	}
	file.close();
	initzcnt = zcnt;
	//cout << "initzcnt=" <<initzcnt<< endl;
	return;
}


//==========================================================
//end readinitialpuzzle
//==========================================================   
//==========================================================
void readpuzzle(){
	//==========================================================

	//file.close();
	//ifstream file;
	//	file.open("i.txt");
	zcnt = 0;
	int num = 0;
	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			//file >> puzzle[x][y];
		//	puzzle[x][y] = ipuzzle[x][y];
			num = puzzle[x][y];
			if (num == 0){ ++zcnt; }
			row[x].col[y] = num;
			col[y].row[x] = num;
			box[x].hash[y] = num;
			row[x].loc[num] = y;
			col[y].loc[num] = x;
		}
	}
	//	file.close();
	//initzcnt = zcnt;
	return;
}


//==========================================================
//end readpuzzle
void writeinitialpuzzle(){
	//==========================================================
	file.close();
	ofstream file;
	file.open("i.txt");
	zcnt = 0;
	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			file << puzzle[x][y] << " ";
			//file << puzzle[x][y];
			int num = puzzle[x][y];
			row[x].col[y] = num;
			col[y].row[x] = num;
			box[x].hash[y] = num;
			row[x].loc[num] = y;
			col[y].loc[num] = x;

			if (num == 0){ ++zcnt; }

		}
		file << endl;
	}
	file << endl;
	file.close();
	//initzcnt = zcnt;
	return;
}

//==========================================================
//end writepuzzle
//==========================================================   
void printpuzzle(){
//==========================================================   
	 int number=0;  
	// if ((zcnt>0)&&(zcnt==lzcnt)&&(!glerr)){return;}  
	 if (!debug){ return; }
	  cout<<endl; 	
	  cout<<"====================================================="<<endl; 	
	  cout<<"     zcnt        ="<<zcnt<<endl;
	  cout<<"     lzcnt       ="<<lzcnt<<endl;
	  cout<<"====================================================="<<endl;
	  cout<<"     glerr             ="<<glerr<<endl; 
	  cout<<"     fnc               ="<<fnc<<endl;
	  cout<<"     glastwrite        ="<<glastwrite<<endl;
	
	  cout<<endl;
	   for (int x=1;x<=rmax-1;++x) {    
	       for (int y=1;y<=cmax-1;++y){       
	         	  number=puzzle[x][y];  
	             if (y==1){  cout<<"                    "<<number;}
	             else{
	                  cout << number;
	              }
	              if ((y==3)||(y==6)){  cout <<" ";}
	         }  
	        if  ((x==3)||(x==6)){   cout<<endl;}   
	  cout<<endl;               
	   }
	  cout<<endl;  
	return;
}
//==========================================================
//end printpuzzle

//==========================================================    
void updp(){
	//==========================================================                                                                                                                                             
	                         


	for (int x = 1; x <= 9; ++x){
		for (int y = 1; y <= 9; ++y){
	//		row[x].col[y] = 0;
	//	    col[y].row[x] = 0;
			row[x].loc[y] = 0;
			col[x].loc[y] = 0;
	    	box[x].hash[y] = 0;
		}
	}
	
	readpuzzle();
	//checkfin();
	readboxes();
	
	
	for (int r = 1; r <= 9; ++r){ gfb(zrow, r); glastbl(zrow, r); row[r].done = false; }
	for (int c = 1; c <= 9; ++c){ gfb(zcol, c); glastbl(zcol, c); col[c].done = false; }
	for (int b = 1; b <= 9; ++b){ gfb(zbox, b); glastbl(zbox, b); box[b].done = false; }

	
	for (int i = 1; i <= 9; i++){ gbls(zrow, i); gbls(zcol, i); gbls(zbox, i); }
	for (int i = 1; i <= 9; i++){ gm(zrow, i); gm(zcol, i); gm(zbox, i); }
	readboxes();
	
	
	for (int i = 1; i <= rmax - 1; ++i){
		writeblposrow(i);
		writeblposcol(i);
		writeblposbox(i);
	}
	for (int unit = 1; unit <= 3; ++unit){
		writencrowunit(unit);
		writenccolunit(unit);
	}
	for (int unit = 1; unit <= 3; ++unit){
		for (int num = 1; num <= 9; ++num){
			writerowunittargrow(unit, num);
			writerowunittargbox(unit, num);
			writecolunittargcol(unit, num);
			writecolunittargbox(unit, num);
		}
	}
	//readboxes();
	for (int b = 1; b <= 9; b++){
		 
		init_box(b);
		readbox(b);
	
	}
//	checkfin();

	// cout<<endl<<"Puzzle updated*****************"<<endl;

	return;
}
//========================================================== 
void writencrowunit(int runit){
	//==========================================================    
	int start = 0;
	int stop = 0;
	int num = 0;
	if (runit == 1){ start = 1; stop = 3; }
	else{
		if (runit == 2){ start = 4; stop = 6; }
		else{
			if (runit == 3){ start = 7; stop = 9; }
			else{
				if (runit == 0){ writencrowunit(1); writencrowunit(2); writencrowunit(3); return; }
			}
		}
	}
	rowunit[runit].bcnt = 0;
	for (int y = 1; y <= cmax - 1; ++y){
		rowunit[runit].nc[y] = 0;
	}
	for (int x = start; x <= stop; ++x){
		for (int y = 1; y <= cmax - 1; ++y){

			num = row[x].loc[y];

			if (num != 0){
				
				++rowunit[runit].nc[y];// cout << "runit= " << runit << " nc[" << y << "] = "<<rowunit[runit].nc[y]<<endl
			}
			else{
				++rowunit[runit].bcnt;
			}
		}
	}

	if (rowunit[runit].bcnt == 0){ rowunit[runit].udone = true; }

	return;
}
//==========================================================    
//end writencrowunit(int runit)
//==========================================================    
void  writenccolunit(int cunit){
	//==========================================================    
	int start = 0;
	int stop = 0;
	int num = 0;
	if (cunit == 1){ start = 1; stop = 3; }
	else{
		if (cunit == 2){ start = 4; stop = 6; }
		else{
			if (cunit == 3){ start = 7; stop = 9; }
		}
	}
	if (cunit == 0){ writenccolunit(1); writenccolunit(2); writenccolunit(3); return; }
	colunit[cunit].bcnt = 0;
	for (int x = 1; x <= rmax - 1; ++x){
		colunit[cunit].nc[x] = 0;
	}
	for (int y = start; y <= stop; ++y){
		for (int x = 1; x <= rmax - 1; ++x){
			num = col[y].loc[x];
			if (num != 0){
				++colunit[cunit].nc[x];
			}
			else{
				++colunit[cunit].bcnt;
			}
		}
	}
	if (colunit[cunit].bcnt==0){colunit[cunit].udone=true;}//cout <<"Unit "<<cunit<< "done!"<<endl;}                                                                

	if (colunit[cunit].bcnt == 0){ colunit[cunit].udone = true; }
	return;
}
//========================================================== 
//end writenccolunit
//==========================================================                  
void  writeblposrow(int r){
	//==========================================================   
	int num = 0;
	if (r == 0){
		for (int x = 1; x <= rmax - 1; ++x){
			writeblposrow(x);
		}
		return;
	}
	row[r].bcnt = 0;
	row[r].firstbl = 0;
	row[r].lastbl = 0;
	for (int y = 1; y <= cmax - 1; ++y){
		row[r].blpos[y] = 0;
	}
	for (int y = 1; y <= cmax - 1; ++y){
		num = row[r].col[y];
		if (num == 0){
			if (row[r].firstbl == 0){ row[r].firstbl = y; }
			row[r].lastbl = y;
			++row[r].bcnt;
			row[r].blpos[y] = row[r].bcnt;
		}
		else{
			row[r].blpos[y] = 0;
		}
	}
	return;
}
//==========================================================   
//end writeblposrow
//==========================================================   
//==========================================================                  
void  writeblposcol(int c){
	//==========================================================   
	int num = 0;
	if (c == 0){
		for (int y = 1; y <= cmax - 1; ++y){
			writeblposcol(y);
		}
		return;
	}
	col[c].bcnt = 0;
	col[c].firstbl = 0;
	col[c].lastbl = 0;
	for (int y = 1; y <= cmax - 1; ++y){
		col[c].blpos[y] = 0;
	}
	for (int y = 1; y <= cmax - 1; ++y){
		num = col[c].row[y];
		if (num == 0){
			if (col[c].firstbl == 0){ col[c].firstbl = y; }
			col[c].lastbl = y;
			++col[c].bcnt;
			col[c].blpos[y] = col[c].bcnt;
		}
		else{
			col[c].blpos[y] = 0;
		}
	}
	return;
}
//========================================================== 
void  writeblposbox(int b){
	//==========================================================   
	int num = 0;
	if (b == 0){
		for (int y = 1; y <= cmax - 1; ++y){
			writeblposbox(y);
		}
		return;
	}
	box[b].bcnt = 0;
	box[b].firstbl = 0;
	box[b].lastbl = 0;
	for (int y = 1; y <= cmax - 1; ++y){
		box[b].blpos[y] = 0;
	}
	for (int y = 1; y <= cmax - 1; ++y){
		num = box[b].val[y];
		if (num == 0){
			++box[b].bcnt;
			if (box[b].firstbl == 0){ box[b].firstbl = y; }
			box[b].lastbl = y;

			box[b].blpos[y] = box[b].bcnt;
		}
		else{
			box[b].blpos[y] = 0;
		}
	}
	return;
}
//=========================================================  
//end writeblposbox
//==========================================================   
int finrow(int r, int value){
	//==========================================================   
	//==========================================================   	
	int res = 0;
	res = row[r].loc[value];
	// if (res>0){res=1;}    i need the hash index returned
	//  if ((res==9)&&(row[r].bcnt>1)&&(value==0)){res=row[r].firstbl;}
	return res;
}
//==========================================================   
//end finrow   	 
//==========================================================   
void writerowunittargrow(int runit, int num){
	//==========================================================   	 
	int start = 0;
	int stop = 0;
	if (num == 0){
		for (int y = 1; y <= 9; ++y){ writerowunittargrow(runit, y); }
		return;
	}
	if (runit == 0){ writerowunittargrow(1, num); writerowunittargrow(2, num); writerowunittargrow(3, num); return; }
	if (runit == 1){ start = 1; }
	else{
		if (runit == 2){ start = 4; }
		else{
			if (runit == 3){ start = 7; }
		}
	}
	if (rowunit[runit].nc[num] == 2){//test

		if (row[start].loc[num] == 0){ rowunit[runit].targrow[num] = start; }
		else{
			if (row[start + 1].loc[num] == 0){ rowunit[runit].targrow[num] = start + 1; }
			else{
				if (row[start + 2].loc[num] == 0){ rowunit[runit].targrow[num] = start + 2; }
			}
		}
	}
	return;
}
//==========================================================   	
//end writrowunittargrow 
//==========================================================   
//==========================================================   
void  writecolunittargcol(int cunit, int num){
	//==========================================================   	  	 
	int start = 0;
	int stop = 0;
	if (num == 0){
		for (int x = 1; x <= 9; ++x){ writecolunittargcol(cunit, x); }
		return;
	}
	if (cunit == 0){ writecolunittargcol(1, num); writecolunittargcol(2, num); writecolunittargcol(3, num); return; }
	if (cunit == 1){ start = 1; }
	else{
		if (cunit == 2){ start = 4; }
		else{
			if (cunit == 3){ start = 7; }
		}
	}
	//if (debug){ cout << "colunit[" << cunit << "].nc[" << num << "]=" << colunit[cunit].nc[num] << endl; }

	if (colunit[cunit].nc[num] == 2){
		if (col[start].loc[num] == 0){ colunit[cunit].targcol[num] = start; }
		else{
			if (col[start + 1].loc[num] == 0){ colunit[cunit].targcol[num] = start + 1; }
			else{
				if (col[start + 2].loc[num] == 0){ colunit[cunit].targcol[num] = start + 2; }
			}
		}
	//	if (debug){ cout << "colunit[" << cunit << "].targetcol[" << num << "]=" << colunit[cunit].targcol[num] << endl; }

	}

	return;
}
//==========================================================   	
//end writecolunittargcol 
//==========================================================   
void writerowunittargbox(int runit, int num){
	//==========================================================   	 
	int start = 0;
	int stop = 0;
	int res = 0;
	if (num == 0){
		for (int y = 1; y <= 9; ++y){ writerowunittargbox(runit, y); }
		return;
	}
	if (runit == 0){ writerowunittargbox(1, num); writerowunittargbox(2, num); writerowunittargbox(3, num); return; }
	if (runit == 1){ start = 1; }
	else{
		if (runit == 2){ start = 4; }
		else{
			if (runit == 3){ start = 7; }
		}
	}
	if (rowunit[runit].nc[num] == 3){
		rowunit[runit].targbox[num] = 0;
		rowunit[runit].targrow[num] = 0;
	}
	else{
		if (rowunit[runit].nc[num] == 2){
			if (rowunit[runit].targrow[num] != 0){
				res = finbox(start, num);
				if (res == 0){ rowunit[runit].targbox[num] = start; }
				else{
					res = finbox(start + 1, num);
					if (res == 0){ rowunit[runit].targbox[num] = start + 1; }
					else{
						res = finbox(start + 2, num);
						if (res == 0) { rowunit[runit].targbox[num] = start + 2; }
					}
				}
			}
		}
	}
	return;
}
//==========================================================   	
//end writerowunittargbox
//==========================================================   
//==========================================================   
void writecolunittargbox(int cunit, int num){
	//==========================================================   	 
	int start = 0;
	int stop = 0;
	int res = 0;
	if (num == 0){
		for (int x = 1; x <= 9; ++x){ writecolunittargbox(cunit, x); }
		return;
	}
	if (cunit == 0){ writecolunittargbox(1, num); writecolunittargbox(2, num); writecolunittargbox(3, num); return; }
	if (cunit == 1){ start = 1; }
	if (cunit == 2){ start = 2; }
	if (cunit == 3){ start = 3; }
	if (colunit[cunit].nc[num] == 3){
		colunit[cunit].targbox[num] = 0;
		colunit[cunit].targcol[num] = 0;
	}
	else{
		if (colunit[cunit].nc[num] == 2){
			if (colunit[cunit].targcol[num] != 0){
				res = finbox(start, num);
				if (res == 0){ colunit[cunit].targbox[num] = start; }
				else{
					res = finbox(start + 3, num);
					if (res == 0){ colunit[cunit].targbox[num] = start + 3; }
					else{
						res = finbox(start + 6, num);
						if (res == 0) { colunit[cunit].targbox[num] = start + 6; }
					}
				}
			}
		}
	}
	return;
}


//==========================================================   	
//end writecolunittargbox
//==========================================================   
//========================================================== 
void readboxes() {
	//==========================================================   
	for (int b = 1; b <= 9; ++b){
		box[b].bcnt = 0;
		readbox(b);
	}
	return;
}
//==========================================================   
//end readboxes()
//========================================================== 
//========================================================== 
void readbox(int b){
	//==========================================================   
	int starti = 0;
	int startj = 0;
	int pos = 1;
	for (int i = 1; i <= 9; ++i){ box[b].hash[i] = 0; box[b].val[i] = 0; }

	switch (b){
	case 0:return; break;
	case 1:starti = 1; startj = 1; break;
	case 2:starti = 1; startj = 4; break;
	case 3:starti = 1; startj = 7; break;

	case 4:starti = 4; startj = 1; break;
	case 5:starti = 4; startj = 4; break;
	case 6:starti = 4; startj = 7; break;

	case 7:starti = 7; startj = 1; break;
	case 8:starti = 7; startj = 4; break;
	case 9:starti = 7; startj = 7; break;
	}
	while (pos <= 9) {
		for (int i = starti; i <= starti + 2; ++i) {
			for (int j = startj; j <= startj + 2; ++j) {
				box[b].val[pos] = puzzle[i][j];
				int val = box[b].val[pos];
				if (val == 0){
					++box[b].bcnt;
				}

				box[b].hash[val] = pos;
				++pos;
			}
		}
	}
	init_box(b);
	return;
}
//==========================================================                                                                                                                                                                                                                                                   
//end readbox(int b)
//==========================================================   
int  finbox(int b, int value){
	//==========================================================   
	int res = 0;
	
	for (int i = 1; i <= 9; ++i){
		if (box[b].val[i] == value){
			res = i;
			break;
		}
	}
	if (res > 0){ res = 1; }
	
	return res;
}
//==========================================================    
//end finbox(int b,int value)
//==========================================================    
//==========================================================    
void procrowunit(int runit){
//========================================================== 

	int c1, c2, c3;
	for (int num = 1; num <= 9; ++num){
		if ((rowunit[runit].nc[num] == 2) && (rowunit[runit].targrow[num] != 0) && (rowunit[runit].targbox[num] != 0)){
			gcolsfromtargboxandtargrow(rowunit[runit].targbox[num], rowunit[runit].targrow[num], c1, c2, c3);
			int r = rowunit[runit].targrow[num];
			bool c1occupied = false;
			bool c2occupied = false;
			bool c3occupied = false;
			int numinc1, numinc2, numinc3;

			int places = 3;
			numinc1 = fincol(c1, num);
			if (numinc1){ --places; }
			else{ if (puzzle[r][c1] > 0){ --places; c1occupied = true; } }
			numinc2 = fincol(c2, num);
			if (numinc2){ --places; }
			else{ if (puzzle[r][c2] > 0){ --places; c2occupied = true; } }
			numinc3 = fincol(c3, num);
			if (numinc3){ --places; }
			else{ if (puzzle[r][c3] > 0){ --places; c3occupied = true; } }

			if (places == 1){
				if ((!numinc1) && (!c1occupied)){
					glastwrite = "procrowc1";
					inspuzzle(r, c1, num);
					if (glerr){ break; }				
				}
				if ((!numinc2) && (!c2occupied)){
					glastwrite = "procrowc2";
					inspuzzle(r, c2, num);
					if (glerr){ break; }
				}
				if ((!numinc3) && (!c3occupied)){
					glastwrite = "procrowc3";
					inspuzzle(r, c3, num);
					if (glerr){ break; }		
				}
			} //places=1
		
		} //nc=2
		if (glerr){ break; }
	} //for
	return;
}

//========================================================== 
//end procrowunit(runit)
//==========================================================    	
void  proccolunit(int cunit){
//==========================================================   

	int r1, r2, r3;
	for (int num = 1; num <= 9; ++num){
		if ((colunit[cunit].nc[num] == 2) && (colunit[cunit].targcol[num] != 0) && (colunit[cunit].targbox[num] != 0)){

			growsfromtargboxandtargcol(colunit[cunit].targbox[num], colunit[cunit].targcol[num], r1, r2, r3);
			int c = colunit[cunit].targcol[num];
			bool r1occupied = false;
			bool r2occupied = false;
			bool r3occupied = false;
			int numinr1, numinr2, numinr3;

			int places = 3;
			numinr1 = finrow(r1, num);
			if (numinr1){ --places; }
			else{ if (puzzle[r1][c] > 0){ --places; r1occupied = true; } }
			numinr2 = finrow(r2, num);
			if (numinr2){ --places; }
			else{ if (puzzle[r2][c] > 0){ --places; r2occupied = true; } }
			numinr3 = finrow(r3, num);
			if (numinr3){ --places; }
			else{ if (puzzle[r3][c] > 0){ --places; r3occupied = true; } }

			if (places == 1){
				if ((!numinr1) && (!r1occupied)){
					glastwrite = "proccolr1";
					inspuzzle(r1, c, num);
					if (glerr){ break; }
				}
				if ((!numinr2) && (!r2occupied)){
					glastwrite = "proccolr2";
					inspuzzle(r2, c, num);
					if (glerr){break; }
				}
				if ((!numinr3) && (!r3occupied)){
					glastwrite = "proccolr3";
					inspuzzle(r3, c, num);
					if (glerr){ break; }
				}
			} //places=1
		} //nc=2
		if (glerr){ break; }
	} //for
	return;
}
//==========================================================    
//========================================================== 
//end proccolunit(cunit)
//==========================================================  

//==========================================================    
//==========================================================    
int gnb(int inwhat, int where, int cb){
	int bcnt = gbls(inwhat, where);
	int res = 0;
	int index = 0;
	if (where == 0){ return 0; }
	//  if (where==0){//cout<<"err function gnb where = 0 line 1394"<<endl;return 0;}
	switch (inwhat) {
	case zrow:if (row[where].bcnt == 0) { break; }
			  index = cb;
			  ++index;
			  while (index <= 9){
				  if (row[where].col[index] == 0){ break; }
				  ++index;

			  }
			  if (index >= 9){ if (row[where].col[9] != 0){ index = 0; } }
			  break;
	case zcol:  if (col[where].bcnt == 0) { break; }
				index = cb;
				++index;
				while (index <= 9){
					if (col[where].row[index] == 0){ break; }
					++index;
				}
				if (index >= 9){ if (col[where].row[9] != 0){ index = 0; } }
				break;

	case zbox: if (box[where].bcnt == 0) { break; }
			   index = cb;
			   ++index;
			   while (index <= 9){
				   if (box[where].val[index] == 0){ return index; break; }
				   ++index;
			   }
			   if (index>9) { return 0; }
			   break;
	}
	if (cb == 9){ cb = 0; }
	if (cb == 0){ index = gfb(inwhat, where); }
	res = index;
	if (res>9){ res = 0; }

	return res;
}
//==========================================================    
//end gnb  
//==========================================================    
int gprevbl(int inwhat, int where, int cb){
	//========================================================== 
	//==========================================================   
	int res = 0;
	int index = 0;
	int bcnt = gbls(inwhat, where);
	switch (inwhat) {
	case zrow: if (row[where].bcnt == 0) { return 0; }
			   index = cb;
			   if (index <= 0){ index = 10; }
			   --index;
			   while (index>0){
				   if (row[where].col[index] == 0){ return index; break; }
				   --index;
			   }
			   // return 0;	                                      
			   break;
	case zcol: if (col[where].bcnt == 0) { return 0; }
			   index = cb;
			   --index;
			   if (index <= 0){ index = 10; }
			   while (index>0){
				   if (box[where].val[index] == 0){ return index; break; }
				   --index;
			   }
			   // return 0;	                                             
			   break;
	case zbox: if (box[where].bcnt == 0) { return 0; }
			   index = cb;
			   --index;
			   if (index <= 0){ index = 10; }
			   while (index>0){
				   if (box[where].val[index] == 0){ return index; break; }
				   --index;
			   }
			   //   return 0;	                                          	                                                                                                                                                
			   break;
	}
	return res;
}
//========================================================== 
//end gprevbl
//==========================================================                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
//==========================================================   
int  fincol(int c, int value){
	//========================================================== 
	//==========================================================   	
	int res = col[c].loc[value];
	if (res>0){ res = 1; }
	return res;
}
//========================================================== 
//end fincol
//==========================================================   	
int fboxfromrow(int r, int pos){
	int unit = 0;
	int box = 0;
	if (r<4){ unit = 1; }
	if (r>6){ unit = 3; }
	else{ unit = 2; }
	if (pos<4){
		switch (unit){
		case 1:box = 1; break;
		case 2:box = 4; break;
		case 3:box = 7; break;
		}
	}
	else{
		if (pos>6){
			switch (unit){
			case 1:box = 3; break;
			case 2:box = 6; break;
			case 3:box = 9; break;
			}
		}
		else{
			switch (unit){
			case 1: box = 2; break;
			case 2: box = 5; break;
			case 3: box = 8; break;
			}
		}
	}
	return box;
}
//========================================================== 
//end fboxfromrow
//==========================================================                                                                                                                                                                      
//==========================================================              
int gmincol(int c, int &m1, int &m2, int &m3){
	//==========================================================              
	//Captures value of m numbers in col c .  The numbers are returned in                    
	//ascending order. res contains the cnt of m numbers.                               
	//first 3 m numbers are returned;                                                        
	//==========================================================              
	//  c     = col                                                                               
	//  res = number cnt                                                               
	//  &m1,&m2,&m3 = first 3 values of m numbers.                                           
	//==========================================================              
	int res = 0;
	//==========================================================              
	string err = "err in parameters -function gmincol";
	//==========================================================                                                                                                           
	m1 = 0;
	m2 = 0;
	m3 = 0;
	int i = 1;
	while (i <= 9){
		if (col[c].loc[i] == 0){
			++res;
			if (m1 == 0){ m1 = i; }
			else{
				if (m2 == 0){ m2 = i; }
				else{
					if (m3 == 0){ m3 = i; }
				}
			}
		}
		++i;
	}
	return res;
}
//==========================================================              
//end function gmincol                                                                 
//==========================================================   
//==========================================================              
int gminrow(int r, int &m1, int &m2, int &m3){
	//==========================================================              
	//Captures value of m numbers in row r .  The numbers are returned in                    
	//ascending order. res contains the cnt of m numbers.                               
	//first 3 m numbers are returned;                                                        
	//==========================================================              
	//  r      = row                                                                               
	//  res = number cnt                                                               
	//  &m1,&m2,&m3 = first 3 values of m numbers.                                           
	//==========================================================              
	int res = 0;
	//==========================================================              
	string err = "err in parameters -function gminrow";
	//==========================================================                                                                                                            
	m1 = 0;
	m2 = 0;
	m3 = 0;
	int i = 1;
	// if ((r<=0)||(r>9)){//cout<<err<<endl;}                                                              
	while (i <= 9){
		if (row[r].loc[i] == 0){
			++res;
			if (m1 == 0){ m1 = i; }
			else{
				if (m2 == 0){ m2 = i; }
				else{
					if (m3 == 0){ m3 = i; }
				}
			}
		}
		++i;
	}
	return res;
}
//==========================================================              
//end function gminrow                                                                 
//==========================================================   
//=========================================================             
int gminbox(int b, int &m1, int &m2, int &m3){
	//==========================================================              
	//Captures value of m numbers in box b .  The numbers are returned in                    
	//ascending order. res contains the cnt of m numbers.                               
	//first 3 m numbers are returned;                                                        
	//==========================================================              
	//  b      = box                                                                              
	//  res = number cnt                                                               
	//  &m1,&m2,&m3 = first 3 values of m numbers.                                           
	//==========================================================              
	int res = 0;
	//==========================================================              
	string err = "err in parameters -function gminginbox";
	//==========================================================                                                                                                          
	m1 = 0;
	m2 = 0;
	m3 = 0;
	int i = 1;
	if ((b <= 0) || (b>9)){ return 0; }
	while (i <= 9){
		if (box[b].hash[i] == 0){
			++res;
			if (m1 == 0){ m1 = i; }
			else{
				if (m2 == 0){ m2 = i; }
				else{
					if (m3 == 0){ m3 = i; }
				}
			}
		}
		++i;
	}
	return res;
}
//==========================================================    
//end gminbox       
//==========================================================                                                                                              
//==========================================================              
//end function gminbox 
//========================================================== 

//==========================================================
int growfromboxandpos(int b, int pos){ //                                         
	//==========================================================
	int r = 0;
	if (b <= 0) { return 0; }
	//if (pos<=0) {return 0;}
	//if (b>9) {return 0;}
	//if (pos>9) {return 0;}
	switch (b){
	case 1:case 2:case 3:   if (pos<4){ r = 1; }
		   else{ if (pos>6){ r = 3; } else{ r = 2; } }break;
	case 4:case 5:case 6:   if (pos<4){ r = 4; }
		   else{ if (pos>6){ r = 6; } else{ r = 5; } }break;
	case 7:case 8:case 9:   if (pos<4){ r = 7; }
		   else{ if (pos>6){ r = 9; } else{ r = 8; } }break;
	}
	return r;
}
//==========================================================                                        
//end growfromboxandpos                                                                           
//==========================================================                                                               
int growfromcolandpos(int c, int pos){//                                                           
	//==========================================================                                                               
	int r = 0;
	if (c <= 0) { return 9999; }
	if (pos <= 0) { return 0; }
	r = pos;
	return r;
}
//end growfromcolandpos                                                                          
//==========================================================                                                               
//==========================================================                                                               
int gcolfromboxandpos(int b, int pos){ //                                                          
	//==========================================================                                                               
	int c = 0;
	if (b <= 0) { return 0; }
	if (pos <= 0) { return 0; }

	switch (b){
	case 1:case 4:case 7: switch (pos){
	case 1:case 4:case 7: c = 1; break;
	case 2:case 5:case 8: c = 2; break;
	case 3:case 6:case 9: c = 3; break;
	}
		   break;
	case 2:case 5:case 8: switch (pos){
	case 1:case 4:case 7: c = 4; break;
	case 2:case 5:case 8: c = 5; break;
	case 3:case 6:case 9: c = 6; break;
	}
		   break;
	case 3:case 6:case 9:  switch (pos){
	case 1:case 4:case 7: c = 7; break;
	case 2:case 5:case 8: c = 8; break;
	case 3:case 6:case 9: c = 9; break;
	}
		   break;
	}
	return c;
}
//==========================================================  
//end gcolfromboxandpos                                                                            
//==========================================================                                         
//end gcolfromboxandrow                                                                            
//==========================================================                                         
//==========================================================                                                                
int gcolfromrowandpos(int r, int pos){//                                                            
	//==========================================================
	int c = 0;
	if (r == 0) { return 0; }
	if (pos <= 0) { return 0; }
	c = pos;
	return c;
}
//==========================================================   
//end gcolfromrowandpos                                                                                  
//==========================================================                                                                      
//==========================================================                                               
int gboxfromrowandcol(int r, int c){//                                                                    
	//==========================================================                                                                      
	int b = 0;
	if (r <= 0) { cout << "PPPPP" << endl; exit(0); return 0; }
	if (c <= 0) { cout << "IIIIIIIII" << endl; exit(0); return 0; }
	switch (c){
	case 1:case 2:case 3: if (r<4){ b = 1; }
		   else{ if (r>6){ b = 7; } else{ b = 4; } }
		   break;
	case 4:case 5:case 6: if (r<4){ b = 2; }
		   else{ if (r>6){ b = 8; } else{ b = 5; } }
		   break;
	case 7:case 8:case 9: if (r<4){ b = 3; }
		   else{ if (r>6){ b = 9; } else{ b = 6; } }
		   break;
	}

	return b;
}
//==========================================================                                                                                                        
//end gboxfromrowandcol                                                                                  
//==========================================================                                               
//==========================================================                                               
int gboxfromrowandpos(int r, int pos){//                                                                  
	//==========================================================                                                                      
	int b = 0;
	//if (r <= 0) { cout << "function gboxfromrowandpos -  box number =0" << endl; return 0; }
	//if (pos <= 0) { cout << "function gboxfromrowandpos - insert pos =0" << endl; return 0; }
	switch (r){
	case 1:case 2:case 3: if (pos<4){ b = 1; }
		   else{ if (pos>6){ b = 3; } else{ b = 2; } }
		   break;
	case 4:case 5:case 6: if (pos<4){ b = 4; }
		   else{ if (pos>6){ b = 6; } else{ b = 5; } }
		   break;
	case 7:case 8:case 9: if (pos<4){ b = 7; }
		   else{ if (pos>6){ b = 9; } else{ b = 8; } }
		   break;
	}
	return b;
}
//==========================================================                                         
//end gboxfromrowandpos                                                                            
//==========================================================                                         
//==========================================================                                                                
int gboxfromcolandpos(int c, int pos){//                                                            
	//==========================================================
	int b = 0;
	//if (c<=0) {cout <<"err function gboxfromcolandpos -  box number =0"<<endl;return 0;}
	//if (pos<=0) {cout <<"err function gboxfromcolandpos - insert pos 0"<<endl;return 0;}
	switch (c){
	case 1:case 2:case 3:   if (pos<4){ b = 1; }
		   else{ if (pos>6){ b = 7; } else { b = 4; } }
		   break;
	case 4:case 5:case 6:   if (pos<4){ b = 2; }
		   else{ if (pos>6){ b = 8; } else { b = 5; } }
		   break;
	case 7:case 8:case 9:   if (pos<4){ b = 3; }
		   else{ if (pos>6){ b = 9; } else { b = 6; } }
		   break;

	}
	return b;
}
//==========================================================
// end gboxfromcolandpos                                                            
//==========================================================
//==========================================================
void gcolsfromtargboxandtargrow(int targbox, int targrow, int &c1, int &c2, int &c3){
	//==========================================================
	c1 = 0; c2 = 0; c3 = 0;

	switch (targrow){
	case 1:case 2:case 3:switch (targbox){
	case 1: c1 = 1; c2 = 2; c3 = 3; break;
	case 2: c1 = 4; c2 = 5; c3 = 6; break;
	case 3: c1 = 7; c2 = 8; c3 = 9; break;
	}
		   break;
	case 4:case 5:case 6:switch (targbox){
	case 4:c1 = 1; c2 = 2; c3 = 3; break;
	case 5:c1 = 4; c2 = 5; c3 = 6; break;
	case 6:c1 = 7; c2 = 8; c3 = 9; break;
	}
		   break;
	case 7:case 8:case 9:switch (targbox){
	case 7:c1 = 1; c2 = 2; c3 = 3; break;
	case 8:c1 = 4; c2 = 5; c3 = 6; break;
	case 9:c1 = 7; c2 = 8; c3 = 9; break;
	}
		   break;

		   break;
	}
	return;
	//==========================================================
	//end gcolsfromtargboxandtargrow(int targbox,targrow,&c1,&c2,&c3) 
	//==========================================================
}
//==========================================================   
void growsfromtargboxandtargcol(int targbox, int targcol, int &r1, int &r2, int &r3){
	//==========================================================
	r1 = 0; r2 = 0; r3 = 0;
	switch (targcol){
	case 1:case 2:case 3:switch (targbox){
	case 1: r1 = 1; r2 = 2; r3 = 3; break;
	case 4: r1 = 4; r2 = 5; r3 = 6; break;
	case 7: r1 = 7; r2 = 8; r3 = 9; break;
	}
		   break;
	case 4:case 5:case 6:switch (targbox){
	case 2:r1 = 1; r2 = 2; r3 = 3; break;
	case 5:r1 = 4; r2 = 5; r3 = 6; break;
	case 8:r1 = 7; r2 = 8; r3 = 9; break;
	}
		   break;
	case 7:case 8:case 9:switch (targbox){
	case 3:r1 = 1; r2 = 2; r3 = 3; break;
	case 6:r1 = 4; r2 = 5; r3 = 6; break;
	case 9:r1 = 7; r2 = 8; r3 = 9; break;
	}
		   break;
		   break;
	}
	return;
	//==========================================================
	//end growsfromtargboxandtargcol(int targbox,targrow,&c1,&c2,&c3) 
	//==========================================================
}
//==========================================================
int insert_m(int inwhat, int where){
	//==========================================================
	//cout<<"in function insert_m"<<endl;   
	//     if (where==0){cout <<"where = 0 line 2219"<<endl;return 1;}
	//readpuzzle();
	int m = 0;
	int const zunit = 3;
	//     int r,c,u,num;
	int insertpointrow = 0;
	int insertpointcol = 0;
	int insertpointbox = 0;
	int insertpoint = 0;
	int res = 0;
	int m1 = 0;
	int m2 = 0;
	int m3 = 0;
	int box1 = 0;

	switch (inwhat){
	case zrow:
		m = gminrow(where, m1, m2, m3);
		if (m == 0){
			//cout<<"m=0"<<endl;

			return 0;
		}
		insertpointcol = gfb(zrow, where);
		box1 = gboxfromrowandcol(where, insertpointcol);
		res = finbox(box1, m1);
		if (res>0){ return 0; }
		//cout <<"err ALREADY IN BOX = "<<box1 <<endl; //cout<<"ROW="<<where<<"m="<<m1<<endl;printpuzzle();return 0;}
		glastwrite = "1873       "; res = inspuzzle(where, insertpointcol, m1);
		if (res>0){

		}

		break;
	case zcol:   if (col[where].bcnt != 1)   { return 0; }
				 m = gmincol(where, m1, m2, m3);
				 if (m == 0){

					 //cout<<"m=0"<<"err function insert_m COL="<<where<<endl; 
					 return 0;

				 }
				 insertpointrow = gfb(zcol, where);
				 if (insertpointrow == 0){ return 0; }//cout<<"err function insert_m"<<endl;return 0;}  
				 glastwrite = "1893         "; res = inspuzzle(insertpointrow, where, m1);
				 if (res>0){
					 col[where].done = true;
					 writeblposcol(insertpointrow);
					 writeblposrow(where);
					 int bx = gboxfromrowandcol(insertpointrow, where);
					 writeblposbox(bx);
				 }

				 break;
	case zbox: //box[where].bcnt = 0;
	//	readbox(where);
		int bcnt = gminbox(where, m1, m2, m3);
		if (bcnt != 1){

			//cout<<"err bcnt="<<bcnt<<"box["<<where<<"]="<<box[where].bcnt<<endl;
			return 0;
		}
		insertpointbox = gfb(zbox, where);
		int r = growfromboxandpos(where, insertpointbox);
		int c = gcolfromboxandpos(where, insertpointbox);
		glastwrite = "1919         "; res = inspuzzle(r, c, m1);
		if (res>0){

		}

		break;
	}
	return res;
}
//==========================================================
//end insert_m
//==========================================================                                                                       
void checksumall(){
	//==========================================================
	//readpuzzle();
	int checksum = 0;
	int res = 0;
	int localerr = 0;
	int rowchecksum = 0;
	int boxchecksum = 0;
	int colchecksum = 0;
	int saver = 0;
	time_t hold_time;
	hold_time = time(NULL);
	int number = 0;

	//time_t elapsedtime = hold_time - start_time;
	// auto gltime1 = std::chrono::high_resolution_clock::now();
	//auto gltime2=std::chrono::duration_cast<std::chrono::microseconds>(time).count()
	auto gltime2 = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	 auto gelapsedtime = gltime2 - gltime1;


//	cout << endl;
//cout << "*****************************************************" << endl;
//cout << "checksums" << endl;
//	cout << "*****row checksums *****" << endl;
//	for (int r = 1; r <= 9; ++r){
//		row[r].checksum = 0;
//		checksum = 0;
//		for (int i = 1; i <= 9; ++i){ checksum = checksum + row[r].col[i]; }
//		row[r].checksum = checksum;
//		rowchecksum = rowchecksum + row[r].checksum;
//		cout << "row[" << r << "].checksum=" << checksum << endl;
//	}
//	cout << "*****col checksums *****" << endl;
//	for (int c = 1; c <= 9; ++c){
//		col[c].checksum = 0;
//		checksum = 0;
//		for (int i = 1; i <= 9; ++i){ checksum = checksum + col[c].row[i]; }
//		col[c].checksum = checksum;
//		colchecksum = colchecksum + col[c].checksum;
//		cout << "col[" << c << "].checksum=" << checksum << endl;
//	}
//	cout << "*****box checksums *****" << endl;
//	for (int b = 1; b <= 9; ++b){
//		box[b].checksum = 0;
//		box[b].bcnt = 0;
//		readbox(b);
//		checksum = 0;
//		for (int i = 1; i <= 9; ++i){ checksum = checksum + box[b].val[i]; }
//		box[b].checksum = checksum;
//		boxchecksum = boxchecksum + box[b].checksum;
//		cout << "box[" << b << "].checksum=" << checksum << endl;
//	}
//	int number = 0;
//	cout << endl;
	cout << "=====================================================" << endl;

	cout << endl;
	zcnt = 0;
	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			number = puzzle[x][y];
			cout << number;
			if (number == 0){ zcnt++; }
			if ((y == 3) || (y == 6)){ cout << " "; }
		}
		if ((x == 3) || (x == 6)){ cout << endl; }
		cout << endl;
	}
	cout << endl;

	cout << "puzzle type=" << puzzletype << endl;
	if (gelapsedtime >= 1000){
		cout << "Elapsed time is: " << gelapsedtime / 1000 << " milliseconds" << endl;
	}
	else{
		if (gelapsedtime == 0){ cout << "elapsed time < 500 microseconds" << endl; }
		else { cout << "elapsed time= " << gelapsedtime << " microseconds" << endl; }
	}
	//cout << endl;
	cout << "# initial clues=" << 81-initzcnt << endl;
	cout << "guesscount=" << guesscount << endl;
//	cout << endl;
//	cout << endl;
	if (guesscount == 0){
		cout << "# solved before first guess=" << initzcnt << endl;
	}
	else{
		cout << "# solved before first guess=" << savegwi << endl;
	}
//cout << endl;
	cout << "# solved squares=" <<initzcnt << endl;
	cout << endl;

	dumporder();
	if (zcnt == 0){
		if (glerr == 0){
			cout << endl;
			pdone = true;
		}
	}



	remove("i.txt");
	if ((puzzletype != "batch") && (puzzletype != "manual input")){
		remove("view-source_view.websudoku.com__level=1.html");
		remove("view-source_show.websudoku.com__level=1.html");
		remove("view-source_view.websudoku.com__level=2.html");
		remove("view-source_show.websudoku.com__level=2.html");
		remove("view-source_view.websudoku.com__level=3.html");
		remove("view-source_show.websudoku.com__level=3.html");
		remove("view-source_view.websudoku.com__level=4.html");
		remove("view-source_show.websudoku.com__level=4.html");

		remove("view-source_https___nine.websudoku.com__level=4.html");
		remove("view-source_https___nine.websudoku.com__level=3.html");
		remove("view-source_https___nine.websudoku.com__level=2.html");
		remove("view-source_https___nine.websudoku.com__level=1.html");

		remove("view-source_https___show.websudoku.com__level=4.html");
		remove("view-source_https___show.websudoku.com__level=3.html");
		remove("view-source_https___show.websudoku.com__level=2.html");
		remove("view-source_https___show.websudoku.com__level=1.html");

		remove("view-source_https___view.websudoku.com__level=4.html");
		remove("view-source_https___view.websudoku.com__level=3.html");
		remove("view-source_https___view.websudoku.com__level=2.html");
		remove("view-source_https___view.websudoku.com__level=1.html");
	}
	else{ remove("webpuzzle.html"); }





	return;
}
//==========================================================
//end insert_m
//==========================================================                                                                       

//==========================================================                                                                  
void init_box(int b){
	//==========================================================  
	initemptyboxrowsandcols(b);

	box[b].r1done = true;
	box[b].r2done = true;
	box[b].r3done = true;
	box[b].c1done = true;
	box[b].c2done = true;
	box[b].c3done = true;

	//rows
	for (int x = 1; x<4; ++x) {
		box[b].r1[x] = box[b].val[x];
		box[b].r2[x] = box[b].val[x + 3];
		box[b].r3[x] = box[b].val[x + 6];
	}
	//columns
	box[b].c1[1] = box[b].r1[1];
	box[b].c1[2] = box[b].r2[1];
	box[b].c1[3] = box[b].r3[1];

	box[b].c2[1] = box[b].r1[2];
	box[b].c2[2] = box[b].r2[2];
	box[b].c2[3] = box[b].r3[2];

	box[b].c3[1] = box[b].r1[3];
	box[b].c3[2] = box[b].r2[3];
	box[b].c3[3] = box[b].r3[3];

	int val1, val2, val3 = 0;
	for (int x = 1; x <= 3; ++x) {
		val1 = box[b].r1[x];
		val2 = box[b].r2[x];
		val3 = box[b].r3[x];
		int   val4 = box[b].c1[x];
		int   val5 = box[b].c2[x];
		int   val6 = box[b].c3[x];

		if (!val1) { box[b].r1done = false; }
		if (!val2) { box[b].r2done = false; }
		if (!val3) { box[b].r3done = false; }
		if (!val4) { box[b].c1done = false; }
		if (!val5) { box[b].c2done = false; }
		if (!val6) { box[b].c3done = false; }
	}
	return;
}

int gfb(int inwhat, int where){
	//==========================================================   
	int res = 0;
	if (where == 0){ cout << "err gfb where =0" << endl; return 0; }
	int firstbl = 0;
	switch (inwhat) {
	case zrow:
		for (int y = 1; y <= 9; ++y){
			if (row[where].col[y] == 0){ firstbl = y; break; }
		}
		if (firstbl != 0){ row[where].firstbl = firstbl; }
		return firstbl;
		break;
	case zcol:
		for (int y = 1; y <= 9; ++y){
			if (col[where].row[y] == 0){ firstbl = y; break; }
		}
		if (firstbl != 0){ col[where].firstbl = firstbl; }
		return firstbl;
		break;
	case zbox:
		for (int y = 1; y <= 9; ++y){
			if (box[where].val[y] == 0){ firstbl = y; break; }
		}
		if (firstbl != 0){ box[where].firstbl = firstbl; }
		return firstbl;
		break;
	}
	return firstbl;
}
//==========================================================  
//end gfb
//==========================================================   
//==========================================================  
int glastbl(int inwhat, int where){
	//==========================================================  
	int lastbl = 0;
	switch (inwhat) {
	case zrow: if (row[where].bcnt == 0) { return 0; break; }
			   for (int y = 9; y >= 1; --y){
				   if (row[where].col[y] == 0) { lastbl = y; break; }
			   }
			   if (lastbl>0){ row[where].lastbl = lastbl; }
			   return lastbl;
			   break;
	case zcol: if (col[where].bcnt == 0) { return 0; break; }
			   for (int x = 9; x >= 1; --x){
				   if (col[where].row[x] == 0) { lastbl = x; break; }
			   }
			   if (lastbl>0){ col[where].lastbl = lastbl; }
			   return lastbl;
			   break;
	case zbox: if (box[where].bcnt == 0) { return 0; break; }
			   for (int b = 9; b >= 1; --b){
				   if (box[where].val[b] == 0) { lastbl = b; break; }
			   }
			   if (lastbl>0){ box[where].lastbl = lastbl; }
			   return lastbl;
			   break;
	}
	return lastbl;
}
//==========================================================  
//end glastbl
//==========================================================  
//==========================================================  
int checkrows(){
	//==========================================================  
	int res = 0;
	for (int r = 1; r <= 9; ++r){
		res = 0;
		int m1 = 0; int m2 = 0; int m3 = 0;
		int mcnt = gminrow(r, m1, m2, m3);
		if (res>0){ ; }
	}

	return res;
}
//==========================================================
// end checkrows()
//==========================================================
int  checkcols(){
	//==========================================================
	int res = 0;
	for (int c = 1; c <= 9; ++c){
		res = 0;
		int m1 = 0; int m2 = 0; int m3 = 0;
		int mcnt = gmincol(c, m1, m2, m3);
		if (res>0){ ; }
	}

	return res;
}
//==========================================================  
// end checkcols()
//==========================================================  
int checkboxes(){
	//==========================================================  
	int res = 0;
	for (int b = 1; b <= 9; ++b){
		res = 0;
		int m1 = 0; int m2 = 0; int m3 = 0;
		box[b].bcnt = 0;
		readbox(b);
		if (res>0){ ; }
	}

	return res;
}
//==========================================================   
//end checkboxes()
//==========================================================   

//==========================================================     
//==========================================================                 
int gallminrow(int r, int &m1, int &m2, int &m3, int &m4, int &m5, int &m6, int &m7, int &m8, int &m9){
	//==========================================================                 
	//Captures value of m numbers in row r .  The numbers are returned in                    
	//ascending order. res contains the cnt of m numbers.                               
	//All m numbers are returned;                                                        
	//==========================================================                 
	//  r      = row                                                                               
	//  res = number cnt                                                               
	//  &m1,&m2,&m3..&m9  =  values of m numbers.                                           
	//==========================================================                  
	int res = 0;
	//==========================================================                  
	string err = "err in parameters -function gallminrow";
	//==========================================================                                                                                                                
	m1 = 0;  m4 = 0;  m7 = 0;
	m2 = 0;  m5 = 0;  m8 = 0;
	m3 = 0;  m6 = 0;  m9 = 0;

	int i = 1;
	if ((r <= 0) || (r > 9)){ cout << err << endl; exit(0); }
	while (i <= 9){
		if (row[r].loc[i] == 0){
			++res;
			if (m1 == 0){ m1 = i; }
			else{
				if (m2 == 0){ m2 = i; }
				else{
					if (m3 == 0){ m3 = i; }
					else{
						if (m4 == 0){ m4 = i; }
						else{
							if (m5 == 0){ m5 = i; }
							else{
								if (m6 == 0){ m6 = i; }
								else{
									if (m7 == 0){ m7 = i; }
									else{
										if (m8 == 0){ m8 = i; }
										else{
											if (m9 == 0){ m9 = i; break; }
										}
									}
								}
							}
						}
					}
				}
			}
		}
		++i;
	}
	return res;
}
//==========================================================                 
//end function gallminrow                                                                 
//==========================================================    
int gallminbox(int b, int &m1, int &m2, int &m3, int &m4, int &m5, int &m6, int &m7, int &m8, int &m9){
	//==========================================================                               
	//Captures value of m numbers in box b .  The numbers are returned in                
	//ascending order. res contains the cnt of m numbers.                           
	//All m numbers are returned;                                                        
	//==========================================================                               
	//  b     = box                                                                           
	//  res = number cnt                                                           
	//  &m1,&m2,&m3..&m9  =  values of m numbers.                                        
	//==========================================================                               
	int res = 0;
	//==========================================================                               
	string err = "err in parameters -function gallminbox";
	//==========================================================                               
	m1 = 0;  m4 = 0;  m7 = 0;
	m2 = 0;  m5 = 0;  m8 = 0;
	m3 = 0;  m6 = 0;  m9 = 0;

	int i = 1;
	if ((b <= 0) || (b>9)){ cout << err << endl; }
	while (i <= 9){
		if (box[b].hash[i] == 0){
			++res;
			if (m1 == 0){ m1 = i; }
			else{
				if (m2 == 0){ m2 = i; }
				else{
					if (m3 == 0){ m3 = i; }
					else{
						if (m4 == 0){ m4 = i; }
						else{
							if (m5 == 0){ m5 = i; }
							else{
								if (m6 == 0){ m6 = i; }
								else{
									if (m7 == 0){ m7 = i; }
									else{
										if (m8 == 0){ m8 = i; }
										else{
											if (m9 == 0){ m9 = i; }
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (i == 9){ break; }
		++i;

	}
	return res;
}
//==========================================================                               
//end function gallminbox                                                          
//==========================================================                               

//==========================================================  
void printrowposandbls(int which){
	//==========================================================  

	//cout <<"==========================================================="<<endl;
	//cout <<"row["<<which<<"].bcnt="<<row[which].bcnt<<endl;
	//cout <<"row["<<which<<"].firstbl="<<row[which].firstbl<<endl;
	//cout <<"row["<<which<<"].lastbl ="<<row[which].lastbl<<endl;
	//cout <<"==========================================================="<<endl;
	//cout <<" c row contents"<<endl;
	//cout <<"==========================================================="<<endl;
	//    for (int i=1;i<=9;++i){

	//cout<<"row["<<which<<"].col["<<i<<"]= "<<row[which].col[i]<<" ";
	//   }
	//cout<<endl;
	//cout<<" c bl position array"<<endl;
	//cout <<"==========================================================="<<endl;
	//     for (int i=1;i<=9;++i){

	//cout<<"row["<<which<<"].blpos["<<i<<"]= "<<row[which].blpos[i]<<" ";
	//   }
	//cout<<endl;
	//cout<<"c number location positional array"<<endl;
	//cout<<"==========================================================="<<endl;
	//    for (int i=1;i<=9;++i){

	//cout<<"row["<<which<<"].loc["<<i<<"]= "<<row[which].loc[i]<<" ";
	//   }
	//cout<<endl;
	//cout<<"==========================================================="<<endl;
	//cout<<"missing numbers array"<<endl;
	//cout<<"==========================================================="<<endl;
	//cout<<"row[1].bcnt="<<row[1].bcnt<<endl;
	//   for (int i=1;i<=9;i++){
	//cout<<"mrow["<<i<<"]="<<mrow[i]<<"  ";}
	//cout<<endl;

	//cout<<"==========================================================="<<endl;
	//cout<<"blanks  array"<<endl;
	//cout<<"==========================================================="<<endl;

	//  for (int i=1;i<=row[which].bcnt;i++){
	//cout<<"blrow["<<i<<"]="<<blrow[i]<<"  ";}
	//cout<<endl;
	//}
	return;
}
//==========================================================  
//end printrowposandbls                                                                                                                                                                  
//========================================================== 


//==========================================================                 
int gallmincol(int c, int &m1, int &m2, int &m3, int &m4, int &m5, int &m6, int &m7, int &m8, int &m9){
	//==========================================================                 
	//Captures value of m numbers in col c .  The numbers are returned in                    
	//ascending order. res contains the cnt of m numbers.                               
	//All m numbers are returned;                                                        
	//==========================================================                 
	//  c      = col                                                                               
	//  res = number cnt                                                               
	//  &m1,&m2,&m3..&m9  =  values of m numbers.                                           
	//==========================================================                  
	int res = 0;
	//==========================================================                  
	string err = "err in parameters -function gallmincol";
	//==========================================================                                                                                                                
	m1 = 0;  m4 = 0;  m7 = 0;
	m2 = 0;  m5 = 0;  m8 = 0;
	m3 = 0;  m6 = 0;  m9 = 0;


	int i = 1;
	// if ((c<=0)||(c>9)){//cout<<err<<endl;}                                                              
	while (i <= 9){
		if (col[c].loc[i] == 0){
			++res;
			if (m1 == 0){ m1 = i; }
			else{
				if (m2 == 0){ m2 = i; }
				else{
					if (m3 == 0){ m3 = i; }
					else{
						if (m4 == 0){ m4 = i; }
						else{
							if (m5 == 0){ m5 = i; }
							else{
								if (m6 == 0){ m6 = i; }
								else{
									if (m7 == 0){ m7 = i; }
									else{
										if (m8 == 0){ m8 = i; }
										else{
											if (m9 == 0){ m9 = i; break; }
										}
									}
								}
							}
						}
					}
				}
			}
		}
		++i;
	}
	return res;
}
//==========================================================                 
//end function gallmincol                                                                 
//==========================================================
void rldsaved(){
	if (debug){
		cout << "************************Reloading initial puzzle" << endl; cout << "glerr= " << glerr << endl;
		printpuzzle();  
		growinserted = false;
	//	printgbtables();
		cout << "current guess count = " << top << endl;
		for (int i = 1; i <= top; i++){
			cout << "glist[" << i << "].r=" << glist[i].r << endl;
			cout << "glist[" <<i << "].c=" << glist[i].c << endl;
			cout << "glist[" << i << "].v=" << glist[i].v << endl;
			cout << "glist[" << i << "].zcnt=" << glist[i].zcnt << endl;
		}
	}
	glerr = false;
	int num = 0;
	zcnt = 0;
	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			puzzle[x][y] = spuzzle[0][x][y];
			num = puzzle[x][y];
			row[x].col[y] = num;
			col[y].row[x] = num;
			box[x].hash[y] = num;
			row[x].loc[num] = y;
			col[y].loc[num] = x;
			if (num == 0){ zcnt++; }
		}
	} 
	updp();	 
	for (int i = 1; i <= top; i++){ insbtable(i); }
	cleargtable();
	rowunit[1].udone = false;
	rowunit[2].udone = false;
	rowunit[3].udone = false;
	colunit[1].udone = false;
	colunit[2].udone = false;
	colunit[3].udone = false;
	pdone = false;	 
	lastwritecnt = 0;
	lzcnt = zcnt;
	return;
}
//==========================================================
//end popp
//==========================================================   
//==========================================================   
//==========================================================
void saveinitialpuzzle(){
	//==========================================================

	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			spuzzle[0][x][y] = puzzle[x][y];
		//	cout << spuzzle[0][x][y];
			//if (y == 9){ cout << endl; }
		}
	}
	stackptr = 0;
	//initzcnt = zcnt;
	return;
}
//==========================================================
//end saveinitialpuzzle
//==========================================================   
//==========================================================
void printgbtables(){
	cout << endl;
	cout << "gcnt=" << top << endl;
	cout << "gtable======================" << endl;
	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			int number = gtable[x][y];
			if (y == 1){ cout << "                    " << number; }
			else{
				cout << number;
			}
			if ((y == 3) || (y == 6)){ cout << " "; }
		}
		if ((x == 3) || (x == 6)){ cout << endl; }
		cout << endl;
	}
	cout << endl;
	cout << "btable======================" << endl;
	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			int number = btable[x][y];
			if (y == 1){ cout << "                    " << number; }
			else{
				cout << number;
			}
			if ((y == 3) || (y == 6)){ cout << " "; }
		}
		if ((x == 3) || (x == 6)){ cout << endl; }
		cout << endl;
	}
	cout << endl;
	cout << "g2cnt=" << currg2cnt << endl;
	cout << "g2table======================" << endl;
	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			int number = g2table[x][y];
			if (y == 1){ cout << "                    " << number; }
			else{
				cout << number;
			}
			if ((y == 3) || (y == 6)){ cout << " "; }
		}
		if ((x == 3) || (x == 6)){ cout << endl; }
cout << endl;
	}
	cout << endl;
	cout << "b2table======================" << endl;
	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			int number = b2table[x][y];
			if (y == 1){ cout << "                    " << number; }
			else{
				cout << number;
			}
			if ((y == 3) || (y == 6)){ cout << " "; }
		}
		if ((x == 3) || (x == 6)){ cout << endl; }
		cout << endl;
	}
	cout << endl;
	return;
}
//==========================================================
void insbtable(int glindex){
	//==========================================================
	int r, c, v;
	r = glist[glindex].r;
	c = glist[glindex].c;
	v = glist[glindex].v;
	if (btable[r][c] == 0){
		btable[r][c] = v;
	}

	return;
}
//==========================================================
void creategtable(){
	//==========================================================
	top = 0;
	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			gtable[x][y] = 0;
			btable[x][y] = 0;
			g2table[x][y] = 0;

		}
	}
	return;
}

//==========================================================
void cleargtable(){
	//==========================================================

	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			gtable[x][y] = 0;
		}
	}
	top = 0;
	return;
}
//==========================================================
void clearg2table(){
	//==========================================================

	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			g2table[x][y] = 0;
		}
	}
	currg2cnt = 0;
	return;
}
//==========================================================
void clearbtable(){
	//==========================================================

	for (int x = 1; x <= rmax - 1; ++x) {
		for (int y = 1; y <= cmax - 1; ++y){
			btable[x][y] = 0;
		}
	}
	top = 0;
	return;
}
//====================================================================================
void printglist(){
	for (int i = 1; i <= top; i++){
		cout << "glist[" << i << "].r=" << glist[i].r << endl;
		cout << "glist[" << i << "].c=" << glist[i].c << endl;
		cout << "glist[" << i << "].v=" << glist[i].v << endl;
		cout << "glist[" << i << "].zcnt=" << glist[i].zcnt << endl;
		cout << "=============" << endl;

	}
	return;
}
 
//=======================================================================================
bool findinbadlist(int r, int c, int v){
	bool found = true;
	bool notfound = false;
	for (int i = 1; i <= blptr; i++){
		if ((r == badlist[i].r) && (c == badlist[i].c) && (v == badlist[i].v)){ return found; }
	}
	return notfound;
}
 
 
//==========================================================================================
//==================================================================================================
void delArow(int listptr){
	if (listptr == 0){

		if (debug){
			cout << "BAD LISTPTR" << endl;
		}
		exit(0);
	}
	int r = Arow[listptr].r;
	int c = Arow[listptr].c;
	int v = Arow[listptr].v;
	Arow[listptr].r = 0;
	Arow[listptr].c = 0;
	Arow[listptr].v = 0;
	while (listptr < ptrArow){
			Arow[listptr].r = Arow[listptr + 1].r;
			Arow[listptr].c = Arow[listptr + 1].c;
			Arow[listptr].v = Arow[listptr + 1].v;
			listptr++;
	}
	if (ptrArow > 0){ ptrArow--; }


	return;
}
//===========================================================================================
void delBrow(int listptr){
	int r = Brow[listptr].r;
	int c = Brow[listptr].c;
	int v = Brow[listptr].v;
	Brow[listptr].r = 0;
	Brow[listptr].c = 0;
	Brow[listptr].v = 0;
	if (listptr < ptrBrow){
		Brow[listptr].r = Brow[listptr + 1].r;
		Brow[listptr].c = Brow[listptr + 1].c;
		Brow[listptr].v = Brow[listptr + 1].v;
	}
	if (ptrBrow > 0){ ptrBrow--; }
	return;
}
//==================================================================================================
void delAcol(int listptr){
	int r = Acol[listptr].r;
	int c = Acol[listptr].c;
	int v = Acol[listptr].v;
	Acol[listptr].r = 0;
	Acol[listptr].c = 0;
	Acol[listptr].v = 0;
	if (listptr < ptrAcol){
		Acol[listptr].r = Acol[listptr + 1].r;
		Acol[listptr].c = Acol[listptr + 1].c;
		Acol[listptr].v = Acol[listptr + 1].v;
	}
	if (ptrAcol > 0){ ptrAcol--; }
	return;
}
//===========================================================================================
void delBcol(int listptr){
	int r = Bcol[listptr].r;
	int c = Bcol[listptr].c;
	int v = Bcol[listptr].v;
	Bcol[listptr].r = 0;
	Bcol[listptr].c = 0;
	Bcol[listptr].v = 0;
	if (listptr < ptrBcol){
		Bcol[listptr].r = Bcol[listptr + 1].r;
		Bcol[listptr].c = Bcol[listptr + 1].c;
		Bcol[listptr].v = Bcol[listptr + 1].v;
	}
	if (ptrBcol > 0){ ptrBcol--; }
	return;
}
 
//========================================================== 
int  insgtable(int r, int c, int v, int AorB, int tgptr, int lasttried){
	thisisaguess = false;
	guesscount++;
	int res = findinglist(r, c, v);
	if (res > 0){
		glist[res].AorB = AorB;
		glist[res].gptr = tgptr;
		glist[res].lasttried = lasttried;
		glist[res].zcnt = zcnt;

		gtable[r][c] = v;
		return 0;
	}
	++top;
	glist[top].r = r;
	glist[top].c = c;
	glist[top].v = v;
	glist[top].AorB = AorB;
	glist[top].gptr = tgptr;
	glist[top].lasttried = lasttried;
	glist[top].zcnt = zcnt;
	gtable[r][c] = v;

	return 0;
}
  //===========================================================================
int findinglist(int r, int c, int v){

	for (int i = 1; i <= top; i++){
		if ((glist[i].r == r) && (glist[i].c == c) && (glist[i].v == v)){
			glist[i].zcnt = zcnt;
			return i;
		}
	}
	return 0;
}
 //==========================================================
//========================================================== 
//========================================================== 
int eliminateinbox(int b){
//==========================================================
	//  //cout<<"in function eliminateinbox"<<endl;
 
//	box[b].bcnt = 0;
//	readbox(b);
	int result = 0;
	int m1 = 0; int m2 = 0; int m3 = 0;
	int r = 0; int c = 0;
//	box[b].bcnt = 0;
//	readbox(b);
//
	int mcount = gminbox(b, m1, m2, m3);

	int firstbl = gfb(zbox, b);
	int currentbl = firstbl;
	int nextbl = gnb(zbox, b, currentbl);
	if (mcount <= 1) { return 0; }
	if (mcount >2){ return 0; }
//	if (mcount == 1){ glastwrite = "2423"; result = insert_m(zbox, b); if (result>0){ return result; } else { return 0; } }
	if (mcount == 1){ result = checkcnt(zbox, b); return result; }


	int m1resrow = finrow(firstbl, m1);
	int m1rescol = fincol(firstbl, m1);
	int m1resb2row = finrow(nextbl, m1);
	int m1resb2col = fincol(nextbl, m1);

	int m2resrow = finrow(firstbl, m2);
	int m2rescol = fincol(firstbl, m2);
	int m2resb2row = finrow(nextbl, m2);
	int m2resb2col = fincol(nextbl, m2);

	if ((m1resrow >0) && (m1rescol>0)){
		if ((m1resb2row == 0) && (m1resb2col == 0)){
			c = gcolfromboxandpos(b, firstbl);
			r = growfromboxandpos(b, firstbl);
			if (puzzle[r][c] != 0){ return 0; }
			result = fincol(c, m2);
			if (result>0){
				c = gcolfromboxandpos(b, nextbl);
				r = growfromboxandpos(b, nextbl);

				glastwrite = "2449         "; result = inspuzzle(r, c, m2);
			}
			else{
			}
		}
	}
	else{
		if ((m2resrow >0) && (m2rescol>0)){
			if ((m2resb2row == 0) && (m2resb2col == 0)){
				c = gcolfromboxandpos(b, nextbl);
				r = growfromboxandpos(b, nextbl);
				result = finbox(b, m2);
				if (result>0) {
					c = gcolfromboxandpos(b, nextbl);
					r = growfromboxandpos(b, nextbl);
					glastwrite = "2464         "; result = inspuzzle(r, c, m2);
				}
			}
		}
	}
	if (result>0){ ; }

	return result;
}
//==========================================================
//end eliminateinbox
//==========================================================   
//==========================================================                 
int gallblsinbox(int b, int &b1, int &b2, int &b3, int &b4, int &b5, int &b6, int &b7, int &b8, int &b9){
	//==========================================================                 
	//Captures value of m numbers in box r .  The numbers are returned in                    
	//ascending order. Result contains the count of m numbers.                               
	//All m numbers are returned;                                                        
	//==========================================================                 
	//  r      = box                                                                               
	//  result = mnumber count                                                               
	//  &b1,&b2,&b3..&b9  =  values of m numbers.                                           
	//==========================================================                  
	int result = 0;
	//==========================================================                  
	string error = "error in parameters -function gallblsinbox";
	//==========================================================                                                                                                                
	b1 = 0;  b4 = 0;  b7 = 0;
	b2 = 0;  b5 = 0;  b8 = 0;
	b3 = 0;  b6 = 0;  b9 = 0;

	int i = 1;
	//if ((b<=0)||(b>9)){//cout<<error<<endl;}                                                              
	while (i <= 9){
		if (box[b].val[i] == 0){
			++result;
			if (b1 == 0){ b1 = i; }
			else{
				if (b2 == 0){ b2 = i; }
				else{
					if (b3 == 0){ b3 = i; }
					else{
						if (b4 == 0){ b4 = i; }
						else{
							if (b5 == 0){ b5 = i; }
							else{
								if (b6 == 0){ b6 = i; }
								else{
									if (b7 == 0){ b7 = i; }
									else{
										if (b8 == 0){ b8 = i; }
										else{
											if (b9 == 0){ b9 = i; break; }
										}
									}
								}
							}
						}
					}
				}
			}
		}
		++i;
	}
	return result;
}
//==========================================================                 
//end function gallblsinbox                                                                 
//==========================================================       

//==========================================================
int box3elimcol(int b){
	//==========================================================

	 
//	box[b].bcnt = 0;
//	readbox(b);
	if (box[b].bcnt != 3){ return 0; }

	int result = 0;
	//  //cout<<"in function box3elimcol: box="<<b<<endl;                                                                                                                                                                                
	int res = 0;
	int mcount = 0;
	int bcount = 0;
	if (b == 0){ return 0; }
	if (box[b].bcnt<2){ return 0; }
	if (box[b].bcnt != 3){ return 0; }
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);

	if ((mcount != 3) || (bcount != 3)){ return 0; }
	if (mcount == 0){ return 0; }
	int r1 = growfromboxandpos(b, b1);
	int c1 = gcolfromboxandpos(b, b1);
	int foundm1 = 0;
	int foundm2 = 0;
	int foundm3 = 0;
	int r2 = growfromboxandpos(b, b2);
	int c2 = gcolfromboxandpos(b, b2);
	int r3 = growfromboxandpos(b, b3);
	int c3 = gcolfromboxandpos(b, b3);

	// 1  2  3
	// 4  5  6
	// 7  8  9

	//looking for bl pairs (1,4) or (1,7) or (4,7)
	// or                     (2,5) or (2,8) or (5,8)
	// or                     (3,6) or (3,9) or (6,9)


	if (((b1 == 1) && (b2 == 4)) || ((b1 == 1) && (b3 == 7)) || ((b2 == 4) && (b3 == 7))){
		res = fincol(c1, m1);
		if (res >0){ foundm1 = 1; }
		res = fincol(c1, m2);
		if (res >0){ foundm2 = 1; }
		res = fincol(c1, m3);
		if (res >0){ foundm3 = 1; }
		if ((foundm1) && (foundm3)){ glastwrite = "2593"; result = inspuzzle(r1, c1, m2); }
		else{
			if ((foundm1) && (foundm2)){ glastwrite = "2595"; result = inspuzzle(r1, c1, m3); }
			else{
				if ((foundm2) && (foundm3)){ glastwrite = "2597"; result = inspuzzle(r1, c1, m1); }
			}
		}
	}
	else{
		if (((b1 == 2) && (b2 == 5)) || ((b2 == 2) && (b3 == 8)) || ((b1 == 5) && (b3 == 8))){

			res = fincol(c2, m1);
			if (res >0){ foundm1 = 1; }
			res = fincol(c2, m2);
			if (res >0){ foundm2 = 1; }
			res = fincol(c2, m3);
			if (res >0){ foundm3 = 1; }
			if ((foundm1) && (foundm3)){ glastwrite = "2613         "; result = inspuzzle(r2, c2, m2); }
			else{
				if ((foundm1) && (foundm2)){ glastwrite = "2615         "; result = inspuzzle(r2, c2, m3); }
				else{
					if ((foundm2) && (foundm3)){ glastwrite = "1617         "; result = inspuzzle(r2, c2, m1); }
				}
			}
		}
		else{
			if (((b1 == 3) && (b2 == 6)) || ((b2 == 3) && (b3 == 9)) || ((b1 == 6) && (b3 == 9))){
				res = fincol(c3, m1);
				if (res >0){ foundm1 = 1; }
				res = fincol(c3, m2);
				if (res >0){ foundm2 = 1; }
				res = fincol(c3, m3);
				if (res >0){ foundm3 = 1; }
				if ((foundm1) && (foundm3)){ glastwrite = "2631         "; result = inspuzzle(r3, c3, m2); }
				else{
					if ((foundm1) && (foundm2)){ glastwrite = "2633         "; result = inspuzzle(r3, c3, m3); }
					else{
						if ((foundm2) && (foundm3)){ glastwrite = "2635         "; result = inspuzzle(r3, c3, m1); }
					}
				}
			}
		}
	}



	if (result>0){ ; return result; }

	return 0;
}
//==========================================================
//end function box3elimcol 
//==========================================================      
//==========================================================              
//==========================================================
int box3elimrow(int b){
	//==========================================================
 
//	box[b].bcnt = 0;
//	readbox(b);
	if (box[b].bcnt != 3){ return 0; }
	int res = 0;
	int result = 0;
	int row1 = 0; int row2 = 0; int row3 = 0;
	//  //cout<<"in function box3elimrow: box="<<b<<endl;                                                                                                                                                                                

	int mcount = 0;
	int bcount = 0;
	if (b == 0){ return 0; }
	if (box[b].bcnt<2){ return 0; }
	if (box[b].bcnt != 3){ return 0; }
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	if (mcount == 0){ return 0; }
	if ((mcount != 3) || (bcount != 3)){ return 0; }

	int r1 = growfromboxandpos(b, b1);
	int c1 = gcolfromboxandpos(b, b1);
	int foundm1 = 0;
	int foundm2 = 0;
	int foundm3 = 0;
	int r2 = growfromboxandpos(b, b2);
	int c2 = gcolfromboxandpos(b, b2);
	int r3 = growfromboxandpos(b, b3);
	int c3 = gcolfromboxandpos(b, b3);

	// 1  2  3
	// 4  5  6
	// 7  8  9

	//looking for bl pairs (1,2) or (1,3) or (2,3)
	// or                     (4,5) or (5,6) or (4,6)
	// or                     (7,8) or (8,9) or (7,9)


	if (((b1 == 1) && (b2 == 2)) || ((b1 == 1) && (b3 == 3)) || ((b2 == 2) && (b3 == 3))){
		res = finrow(r1, m1);
		if (res >0){ foundm1 = 1; }
		res = finrow(r1, m2);
		if (res >0){ foundm2 = 1; }
		res = finrow(r1, m3);
		if (res >0){ foundm3 = 1; }
		if ((foundm1) && (foundm3)){ glastwrite = "2712        "; result = inspuzzle(r1, c1, m2); }
		else{
			if ((foundm1) && (foundm2)){ glastwrite = "2714         "; result = inspuzzle(r1, c1, m3); }
			else{
				if ((foundm2) && (foundm3)){ glastwrite = "2716         "; result = inspuzzle(r1, c1, m1); }
			}
		}

		row1 = 1;
	}
	else{
		if (((b1 == 4) && (b2 == 5)) || ((b2 == 5) && (b3 == 6)) || ((b1 == 4) && (b3 == 6))){
			row2 = 1;
			res = finrow(r2, m1);
			if (res >0){ foundm1 = 1; }
			res = finrow(r2, m2);
			if (res >0){ foundm2 = 1; }
			res = finrow(r2, m3);
			if (res >0){ foundm3 = 1; }
			if ((foundm1) && (foundm3)){ glastwrite = "2732"; result = inspuzzle(r2, c2, m2); }
			else{
				if ((foundm1) && (foundm2)){ glastwrite = "2734"; result = inspuzzle(r2, c2, m3); }
				else{
					if ((foundm2) && (foundm3)){ glastwrite = "2736"; result = inspuzzle(r2, c2, m1); }
				}
			}

		}
		else{
			if (((b1 == 7) && (b2 == 8)) || ((b2 == 8) && (b3 == 9)) || ((b1 == 7) && (b3 == 9))){
				res = finrow(r3, m1);
				if (res >0){ foundm1 = 1; }
				res = finrow(r3, m2);
				if (res >0){ foundm2 = 1; }
				res = finrow(r3, m3);
				if (res >0){ foundm3 = 1; }
				if ((foundm1) && (foundm3)){ glastwrite = "2750"; result = inspuzzle(r3, c2, m2); }
				else{
					if ((foundm1) && (foundm2)){ glastwrite = "2752"; result = inspuzzle(r3, c2, m3); }
					else{
						if ((foundm2) && (foundm3)){ glastwrite = "2754"; result = inspuzzle(r3, c2, m1); }
					}
				}
				row3 = 1;
			}
		}
	}
	if (result>0){ ; }
	return result;
}
//==========================================================
//end function box3elimrow 
//==========================================================            

//==========================================================
int box2elimrow(int b){
	//==========================================================
	if (box[b].bcnt != 2){
		return 0;
	}

	int res = 0;
	int result = 0;
	int row1 = 0; int row2 = 0; int row3 = 0;


	int mcount = 0;
	int bcount = 0;
	if (b == 0){ return 0; }
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);

	if (mcount != 2){ return 0; }

	int r1 = growfromboxandpos(b, b1);
	int c1 = gcolfromboxandpos(b, b1);

	int r2 = growfromboxandpos(b, b2);
	int c2 = gcolfromboxandpos(b, b2);
	if (r1 != r2){ return 0; }
	int resultm1b1 = fincol(c1, m1);
	int resultm1b2 = fincol(c2, m1);

	int resultm2b1 = fincol(c1, m2);

	int resultm2b2 = fincol(c2, m2);

	if (resultm1b1>0){
		glastwrite = "2821"; result = inspuzzle(r1, c1, m2);
		;
		return result;
	}
	if (resultm1b2>0){
		glastwrite = "2828"; result = inspuzzle(r1, c1, m1);
		;
		return result;
	}
	if (resultm2b1>0){
		glastwrite = "2834"; result = inspuzzle(r1, c1, m1);
		;
		return result;
	}
	if (resultm2b2>0){
		glastwrite = "2840"; result = inspuzzle(r2, c2, m1);
		;
		return result;
	}

	return 0;
}
//==========================================================
//end function box2elimrow 
//==========================================================            

//==========================================================   
//==========================================================                 
int gallblsincol(int c, int &b1, int &b2, int &b3, int &b4, int &b5, int &b6, int &b7, int &b8, int &b9){
	//==========================================================                 
	//Captures value of m numbers in box r .  The numbers are returned in                    
	//ascending order. Result contains the count of m numbers.                               
	//All m numbers are returned;                                                        
	//==========================================================                 
	//  c      = col                                                                               
	//  result = mnumber count                                                               
	//  &b1,&b2,&b3..&b9  =  values of m numbers.                                           
	//==========================================================                  
	int result = 0;
	//==========================================================                  
	string error = "error in parameters -function gallblsinbox";
	//==========================================================                                                                                                                
	b1 = 0;  b4 = 0;  b7 = 0;
	b2 = 0;  b5 = 0;  b8 = 0;
	b3 = 0;  b6 = 0;  b9 = 0;

	int i = 1;
	// if ((c<=0)||(c>9)){//cout<<error<<endl;}                                                              
	while (i <= 9){
		if (col[c].row[i] == 0){
			++result;
			if (b1 == 0){ b1 = i; }
			else{
				if (b2 == 0){ b2 = i; }
				else{
					if (b3 == 0){ b3 = i; }
					else{
						if (b4 == 0){ b4 = i; }
						else{
							if (b5 == 0){ b5 = i; }
							else{
								if (b6 == 0){ b6 = i; }
								else{
									if (b7 == 0){ b7 = i; }
									else{
										if (b8 == 0){ b8 = i; }
										else{
											if (b9 == 0){ b9 = i; break; }
										}
									}
								}
							}
						}
					}
				}
			}
		}
		++i;
	}
	return result;
}
//==========================================================                 
//end function gallblsincol                                                                
//==========================================================  
//==========================================================   

//==========================================================    
int moreboxprocing(int b){
	//==========================================================
	//	readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
	return 0;
	//**********************************************************************error************************************
	if (box[b].done == true){ box[b].bcnt = 0; return 0; }
	if (box[b].bcnt == 0){ box[b].done = true; return 0; }

	int result = 0;
	int boxrow3 = 0;
	int bm1 = 0; int bm2 = 0; int bm3 = 0;
	int rm1 = 0; int rm2 = 0; int rm3 = 0;
	int insertpoint = 0;
	int bcount = 0;
	int rcount = 0;
	int firstbl = 0; int lastbl = 0;

	int nextbl = 0; int prevbl = 0; int boxcol1 = 0; int boxcol3 = 0;
	//  //cout <<"in function moreboxprocing"<<endl;


	if (box[b].bcnt>6){ return 0; }
	if ((box[b].r1done == true) && (box[b].r2done == true)){
		if (box[b].r3done == false){
			int boxrow3 = growfromboxandpos(b, 7);
			if (row[boxrow3].bcnt == box[b].bcnt + 1){
				rcount = gminrow(boxrow3, rm1, rm2, rm3);
				bcount = gminbox(b, bm1, bm2, bm3);

				boxcol1 = gcolfromboxandpos(b, 7);
				boxcol3 = boxcol1 + 2;
				prevbl = gprevbl(zrow, boxrow3, boxcol1);
				if (prevbl>0){ insertpoint = prevbl; }
				else{
					int nextbl = gnb(zrow, boxrow3, boxcol3);
					if (nextbl>0){ insertpoint = nextbl; }
				}
				if (insertpoint == 0){ return 0; }
				if ((rm1 != bm1) && (rm1 != bm2)){ glastwrite = "2952"; result = inspuzzle(boxrow3, insertpoint, rm1); return result; }
				else{
					if ((rm2 != bm1) && (rm2 != bm2)){ glastwrite = "2954"; result = inspuzzle(boxrow3, insertpoint, rm2); return result; }
					else{
						if ((rm3 != bm1) && (rm3 != bm2)){ glastwrite = "2956"; result = inspuzzle(boxrow3, insertpoint, rm3); return result; }
					}
				}
			}
		}
	}
	if (box[b].bcnt>6){ return 0; }
	if ((box[b].r1done == true) && (box[b].r3done == true)){
		if (box[b].r2done == false){
			int boxrow2 = growfromboxandpos(b, 4);
			if (row[boxrow2].bcnt == box[b].bcnt + 1){
				rcount = gminrow(boxrow2, rm1, rm2, rm3);
				bcount = gminbox(b, bm1, bm2, bm3);
				boxcol1 = gcolfromboxandpos(b, 4);
				boxcol3 = boxcol1 + 2;
				insertpoint = 0;
				prevbl = gprevbl(zrow, boxrow2, boxcol1);
				if (prevbl>0){ insertpoint = prevbl; }
				else{
					int nextbl = gnb(zrow, boxrow2, boxcol3);
					if (nextbl>0){ insertpoint = nextbl; }
				}
				if (insertpoint == 0){ return 0; }



				if ((rm1 != bm1) && (rm1 != bm2)){ glastwrite = "2984"; result = inspuzzle(boxrow2, insertpoint, rm1); return result; }
				else{
					if ((rm2 != bm1) && (rm2 != bm2)){ glastwrite = "2986"; result = inspuzzle(boxrow2, insertpoint, rm2); return result; }
					else{
						if ((rm3 != bm1) && (rm3 != bm2)){ glastwrite = "2988"; result = inspuzzle(boxrow2, insertpoint, rm3); return result; }
					}
				}
			}
		}
	}
	return result;
}

//==========================================================
//end moreboxprocing
//==========================================================  
//========================================================== 
int box5elim(int b){
//==========================================================

	int result = 0;
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	int mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	if (mcount == 0){ box[b].done = true; return 0; }

	if (mcount>5){ return 0; }
	int m1rowresb1 = 0; int m1rowresb2 = 0; int m1rowresb3 = 0; int m1rowresb4 = 0; int m1rowresb5 = 0;
	int m1colresb1 = 0; int m1colresb2 = 0; int m1colresb3 = 0; int m1colresb4 = 0; int m1colresb5 = 0;

	int m2rowresb1 = 0; int m2rowresb2 = 0; int m2rowresb3 = 0; int m2rowresb4 = 0; int m2rowresb5 = 0;
	int m2colresb1 = 0; int m2colresb2 = 0; int m2colresb3 = 0; int m2colresb4 = 0; int m2colresb5 = 0;

	int m3rowresb1 = 0; int m3rowresb2 = 0; int m3rowresb3 = 0; int m3rowresb4 = 0; int m3rowresb5 = 0;
	int m3colresb1 = 0; int m3colresb2 = 0; int m3colresb3 = 0; int m3colresb4 = 0; int m3colresb5 = 0;

	int m4rowresb1 = 0; int m4rowresb2 = 0; int m4rowresb3 = 0; int m4rowresb4 = 0; int m4rowresb5 = 0;
	int m4colresb1 = 0; int m4colresb2 = 0; int m4colresb3 = 0; int m4colresb4 = 0; int m4colresb5 = 0;

	int m5rowresb1 = 0; int m5rowresb2 = 0; int m5rowresb3 = 0; int m5rowresb4 = 0; int m5rowresb5 = 0;
	int m5colresb1 = 0; int m5colresb2 = 0; int m5colresb3 = 0; int m5colresb4 = 0; int m5colresb5 = 0;


	int b1row = 0; int b2row = 0; int b3row = 0; int b4row = 0; int b5row = 0;
	int b1col = 0; int b2col = 0; int b3col = 0; int b4col = 0; int b5col = 0;

	int m1restotal = 0; int m2restotal = 0; int m3restotal = 0; int m4restotal = 0; int m5restotal = 0;

	int m1r = 0; int m1c = 0;   int m2r = 0; int m2c = 0;  int m3r = 0; int m3c = 0; int m4r = 0; int m4c = 0; int m5r = 0; int m5c = 0;


	b1row = growfromboxandpos(b, b1);
	if (b1row <= 0) { return 0; }

	if (mcount>1){ b2row = growfromboxandpos(b, b2); }
	if (mcount>2){ b3row = growfromboxandpos(b, b3); }
	if (mcount>3){ b4row = growfromboxandpos(b, b4); }
	if (mcount>4){ b5row = growfromboxandpos(b, b5); }

	b1col = gcolfromboxandpos(b, b1);
	if (b1col <= 0) { return 0; }

	if (mcount>1){ b2col = gcolfromboxandpos(b, b2); }
	if (mcount>2){ b3col = gcolfromboxandpos(b, b3); }
	if (mcount>3){ b4col = gcolfromboxandpos(b, b4); }
	if (mcount>4){ b5col = gcolfromboxandpos(b, b5); }

	if (mcount == 1){

		// return 1;

		glastwrite = "3060"; result = inspuzzle(b1row, b1col, m1); return result;
	}

	//**********************************************************
	//          m1 procing
	//**********************************************************
	if (mcount == 0){ return 0; }
	m1rowresb1 = finrow(b1row, m1);
	m1colresb1 = fincol(b1col, m1);
	int elimcount = 0;
	m1restotal = 0;
	int targrow = 0; int targcol = 0;
	m1r = 0; m1c = 0;
	if ((m1rowresb1 == 0) && (m1colresb1 == 0)){ ++m1restotal; m1r = b1row; m1c = b1col; }
	if ((m1rowresb1>0) || (m1colresb1>0)){ ++elimcount; m1c = 0; m1r = 0; }
	m1rowresb2 = finrow(b2row, m1);
	m1colresb2 = fincol(b2col, m1);

	if ((m1rowresb2 == 0) && (m1colresb2 == 0)){ ++m1restotal; m1r = b2row; m1c = b2col; }
	if ((m1rowresb2>0) || (m1colresb2>0)){ ++elimcount; m1c = 0; m1r = 0; }
	if (mcount>2){
		m1rowresb3 = finrow(b3row, m1);
		m1colresb3 = fincol(b3col, m1);
		if ((m1rowresb3 == 0) && (m1colresb3 == 0)){ ++m1restotal; m1r = b3row; m1c = b3col; }
		if ((m1rowresb3>0) || (m1colresb3>0)){ ++elimcount; m1c = 0; m1r = 0; }

	}
	if (mcount>3){
		m1rowresb4 = finrow(b4row, m1);
		m1colresb4 = fincol(b4col, m1);
		if ((m1rowresb4 == 0) && (m1colresb4 == 0)){ ++m1restotal; m1r = b4row; m1c = b4col; }
		if ((m1rowresb4>0) || (m1colresb4>0)){ ++elimcount; m1c = 0; m1r = 0; }
	}
	if (mcount>4){
		m1rowresb5 = finrow(b5row, m1);
		m1colresb5 = fincol(b5col, m1);
		if ((m1rowresb5 == 0) && (m1colresb5 == 0)){ ++m1restotal; m1r = b5row; m1c = b5col; }
		if ((m1rowresb5>0) || (m1colresb5>0)){ ++elimcount; m1c = 0; m1r = 0; }
	}




	if ((m1restotal == 1) && (elimcount = mcount - 1)){
		if ((m1r>0) && (m1c>0) && (m1>0)){
			glastwrite = "3106"; result = inspuzzle(m1r, m1c, m1); return result;
		}
	}
	//*******************************************************
	//end m1procing
	//*******************************************************	

	//*******************************************************
	//          m2 procing
	//*******************************************************
	if (mcount<2){ return 0; }
	m2restotal = 0;
	m2rowresb1 = finrow(b1row, m2);
	m2colresb1 = fincol(b1col, m2);

	if ((m2rowresb1 == 0) && (m2colresb1 == 0)){ ++m2restotal; m2r = b1row; m2c = b1col; }

	if (mcount>1){
		m2rowresb2 = finrow(b2row, m2);
		m2colresb2 = fincol(b2col, m2);
		if ((m2rowresb2 == 0) && (m2colresb2 == 0)){ ++m2restotal; m2r = b2row; m2c = b2col; }
	}
	if (mcount>2){
		m2rowresb3 = finrow(b3row, m2);
		m2colresb3 = fincol(b3col, m2);
		if ((m2rowresb3 == 0) && (m2colresb3 == 0)){ ++m2restotal; m2r = b3row; m2c = b3col; }
	}
	if (mcount>3){
		m2rowresb4 = finrow(b4row, m2);
		m2colresb4 = fincol(b4col, m2);
		if ((m2rowresb4 == 0) && (m2colresb4 == 0)){ ++m2restotal; m2r = b4row; m2c = b4col; }
	}
	if (mcount>4){
		m2rowresb5 = finrow(b5row, m2);
		m2colresb5 = fincol(b5col, m2);
		if ((m2rowresb5 == 0) && (m2colresb5 == 0)){ ++m2restotal; m2r = b5row; m2c = b5col; }
	}
	if (mcount == 2){
		//was && not ||                   
		if ((m2rowresb2>0) || (m2colresb2>0)){

			glastwrite = "3147"; result = inspuzzle(b2row, b2col, m1);
			
			glastwrite = "3148"; result = inspuzzle(b1row, b1col, m2);

			return result;
		}
	}
	if ((m2restotal == 1) && (m2r>0) && (m2c>0)&(m2>0)){
		glastwrite = "3155"; result = inspuzzle(m2r, m2c, m2);  return result;
	}


	//*******************************************************
	//end m2procing
	//*******************************************************	
	//*******************************************************
	//          m3 procing
	//*******************************************************

	if (mcount <3) { return 0; }
	m3restotal = 0;
	m3rowresb1 = finrow(b1row, m3);
	m3colresb1 = fincol(b1col, m3);

	if ((m3rowresb1 == 0) && (m3colresb1 == 0)){ ++m3restotal; m3r = b1row; m3c = b1col; }


	m3rowresb2 = finrow(b2row, m3);
	m3colresb2 = fincol(b2col, m3);

	if ((m3rowresb2 == 0) && (m3colresb2 == 0)){ ++m3restotal; m3r = b2row; m3c = b2col; }

	m3rowresb3 = finrow(b3row, m3);
	m3colresb3 = fincol(b3col, m3);

	if ((m3rowresb3 == 0) && (m3colresb3 == 0)){ ++m3restotal; m3r = b3row; m3c = b3col; }

	if (mcount>3){
		m3rowresb4 = finrow(b4row, m3);
		m3colresb4 = fincol(b4col, m3);
		if ((m3rowresb4 == 0) && (m3colresb4 == 0)){ ++m3restotal; m3r = b4row; m3c = b4col; }
	}
	if (mcount>4){
		m3rowresb5 = finrow(b5row, m3);
		m3colresb5 = fincol(b5col, m3);
		if ((m3rowresb5 == 0) && (m3colresb5 == 0)){ ++m3restotal; m3r = b5row; m3c = b5col; }
	}
	if ((m3restotal == 1) && (m3r>0) && (m3c>0) && (m3>0)){
	glastwrite = "3195         "; result = inspuzzle(m3r, m3c, m3);  return result;
	}


	//*******************************************************
	//end m3procing
	//*******************************************************	      
	//*******************************************************
	//          m4 procing
	//*******************************************************

	if (mcount<4) { return 0; }
	m4restotal = 0;
	m4rowresb1 = finrow(b1row, m4);
	m4colresb1 = fincol(b1col, m4);

	if ((m4rowresb1 == 0) && (m4colresb1 == 0)){ ++m4restotal; m4r = b1row; m4c = b1col; }


	m4rowresb2 = finrow(b2row, m4);
	m4colresb2 = fincol(b2col, m4);

	if ((m4rowresb2 == 0) && (m4colresb2 == 0)){ ++m4restotal; m4r = b2row; m4c = b2col; }

	m4rowresb3 = finrow(b3row, m4);
	m4colresb3 = fincol(b3col, m4);

	if ((m4rowresb3 == 0) && (m4colresb3 == 0)){ ++m4restotal; m4r = b3row; m4c = b3col; }


	m4rowresb4 = finrow(b4row, m4);
	m4colresb4 = fincol(b4col, m4);

	if ((m4rowresb4 == 0) && (m4colresb4 == 0)){ ++m4restotal; m4r = b4row; m4c = b4col; }

	if (mcount>4){
		m4rowresb5 = finrow(b5row, m4);
		m4colresb5 = fincol(b5col, m4);
		if ((m4rowresb5 == 0) && (m4colresb5 == 0)){ ++m4restotal; m4r = b5row; m4c = b5col; }
	}

	if ((m4restotal == 1) && (m4r>0) && (m4c>0)){
		glastwrite = "3237         "; result = inspuzzle(m4r, m4c, m4);   return result;
	}


	//*******************************************************
	//end m4procing
	//*******************************************************	   
	//*******************************************************
	//          m5 procing
	//*******************************************************
	if (mcount < 5){ return 0; }
	m5restotal = 0;
	m5rowresb1 = finrow(b1row, m5);
	m5colresb1 = fincol(b1col, m5);

	if ((m5rowresb1 == 0) && (m5colresb1 == 0)){ ++m5restotal; m5r = b1row; m5c = b1col; }


	m5rowresb2 = finrow(b2row, m5);
	m5colresb2 = fincol(b2col, m5);

	if ((m5rowresb2 == 0) && (m5colresb2 == 0)){ ++m5restotal; m5r = b2row; m5c = b2col; }

	m5rowresb3 = finrow(b3row, m5);
	m5colresb3 = fincol(b3col, m5);

	if ((m5rowresb3 == 0) && (m5colresb3 == 0)){ ++m5restotal; m5r = b3row; m5c = b3col; }


	m5rowresb4 = finrow(b4row, m5);
	m5colresb4 = fincol(b4col, m5);

	if ((m5rowresb4 == 0) && (m5colresb4 == 0)){ ++m5restotal; m5r = b4row; m5c = b4col; }


	m5rowresb5 = finrow(b5row, m5);
	m5colresb5 = fincol(b5col, m5);

	if ((m5rowresb5 == 0) && (m5colresb5 == 0)){ ++m5restotal; m5r = b5row; m5c = b5col; }


	if ((m5restotal == 1) && (m5r>0)&(m5c>0)){
		glastwrite = "3279         "; result = inspuzzle(m5r, m5c, m5); return result;
	}
	//*******************************************************
	//end m5procing
	//*******************************************************	   
	return 0;
}
//==========================================================
//end box5elim
//==========================================================   

//========================================================== 
int row5elim(int r){
	//==========================================================
	//  //cout <<"in function row5elim r="<<r<<endl;
	//readpuzzle();
	int result = 0;
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;

	int mcount = gallminrow(r, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int bcount = gallblsinrow(r, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	if (mcount == 0){ return 0; }

	if (mcount>5){ return 0; }


	int m1colresb1 = 0; int m1colresb2 = 0; int m1colresb3 = 0; int m1colresb4 = 0; int m1colresb5 = 0;
	int m2colresb1 = 0; int m2colresb2 = 0; int m2colresb3 = 0; int m2colresb4 = 0; int m2colresb5 = 0;
	int m3colresb1 = 0; int m3colresb2 = 0; int m3colresb3 = 0; int m3colresb4 = 0; int m3colresb5 = 0;
	int m4colresb1 = 0; int m4colresb2 = 0; int m4colresb3 = 0; int m4colresb4 = 0; int m4colresb5 = 0;
	int m5colresb1 = 0; int m5colresb2 = 0; int m5colresb3 = 0; int m5colresb4 = 0; int m5colresb5 = 0;

	int b1col = 0; int b2col = 0; int b3col = 0; int b4col = 0; int b5col = 0;
	int m1restotal = 0; int m2restotal = 0; int m3restotal = 0; int m4restotal = 0; int m5restotal = 0;
	int m1c = 0;    int m2c = 0;   int m3c = 0;   int m4c = 0;  int m5c = 0;

	//**********************************************************
	//          m1 procing
	//**********************************************************
	if (mcount == 0){ return 0; }
	if (mcount == 1){
		
		int res=checkcnt(zrow, r);
		return res;
	}
	m1colresb1 = fincol(b1, m1);
	if (m1colresb1 == 0){ ++m1restotal; m1c = b1; }

	m1colresb2 = fincol(b2, m1);
	if (m1colresb2 == 0){ ++m1restotal; m1c = b2; }
	if (mcount>2){
		m1colresb3 = fincol(b3, m1);
		if (m1colresb3 == 0){ ++m1restotal; m1c = b3; }
	}
	if (mcount>3){
		m1colresb4 = fincol(b4, m1);
		if (m1colresb4 == 0){ ++m1restotal; m1c = b4; }
	}
	if (mcount>4){
		m1colresb5 = fincol(b5, m1);
		if (m1colresb5 == 0){ ++m1restotal; m1c = b5; }
	}
	if (m1restotal == 1){
		glastwrite = "3342"; result = inspuzzle(r, m1c, m1); return result;
	}
	//*******************************************************
	//end m1procing 
	//*******************************************************
	//          m2 procing
	//*******************************************************
	if (mcount<2){ return 0; }
	if (mcount == 0){ return 0; }
	m2colresb1 = fincol(b1, m2);
	if (m2colresb1 == 0){ ++m2restotal; m2c = b1; }

	m2colresb2 = fincol(b2, m2);
	if (m2colresb2 == 0){ ++m2restotal; m2c = b2; }
	if (mcount>2){
		m2colresb3 = fincol(b3, m2);
		if (m2colresb3 == 0){ ++m2restotal; m2c = b3; }
	}
	if (mcount>3){
		m2colresb4 = fincol(b4, m2);
		if (m2colresb4 == 0){ ++m2restotal; m2c = b4; }
	}
	if (mcount>4){
		m2colresb5 = fincol(b5, m2);
		if (m2colresb5 == 0){ ++m2restotal; m2c = b5; }
	}
	if (m2restotal == 1){
		glastwrite = "3369         "; result = inspuzzle(r, m2c, m2); return result;
	}

	//*******************************************************
	//end m2procing	
	//*******************************************************
	//          m3 procing
	//*******************************************************

	if (mcount <3) { return 0; }

	m3colresb1 = fincol(b1, m3);
	if (m3colresb1 == 0){ ++m3restotal; m3c = b1; }

	m3colresb2 = fincol(b2, m3);
	if (m3colresb2 == 0){ ++m3restotal; m3c = b2; }

	m3colresb3 = fincol(b3, m3);
	if (m3colresb3 == 0){ ++m3restotal; m3c = b3; }
	if (mcount>3){
		m3colresb4 = fincol(b4, m3);
		if (m3colresb4 == 0){ ++m3restotal; m3c = b4; }
	}
	if (mcount>4){
		m3colresb5 = fincol(b5, m3);
		if (m3colresb5 == 0){ ++m3restotal; m3c = b5; }
	}
	if ((m3restotal == 1) && (m3c>0)){
		glastwrite = "3397         "; result = inspuzzle(r, m3c, m3); 
	   return result;
	}

	//*******************************************************
	//end m3procing
	//*******************************************************	      
	//          m4 procing
	//*******************************************************

	if (mcount<4) { return 0; }
	m4colresb1 = fincol(b1, m4);
	if (m4colresb1 == 0){ ++m4restotal; m4c = b1; }

	m4colresb2 = fincol(b2, m4);
	if (m4colresb2 == 0){ ++m4restotal; m4c = b2; }

	m4colresb3 = fincol(b3, m4);
	if (m4colresb3 == 0){ ++m4restotal; m4c = b3; }

	m4colresb4 = fincol(b4, m4);
	if (m4colresb4 == 0){ ++m4restotal; m4c = b4; }
	if (mcount>4){
		m4colresb5 = fincol(b5, m4);
		if (m4colresb5 == 0){ ++m4restotal; m4c = b5; }
	}
	if (m4restotal == 1){
		glastwrite = "3423         "; result = inspuzzle(r, m4c, m4); return result;
	}

	//*******************************************************
	//end m4procing	   
	//*******************************************************
	//          m5 procing
	//*******************************************************
	if (mcount < 5){ return 0; }
	m5colresb1 = fincol(b1, m5);
	if (m5colresb1 == 0){ ++m5restotal; m5c = b1; }

	m5colresb2 = fincol(b2, m5);
	if (m5colresb2 == 0){ ++m5restotal; m5c = b2; }

	m5colresb3 = fincol(b3, m5);
	if (m5colresb3 == 0){ ++m5restotal; m5c = b3; }

	m5colresb4 = fincol(b4, m5);
	if (m5colresb4 == 0){ ++m5restotal; m5c = b4; }

	m5colresb5 = fincol(b5, m5);
	if (m5colresb5 == 0){ ++m5restotal; m5c = b5; }

	if (m5restotal == 1){
		glastwrite = "3448         "; result = inspuzzle(r, m5c, m5); return result;
	}
	if (mcount>5){ return 0; }

	//*******************************************************
	//end m5procing
	//*******************************************************	   
	return 0;
}
//==========================================================
//end row5elim
//==========================================================   
//==========================================================   
//==========================================================                 
int gallblsinrow(int r, int &b1, int &b2, int &b3, int &b4, int &b5, int &b6, int &b7, int &b8, int &b9){
	//==========================================================                 
	//Captures value of m numbers in row r .  The numbers are returned in                    
	//ascending order. Result contains the count of m numbers.                               
	//All m numbers are returned;                                                        
	//==========================================================                 
	//  r      = row                                                                               
	//  result = mnumber count                                                               
	//  &b1,&b2,&b3..&b9  =  values of m numbers.                                           
	//==========================================================                  
	int result = 0;
	//==========================================================                  
	string error = "error in parameters -function gallblsinrow";
	//==========================================================                                                                                                                
	b1 = 0;  b4 = 0;  b7 = 0;
	b2 = 0;  b5 = 0;  b8 = 0;
	b3 = 0;  b6 = 0;  b9 = 0;

	int i = 1;
	// if ((r<=0)||(r>9)){//cout<<error<<endl;}                                                              
	while (i <= 9){
		if (row[r].col[i] == 0){
			++result;
			if (b1 == 0){ b1 = i; }
			else{
				if (b2 == 0){ b2 = i; }
				else{
					if (b3 == 0){ b3 = i; }
					else{
						if (b4 == 0){ b4 = i; }
						else{
							if (b5 == 0){ b5 = i; }
							else{
								if (b6 == 0){ b6 = i; }
								else{
									if (b7 == 0){ b7 = i; }
									else{
										if (b8 == 0){ b8 = i; }
										else{
											if (b9 == 0){ b9 = i; break; }
										}
									}
								}
							}
						}
					}
				}
			}
		}
		++i;
	}
	return result;
}
//==========================================================                 
//end function gallblsinrow                                                                
//==========================================================     

//========================================================== 
int col5elim(int c){
	//==========================================================
	//  //cout <<"in function col5elim c="<<c<<endl;
	//readpuzzle();
	int result = 0;
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;

	int mcount = gallmincol(c, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int bcount = gallblsincol(c, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	if (mcount == 0){ return 0; }
	if (mcount>5){ return 0; }

	int m1rowresb1 = 0; int m1rowresb2 = 0; int m1rowresb3 = 0; int m1rowresb4 = 0; int m1rowresb5 = 0;
	int m2rowresb1 = 0; int m2rowresb2 = 0; int m2rowresb3 = 0; int m2rowresb4 = 0; int m2rowresb5 = 0;
	int m3rowresb1 = 0; int m3rowresb2 = 0; int m3rowresb3 = 0; int m3rowresb4 = 0; int m3rowresb5 = 0;
	int m4rowresb1 = 0; int m4rowresb2 = 0; int m4rowresb3 = 0; int m4rowresb4 = 0; int m4rowresb5 = 0;
	int m5rowresb1 = 0; int m5rowresb2 = 0; int m5rowresb3 = 0; int m5rowresb4 = 0; int m5rowresb5 = 0;

	int b1row = 0; int b2row = 0; int b3row = 0; int b4row = 0; int b5row = 0;
	int m1restotal = 0; int m2restotal = 0; int m3restotal = 0; int m4restotal = 0; int m5restotal = 0;
	int m1r = 0;    int m2r = 0;   int m3r = 0;   int m4r = 0;  int m5r = 0;

	//**********************************************************
	//          m1 procing
	//**********************************************************
	if (mcount == 0){ return 0; }

	if (mcount == 1){ glastwrite = "3548"; result = inspuzzle(b1, c, m1); return result; }

	m1rowresb1 = finrow(b1, m1);
	if (m1rowresb1 == 0){ ++m1restotal; m1r = b1; }
	if (mcount>1){
		m1rowresb2 = finrow(b2, m1);
		if (m1rowresb2 == 0){ ++m1restotal; m1r = b2; }
	}
	if (mcount>2){
		m1rowresb3 = finrow(b3, m1);
		if (m1rowresb3 == 0){ ++m1restotal; m1r = b3; }
	}
	if (mcount>3){
		m1rowresb4 = finrow(b4, m1);
		if (m1rowresb4 == 0){ ++m1restotal; m1r = b4; }
	}
	if (mcount>4){
		m1rowresb5 = finrow(b5, m1);
		if (m1rowresb5 == 0){ ++m1restotal; m1r = b5; }
	}
	if (m1restotal == 1){
		glastwrite = "3570"; result = inspuzzle(m1r, c, m1); return result;
	}
	//*******************************************************
	//end m1procing 
	//*******************************************************
	//          m2 procing
	//*******************************************************
	if (mcount<2){ return 0; }
	if (mcount == 0){ return 0; }
	m2rowresb1 = finrow(b1, m2);
	if (m2rowresb1 == 0){ ++m2restotal; m2r = b1; }

	m2rowresb2 = finrow(b2, m2);
	if (m2rowresb2 == 0){ ++m2restotal; m2r = b2; }
	if (mcount>2){
		m2rowresb3 = finrow(b3, m2);
		if (m2rowresb3 == 0){ ++m2restotal; m2r = b3; }
	}
	if (mcount>3){
		m2rowresb4 = finrow(b4, m2);
		if (m2rowresb4 == 0){ ++m2restotal; m2r = b4; }
	}
	if (mcount>4){
		m2rowresb5 = finrow(b5, m2);
		if (m2rowresb5 == 0){ ++m2restotal; m2r = b5; }
	}
	if (m2restotal == 1){
	glastwrite = "3597"; result = inspuzzle(m2r, c, m2); return result;
	}

	//*******************************************************
	//end m2procing	
	//*******************************************************
	//          m3 procing
	//*******************************************************

	if (mcount <3) { return 0; }

	m3rowresb1 = finrow(b1, m3);
	if (m3rowresb1 == 0){ ++m3restotal; m3r = b1; }

	m3rowresb2 = finrow(b2, m3);
	if (m3rowresb2 == 0){ ++m3restotal; m3r = b2; }

	m3rowresb3 = finrow(b3, m3);
	if (m3rowresb3 == 0){ ++m3restotal; m3r = b3; }
	if (mcount>3){
		m3rowresb4 = finrow(b4, m3);
		if (m3rowresb4 == 0){ ++m3restotal; m3r = b4; }
	}
	if (mcount>4){
		m3rowresb5 = finrow(b5, m3);
		if (m3rowresb5 == 0){ ++m3restotal; m3r = b5; }
	}
	if (m3restotal == 1){
		glastwrite = "3625"; result = inspuzzle(m3r, c, m3); return result;
	}

	//*******************************************************
	//end m3procing
	//*******************************************************	      
	//          m4 procing
	//*******************************************************
	m4restotal = 0;
	if (mcount<4) { return 0; }
	if (mcount>5) { return 0; }
	m4rowresb1 = finrow(b1, m4);
	if (m4rowresb1 == 0){ ++m4restotal; m4r = b1; }

	m4rowresb2 = finrow(b2, m4);
	if (m4rowresb2 == 0){ ++m4restotal; m4r = b2; }

	m4rowresb3 = finrow(b3, m4);
	if (m4rowresb3 == 0){ ++m4restotal; m4r = b3; }

	m4rowresb4 = finrow(b4, m4);
	if (m4rowresb4 == 0){ ++m4restotal; m4r = b4; }

	if (mcount == 5){ m4rowresb5 = finrow(b5, m4); }
	if ((mcount == 5) && (m4rowresb5 == 0)){ ++m4restotal; m4r = b5; }

	if (m4restotal == 1){
		glastwrite = "3652         "; result = inspuzzle(m4r, c, m4); return result;
	}

	//*******************************************************
	//end m4procing	   
	//*******************************************************
	//          m5 procing
	//*******************************************************
	if (mcount < 5){ return 0; }
	m5rowresb1 = finrow(b1, m5);
	if (m5rowresb1 == 0){ ++m5restotal; m5r = b1; }

	m5rowresb2 = finrow(b2, m5);
	if (m5rowresb2 == 0){ ++m5restotal; m5r = b2; }

	m5rowresb3 = finrow(b3, m5);
	if (m5rowresb3 == 0){ ++m5restotal; m5r = b3; }

	m5rowresb4 = finrow(b4, m5);
	if (m5rowresb4 == 0){ ++m5restotal; m5r = b4; }

	m5rowresb5 = finrow(b5, m5);
	if (m5rowresb5 == 0){ ++m5restotal; m5r = b5; }

	if (m5restotal == 1){
		glastwrite = "3677         "; result = inspuzzle(m5r, c, m5); return result;
	}
	if (mcount>5) { return 0; }
	//*******************************************************
	//end m5procing
	//*******************************************************	   
	return 0;
}

//==========================================================
//end col5elim
//==========================================================   
//==========================================================     
//==========================================================
int box3elim(int b){

	int result = 0;
	int res = 0;
	int m1 = 0; int m2 = 0; int m3 = 0;
	int found1st = 0;
	int found2nd = 0;
	int found3rd = 0;
	int mcount = gminbox(b, m1, m2, m3);
	if (mcount != 3){ return 0; }
	int firstbl = gfb(zbox, b);
	int lastbl = glastbl(zbox, b);
	int secondbl = gnb(zbox, b, firstbl);
	int colb1 = gcolfromboxandpos(b, firstbl);
	int colb2 = gcolfromboxandpos(b, secondbl);
	int colb3 = gcolfromboxandpos(b, lastbl);
	int rowb1 = growfromboxandpos(b, firstbl);
	int rowb2 = growfromboxandpos(b, secondbl);
	int rowb3 = growfromboxandpos(b, lastbl);

	res = fincol(colb1, m1);
	if (res >0){ found1st = m1; }
	res = fincol(colb1, m2);
	if (res >0){ found2nd = m2; }
	res = fincol(colb1, m3);
	if (res >0){ found3rd = m3; }

	if ((found1st>0) && (found2nd>0) && (found3rd == 0)){ glastwrite = "3720         "; result = inspuzzle(rowb1, colb1, m3); return result; }
	if ((found2nd>0) && (found3rd>0) && (found1st == 0)){ glastwrite = "3725         "; result = inspuzzle(rowb1, colb1, m1); return result; }
	if ((found1st>0) && (found3rd>0) && (found2nd == 0)){ glastwrite = "3724         "; result = inspuzzle(rowb1, colb1, m2); return result; }

	found1st = 0;
	found2nd = 0;
	found3rd = 0;

	res = fincol(colb2, m1);
	if (res >0){ found1st = m1; }
	res = fincol(colb2, m2);
	if (res >0){ found2nd = m2; }
	res = fincol(colb2, m3);
	if (res >0){ found3rd = m3; }

	if ((found1st>0) && (found2nd>0) && (found3rd == 0)){ glastwrite = "3741         "; result = inspuzzle(rowb2, colb2, m3); return result; }
	if ((found1st>0) && (found3rd>0) && (found2nd == 0)){ glastwrite = "3745         "; result = inspuzzle(rowb2, colb2, m2); return result; }
	if ((found2nd>0) && (found3rd>0) && (found1st == 0)){ glastwrite = "3746         "; result = inspuzzle(rowb2, colb2, m1); return result; }

	found1st = 0;
	found2nd = 0;
	found3rd = 0;

	res = fincol(colb3, m1);
	if (res >0){ found1st = m1; }
	res = fincol(colb3, m2);
	if (res >0){ found2nd = m2; }
	res = fincol(colb3, m3);
	if (res >0){ found3rd = m3; }


	if ((found1st>0) && (found2nd>0) && (found3rd == 0)){ glastwrite = "zzzz         "; result = inspuzzle(rowb3, colb3, m3); return result; }
	if ((found2nd>0) && (found3rd>0) && (found1st == 0)){ glastwrite = "3765         "; result = inspuzzle(rowb3, colb3, m1); return result; }
	if ((found1st>0) && (found3rd>0) && (found2nd == 0)){ glastwrite = "3764         "; result = inspuzzle(rowb3, colb3, m2); return result; }

	return 0;
}
//==========================================================
//end box3elim
//==========================================================

//==========================================================
int row3elim(int r){
	//==========================================================
	////cout <<"in row3elim"<<endl;
	//readpuzzle();
	int res = 0;

	int result = 0;
	int m1 = 0; int m2 = 0; int m3 = 0;
	int found1st = 0;
	int found2nd = 0;
	int found3rd = 0;
	int mcount = gminrow(r, m1, m2, m3);
	if (mcount != 3){ return 0; }

	int b1 = gfb(zrow, r);
	int b3 = glastbl(zrow, r);
	int b2 = gnb(zrow, r, b1);

	res = fincol(b1, m1);
	if (res >0){ found1st = m1; }
	res = fincol(b1, m2);
	if (res >0){ found2nd = m2; }
	if ((found1st>0) && (found2nd>0)){
		res = fincol(b1, m3);
		if (res >0){ return 0; }
		glastwrite = " 3868        "; result = inspuzzle(r, b1, m3); return result;
	}
	res = fincol(b1, m3);
	if (res >0){ found3rd = m3; }
	if ((found1st>0) && (found3rd>0) && (found2nd == 0)){ glastwrite = "3872         "; result = inspuzzle(r, b1, m2); return result; }
	if ((found2nd>0) && (found3rd>0) && (found1st == 0)){ glastwrite = "3873         "; result = inspuzzle(r, b1, m1); return result; }

	found1st = 0;
	found2nd = 0;
	found3rd = 0;
	res = fincol(b2, m1);
	if (res >0){ found1st = m1; }
	res = fincol(b2, m2);
	if (res >0){ found2nd = m2; }
	if ((found1st>0) && (found2nd>0)){
		res = fincol(b2, m3);
		if (res >0){ return 0; }
		glastwrite = "3889         "; result = inspuzzle(r, b2, m3); return result;
	}
	res = fincol(b2, m3);
	if (res >0){ found3rd = m3; }
	if ((found1st>0) && (found3rd>0) && (found2nd == 0)){ glastwrite = "3892         "; result = inspuzzle(r, b2, m2); return result; }
	if ((found2nd>0) && (found3rd>0) && (found1st == 0)){ glastwrite = "3894         "; result = inspuzzle(r, b2, m1); return result; }

	found1st = 0;
	found2nd = 0;
	found3rd = 0;
	res = fincol(b3, m1);
	if (res >0){ found1st = m1; }
	res = fincol(b3, m2);
	if (res >0){ found2nd = m2; }
	if ((found1st>0) && (found2nd>0)){
		res = fincol(b3, m3);
		if (res >0){ return 0; }
		glastwrite = "3904         "; result = inspuzzle(r, b3, m3); return result;
	}
	res = fincol(b3, m3);
	if (res >0){ found3rd = m3; }
	if ((found1st>0) && (found3rd>0) && (found2nd == 0)){ glastwrite = "3912         "; result = inspuzzle(r, b3, m2); return result; }
	if ((found2nd>0) && (found3rd>0) && (found1st == 0)){ glastwrite = "3913        "; result = inspuzzle(r, b3, m1); return result; }


	return 0;
}
//==========================================================
//end row3elim
//==========================================================
//==========================================================
int col3elim(int c){
	//==========================================================
	////cout <<"in col3elim"<<endl;
	//readpuzzle();

	int res = 0;
	int result = 0;
	int m1 = 0; int m2 = 0; int m3 = 0;
	int found1st = 0;
	int found2nd = 0;
	int found3rd = 0;
	int mcount = gmincol(c, m1, m2, m3);
	if (mcount != 3){ return 0; }

	int b1 = gfb(zcol, c);
	int b3 = glastbl(zcol, c);
	int b2 = gnb(zcol, c, b1);
	res = finrow(b1, m1);
	if (res>0){ found1st = m1; }
	res = finrow(b1, m2);
	if (res>0){ found2nd = m2; }
	if ((found1st>0) && (found2nd>0)){
		res = finrow(b1, m3);
		if (res>0){ return 0; }
		glastwrite = "3949         "; result = inspuzzle(b1, c, m3); return result;
	}
	res = finrow(b1, m3);
	if (res>0){ found3rd = m3; }

	if ((found1st>0) && (found3rd>0) && (found2nd == 0)){ glastwrite = "3955         "; result = inspuzzle(b1, c, m2); return result; }
	if ((found2nd>0) && (found3rd>0) && (found1st == 0)){ glastwrite = "3956        "; result = inspuzzle(b1, c, m1); return result; }

	found1st = 0;
	found2nd = 0;
	found3rd = 0;
	res = finrow(b2, m1);
	if (res>0){ found1st = m1; }
	res = finrow(b2, m2);
	if (res>0){ found2nd = m2; }
	if ((found1st>0) && (found2nd>0)){
		res = finrow(b2, m3);
		if (res>0){ return 0; }
		glastwrite = "3972         "; result = inspuzzle(b2, c, m3); return result;
	}
	res = finrow(b2, m3);
	if (res>0){ found3rd = m3; }

	if ((found1st>0) && (found3rd>0) && (found2nd == 0)){ glastwrite = "3978         "; result = inspuzzle(b2, c, m2); return result; }
	if ((found2nd>0) && (found3rd>0) && (found1st == 0)){ glastwrite = "3979         "; result = inspuzzle(b2, c, m1); return result; }

	found1st = 0;
	found2nd = 0;
	found3rd = 0;
	res = finrow(b3, m1);
	if (result>0){ found1st = m1; }
	res = finrow(b3, m2);
	if (res>0){ found2nd = m2; }
	if ((found1st>0) && (found2nd>0)){
		res = finrow(b3, m3);
		if (res>0){ return 0; }
		//cout <<"insert line 4181"<<endl;

		glastwrite = "3995         "; result = inspuzzle(b3, c, m3); return result;
	}
	res = finrow(b3, m3);
	if (res>0){ found3rd = m3; }

	if ((found1st>0) && (found3rd>0) && (found2nd == 0)){ glastwrite = "4001         "; result = inspuzzle(b3, c, m2); return result; }
	if ((found2nd>0) && (found3rd>0) && (found1st == 0)){ glastwrite = "4002         "; result = inspuzzle(b3, c, m1); return result; }


	return result;
}
//==========================================================
//end col3elim
//==========================================================
//==========================================================
int boxandrowelim3col(int c){
	//==========================================================
	//****************m1 procing
	////cout<<"in function boxandrowelim3col"<<c<<endl;   
	int m1 = 0; int m2 = 0; int m3 = 0;
	int result = 0;
	int mcount = gmincol(c, m1, m2, m3);
	if (mcount != 3){ return 0; }
	readboxes();
	int b1 = gfb(zcol, c);
	int b3 = glastbl(zcol, c);
	int b2 = gnb(zcol, c, b1);
	int boxb1 = gboxfromcolandpos(c, b1);
	int boxb2 = gboxfromcolandpos(c, b2);
	int boxb3 = gboxfromcolandpos(c, b3);


	int foundinbox1 = finbox(boxb1, m1);
	int foundinbox2 = finbox(boxb2, m1);
	int foundinbox3 = finbox(boxb3, m1);

	if ((b2 > 6) && (b3 > 6) && (foundinbox3 > 0) && (foundinbox1 == 0)){ if (debug){ cout << "insertline 6524" << endl; glastwrite = " xyz        "; printpuzzle(); } result = inspuzzle(b1, c, m1); return result; }
	else{
		if ((b2 < 7) && (b2>3) && (b3 < 7) && (b3>3) && (b1 < 4) && (foundinbox2>0) && (foundinbox1 == 0)) { if (debug){ cout << "insertline 6526" << endl; glastwrite = "4036         "; } result = inspuzzle(b1, c, m1); return result; }
		else{
			if ((b1 < 4) && (b2 < 4) && (foundinbox1>0) && (foundinbox3 == 0)){ if (debug){ cout << "insertline 6528" << endl; glastwrite = "4038         "; printpuzzle(); }result = inspuzzle(b3, c, m1); return result; }
		}
	}

	//****************m2 procing   

	foundinbox1 = finbox(boxb1, m2);
	foundinbox2 = finbox(boxb2, m2);
	foundinbox3 = finbox(boxb3, m2);

	if ((b2 > 6) && (b3 > 6) && (foundinbox3 > 0) && (foundinbox1 == 0)){ if (debug){ cout << "insertline 6538" << endl; glastwrite = "4048         "; printpuzzle(); } result = inspuzzle(b1, c, m2); return result; }
	else{
		if ((b2 < 7) && (b2>3) && (b3 < 7) && (b3>3) && (b1 < 4) && (foundinbox2>0) && (foundinbox3 > 0) && (foundinbox1 == 0)) { glastwrite = "4050         "; printpuzzle(); result = inspuzzle(b1, c, m2); return result; }
		else{
			if ((b1 < 4) && (b2 < 4) && (foundinbox1>0) && (foundinbox3 == 0)){ glastwrite = "4052         "; printpuzzle(); result = inspuzzle(b3, c, m2); return result; }
		}
	}
	//****************m3 procing

	foundinbox1 = finbox(boxb1, m3);
	foundinbox2 = finbox(boxb2, m3);
	foundinbox3 = finbox(boxb3, m3);

	if ((b2>6) && (b3>6) && (foundinbox3>0) && (foundinbox1 == 0)){ glastwrite = "4061         "; result = inspuzzle(b1, c, m3); return result; }
	else{
		if ((b2<7) && (b2>3) && (b3<7) && (b3>3) && (b1<4) && (foundinbox2>0) && (foundinbox1 == 0)) { glastwrite = "4063         "; result = inspuzzle(b1, c, m3); return result; }
		else{
			if ((b1<4) && (b2<4) && (foundinbox1>0) && (foundinbox3 == 0)){ glastwrite = "4065         "; result = inspuzzle(b3, c, m3); return result; }
		}
	}
	if (result>0){ ; }

	return result;
}
//==========================================================
//end boxandrowelimcol
//==========================================================
//==========================================================                                                                                                             
int boxandcolelim3row(int r){
	//==========================================================                                                                                                             
	////cout<<"in function boxandcolelim3row"<<r<<endl;   

	//****************m1 procing                                                                                                                                          
	int m1 = 0; int m2 = 0; int m3 = 0;
	int result = 0;
	int mcount = gminrow(r, m1, m2, m3);
	if (mcount != 3){ return 0; }
	int b1 = gfb(zrow, r);
	if (mcount == 0){ return 0; }

	int b3 = glastbl(zrow, r);

	int b2 = gnb(zrow, r, b1);
	int boxb1 = gboxfromrowandpos(r, b1);
	int boxb2 = gboxfromrowandpos(r, b2);
	int boxb3 = gboxfromrowandpos(r, b3);

	int foundinbox1 = finbox(boxb1, m1);
	int foundinbox2 = finbox(boxb2, m1);
	int foundinbox3 = finbox(boxb3, m1);

	if ((b2>6) && (b3>6) && (foundinbox3>0) && (foundinbox1 == 0)){ glastwrite = "4103         "; result = inspuzzle(r, b1, m1); return result; }
	if ((b2<7) && (b2>3) && (b3<7) && (b3>3) && (b1<4) && (foundinbox2>0) && (foundinbox1 == 0)) { glastwrite = "4104         "; result = inspuzzle(r, b1, m1); return result; }
	if ((b1<4) && (b2<4) && (foundinbox1>0) && (foundinbox3 == 0)){ glastwrite = "4105         "; result = inspuzzle(r, b3, m1); return result; }
	//****************m2 procing                                                                                                                                          

	foundinbox1 = finbox(boxb1, m2);
	foundinbox2 = finbox(boxb2, m2);
	foundinbox3 = finbox(boxb3, m2);

	if ((b2>6) && (b3>6) && (foundinbox3>0) && (foundinbox1 == 0)){ glastwrite = "4113        "; result = inspuzzle(r, b1, m2); return result; }
	if ((b2<7) && (b2>3) && (b3<7) && (b3>3) && (b1<4) && (foundinbox2>0) && (foundinbox1 == 0)) { glastwrite = "4114         "; result = inspuzzle(r, b1, m2); return result; }
	if ((b1<4) && (b2<4) && (foundinbox1>0) && (foundinbox3 == 0)){ glastwrite = "4115        "; result = inspuzzle(r, b3, m2); return result; }
	//****************m3 procing                                                                                                                                          

	foundinbox1 = finbox(boxb1, m3);
	foundinbox2 = finbox(boxb2, m3);
	foundinbox3 = finbox(boxb3, m3);

	if ((b2>6) && (b3>6) && (foundinbox3>0) && (foundinbox1 == 0)){ glastwrite = "4123         "; result = inspuzzle(r, b1, m3); return result; }
	if ((b2<7) && (b2>3) && (b3<7) && (b3>3) && (b1<4) && (foundinbox2>0) && (foundinbox1 == 0)) { glastwrite = "4124         "; result = inspuzzle(r, b1, m3); return result; }
	if ((b1<4) && (b2<4) && (foundinbox1>0) && (foundinbox3 == 0)){ glastwrite = "4125         "; result = inspuzzle(r, b3, m3); return result; }

	return 0;
}
//==========================================================                                                                                                             
//end boxandcolelimrow                                                                                                                                                   
//==========================================================    	  	 	             	  	 	                                                                             
//==========================================================
int heavylogic(){
	//========================================================== 
	////cout <<"in function heavylogic"<<endl;
	//checkfin();
	int result = 0;
	int boxb1; int boxb2; int boxb3; int boxb4; int boxb5;
	int mcount; int bcount = 0;
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	int foundinb1 = 0; int foundinb2 = 0; int foundinb3 = 0; int foundinb4 = 0; int foundinb5 = 0;
	int resultcountm1 = 0; int resultcountm2 = 0; int resultcountm3 = 0; int resultcountm4 = 0; int resultcountm5 = 0;
	//if (zcnt == 0){ checksumall(); printpuzzle(); exit(0); }

	//	readpuzzle();
	//readboxes();
	for (int runit = 1; runit <= 3; ++runit){
		int targrownum1 = 0; int targboxnum1 = 0;
		int targrownum2 = 0; int targboxnum2 = 0;
		int savenum1 = 0; int savenum2 = 0;
		for (int num = 1; num <= 9; ++num){
			if (rowunit[runit].nc[num] == 2){
				if (savenum1 == 0){
					savenum1 = num;
					targrownum1 = rowunit[runit].targrow[savenum1];
					targboxnum1 = rowunit[runit].targbox[savenum1];
					if ((!targrownum1) || (!targboxnum1)){ return 0; }
				}
				else{
					if (savenum2 == 0){

						targrownum2 = rowunit[runit].targrow[num];
						targboxnum2 = rowunit[runit].targbox[num];
						if ((!targrownum2) || (!targboxnum2)){ return 0; }
						if ((targrownum1 == targrownum2) && (targboxnum1 == targboxnum2)){
							savenum2 = num;
						}
					}
				}
				if ((savenum1>0) && (savenum2>0)){ break; }
			}
		}
		if ((savenum1>0) && (savenum2>0)){//g row
			if (targboxnum1 == targboxnum2){//now g all m in targrow             
				mcount = 0; bcount = 0;
				foundinb1 = 0; foundinb2 = 0; foundinb3 = 0; foundinb4 = 0; foundinb5 = 0;

				resultcountm1 = 0; resultcountm2 = 0; resultcountm3 = 0; resultcountm4 = 0; resultcountm5 = 0;
				mcount = gallminrow(targrownum1, m1, m2, m3, m4, m5, m6, m7, m8, m9);
				if ((mcount<4) || (mcount>5)){ continue; }
				resultcountm1 = 0;
				bcount = gallblsinrow(targrownum1, b1, b2, b3, b4, b5, b6, b7, b8, b9);
				if ((m1 != savenum1) && (m1 != savenum2)){//check for 2 of 3 excluding targbox
					boxb1 = gboxfromrowandpos(targrownum1, b1);
					if (boxb1 != targboxnum1){
						foundinb1 = fincol(b1, m1);
						if (foundinb1>0){ ++resultcountm1; }
					}
					boxb2 = gboxfromrowandpos(targrownum1, b2);
					if (boxb2 != targboxnum1){
						foundinb2 = fincol(b2, m1);
						if (foundinb2>0){ ++resultcountm1; }
					}
					boxb3 = gboxfromrowandpos(targrownum1, b3);
					if (boxb3 != targboxnum1){
						foundinb3 = fincol(b3, m1);
						if (foundinb3>0){ ++resultcountm1; }
					}
					boxb4 = gboxfromrowandpos(targrownum1, b4);
					if (boxb4 != targboxnum1){
						foundinb4 = fincol(b4, m1);
						if (foundinb4>0){ ++resultcountm1; }
					}

					if (mcount == 5){
						boxb5 = gboxfromrowandpos(targrownum1, b5);
						if (boxb5 != targboxnum1){
							foundinb5 = fincol(b5, m1);
							if (foundinb5>0){ ++resultcountm1; }
						}
					}

					if (((mcount == 4) && (resultcountm1 == 1)) || ((mcount == 5) && (resultcountm1 == 2))){
						if ((foundinb1 == 0) && (boxb1 != targboxnum1)){ glastwrite = "4212         "; result = inspuzzle(targrownum1, b1, m1); return result; }
						if ((foundinb2 == 0) && (boxb2 != targboxnum1)){ glastwrite = "4213         "; result = inspuzzle(targrownum1, b2, m1); return result; }
						if ((foundinb3 == 0) && (boxb3 != targboxnum1)){ glastwrite = "4214         "; result = inspuzzle(targrownum1, b3, m1); return result; }
						if ((foundinb4 == 0) && (boxb4 != targboxnum1)){ glastwrite = "4215         "; result = inspuzzle(targrownum1, b4, m1); return result; }
						if ((mcount == 5) && (foundinb5 == 0) && (boxb5 != targboxnum1)){ glastwrite = " 4216        "; result = inspuzzle(targrownum1, b5, m1); return result; }
					}
				}
			}
			foundinb1 = 0; foundinb2 = 0; foundinb3 = 0; foundinb4 = 0; foundinb5 = 0;
			resultcountm2 = 0;
			if ((m2 != savenum1) && (m2 != savenum2)){//check for 2 of 3 excluding targbox

				boxb1 = gboxfromrowandpos(targrownum1, b1);
				if (boxb1 != targboxnum1){
					foundinb1 = fincol(b1, m2);
					if (foundinb1>0){ ++resultcountm2; }
				}
				boxb2 = gboxfromrowandpos(targrownum1, b2);
				if (boxb2 != targboxnum1){
					foundinb2 = fincol(b2, m2);
					if (foundinb2>0){ ++resultcountm2; }
				}
				boxb3 = gboxfromrowandpos(targrownum1, b3);
				if (boxb3 != targboxnum1){
					foundinb3 = fincol(b3, m2);
					if (foundinb3>0){ ++resultcountm2; }
				}
				boxb4 = gboxfromrowandpos(targrownum1, b4);
				if (boxb4 != targboxnum1){
					foundinb4 = fincol(b4, m2);
					if (foundinb4>0){ ++resultcountm2; }
				}
				if (mcount == 5){
					boxb5 = gboxfromrowandpos(targrownum1, b5);
					if (boxb5 != targboxnum1){
						foundinb5 = fincol(b5, m2);
						if (foundinb5>0){ ++resultcountm2; }
					}
				}

				if (((mcount == 4) && (resultcountm2 == 1)) || ((mcount == 5) && (resultcountm2 == 2))){

					if ((foundinb1 == 0) && (boxb1 != targboxnum1)){ glastwrite = "4251         "; result = inspuzzle(targrownum1, b1, m2); return result; }
					if ((foundinb2 == 0) && (boxb2 != targboxnum1)){ glastwrite = "4252         "; result = inspuzzle(targrownum1, b2, m2); return result; }
					if ((foundinb3 == 0) && (boxb3 != targboxnum1)){ glastwrite = "4253         "; result = inspuzzle(targrownum1, b3, m2); return result; }
					if ((foundinb4 == 0) && (boxb4 != targboxnum1)){ glastwrite = "4254         "; result = inspuzzle(targrownum1, b4, m2); return result; }
					if ((mcount == 5) && (foundinb5 == 0) && (boxb5 != targboxnum1)){ glastwrite = "4255         "; result = inspuzzle(targrownum1, b5, m2); return result; }
				}

			}
			foundinb1 = 0; foundinb2 = 0; foundinb3 = 0; foundinb4 = 0; foundinb5 = 0;
			resultcountm3 = 0;
			if ((m3 != savenum1) && (m3 != savenum2)){//check for 2 of 3 excluding targbox                             
				boxb1 = gboxfromrowandpos(targrownum1, b1);
				if (boxb1 != targboxnum1){
					foundinb1 = fincol(b1, m3);
					if (foundinb1>0){ ++resultcountm3; }
				}
				boxb2 = gboxfromrowandpos(targrownum1, b2);
				if (boxb2 != targboxnum1){
					foundinb2 = fincol(b2, m3);
					if (foundinb2>0){ ++resultcountm3; }

				}
				boxb3 = gboxfromrowandpos(targrownum1, b3);
				if (boxb3 != targboxnum1){
					foundinb3 = fincol(b3, m3);
					if (foundinb3>0){ ++resultcountm3; }
				}
				boxb4 = gboxfromrowandpos(targrownum1, b4);
				if (boxb4 != targboxnum1){
					foundinb4 = fincol(b4, m3);
					if (foundinb4>0){ ++resultcountm3; }
				}
				if (mcount == 5){
					boxb5 = gboxfromrowandpos(targrownum1, b5);
					if (boxb5 != targboxnum1){
						foundinb5 = fincol(b5, m3);
						if (foundinb5>0){ ++resultcountm3; }
					}
				}
				if (((mcount == 4) && (resultcountm3 == 1)) || ((mcount == 5) && (resultcountm3 == 2))){

					if ((foundinb1 == 0) && (boxb1 != targboxnum1)){ glastwrite = "         "; result = inspuzzle(targrownum1, b1, m3); return result; }
					if ((foundinb2 == 0) && (boxb2 != targboxnum1)){ glastwrite = "         "; result = inspuzzle(targrownum1, b2, m3); return result; }
					if ((foundinb3 == 0) && (boxb3 != targboxnum1)){ glastwrite = "         "; result = inspuzzle(targrownum1, b3, m3); return result; }
					if ((foundinb4 == 0) && (boxb4 != targboxnum1)){ glastwrite = "         "; result = inspuzzle(targrownum1, b4, m3); return result; }
					if ((mcount == 5) && (foundinb5 == 0) && (boxb5 != targboxnum1)){ glastwrite = "         "; result = inspuzzle(targrownum1, b5, m3); return result; }
				}
			}
			foundinb1 = 0; foundinb2 = 0; foundinb3 = 0; foundinb4 = 0; foundinb5 = 0;
			resultcountm4 = 0;
			if ((m4 != savenum1) && (m4 != savenum2)){//check for 2 of 3 excluding targbox                                 
				boxb1 = gboxfromrowandpos(targrownum1, b1);
				if (boxb1 != targboxnum1){
					foundinb1 = fincol(b1, m4);
					if (foundinb1>0){ ++resultcountm4; }
				}
				boxb2 = gboxfromrowandpos(targrownum1, b2);
				if (boxb2 != targboxnum1){
					foundinb2 = fincol(b2, m4);
					if (foundinb2>0){ ++resultcountm4; }
				}
				boxb3 = gboxfromrowandpos(targrownum1, b3);
				if (boxb3 != targboxnum1){
					foundinb3 = fincol(b3, m4);
					if (foundinb3>0){ ++resultcountm4; }
				}
				boxb4 = gboxfromrowandpos(targrownum1, b4);
				if (boxb4 != targboxnum1){
					foundinb4 = fincol(b4, m4);
					if (foundinb4>0){ ++resultcountm4; }
				}
				if (mcount == 5){
					boxb5 = gboxfromrowandpos(targrownum1, b5);
					if (boxb5 != targboxnum1){
						foundinb5 = fincol(b5, m4);
						if (foundinb5>0){ ++resultcountm4; }
					}
				}
				if (((mcount == 4) && (resultcountm4 == 1)) || ((mcount == 5) && (resultcountm4 == 2))){

					if ((foundinb1 == 0) && (boxb1 != targboxnum1)){
						glastwrite = "4329         "; result = inspuzzle(targrownum1, b1, m4); return result;
					}
					else{
						if ((foundinb2 == 0) && (boxb2 != targboxnum1)){
							glastwrite = "4330         "; result = inspuzzle(targrownum1, b2, m4); return result;
						}
						else{
							if ((foundinb3 == 0) && (boxb3 != targboxnum1)){
								glastwrite = "4331         "; result = inspuzzle(targrownum1, b3, m4); return result;
							}
							else{
								if ((foundinb4 == 0) && (boxb4 != targboxnum1)){
									glastwrite = "4332         "; result = inspuzzle(targrownum1, b4, m4); return result;
								}
								else{
									if ((mcount == 5) && (foundinb5 == 0) && (boxb5 != targboxnum1)){
										glastwrite = "4333         "; result = inspuzzle(targrownum1, b5, m4); return result;
									}
								}
							}
						}
					}
				}



			}
			foundinb1 = 0; foundinb2 = 0; foundinb3 = 0; foundinb4 = 0; foundinb5 = 0;
			resultcountm5 = 0;
			if ((m5 != savenum1) && (m5 != savenum2)){//check for 2 of 3 excluding targbox                                                                                                                                      
				boxb1 = gboxfromrowandpos(targrownum1, b1);
				if (boxb1 != targboxnum1){
					foundinb1 = fincol(b1, m5);
					if (foundinb1>0){ ++resultcountm5; }
				}
				boxb2 = gboxfromrowandpos(targrownum1, b2);
				if (boxb2 != targboxnum1){
					foundinb2 = fincol(b2, m5);
					if (foundinb2>0){ ++resultcountm5; }

				}
				boxb3 = gboxfromrowandpos(targrownum1, b3);
				if (boxb3 != targboxnum1){
					foundinb3 = fincol(b3, m5);
					if (foundinb3>0){ ++resultcountm5; }
				}
				boxb4 = gboxfromrowandpos(targrownum1, b4);
				if (boxb4 != targboxnum1){
					foundinb4 = fincol(b4, m5);
					if (foundinb4>0){ ++resultcountm5; }
				}
				if (mcount == 5){
					boxb5 = gboxfromrowandpos(targrownum1, b5);
					if (boxb5 != targboxnum1){
						foundinb5 = fincol(b5, m5);
						if (foundinb5>0){ ++resultcountm5; }
					}
				}
				if (((mcount == 4) && (resultcountm5 == 1)) || ((mcount == 5) && (resultcountm5 == 2))){

					if ((foundinb1 == 0) && (boxb1 != targboxnum1)){ glastwrite = "4369         "; result = inspuzzle(targrownum1, b1, m5); return result; }
					if ((foundinb2 == 0) && (boxb2 != targboxnum1)){ glastwrite = "4370         "; result = inspuzzle(targrownum1, b2, m5); return result; }
					if ((foundinb3 == 0) && (boxb3 != targboxnum1)){ glastwrite = "4372         "; result = inspuzzle(targrownum1, b3, m5); return result; }
					if ((foundinb4 == 0) && (boxb4 != targboxnum1)){ glastwrite = "4373         "; result = inspuzzle(targrownum1, b4, m5); return result; }
					if ((mcount == 5) && (foundinb5 == 0) && (boxb5 != targboxnum1)){ glastwrite = "4374         "; result = inspuzzle(targrownum1, b5, m5); return result; }
				}
			}
		}

	}
	return 0;
}
//==========================================================
//end heavylogic
//==========================================================


//==========================================================                                                       
//==========================================================
int boxrow3done4(int b){
	//==========================================================
	////cout<<"in function boxrow3done4"<<b<<endl;
	//readpuzzle();
	if (box[b].done == true){ return 0; }
	if (box[b].bcnt == 0){ box[b].done = true; }
//	box[b].bcnt = 0;
//	readbox(b);
	bool m1elimb1 = false; bool m1elimb2 = false; bool m1elimb3 = false; bool m1elimb4 = false;
	bool m2elimb1 = false; bool m2elimb2 = false; bool m2elimb3 = false; bool m2elimb4 = false;
	bool m3elimb1 = false; bool m3elimb2 = false; bool m3elimb3 = false; bool m3elimb4 = false;
	bool m4elimb1 = false; bool m4elimb2 = false; bool m4elimb3 = false; bool m4elimb4 = false;
	int m1elimcount = 0; int m2elimcount = 0; int m3elimcount = 0; int m4elimcount = 0;
	int result = 0;
	if (box[b].done == true){ return 0; }
	if (box[b].r3done == false){ return 0; }
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	int mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	if (mcount != 4){ return 0; }
	if (bcount != 4){ return 0; }

	//*********************m1 procing
	int b1row = growfromboxandpos(b, b1);
	int b1col = gcolfromboxandpos(b, b1);
	int b1resrowm1 = finrow(b1row, m1);
	int b1rescolm1 = fincol(b1col, m1);
	if ((b1resrowm1>0) || (b1rescolm1>0)){ m1elimb1 = true; ++m1elimcount; }

	int b2row = growfromboxandpos(b, b2);
	int b2col = gcolfromboxandpos(b, b2);
	int b2resrowm1 = finrow(b2row, m1);
	int b2rescolm1 = fincol(b2col, m1);
	if ((b2resrowm1>0) || (b2rescolm1>0)){ m1elimb2 = true; ++m1elimcount; }

	int b3row = growfromboxandpos(b, b3);
	int b3col = gcolfromboxandpos(b, b3);
	int b3resrowm1 = finrow(b3row, m1);
	int b3rescolm1 = fincol(b3col, m1);
	if ((b3resrowm1>0) || (b3rescolm1>0)){ m1elimb3 = true; ++m1elimcount; }

	int b4row = growfromboxandpos(b, b4);
	int b4col = gcolfromboxandpos(b, b4);
	int b4resrowm1 = finrow(b4row, m1);
	int b4rescolm1 = fincol(b4col, m1);
	if ((b4resrowm1>0) || (b4rescolm1>0)){ m1elimb4 = true; ++m1elimcount; }

	if (m1elimcount == 3){
		//cout<<"insert line 7595"<<endl;                                            
		if (m1elimb1 == false){ glastwrite = "4438         "; result = inspuzzle(b1row, b1col, m1); }
		if (m1elimb2 == false){ glastwrite = "4439         "; result = inspuzzle(b2row, b2col, m1); }
		if (m1elimb3 == false){ glastwrite = "4440         "; result = inspuzzle(b3row, b3col, m1); }
		if (m1elimb4 == false){ glastwrite = "4441         "; result = inspuzzle(b4row, b4col, m1); }
		;
		return result;
	}

	//**********************m2 procing
	int b1resrowm2 = finrow(b1row, m2);
	int b1rescolm2 = fincol(b1col, m2);
	if ((b1resrowm2>0) || (b1rescolm2>0)){ m2elimb1 = true; ++m2elimcount; }

	int b2resrowm2 = finrow(b2row, m2);
	int b2rescolm2 = fincol(b2col, m2);
	if ((b2resrowm2>0) || (b2rescolm2>0)){ m2elimb2 = true; ++m2elimcount; }

	int b3resrowm2 = finrow(b3row, m2);
	int b3rescolm2 = fincol(b3col, m2);
	if ((b3resrowm2>0) || (b3rescolm2>0)){ m2elimb3 = true; ++m2elimcount; }

	int b4resrowm2 = finrow(b4row, m2);
	int b4rescolm2 = fincol(b4col, m2);
	if ((b4resrowm2>0) || (b4rescolm2>0)){ m2elimb4 = true; ++m2elimcount; }

	if (m2elimcount == 3){
		if (m2elimb1 == false){ glastwrite = "4465         "; result = inspuzzle(b1row, b1col, m2); }
		if (m2elimb2 == false){ glastwrite = "4466         "; result = inspuzzle(b2row, b2col, m2); }
		if (m2elimb3 == false){ glastwrite = "4467         "; result = inspuzzle(b3row, b3col, m2); }
		if (m2elimb4 == false){ glastwrite = "4468         "; result = inspuzzle(b4row, b4col, m2); }

		return result;
	}

	//**********************m3 procing                              
	int b1resrowm3 = finrow(b1row, m3);
	int b1rescolm3 = fincol(b1col, m3);
	if ((b1resrowm3>0) || (b1rescolm3>0)){ m3elimb1 = true; ++m3elimcount; }

	int b2resrowm3 = finrow(b2row, m3);
	int b2rescolm3 = fincol(b2col, m3);
	if ((b2resrowm3>0) || (b2rescolm3>0)){ m3elimb2 = true; ++m3elimcount; }

	int b3resrowm3 = finrow(b3row, m3);
	int b3rescolm3 = fincol(b3col, m3);
	if ((b3resrowm3>0) || (b3rescolm3>0)){ m3elimb3 = true; ++m3elimcount; }

	int b4resrowm3 = finrow(b4row, m3);
	int b4rescolm3 = fincol(b4col, m3);
	if ((b4resrowm3>0) || (b4rescolm3>0)){ m3elimb4 = true; ++m3elimcount; }

	if (m3elimcount == 3){
		if (m3elimb1 == false){ glastwrite = "4492         "; result = inspuzzle(b1row, b1col, m3); }
		if (m3elimb2 == false){ glastwrite = "4493         "; result = inspuzzle(b2row, b2col, m3); }
		if (m3elimb3 == false){ glastwrite = "4494         "; result = inspuzzle(b3row, b3col, m3); }
		if (m3elimb4 == false){ glastwrite = "4495         "; result = inspuzzle(b4row, b4col, m3); }

		return result;
	}

	//**********************m4 procing                              
	int b1resrowm4 = finrow(b1row, m4);
	int b1rescolm4 = fincol(b1col, m4);
	if ((b1resrowm4>0) || (b1rescolm4>0)){ m4elimb1 = true; ++m4elimcount; }

	int b2resrowm4 = finrow(b2row, m4);
	int b2rescolm4 = fincol(b2col, m4);
	if ((b2resrowm4>0) || (b2rescolm4>0)){ m4elimb2 = true; ++m4elimcount; }

	int b3resrowm4 = finrow(b3row, m4);
	int b3rescolm4 = fincol(b3col, m4);
	if ((b3resrowm4>0) || (b3rescolm4>0)){ m4elimb3 = true; ++m4elimcount; }

	int b4resrowm4 = finrow(b4row, m4);
	int b4rescolm4 = fincol(b4col, m4);
	if ((b4resrowm4>0) || (b4rescolm4>0)){ m4elimb4 = true; ++m4elimcount; }

	if (m4elimcount == 3){
		if (m4elimb1 == false){ glastwrite = "4519         "; result = inspuzzle(b1row, b1col, m4); }
		if (m4elimb2 == false){ glastwrite = "4520         "; result = inspuzzle(b2row, b2col, m4); }
		if (m4elimb3 == false){ glastwrite = "4521         "; result = inspuzzle(b3row, b3col, m4); }
		if (m4elimb4 == false){ glastwrite = "4522         "; result = inspuzzle(b4row, b4col, m4); }

		return result;
	}
	return 0;
}
//==========================================================
//end boxrow3done4
//========================================================== 
//==========================================================
int boxrow3done3(int b){
	//==========================================================
	////cout<<"in function boxrow3done3"<<b<<endl;
	//readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
	bool m1elimb1 = false; bool m1elimb2 = false; bool m1elimb3 = false;
	bool m2elimb1 = false; bool m2elimb2 = false; bool m2elimb3 = false;
	bool m3elimb1 = false; bool m3elimb2 = false; bool m3elimb3 = false;
	int m1elimcount = 0; int m2elimcount = 0; int m3elimcount = 0;
	int result = 0;
	if (box[b].done == true){ return 0; }
	if (box[b].r3done == false){ return 0; }
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	int mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	if (mcount != 3){ return 0; }
	if (bcount != 3){ return 0; }
	//*********************m1 procing
	int b1row = growfromboxandpos(b, b1);
	int b1col = gcolfromboxandpos(b, b1);
	int b1resrowm1 = finrow(b1row, m1);
	int b1rescolm1 = fincol(b1col, m1);
	if ((b1resrowm1>0) || (b1rescolm1>0)){ m1elimb1 = true; ++m1elimcount; }

	int b2row = growfromboxandpos(b, b2);
	int b2col = gcolfromboxandpos(b, b2);
	int b2resrowm1 = finrow(b2row, m1);
	int b2rescolm1 = fincol(b2col, m1);
	if ((b2resrowm1>0) || (b2rescolm1>0)){ m1elimb2 = true; ++m1elimcount; }

	int b3row = growfromboxandpos(b, b3);
	int b3col = gcolfromboxandpos(b, b3);
	int b3resrowm1 = finrow(b3row, m1);
	int b3rescolm1 = fincol(b3col, m1);
	if ((b3resrowm1>0) || (b3rescolm1>0)){ m1elimb3 = true; ++m1elimcount; }

	if (m1elimcount == 2){
		if (m1elimb1 == false){ glastwrite = "4573         "; result = inspuzzle(b1row, b1col, m1); }
		if (m1elimb2 == false){ glastwrite = "4574         "; result = inspuzzle(b2row, b2col, m1); }
		if (m1elimb3 == false){ glastwrite = "4575         "; result = inspuzzle(b3row, b3col, m1); }
		;
		return result;
	}

	//**********************m2 procing
	int b1resrowm2 = finrow(b1row, m2);
	int b1rescolm2 = fincol(b1col, m2);
	if ((b1resrowm2>0) || (b1rescolm2>0)){ m2elimb1 = true; ++m2elimcount; }

	int b2resrowm2 = finrow(b2row, m2);
	int b2rescolm2 = fincol(b2col, m2);
	if ((b2resrowm2>0) || (b2rescolm2>0)){ m2elimb2 = true; ++m2elimcount; }

	int b3resrowm2 = finrow(b3row, m2);
	int b3rescolm2 = fincol(b3col, m2);
	if ((b3resrowm2>0) || (b3rescolm2>0)){ m2elimb3 = true; ++m2elimcount; }

	if (m2elimcount == 2){
		if (m2elimb1 == false){ glastwrite = "4595         "; result = inspuzzle(b1row, b1col, m2); }
		if (m2elimb2 == false){ glastwrite = "4596         "; result = inspuzzle(b2row, b2col, m2); }
		if (m2elimb3 == false){ glastwrite = "4597         "; result = inspuzzle(b3row, b3col, m2); }

		return result;
	}

	//**********************m3 procing                              
	int b1resrowm3 = finrow(b1row, m3);
	int b1rescolm3 = fincol(b1col, m3);
	if ((b1resrowm3>0) || (b1rescolm3>0)){ m3elimb1 = true; ++m3elimcount; }

	int b2resrowm3 = finrow(b2row, m3);
	int b2rescolm3 = fincol(b2col, m3);
	if ((b2resrowm3>0) || (b2rescolm3>0)){ m3elimb2 = true; ++m3elimcount; }

	int b3resrowm3 = finrow(b3row, m3);
	int b3rescolm3 = fincol(b3col, m3);
	if ((b3resrowm3>0) || (b3rescolm3>0)){ m3elimb3 = true; ++m3elimcount; }

	if (m3elimcount == 2){
		if (m3elimb1 == false){ glastwrite = "4617         "; result = inspuzzle(b1row, b1col, m3); }
		if (m3elimb2 == false){ glastwrite = "4618         "; result = inspuzzle(b2row, b2col, m3); }
		if (m3elimb3 == false){ glastwrite = "4619         "; result = inspuzzle(b3row, b3col, m3); }

		return result;
	}

	return 0;
}
//==========================================================
//end boxrow3done3
//==========================================================                                                              
//==========================================================
int boxcol3done4(int b){
	//==========================================================
	////cout<<"in function boxcol3done4"<<endl;
	//	readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
	bool m1elimb1 = false; bool m1elimb2 = false; bool m1elimb3 = false; bool m1elimb4 = false;
	bool m2elimb1 = false; bool m2elimb2 = false; bool m2elimb3 = false; bool m2elimb4 = false;
	bool m3elimb1 = false; bool m3elimb2 = false; bool m3elimb3 = false; bool m3elimb4 = false;
	bool m4elimb1 = false; bool m4elimb2 = false; bool m4elimb3 = false; bool m4elimb4 = false;
	int m1elimcount = 0; int m2elimcount = 0; int m3elimcount = 0; int m4elimcount = 0;
	int result = 0;
	if (box[b].done == true){ return 0; }
	if (box[b].c3done == false){ return 0; }
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	int mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	if (mcount != 4){ return 0; }
	if (bcount != 4){ return 0; }
	//*********************m1 procing
	int b1row = growfromboxandpos(b, b1);
	int b1col = gcolfromboxandpos(b, b1);
	int b1resrowm1 = finrow(b1row, m1);
	int b1rescolm1 = fincol(b1col, m1);
	if ((b1resrowm1>0) || (b1rescolm1>0)){ m1elimb1 = true; ++m1elimcount; }

	int b2row = growfromboxandpos(b, b2);
	int b2col = gcolfromboxandpos(b, b2);
	int b2resrowm1 = finrow(b2row, m1);
	int b2rescolm1 = fincol(b2col, m1);
	if ((b2resrowm1>0) || (b2rescolm1>0)){ m1elimb2 = true; ++m1elimcount; }

	int b3row = growfromboxandpos(b, b3);
	int b3col = gcolfromboxandpos(b, b3);
	int b3resrowm1 = finrow(b3row, m1);
	int b3rescolm1 = fincol(b3col, m1);
	if ((b3resrowm1>0) || (b3rescolm1>0)){ m1elimb3 = true; ++m1elimcount; }

	int b4row = growfromboxandpos(b, b4);
	int b4col = gcolfromboxandpos(b, b4);
	int b4resrowm1 = finrow(b4row, m1);
	int b4rescolm1 = fincol(b4col, m1);
	if ((b4resrowm1>0) || (b4rescolm1>0)){ m1elimb4 = true; ++m1elimcount; }

	if (m1elimcount == 3){
		if (m1elimb1 == false){ glastwrite = "4678         "; result = inspuzzle(b1row, b1col, m1); }
		if (m1elimb2 == false){ glastwrite = "4679         "; result = inspuzzle(b2row, b2col, m1); }
		if (m1elimb3 == false){ glastwrite = "4680         "; result = inspuzzle(b3row, b3col, m1); }
		if (m1elimb4 == false){ glastwrite = "4681         "; result = inspuzzle(b4row, b4col, m1); }
		;
		return result;
	}

	//**********************m2 procing
	int b1resrowm2 = finrow(b1row, m2);
	int b1rescolm2 = fincol(b1col, m2);
	if ((b1resrowm2>0) || (b1rescolm2>0)){ m2elimb1 = true; ++m2elimcount; }

	int b2resrowm2 = finrow(b2row, m2);
	int b2rescolm2 = fincol(b2col, m2);
	if ((b2resrowm2>0) || (b2rescolm2>0)){ m2elimb2 = true; ++m2elimcount; }

	int b3resrowm2 = finrow(b3row, m2);
	int b3rescolm2 = fincol(b3col, m2);
	if ((b3resrowm2>0) || (b3rescolm2>0)){ m2elimb3 = true; ++m2elimcount; }

	int b4resrowm2 = finrow(b4row, m2);
	int b4rescolm2 = fincol(b4col, m2);
	if ((b4resrowm2>0) || (b4rescolm2>0)){ m2elimb4 = true; ++m2elimcount; }

	if (m2elimcount == 3){
		if (m2elimb1 == false){ glastwrite = "4705         "; result = inspuzzle(b1row, b1col, m2); }
		if (m2elimb2 == false){ glastwrite = "4706         "; result = inspuzzle(b2row, b2col, m2); }
		if (m2elimb3 == false){ glastwrite = "4707         "; result = inspuzzle(b3row, b3col, m2); }
		if (m2elimb4 == false){ glastwrite = "4708         "; result = inspuzzle(b4row, b4col, m2); }

		return result;
	}

	//**********************m3 procing                              
	int b1resrowm3 = finrow(b1row, m3);
	int b1rescolm3 = fincol(b1col, m3);
	if ((b1resrowm3>0) || (b1rescolm3>0)){ m3elimb1 = true; ++m3elimcount; }

	int b2resrowm3 = finrow(b2row, m3);
	int b2rescolm3 = fincol(b2col, m3);
	if ((b2resrowm3>0) || (b2rescolm3>0)){ m3elimb2 = true; ++m3elimcount; }

	int b3resrowm3 = finrow(b3row, m3);
	int b3rescolm3 = fincol(b3col, m3);
	if ((b3resrowm3>0) || (b3rescolm3>0)){ m3elimb3 = true; ++m3elimcount; }

	int b4resrowm3 = finrow(b4row, m3);
	int b4rescolm3 = fincol(b4col, m3);
	if ((b4resrowm3>0) || (b4rescolm3>0)){ m3elimb4 = true; ++m3elimcount; }

	if (m3elimcount == 3){
		if (m3elimb1 == false){ glastwrite = "4732         "; result = inspuzzle(b1row, b1col, m3); }
		if (m3elimb2 == false){ glastwrite = "4733         "; result = inspuzzle(b2row, b2col, m3); }
		if (m3elimb3 == false){ glastwrite = "4734         "; result = inspuzzle(b3row, b3col, m3); }
		if (m3elimb4 == false){ glastwrite = "4735         "; result = inspuzzle(b4row, b4col, m3); }

		return result;
	}

	//**********************m4 procing                              
	int b1resrowm4 = finrow(b1row, m4);
	int b1rescolm4 = fincol(b1col, m4);
	if ((b1resrowm4>0) || (b1rescolm4>0)){ m4elimb1 = true; ++m4elimcount; }

	int b2resrowm4 = finrow(b2row, m4);
	int b2rescolm4 = fincol(b2col, m4);
	if ((b2resrowm4>0) || (b2rescolm4>0)){ m4elimb2 = true; ++m4elimcount; }

	int b3resrowm4 = finrow(b3row, m4);
	int b3rescolm4 = fincol(b3col, m4);
	if ((b3resrowm4>0) || (b3rescolm4>0)){ m4elimb3 = true; ++m4elimcount; }

	int b4resrowm4 = finrow(b4row, m4);
	int b4rescolm4 = fincol(b4col, m4);
	if ((b4resrowm4>0) || (b4rescolm4>0)){ m4elimb4 = true; ++m4elimcount; }

	if (m4elimcount == 3){
		if (m4elimb1 == false){ glastwrite = "4759         "; result = inspuzzle(b1row, b1col, m4); }
		if (m4elimb2 == false){ glastwrite = "4760         "; result = inspuzzle(b2row, b2col, m4); }
		if (m4elimb3 == false){ glastwrite = "4761        "; result = inspuzzle(b3row, b3col, m4); }
		if (m4elimb4 == false){ glastwrite = "4762         "; result = inspuzzle(b4row, b4col, m4); }

		return result;
	}
	return 0;
}
//==========================================================
//end boxcol3done4
//==========================================================
//==========================================================
int box2elimcol(int b){
	//==========================================================
	//   //cout<<"in function box2elimcol box="<<b<<endl;
	//	readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
	int result = 0;
	int m1 = 0; int m2 = 0; int m3 = 0;
	int mcount = gminbox(b, m1, m2, m3);
	if (mcount != 2){ return 0; }
	int firstbl = gfb(zbox, b);
	int lastbl = glastbl(zbox, b);
	if ((lastbl != firstbl + 3) && (lastbl != firstbl + 6)){ return 0; }
	//simple row elim
	int b1row = growfromboxandpos(b, firstbl);
	int b1col = gcolfromboxandpos(b, firstbl);
	int b2row = growfromboxandpos(b, lastbl);
	int b2col = gcolfromboxandpos(b, lastbl);
	int resm1b1 = finrow(b1row, m1);
	int resm2b1 = finrow(b1row, m2);
	int resm1b2 = finrow(b2row, m1);
	int resm2b2 = finrow(b2row, m2);
	if (resm1b1>0){
		if (puzzle[b1row][b1col] != 0){ return 0; }
		glastwrite = "4800         "; result = inspuzzle(b1row, b1col, m2);
		;
		return result;
	}
	if (resm2b1>0){
		 glastwrite = "4806         "; result = inspuzzle(b1row, b1col, m1);
		;
		return result;
	}
	if (resm1b2>0){
		glastwrite = "4812         "; result = inspuzzle(b2row, b2col, m2);
		;
		return result;
	}
	if (resm2b2>0){
		glastwrite = "4818         "; result = inspuzzle(b2row, b2col, m1);
		;
		return result;
	}

	return 0;
}
//==========================================================
//end box2elimcol
//==========================================================   

//==========================================================
int boxelimc2done(int b){
	//==========================================================
	//	readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
//	init_box(b);

	int result = 0;
	if (box[b].done == true){ return 0; }

	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	int bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	int peer1 = 0;
	int peer2 = 0;

	if (mcount<2){ return 0; }

	if (mcount>5){ return 0; }
	int c2bcnt = 0;
	switch (b){
	case 7:peer1 = 4; peer2 = 1; break;
	case 1:peer1 = 4; peer2 = 7; break;
	case 4:peer1 = 1; peer2 = 7; break;

	case 8:peer1 = 5; peer2 = 2; break;
	case 2:peer1 = 5; peer2 = 8; break;
	case 5:peer1 = 2; peer2 = 8; break;

	case 9:peer1 = 6; peer2 = 3; break;
	case 3:peer1 = 6; peer2 = 9; break;
	case 6:peer1 = 3; peer2 = 9; break;
	}

	if (box[peer1].c2done == false){
		//swap peer 1 and peer 2 and check c2done again.  then erase peer 2 function altogher 	
		int savepeer1 = peer1;
		peer1 = peer2;
		peer2 = savepeer1;
		if (box[peer1].c2done == false){ return 0; }
		//brilliant!
	}
	if (box[b].c2done == true){ return 0; }
	int c1resm1 = 0; int c1resm2 = 0; int c1resm3 = 0; int c1resm4 = 0;
	//g columns for box and pos
	int boxc1 = gcolfromboxandpos(b, 1);
	int boxc2 = boxc1 + 1;
	int boxc3 = boxc1 + 2;


	if (mcount<2){ return 0; }

	if (mcount>5){ return 0; }
	c2bcnt = 0;

	if (box[b].c2[1] == 0){ ++c2bcnt; }
	if (box[b].c2[2] == 0){ ++c2bcnt; }
	if (box[b].c2[3] == 0){ ++c2bcnt; }

	int targbl = 0;
	int targrow = 0;
	int targcol = boxc2;
	int boxr1 = growfromboxandpos(b, 1);
	int boxr2 = boxr1 + 1;
	int boxr3 = boxr1 + 2;

	if (c2bcnt == 1){

		if (box[b].c2[1] == 0){ targrow = boxr1; }
		else {
			if (box[b].c2[2] == 0){ targrow = boxr2; }
			else { if (box[b].c2[3] == 0){ targrow = boxr3; } }
		}
	}


	int r1resm1 = 0; int r1resm2 = 0; int r1resm3 = 0; int r1resm4 = 0; int r1resm5 = 0;
	int r2resm1 = 0; int r2resm2 = 0; int r2resm3 = 0; int r2resm4 = 0; int r2resm5 = 0;
	int r3resm1 = 0; int r3resm2 = 0; int r3resm3 = 0; int r3resm4 = 0; int r3resm5 = 0;

	if (c2bcnt>1){ //set up for elimination...

		r1resm1 = finrow(boxr1, m1);
		r1resm2 = finrow(boxr1, m2);
		if (mcount>2){ r1resm3 = finrow(boxr1, m3); }
		if (mcount>3){ r1resm4 = finrow(boxr1, m4); }
		if (mcount>4){ r1resm5 = finrow(boxr1, m5); }


		r2resm1 = finrow(boxr2, m1);
		r2resm2 = finrow(boxr2, m2);
		if (mcount>2){ r2resm3 = finrow(boxr2, m3); }
		if (mcount>3){ r2resm4 = finrow(boxr2, m4); }
		if (mcount>4){ r2resm5 = finrow(boxr2, m5); }

		r3resm1 = finrow(boxr3, m1);
		r3resm2 = finrow(boxr3, m2);
		if (mcount>2){ r3resm3 = finrow(boxr3, m3); }
		if (mcount>3){ r3resm4 = finrow(boxr3, m4); }
		if (mcount>4){ r3resm5 = finrow(boxr3, m5); }
		//if c2bl>1 defer assignment of targbl till later...
	}

	//==================m1 procing==========================
	//check to make sure m1 is either in peer1 or peer2
	int peer1resm1 = finbox(peer1, m1);
	int peer2resm1 = finbox(peer2, m1);
	if (((peer1resm1>0) && (!box[peer1].c2done)) || (peer2resm1>0) && ((!box[peer2].c2done))) {//continue with m1
		//make sure m1 is not already in column boxc2
		result = fincol(boxc2, m1);
		if (result == 0){//continue 
			if (targrow == 0){//c2bcnt>1 		        	 
				if ((!box[b].c2[1]) && (!r1resm1)){
					if ((r2resm1>0) && (r3resm1>0))     { targrow = boxr1; }
					if ((r2resm1>0) && (box[b].c2[3]>0)){ targrow = boxr1; }
					if ((r3resm1>0) && (box[b].c2[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((!box[b].c2[2]) && (!r2resm1)){
						if ((r1resm1>0) && (r3resm1>0))     { targrow = boxr2; }
						if ((r1resm1>0) && (box[b].c2[3]>0)){ targrow = boxr2; }
						if ((r3resm1>0) && (box[b].c2[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((!box[b].c2[3]) && (!r3resm1)){
							if ((r1resm1>0) && (r2resm1>0))   { targrow = boxr3; }
							if ((r1resm1>0) && (box[b].c2[2]>0)){ targrow = boxr3; }
							if ((r2resm1>0) && (box[b].c2[1]>0)){ targrow = boxr3; }
						}
					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "5049         "; result = inspuzzle(targrow, targcol, m1);
				;
				return result;
			}
		}
	}

	//==================m2 procing==========================
	//check to make sure m2 is either in peer1 or peer2
	int peer1resm2 = finbox(peer1, m2);
	int peer2resm2 = finbox(peer2, m2);
	if (((peer1resm2>0) && (box[peer1].c2done == false)) || (peer2resm2>0) && ((box[peer2].c2done == false))) {//continue with m2

		//make sure m2 is not already in column boxc2
		result = fincol(boxc2, m2);
		if (result == 0){//continue 
			if (targrow == 0){//c2bcnt>1 		        	 
				if ((box[b].c2[1] == 0) && (r1resm2 == 0)){
					if ((r2resm2>0) && (r3resm2>0))     { targrow = boxr1; }
					if ((r2resm2>0) && (box[b].c2[3]>0)){ targrow = boxr1; }
					if ((r3resm2>0) && (box[b].c2[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c2[2] == 0) && (r2resm2 == 0)){
						if ((r1resm2>0) && (r3resm2>0))     { targrow = boxr2; }
						if ((r1resm2>0) && (box[b].c2[3]>0)){ targrow = boxr2; }
						if ((r3resm2>0) && (box[b].c2[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c2[3] == 0) && (r3resm2 == 0)){
							if ((r1resm2>0) && (r2resm2>0))   { targrow = boxr3; }
							if ((r1resm2>0) && (box[b].c2[2]>0)){ targrow = boxr3; }
							if ((r2resm2>0) && (box[b].c2[1]>0)){ targrow = boxr3; }
						}
					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "5095         "; result = inspuzzle(targrow, targcol, m2);
				;
				return result;
			}
		}
	}
	if (mcount<3){ return 0; }
	//==================m3 procing==========================
	//check to make sure m3 is either in peer1 or peer2
	int peer1resm3 = finbox(peer1, m3);
	int peer2resm3 = finbox(peer2, m3);
	if (((peer1resm3>0) && (box[peer1].c2done == false)) || (peer2resm3>0) && ((box[peer2].c2done == false))) {//continue with m3

		//make sure m3 is not already in column boxc2
		result = fincol(boxc2, m3);
		if (result == 0){//continue 
			if (targrow == 0){//c2bcnt>1 		        	 
				if ((box[b].c2[1] == 0) && (r1resm3 == 0)){
					if ((r2resm3>0) && (r3resm3>0))     { targrow = boxr1; }
					if ((r2resm3>0) && (box[b].c2[3]>0)){ targrow = boxr1; }
					if ((r3resm3>0) && (box[b].c2[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c2[2] == 0) && (r2resm3 == 0)){
						if ((r1resm3>0) && (r3resm3>0))     { targrow = boxr2; }
						if ((r1resm3>0) && (box[b].c2[3]>0)){ targrow = boxr2; }
						if ((r3resm3>0) && (box[b].c2[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c2[3] == 0) && (r3resm3 == 0)){
							if ((r1resm3>0) && (r2resm3>0))   { targrow = boxr3; }
							if ((r1resm3>0) && (box[b].c2[2]>0)){ targrow = boxr3; }
							if ((r2resm3>0) && (box[b].c2[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "5142         "; result = inspuzzle(targrow, targcol, m3);
				;
				return result;
			}
		}
	}

	if (mcount<4){ return 0; }

	//==================m4 procing==========================
	//check to make sure m4 is either in peer1 or peer2
	int peer1resm4 = finbox(peer1, m4);
	int peer2resm4 = finbox(peer2, m4);
	if (((peer1resm4>0) && (box[peer1].c2done == false)) || (peer2resm4>0) && ((box[peer2].c2done == false))) {//continue with m2

		//make sure m4 is not already in column boxc2
		result = fincol(boxc2, m4);
		if (result == 0){//continue 
			if (targrow == 0){//c2bcnt>1 		        	 
				if ((box[b].c2[1] == 0) && (r1resm4 == 0)){
					if ((r2resm4>0) && (r3resm4>0))     { targrow = boxr1; }
					if ((r2resm4>0) && (box[b].c2[3]>0)){ targrow = boxr1; }
					if ((r3resm4>0) && (box[b].c2[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c2[2] == 0) && (r2resm4 == 0)){
						if ((r1resm4>0) && (r3resm4>0))     { targrow = boxr2; }
						if ((r1resm4>0) && (box[b].c2[3]>0)){ targrow = boxr2; }
						if ((r3resm4>0) && (box[b].c2[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c2[3] == 0) && (r3resm4 == 0)){
							if ((r1resm4>0) && (r2resm4>0))   { targrow = boxr3; }
							if ((r1resm4>0) && (box[b].c2[2]>0)){ targrow = boxr3; }
							if ((r2resm4>0) && (box[b].c2[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "5191         "; result = inspuzzle(targrow, targcol, m4);
				;
				return result;
			}
		}
	}


	if (mcount<5){ return 0; }
	//==================m5 procing==========================
	//check to make sure m5 is either in peer1 or peer2
	int peer1resm5 = finbox(peer1, m5);
	int peer2resm5 = finbox(peer2, m5);
	if (((peer1resm5>0) && (box[peer1].c2done == false)) || ((peer2resm5>0) && (box[peer2].c2done == false))) {//continue with m5

		//make sure m5 is not already in column boxc2
		result = fincol(boxc2, m5);
		if (result == 0){//continue 
			if (targrow == 0){//c2bcnt>1 		        	 
				if ((box[b].c2[1] == 0) && (r1resm5 == 0)){
					if ((r2resm5>0) && (r3resm5>0))     { targrow = boxr1; }
					if ((r2resm5>0) && (box[b].c2[3]>0)){ targrow = boxr1; }
					if ((r3resm5>0) && (box[b].c2[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c2[2] == 0) && (r2resm5 == 0)){
						if ((r1resm5>0) && (r3resm5>0))     { targrow = boxr2; }
						if ((r1resm5>0) && (box[b].c2[3]>0)){ targrow = boxr2; }
						if ((r3resm5>0) && (box[b].c2[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c2[3] == 0) && (r3resm5 == 0)){
							if ((r1resm5>0) && (r2resm5>0))   { targrow = boxr3; }
							if ((r1resm5>0) && (box[b].c2[2]>0)){ targrow = boxr3; }
							if ((r2resm5>0) && (box[b].c2[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "5240         "; result = inspuzzle(targrow, targcol, m5);
				;
				return result;
			}
		}
	}

	return 0;
}
//==========================================================
//end boxelimc2done
//========================================================== 

//==========================================================
int boxelimr2done(int b){
	//==========================================================
	//	readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
//	init_box(b);

	int result = 0;
	if (box[b].done == true){ return 0; }

	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	int bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	int peer1 = 0;
	int peer2 = 0;
	switch (b){
	case 1:peer1 = 2; peer2 = 3; break;
	case 2:peer1 = 1; peer2 = 3; break;
	case 3:peer1 = 2; peer2 = 1; break;

	case 4:peer1 = 5; peer2 = 6; break;
	case 5:peer1 = 4; peer2 = 6; break;
	case 6:peer1 = 5; peer2 = 4; break;

	case 7:peer1 = 8; peer2 = 9; break;
	case 8:peer1 = 7; peer2 = 9; break;
	case 9:peer1 = 8; peer2 = 7; break;
	}

	if (box[peer1].r2done == false){
		//swap peer 1 and peer 2 and check r2done again.  then erase peer 2 function altogher 	
		int savepeer1 = peer1;
		peer1 = peer2;
		peer2 = savepeer1;
		if (box[peer1].r2done == false){ return 0; }
		//brilliant!
	}
	if (box[b].r2done == true){ return 0; }
	int r1resm1 = 0; int r1resm2 = 0; int r1resm3 = 0; int r1resm4 = 0;
	//g rows for box and pos
	int boxr1 = growfromboxandpos(b, 1);
	int boxr2 = boxr1 + 1;
	int boxr3 = boxr1 + 2;


	if (mcount<2){ return 0; }

	if (mcount>5){ return 0; }
	int r2bcnt = 0;

	if (box[b].r2[1] == 0){ ++r2bcnt; }
	if (box[b].r2[2] == 0){ ++r2bcnt; }
	if (box[b].r2[3] == 0){ ++r2bcnt; }

	int targbl = 0;
	int targcol = 0;
	int targrow = boxr2;
	int boxc1 = gcolfromboxandpos(b, 1);
	int boxc2 = boxc1 + 1;
	int boxc3 = boxc1 + 2;

	if (r2bcnt == 1){

		if (box[b].r2[1] == 0){ targcol = boxc1; }
		else {
			if (box[b].r2[2] == 0){ targcol = boxc2; }
			else { if (box[b].r2[3] == 0){ targcol = boxc3; } }
		}
	}


	int c1resm1 = 0; int c1resm2 = 0; int c1resm3 = 0; int c1resm4 = 0; int c1resm5 = 0;
	int c2resm1 = 0; int c2resm2 = 0; int c2resm3 = 0; int c2resm4 = 0; int c2resm5 = 0;
	int c3resm1 = 0; int c3resm2 = 0; int c3resm3 = 0; int c3resm4 = 0; int c3resm5 = 0;

	if (r2bcnt>1){ //set up for elimination...

		c1resm1 = fincol(boxc1, m1);
		c1resm2 = fincol(boxc1, m2);
		if (mcount>2){ c1resm3 = fincol(boxc1, m3); }
		if (mcount>3){ c1resm4 = fincol(boxc1, m4); }
		if (mcount>4){ c1resm5 = fincol(boxc1, m5); }


		c2resm1 = fincol(boxc2, m1);
		c2resm2 = fincol(boxc2, m2);
		if (mcount>2){ c2resm3 = fincol(boxc2, m3); }
		if (mcount>3){ c2resm4 = fincol(boxc2, m4); }
		if (mcount>4){ c2resm5 = fincol(boxc2, m5); }

		c3resm1 = fincol(boxc3, m1);
		c3resm2 = fincol(boxc3, m2);
		if (mcount>2){ c3resm3 = fincol(boxc3, m3); }
		if (mcount>3){ c3resm4 = fincol(boxc3, m4); }
		if (mcount>4){ c3resm5 = fincol(boxc3, m5); }

		//if r2bl>1 defer assignment of targbl till later...
	}
	//==================m1 procing==========================
	//check to make sure m1 is either in peer1 or peer2
	int peer1resm1 = finbox(peer1, m1);
	int peer2resm1 = finbox(peer2, m1);
	if (((peer1resm1>0) && (box[peer1].r2done == false)) || (peer2resm1>0) && ((box[peer2].r2done == false))) {//continue with m1
		//make sure m1 is not already in row boxr2
		result = finrow(boxr2, m1);
		if (result == 0){//continue 
			if (targcol == 0){//r2bcnt>1 		        	 
				if ((box[b].r2[1] == 0) && (c1resm1 == 0)){
					if ((c2resm1>0) && (c3resm1>0))     { targcol = boxc1; }
					if ((c2resm1>0) && (box[b].r2[3]>0)){ targcol = boxc1; }
					if ((c3resm1>0) && (box[b].r2[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r2[2] == 0) && (c2resm1 == 0)){
						if ((c1resm1>0) && (c3resm1>0))     { targcol = boxc2; }
						if ((c1resm1>0) && (box[b].r2[3]>0)){ targcol = boxc2; }
						if ((c3resm1>0) && (box[b].r2[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r2[3] == 0) && (c3resm1 == 0)){
							if ((c1resm1>0) && (c2resm1>0))   { targcol = boxc3; }
							if ((c1resm1>0) && (box[b].r2[2]>0)){ targcol = boxc3; }
							if ((c2resm1>0) && (box[b].r2[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "5399         "; result = inspuzzle(targrow, targcol, m1);
				;
				return result;
			}
		}
	}

	//==================m2 procing==========================
	//check to make sure m2 is either in peer1 or peer2
	int peer1resm2 = finbox(peer1, m2);
	int peer2resm2 = finbox(peer2, m2);
	if (((peer1resm2>0) && (box[peer1].r2done == false)) || (peer2resm2>0) && ((box[peer2].r2done == false))) {//continue with m2

		//make sure m2 is not already in row boxr2
		result = finrow(boxr2, m2);
		if (result == 0){//continue 
			if (targcol == 0){//r2bcnt>1 		        	 
				if ((box[b].r2[1] == 0) && (c1resm2 == 0)){
					if ((c2resm2>0) && (c3resm2>0))     { targcol = boxc1; }
					if ((c2resm2>0) && (box[b].r2[3]>0)){ targcol = boxc1; }
					if ((c3resm2>0) && (box[b].r2[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r2[2] == 0) && (c2resm2 == 0)){
						if ((c1resm2>0) && (c3resm2>0))     { targcol = boxc2; }
						if ((c1resm2>0) && (box[b].r2[3]>0)){ targcol = boxc2; }
						if ((c3resm2>0) && (box[b].r2[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r2[3] == 0) && (c3resm2 == 0)){
							if ((c1resm2>0) && (c2resm2>0))   { targcol = boxc3; }
							if ((c1resm2>0) && (box[b].r2[2]>0)){ targcol = boxc3; }
							if ((c2resm2>0) && (box[b].r2[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "5446         "; result = inspuzzle(targrow, targcol, m2);
				;
				return result;
			}
		}
	}
	if (mcount<3){ return 0; }
	//==================m3 procing==========================
	//check to make sure m3 is either in peer1 or peer2
	int peer1resm3 = finbox(peer1, m3);
	int peer2resm3 = finbox(peer2, m3);
	if (((peer1resm3>0) && (box[peer1].r2done == false)) || (peer2resm3>0) && ((box[peer2].r2done == false))) {//continue with m3

		//make sure m3 is not already in row boxr2
		result = finrow(boxr2, m3);
		if (result == 0){//continue 
			if (targcol == 0){//r2bcnt>1 		        	 
				if ((box[b].r2[1] == 0) && (c1resm3 == 0)){
					if ((c2resm3>0) && (c3resm3>0))     { targcol = boxc1; }
					if ((c2resm3>0) && (box[b].r2[3]>0)){ targcol = boxc1; }
					if ((c3resm3>0) && (box[b].r2[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r2[2] == 0) && (c2resm3 == 0)){
						if ((c1resm3>0) && (c3resm3>0))     { targcol = boxc2; }
						if ((c1resm3>0) && (box[b].r2[3]>0)){ targcol = boxc2; }
						if ((c3resm3>0) && (box[b].r2[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r2[3] == 0) && (c3resm3 == 0)){
							if ((c1resm3>0) && (c2resm3>0))   { targcol = boxc3; }
							if ((c1resm3>0) && (box[b].r2[2]>0)){ targcol = boxc3; }
							if ((c2resm3>0) && (box[b].r2[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "5493         "; result = inspuzzle(targrow, targcol, m3);
				;
				return result;
			}
		}
	}

	if (mcount<4){ return 0; }

	//==================m4 procing==========================
	//check to make sure m4 is either in peer1 or peer2
	int peer1resm4 = finbox(peer1, m4);
	int peer2resm4 = finbox(peer2, m4);
	if (((peer1resm4>0) && (box[peer1].r2done == false)) || (peer2resm4>0) && ((box[peer2].r2done == false))) {//continue with m2

		//make sure m4 is not already in row boxr2
		result = finrow(boxr2, m4);
		if (result == 0){//continue 
			if (targcol == 0){//r2bcnt>1 		        	 
				if ((box[b].r2[1] == 0) && (c1resm4 == 0)){
					if ((c2resm4>0) && (c3resm4>0))     { targcol = boxc1; }
					if ((c2resm4>0) && (box[b].r2[3]>0)){ targcol = boxc1; }
					if ((c3resm4>0) && (box[b].r2[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r2[2] == 0) && (c2resm4 == 0)){
						if ((c1resm4>0) && (c3resm4>0))     { targcol = boxc2; }
						if ((c1resm4>0) && (box[b].r2[3]>0)){ targcol = boxc2; }
						if ((c3resm4>0) && (box[b].r2[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r2[3] == 0) && (c3resm4 == 0)){
							if ((c1resm4>0) && (c2resm4>0))   { targcol = boxc3; }
							if ((c1resm4>0) && (box[b].r2[2]>0)){ targcol = boxc3; }
							if ((c2resm4>0) && (box[b].r2[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "5542         "; result = inspuzzle(targrow, targcol, m4);
				;
				return result;
			}
		}
	}


	if (mcount<5){ return 0; }
	//==================m5 procing==========================
	//check to make sure m5 is either in peer1 or peer2
	int peer1resm5 = finbox(peer1, m5);
	int peer2resm5 = finbox(peer2, m5);
	if (((peer1resm5>0) && (box[peer1].r2done == false)) || ((peer2resm5>0) && (box[peer2].r2done == false))) {//continue with m5

		//make sure m5 is not already in row boxr2
		result = finrow(boxr2, m5);
		if (result == 0){//continue 
			if (targcol == 0){//r2bcnt>1 		        	 
				if ((box[b].r2[1] == 0) && (c1resm5 == 0)){
					if ((c2resm5>0) && (c3resm5>0))     { targcol = boxc1; }
					if ((c2resm5>0) && (box[b].r2[3]>0)){ targcol = boxc1; }
					if ((c3resm5>0) && (box[b].r2[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r2[2] == 0) && (c2resm5 == 0)){
						if ((c1resm5>0) && (c3resm5>0))     { targcol = boxc2; }
						if ((c1resm5>0) && (box[b].r2[3]>0)){ targcol = boxc2; }
						if ((c3resm5>0) && (box[b].r2[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r2[3] == 0) && (c3resm5 == 0)){
							if ((c1resm5>0) && (c2resm5>0))   { targcol = boxc3; }
							if ((c1resm5>0) && (box[b].r2[2]>0)){ targcol = boxc3; }
							if ((c2resm5>0) && (box[b].r2[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				//cout<<"insert line 8479 function boxelimr2done m5 box="<<b<<endl;
				glastwrite = "5591         "; result = inspuzzle(targrow, targcol, m5);
				;
				return result;
			}
		}
	}

	return 0;
}
//==========================================================
//end boxelimr2done
//========================================================== 
//==========================================================
int boxelimr1done(int b){
	//==========================================================
	//readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
//	init_box(b);

	int result = 0;
	if (box[b].done == true){ return 0; }

	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	int bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	int peer1 = 0;
	int peer2 = 0;
	switch (b){
	case 1:peer1 = 2; peer2 = 3; break;
	case 2:peer1 = 1; peer2 = 3; break;
	case 3:peer1 = 2; peer2 = 1; break;

	case 4:peer1 = 5; peer2 = 6; break;
	case 5:peer1 = 4; peer2 = 6; break;
	case 6:peer1 = 5; peer2 = 4; break;

	case 7:peer1 = 8; peer2 = 9; break;
	case 8:peer1 = 7; peer2 = 9; break;
	case 9:peer1 = 8; peer2 = 7; break;
	}

	if (box[peer1].r1done == false){
		//swap peer 1 and peer 2 and check r1done again.  then erase peer 2 function altogher 	
		int savepeer1 = peer1;
		peer1 = peer2;
		peer2 = savepeer1;
		if (box[peer1].r1done == false){ return 0; }
		//brilliant!
	}
	if (box[b].r1done == true){ return 0; }
	int r1resm1 = 0; int r1resm2 = 0; int r1resm3 = 0; int r1resm4 = 0;
	//g rows for box and pos
	int boxr1 = growfromboxandpos(b, 1);
	int boxr2 = boxr1 + 1;
	int boxr3 = boxr1 + 2;


	if (mcount<2){ return 0; }

	if (mcount>5){ return 0; }
	int r1bcnt = 0;

	if (box[b].r1[1] == 0){ ++r1bcnt; }
	if (box[b].r1[2] == 0){ ++r1bcnt; }
	if (box[b].r1[3] == 0){ ++r1bcnt; }

	int targbl = 0;
	int targcol = 0;
	int targrow = boxr1;
	int boxc1 = gcolfromboxandpos(b, 1);
	int boxc2 = boxc1 + 1;
	int boxc3 = boxc1 + 2;

	if (r1bcnt == 1){

		if (box[b].r1[1] == 0){ targcol = boxc1; }
		else {
			if (box[b].r1[2] == 0){ targcol = boxc2; }
			else { if (box[b].r1[3] == 0){ targcol = boxc3; } }
		}
	}


	int c1resm1 = 0; int c1resm2 = 0; int c1resm3 = 0; int c1resm4 = 0; int c1resm5 = 0;
	int c2resm1 = 0; int c2resm2 = 0; int c2resm3 = 0; int c2resm4 = 0; int c2resm5 = 0;
	int c3resm1 = 0; int c3resm2 = 0; int c3resm3 = 0; int c3resm4 = 0; int c3resm5 = 0;

	if (r1bcnt>1){ //set up for elimination...

		c1resm1 = fincol(boxc1, m1);
		c1resm2 = fincol(boxc1, m2);
		if (mcount>2){ c1resm3 = fincol(boxc1, m3); }
		if (mcount>3){ c1resm4 = fincol(boxc1, m4); }
		if (mcount>4){ c1resm5 = fincol(boxc1, m5); }


		c2resm1 = fincol(boxc2, m1);
		c2resm2 = fincol(boxc2, m2);
		if (mcount>2){ c2resm3 = fincol(boxc2, m3); }
		if (mcount>3){ c2resm4 = fincol(boxc2, m4); }
		if (mcount>4){ c2resm5 = fincol(boxc2, m5); }

		c3resm1 = fincol(boxc3, m1);
		c3resm2 = fincol(boxc3, m2);
		if (mcount>2){ c3resm3 = fincol(boxc3, m3); }
		if (mcount>3){ c3resm4 = fincol(boxc3, m4); }
		if (mcount>4){ c3resm5 = fincol(boxc3, m5); }
		//if r1bl>1 defer assignment of targbl till later...
	}

	//==================m1 procing==========================
	//check to make sure m1 is either in peer1 or peer2
	int peer1resm1 = finbox(peer1, m1);
	int peer2resm1 = finbox(peer2, m1);
	if (((peer1resm1>0) && (box[peer1].r1done == false)) || (peer2resm1>0) && ((box[peer2].r1done == false))) {//continue with m1
		//make sure m1 is not already in row boxr1
		result = finrow(boxr1, m1);
		if (result == 0){//continue 
			if (targcol == 0){//r1bcnt>1 		        	 3321

				if ((box[b].r1[1] == 0) && (c1resm1 == 0)){
					if ((c2resm1>0) && (c3resm1>0))     { targcol = boxc1; }
					if ((c2resm1>0) && (box[b].r1[3]>0)){ targcol = boxc1; }
					if ((c3resm1>0) && (box[b].r1[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r1[2] == 0) && (c2resm1 == 0)){
						if ((c1resm1>0) && (c3resm1>0))     { targcol = boxc2; }
						if ((c1resm1>0) && (box[b].r1[3]>0)){ targcol = boxc2; }
						if ((c3resm1>0) && (box[b].r1[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r1[3] == 0) && (c3resm1 == 0)){
							if ((c1resm1>0) && (c2resm1>0))   { targcol = boxc3; }
							if ((c1resm1>0) && (box[b].r1[2]>0)){ targcol = boxc3; }
							if ((c2resm1>0) && (box[b].r1[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "xxxx   "; result = inspuzzle(targrow, targcol, m1);
				;
				return result;
			}
		}
	}

	//==================m2 procing==========================
	//check to make sure m2 is either in peer1 or peer2
	int peer1resm2 = finbox(peer1, m2);
	int peer2resm2 = finbox(peer2, m2);
	if (((peer1resm2>0) && (box[peer1].r1done == false)) || (peer2resm2>0) && ((box[peer2].r1done == false))) {//continue with m2

		//make sure m2 is not already in row boxr1
		result = finrow(boxr1, m2);
		if (result == 0){//continue 
			if (targcol == 0){//r1bcnt>1 		        	 
				if ((box[b].r1[1] == 0) && (c1resm2 == 0)){
					if ((c2resm2>0) && (c3resm2>0))     { targcol = boxc1; }
					if ((c2resm2>0) && (box[b].r1[3]>0)){ targcol = boxc1; }
					if ((c3resm2>0) && (box[b].r1[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r1[2] == 0) && (c2resm2 == 0)){
						if ((c1resm2>0) && (c3resm2>0))     { targcol = boxc2; }
						if ((c1resm2>0) && (box[b].r1[3]>0)){ targcol = boxc2; }
						if ((c3resm2>0) && (box[b].r1[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r1[3] == 0) && (c3resm2 == 0)){
							if ((c1resm2>0) && (c2resm2>0))   { targcol = boxc3; }
							if ((c1resm2>0) && (box[b].r1[2]>0)){ targcol = boxc3; }
							if ((c2resm2>0) && (box[b].r1[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "5802         "; result = inspuzzle(targrow, targcol, m2);
				;
				return result;
			}
		}
	}
	if (mcount<3){ return 0; }
	//==================m3 procing==========================
	//check to make sure m3 is either in peer1 or peer2
	int peer1resm3 = finbox(peer1, m3);
	int peer2resm3 = finbox(peer2, m3);
	if (((peer1resm3>0) && (box[peer1].r1done == false)) || (peer2resm3>0) && ((box[peer2].r1done == false))) {//continue with m3

		//make sure m3 is not already in row boxr1
		result = finrow(boxr1, m3);
		if (result == 0){//continue 
			if (targcol == 0){//r1bcnt>1 		        	 
				if ((box[b].r1[1] == 0) && (c1resm3 == 0)){
					if ((c2resm3>0) && (c3resm3>0))     { targcol = boxc1; }
					if ((c2resm3>0) && (box[b].r1[3]>0)){ targcol = boxc1; }
					if ((c3resm3>0) && (box[b].r1[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r1[2] == 0) && (c2resm3 == 0)){
						if ((c1resm3>0) && (c3resm3>0))     { targcol = boxc2; }
						if ((c1resm3>0) && (box[b].r1[3]>0)){ targcol = boxc2; }
						if ((c3resm3>0) && (box[b].r1[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r1[3] == 0) && (c3resm3 == 0)){
							if ((c1resm3>0) && (c2resm3>0))   { targcol = boxc3; }
							if ((c1resm3>0) && (box[b].r1[2]>0)){ targcol = boxc3; }
							if ((c2resm3>0) && (box[b].r1[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "5852         "; result = inspuzzle(targrow, targcol, m3);
				;
				return result;
			}
		}
	}

	if (mcount<4){ return 0; }

	//==================m4 procing==========================
	//check to make sure m4 is either in peer1 or peer2
	int peer1resm4 = finbox(peer1, m4);
	int peer2resm4 = finbox(peer2, m4);
	if (((peer1resm4>0) && (box[peer1].r1done == false)) || (peer2resm4>0) && ((box[peer2].r1done == false))) {//continue with m2

		//make sure m4 is not already in row boxr1
		result = finrow(boxr1, m4);
		if (result == 0){//continue 
			if (targcol == 0){//r1bcnt>1 		        	 
				if ((box[b].r1[1] == 0) && (c1resm4 == 0)){
					if ((c2resm4>0) && (c3resm4>0))     { targcol = boxc1; }
					if ((c2resm4>0) && (box[b].r1[3]>0)){ targcol = boxc1; }
					if ((c3resm4>0) && (box[b].r1[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r1[2] == 0) && (c2resm4 == 0)){
						if ((c1resm4>0) && (c3resm4>0))     { targcol = boxc2; }
						if ((c1resm4>0) && (box[b].r1[3]>0)){ targcol = boxc2; }
						if ((c3resm4>0) && (box[b].r1[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r1[3] == 0) && (c3resm4 == 0)){
							if ((c1resm4>0) && (c2resm4>0))   { targcol = boxc3; }
							if ((c1resm4>0) && (box[b].r1[2]>0)){ targcol = boxc3; }
							if ((c2resm4>0) && (box[b].r1[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "5904         "; result = inspuzzle(targrow, targcol, m4);
				;
				return result;
			}
		}
	}


	if (mcount<5){ return 0; }
	//==================m5 procing==========================
	//check to make sure m5 is either in peer1 or peer2
	int peer1resm5 = finbox(peer1, m5);
	int peer2resm5 = finbox(peer2, m5);
	if (((peer1resm5>0) && (box[peer1].r1done == false)) || ((peer2resm5>0) && (box[peer2].r1done == false))) {//continue with m5

		//make sure m5 is not already in row boxr1
		result = finrow(boxr1, m5);
		if (result == 0){//continue 
			if (targcol == 0){//r1bcnt>1 		        	 
				if ((box[b].r1[1] == 0) && (c1resm5 == 0)){
					if ((c2resm5>0) && (c3resm5>0))     { targcol = boxc1; }
					if ((c2resm5>0) && (box[b].r1[3]>0)){ targcol = boxc1; }
					if ((c3resm5>0) && (box[b].r1[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r1[2] == 0) && (c2resm5 == 0)){
						if ((c1resm5>0) && (c3resm5>0))     { targcol = boxc2; }
						if ((c1resm5>0) && (box[b].r1[3]>0)){ targcol = boxc2; }
						if ((c3resm5>0) && (box[b].r1[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r1[3] == 0) && (c3resm5 == 0)){
							if ((c1resm5>0) && (c2resm5>0))   { targcol = boxc3; }
							if ((c1resm5>0) && (box[b].r1[2]>0)){ targcol = boxc3; }
							if ((c2resm5>0) && (box[b].r1[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				//cout<<"insert line 8871 function boxelimr1done m5 box="<<b<<endl;
				glastwrite = "5956         "; result = inspuzzle(targrow, targcol, m5);
				;
				return result;
			}
		}
	}

	return 0;
}
//==========================================================
//end boxelimr1done
//==========================================================   
//==========================================================
int boxelimr3done(int b){
	//==========================================================
	//	readpuzzle();
	//box[b].bcnt = 0;
//	readbox(b);
//	init_box(b);

	int result = 0;
	//  //cout<<"in function boxelimr3done box="<<b<<endl;
	if (box[b].done == true){ return 0; }

	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	int bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	int peer1 = 0;
	int peer2 = 0;
	switch (b){
	case 1:peer1 = 2; peer2 = 3; break;
	case 2:peer1 = 1; peer2 = 3; break;
	case 3:peer1 = 2; peer2 = 1; break;

	case 4:peer1 = 5; peer2 = 6; break;
	case 5:peer1 = 4; peer2 = 6; break;
	case 6:peer1 = 5; peer2 = 4; break;

	case 7:peer1 = 8; peer2 = 9; break;
	case 8:peer1 = 7; peer2 = 9; break;
	case 9:peer1 = 8; peer2 = 7; break;
	}

	if (box[peer1].r3done == false){
		//swap peer 1 and peer 2 and check r3done again.  then erase peer 2 function altogher 	
		int savepeer1 = peer1;
		peer1 = peer2;
		peer2 = savepeer1;
		if (box[peer1].r3done == false){ return 0; }
		//brilliant!
	}
	if (box[b].r3done == true){ return 0; }
	int r3resm1 = 0; int r3resm2 = 0; int r3resm3 = 0; int r3resm4 = 0;
	//g rows for box and pos
	int boxr1 = growfromboxandpos(b, 1);
	int boxr2 = boxr1 + 1;
	int boxr3 = boxr1 + 2;


	if (mcount<2){ return 0; }

	if (mcount>5){ return 0; }
	int r3bcnt = 0;

	if (box[b].r3[1] == 0){ ++r3bcnt; }
	if (box[b].r3[2] == 0){ ++r3bcnt; }
	if (box[b].r3[3] == 0){ ++r3bcnt; }

	int targbl = 0;
	int targcol = 0;
	int targrow = boxr3;
	int boxc1 = gcolfromboxandpos(b, 1);
	int boxc2 = boxc1 + 1;
	int boxc3 = boxc1 + 2;

	if (r3bcnt == 1){

		if (box[b].r3[1] == 0){ targcol = boxc1; }
		else {
			if (box[b].r3[2] == 0){ targcol = boxc2; }
			else { if (box[b].r3[3] == 0){ targcol = boxc3; } }
		}
	}


	int c1resm1 = 0; int c1resm2 = 0; int c1resm3 = 0; int c1resm4 = 0; int c1resm5 = 0;
	int c2resm1 = 0; int c2resm2 = 0; int c2resm3 = 0; int c2resm4 = 0; int c2resm5 = 0;
	int c3resm1 = 0; int c3resm2 = 0; int c3resm3 = 0; int c3resm4 = 0; int c3resm5 = 0;

	if (r3bcnt>1){ //set up for elimination...

		c1resm1 = fincol(boxc1, m1);
		c1resm2 = fincol(boxc1, m2);
		if (mcount>2){ c1resm3 = fincol(boxc1, m3); }
		if (mcount>3){ c1resm4 = fincol(boxc1, m4); }
		if (mcount>4){ c1resm5 = fincol(boxc1, m5); }


		c2resm1 = fincol(boxc2, m1);
		c2resm2 = fincol(boxc2, m2);
		if (mcount>2){ c2resm3 = fincol(boxc2, m3); }
		if (mcount>3){ c2resm4 = fincol(boxc2, m4); }
		if (mcount>4){ c2resm5 = fincol(boxc2, m5); }

		c3resm1 = fincol(boxc3, m1);
		c3resm2 = fincol(boxc3, m2);
		if (mcount>2){ c3resm3 = fincol(boxc3, m3); }
		if (mcount>3){ c3resm4 = fincol(boxc3, m4); }
		if (mcount>4){ c3resm5 = fincol(boxc3, m5); }

		//if r3bl>1 defer assignment of targbl till later...
	}

	//==================m1 procing==========================
	//check to make sure m1 is either in peer1 or peer2
	int peer1resm1 = finbox(peer1, m1);
	int peer2resm1 = finbox(peer2, m1);
	if (((peer1resm1>0) && (box[peer1].r3done == false)) || (peer2resm1>0) && ((box[peer2].r3done == false))) {//continue with m1
		//make sure m1 is not already in row boxr3
		result = finrow(boxr3, m1);
		if (result == 0){//continue 
			if (targcol == 0){//r3bcnt>1 		        	 
				if ((box[b].r3[1] == 0) && (c1resm1 == 0)){
					if ((c2resm1>0) && (c3resm1>0))     { targcol = boxc1; }
					if ((c2resm1>0) && (box[b].r3[3]>0)){ targcol = boxc1; }
					if ((c3resm1>0) && (box[b].r3[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r3[2] == 0) && (c2resm1 == 0)){
						if ((c1resm1>0) && (c3resm1>0))     { targcol = boxc2; }
						if ((c1resm1>0) && (box[b].r3[3]>0)){ targcol = boxc2; }
						if ((c3resm1>0) && (box[b].r3[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r3[3] == 0) && (c3resm1 == 0)){

							if ((c1resm1>0) && (c2resm1>0))   { targcol = boxc3; }
							if ((c1resm1>0) && (box[b].r3[2]>0)){ targcol = boxc3; }
							if ((c2resm1>0) && (box[b].r3[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "6120         "; result = inspuzzle(targrow, targcol, m1);
				;
				return result;
			}
		}
	}

	//==================m2 procing==========================
	//check to make sure m2 is either in peer1 or peer2
	int peer1resm2 = finbox(peer1, m2);
	int peer2resm2 = finbox(peer2, m2);
	if (((peer1resm2>0) && (box[peer1].r3done == false)) || (peer2resm2>0) && ((box[peer2].r3done == false))) {//continue with m2

		//make sure m2 is not already in row boxr3
		result = finrow(boxr3, m2);
		if (result == 0){//continue 
			if (targcol == 0){//r3bcnt>1 		        	 
				if ((box[b].r3[1] == 0) && (c1resm2 == 0)){
					if ((c2resm2>0) && (c3resm2>0))     { targcol = boxc1; }
					if ((c2resm2>0) && (box[b].r3[3]>0)){ targcol = boxc1; }
					if ((c3resm2>0) && (box[b].r3[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r3[2] == 0) && (c2resm2 == 0)){
						if ((c1resm2>0) && (c3resm2>0))     { targcol = boxc2; }
						if ((c1resm2>0) && (box[b].r3[3]>0)){ targcol = boxc2; }
						if ((c3resm2>0) && (box[b].r3[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r3[3] == 0) && (c3resm2 == 0)){
							if ((c1resm2>0) && (c2resm2>0))   { targcol = boxc3; }
							if ((c1resm2>0) && (box[b].r3[2]>0)){ targcol = boxc3; }
							if ((c2resm2>0) && (box[b].r3[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "6169         "; result = inspuzzle(targrow, targcol, m2);
				;
				return result;
			}
		}
	}
	if (mcount<3){ return 0; }
	//==================m3 procing==========================
	//check to make sure m3 is either in peer1 or peer2
	int peer1resm3 = finbox(peer1, m3);
	int peer2resm3 = finbox(peer2, m3);
	if (((peer1resm3>0) && (box[peer1].r3done == false)) || (peer2resm3>0) && ((box[peer2].r3done == false))) {//continue with m3

		//make sure m3 is not already in row boxr3
		result = finrow(boxr3, m3);
		if (result == 0){//continue 
			if (targcol == 0){//r3bcnt>1 		        	 
				if ((box[b].r3[1] == 0) && (c1resm3 == 0)){
					if ((c2resm3>0) && (c3resm3>0))     { targcol = boxc1; }
					if ((c2resm3>0) && (box[b].r3[3]>0)){ targcol = boxc1; }
					if ((c3resm3>0) && (box[b].r3[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r3[2] == 0) && (c2resm3 == 0)){
						if ((c1resm3>0) && (c3resm3>0))     { targcol = boxc2; }
						if ((c1resm3>0) && (box[b].r3[3]>0)){ targcol = boxc2; }
						if ((c3resm3>0) && (box[b].r3[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r3[3] == 0) && (c3resm3 == 0)){
							if ((c1resm3>0) && (c2resm3>0))   { targcol = boxc3; }
							if ((c1resm3>0) && (box[b].r3[2]>0)){ targcol = boxc3; }
							if ((c2resm3>0) && (box[b].r3[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "6219         "; result = inspuzzle(targrow, targcol, m3);
				;
				return result;
			}
		}
	}

	if (mcount<4){ return 0; }

	//==================m4 procing==========================
	//check to make sure m4 is either in peer1 or peer2
	int peer1resm4 = finbox(peer1, m4);
	int peer2resm4 = finbox(peer2, m4);
	if (((peer1resm4>0) && (box[peer1].r3done == false)) || (peer2resm4>0) && ((box[peer2].r3done == false))) {//continue with m2

		//make sure m4 is not already in row boxr3
		result = finrow(boxr3, m4);
		if (result == 0){//continue 
			if (targcol == 0){//r3bcnt>1 		        	 
				if ((box[b].r3[1] == 0) && (c1resm4 == 0)){
					if ((c2resm4>0) && (c3resm4>0))     { targcol = boxc1; }
					if ((c2resm4>0) && (box[b].r3[3]>0)){ targcol = boxc1; }
					if ((c3resm4>0) && (box[b].r3[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r3[2] == 0) && (c2resm4 == 0)){
						if ((c1resm4>0) && (c3resm4>0))     { targcol = boxc2; }
						if ((c1resm4>0) && (box[b].r3[3]>0)){ targcol = boxc2; }
						if ((c3resm4>0) && (box[b].r3[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r3[3] == 0) && (c3resm4 == 0)){
							if ((c1resm4>0) && (c2resm4>0))   { targcol = boxc3; }
							if ((c1resm4>0) && (box[b].r3[2]>0)){ targcol = boxc3; }
							if ((c2resm4>0) && (box[b].r3[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "6271         "; result = inspuzzle(targrow, targcol, m4);
				;
				return result;
			}
		}
	}


	if (mcount<5){ return 0; }
	//==================m5 procing==========================
	//check to make sure m5 is either in peer1 or peer2
	int peer1resm5 = finbox(peer1, m5);
	int peer2resm5 = finbox(peer2, m5);
	if (((peer1resm5>0) && (box[peer1].r3done == false)) || ((peer2resm5>0) && (box[peer2].r3done == false))) {//continue with m5

		//make sure m5 is not already in row boxr3
		result = finrow(boxr3, m5);
		if (result == 0){//continue 
			if (targcol == 0){//r3bcnt>1 		        	 
				if ((box[b].r3[1] == 0) && (c1resm5 == 0)){
					if ((c2resm5>0) && (c3resm5>0))     { targcol = boxc1; }
					if ((c2resm5>0) && (box[b].r3[3]>0)){ targcol = boxc1; }
					if ((c3resm5>0) && (box[b].r3[2]>0)){ targcol = boxc1; }
				}
				else{
					if ((box[b].r3[2] == 0) && (c2resm5 == 0)){
						if ((c1resm5>0) && (c3resm5>0))     { targcol = boxc2; }
						if ((c1resm5>0) && (box[b].r3[3]>0)){ targcol = boxc2; }
						if ((c3resm5>0) && (box[b].r3[1]>0)){ targcol = boxc2; }

					}
					else{
						if ((box[b].r3[3] == 0) && (c3resm5 == 0)){
							if ((c1resm5>0) && (c2resm5>0))   { targcol = boxc3; }
							if ((c1resm5>0) && (box[b].r3[2]>0)){ targcol = boxc3; }
							if ((c2resm5>0) && (box[b].r3[1]>0)){ targcol = boxc3; }
						}

					}
				}
			}
			if (targcol>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "6323         "; result = inspuzzle(targrow, targcol, m5);
				;
				return result;
			}
		}
	}

	return 0;
}
//==========================================================
//end boxelimr3done
//========================================================== 
//==========================================================
int boxelimc1done(int b){
	//==========================================================
	//	readpuzzle();
	//box[b].bcnt = 0;
//	readbox(b);
	//init_box(b);

	int result = 0;
	if (box[b].done == true){ return 0; }

	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	int bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	int peer1 = 0;
	int peer2 = 0;
	switch (b){
	case 7:peer1 = 4; peer2 = 1; break;
	case 1:peer1 = 4; peer2 = 7; break;
	case 4:peer1 = 1; peer2 = 7; break;

	case 8:peer1 = 5; peer2 = 2; break;
	case 2:peer1 = 5; peer2 = 8; break;
	case 5:peer1 = 2; peer2 = 8; break;

	case 9:peer1 = 6; peer2 = 3; break;
	case 3:peer1 = 6; peer2 = 9; break;
	case 6:peer1 = 3; peer2 = 9; break;
	}

	if (box[peer1].c1done == false){
		//swap peer 1 and peer 2 and check c1done again.  then erase peer 2 function altogher 	
		int savepeer1 = peer1;
		peer1 = peer2;
		peer2 = savepeer1;
		if (box[peer1].c1done == false){ return 0; }
		//brilliant!
	}
	if (box[b].c1done == true){ return 0; }
	int c1resm1 = 0; int c1resm2 = 0; int c1resm3 = 0; int c1resm4 = 0;
	//g columns for box and pos
	int boxc1 = gcolfromboxandpos(b, 1);
	int boxc2 = boxc1 + 1;
	int boxc3 = boxc1 + 2;


	if (mcount<2){ return 0; }

	if (mcount>5){ return 0; }
	int c1bcnt = 0;

	if (box[b].c1[1] == 0){ ++c1bcnt; }
	if (box[b].c1[2] == 0){ ++c1bcnt; }
	if (box[b].c1[3] == 0){ ++c1bcnt; }

	int targbl = 0;
	int targrow = 0;
	int targcol = boxc1;
	int boxr1 = growfromboxandpos(b, 1);
	int boxr2 = boxr1 + 1;
	int boxr3 = boxr1 + 2;

	if (c1bcnt == 1){

		if (box[b].c1[1] == 0){ targrow = boxr1; }
		else {
			if (box[b].c1[2] == 0){ targrow = boxr2; }
			else { if (box[b].c1[3] == 0){ targrow = boxr3; } }
		}
	}


	int r1resm1 = 0; int r1resm2 = 0; int r1resm3 = 0; int r1resm4 = 0; int r1resm5 = 0;
	int r2resm1 = 0; int r2resm2 = 0; int r2resm3 = 0; int r2resm4 = 0; int r2resm5 = 0;
	int r3resm1 = 0; int r3resm2 = 0; int r3resm3 = 0; int r3resm4 = 0; int r3resm5 = 0;

	if (c1bcnt>1){ //set up for elimination...

		r1resm1 = finrow(boxr1, m1);
		r1resm2 = finrow(boxr1, m2);
		if (mcount>2){ r1resm3 = finrow(boxr1, m3); }
		if (mcount>3){ r1resm4 = finrow(boxr1, m4); }
		if (mcount>4){ r1resm5 = finrow(boxr1, m5); }


		r2resm1 = finrow(boxr2, m1);
		r2resm2 = finrow(boxr2, m2);
		if (mcount>2){ r2resm3 = finrow(boxr2, m3); }
		if (mcount>3){ r2resm4 = finrow(boxr2, m4); }
		if (mcount>4){ r2resm5 = finrow(boxr2, m5); }

		r3resm1 = finrow(boxr3, m1);
		r3resm2 = finrow(boxr3, m2);
		if (mcount>2){ r3resm3 = finrow(boxr3, m3); }
		if (mcount>3){ r3resm4 = finrow(boxr3, m4); }
		if (mcount>4){ r3resm5 = finrow(boxr3, m5); }

		//if c1bl>1 defer assignment of targbl till later...
	}

	//==================m1 procing==========================
	//check to make sure m1 is either in peer1 or peer2
	int peer1resm1 = finbox(peer1, m1);
	int peer2resm1 = finbox(peer2, m1);
	if (((peer1resm1>0) && (box[peer1].c1done == false)) || (peer2resm1>0) && ((box[peer2].c1done == false))) {//continue with m1
		//make sure m1 is not already in column boxc1
		result = fincol(boxc1, m1);
		if (result == 0){//continue 
			if (targrow == 0){//c1bcnt>1 		        	 
				if ((box[b].c1[1] == 0) && (r1resm1 == 0)){
					if ((r2resm1>0) && (r3resm1>0))     { targrow = boxr1; }
					if ((r2resm1>0) && (box[b].c1[3]>0)){ targrow = boxr1; }
					if ((r3resm1>0) && (box[b].c1[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c1[2] == 0) && (r2resm1 == 0)){
						if ((r1resm1>0) && (r3resm1>0))     { targrow = boxr2; }
						if ((r1resm1>0) && (box[b].c1[3]>0)){ targrow = boxr2; }
						if ((r3resm1>0) && (box[b].c1[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c1[3] == 0) && (r3resm1 == 0)){
							if ((r1resm1>0) && (r2resm1>0))   { targrow = boxr3; }
							if ((r1resm1>0) && (box[b].c1[2]>0)){ targrow = boxr3; }
							if ((r2resm1>0) && (box[b].c1[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				int rowres = finrow(targrow, m1);
				if (rowres>0){ return 0; }
				glastwrite = "6251         "; result = inspuzzle(targrow, targcol, m1);
				;
				return result;
			}
		}
	}

	//==================m2 procing==========================
	//check to make sure m2 is either in peer1 or peer2
	int peer1resm2 = finbox(peer1, m2);
	int peer2resm2 = finbox(peer2, m2);
	if (((peer1resm2>0) && (box[peer1].c1done == false)) || (peer2resm2>0) && ((box[peer2].c1done == false))) {//continue with m2

		//make sure m2 is not already in column boxc1
		result = fincol(boxc1, m2);
		if (result == 0){//continue 
			if (targrow == 0){//c1bcnt>1 		        	 
				if ((box[b].c1[1] == 0) && (r1resm2 == 0)){
					if ((r2resm2>0) && (r3resm2>0))     { targrow = boxr1; }
					if ((r2resm2>0) && (box[b].c1[3]>0)){ targrow = boxr1; }
					if ((r3resm2>0) && (box[b].c1[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c1[2] == 0) && (r2resm2 == 0)){
						if ((r1resm2>0) && (r3resm2>0))     { targrow = boxr2; }
						if ((r1resm2>0) && (box[b].c1[3]>0)){ targrow = boxr2; }
						if ((r3resm2>0) && (box[b].c1[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c1[3] == 0) && (r3resm2 == 0)){
							if ((r1resm2>0) && (r2resm2>0))   { targrow = boxr3; }
							if ((r1resm2>0) && (box[b].c1[2]>0)){ targrow = boxr3; }
							if ((r2resm2>0) && (box[b].c1[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				int rowres = finrow(targrow, m2);
				if (rowres>0){ return 0; }
				glastwrite = "6526         "; result = inspuzzle(targrow, targcol, m2);
				;
				return result;
			}
		}
	}
	if (mcount<3){ return 0; }
	//==================m3 procing==========================
	//check to make sure m3 is either in peer1 or peer2
	int peer1resm3 = finbox(peer1, m3);
	int peer2resm3 = finbox(peer2, m3);
	if (((peer1resm3>0) && (box[peer1].c1done == false)) || (peer2resm3>0) && ((box[peer2].c1done == false))) {//continue with m3

		//make sure m3 is not already in column boxc1
		result = fincol(boxc1, m3);
		if (result == 0){//continue 
			if (targrow == 0){//c1bcnt>1 		        	 
				if ((box[b].c1[1] == 0) && (r1resm3 == 0)){
					if ((r2resm3>0) && (r3resm3>0))     { targrow = boxr1; }
					if ((r2resm3>0) && (box[b].c1[3]>0)){ targrow = boxr1; }
					if ((r3resm3>0) && (box[b].c1[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c1[2] == 0) && (r2resm3 == 0)){
						if ((r1resm3>0) && (r3resm3>0))     { targrow = boxr2; }
						if ((r1resm3>0) && (box[b].c1[3]>0)){ targrow = boxr2; }
						if ((r3resm3>0) && (box[b].c1[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c1[3] == 0) && (r3resm3 == 0)){

							if ((r1resm3>0) && (r2resm3>0))   { targrow = boxr3; }
							if ((r1resm3>0) && (box[b].c1[2]>0)){ targrow = boxr3; }
							if ((r2resm3>0) && (box[b].c1[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "6571         "; result = inspuzzle(targrow, targcol, m3);
				;
				return result;
			}
		}
	}

	if (mcount<4){ return 0; }

	//==================m4 procing==========================
	//check to make sure m4 is either in peer1 or peer2
	int peer1resm4 = finbox(peer1, m4);
	int peer2resm4 = finbox(peer2, m4);
	if (((peer1resm4>0) && (box[peer1].c1done == false)) || (peer2resm4>0) && ((box[peer2].c1done == false))) {//continue with m2

		//make sure m4 is not already in column boxc1
		result = fincol(boxc1, m4);
		if (result == 0){//continue 
			if (targrow == 0){//c1bcnt>1 		        	 
				if ((box[b].c1[1] == 0) && (r1resm4 == 0)){
					if ((r2resm4>0) && (r3resm4>0))     { targrow = boxr1; }
					if ((r2resm4>0) && (box[b].c1[3]>0)){ targrow = boxr1; }
					if ((r3resm4>0) && (box[b].c1[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c1[2] == 0) && (r2resm4 == 0)){
						if ((r1resm4>0) && (r3resm4>0))     { targrow = boxr2; }
						if ((r1resm4>0) && (box[b].c1[3]>0)){ targrow = boxr2; }
						if ((r3resm4>0) && (box[b].c1[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c1[3] == 0) && (r3resm4 == 0)){
							if ((r1resm4>0) && (r2resm4>0))   { targrow = boxr3; }
							if ((r1resm4>0) && (box[b].c1[2]>0)){ targrow = boxr3; }
							if ((r2resm4>0) && (box[b].c1[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "6382         "; result = inspuzzle(targrow, targcol, m4);
				;
				return result;
			}
		}
	}


	if (mcount<5){ return 0; }
	//==================m5 procing==========================
	//check to make sure m5 is either in peer1 or peer2
	int peer1resm5 = finbox(peer1, m5);
	int peer2resm5 = finbox(peer2, m5);
	if (((peer1resm5>0) && (box[peer1].c1done == false)) || ((peer2resm5>0) && (box[peer2].c1done == false))) {//continue with m5

		//make sure m5 is not already in column boxc1
		result = fincol(boxc1, m5);
		//     //cout<<"result="<<result<<endl; 
		if (result == 0){//continue 
			if (targrow == 0){//c1bcnt>1 		        	 
				if ((box[b].c1[1] == 0) && (r1resm5 == 0)){
					if ((r2resm5>0) && (r3resm5>0))     { targrow = boxr1; }
					if ((r2resm5>0) && (box[b].c1[3]>0)){ targrow = boxr1; }
					if ((r3resm5>0) && (box[b].c1[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c1[2] == 0) && (r2resm5 == 0)){
						if ((r1resm5>0) && (r3resm5>0))     { targrow = boxr2; }
						if ((r1resm5>0) && (box[b].c1[3]>0)){ targrow = boxr2; }
						if ((r3resm5>0) && (box[b].c1[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c1[3] == 0) && (r3resm5 == 0)){
							if ((r1resm5>0) && (r2resm5>0))   { targrow = boxr3; }
							if ((r1resm5>0) && (box[b].c1[2]>0)){ targrow = boxr3; }
							if ((r2resm5>0) && (box[b].c1[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "6665         "; result = inspuzzle(targrow, targcol, m5);
				;
				return result;
			}
		}
	}

	return 0;
}
//==========================================================
//end boxelimc1done                                                                                                                                                                                                                     
//##########################################################  
//==========================================================
int boxelimc3done(int b){
	//==========================================================
	//	readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
//	init_box(b);

	int result = 0;
	//  //cout<<"in function boxelimc3done box="<<b<<endl;
	if (box[b].done == true){ return 0; }

	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int b1 = 0; int b2 = 0; int b3 = 0; int b4 = 0; int b5 = 0; int b6 = 0; int b7 = 0; int b8 = 0; int b9 = 0;
	int bcount = gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);
	int peer1 = 0;
	int peer2 = 0;
	switch (b){
	case 7:peer1 = 4; peer2 = 1; break;
	case 1:peer1 = 4; peer2 = 7; break;
	case 4:peer1 = 1; peer2 = 7; break;

	case 8:peer1 = 5; peer2 = 2; break;
	case 2:peer1 = 5; peer2 = 8; break;
	case 5:peer1 = 2; peer2 = 8; break;

	case 9:peer1 = 6; peer2 = 3; break;
	case 3:peer1 = 6; peer2 = 9; break;
	case 6:peer1 = 3; peer2 = 9; break;
	}

	if (box[peer1].c3done == false){
		//swap peer 1 and peer 2 and check c3done again.  then erase peer 2 function altogher 	
		int savepeer1 = peer1;
		peer1 = peer2;
		peer2 = savepeer1;
		if (box[peer1].c3done == false){ return 0; }
		//brilliant!
	}
	if (box[b].c3done == true){ return 0; }
	int c3resm1 = 0; int c3resm2 = 0; int c3resm3 = 0; int c3resm4 = 0;
	//g columns for box and pos
	int boxc1 = gcolfromboxandpos(b, 1);
	int boxc2 = boxc1 + 1;
	int boxc3 = boxc1 + 2;


	if (mcount<2){ return 0; }

	if (mcount>5){ return 0; }
	int c3bcnt = 0;

	if (box[b].c3[1] == 0){ ++c3bcnt; }
	if (box[b].c3[2] == 0){ ++c3bcnt; }
	if (box[b].c3[3] == 0){ ++c3bcnt; }

	int targbl = 0;
	int targrow = 0;
	int targcol = boxc3;
	int boxr1 = growfromboxandpos(b, 1);
	int boxr2 = boxr1 + 1;
	int boxr3 = boxr1 + 2;

	if (c3bcnt == 1){

		if (box[b].c3[1] == 0){ targrow = boxr1; }
		else {
			if (box[b].c3[2] == 0){ targrow = boxr2; }
			else { if (box[b].c3[3] == 0){ targrow = boxr3; } }
		}
	}


	int r1resm1 = 0; int r1resm2 = 0; int r1resm3 = 0; int r1resm4 = 0; int r1resm5 = 0;
	int r2resm1 = 0; int r2resm2 = 0; int r2resm3 = 0; int r2resm4 = 0; int r2resm5 = 0;
	int r3resm1 = 0; int r3resm2 = 0; int r3resm3 = 0; int r3resm4 = 0; int r3resm5 = 0;

	if (c3bcnt>1){ //set up for elimination...

		r1resm1 = finrow(boxr1, m1);
		r1resm2 = finrow(boxr1, m2);
		if (mcount>2){ r1resm3 = finrow(boxr1, m3); }
		if (mcount>3){ r1resm4 = finrow(boxr1, m4); }
		if (mcount>4){ r1resm5 = finrow(boxr1, m5); }


		r2resm1 = finrow(boxr2, m1);
		r2resm2 = finrow(boxr2, m2);
		if (mcount>2){ r2resm3 = finrow(boxr2, m3); }
		if (mcount>3){ r2resm4 = finrow(boxr2, m4); }
		if (mcount>4){ r2resm5 = finrow(boxr2, m5); }

		r3resm1 = finrow(boxr3, m1);
		r3resm2 = finrow(boxr3, m2);
		if (mcount>2){ r3resm3 = finrow(boxr3, m3); }
		if (mcount>3){ r3resm4 = finrow(boxr3, m4); }
		if (mcount>4){ r3resm5 = finrow(boxr3, m5); }

		//if c3bl>1 defer assignment of targbl till later...
	}

	//==================m1 procing==========================
	//check to make sure m1 is either in peer1 or peer2
	int peer1resm1 = finbox(peer1, m1);
	int peer2resm1 = finbox(peer2, m1);
	if (((peer1resm1>0) && (box[peer1].c3done == false)) || (peer2resm1>0) && ((box[peer2].c3done == false))) {//continue with m1
		//make sure m1 is not already in column boxc3
		result = fincol(boxc3, m1);
		if (result == 0){//continue 
			if (targrow == 0){//c3bcnt>1 		        	 
				if ((box[b].c3[1] == 0) && (r1resm1 == 0)){
					if ((r2resm1>0) && (r3resm1>0))     { targrow = boxr1; }
					if ((r2resm1>0) && (box[b].c3[3]>0)){ targrow = boxr1; }
					if ((r3resm1>0) && (box[b].c3[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c3[2] == 0) && (r2resm1 == 0)){
						if ((r1resm1>0) && (r3resm1>0))     { targrow = boxr2; }
						if ((r1resm1>0) && (box[b].c3[3]>0)){ targrow = boxr2; }
						if ((r3resm1>0) && (box[b].c3[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c3[3] == 0) && (r3resm1 == 0)){
							if ((r1resm1>0) && (r2resm1>0))   { targrow = boxr3; }
							if ((r1resm1>0) && (box[b].c3[2]>0)){ targrow = boxr3; }
							if ((r2resm1>0) && (box[b].c3[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "6816         "; result =

					inspuzzle(targrow, targcol, m1);

				return result;
			}
		}
	}


	//check to make sure m2 is either in peer1 or peer2
	int peer1resm2 = finbox(peer1, m2);
	int peer2resm2 = finbox(peer2, m2);
	if (((peer1resm2>0) && (box[peer1].c3done == false)) || (peer2resm2>0) && ((box[peer2].c3done == false))) {//continue with m2

		//make sure m2 is not already in column boxc3
		result = fincol(boxc3, m2);
		if (result == 0){//continue 
			if (targrow == 0){//c3bcnt>1 		        	 
				if ((box[b].c3[1] == 0) && (r1resm2 == 0)){
					if ((r2resm2>0) && (r3resm2>0))     { targrow = boxr1; }
					if ((r2resm2>0) && (box[b].c3[3]>0)){ targrow = boxr1; }
					if ((r3resm2>0) && (box[b].c3[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c3[2] == 0) && (r2resm2 == 0)){
						if ((r1resm2>0) && (r3resm2>0))     { targrow = boxr2; }
						if ((r1resm2>0) && (box[b].c3[3]>0)){ targrow = boxr2; }
						if ((r3resm2>0) && (box[b].c3[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c3[3] == 0) && (r3resm2 == 0)){
							if ((r1resm2>0) && (r2resm2>0))   { targrow = boxr3; }
							if ((r1resm2>0) && (box[b].c3[2]>0)){ targrow = boxr3; }
							if ((r2resm2>0) && (box[b].c3[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "6861         "; result = inspuzzle(targrow, targcol, m2);
				;
				return result;
			}
		}
	}
	if (mcount<3){ return 0; }
	//==================m3 procing==========================
	//check to make sure m3 is either in peer1 or peer2
	int peer1resm3 = finbox(peer1, m3);
	int peer2resm3 = finbox(peer2, m3);
	if (((peer1resm3>0) && (box[peer1].c3done == false)) || (peer2resm3>0) && ((box[peer2].c3done == false))) {//continue with m3

		//make sure m3 is not already in column boxc3
		result = fincol(boxc3, m3);
		if (result == 0){//continue 
			if (targrow == 0){//c3bcnt>1 		        	 
				if ((box[b].c3[1] == 0) && (r1resm3 == 0)){
					if ((r2resm3>0) && (r3resm3>0))     { targrow = boxr1; }
					if ((r2resm3>0) && (box[b].c3[3]>0)){ targrow = boxr1; }
					if ((r3resm3>0) && (box[b].c3[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c3[2] == 0) && (r2resm3 == 0)){
						if ((r1resm3>0) && (r3resm3>0))     { targrow = boxr2; }
						if ((r1resm3>0) && (box[b].c3[3]>0)){ targrow = boxr2; }
						if ((r3resm3>0) && (box[b].c3[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c3[3] == 0) && (r3resm3 == 0)){

							if ((r1resm3>0) && (r2resm3>0))   { targrow = boxr3; }
							if ((r1resm3>0) && (box[b].c3[2]>0)){ targrow = boxr3; }
							if ((r2resm3>0) && (box[b].c3[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "6905         "; result = inspuzzle(targrow, targcol, m3);
				;
				return result;
			}
		}
	}

	if (mcount<4){ return 0; }

	//==================m4 procing==========================
	//check to make sure m4 is either in peer1 or peer2
	int peer1resm4 = finbox(peer1, m4);
	int peer2resm4 = finbox(peer2, m4);
	if (((peer1resm4>0) && (box[peer1].c3done == false)) || (peer2resm4>0) && ((box[peer2].c3done == false))) {//continue with m2

		//make sure m4 is not already in column boxc3
		result = fincol(boxc3, m4);
		if (result == 0){//continue 
			if (targrow == 0){//c3bcnt>1 		        	 
				if ((box[b].c3[1] == 0) && (r1resm4 == 0)){
					if ((r2resm4>0) && (r3resm4>0))     { targrow = boxr1; }
					if ((r2resm4>0) && (box[b].c3[3]>0)){ targrow = boxr1; }
					if ((r3resm4>0) && (box[b].c3[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c3[2] == 0) && (r2resm4 == 0)){
						if ((r1resm4>0) && (r3resm4>0))     { targrow = boxr2; }
						if ((r1resm4>0) && (box[b].c3[3]>0)){ targrow = boxr2; }
						if ((r3resm4>0) && (box[b].c3[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c3[3] == 0) && (r3resm4 == 0)){
							if ((r1resm4>0) && (r2resm4>0))   { targrow = boxr3; }
							if ((r1resm4>0) && (box[b].c3[2]>0)){ targrow = boxr3; }
							if ((r2resm4>0) && (box[b].c3[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				//cout<<"insert line 9998 function boxelimc3done m4 box="<<b<<endl;
				glastwrite = "6950         "; result = inspuzzle(targrow, targcol, m4);
				;
				return result;
			}
		}
	}


	if (mcount<5){ return 0; }
	//==================m5 procing==========================
	//check to make sure m5 is either in peer1 or peer2
	int peer1resm5 = finbox(peer1, m5);
	int peer2resm5 = finbox(peer2, m5);
	if (((peer1resm5>0) && (box[peer1].c3done == false)) || ((peer2resm5>0) && (box[peer2].c3done == false))) {//continue with m5

		//make sure m5 is not already in column boxc3
		result = fincol(boxc3, m5);
		if (result == 0){//continue 
			if (targrow == 0){//c3bcnt>1 		        	 
				if ((box[b].c3[1] == 0) && (r1resm5 == 0)){
					if ((r2resm5>0) && (r3resm5>0))     { targrow = boxr1; }
					if ((r2resm5>0) && (box[b].c3[3]>0)){ targrow = boxr1; }
					if ((r3resm5>0) && (box[b].c3[2]>0)){ targrow = boxr1; }
				}
				else{
					if ((box[b].c3[2] == 0) && (r2resm5 == 0)){
						if ((r1resm5>0) && (r3resm5>0))     { targrow = boxr2; }
						if ((r1resm5>0) && (box[b].c3[3]>0)){ targrow = boxr2; }
						if ((r3resm5>0) && (box[b].c3[1]>0)){ targrow = boxr2; }

					}
					else{
						if ((box[b].c3[3] == 0) && (r3resm5 == 0)){
							if ((r1resm5>0) && (r2resm5>0))   { targrow = boxr3; }
							if ((r1resm5>0) && (box[b].c3[2]>0)){ targrow = boxr3; }
							if ((r2resm5>0) && (box[b].c3[1]>0)){ targrow = boxr3; }
						}

					}
				}
			}
			if (targrow>0){
				//insert and finish   
				//got everything  finish...
				glastwrite = "6999         "; result = inspuzzle(targrow, targcol, m5);
				;
				return result;
			}
		}
	}

	return 0;
}
//==========================================================
//end boxelimc3done                                                                                                                                                                                                                     
//########################################################## 

//==========================================================
int boxsubtract2c3(int b){
	//==========================================================
	////cout<<"in function boxsubtract2c3 box="<<b<<endl;
	int result = 0;
	//	readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
//	init_box(b);
	//pBox(b);
	int m1 = 0; int m2 = 0; int m3 = 0;
	int mcount = gminbox(b, m1, m2, m3);
	if (mcount != 2){ return 0; }

	if ((box[b].c1done == false) || (box[b].c2done == false)){ return 0; }

	int c3 = gcolfromboxandpos(b, 3);

	int boxbl1 = gfb(zbox, b);
	int boxbl2 = gnb(zbox, b, boxbl1);
	int boxrow1 = growfromboxandpos(b, boxbl1);
	int boxrow2 = growfromboxandpos(b, boxbl2);

	int cm1 = 0; int cm2 = 0; int cm3 = 0; int cm4 = 0; int cm5 = 0;
	int cm6 = 0; int cm7 = 0; int cm8 = 0; int cm9 = 0;
	int cmcount = gallmincol(c3, cm1, cm2, cm3, cm4, cm5, cm6, cm7, cm8, cm9);
	if (cmcount != 4){ return 0; }
	//"subtract box m numbers"
	if (cm1 == m1){ cm1 = 0; }
	if (cm2 == m1){ cm2 = 0; }
	if (cm3 == m1){ cm3 = 0; }
	if (cm4 == m1){ cm4 = 0; }
	if (cm1 == m2){ cm1 = 0; }
	if (cm2 == m2){ cm2 = 0; }
	if (cm3 == m2){ cm3 = 0; }
	if (cm4 == m2){ cm4 = 0; }

	//now attempt elimination with the remaining two

	int targnum1 = 0;
	int targnum2 = 0;
	int targrow1 = 0;
	int targrow2 = 0;

	if (cm1>0){ targnum1 = cm1; }
	if (cm2>0){ if (targnum1 == 0){ targnum1 = cm2; } else{ targnum2 = cm2; } }
	if (cm3>0){ if (targnum1 == 0){ targnum1 = cm3; } else{ targnum2 = cm3; } }
	if (cm4>0){ targnum2 = cm4; }

	//now find the nonbox bls in the column to check
	int columnbl1 = 0; int columnbl2 = 0; int columnbl3 = 0; int columnbl4 = 0;
	columnbl1 = gfb(zcol, c3);
	columnbl2 = gnb(zcol, c3, columnbl1);
	columnbl3 = gnb(zcol, c3, columnbl2);
	columnbl4 = glastbl(zcol, c3);
	if ((columnbl1 != boxrow1) && (columnbl1 != boxrow2)){ targrow1 = columnbl1; }
	if ((columnbl2 != boxrow1) && (columnbl2 != boxrow2)){ if (targrow1 == 0){ targrow1 = columnbl2; } else{ targrow2 = columnbl2; } }

	if ((columnbl3 != boxrow1) && (columnbl3 != boxrow2)){ if (targrow1 == 0){ targrow1 = columnbl3; } else{ targrow2 = columnbl3; } }
	if ((columnbl4 != boxrow1) && (columnbl4 != boxrow2)){ targrow2 = columnbl4; }

	if ((targrow1 == 0) || (targrow2 == 0)){
		//cout<<"ERROR FUNCTION BOXSUBTRACT2C3 LINE 10906 C3="<<c3<<endl;
	}
	int num1result1 = finrow(targrow1, targnum1);
	int num1result2 = finrow(targrow2, targnum1);
	int num2result1 = finrow(targrow1, targnum2);
	int num2result2 = finrow(targrow2, targnum2);
	result = 0;
	if ((num1result1>0) && (num1result2 == 0)){
		glastwrite = "7084         "; result = inspuzzle(targrow2, c3, targnum1);
		glastwrite = "7085         "; result = inspuzzle(targrow1, c3, targnum2);
	}
	else{
		if ((num2result1>0) && (num2result2 == 0)){
			glastwrite = "7090         "; result = inspuzzle(targrow2, c3, targnum2);
			glastwrite = "7091         "; result = inspuzzle(targrow1, c3, targnum1);
		}
		else{
			if ((num1result2>0) && (num1result1 == 0)){
				glastwrite = "7096         "; result = inspuzzle(targrow1, c3, targnum1);
				glastwrite = "7097         "; result = inspuzzle(targrow2, c3, targnum2);
			}
			else{
				if ((num2result2>0) && (num2result1 == 0)){
					glastwrite = "7101         "; result = inspuzzle(targrow1, c3, targnum2);
					glastwrite = "7102         "; result = inspuzzle(targrow2, c3, targnum1);
				}
			}
		}
	}
	if (result>0){ ; }
	return result;
}
//==========================================================
//end boxsubtract2c3
//==========================================================

//==========================================================
int boxsubtract2c2(int b){
	//==========================================================
	////cout<<"in function boxsubtract2c2 box="<<b<<endl;
	int result = 0;
	//	readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
//	init_box(b);
	//pBox(b);
	int m1 = 0; int m2 = 0; int m3 = 0;
	int mcount = gminbox(b, m1, m2, m3);
	if (mcount != 2){ return 0; }

	if ((box[b].c1done == false) || (box[b].c3done == false)){ return 0; }

	int c2 = gcolfromboxandpos(b, 2);

	int boxbl1 = gfb(zbox, b);
	int boxbl2 = gnb(zbox, b, boxbl1);
	int boxrow1 = growfromboxandpos(b, boxbl1);
	int boxrow2 = growfromboxandpos(b, boxbl2);

	int cm1 = 0; int cm2 = 0; int cm3 = 0; int cm4 = 0; int cm5 = 0;
	int cm6 = 0; int cm7 = 0; int cm8 = 0; int cm9 = 0;
	int cmcount = gallmincol(c2, cm1, cm2, cm3, cm4, cm5, cm6, cm7, cm8, cm9);
	if (cmcount != 4){ return 0; }
	//"subtract box m numbers"
	if (cm1 == m1){ cm1 = 0; }
	if (cm2 == m1){ cm2 = 0; }
	if (cm3 == m1){ cm3 = 0; }
	if (cm4 == m1){ cm4 = 0; }
	if (cm1 == m2){ cm1 = 0; }
	if (cm2 == m2){ cm2 = 0; }
	if (cm3 == m2){ cm3 = 0; }
	if (cm4 == m2){ cm4 = 0; }

	//now attempt elimination with the remaining two

	int targnum1 = 0;
	int targnum2 = 0;
	int targrow1 = 0;
	int targrow2 = 0;

	if (cm1>0){ targnum1 = cm1; }
	if (cm2>0){ if (targnum1 == 0){ targnum1 = cm2; } else{ targnum2 = cm2; } }
	if (cm3>0){ if (targnum1 == 0){ targnum1 = cm3; } else{ targnum2 = cm3; } }
	if (cm4>0){ targnum2 = cm4; }
	if ((targnum1 == 0) || (targnum2 == 0)){
		//cout<<"ERROR FUNCTION BOXSUBTRACT2C2 LINE 11004 C2="<<c2<<endl;
	}

	//now find the nonbox bls in the column to check
	int columnbl1 = 0; int columnbl2 = 0; int columnbl3 = 0; int columnbl4 = 0;
	columnbl1 = gfb(zcol, c2);
	columnbl2 = gnb(zcol, c2, columnbl1);
	columnbl3 = gnb(zcol, c2, columnbl2);
	columnbl4 = glastbl(zcol, c2);
	if ((columnbl1 != boxrow1) && (columnbl1 != boxrow2)){ targrow1 = columnbl1; }
	if ((columnbl2 != boxrow1) && (columnbl2 != boxrow2)){ if (targrow1 == 0){ targrow1 = columnbl2; } else{ targrow2 = columnbl2; } }

	if ((columnbl3 != boxrow1) && (columnbl3 != boxrow2)){ if (targrow1 == 0){ targrow1 = columnbl3; } else{ targrow2 = columnbl3; } }
	if ((columnbl4 != boxrow1) && (columnbl4 != boxrow2)){ targrow2 = columnbl4; }

	if ((targrow1 == 0) || (targrow2 == 0)){
		//cout<<"ERROR FUNCTION BOXSUBTRACT2C2 LINE 11028 C2="<<c2<<endl;
	}
	int num1result1 = finrow(targrow1, targnum1);
	int num1result2 = finrow(targrow2, targnum1);
	int num2result1 = finrow(targrow1, targnum2);
	int num2result2 = finrow(targrow2, targnum2);
	result = 0;
	if ((num1result1>0) && (num1result2 == 0)){
		glastwrite = "7187         "; result = inspuzzle(targrow2, c2, targnum1);
		glastwrite = "7188         "; result = inspuzzle(targrow1, c2, targnum2);
	}
	else{
		if ((num2result1>0) && (num2result2 == 0)){
			glastwrite = "7189         "; result = inspuzzle(targrow2, c2, targnum2);
			glastwrite = "7190         "; result = inspuzzle(targrow1, c2, targnum1);
		}
		else{
			if ((num1result2>0) && (num1result1 == 0)){
				glastwrite = "7199         "; result = inspuzzle(targrow1, c2, targnum1);
				glastwrite = "7200         "; result = inspuzzle(targrow2, c2, targnum2);
			}
			else{
				if ((num2result2>0) && (num2result1 == 0)){
					glastwrite = "7204         "; result = inspuzzle(targrow1, c2, targnum2);
					glastwrite = "7205         "; result = inspuzzle(targrow2, c2, targnum1);
				}
			}
		}
	}
	if (result>0){ ; }
	return result;
}
//==========================================================
//end boxsubtract2c2
//==========================================================

//==========================================================
int boxsubtract2c1(int b){
	//==========================================================
	////cout<<"in function boxsubtract2c1 box="<<b<<endl;
	int result = 0;
	//	readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
//	init_box(b);
	//pBox(b);
	int m1 = 0; int m2 = 0; int m3 = 0;
	int mcount = gminbox(b, m1, m2, m3);
	if (mcount != 2){ return 0; }

	if ((box[b].c2done == false) || (box[b].c3done == false)){ return 0; }

	int c1 = gcolfromboxandpos(b, 1);

	int boxbl1 = gfb(zbox, b);
	int boxbl2 = gnb(zbox, b, boxbl1);
	int boxrow1 = growfromboxandpos(b, boxbl1);
	int boxrow2 = growfromboxandpos(b, boxbl2);

	int cm1 = 0; int cm2 = 0; int cm3 = 0; int cm4 = 0; int cm5 = 0;
	int cm6 = 0; int cm7 = 0; int cm8 = 0; int cm9 = 0;
	int cmcount = gallmincol(c1, cm1, cm2, cm3, cm4, cm5, cm6, cm7, cm8, cm9);
	if (cmcount != 4){ return 0; }
	//"subtract box m numbers"
	if (cm1 == m1){ cm1 = 0; }
	if (cm2 == m1){ cm2 = 0; }
	if (cm3 == m1){ cm3 = 0; }
	if (cm4 == m1){ cm4 = 0; }
	if (cm1 == m2){ cm1 = 0; }
	if (cm2 == m2){ cm2 = 0; }
	if (cm3 == m2){ cm3 = 0; }
	if (cm4 == m2){ cm4 = 0; }

	//now attempt elimination with the remaining two

	int targnum1 = 0;
	int targnum2 = 0;
	int targrow1 = 0;
	int targrow2 = 0;

	if (cm1>0){ targnum1 = cm1; }
	if (cm2>0){ if (targnum1 == 0){ targnum1 = cm2; } else{ targnum2 = cm2; } }
	if (cm3>0){ if (targnum1 == 0){ targnum1 = cm3; } else{ targnum2 = cm3; } }
	if (cm4>0){ targnum2 = cm4; }
	if ((targnum1 == 0) || (targnum2 == 0)){
		//cout<<"ERROR FUNCTION BOXSUBTRACT2C1 LINE 11126 C1="<<c1<<endl;
	}

	//now find the nonbox bls in the column to check
	int columnbl1 = 0; int columnbl2 = 0; int columnbl3 = 0; int columnbl4 = 0;
	columnbl1 = gfb(zcol, c1);
	columnbl2 = gnb(zcol, c1, columnbl1);
	columnbl3 = gnb(zcol, c1, columnbl2);
	columnbl4 = glastbl(zcol, c1);
	if ((columnbl1 != boxrow1) && (columnbl1 != boxrow2)){ targrow1 = columnbl1; }
	if ((columnbl2 != boxrow1) && (columnbl2 != boxrow2)){ if (targrow1 == 0){ targrow1 = columnbl2; } else{ targrow2 = columnbl2; } }

	if ((columnbl3 != boxrow1) && (columnbl3 != boxrow2)){ if (targrow1 == 0){ targrow1 = columnbl3; } else{ targrow2 = columnbl3; } }
	if ((columnbl4 != boxrow1) && (columnbl4 != boxrow2)){ targrow2 = columnbl4; }

	if ((targrow1 == 0) || (targrow2 == 0)){
		//cout<<"ERROR FUNCTION BOXSUBTRACT2C1 LINE 11150 C1="<<c1<<endl;
	}
	int num1result1 = finrow(targrow1, targnum1);
	int num1result2 = finrow(targrow2, targnum1);
	int num2result1 = finrow(targrow1, targnum2);
	int num2result2 = finrow(targrow2, targnum2);
	result = 0;
	if ((num1result1>0) && (num1result2 == 0)){
		glastwrite = "7292         "; result = inspuzzle(targrow2, c1, targnum1);
		glastwrite = "7293         "; result = inspuzzle(targrow1, c1, targnum2);
	}
	else{
		if ((num2result1>0) && (num2result2 == 0)){
			glastwrite = "7298         "; result = inspuzzle(targrow2, c1, targnum2);
			glastwrite = "7299         "; result = inspuzzle(targrow1, c1, targnum1);
		}
		else{
			if ((num1result2>0) && (num1result1 == 0)){
				glastwrite = "7304         "; result = inspuzzle(targrow1, c1, targnum1);
				glastwrite = "7305         "; result = inspuzzle(targrow2, c1, targnum2);
			}
			else{
				if ((num2result2>0) && (num2result1 == 0)){
					glastwrite = "7309         "; result = inspuzzle(targrow1, c1, targnum2);
					glastwrite = "7310         "; result = inspuzzle(targrow2, c1, targnum1);
				}
			}
		}
	}
	if (result>0){ ; }
	return result;
}
//==========================================================
//end boxsubtract2c1
//==========================================================

//==========================================================
int boxsubtract2r1(int b){
	//==========================================================
	////cout<<"in function boxsubtract2r1 box="<<b<<endl;
	int result = 0;
	//	readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
//	init_box(b);
	//pBox(b);
	int m1 = 0; int m2 = 0; int m3 = 0;
	int mcount = gminbox(b, m1, m2, m3);
	if (mcount != 2){ return 0; }

	if ((box[b].r2done == false) || (box[b].r3done == false)){ return 0; }

	int r1 = growfromboxandpos(b, 1);

	int boxbl1 = gfb(zbox, b);
	int boxbl2 = gnb(zbox, b, boxbl1);
	int boxcol1 = gcolfromboxandpos(b, boxbl1);
	int boxcol2 = gcolfromboxandpos(b, boxbl2);

	int rm1 = 0; int rm2 = 0; int rm3 = 0; int rm4 = 0; int rm5 = 0;
	int rm6 = 0; int rm7 = 0; int rm8 = 0; int rm9 = 0;
	int rmcount = gallminrow(r1, rm1, rm2, rm3, rm4, rm5, rm6, rm7, rm8, rm9);
	if (rmcount != 4){ return 0; }
	//"subtract box m numbers"
	if (rm1 == m1){ rm1 = 0; }
	if (rm2 == m1){ rm2 = 0; }
	if (rm3 == m1){ rm3 = 0; }
	if (rm4 == m1){ rm4 = 0; }
	if (rm1 == m2){ rm1 = 0; }
	if (rm2 == m2){ rm2 = 0; }
	if (rm3 == m2){ rm3 = 0; }
	if (rm4 == m2){ rm4 = 0; }

	//now attempt elimination with the remaining two

	int targnum1 = 0;
	int targnum2 = 0;
	int targcol1 = 0;
	int targcol2 = 0;

	if (rm1>0){ targnum1 = rm1; }
	if (rm2>0){ if (targnum1 == 0){ targnum1 = rm2; } else{ targnum2 = rm2; } }
	if (rm3>0){ if (targnum1 == 0){ targnum1 = rm3; } else{ targnum2 = rm3; } }
	if (rm4>0){ targnum2 = rm4; }

	//now find the nonbox bls in the row to check
	int rowbl1 = 0; int rowbl2 = 0; int rowbl3 = 0; int rowbl4 = 0;
	rowbl1 = gfb(zrow, r1);
	rowbl2 = gnb(zrow, r1, rowbl1);
	rowbl3 = gnb(zrow, r1, rowbl2);
	rowbl4 = glastbl(zrow, r1);
	if ((rowbl1 != boxcol1) && (rowbl1 != boxcol2)){ targcol1 = rowbl1; }
	if ((rowbl2 != boxcol1) && (rowbl2 != boxcol2)){ if (targcol1 == 0){ targcol1 = rowbl2; } else{ targcol2 = rowbl2; } }

	if ((rowbl3 != boxcol1) && (rowbl3 != boxcol2)){ if (targcol1 == 0){ targcol1 = rowbl3; } else{ targcol2 = rowbl3; } }
	if ((rowbl4 != boxcol1) && (rowbl4 != boxcol2)){ targcol2 = rowbl4; }

	int num1result1 = fincol(targcol1, targnum1);
	int num1result2 = fincol(targcol2, targnum1);
	int num2result1 = fincol(targcol1, targnum2);
	int num2result2 = fincol(targcol2, targnum2);
	result = 0;
	if ((num1result1>0) && (num1result2 == 0)){
		glastwrite = "7389         "; result = inspuzzle(r1, targcol2, targnum1);
		glastwrite = "7390         "; result = inspuzzle(r1, targcol1, targnum2);
	}
	else{
		if ((num2result1>0) && (num2result2 == 0)){
			glastwrite = "7395         "; result = inspuzzle(r1, targcol2, targnum2);
			glastwrite = "7396         "; result = inspuzzle(r1, targcol1, targnum1);
		}
		else{
			if ((num1result2>0) && (num1result1 == 0)){
				glastwrite = "7401         "; result = inspuzzle(r1, targcol1, targnum1);
				glastwrite = "7402         "; result = inspuzzle(r1, targcol2, targnum2);
			}
			else{
				if ((num2result2>0) && (num2result1 == 0)){
					glastwrite = "7406         "; result = inspuzzle(r1, targcol1, targnum2);
					glastwrite = "7407         "; result = inspuzzle(r1, targcol2, targnum1);
				}
			}
		}
	}
	 
	return result;
}
//==========================================================
//end boxsubtract2r1
//==========================================================
//==========================================================
int boxsubtract2r2(int b){
	//==========================================================
	////cout<<"in function boxsubtract2r2 box="<<b<<endl;
	int result = 0;
	//return 0;                                      //**************************************************bad***************************************************************************
	//readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
//	init_box(b);
	//pBox(b);
	int m1 = 0; int m2 = 0; int m3 = 0;
	int mcount = gminbox(b, m1, m2, m3);
	if (mcount != 2){ return 0; }

	if ((box[b].r1done == false) || (box[b].r3done == false)){ return 0; }

	int r2 = growfromboxandpos(b, 2);

	int boxbl1 = gfb(zbox, b);
	int boxbl2 = gnb(zbox, b, boxbl1);
	int boxcol1 = gcolfromboxandpos(b, boxbl1);
	int boxcol2 = gcolfromboxandpos(b, boxbl2);

	int rm1 = 0; int rm2 = 0; int rm3 = 0; int rm4 = 0; int rm5 = 0;
	int rm6 = 0; int rm7 = 0; int rm8 = 0; int rm9 = 0;
	int rmcount = gallminrow(r2, rm1, rm2, rm3, rm4, rm5, rm6, rm7, rm8, rm9);
	if (rmcount != 4){ return 0; }
	//"subtract box m numbers"
	if (rm1 == m1){ rm1 = 0; }
	if (rm2 == m1){ rm2 = 0; }
	if (rm3 == m1){ rm3 = 0; }
	if (rm4 == m1){ rm4 = 0; }
	if (rm1 == m2){ rm1 = 0; }
	if (rm2 == m2){ rm2 = 0; }
	if (rm3 == m2){ rm3 = 0; }
	if (rm4 == m2){ rm4 = 0; }

	//now attempt elimination with the remaining two

	int targnum1 = 0;
	int targnum2 = 0;
	int targcol1 = 0;
	int targcol2 = 0;

	if (rm1>0){ targnum1 = rm1; }
	if (rm2>0){ if (targnum1 == 0){ targnum1 = rm2; } else{ targnum2 = rm2; } }
	if (rm3>0){ if (targnum1 == 0){ targnum1 = rm3; } else{ targnum2 = rm3; } }
	if (rm4>0){ targnum2 = rm4; }

	//now find the nonbox bls in the row to check
	int rowbl1 = 0; int rowbl2 = 0; int rowbl3 = 0; int rowbl4 = 0;
	rowbl1 = gfb(zrow, r2);
	rowbl2 = gnb(zrow, r2, rowbl1);
	rowbl3 = gnb(zrow, r2, rowbl2);
	rowbl4 = glastbl(zrow, r2);
	if ((rowbl1 != boxcol1) && (rowbl1 != boxcol2)){ targcol1 = rowbl1; }
	if ((rowbl2 != boxcol1) && (rowbl2 != boxcol2)){ if (targcol1 == 0){ targcol1 = rowbl2; } else{ targcol2 = rowbl2; } }

	if ((rowbl3 != boxcol1) && (rowbl3 != boxcol2)){ if (targcol1 == 0){ targcol1 = rowbl3; } else{ targcol2 = rowbl3; } }
	if ((rowbl4 != boxcol1) && (rowbl4 != boxcol2)){ targcol2 = rowbl4; }

	int num1result1 = fincol(targcol1, targnum1);
	int num1result2 = fincol(targcol2, targnum1);
	int num2result1 = fincol(targcol1, targnum2);
	int num2result2 = fincol(targcol2, targnum2);
	result = 0;
	if ((num1result1>0) && (num1result2 == 0)){
		glastwrite = "7486         "; result = inspuzzle(r2, targcol2, targnum1);
		glastwrite = "7487         "; result = inspuzzle(r2, targcol1, targnum2);
	}
	else{
		if ((num2result1>0) && (num2result2 == 0)){
			glastwrite = "7492         "; result = inspuzzle(r2, targcol2, targnum2);
			glastwrite = "7493         "; result = inspuzzle(r2, targcol1, targnum1);
		}
		else{
			if ((num1result2>0) && (num1result1 == 0)){
			//	glastwrite = "7498         "; result = inspuzzle(r2, targcol1, targnum1);
				glastwrite = "7499         "; result = inspuzzle(r2, targcol2, targnum2);
			}
			else{
				if ((num2result2>0) && (num2result1 == 0)){
			//		glastwrite = "7503         "; result = inspuzzle(r2, targcol1, targnum2);
			//		glastwrite = "7504         "; result = inspuzzle(r2, targcol2, targnum1);
				}
			}
		}
	}
	//if (result>0){ ; }
	return result;
}
//==========================================================
//end boxsubtract2r2
//==========================================================

//==========================================================
int boxsubtract2r3(int b){
	//==========================================================
	////cout<<"in function boxsubtract2r3 box="<<b<<endl;
	int result = 0;
	//readpuzzle();
	//box[b].bcnt = 0;
	//readbox(b);
	//init_box(b);
	//pBox(b);
	int m1 = 0; int m2 = 0; int m3 = 0;
	int mcount = gminbox(b, m1, m2, m3);
	if (mcount != 2){ return 0; }

	if ((box[b].r1done == false) || (box[b].r2done == false)){ return 0; }

	int r3 = growfromboxandpos(b, 3);

	int boxbl1 = gfb(zbox, b);
	int boxbl2 = gnb(zbox, b, boxbl1);
	int boxcol1 = gcolfromboxandpos(b, boxbl1);
	int boxcol2 = gcolfromboxandpos(b, boxbl2);
	if ((boxbl1 == 0) || (boxbl2 == 0) || (boxcol1 == 0) || (boxcol2 == 0) || (m1 == 0) || (m2 == 0)){
		//cout<<"ERROR FUNCTION BOXSUBTRACT2R3 line 11413 box="<<b<<endl;
	}

	int rm1 = 0; int rm2 = 0; int rm3 = 0; int rm4 = 0; int rm5 = 0;
	int rm6 = 0; int rm7 = 0; int rm8 = 0; int rm9 = 0;
	int rmcount = gallminrow(r3, rm1, rm2, rm3, rm4, rm5, rm6, rm7, rm8, rm9);
	if (rmcount != 4){ return 0; }
	//"subtract box m numbers"
	if (rm1 == m1){ rm1 = 0; }
	if (rm2 == m1){ rm2 = 0; }
	if (rm3 == m1){ rm3 = 0; }
	if (rm4 == m1){ rm4 = 0; }
	if (rm1 == m2){ rm1 = 0; }
	if (rm2 == m2){ rm2 = 0; }
	if (rm3 == m2){ rm3 = 0; }
	if (rm4 == m2){ rm4 = 0; }

	//now attempt elimination with the remaining two

	int targnum1 = 0;
	int targnum2 = 0;
	int targcol1 = 0;
	int targcol2 = 0;

	if (rm1>0){ targnum1 = rm1; }
	if (rm2>0){ if (targnum1 == 0){ targnum1 = rm2; } else{ targnum2 = rm2; } }
	if (rm3>0){ if (targnum1 == 0){ targnum1 = rm3; } else{ if (targnum2 == 0){ targnum2 = rm3; } } }
	if (rm4>0){ if (targnum2 == 0){ targnum2 = rm4; } }
	if ((targnum1 == 0) || (targnum2 == 0)){ return 0; }
	//now find the nonbox bls in the row to check
	int rowbl1 = 0; int rowbl2 = 0; int rowbl3 = 0; int rowbl4 = 0;
	rowbl1 = gfb(zrow, r3);
	rowbl2 = gnb(zrow, r3, rowbl1);
	rowbl3 = gnb(zrow, r3, rowbl2);
	rowbl4 = glastbl(zrow, r3);
	if ((rowbl1 == 0) || (rowbl2 == 0) || (rowbl3 == 0) || (rowbl4 == 0)){ return 0; }
	if ((rowbl1 != boxcol1) && (rowbl1 != boxcol2)){ targcol1 = rowbl1; }
	if ((rowbl2 != boxcol1) && (rowbl2 != boxcol2)){ if (targcol1 == 0){ targcol1 = rowbl2; } else{ targcol2 = rowbl2; } }

	if ((rowbl3 != boxcol1) && (rowbl3 != boxcol2)){ if (targcol1 == 0){ targcol1 = rowbl3; } else{ if (targcol2 == 0){ targcol2 = rowbl3; } } }
	if ((rowbl4 != boxcol1) && (rowbl4 != boxcol2)){ if (targcol2 == 0){ targcol2 = rowbl4; } }

	//if ((targcol1==0)||(targcol2==0)){//cout<<"ERROR FUNCTION ROWELIMTRIPLE LINE 11472 BOX="<<b<<endl;}
	int num1result1 = fincol(targcol1, targnum1);
	int num1result2 = fincol(targcol2, targnum1);
	int num2result1 = fincol(targcol1, targnum2);
	int num2result2 = fincol(targcol2, targnum2);
	result = 0;
	if ((num1result1>0) && (num1result2 == 0)){
	//	glastwrite = " 7589        "; result = inspuzzle(r3, targcol2, targnum1);
	//	glastwrite = "7590         "; result = inspuzzle(r3, targcol1, targnum2);
	}
	else{
		if ((num2result1>0) && (num2result2 == 0)){
		//	glastwrite = "7595         "; result = inspuzzle(r3, targcol2, targnum2);
		//	glastwrite = "7596         "; result = inspuzzle(r3, targcol1, targnum1);
		}
		else{
			if ((num1result2>0) && (num1result1 == 0)){
			//	glastwrite = "7601         "; result = inspuzzle(r3, targcol1, targnum1);
			//	glastwrite = "7602         "; result = inspuzzle(r3, targcol2, targnum2);
			}
			else{
				if ((num2result2>0) && (num2result1 == 0)){
				//	glastwrite = "7603         "; result = inspuzzle(r3, targcol1, targnum2);
			//		glastwrite = "7604         "; result = inspuzzle(r3, targcol2, targnum1);
				}
			}
		}
	}
	if (result>0){ ; }
	return result;
}
//==========================================================
//end boxsubtract2r3
//==========================================================

//==========================================================
int rowelimdouble(int r){
	//==========================================================
	//readpuzzle();
	int result = 0;
	////cout<<"in function rowelimdouble row="<<r<<endl;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
	int m1 = 0; int m2 = 0; int m3 = 0;
	int mcount = gminrow(r, m1, m2, m3);
	if (mcount != 3){ return 0; }
	int currentbl = gfb(zrow, r);
	int lastbl = glastbl(zrow, r);
	if ((currentbl == 0) || (lastbl == 0) || (m1 == 0) || (m2 == 0) || (m3 == 0)){
		//cout<<"ERROR FUNCTION ROWELIMDOUBLE LINE 11521 ROW="<<r<<endl;
		return 0;
	}
	while (currentbl <= lastbl){
		int elimcount = 0;
		int m1result = fincol(currentbl, m1);
		if (m1result>0){ ++elimcount; }
		int m2result = fincol(currentbl, m2);
		if (m2result>0){ ++elimcount; }
		int m3result = fincol(currentbl, m3);
		if (m3result>0){ ++elimcount; }
		if (elimcount == 2){
			if (m1result == 0){ glastwrite = "7642         "; result = inspuzzle(r, currentbl, m1); return result; } // this may be bad
			if (m2result == 0){ glastwrite = "7643         "; result = inspuzzle(r, currentbl, m2); return result; }
			if (m3result == 0){ glastwrite = "7644         "; result = inspuzzle(r, currentbl, m3); return result; }

		}
		if (currentbl == lastbl){ break; }
		currentbl = gnb(zrow, r, currentbl);
		if (currentbl == 0){ break; }
	}
	return 0;
}
//==========================================================
//end rowelimdouble
//==========================================================
//==========================================================
int rowelimtriple(int r){
	//==========================================================
	//readpuzzle();
	int result = 0;
	////cout<<"in function rowelimtriple row="<<r<<endl;
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int mcount = gallminrow(r, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	if (mcount != 4){ return 0; }
	int currentbl = gfb(zrow, r);
	int lastbl = glastbl(zrow, r);
	if ((currentbl == 0) || (lastbl == 0) || (m1 == 0) || (m2 == 0) || (m3 == 0) || (m4 == 0)){
		//cout<<"ERROR FUNCTION ROWELIMTRIPLE LINE 11560 ROW="<<r<<endl;
		return 0;
	}
	while (currentbl <= lastbl){
		int elimcount = 0;
		int m1result = fincol(currentbl, m1);
		int m2result = fincol(currentbl, m2);
		int m3result = fincol(currentbl, m3);
		int m4result = fincol(currentbl, m4);
		if (m1result>0){ ++elimcount; }
		if (m2result>0){ ++elimcount; }
		if (m3result>0){ ++elimcount; }
		if (m4result>0){ ++elimcount; }
		if (elimcount == 3){
			if (m1result == 0){ glastwrite = "7682         "; result = inspuzzle(r, currentbl, m1); return result; }
			if (m2result == 0){ glastwrite = "7683         "; result = inspuzzle(r, currentbl, m2); return result; }
			if (m3result == 0){ glastwrite = "7684         "; result = inspuzzle(r, currentbl, m3); return result; }
			if (m4result == 0){ glastwrite = "7685         "; result = inspuzzle(r, currentbl, m4); return result; }
		}
		if (currentbl == lastbl){ break; }
		currentbl = gnb(zrow, r, currentbl);
		if (currentbl == 0){ break; }
	}
	return 0;
}
//==========================================================
//end rowelimtriple
//==========================================================
//==========================================================
int colelimtriple(int c){
	//==========================================================
	int result = 0;
	////cout<<"in function colelimtriple col="<<c<<endl;
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int mcount = gallmincol(c, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	if (mcount != 4){ return 0; }
	int currentbl = gfb(zcol, c);
	int lastbl = glastbl(zcol, c);
	if ((currentbl == 0) || (lastbl == 0) || (m1 == 0) || (m2 == 0) || (m3 == 0) || (m4 == 0)){
		//cout<<"ERROR FUNCTION COLELIMTRIPLE LINE 11600 COL="<<c<<endl;
		return 0;
	}

	while (currentbl <= lastbl){
		int elimcount = 0;
		int m1result = finrow(currentbl, m1);
		int currentbox = gboxfromcolandpos(c, currentbl);
		int boxres1 = finbox(currentbox, m1);
		if (boxres1>0){ m1result = boxres1; }
		int m2result = finrow(currentbl, m2);
		int m3result = finrow(currentbl, m3);
		int m4result = finrow(currentbl, m4);
		if (m1result>0){ ++elimcount; }
		if (m2result>0){ ++elimcount; }
		if (m3result>0){ ++elimcount; }
		if (m4result>0){ ++elimcount; }
		if (elimcount == 3){
			if (m1result == 0){ glastwrite = "7726"; result = inspuzzle(currentbl, c, m1); return result; }
			else{
				if (m2result == 0){ glastwrite = "7727"; result = inspuzzle(currentbl, c, m2); return result; }
				else{
					if (m3result == 0){ glastwrite = "7728"; result = inspuzzle(currentbl, c, m3); return result; }
					else{ if (m4result == 0){ glastwrite = "7729"; result = inspuzzle(currentbl, c, m4); return result; } }
				}
			}

		}
		if (currentbl == lastbl){ break; }
		currentbl = gnb(zcol, c, currentbl);
		if (currentbl == 0){ break; }
	}
	return 0;
}
//==========================================================
//end colelimtriple
//==========================================================
//==========================================================
int colelimdouble(int c){
	//==========================================================
	int result = 0;
	//if (debug){ cout << "in function colelimdouble col=" << c << endl; }

	int m1, m2, m3, m4, m5, m6, m7, m8, m9;
	int res = 0;
	int mcount = gallmincol(c, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	if (mcount != 3){ return 0; }
	int currentbl = gfb(zcol, c);
	int lastbl = glastbl(zcol, c);
	if ((currentbl == 0) || (lastbl == 0) || (m1 == 0) || (m2 == 0) || (m3 == 0)){
		glerr = true;
		return 0;
	}
	while (currentbl <= lastbl){
		int elimcount = 0;
		int m1result = finrow(currentbl, m1);
		int m2result = finrow(currentbl, m2);
		int m3result = finrow(currentbl, m3);

		if (m1result>0){ ++elimcount; }
		if (m2result>0){ ++elimcount; }
		if (m3result>0){ ++elimcount; }

		if (elimcount == 2){
			if (m1result == 0){ glastwrite = "colelimdouble1";   res =  inspuzzle(currentbl, c, m1); }
			if (m2result == 0){ glastwrite = "colelimdouble2";   res = inspuzzle(currentbl, c, m2); }
			if (m3result == 0){ glastwrite = "colelimdouble3";   res =inspuzzle(currentbl, c, m3); }
			
		}
		if (currentbl == lastbl){ break; }
		currentbl = gnb(zcol, c, currentbl);
		if (currentbl == 0){ break; }
	}
	return res;
}
//==========================================================
//end colelimdouble
//==========================================================
//==========================================================   
int procallnumbersrow(int r){
	//========================================================== 

	////cout<<"in function procallnumbersrow row="<<r<<endl;  

	//readpuzzle();
	if (row[r].done == true){ return 0; }
	//readboxes();

	int mcount = 0;
	int result = 0;

	//basic algorithm will be
	//1. collect all bls
	//2. collect all m numbers
	//3. cycle each m number through 2 different ways:
	//3a.to see if there is already that number present in all bls except 1  (the easy check)
	//3b.The hard check will be to run each m number through and check how many places it could go.
	//   once it has done that for all the numbers in the m number list, it will see if any 
	//   of the m numbers can go in only one spot.  if so, it will insert that number and then
	//   repeat the proc with the remaining numbers until no remaining number can only go in one bl.
	//
	//   new functions used : gallminrow  

	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	mcount = gallminrow(r, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	if (mcount == 0){
		row[r].done = true;
		//    //cout<<"ROW COMPLETE FUNCTION procALLNUMBERSROW  ROW="<<r<<endl; 
		return 0;
	}
	int currentm[10];

	currentm[1] = m1;
	currentm[2] = m2;
	currentm[3] = m3;
	currentm[4] = m4;
	currentm[5] = m5;
	currentm[6] = m6;
	currentm[7] = m7;
	currentm[8] = m8;
	currentm[9] = m9;


	int currentbl = 0;
	int firstbl = gfb(zrow, r);
	 
	int lastbl = glastbl(zrow, r);
	 

	if ((firstbl == 0) || (lastbl == 0)){
		//cout<<"ERROR procALLNUMBBERSROW"<<endl;
		return 0;
	}

	for (int i = 1; i <= mcount; ++i){
		int currentresult = 0;
		int elimcount = 0;
		int targbl = 0;
		//int firstbl = gfb(zrow, r);   //8-7-18
		//int lastbl = glastbl(zrow, r);
		currentbl = firstbl;
		while (currentbl <= lastbl){
			if (currentbl == 0){ break; }
			currentresult = fincol(currentbl, currentm[i]);
			if (currentresult>0){ ++elimcount; }
			else{ targbl = currentbl; }
			if (currentbl == lastbl){ break; }
			currentbl = gnb(zrow, r, currentbl);
		}
		if ((elimcount == mcount - 1) && (targbl>0)){

			int tbox = gboxfromrowandpos(r, targbl);
			int tboxres = finbox(tbox, currentm[i]);

			if (tboxres == 0){
			    glastwrite = "7855"; result = inspuzzle(r, targbl, currentm[i]); return result;

			}
		}
		if (glerr){ break; }
	}
	return result;
	//return result;
}

//==========================================================   
//end procallnumbersrow
//==========================================================    
//==========================================================   
int procallnumberscol(int c){
	//========================================================== 

	////cout<<"in function procallnumberscol col="<<c<<endl;  

	//readpuzzle();
	if (col[c].done == true){ return 0; }
	//readboxes();

	int mcount = 0;
	int result = 0;

	//basic algorithm will be
	//1. collect all bls
	//2. collect all m numbers
	//3. cycle each m number through 2 different ways:
	//3a.to see if there is already that number present in all bls except 1  (the easy check)
	//3b.The hard check will be to run each m number through and check how many places it could go.
	//   once it has done that for all the numbers in the m number list, it will see if any 
	//   of the m numbers can go in only one spot.  if so, it will insert that number and then
	//   repeat the proc with the remaining numbers until no remaining number can only go in one bl.
	//
	//   new functions used : gallmincol  

	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	mcount = gallmincol(c, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	if (mcount == 0){
		col[c].done = true;
		return 0;
	}
	int currentm[10];

	currentm[1] = m1;
	currentm[2] = m2;
	currentm[3] = m3;
	currentm[4] = m4;
	currentm[5] = m5;
	currentm[6] = m6;
	currentm[7] = m7;
	currentm[8] = m8;
	currentm[9] = m9;


	int currentbl = 0;
	int firstbl = gfb(zcol, c);
	int lastbl = glastbl(zcol, c);

	if ((firstbl == 0) || (lastbl == 0)){
		//cout<<"ERROR procALLNUMBBERSCOL"<<endl;
		return 0;
	}

	for (int i = 1; i <= mcount; ++i){
		int currentresult = 0;
		int elimcount = 0;
		int targbl = 0;
		currentbl = firstbl;
		while (currentbl <= lastbl){
			if (currentbl == 0){ break; }
			currentresult = finrow(currentbl, currentm[i]);
			if (currentresult>0){ ++elimcount; }
			else{ targbl = currentbl; }
			if (currentbl == lastbl){ break; }
			currentbl = gnb(zcol, c, currentbl);
		}
		if ((elimcount == mcount - 1) && (targbl>0)){
			int tbox = gboxfromcolandpos(c, targbl);
			int tboxres = finbox(tbox, currentm[i]);

			if (tboxres == 0){
		
				glastwrite = "7946         "; result = inspuzzle(targbl, c, currentm[i]);
				
				 return result;
				if (glerr){ break; }
			}
		}
		if (glerr){ break; }
	}

	//return result;
	return 0;
}

//==========================================================   
//end procallnumberscol
//==========================================================    
//==========================================================   
int procallnumbersbox(int b){
//========================================================== 

	////cout<<"in function procallnumbersbox box="<<b<<endl;  

	//readpuzzle();
	//if (box[b].done==true){//cout<<"box COMPLETE FUNCTION procALLNUMBERSBOX  BOX="<<b<<endl; return 0;}   


	int mcount = 0;
	int result = 0;

	//basic algorithm will be
	//1. collect all bls
	//2. collect all m numbers
	//3. cycle each m number through 2 different ways:
	//3a.to see if there is already that number present in all bls except 1  (the easy check)
	//3b.The hard check will be to run each m number through and check how many places it could go.
	//   once it has done that for all the numbers in the m number list, it will see if any 
	//   of the m numbers can go in only one spot.  if so, it will insert that number and then
	//   repeat the proc with the remaining numbers until no remaining number can only go in one bl.
	//
	//   new functions used : gallminbox  

	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	if (mcount == 0){
		box[b].done = true;
		return 0;
	}
	int currentm[10];

	currentm[1] = m1;
	currentm[2] = m2;
	currentm[3] = m3;
	currentm[4] = m4;
	currentm[5] = m5;
	currentm[6] = m6;
	currentm[7] = m7;
	currentm[8] = m8;
	currentm[9] = m9;


	int currentbl = 0;
	int firstbl = gfb(zbox, b);
	int lastbl = glastbl(zbox, b);

	if ((firstbl == 0) || (lastbl == 0)){
		//cout<<"ERROR procALLNUMBBERSBOX"<<endl;
		return 0;
	}
	int currentresult = 0;
	int elimcount = 0;
	int targbl = 0;
	int targrow = 0;
	int targcol = 0;
	int cm = 0;
	int currentrow = 0;
	int currentcol = 0;
	for (int i = 1; i <= mcount; ++i){
		currentresult = 0;
		elimcount = 0;
		targbl = 0;
		targrow = 0;
		targcol = 0;
		currentbl = firstbl;
		while (currentbl <= lastbl){
			if (currentbl == 0){ break; }
			currentcol = gcolfromboxandpos(b, currentbl);
			currentrow = growfromboxandpos(b, currentbl);
			cm = currentm[i];
			int currentresultrow = finrow(currentrow, cm);
			int currentresultcol = fincol(currentcol, cm);
			if ((currentresultrow>0) || (currentresultcol>0)){ ++elimcount; }
			else{ targbl = currentbl; targrow = currentrow; targcol = currentcol; }
			if (currentbl == lastbl){ break; }
			currentbl = gnb(zbox, b, currentbl);
		}

	}
	if ((elimcount == mcount - 1) && (targbl>0)){

		glastwrite = "8044"; result = inspuzzle(targrow, targcol, cm);

		return result;
	}
	return 0;
}

//==========================================================   
//end procallnumbersbox
//==========================================================    


//==========================================================   
//==========================================================



//==========================================================
int c3bl(int b){
	//==========================================================
	//   //cout<<"in function c3bl box="<<b<<endl;
	if ((box[b].bcnt == 0) || (box[b].done)){ return 0; }
//	for (int i = 1; i <= 9; ++i){ box[b].hash[i] = 0; }
	//                         
	//readpuzzle();
//	box[b].bcnt = 0;
//	readbox(b);
	int result = 0;
	int targbl = 0;
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int firstbl = 0;
	if (mcount != 4){ return 0; }

	bool col3bl = box[b].c3empty;
	if (!col3bl){ return 0; }
	if (box[b].c2done == true){
		if (box[b].c1[1] == 0){ targbl = 1; }
		else{
			if (box[b].c1[2] == 0){ targbl = 4; }
			else{
				targbl = 7;
			}
		}
	}
	if (targbl == 0){ return 0; }
	int c3 = gcolfromboxandpos(b, 3);
	int targrow = growfromboxandpos(b, targbl);
	int targcol = gcolfromboxandpos(b, targbl);
	int elimc3m1 = fincol(c3, m1);
	int elimc3m2 = fincol(c3, m2);
	int elimc3m3 = fincol(c3, m3);
	int elimc3m4 = fincol(c3, m4);

	int m1foundinbox = finbox(b, m1);
	int m2foundinbox = finbox(b, m2);
	int m3foundinbox = finbox(b, m3);
	int m4foundinbox = finbox(b, m4);

	int targnum = 0;
	if ((elimc3m1 == 0) && (m1foundinbox>0)){ targnum = m1; }
	if ((elimc3m2 == 0) && (m2foundinbox>0)){ targnum = m2; }
	if ((elimc3m3 == 0) && (m3foundinbox>0)){ targnum = m3; }
	if ((elimc3m4 == 0) && (m4foundinbox>0)){ targnum = m4; }

	if (targnum>0){ glastwrite = "8178         "; result = inspuzzle(targrow, targcol, targnum); }
	;
	return result;
}
//==========================================================
//end c3bl
//==========================================================

//==========================================================
int c1bl(int b){
	//==========================================================
	//  //cout<<"in function c1bl box="<<b<<endl;
	if ((box[b].bcnt == 0) || (box[b].done)){ return 0; }
//	for (int i = 1; i <= 9; ++i){ box[b].hash[i] = 0; }
	//                         
	//readpuzzle();
	//box[b].bcnt = 0;
	//readbox(b);

	int result = 0;
	int targbl = 0;
	int m1 = 0; int m2 = 0; int m3 = 0; int m4 = 0; int m5 = 0; int m6 = 0; int m7 = 0; int m8 = 0; int m9 = 0;
	int mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	int firstbl = 0;
	if (mcount != 4){ return 0; }
	int col1bl = 0;
	col1bl = box[b].c1[1] + box[b].c1[2] + box[b].c1[3];
	if (col1bl != 0){ return 0; }
	if (box[b].c2done == true){
		if (box[b].c3[1] == 0){ targbl = 3; }
		else{
			if (box[b].c3[2] == 0){ targbl = 6; }
			else{
				targbl = 9;
			}
		}
	}
	if (targbl == 0){ return 0; }
	int c1 = gcolfromboxandpos(b, 1);
	int targrow = growfromboxandpos(b, targbl);
	int targcol = gcolfromboxandpos(b, targbl);
	int elimc1m1 = fincol(c1, m1);
	int elimc1m2 = fincol(c1, m2);
	int elimc1m3 = fincol(c1, m3);
	int elimc1m4 = fincol(c1, m4);

	int m1foundinbox = finbox(b, m1);
	int m2foundinbox = finbox(b, m2);
	int m3foundinbox = finbox(b, m3);
	int m4foundinbox = finbox(b, m4);

	int targnum = 0;
	if ((elimc1m1 == 0) && (m1foundinbox>0)){ targnum = m1; }
	if ((elimc1m2 == 0) && (m2foundinbox>0)){ targnum = m2; }
	if ((elimc1m3 == 0) && (m3foundinbox>0)){ targnum = m3; }
	if ((elimc1m4 == 0) && (m4foundinbox>0)){ targnum = m4; }

	if (targnum>0){ glastwrite = "8235         "; result = inspuzzle(targrow, targcol, targnum); }
	;
	return result;
}
//==========================================================
//end c1bl

//==========================================================
void initemptyboxrowsandcols(int b){
	//==========================================================
	int totr1 = 0; int totr2 = 0; int totr3 = 0;
	int totc1 = 0; int totc2 = 0; int totc3 = 0;

	box[b].r1empty = false;
	box[b].r2empty = false;
	box[b].r3empty = false;
	box[b].c1empty = false;
	box[b].c2empty = false;
	box[b].c3empty = false;


	for (int x = 1; x <= 3; ++x) {
		totr1 = totr1 + box[b].r1[x];
		totr2 = totr2 + box[b].r2[x];
		totr3 = totr3 + box[b].r3[x];
		totc1 = totc1 + box[b].c1[x];
		totc2 = totc2 + box[b].c2[x];
		totc3 = totc3 + box[b].c3[x];
	}
	if (!totr1) { box[b].r1empty = true; }
	if (!totr2) { box[b].r2empty = true; }
	if (!totr3) { box[b].r3empty = true; }
	if (!totc1) { box[b].c1empty = true; }
	if (!totc2) { box[b].c2empty = true; }
	if (!totc3) { box[b].c3empty = true; }

	return;
}
//==========================================================
//end initemptyboxrowsandcols(int b){

///==========================================================
int box4cancelbls(int b){
	//==========================================================

	////cout<<"in function box4cancelbls b="<<b<<endl;
	int result = 0;
	int m1, m2, m3, m4, m5, m6, m7, m8, m9;
	int b1, b2, b3, b4, b5, b6, b7, b8, b9;
	int mcount = 0;
	int m1res = 0; int m2res = 0; int m3res = 0; int m4res = 0;
	mcount = gallminbox(b, m1, m2, m3, m4, m5, m6, m7, m8, m9);
	gallblsinbox(b, b1, b2, b3, b4, b5, b6, b7, b8, b9);

	int r1 = growfromboxandpos(b, 1);
	int r2 = r1 + 1;
	int r3 = r2 + 1;
	int c1 = gcolfromboxandpos(b, 1);
	int c2 = c1 + 1;
	int c3 = c2 + 1;
	int targnum = 0;
	int m1resc = 0;
	int m2resc = 0;
	int m3resc = 0;
	int m4resc = 0;
	int targnumc = 0;
	if (mcount != 4){ return 0; }

	if ((box[b].r1done) && (box[b].r3empty)){
		//middle row has one bl which might be "eliminated"
		//if all three bls in r3 can be cancelled by one m
		//number, then that number which cancels the row is the m
		//number in the middle row.  Simple....
		m1res = finrow(r3, m1);
		m2res = finrow(r3, m2);
		m3res = finrow(r3, m3);
		m4res = finrow(r3, m4);
	}
	if ((box[b].r3done) && (box[b].r1empty)){
		//same deal
		m1res = finrow(r1, m1);
		m2res = finrow(r1, m2);
		m3res = finrow(r1, m3);
		m4res = finrow(r1, m4);
	}
	if ((box[b].c1done) && (box[b].c3empty)){
		//middle col has one bl which might be "eliminated"
		//if all three bls in c3 can be cancelled by one m
		//number, then that number which cancels the col is the m
		//number in the middle col.  Simple....
		m1resc = fincol(c3, m1);
		m2resc = fincol(c3, m2);
		m3resc = fincol(c3, m3);
		m4resc = fincol(c3, m4);
	}
	if ((box[b].c3done) && (box[b].c1empty)){
		//middle col has one bl which might be "eliminated"
		//if all three bls in c3 can be cancelled by one m
		//number, then that number which cancels the col is the m
		//number in the middle col.  Simple....
		m1resc = fincol(c1, m1);
		m2resc = fincol(c1, m2);
		m3resc = fincol(c1, m3);
		m4resc = fincol(c1, m4);
	}


	targnum = 0;
	if (m1res>0){ targnum = m1; }//cout<<"targnum="<<targnum<<endl;}
	else{
		if (m2res>0){ targnum = m2; }
		else{
			if (m3res>0){ targnum = m3; }
			else{
				if (m4res>0){ targnum = m4; }
			}
		}
	}
	targnumc = 0;
	if (m1resc>0){ targnumc = m1; }//cout<<"targnumc="<<targnumc<<endl;}    
	else{
		if (m2resc>0){ targnumc = m2; }
		else{
			if (m3resc>0){ targnumc = m3; }
			else{
				if (m4resc>0){ targnumc = m4; }
			}
		}
	}

	if (targnum){
		int targcol = 0;
		//find the bl in r2
		if (box[b].r2[1] == 0){ targcol = c1; }
		else{
			if (box[b].r2[2] == 0){ targcol = c2; }
			else{
				if (box[b].r2[3] == 0){ targcol = c3; }
			}
		}

		if (targcol){
			glastwrite = "8377         "; result = inspuzzle(r2, targcol, targnum);
			;
			return result;
		}
	}
	if (targnumc){
		int targrow = 0;
		//find the bl in c2
		if (box[b].c2[1] == 0){ targrow = r1; }
		else{
			if (box[b].c2[2] == 0){ targrow = r2; }
			else{
				if (box[b].c2[3] == 0){ targrow = r3; }
			}
		}
		if (targrow){
			glastwrite = "8393         "; result = inspuzzle(targrow, c2, targnumc);
			;
			return result;
		}
	}
	return 0;
}
//==========================================================
//end  box4cancelbls(b){
//==========================================================
//==========================================================


//========================================================== 
void procpuzzle(){
	//==========================================================   
	//==========================================================    
	
	if (debug){ cout << "in function proc puzzle. Zcnt="<<zcnt << "lzcnt="<<lzcnt<<"stackptr="<<stackptr<<endl; }
	//debug = false;
	if (glerr){ return; }
	int tzcnt = zcnt;
	//checkfin();
	int res = 0;
	thisisaguess = false;
	for (int unit = 1; unit <= 3; ++unit){
		procrowunit(unit);
		if (glerr){ break; }
	}
	if (glerr){ return; }
	for (int unit = 1; unit <= 3; ++unit){
		proccolunit(unit);
		if (glerr){ break; }
	}
	if (glerr){ return; }
	for (int c = 1; c <= 3; c++){
		for (int v = 1; v <= 9; v++){
			int res = col123(c, v);
			if (glerr){ break; }
		}
		if (glerr){ break; }
	}
	if (glerr){ return; }
	for (int c = 4; c <= 6; c++){
		for (int v = 1; v <= 9; v++){
			int res = col456(c, v);
			if (glerr){ break; }
		}
		if (glerr){ break; }
	}
	if (glerr){ return; }
	for (int c = 7; c <= 9; c++){
		for (int v = 1; v <= 9; v++){
			int res = col789(c, v);
			if (glerr){ break; }
		}
		if (glerr){ break; }
	}
	if (glerr){ return; }

	for (int v = 1; v <= 9; v++){
		res = cornercancel(1, v);
		if (glerr){ break; }
		res = cornercancel(3, v);
		if (glerr){ break; }
		res = cornercancel(7, v);
		if (glerr){ break; }
		res = cornercancel(9, v);
		if (glerr){ break; }
	}
	if (glerr){ return; }

	for (int r = 1; r <= 9; r++){
		for (int v = 1; v <= 9; v++){
			res = newalgorithm(r, v);
			if (glerr){ break; }
		}
		if (glerr){ break; }
	}
	if (glerr){ return; }

	//loop by row
	for (int i = 1; i <= 9; ++i){
		res = checkcnt(zrow, i);
		if (glerr){ break; }
		if (res){ continue; }

		int mcnt = gm(zrow, i);
		int bcnt = gbls(zrow, i);
		if (bcnt == 0){ continue; }
		if (row[i].done) { continue; }
		if (mcnt == 0){ continue; }
		if (glerr){ break; }

		fnc = 1;  res = procallnumbersrow(i);
		if (res){ continue; }
		if (glerr){ break; }

		res = checkcnt(zrow, i);
		if (res){ continue; }
		if (glerr){ break; }

		fnc = 14; res = row5elim(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 26; res = rowelimdouble(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 28; res = rowelimtriple(i);
		if (glerr){ break; }
		if (res){ continue; }

		//sanitycheck set error

	
	}//loop by row
	if (glerr){ return; }
	//loop by col
	for (int i = 1; i <= 9; i++){
		res = checkcnt(zcol, i);
		if (glerr){ break; }
		if (res){ continue; }

		int mcnt = gm(zcol, i);
		int bcnt = gbls(zcol, i);
		if (col[i].done) { continue; }
		if (mcnt == 0){ continue; }
		if (glerr){ break; }

		fnc = 2;  res = procallnumberscol(i);
		if (glerr){ break; }
		if (res){ continue; }

		res = checkcnt(zcol, i);
		if (glerr){ break; }
		if (res){ continue; }

		fnc = 15; res = col5elim(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 27; res = colelimdouble(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 29; res = colelimtriple(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 30; res = c1bl(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 31; res = c3bl(i);
		if (glerr){ break; }
		if (res){ continue; }
		res = checkcnt(zcol, i);
		if (glerr){ break; }
		if (res){ continue; }
		//sanitycheck set error

		mcnt = gm(zcol, i);
		bcnt = gm(zcol, i);
		int done = col[i].done;

	 
		
	 }//loop by col
	if (glerr){ return; }
	//loop by box

	for (int i = 1; i <= 9; i++){
		res = checkcnt(zbox, i);
		if (glerr){ break; }
		if (res){ continue; }
		int mcnt = gm(zbox, i);
		if (box[i].done) { continue; }
		if (mcnt == 0){ continue; }
		int bcnt = gm(zbox, i);
		if (bcnt == 0){ continue; }

		fnc = 4; res = box2elimcol(i);
		if (res){ continue; }
		if (glerr){ break; }
		fnc = 3; res = procallnumbersbox(i);
		if (glerr){ break; }
		if (res){ continue; }

		res = checkcnt(zbox, i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 5; res = box3elimrow(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 6; res = box3elimcol(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 7; res = boxrow3done4(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 8; res = boxrow3done3(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 9; res = boxcol3done4(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 11; res = boxelimr1done(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 12; res = boxelimr2done(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 13; res = boxelimr3done(i);
		if (glerr){ break; }
		fnc = 16; res = box5elim(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 18; res = boxelimc2done(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 17; res = boxelimc1done(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 19; res = boxelimc3done(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 20; res = boxsubtract2c1(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 21; res = boxsubtract2c2(i);
		if (glerr){ break; }
		fnc = 22; res = boxsubtract2c3(i);
		if (glerr){ break; }
		fnc = 23; res = boxsubtract2r1(i);
		if (glerr){ break; }
		fnc = 24; res = boxsubtract2r2(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 25; res = boxsubtract2r3(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 32; res = eliminateinbox(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 33; res = box3elim(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 34; res = boxandcolelim3row(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 35; res = boxandrowelim3col(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 36; res = box4cancelbls(i);
		if (glerr){ break; }
		if (res){ continue; }
		fnc = 37; res = moreboxprocing(i);
		if (glerr){ break; }
		if (res){ continue; }
		res = checkcnt(zbox, i);
		if (glerr){ break; }
		if (res){ continue; }
		//sanitycheck set error
	}
	if (glerr){ return; }
	checkcnts();
	if (tzcnt == zcnt){ lzcnt = zcnt; }
  
	//thisisaguess = true;
	//debug = true;
	return;
}

//=========================================================
void initp(){
//	if ((saveonce) && (glerr)){ cout << "grave err" << endl; exit(0); }
	if (saveonce == 1){
		writeinitialpuzzle();

		saveinitialpuzzle();
		readpuzzle();
		updp();
		creategtable();

		initlastwrite();
		
		procpuzzle();
		writeinitialpuzzle();

		saveinitialpuzzle();	                         
		updp();

	}

	for (int i = 1; i <= 9; i++){
		gm(zrow, i);
		gbls(zrow, i);
		gm(zcol, i);
		gbls(zcol, i);
		gm(zbox, i);
		gbls(zbox, i);
	}
	 
	updp();
	if (saveonce == 1){
		//time to start timing
		saveonce = 0;
		//start_time = time(NULL);
		// gltime1 = std::chrono::high_resolution_clock::now();
		gltime1 = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
		// start_time = chrono::high_resolution_clock::now();

	}

}

//=========================================================
void checkfin(){
	if (zcnt == 0){
		//worder(lastwrite[1].r, lastwrite[1].c, lastwrite[1].v);
		checksumall(); exit(0); }
	return;
}
//=========================================================
void procp(){
//	checkfin();
	while (true){
		lzcnt = zcnt;
		procpuzzle();
		checkcnts();
		if (glerr){ break; }
		if (zcnt >= lzcnt){ break; }
	}
	lzcnt=zcnt;
	//checkfin();
	return;
}

//======================================================
int  gm(int etype, int i){
	//=========================
	int m1, m2, m3, m4, m5, m6, m7, m8, m9;
	int mcnt;
	if (i<1){ return 0; }

	switch (etype){

	case zrow: for (int j = 1; j <= 9; j++){ mrow[j] = 0; }
			   mcnt = gallminrow(i, m1, m2, m3, m4, m5, m6, m7, m8, m9);
			   mrow[1] = m1; mrow[2] = m2; mrow[3] = m3; mrow[4] = m4; mrow[5] = m5; mrow[6] = m6; mrow[7] = m7; mrow[8] = m8; mrow[9] = m9;
			   if (mcnt == 0){ row[i].done = true; }
			   return mcnt;
			   break;

	case zcol: for (int j = 1; j <= 9; j++){ mcol[j] = 0; }
			   mcnt = gallmincol(i, m1, m2, m3, m4, m5, m6, m7, m8, m9);
			   mcol[1] = m1; mcol[2] = m2; mcol[3] = m3; mcol[4] = m4; mcol[5] = m5; mcol[6] = m6; mcol[7] = m7; mcol[8] = m8; mcol[9] = m9;
			   if (mcnt == 0){ col[i].done = true; }
			   return  mcnt;
			   break;

	case zbox: for (int j = 1; j <= 9; j++){ mbox[j] = 0; }
			   mcnt = gallminbox(i, m1, m2, m3, m4, m5, m6, m7, m8, m9);
			   mbox[1] = m1; mbox[2] = m2; mbox[3] = m3; mbox[4] = m4; mbox[5] = m5; mbox[6] = m6; mbox[7] = m7; mbox[8] = m8; mbox[9] = m9;
			   if (mcnt == 0){ box[i].done = true; }
			   return mcnt;
			   break;
	}

	return 0;
}
//=========================
//end gm
//=========================
//=========================
int  gbls(int etype, int i){
	//=========================
	int b1, b2, b3, b4, b5, b6, b7, b8, b9;
	int bcnt;
	if (i<1){ return 0; }

	switch (etype){

	case zrow: for (int j = 1; j <= 9; j++){ blrow[j] = 0; }
			   bcnt= gallblsinrow(i, b1, b2, b3, b4, b5, b6, b7, b8, b9);
			   blrow[1] = b1; blrow[2] = b2; blrow[3] = b3; blrow[4] = b4; blrow[5] = b5; blrow[6] = b6; blrow[7] = b7; blrow[8] = b8; blrow[9] = b9;
			   if (bcnt == 0){ row[i].done = true; }
			   return bcnt;
			   break;

	case zcol: for (int j = 1; j <= 9; j++){ blcol[j] = 0; }
			   bcnt = gallblsincol(i, b1, b2, b3, b4, b5, b6, b7, b8, b9);
			   blcol[1] = b1; blcol[2] = b2; blcol[3] = b3; blcol[4] = b4; blcol[5] = b5; blcol[6] = b6; blcol[7] = b7; blcol[8] = b8; blcol[9] = b9;
			   if (bcnt == 0){ col[i].done = true; }
			   return bcnt;
			   break;

	case zbox: for (int j = 1; j <= 9; j++){ blbox[j] = 0; }
			   bcnt = gallblsinbox(i, b1, b2, b3, b4, b5, b6, b7, b8, b9);
			   blbox[1] = b1; blbox[2] = b2; blbox[3] = b3; blbox[4] = b4; blbox[5] = b5; blbox[6] = b6; blbox[7] = b7; blbox[8] = b8; blbox[9] = b9;
			   if (bcnt == 0){ box[i].done = true; }
			   return bcnt;
			   break;
	}

	return 0;
}
//=========================
//end gbls
//=========================
//=========================
void initex(int etype, int i){
	//=========================
	
	switch (etype){
	case zrow:
		for (int i = 1; i <= 9; i++){			
			gbls(zrow, i);
			setexstart(zrow, i);
		}
		break;

	case zcol:
		for (int i = 1; i <= 9; i++){
			
			gbls(zcol, i);
			setexstart(zcol, i);
		}
		break;

	case zbox:
		for (int i = 1; i <= 9; i++){
			
			gbls(zbox, i);
			setexstart(zbox, i);
		}
		break;
	}
	return;
}
//=========================
//end initex
//=========================
void setexstart(int etype, int i){
	//=========================
	int mcnt = 0;
	switch (etype){
	case zrow:
		mcnt = gm(zrow, i);
		if (mcnt == 0){ row[i].done = true; break; }		 
		break;

	case zcol:
		mcnt = gm(zcol, i);
		if (mcnt == 0){ col[i].done = true; break; }
				break;
	case zbox:
		mcnt = gm(zbox, i);
		if (mcnt == 0){ box[i].done = true; break; }
		

		break;
	}
	return;
}
//=========================
//end setexstart
//=========================

//===============================
int gprevnum(int etype, int x, int cnum){
	//===============================

	if (etype>2){ return 0; }
	if ((x<1) || (x>9)){ return 0; }
	if ((cnum<1) || (cnum>9)){ return 0; }

	int mcnt = 0;

	switch (etype){
	case zrow: mcnt = gm(zrow, x); break;
	case zcol: mcnt = gm(zcol, x); break;
	case zbox: mcnt = gm(zbox, x); break;
		return 0;
		break;
	}
	if (mcnt<2){ return 0; }

	switch (etype){
	case zrow:
		for (int i = 1; i<mcnt; i++){ if (mrow[i] == cnum){ return mrow[i - 1]; } }break;
	case zcol:
		for (int i = 1; i<mcnt; i++){ if (mcol[i] == cnum){ return mcol[i - 1]; } }break;
	case zbox:
		for (int i = 1; i<mcnt; i++){ if (mbox[i] == cnum){ return mbox[i - 1]; } }break;
		return 0;
		break;
	}
	return 0;
}

//==================================
int first(int etype, int x){
	//==================================

	if (etype>2){ return 0; }
	if ((x<1) || (x>9)){ return 0; }

	int mcnt = 0;
	bool found = false;

	switch (etype){
	case zrow: mcnt = gm(zrow, x); return mrow[1]; break;
	case zcol: mcnt = gm(zcol, x); return mcol[1]; break;
	case zbox: mcnt = gm(zbox, x); return mbox[1]; break;
		return -1;
		break;
	}
	return 0;
}
//==================================
int last(int etype, int x){
	//==================================

	if (etype>2){ return 0; }
	if ((x<1) || (x>9)){ return 0; }

	int mcnt = 0;
	bool found = false;

	switch (etype){
	case zrow: mcnt = gm(zrow, x); return mrow[mcnt]; break;
	case zcol: mcnt = gm(zcol, x); return mcol[mcnt]; break;
	case zbox: mcnt = gm(zbox, x); return mbox[mcnt]; break;
		return 0;//
		break;
	}
	return 0;
}
int replayglist(){
	return 0;
	popp();
	int const A = 1;
	int const B = 2;
	//int r, c, v, tptr;
	int r = 0;
	int c = 0;
	int v = 0;
	int tptr = 0;
	int listptr = 1;
	int lasttried = 0;
	while (true){
		if ((listptr == 1) || (listptr == top)){
			tptr = glist[listptr].gptr;
			if (glist[listptr].AorB == A){
				r = Brow[tptr].r;
				c = Brow[tptr].c;
				v = Brow[tptr].v;
				glist[listptr].lasttried = listptr;
			}
			else{
				if (glist[listptr].AorB == B){
					r = Arow[tptr].r;
					c = Arow[tptr].c;
					v = Arow[tptr].v;
					glist[listptr].lasttried = listptr;

				}
			}
			glastwrite = "replayglist";
			int res = inspuzzle(r, c, v);
			if (res > 0){
				procp();
				if (!glerr){
					if (lasttried == A){
						glist[listptr].AorB = A;
					}
					else{
						glist[listptr].AorB = B;
					}

					glist[listptr].r = r;
					glist[listptr].c = c;
					glist[listptr].v = v;
				}
			}
		}
		//if (glerr){ delgtable(listptr); popp(); }//inconclusive lower on stack
		if (glerr){ popp(); }
		listptr++;
		if (listptr > top){ break; }

	}
	return 0;
}




//==========================================================
int inspuzzle(int r, int c, int v){
	//==========================================================
	int res = 0;
 
	errorcode = checkinsert(r, c, v);
	if (errorcode > 0){
		glerr = true;
		if (debug){
			cout << "glerr=trueXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx" << endl;
			cout << "guesscount=" << guesscount << endl;
			printglist();
		}
		if (gfirstguess){ printpuzzle(); cout << "fatal error!!!!!!!!!!!!!!!" << endl; exit(0); }
		res = 0;
	//	debug = true;
		//if (thisisaguess == false){
//if (guesscount > 0){
				//printpuzzle();
				//cout << "IN REPLAYGLIST" << endl;
				//replayglist();
			//	printglist();
			//	return 0;
			//}
//}
		if (debug){
			cout << "errorcode=" << errorcode << endl;
			cout << "rcv=" << r << c << v << endl;
			cout << endl;
			cout << "================puzzle insert FAILED=============" << endl;
			cout << "row=" << r << " col=" << c << " value=" << v << endl;
			cout << "================puzzle insert FAILED=============" << endl;
			cout << "last write from     " << glastwrite << endl;
			cout << "last write from fnc=" << fnc << endl << endl;
			printpuzzle();
		}
	 
		//debug = false;
	}
	else{
		if ((puzzle[r][c] == 0) && (puzzle[r][c] != v)){
			if (debug == true){
				cout << endl;
				cout << "================puzzle insert successful=============" << endl;
				cout << "row=" << r << " col=" << c << " value=" << v << endl;
				cout << "================puzzle insert successful=============" << endl;
				cout << "last write from     " << glastwrite << endl;
				cout << "last write from fnc=" << fnc << endl << endl;
			}
			fnc = 0;
			puzzle[r][c] = v;
			if (zcnt > 0){ zcnt--; }
			worder(r, c, v);
			errorcode = 0;
			res = v;
			checkfin();

			lastwrite[1].r = r;
			lastwrite[1].c = c;
			lastwrite[1].v = v;
			lastwrite[1].zcnt = zcnt;
			updp();
		}
	}
	if (debug){
		cout << "zcnt=" << zcnt << " glerr=" << glerr << endl;
		cout << "stackptr=" << stackptr << endl;
	}
	//checkfin();
	return res;
}
//==========================================================

//============================================================
int checkinsert(int r, int c, int v){
	//============================================================
	int  const  noerr = 0;
	errorcode = noerr;
	if (glerr){ errorcode = gerr; return errorcode; }
	if (r > 9)    { errorcode = badr; exit(0); return errorcode; }
	if (r <= 0)   { errorcode = badr; exit(0); return errorcode; }
	if (c > 9)    { errorcode = badc; exit(0); return errorcode; }
	if (c <= 0)   { errorcode = badc; exit(0); return errorcode; }
	if (v > 9)    { errorcode = badv; exit(0); return errorcode; }
	if (v <= 0)   { errorcode = badv; exit(0); return errorcode; }

	//12-02-18//if (puzzle[r][c] == v){ return noerr; }
	int tres = finrow(r, v);
	if (tres){ errorcode = inrow; return errorcode; }
	tres = fincol(c, v);
	if (tres){ errorcode = incol; return errorcode; }
	int tbox = gboxfromrowandcol(r, c);
	tres = finbox(tbox, v);
	if (tres){ errorcode = inbox; return errorcode; }
	//12-02-18//if ((puzzle[r][c]>0) && (puzzle[r][c] != v)){ errorcode = overwrite; return errorcode; }
	if (puzzle[r][c] > 0){ errorcode = overwrite; }
	if ((errorcode == noerr) && (v != 0)){
		if (debug == true){ cout << "insert allowed for (r,c,v)=(" << r << c << v << ")" << endl; }
	}
	if (debug == true){
		if (errorcode>noerr){
			cout << "insert not allowed for (r,c,v)=(" << r << c << v << ")" << endl;
			switch (errorcode){
			case noerr:break;
			case  inrow:  cout << "error = already in row" << endl;           break;
			case  incol:  cout << "error = already in col" << endl;           break;
			case  inbox:  cout << "error = already in box" << endl;           break;
			case  gerr:  cout << "error = glerr already present" << endl;    break;
			case  badr:  cout << "error = bad row value" << endl;            break;
			case  badc:  cout << "error = bad col value" << endl;  cout << "MMMMMMMMMMMM" << endl;         break;
			case  badv:  cout << "error = bad cnum value" << endl;           break;
			case  overwrite:  cout << "error = attempted overwrite" << endl;      break;
				break;
			}
		}
	}
	return errorcode;
}

//=========================================================
//int brow=growfromboxandpos(i,nextcbl);
//int bcol=gcolfromboxandrow(i,brow);

//====================================================
int  checkcnt(int etype, int i){
	//====================================================
	fnc = 61;
	//checkfin();
	int mcnt = gm(etype, i);
	int bcnt = gbls(etype, i);
	int tnum, tbl;
	if (glerr){ return 0; }
	int res = 0;
	if (mcnt != 1){ return 0; }

	switch (etype){
	case zrow:
		if (row[i].done){  return 0; }
		tnum = mrow[1];
		tbl = blrow[1];
		glastwrite = "checkcnt row 8740";
		res = inspuzzle(i, tbl, tnum);
		return res; break;

	case zcol:
		if (col[i].done){  return 0; }
		if (debug){ cout << "mcnt=" << mcnt << endl; }
		tnum = mcol[1];
		tbl = blcol[1];
		glastwrite = "checkcnt col 8747";
		res = inspuzzle(tbl, i, tnum);
		return res; break;

	case zbox:
		if (box[i].done){  return 0; }
		tnum = mbox[1];
	//	tbl = gfb(zbox, i);
		if (bcnt != 1){ cout << "FFFFFFFFFFFF" << endl; exit(0); }
		tbl = blbox[1];
		int trow = growfromboxandpos(i, tbl);
		int tcol = gcolfromboxandpos(i, tbl);
		glastwrite = "checkcnt box 8757";
		res = inspuzzle(trow, tcol, tnum);
		return res; break;
		break;
	}
	return 0;
}
//===================================== 
//end checkcnt  

//===================================
int checkcnts(){
//===================================
	int tres = 0;
	int res = 0;
	thisisaguess = false;
	if (glerr){ return 0; }
	for (int i = 1; i <= 9; i++){
		tres = checkcnt(zrow, i);
		if (glerr){ break; }
		if (tres>0){ res = tres; }
		tres = checkcnt(zcol, i);
		if (glerr){ break; }
		if (tres>0){ res = tres; }
		tres = checkcnt(zbox, i);
		if (glerr){ break; }
		if (tres>0){ res = tres; }

	}
	 
	return res;
}
//===================================
int checkunits(){
	int donecnt = 0;
	for (int i = 1; i <= 3; i++){
		if (rowunit[i].udone){ donecnt++; }
		if (colunit[i].udone){ donecnt++; }
	}
	return donecnt;
}
//==========================================================




//==============================================
//==============================================
int _tmain(){
	fnc = 0;
	if (debug){ cout << endl << "in function main" << endl; }
	if (!ranonce){ getpuzzleandeditmask(); ranonce = true; readinitialpuzzle(); updp(); }
	lzcnt = zcnt;
	updp();
	if (saveonce){
		initp();
		if (glerr){
			cout << "error " << endl;
			exit(0);
		}
	}
	//==================================
	//non guessing loop
	//==================================
	lzcnt = zcnt;
	while (true){
		lzcnt = zcnt;
		thisisaguess = false;

		//checkfin();
		procpuzzle();
		//updp();
		if (glerr){ break; }
		if (zcnt >= lzcnt){ break; }
	}
	//========================
	//end non guessing loop
	//========================
	if (debug){
		cout << "exiting non-guessing loop" << endl;
		cout << "glerr=" << glerr << endl;
	}
	lzcnt = zcnt;
	if (gfirstguess){
		gfirstguess = false;
		saveinitialpuzzle();
		top = 0;
		lzcnt = zcnt;
		procpuzzle();
		checkcnts();
		saveinitialpuzzle();
		savezcnt = zcnt;

		writeinitialpuzzle();
		stackptr = 0;
		if (debug){
			cout << "*************************************saving this puzzle" << endl;
			printpuzzle();
		}
		ptrArow = 0;
		ptrBrow = 0;
		for (int unit = 1; unit <= 3; unit++){
			for (int num = 1; num <= 9; num++){
				collectpairsrow(unit, num);
			}
			for (int num = 1; num <= 9; num++){
				collectpairscol(unit, num);
			}
		}
		stackptr = 0;

		pArow(0);
		pBrow(0);
		initrt();
		//	MergeAB();
		//	dumporder();
		savegwi = gwi;

	}
	if (debug){
		cout << "lzcnt=" << lzcnt << endl;
		cout << "zcnt=" << zcnt << endl;
		cout << "glerr=" << glerr << endl;
	}
	int inserted = 0;
	int tzcnt = zcnt;
	//debug = true;
	while (true){
		//	debug = true;
		//===============================================
		if (glerr){ popp(); }
		//	if (!growinserted){
		//		inserted = insertrow();
		//	if (inserted > 0){
		//		procp();
		//		if (glerr){ popp(); }
		//	}
		//}

		int loopcnt = 0;
		//	if (gtotalinsertedcount != ptrArow){
		while (true){
			loopcnt++;
			inserted = insertA();
			if (inserted > 0){
				procp();
				if (!glerr){ break; }
			}
			if ((loopcnt > ptrArow) && (gtotalinsertedcount > 0)){ break; }
			glerr = false;
		}
		//	}
		glerr = false;
		//	if (glerr){ _tmain(); }
	
		inserted = finishrow(0);
		if (glerr){ _tmain(); }
		if (inserted > 0){
			procp();
			if (glerr){ _tmain(); }
		}
		inserted = finishbox();
		if (glerr){ _tmain(); }

		if (inserted > 0){
			procp();
			if (glerr){ _tmain(); }

		}
		if (glerr){ _tmain(); }
		inserted = finishcol(0);
		if (glerr){ _tmain(); }

		if (inserted > 0){
			procp();
			if (glerr){ _tmain(); }
		}
		//if (glerr){ _tmain(); }
		//if (glerr){ popp(); }
		inserted = 0;
		if (glastrow != 0){ inserted = pickrow(glastrow); }
	//	else{
		//	int lowrow = getlowrow();
		//	inserted = pickrow(lowrow);
	//	}
		glerr = false;
		if (inserted > 0){
			procp();
			if (glerr){ _tmain(); }
		}

	

		int lowcol = getlowcol();
		inserted = pickcol(lowcol);
		glerr = false;
		if (inserted > 0){
			procp();
			if (glerr){ popp(); }
		}
	}
		 
	return 0;
}
//=====================
//end main program
//=====================
int getlowrow(){
	int lowrow = 0;
	int lowmcntrow = 9;
	int mcnt = 9;

	for (int i = 1; i <= 9; i++){
		if (row[i].done == false) {

				mcnt = gm(zrow, i);
				if (mcnt < lowmcntrow){
					lowrow = i;
					lowmcntrow = mcnt;
				}
			}
		}
	//glastrow = lowrow;
	return lowrow;
}
 

//=======================================
int finishrow(int r){
	if (r == 0){ r = getlowrow(); }
	if (glerr){ popp(); return 0; }
	int inserted = 0;
	int mcnt = gm(zrow, r);
	if (mcnt == 1){
		inserted = checkcnt(zrow, r);
		if (glerr){ popp(); }
		return inserted;
	}


	if (mcnt != 2){ return 0; }
	auto time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	uint_fast64_t  seed = time;
	mt19937_64 generator(seed);
	//std::uniform_int_distribution<int> uni(1, 2); // guaranteed unbiased

	//auto which = uni(generator);
	int which = generator() % 2 + 1;
	gbls(zrow, r);
	int m1 = mrow[1];
	int m2 = mrow[2];
	int c1 = blrow[1];
	int c2 = blrow[2];
	if (which == 1){
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishrow1&&&&& M1 IN C1 &&&&&&&&&&&&&&&&&&&&&";
		thisisaguess = true;
		inserted = inspuzzle(r, c1, m1);
		if (inserted > 0){
			insgtable(r, c1, m1,0,0,0);
			glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishrow1&&&&& M2 IN C2 &&&&&&&&&&&&&&&&&&&&&";
			inserted = inspuzzle(r, c2, m2);
			if (inserted > 0){
				return inserted;
			}
			glerr = false;
			puzzle[r][c1] = 0;    //dangerous
			zcnt++;
			delgtable(top);
			order[gwi].guess = false;
		}
		glerr = false;
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishrow1&&&&& M1 IN C2 &&&&&&&&&&&&&&&&&&&&&";
		thisisaguess = true;
		inserted = inspuzzle(r, c2, m1);
		if (inserted > 0){
			insgtable(r, c2, m1, 0, 0, 0);
		}
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishrow1&&&&& M2 IN C1 &&&&&&&&&&&&&&&&&&&&&";
		inserted = inspuzzle(r, c1, m2);
		thisisaguess = false;
		return inserted;
	}
	//=============which=2=================
	glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishrow1&&&&& M1 IN C2 &&&&&&&&&&&&&&&&&&&&&";
	thisisaguess = true;
	inserted = inspuzzle(r, c2, m1);
	if (inserted > 0){
		insgtable(r, c2, m1,0,0,0);
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishrow1&&&&& M2 IN C1 &&&&&&&&&&&&&&&&&&&&&";
		inserted = inspuzzle(r, c1, m2);
		if (inserted > 0){
			return inserted;
		}
		glerr = false;
		puzzle[r][c2] = 0;
		zcnt++;
		delgtable(top);
		order[gwi].guess = false;
	}
	glerr = false;
	glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishrow1&&&&& M1 IN C1 &&&&&&&&&&&&&&&&&&&&&";
	thisisaguess = true;
	inserted = inspuzzle(r, c1, m1);
	if (inserted > 0){
		insgtable(r, c1, m1,0,0,0);
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishrow1&&&&& M2 IN C2 &&&&&&&&&&&&&&&&&&&&&";
		inserted = inspuzzle(r, c2, m2);
	}
	thisisaguess = false;
	return inserted;
}

//==============================================

//===========================================
//=====================
int getlowcol(){
	int lowcol = 0;
	int lowmcntcol = 9;
	int mcnt = 9;

	for (int i = 1; i <= 9; i++){
		if (col[i].done == false) {
				mcnt = gm(zcol, i);
				if (mcnt < lowmcntcol){//only allow change lowcol on less than only
					lowcol = i;
					lowmcntcol = mcnt;
				}
			}
		}
	glastcol = lowcol;
	return lowcol;
}
int finishcol(int c){
	if (c == 0){ c = getlowcol(); }
	if (glerr){ popp(); return 0; }
	int inserted = 0;
	int mcnt = gm(zcol, c);
	if (mcnt == 1){
		inserted = checkcnt(zcol, c);
		if (glerr){ popp(); }
		return inserted;
	}


	if (mcnt != 2){ return 0; }
	auto time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	uint_fast64_t  seed = time;
	mt19937_64 generator(seed);
//	std::uniform_int_distribution<int> uni(1, 2); // guaranteed unbiased

	//auto which = uni(generator);
	int which = generator() % 2 + 1;

	gbls(zcol, c);
	int m1 = mcol[1];
	int m2 = mcol[2];
	int r1 = blcol[1];
	int r2 = blcol[2];
	if (which == 1){
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishcol1&&&&& M1 IN R1 &&&&&&&&&&&&&&&&&&&&&";
		thisisaguess = true;
		inserted = inspuzzle(r1, c, m1);
		if (inserted > 0){
			insgtable(r1, c, m1,0,0,0);
			glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishcol1&&&&& M2 IN R2 &&&&&&&&&&&&&&&&&&&&&";
			inserted = inspuzzle(r2, c, m2);
			if (inserted > 0){
				return inserted;
			}
			glerr = false;
			puzzle[r1][c] = 0;  //dangerous
			zcnt++;
			delgtable(top);
			order[gwi].guess = false;
		}
		glerr = false;
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishcol1&&&&& M1 IN R2 &&&&&&&&&&&&&&&&&&&&&";
		thisisaguess = true;
		inserted = inspuzzle(r2, c, m1);
		if (inserted >0){
			insgtable(r2, c, m1, 0, 0, 0);
		}
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishcol1&&&&& M2 IN R1 &&&&&&&&&&&&&&&&&&&&&";
		inserted = inspuzzle(r1, c, m2);
		thisisaguess = false;
		return inserted;
	}

	//=============which=2=================
	glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishcol1&&&&& M1 IN R2 &&&&&&&&&&&&&&&&&&&&&";
	thisisaguess = true;
	inserted = inspuzzle(r2, c, m1);
	if (inserted > 0){
		insgtable(r2, c, m1,0,0,0);

		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishcol1&&&&& M2 IN R1 &&&&&&&&&&&&&&&&&&&&&";
		inserted = inspuzzle(r1, c, m2);
		if (inserted > 0){
			insgtable(r2, c, m1,0,0,0);
			return inserted;
		}
		glerr = false;
		puzzle[r2][c] = 0;            //dangerous
		zcnt++;
		delgtable(top);
		order[gwi].guess = false;
	}
	glerr = false;
	glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishcol1&&&&& M1 IN R1 &&&&&&&&&&&&&&&&&&&&&";
	thisisaguess = true;
	inserted = inspuzzle(r1, c, m1);
	if (inserted > 0){
		insgtable(r1, c, m1, 0, 0, 0);
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishcol1&&&&& M2 IN R2 &&&&&&&&&&&&&&&&&&&&&";
		inserted = inspuzzle(r2, c, m2);
	}
	thisisaguess = false;
	return inserted;
}
//==============================================
//=====================
int getlowbox(){
	int lowbox = 0;
	int lowmcntbox = 9;
	int mcnt = 9;
	for (int i = 1; i <= 9; i++){
		if (box[i].done == false) {
			mcnt = gm(zbox, i);
			if (mcnt < lowmcntbox){
				lowbox = i;
				lowmcntbox = mcnt;
			}
		}
	}
	return lowbox;
}
//=======================================
int finishbox(){
	int b = getlowbox();
	int res = 0;
	int mcnt = gm(zbox, b);
	if (mcnt == 1){
		res = checkcnt(zbox, b);
		if (glerr){
			popp();
		}
		return res;
	}
	if (mcnt != 2){ return 0; }
	auto time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	uint_fast64_t  seed = time;
	mt19937_64 generator(seed);
	//std::uniform_int_distribution<int> uni(1, 2); // guaranteed unbiased
	//auto which = uni(generator);
	int which = generator() % 2 + 1;

	gbls(zbox, b);
	int m1 = mbox[1];
	int m2 = mbox[2];

	int b1 = blbox[1];
	int b2 = blbox[2];
	int trow1 = growfromboxandpos(b, b1);
	int tcol1 = gcolfromboxandpos(b, b1);
	int trow2 = growfromboxandpos(b, b2);
	int tcol2 = gcolfromboxandpos(b, b2);
	if (which == 1){
		thisisaguess = true;
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishbox1&&&&&&&&&&&&&&&&&&&&&&&&&&";
		res = inspuzzle(trow1, tcol1, m1);
		if (!glerr){
			insgtable(trow1, tcol1, m1,0,0,0);
			glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishbox2&&&&&&&&&&&&&&&&&&&&&&&&&&";
			res = inspuzzle(trow2, tcol2, m2);
			if (res > 0){ 
				return res;
			}
			glerr = false;
			puzzle[trow1][tcol1] = 0;  //dangerous
			zcnt++;
			delgtable(top);
			order[gwi].guess = false;
		}
		glerr = false;
		thisisaguess = true;
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishbox3&&&&&&&&&&&&&&&&&&&&&&&&&&";
		res = inspuzzle(trow2, tcol2, m1);
		if (!glerr){
			insgtable(trow2, tcol2, m1, 0, 0, 0);
			glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishbox4&&&&&&&&&&&&&&&&&&&&&&&&&&";
			res = inspuzzle(trow1, tcol1, m2);
		}
		thisisaguess = false;
		return res;
	}
	if (which == 2){
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishbox1&&&&&&&&&&&&&&&&&&&&&&&&&&";
		thisisaguess = true;
		res = inspuzzle(trow2, tcol2, m1);
		if (!glerr){
			insgtable(trow2, tcol2, m1,0,0,0);
			glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishbox2&&&&&&&&&&&&&&&&&&&&&&&&&&";
			res = inspuzzle(trow1, tcol1, m2);
			if (res > 0){ 
				return res;
			}
			glerr = false;
			puzzle[trow2][tcol2] = 0;       //d
			zcnt++;
			delgtable(top);
			order[gwi].guess = false;
		}
		glerr = false;
		thisisaguess = true;
		glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishbox3&&&&&&&&&&&&&&&&&&&&&&&&&&";
		res = inspuzzle(trow1, tcol1, m1);
		if (!glerr){
			insgtable(trow1, tcol1, m1, 0, 0, 0);

			glastwrite = "&&&&&&&&&&&&&&&&&&&&&finishbox4&&&&&&&&&&&&&&&&&&&&&&&&&&";
			res = inspuzzle(trow2, tcol2, m2);
		}
	}
	thisisaguess =false;
	return res;
}
//===========================================
//=============================================
int pickrow(int r){
	auto time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	uint_fast64_t  seed = time;
	mt19937_64 generator(seed);
	int mcnt = 0;
	int bcnt = 0;
	int rand1 = 0;
	int rand2 = 0;
	int res = 0;
	int trycount = 0;
	res = 0;
	if (r == 0){
		r = getlowrow();
		if (row[r].done){
			return 0;
		}
	}
	while (true){
		glerr = false;
		if (row[r].done){
			return 0;
		}
		mcnt = gm(zrow, r);
		if (mcnt < 3){ ginsertedrow = 0; res = finishrow(r); return res; }
		bcnt = gbls(zrow, r);
		if (mcnt != bcnt){ cout << "FATAL ERROR MCNT != BCNT" << endl; popp(); }
		trycount++;
		rand1 = generator() % mcnt + 1;
		rand2 = generator() % bcnt + 1;

		int c = blrow[rand1];
		int v = mrow[rand2];
		int tbox = gboxfromrowandcol(r, c);

		if (debug){
			if (r == 0){ cout << "GLERR r=0" << endl; exit(0); }
			if (c == 0){ cout << "GLERR c=0" << endl; exit(0); }
			if (v == 0){ cout << "GLERR v=0" << endl; exit(0); }
			if (tbox == 0){ cout << "GLERR tbox=0" << endl; exit(0); }
		}

		if (puzzle[r][c] == 0){
			int inrow = finrow(r, v);
			int incol = fincol(c, v);
			int inbox = finbox(tbox, v);
			if ((!incol) && (!incol) && (!inbox)){
				glastwrite = "--------------------------------pickrow-------";
				thisisaguess = true;
				res = inspuzzle(r, c, v);
				if (debug){ if (glerr){ cout << "GLERR" << endl; } }
				if (res > 0){
					insgtable(r, c, v,0,0,0);
					return res;
				}
				glerr = false;
			}
		}
		glerr = false;
		if (trycount > mcnt){
			popp();
			thisisaguess = false;
			return 0;
		}
	}

	return res;
}
//=============================================
//=============================================
int pickcol(int c){
	auto time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	uint_fast64_t  seed = time;
	mt19937_64 generator(seed);

	int mcnt = 0;
	int bcnt = 0;
	int rand1 = 0;
	int rand2 = 0;
	int res = 0;
	int trycount = 0;
	res = 0;
	if (c == 0){
		c = getlowcol();
		if (col[c].done){ return 0; }
	}
	while (true){
		glerr = false;
		mcnt = gm(zcol, c);
		if (mcnt < 3){ ginsertedcol = 0; res = finishcol(c); return res; }
		bcnt = gbls(zcol, c);
		trycount++;
		rand1 = generator() % mcnt + 1;
		rand2 = generator() % bcnt + 1;

		int r = blcol[rand1];
		int v = mcol[rand2];
		int tbox = gboxfromrowandcol(r, c);

		if (debug){
			if (r == 0){ cout << "GLERR r=0" << endl; exit(0); }
			if (c == 0){ cout << "GLERR c=0" << endl; exit(0); }
			if (v == 0){ cout << "GLERR v=0" << endl; exit(0); }
			if (tbox == 0){ cout << "GLERR tbox=0" << endl; exit(0); }
		}

		if (puzzle[r][c] == 0){
			int incol = fincol(c, v);
			int inrow = finrow(r, v);
			int inbox = finbox(tbox, v);
			if ((!inrow) && (!incol) && (!inbox)){
				glastwrite = "--------------------------------pickcol-------";
				thisisaguess = true;

				res = inspuzzle(r, c, v);
				if (res > 0){
					insgtable(r, c, v,0,0,0);
					return res;
				}
				glerr = false;
			}
		}
		glerr = false;
		if (trycount > mcnt){
			thisisaguess = false;
			popp();
			return 0;
		}
	}

	return res;
}
//=============================================

 //=============================================
 
//=============================================


//=====================
void swapAlist(){

	int sr, sc, sv;
	int listptr = ptrArow;
	for (int i = 1; i <= ptrArow / 2; i++){
		sr = Arow[i].r;
		sc = Arow[i].c;
		sv = Arow[i].v;
		Arow[i].r = Arow[listptr].r;
		Arow[i].c = Arow[listptr].c;
		Arow[i].v = Arow[listptr].v;
		Arow[listptr].r = sr;
		Arow[listptr].c = sc;
		Arow[listptr].v = sv;
		listptr--;
	//	if (debug){ pArow(0); }
	}
	return;
}
//================================= 
void swapBlist(){

	int sr, sc, sv;
	int listptr = ptrBrow;
	for (int i = 1; i <= ptrBrow / 2; i++){
		sr = Brow[i].r;
		sc = Brow[i].c;
		sv = Brow[i].v;
		Brow[i].r = Brow[listptr].r;
		Brow[i].c = Brow[listptr].c;
		Brow[i].v = Brow[listptr].v;
		Brow[listptr].r = sr;
		Brow[listptr].c = sc;
		Brow[listptr].v = sv;
		listptr--;
	//	if (debug){ pBrow(0); }
	}
	return;
}
//=====================================
int MergeAB(){
	thisisaguess = true;
	int inserted = 0;
	int A = 1;
	int res = 0;

	if (ptrArow == 0){ return 0; }
	//first try to gen error with inserts only
	int currindex = 0;
	int errorindex = 0;
	int r, c, v;
	if (debug){ cout << "inserting A side till error" << endl; }
	//popp();
	if (glerr){ popp(); }
	 
		 
	for (int i = 1; i <= ptrBrow; i++){
		r = Brow[i].r;
		c = Brow[i].c;
		v = Brow[i].v;
		insArow(r, c, v);
		
	}
	//pArow(0);
	//exit(0);
	return res;
}
//=====================================

 
//===========================================

int insertA(){
	if (glerr){ cout << "INSERTA" << endl; printpuzzle(); exit(0); }
	int res = 0;
	if (ptrArow == 0){ return 0; }
	int const A = 1;
	int const B = 2;
	auto time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	uint_fast64_t  seed = time;
	std::mt19937_64 generator(seed);    // random-number engine used (Mersenne-Twister in this case)

	//std::uniform_int_distribution<int> uni(1, ptrArow); // guaranteed unbiased

//	auto random_integer = uni(generator);
	int tptr = 0;
	int trycount = 0;
	int which = 0;
	int last = 0;
	res = 0;
	//tptr = generator() % ptrArow + 1;
	//int gptr = random_integer;
	gptr++;
	if (gptr > ptrArow){ gptr = 1; }
	int r1 = Arow[gptr].r;
	int c1 = Arow[gptr].c;
	int v1 = Arow[gptr].v;
	int r2 = Brow[gptr].r;
	int c2 = Brow[gptr].c;
	int v2 = Brow[gptr].v;
	if (row[r1].done){ return 0; }
	if (row[r2].done){ return 0; }
	if (col[c1].done){ return 0; }
	if (col[c2].done){ return 0; }
	if (puzzle[r1][c1] == v1){
		return 0;
	}
	if (puzzle[r2][c2] == v2){
		return 0;
	}
	if ((puzzle[r1][c1] > 0) && (puzzle[r2][c2] > 0)){
		popp();
	}
	//std::uniform_int_distribution<int> uni2(1, 2); // guaranteed unbiased

	//auto random_integer = uni2(generator);
	//which = random_integer;
	which = generator() % 2 + 1;
	if (which == B){
		if (puzzle[r2][c2] !=0){
			return 0;
		}
		glastwrite = "----------------------------------insertBR2";
		thisisaguess = true;

		res = inspuzzle(r2, c2, v2);
		if (!glerr){
			ginsertedBcount++;
			gtotalinsertedcount++;
			tptr = gptr;
			insgtable(r2, c2, v2,B,tptr,B);
			glastrow = r2;
		}
		thisisaguess = false;
		return res;
	}
	if (which == A){
		if (puzzle[r1][c1] != 0){
			return 0;
		}
		glastwrite = "----------------------------------insertAR1";
		thisisaguess = true;

		res = inspuzzle(r1, c1, v1);
		if (!glerr){
			ginsertedAcount++;
			gtotalinsertedcount++;
			tptr = gptr;
			insgtable(r1, c1, v1,A,tptr,A);
			glastrow = r1;
		}
		thisisaguess = false;
		return res;
	}
	return res;
}
 
//===============================
void initrt(){
	for (int i = 1; i <= 9; i++){
		rt[i].numtries = 0;
		for (int j = 1; j <= 9; j++){
			for (int k = 1; k <= 9; k++){
				rt[i].r[i][j] = 0;
			}
		}
	}
	return;
}
//==============================
//=================================
bool rowmatch(int r){
return false;
	int mcnt;
	int matchcnt = 0;
	if (r == 0){ cout << "RRRRRRRRRRRR" << endl; printpuzzle(); exit(0); }
	bool newrowisduplicate = false;
	if (row[r].done){mcnt = 0; }
	else{
	 mcnt = gm(zrow, r);
	}  //to do partial match for incomplete rows
	for (int i = 1; i < rt[r].numtries; i++){
		for (int j = 1; j <= 9-mcnt; j++){
			if (rt[r].r[i][j] == puzzle[r][j]){matchcnt++; }
		}
		if (matchcnt == 9-mcnt){
			newrowisduplicate = true;
			if (debug){
				cout << "DUPLICATE ROW = " << r << endl;
				if (mcnt < 9){
					cout << "PARTIAL MATCH MCNT = " << 9-mcnt << endl;
				}
				printpuzzle();
			}
		}
		if (debug){
			cout << "NOT A  DUPLICATE ROW = " << r << endl;
			if (mcnt < 9){
				cout << "PARTIAL MATCH MCNT = " << matchcnt << endl;
			}
			//	printpuzzle();
		}
		matchcnt = 0;
	}
	if (!newrowisduplicate){
		
		int triedcnt = rt[r].numtries++;
		for (int j = 1; j <= 9-mcnt; j++){
			rt[r].r[triedcnt][j] = puzzle[r][j];
		}
	}
	return newrowisduplicate;
}
//===============================
int insertrow(){
	thisisaguess = true;
	if (growinserted){ return 0; }

	int fillerrorcounter = 0;
	auto time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	uint_fast64_t  seed = time;
	mt19937_64 generator(seed);
	
    
	int r = getlowrow();

	int  c, v, inserted, blcnt, mcnt;
	 
	
	mcnt = gm(zrow, r);
	if (row[r].done){ r = getlowrow(); }

	//if (mcnt < 3){
	//	int res=finishrow(r);
	//	if (res > 0){ growinserted = true; return 1; }
	//	return 0;
	//}
	while (true){
		if (glerr){ popp(); }
		mcnt = gm(zrow, r);
		if (mcnt == 0){ growinserted = true; return 1; }
		blcnt = gbls(zrow, r);
		int randindex2 = generator() % blcnt + 1;
		int randindex = generator() % mcnt + 1;
		v = mrow[randindex];
		if (v == 0){ cout << "PPPPPPPPPPPP" << endl; exit(0); }
		c = blrow[randindex2];
		if (c == 0){ cout << "LLLLLLLLLLL" << endl; exit(0); }
		if (puzzle[r][c] == 0){
			glastwrite = "insertrow@@@@@@@@@@@@@";
			inserted = inspuzzle(r, c, v);
			if (glerr){ popp(); }
		}
		if (row[r].done){
			if (debug){
				printpuzzle();
				cout << "row filled! row= " << r << endl;
				growinserted = true;
			}
			break;
		}
	}
	return inserted;
}
//==================================================================
//===============================================
int collectpairsrow(int runit, int num){
	int c1, c2, c3;
	int places = 3;
	int inserted = 0;
	if (rowunit[runit].nc[num] != 2){
		return 15;
	}
	if (rowunit[runit].targrow[num] == 0){
		return 15;
	}
	if (rowunit[runit].targbox[num] == 0){
		return 15;
	}
	if ((rowunit[runit].nc[num] == 2) && (rowunit[runit].targrow[num] != 0) && (rowunit[runit].targbox[num] != 0)){
		gcolsfromtargboxandtargrow(rowunit[runit].targbox[num], rowunit[runit].targrow[num], c1, c2, c3);
		int r = rowunit[runit].targrow[num];
		bool c1occupied = false;
		bool c2occupied = false;
		bool c3occupied = false;
		int numinc1, numinc2, numinc3;
		numinc1 = fincol(c1, num);
		if (numinc1){ c1occupied = true; --places; }
		else{
			if (puzzle[r][c1] > 0){ --places; c1occupied = true; }
		}
		numinc2 = fincol(c2, num);
		if (numinc2){ c2occupied = true; --places; }
		else{
			if (puzzle[r][c2] > 0){ --places; c2occupied = true; }
		}
		numinc3 = fincol(c3, num);
		if (numinc3){ c3occupied = true; --places; }
		else{
			if (puzzle[r][c3] > 0){ --places; c3occupied = true; }
		}
		if (places == 2){
			int chA = 0;
			int chB = 0;
			//==================================
			if ((!c1occupied) && (!c2occupied)){
				//==============================
				chA = c1;
				chB = c2;
			}
			//=================================
			if ((!c2occupied) && (!c3occupied)){
				//=============================
				chA = c2;
				chB = c3;
			}
			//=================================
			if ((!c1occupied) && (!c3occupied)){
				//=============================
				chA = c1;
				chB = c3;
			}
			//==================================
			if ((chA > 0) && (chB > 0)){
				insArow(r, chA, num);
				insBrow(r, chB, num);
			}
			//==================================
		}
	}
	return 0;
}
//=========================================================
int collectpairscol(int cunit, int n){
	//===================================================== 
	int r1, r2, r3, ninr1, ninr2, ninr3;
	if (colunit[cunit].nc[n] != 2){
		return 15;
	}
	if (colunit[cunit].targcol[n] == 0){
		return 15;
	}
	if (colunit[cunit].targbox[n] == 0){

		return 15;
	}
	if ((colunit[cunit].nc[n] == 2) && (colunit[cunit].targcol[n] != 0) && (colunit[cunit].targbox[n] != 0)){
		growsfromtargboxandtargcol(colunit[cunit].targbox[n], colunit[cunit].targcol[n], r1, r2, r3);
		int c = colunit[cunit].targcol[n];
		bool r1occupied = false;
		bool r2occupied = false;
		bool r3occupied = false;
		int places = 3;
		int chA = 0;
		int chB = 0;
		ninr1 = finrow(r1, n);
		if (ninr1){ r1occupied = true; --places; }
		else{ if (puzzle[r1][c] > 0){ --places; r1occupied = true; } }
		ninr2 = finrow(r2, n);
		if (ninr2){ r2occupied = true; --places; }
		else{ if (puzzle[r2][c] > 0){ --places; r2occupied = true; } }
		ninr3 = finrow(r3, n);
		if (ninr3){ r3occupied = true; --places; }
		else{ if (puzzle[r3][c] > 0){ --places; r3occupied = true; } }
		if (places == 2){
			//==================================
			if ((!r1occupied) && (!r2occupied)){
				//==============================
				chA = r1;
				chB = r2;
			}
			//=================================
			if ((!r2occupied) && (!r3occupied)){
				//=============================
				chA = r2;
				chB = r3;
			}
			//=================================
			if ((!r1occupied) && (!r3occupied)){
				//=============================
				chA = r1;
				chB = r3;
			}
			//==================================
			if ((chA > 0) && (chB > 0)){
				insArow(chA, c, n);             //put all in rows simplify
				insBrow(chB, c, n);
			}
			//==================================
		}
	}
	return 0;
}
//=====================================================================
int  insArow(int r, int c, int v){
	++ptrArow;
	r = Arow[ptrArow].r = r;
	c = Arow[ptrArow].c = c;
	v = Arow[ptrArow].v = v;
	return 0;
}
//=====================================================================
int  insBrow(int r, int c, int v){
	++ptrBrow;
	r = Brow[ptrBrow].r = r;
	c = Brow[ptrBrow].c = c;
	v = Brow[ptrBrow].v = v;
	return 0;
}
//====================================================================
void  pArow(int listptr){
	if (!debug){ return; }
	if (listptr == 0){
		for (int i = 1; i <=ptrArow; ++i){
			cout << "Arow[" << i << "].r = " << Arow[i].r << endl;
			cout << "Arow[" << i << "].c = " << Arow[i].c << endl;
			cout << "Arow[" << i << "].v = " << Arow[i].v << endl;
			cout << "==============================================" << endl;
		}
	}
	else{
		cout << "==============================================" << endl;
		cout << "Arow[" << listptr << "].r = " << Arow[listptr].r << endl;
		cout << "Arow[" << listptr << "].c = " << Arow[listptr].c << endl;
		cout << "Arow[" << listptr << "].v = " << Arow[listptr].v << endl;
		cout << "==============================================" << endl;
	}
	return;
}
//====================================================================
void  pAcol(int ptrA){
	if (!debug){ return; }
	if (ptrA == 0){
		for (int i = 1; i <= ptrAcol; i++){
			cout << "Acol[" << i << "].r = " << Acol[i].r << endl;
			cout << "Acol[" << i << "].c = " << Acol[i].c << endl;
			cout << "Acol[" << i << "].v = " << Acol[i].v << endl;
			cout << "==============================================" << endl;
		}
	}
	else{
		cout << "==============================================" << endl;
		cout << "Acol[" << ptrA << "].r = " << Acol[ptrA].r << endl;
		cout << "Acol[" << ptrA << "].c = " << Acol[ptrA].c << endl;
		cout << "Acol[" << ptrA << "].v = " << Acol[ptrA].v << endl;
		cout << "==============================================" << endl;
	}
	return;
}
//====================================================================
void  pBrow(int listptr){
	if (!debug){ return; }
	if (listptr == 0){
		for (int i = 1; i <= ptrBrow; i++){
			cout << "Brow[" << i << "].r = " << Brow[i].r << endl;
			cout << "Brow[" << i << "].c = " << Brow[i].c << endl;
			cout << "Brow[" << i << "].v = " << Brow[i].v << endl;
			cout << "==============================================" << endl;
		}
	}
	else{
		cout << "==============================================" << endl;
		cout << "Brow[" << listptr << "].r = " << Brow[listptr].r << endl;
		cout << "Brow[" << listptr << "].c = " << Brow[listptr].c << endl;
		cout << "Brow[" << listptr << "].v = " << Brow[listptr].v << endl;
		cout << "==============================================" << endl;
	}

	return;
}
//==================================================================
//====================================================================
void  pBcol(int ptrB){
	if (!debug){ return; }
	if (ptrB == 0){
		for (int i = 1; i <= ptrBcol; i++){
			cout << "Bcol[" << i << "].r = " << Bcol[i].r << endl;
			cout << "Bcol[" << i << "].c = " << Bcol[i].c << endl;
			cout << "Bcol[" << i << "].v = " << Bcol[i].v << endl;
			cout << "==============================================" << endl;
		}
	}
	else{
		cout << "==============================================" << endl;
		cout << "Bcol[" << ptrB << "].r = " << Bcol[ptrB].r << endl;
		cout << "Bcol[" << ptrB << "].c = " << Bcol[ptrB].c << endl;
		cout << "Bcol[" << ptrB << "].v = " << Bcol[ptrB].v << endl;
		cout << "==============================================" << endl;
	}
	return;
}

//============================================================
int  insAcol(int r, int c, int v){
	++ptrAcol;
	r = Acol[ptrAcol].r = r;
	c = Acol[ptrAcol].c = c;
	v = Acol[ptrAcol].v = v;
	return 0;
}
//============================================================
//============================================================
int  insBcol(int r, int c, int v){
	++ptrBcol;
	r = Bcol[ptrBcol].r = r;
	c = Bcol[ptrBcol].c = c;
	v = Bcol[ptrBcol].v = v;
	return 0;
}



 
//===============================================================
int pickrand2(){
	if (zcnt < 20){
		if (debug){ cout << "LOW ZCNT RAND2" << endl; }
		popp();
	//	return 0;
	}
	auto time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	uint_fast64_t  seed = time;
	mt19937_64 generator(seed);
	//mt19937_64 generator(gseed);  // mt19937_64 is a standard 64 bit mersenne_twister_engine

	int mcntrow = 9;
	int mcntcol = 9;
	int mcntbox = 9;
	int inserted = 0;
	int index = 1;
	for (int i = 1; i <= 9; i++){
		mcntrow = gm(zrow, i);
		if (mcntrow==2){
			index = i;
			break;
		}
		mcntcol = gm(zcol, i);
		if (mcntcol ==2){
			index = i;
			break;
		}
		mcntbox = gm(zbox, i);
		if (mcntbox ==2){
			index = i;
			break;
		}
	}
	//========================================================================================================
	if (mcntrow==2){
		gbls(zrow, index);
		int randm = generator() % 2 + 1;
		int randbl = generator() % 2 + 1;
		int bl = blrow[randbl];
		int value = mrow[randm];
		int inrow = finrow(index, value);
		int incol = fincol(bl, value);
		int tbox = gboxfromrowandcol(index, bl);
		int inbox = finbox(tbox, value);       //or box
		if ((!incol) && (!inrow)&&(!inbox)){
			glastwrite = "***********************pickrand2 row*******A********************";
			inserted = inspuzzle(index, bl, value);
			if (inserted > 0){ glastrow = index; return inserted; }
			if (debug){ if (glerr){ cout << "GLERR 2" << endl; } }
			glerr = false;
		}
		if (bl == blrow[1]){bl = blrow[2];}
		else{bl = blrow[1];}
		inrow = finrow(index, value);
		incol = fincol(bl, value);
		 tbox = gboxfromrowandcol(index, bl);
	     inbox = finbox(tbox, value);       //or box
		if ((!incol) && (!inrow) && (!inbox)){
			glastwrite = "***********************pickrand2 row*********B******************";
			inserted = inspuzzle(index, bl, value);
			if (inserted > 0){ glastrow = index; return inserted; }
			if (debug){ if (glerr){ cout << "GLERR 3" << endl; } }
			glerr = false;
			
		}
		if (value == mrow[1]){ value = mrow[2]; }
		else{value = mrow[1];}
		inrow = finrow(index, value);
		incol = fincol(bl, value);
		 tbox = gboxfromrowandcol(index, bl);
		 inbox = finbox(tbox, value);       //or box
		if ((!incol) && (!inrow) && (!inbox)){
			glastwrite = "***********************pickrand2 row*******C********************";
			inserted = inspuzzle(index, bl, value);
			if (inserted > 0){ glastrow = index; return inserted; }
			if (debug){ if (glerr){ cout << "GLERR 4" << endl; } }
			glerr = false;
		}
		if (bl == blrow[1]){bl = blrow[2];}
		else{bl = blrow[1];}
		inrow = finrow(index, value);
		incol = fincol(bl, value);
		 tbox = gboxfromrowandcol(index, bl);
	  inbox = finbox(tbox, value);       //or box
		if ((!incol) && (!inrow) && (!inbox)){
			glastwrite = "***********************pickrand2 row*********D******************";
			inserted = inspuzzle(index, bl, value);
			if (inserted > 0){ glastrow = index; return inserted; }
			if (debug){ if (glerr){ cout << "GLERR 5" << endl; } }
			if (glerr){ popp(); }
		}
		if (glerr){ popp(); }
		return inserted;
	}
	//=======================================================================================================
	if (mcntcol==2){
		gbls(zcol, index);
		int randm = generator() % 2 + 1;
		int randbl = generator() % 2 + 1;
		int bl = blcol[randbl];
		int value = mcol[randm];
		int inrow = finrow(index, value);
		int tbox = gboxfromrowandcol(bl, index);
		int inbox = finbox(tbox, value);       //or box
		if ((!incol) && (!inrow) && (!inbox)){
			glastwrite = "***********************pickrand2 col**********A*****************";
			inserted = inspuzzle(bl, index, value);
			if (inserted > 0){ glastrow = bl; return inserted; }
			if (debug){ if (glerr){ cout << "GLERR 6" << endl; } }
			//if (glerr){ popp(); }
			glerr = false;
		}
		if (bl == blcol[1]){
			bl = blcol[2];
		}
		else{
			bl = blcol[1];
		}
		tbox = gboxfromrowandcol(bl, index);
		inbox = finbox(tbox, value);       //or box
		inrow = finrow(index, value);
		if ((!incol) && (!inrow) && (!inbox)){

			glastwrite = "***********************pickrand2 col**********B****************";
			inserted = inspuzzle(bl, index, value);
			if (inserted > 0){ glastrow = bl; return inserted; }
			if (debug){ if (glerr){ cout << "GLERR 7" << endl; } }
		//	if (glerr){ popp(); }
			glerr = false;
		}
		if (value == mcol[1]){
			value = mcol[2];
		}
		else{
			value = mcol[1];
		}
		inrow = finrow(index, value);
		tbox = gboxfromrowandcol(bl, index);
		inbox = finbox(tbox, value);       //or box
		if ((!incol) && (!inrow) && (!inbox)){
			glastwrite = "***********************pickrand2 col**********C*****************";
			inserted = inspuzzle(bl, index, value);
			if (inserted > 0){ glastrow = bl; return inserted; }
			if (debug){ if (glerr){ cout << "GLERR 8" << endl; } }
		//	if (glerr){ popp(); }
			glerr = false;
		}
		if (bl == blcol[1]){
			bl = blcol[2];
		}
		else{
			bl = blcol[1];
		}
		tbox = gboxfromrowandcol(bl, index);
		inbox = finbox(tbox, value);       //or box
		inrow = finrow(index, value);
		if ((!incol) && (!inrow) && (!inbox)){
			glastwrite = "***********************pickrand2 col**********D****************";
			inserted = inspuzzle(bl, index, value);
			if (inserted > 0){ glastrow = bl; return inserted; }
			if (debug){ if (glerr){ cout << "GLERR 9" << endl; } }
			if (glerr){ popp(); }
		}
		if (glerr){ popp(); }
		return 0;
	}
	//=======================================================================================================
	if (mcntbox ==2){
		gbls(zbox, index);
		int randm = generator() % 2 + 1;
		int randbl = generator() % 2 + 1;
		int bl = blbox[randbl];
		int value = mbox[randm];
		int trow = growfromboxandpos(index, bl);
		int tcol = gcolfromboxandpos(index, bl);
		int inbox = finbox(index, value);
		if (!inbox){
			glastwrite = "***********************pickrand2 box************A***************";
			inserted = inspuzzle(trow, tcol, value);
			if (inserted > 0){ glastrow = trow; return inserted; }
			if (debug){ if (glerr){ cout << "GLERR 10" << endl; } }
		//	if (glerr){ popp(); }
			glerr = false;
		}
		if (bl == blbox[1]){
			bl = blbox[2];
		}
		else{
			bl = blbox[1];
		}
		trow = growfromboxandpos(index, bl);
		tcol = gcolfromboxandpos(index, bl);
		inbox = finbox(index, value);
		if (!inbox){
			glastwrite = "***********************pickrand2 box***********B**************";
			inserted = inspuzzle(trow, tcol, value);
			if (inserted > 0){ glastrow = trow; return inserted; }
			if (debug){ if (glerr){ cout << "GLERR 11" << endl; } }
		//	if (glerr){ popp(); }
			glerr = false;
		}
		if (value == mbox[1]){
			value = mbox[2];
		}
		else{
			value = mbox[1];
		}
		 trow = growfromboxandpos(index, bl);
		 tcol = gcolfromboxandpos(index, bl);
		 inbox = finbox(index, value);
		if (!inbox){
			glastwrite = "***********************pickrand2 box************C***************";
			inserted = inspuzzle(trow, tcol, value);
			if (inserted > 0){ glastrow = trow; return inserted; }
			if (debug){ if (glerr){ cout << "GLERR 12" << endl; } }
			//if (glerr){ popp(); }
			glerr = false;
		}
		if (bl == blbox[1]){
			bl = blbox[2];
		}
		else{
			bl = blbox[1];
		}
		trow = growfromboxandpos(index, bl);
		tcol = gcolfromboxandpos(index, bl);
		inbox = finbox(index, value);
		if (!inbox){
			glastwrite = "***********************pickrand2 box***********D**************";
			inserted = inspuzzle(trow, tcol, value);
			if (inserted > 0){ glastrow = trow; return inserted; }
			if (debug){ if (glerr){ cout << "GLERR 13" << endl; } }
			if (glerr){ popp(); }
		}
		if (glerr){ popp(); }
		//popp();
		return 0;
	}
	//=======================================================================================================
	return 0;
}

//=========================================================================================
int pickrandunbounded(){
	if (zcnt < 20){
		if (debug){ cout << "LOW ZCNT UNBOUNDED" << endl; }
		popp();
		return 0;
	}
	auto time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	uint_fast64_t  seed = time;
	mt19937_64 generator(seed);
	//mt19937_64 generator(gseed);  // mt19937_64 is a standard 64 bit mersenne_twister_engine
	int mcntrow = 0;
	int mcntcol = 0;
	int mcntbox = 0;
	int inserted = 0;
	int rowindex = 0;
	int colindex = 0;
	int boxindex = 0;
	int lowestmcntrow = 9;
	int lowestmcntcol = 9;
	int lowestmcntbox = 9;
	int lowindex = 9;
	for (int i = 1; i <= 9; i++){
		mcntcol = gm(zcol, i);
		if ((mcntcol < lowestmcntcol) && (mcntcol>0)){
			if (debug){ cout << "mcntcol=" << mcntcol << endl; }
			lowestmcntcol = mcntcol;
			colindex = i;
		}
	}
	for (int i = 1; i <= 9; i++){
		mcntbox = gm(zbox, i);
		gbls(zbox, i);
		if ((mcntbox < lowestmcntbox) && (mcntbox>0)){
			if (debug){ cout << "mcntbox=" << mcntbox << endl; }
			lowestmcntbox = mcntbox;
			boxindex = i;
		}
	}
	for (int i = 1; i <= 9; i++){
		mcntrow = gm(zrow, i);
		if ((mcntrow < lowestmcntrow) && (mcntrow>0)){
			if (debug){ cout << "mcntrow=" << mcntrow << endl; }
			lowestmcntrow = mcntrow;
			rowindex = i;
		}
	}
	int lowestmcnt = 9;
	int which = 0;
	if (lowestmcntrow < lowestmcnt){ lowestmcnt = lowestmcntrow; which = zrow; lowindex = rowindex; }
	if (lowestmcntcol < lowestmcnt){ lowestmcnt = lowestmcntcol; which = zcol; lowindex = colindex; }
	if (lowestmcntbox < lowestmcnt){ lowestmcnt = lowestmcntbox; which = zbox; lowindex = boxindex; }
	gbls(which, lowindex);
	int randm = generator() % lowestmcnt + 1;
	int randbl = generator() % lowestmcnt + 1;
	if (which == zcol){
		if (debug){ cout << "WHICH=COL" << endl; }
		int bl = blcol[randbl];
		int value = mcol[randm];
		int inrow = finrow(bl, value);
		int incol = fincol(lowindex, value);
		int tbox = gboxfromrowandcol(bl, lowindex);
		int inbox = finbox(tbox, value); 
		if (debug){ cout << "RCV=" << bl << lowindex << value << endl; }
		if ((!inrow)&&(!inbox)&&(!incol)){
			glastwrite = "***********************pickrandunbounded col***************************";
			inserted = inspuzzle(bl, lowindex, value);
			if (debug){ if (glerr){ cout << "GLERR 14" << endl; } }
			glerr = false;
			return inserted;
		}
		return 0;
	}
	if (which == zbox){
		if (debug){ cout << "WHICH=BOX" << endl; }

		int bl = blbox[randbl];
		int value = mbox[randm];
		int trow = growfromboxandpos(lowindex, bl); 
		int tcol = gcolfromboxandpos(lowindex, bl);
		int inbox = finbox(lowindex, value);
		int inrow = finrow(trow, value);
		int incol = fincol(tcol, value);
		if (debug){ cout << "RCV=" << trow << tcol << value << endl; }

		if ((!inbox)&&(!inrow)&&(!incol)){
			glastwrite = "***********************pickrandunbounded box***************************";
			inserted = inspuzzle(trow, tcol, value);
			if (debug){ if (glerr){ cout << "GLERR 15" << endl; } }
		//	if (glerr){ popp(); }
			glerr = false;
			return inserted;
		}
		return 0;
	}
	if (which == zrow){
		if (debug){ cout << "WHICH=ROW" << endl; }

		int bl = blrow[randbl];
		int value = mrow[randm];
		int inrow = finrow(lowindex, value);
		int tcol = fincol(bl, value);
		if (debug){ cout << "RCV=" << lowindex << bl << value << endl; }

		if ((!incol) && (!inrow)){
			glastwrite = "***********************pickrandunbounded row***************************";
			inserted = inspuzzle(lowindex, bl, value);
			if (debug){ if (glerr){ cout << "GLERR 16" << endl; } }
		//	if (glerr){ popp(); }
			glerr = false;
			return inserted;
		}
		return 0;
	}
	return 0;
}
//===============================================================================================

int predictpath(){
	//Extrapolate forward because the deterministic algorithms couldn't figure out
	//the next number. Only choose best candidate very carefully and go back to not guessing.
	//===========================================================================================
	auto time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();
	uint_fast64_t  seed = time;
	mt19937_64 generator(seed);

	//int seed = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count();

	//mt19937_64 generator(seed);  // mt19937_64 is a standard 64 bit mersenne_twister_engine
//	checkfin();
	int mcnt = 0;
	int res = 0;
	// (glerr){ popp(); }
	if (glerr){ popp(); }
	//if (ginsertedrow > 0){ return 0; }
	//if (ginsertedcol > 0){ return 0; }
	//if (zcnt < 3){ popp(); }
	while (true){
		glerr = false;
		
		while (true){//Look for the first incomplete row then break out.
			//The row to check is completely randomized by a high quality generator.
			if (debug){ cout << "gindex=" << gindex << endl; }
			gindex = generator() % 9 + 1;
			if (row[gindex].done == false){
				mcnt = gm(zrow, gindex);
				if (mcnt > 1){ break; }
			}
		}
		int rand1, rand2;
		int mcnt = gm(zrow, gindex);
		int bcnt = gbls(zrow, gindex); //get number of incomplete squares in current row.

		// generate random index to ordered list of missing numbers in row
		rand1 = generator() % mcnt + 1;

		// generate random index to ordered list of blank spots in row
		rand2 = generator() % mcnt + 1;
		//the next two lines select a random value out of the valid remaining missing numbers 
		//and a random valid blankspot out of the blanks left to choose from.
		if ((rand1 > 0) && (rand2 > 0) && (rand1 <= 9) && (rand2 <= 9)){
			int col = blrow[rand1];
			int value = mrow[rand2];
			//will only insert the randomized value at the random location first off by making certain that
			//an original puzzle clue is not being accidentally overwritten.

			//Do some validity checks before trying the actual insert
			int inrow = finrow(gindex, value);     //Make sure that number is not in current row
			int incol = fincol(col, value);        //Or column
			int tbox = gboxfromrowandcol(gindex, col);
			int inbox = finbox(tbox, value);       //or box
			if ((inrow == 0) && (incol == 0) && (inbox == 0) && (!glerr)){   //looks clean, go ahead and insert;
				if (puzzle[gindex][col] == 0){
					glastwrite = "***********************predictpath";
					thisisaguess = true;
					int res = inspuzzle(gindex, col, value);
					if (res > 0){
						thisisaguess = false;
						return res;
					}
				}
			}
		}
	}
	return 0;
}

//==========================================================    	
int  col456(int c, int v){
	//==========================================================
	//this routine should be called in a double loop where
	//col=4, val=1-9
	//then col=5 val=1-9
	//and finally col=6 val=1-9 
	// valid for columns 4,5,6
	////cout<<"in col456 "<<"c="<<c<<" v="<<v<<endl;
	//return 0;//********************************************************************
	fnc = 1000;
	//readpuzzle();
//	readboxes();
	
	int result = 0;

	int whichbox = 0;
	int res1 = 0; int res2 = 0; int res3 = 0; int res4 = 0; int res5 = 0;
	int res6 = 0; int res7 = 0; int res8 = 0; int res9 = 0;

	int box2availablespots = 3;
	int box5availablespots = 3;
	int box8availablespots = 3;



	//start out and determine that value is only found in 1 box out of 3.

	//this is valid for any column 4-6 

	res1 = finbox(2, v);
	if (res1>0){ whichbox = 2; }
	res2 = finbox(5, v);
	if ((res1>0) && (res2>0)){ return 0; }
	if (res2>0){ whichbox = 5; }
	res3 = finbox(8, v);
	if ((res3>0) && (whichbox>0)){ return 0; }
	if (res3>0){ whichbox = 8; }

	if (whichbox == 0){ return 0; }
	//need to make sure that if there is only one box currently with
	//the number v to insert, the number cannot already exist in the 
	//column you are working on
	result = fincol(c, v);
	if (result>0){ return 0; }
	//found num v in only 1 box (whichbox)


	//===============================================================
	if (whichbox != 2){
		//===============================================================
		//in box 2,we want to identify in (1,4,7)or(2,5,8) or(3,6,9) how many spots available
		//to insert number v
		//
		//    1| 2| 3|
		//    4| 5| 6|
		//    7| 8| 9|	

		//so we check rows 1,2,3 to see if num v is present.
		//if so, we decrease number of spots from 3 by 1 for each
		//row where v is found


		res1 = finrow(1, v);
		if (res1>0){ box2availablespots = 2; }
		res2 = finrow(2, v);
		if (res2>0){ box2availablespots--; }
		res3 = finrow(3, v);
		if (res3>0){ box2availablespots--; }

		//for box 2, positions we also decrement available	
		//spots if any of those positions already has a number in
		//it. However, we don't want to do this if box2availablespots is 
		//already 0.  Only if it is greater than 0.
		if ((puzzle[1][c]>0) && (res1 == 0) && (box2availablespots>0)){
			//we don't want to decrement box2availablespots again
			//if it has already been done because number v has
			//already been found to exist in row 1.

			box2availablespots--;
		}
		if ((puzzle[2][c]>0) && (res2 == 0) && (box2availablespots>0)){

			box2availablespots--;
		}
		if ((puzzle[3][c]>0) && (res3 == 0) && (box2availablespots>0)){

			box2availablespots--;
		}
		//=========================================================   
	}//end whichbox!=2  
	//=========================================================  


	//===============================================================
	if (whichbox != 5){
		//===============================================================
		//in box 5,we want to identify in (1,4,7)or(2,5,8) or(3,6,9) how many spots available   
		//to insert number v
		//
		//    1| 2| 3|
		//    4| 5| 6|
		//    7| 8| 9|	

		//so we check rows 4,5,6 to see if num v is present.
		//if so, we decrease number of spots from 3 by 1 for each
		//row where v is found


		res4 = finrow(4, v);
		if (res4>0){ box5availablespots = 2; }
		res5 = finrow(5, v);
		if (res5>0){ box5availablespots--; }
		res6 = finrow(6, v);
		if (res6>0){ box5availablespots--; }

		//for box 5, we also decrement available	
		//spots if any of those positions already has a number in
		//it. we don't want to do this if box5availablespots is 
		//already 0.  Only if it is greater than 0.
		if ((puzzle[4][c]>0) && (res4 == 0) && (box5availablespots>0)){
			//we don't want to decrement box5availablespots again
			//if it has already been done because number v has
			//already been found to exist in row 4.

			box5availablespots--;
		}
		if ((puzzle[5][c]>0) && (res5 == 0) && (box5availablespots>0)){

			box5availablespots--;
		}
		if ((puzzle[6][c]>0) && (res6 == 0) && (box5availablespots>0)){

			box5availablespots--;
		}
		//=========================================================   
	}//end whichbox!=5  
	//=========================================================  
	//===============================================================
	if (whichbox != 8){
		//===============================================================
		//in box 8,we want to identify in (1,4,7)or(2,5,8) or(3,6,9) how many spots available

		//to insert number v
		//
		//    1 2| 3|
		//    4 5| 6|
		//    7 8| 9|	

		//so we check rows 7,8,9 to see if num v is present.
		//if so, we decrease number of spots from 3 by 1 for each
		//row where v is found


		res7 = finrow(7, v);
		if (res7>0){ box8availablespots = 2; }
		res8 = finrow(8, v);
		if (res8>0){ box8availablespots--; }
		res9 = finrow(9, v);
		if (res9>0){ box8availablespots--; }

		//for box 8, we also decrement available	
		//spots if any of those positions already has a number in
		//it. we don't want to do this if box8availablespots is 
		//already 0.  Only if it is greater than 0.
		if ((puzzle[7][c]>0) && (res7 == 0) && (box8availablespots>0)){
			//we don't want to decrement box8availablespots again
			//if it has already been done because number v has
			//already been found to exist in row 7.

			box8availablespots--;
		}
		if ((puzzle[8][c]>0) && (res8 == 0) && (box8availablespots>0)){

			box8availablespots--;
		}
		if ((puzzle[9][c]>0) && (res9 == 0) && (box8availablespots>0)){

			box8availablespots--;
		}
		//=========================================================   
	}//end whichbox!=8  
	//=========================================================  

	//now we are ready to make a decision if we can insert num v somewhere in column c.
	//we know that num v is present in 1 box only.

	//we also know how many spots in the other two boxes for column c where num v could be 
	//inserted.  To successfully meet the algorithm requirements we need to have the following
	//outcomes:

	//if num v is in box 2 then we need the combination of 0 insert spots in box 5 and 
	//1 insert spot in box 8 or we need 1 insert spot in box 5 and 0 insert spots in box 8
	//
	//if num v is in box 5 then we need the combination of 0 insert spots in box 2 and
	//1 insert spot in box 8 or we need 1 insert spot in box 2 and 0 insert spots in box 8
	//
	//if num v is in box 8 then we need the combination of 0 insert spots in box 2 and 
	//1 insert spot in box 5 or 1 insert spot in box 2 and 0 insert spots in box 5. 
	//=====================================================================================
	if ((whichbox == 2) && (box5availablespots == 0) && (box8availablespots == 1)){

		//insert v in column c within box 8, in either row 7,8,9   	  
		//check puzzle[7][c] first

		if ((puzzle[7][c] == 0) && (res7 == 0)){
			////cout<<"r=7"<<endl;

			glastwrite = "col456w1"; result = inspuzzle(7, c, v);
	//		if (glerr) { debug = false; printpuzzle(); exit(0); }
			return result;
		}
		//check puzzle[8][c] next

		if ((puzzle[8][c] == 0) && (res8 == 0)){
			//cout<<"r=8"<<endl;

			glastwrite = "col456w2"; result = inspuzzle(8, c, v);
			return result;
		}
		//check puzzle[9][c] next
		if ((puzzle[9][c] == 0) && (res9 == 0)){
			////cout<<"r=9"<<endl;

			glastwrite = "col456w3"; result = inspuzzle(9, c, v);
			return result;
		}
	} //end whichbox=2 and box5=0 and box8=1
	//now check whichbox=2 and box5=1 and box8=0

	if ((whichbox == 2) && (box5availablespots == 1) && (box8availablespots == 0)){

		//insert v in column c within box 5, in either row 4,5,6   	  
		//check puzzle[4][c] first

		if ((puzzle[4][c] == 0) && (res4 == 0)){

			glastwrite = "col456w4"; result = inspuzzle(4, c, v);
			return result;
		}
		//check puzzle[5][c] next

		if ((puzzle[5][c] == 0) && (res5 == 0)){

			glastwrite = "col456w5"; result = inspuzzle(5, c, v);
			return result;
		}
		//check puzzle[6][c] next
		if ((puzzle[6][c] == 0) && (res6 == 0)){

			glastwrite = "col456w6"; result = inspuzzle(6, c, v);
			return result;
		}
	} //end whichbox=2 and box5=1 and box8=0  
	//===========================================================================

	//===========================================================================
	if ((whichbox == 5) && (box2availablespots == 0) && (box8availablespots == 1)){

		//insert v in column c within box 8, in either row 7,8,9   	  
		//check puzzle[7][c] first

		if ((puzzle[7][c] == 0) && (res7 == 0)){

			glastwrite = "col456w7"; result = inspuzzle(7, c, v);
			return result;
		}
		//check puzzle[8][c] next

		if ((puzzle[8][c] == 0) && (res8 == 0)){

			glastwrite = "col456w8"; result = inspuzzle(8, c, v);
			return result;
		}
		//check puzzle[9][c] next
		if ((puzzle[9][c] == 0) && (res9 == 0)){

			glastwrite = "col456w9"; result = inspuzzle(9, c, v);
			return result;
		}
	} //end whichbox=5 and box2=0 and box8=1
	//now check whichbox=5 and box2=1 and box8=0

	if ((whichbox == 5) && (box2availablespots == 1) && (box8availablespots == 0)){

		//insert v in column c within box 2, in either row 1,2,3   	  
		//check puzzle[1][c] first

		if ((puzzle[1][c] == 0) && (res1 == 0)){

			glastwrite = "col456w10"; result = inspuzzle(1, c, v);
			return result;
		}
		//check puzzle[2][c] next

		if ((puzzle[2][c] == 0) && (res2 == 0)){
			//   //cout<<"r=2"<<endl;
			//  //cout<<"2"<<c<<v<<endl;
			glastwrite = "col456w11"; result = inspuzzle(2, c, v);
		//	if (glerr) { debug = false; printpuzzle(); exit(0); }
			return result;
		}
		//check puzzle[3[c] next
		if ((puzzle[3][c] == 0) && (res3 == 0)){
			//   //cout<<"r=3"<<endl;
			//   //cout<<"3"<<c<<v<<endl;

			glastwrite = "col456w12"; result = inspuzzle(3, c, v);
		//	if (glerr) { debug = false; printpuzzle(); exit(0); }
			return result;
		}
	} //end whichbox=5 and box2=1 and box8=0  
	//===========================================================================


	//===========================================================================
	if ((whichbox == 8) && (box2availablespots == 0) && (box5availablespots == 1)){

		//insert v in column c within box 5, in either row 4,5,6   	  
		//check puzzle[4][c] first

		if ((puzzle[4][c] == 0) && (res4 == 0)){

			glastwrite = "col456w13"; result = inspuzzle(4, c, v);
			return result;
		}
		//check puzzle[5][c] next

		if ((puzzle[5][c] == 0) && (res5 == 0)){

			glastwrite = "col456w14"; result = inspuzzle(5, c, v);
			return result;
		}
		//check puzzle[6][c] next
		if ((puzzle[6][c] == 0) && (res6 == 0)){

			glastwrite = "col456w15"; result = inspuzzle(6, c, v);
			return result;
		}
	} //end whichbox=8 and box2=0 and box5=1
	//now check whichbox=8 and box2=1 and box5=0

	if ((whichbox == 8) && (box2availablespots == 1) && (box5availablespots == 0)){

		//insert v in column c within box 2, in either row 1,2,3   	  
		//check puzzle[1][c] first

		if ((puzzle[1][c] == 0) && (res1 == 0)){

		 	glastwrite = "col456w16"; result = inspuzzle(1, c, v);
			return result;
		}
		//check puzzle[2][c] next

		if ((puzzle[2][c] == 0) && (res2 == 0)){

			glastwrite = "col456w17"; result = inspuzzle(2, c, v);
			return result;
		}
		//check puzzle[3[c] next
		if ((puzzle[3][c] == 0) && (res3 == 0)){

			glastwrite = "col456w18"; result = inspuzzle(3, c, v);
			return result;
		}
	} //end whichbox=5 and box2=1 and box8=0  
	//===========================================================================


	return 0;

}
//============================================================================== 
//end col456();
//===============================================================================
//==========================================================    	
int  col123(int c, int v){
	//==========================================================
	//this routine should be called in a double loop where
	//col=1, val=1-9
	//then col=2 val=1-9
	//and finally col=3 val=1-9 
	// valid for columns 1,2,3
	////cout<<"in col123 "<<"c="<<c<<" v="<<v<<endl;
	//                         
	fnc = 1001;
	//readpuzzle();
	//readboxes();

	int result = 0;

	int whichbox = 0;
	int res1 = 0; int res2 = 0; int res3 = 0; int res4 = 0; int res5 = 0;
	int res6 = 0; int res7 = 0; int res8 = 0; int res9 = 0;

	int box1availablespots = 3;
	int box4availablespots = 3;
	int box7availablespots = 3;



	//start out and determine that value is only found in 1 box out of 3.

	//this is valid for any column 1-3 

	res1 = finbox(1, v);
	if (res1>0){ whichbox = 1; }
	res2 = finbox(4, v);
	if ((res1>0) && (res2>0)){ return 0; }
	if (res2>0){ whichbox = 4; }
	res3 = finbox(7, v);
	if ((res3>0) && (whichbox>0)){ return 0; }
	if (res3>0){ whichbox = 7; }

	if (whichbox == 0){ return 0; }
	//need to make sure that if there is only one box currently with
	//the number v to insert, the number cannot already exist in the 
	//column you are working on
	result = fincol(c, v);
	if (result>0){ return 0; }
	//found num v in only 1 box (whichbox)


	//===============================================================
	if (whichbox != 1){
		//===============================================================
		//in box 1,we want to identify in (1,4,7)or(2,5,8) or(3,6,9) how many spots available
		//to insert number v
		//
		//    1| 2| 3|
		//    4| 5| 6|
		//    7| 8| 9|	

		//so we check rows 1,2,3 to see if num v is present.
		//if so, we decrease number of spots from 3 by 1 for each
		//row where v is found


		res1 = finrow(1, v);
		if (res1>0){ box1availablespots = 2; }
		res2 = finrow(2, v);
		if (res2>0){ box1availablespots--; }
		res3 = finrow(3, v);
		if (res3>0){ box1availablespots--; }

		//for box 1, positions we also decrement available	
		//spots if any of those positions already has a number in
		//it. However, we don't want to do this if box1availablespots is 
		//already 0.  Only if it is greater than 0.
		if ((puzzle[1][c]>0) && (res1 == 0) && (box1availablespots>0)){
			//we don't want to decrement box1availablespots again
			//if it has already been done because number v has
			//already been found to exist in row 1.

			box1availablespots--;
		}
		if ((puzzle[2][c]>0) && (res2 == 0) && (box1availablespots>0)){

			box1availablespots--;
		}
		if ((puzzle[3][c]>0) && (res3 == 0) && (box1availablespots>0)){

			box1availablespots--;
		}
		//=========================================================   
	}//end whichbox!=1 
	//=========================================================  


	//===============================================================
	if (whichbox != 4){
		//===============================================================
		//in box 4,we want to identify in (1,4,7)or(2,5,8) or(3,6,9) how many spots available   
		//to insert number v
		//
		//    1| 2| 3|
		//    4| 5| 6|
		//    7| 8| 9|	

		//so we check rows 4,5,6 to see if num v is present.
		//if so, we decrease number of spots from 3 by 1 for each
		//row where v is found


		res4 = finrow(4, v);
		if (res4>0){ box4availablespots = 2; }
		res5 = finrow(5, v);
		if (res5>0){ box4availablespots--; }
		res6 = finrow(6, v);
		if (res6>0){ box4availablespots--; }

		//for box 4, we also decrement available	
		//spots if any of those positions already has a number in
		//it. we don't want to do this if box4availablespots is 
		//already 0.  Only if it is greater than 0.
		if ((puzzle[4][c]>0) && (res4 == 0) && (box4availablespots>0)){
			//we don't want to decrement box4availablespots again
			//if it has already been done because number v has
			//already been found to exist in row 4.

			box4availablespots--;
		}
		if ((puzzle[5][c]>0) && (res5 == 0) && (box4availablespots>0)){

			box4availablespots--;
		}
		if ((puzzle[6][c]>0) && (res6 == 0) && (box4availablespots>0)){

			box4availablespots--;
		}
		//=========================================================   
	}//end whichbox!=4  
	//=========================================================  
	//===============================================================
	if (whichbox != 7){
		//===============================================================
		//in box 7,we want to identify in (1,4,7)or(2,5,8) or(3,6,9) how many spots available

		//to insert number v
		//
		//    1 2| 3|
		//    4 5| 6|
		//    7 8| 9|	

		//so we check rows 7,8,9 to see if num v is present.
		//if so, we decrease number of spots from 3 by 1 for each
		//row where v is found


		res7 = finrow(7, v);
		if (res7>0){ box7availablespots = 2; }
		res8 = finrow(8, v);
		if (res8>0){ box7availablespots--; }
		res9 = finrow(9, v);
		if (res9>0){ box7availablespots--; }

		//for box 7, we also decrement available	
		//spots if any of those positions already has a number in
		//it. we don't want to do this if box7availablespots is 
		//already 0.  Only if it is greater than 0.
		if ((puzzle[7][c]>0) && (res7 == 0) && (box7availablespots>0)){
			//we don't want to decrement box7availablespots again
			//if it has already been done because number v has
			//already been found to exist in row 7.

			box7availablespots--;
		}
		if ((puzzle[8][c]>0) && (res8 == 0) && (box7availablespots>0)){

			box7availablespots--;
		}
		if ((puzzle[9][c]>0) && (res9 == 0) && (box7availablespots>0)){

			box7availablespots--;
		}
		//=========================================================   
	}//end whichbox!=7  
	//=========================================================  

	//now we are ready to make a decision if we can insert num v somewhere in column c.
	//we know that num v is present in 1 box only.

	//we also know how many spots in the other two boxes for column c where num v could be 
	//inserted.  To successfully meet the algorithm requirements we need to have the following
	//outcomes:

	//if num v is in box 1then we need the combination of 0 insert spots in box 4 and 
	//1 insert spot in box 7 or we need 1 insert spot in box 4 and 0 insert spots in box 7
	//
	//if num v is in box 4 then we need the combination of 0 insert spots in box 1 and
	//1 insert spot in box 7 or we need 1 insert spot in box 1 and 0 insert spots in box 7
	//
	//if num v is in box 7 then we need the combination of 0 insert spots in box 1 and 
	//1 insert spot in box 4 or 1 insert spot in box 1 and 0 insert spots in box 4. 
	//=====================================================================================
	if ((whichbox == 1) && (box4availablespots == 0) && (box7availablespots == 1)){

		//insert v in column c within box 7, in either row 7,8,9   	  
		//check puzzle[7][c] first

		if ((puzzle[7][c] == 0) && (res7 == 0)){
			////cout<<"r=7"<<endl;

			glastwrite = "col123w1"; result = inspuzzle(7, c, v);

			return result;
		}
		//check puzzle[7][c] next

		if ((puzzle[8][c] == 0) && (res8 == 0)){
			////cout<<"r=8"<<endl;

			glastwrite = "col123w2"; result = inspuzzle(8, c, v);
			return result;
		}
		//check puzzle[9][c] next
		if ((puzzle[9][c] == 0) && (res9 == 0)){
			////cout<<"r=9"<<endl;

			glastwrite = "col123w3"; result = inspuzzle(9, c, v);
			return result;
		}
	} //end whichbox=1 and box4=0 and box7=1
	//now check whichbox=1 and box4=1 and box7=0

	if ((whichbox == 1) && (box4availablespots == 1) && (box7availablespots == 0)){

		//insert v in column c within box 4, in either row 4,5,6   	  
		//check puzzle[4][c] first

		if ((puzzle[4][c] == 0) && (res4 == 0)){

			glastwrite = "col123w4"; result = inspuzzle(4, c, v);
			return result;
		}
		//check puzzle[5][c] next

		if ((puzzle[5][c] == 0) && (res5 == 0)){

			glastwrite = "col123w5"; result = inspuzzle(5, c, v);
			return result;
		}
		//check puzzle[6][c] next
		if ((puzzle[6][c] == 0) && (res6 == 0)){
			//this may be bad
	//		glastwrite = "col123w6"; result = inspuzzle(6, c, v);
		//	return result;
		}
	} //end whichbox=1 and box4=1 and box7=0  
	//===========================================================================

	//===========================================================================
	if ((whichbox == 4) && (box1availablespots == 0) && (box7availablespots == 1)){

		//insert v in column c within box 7, in either row 7,8,9   	  
		//check puzzle[7][c] first

		if ((puzzle[7][c] == 0) && (res7 == 0)){

			glastwrite = "col123w7"; result = inspuzzle(7, c, v);
			return result;
		}
		//check puzzle[8][c] next

		if ((puzzle[8][c] == 0) && (res8 == 0)){

			glastwrite = "col123w8"; result = inspuzzle(8, c, v);
			return result;
		}
		//check puzzle[9][c] next
		if ((puzzle[9][c] == 0) && (res9 == 0)){

			glastwrite = "col123w9"; result = inspuzzle(9, c, v);
			return result;
		}
	} //end whichbox=4 and box1=0 and box7=1
	//now check whichbox=3 and box1=1 and box7=0

	if ((whichbox == 4) && (box1availablespots == 1) && (box7availablespots == 0)){

		//insert v in column c within box 1, in either row 1,2,3   	  
		//check puzzle[1][c] first

		if ((puzzle[1][c] == 0) && (res1 == 0)){

			glastwrite = "col123w10"; result = inspuzzle(1, c, v);
			return result;
		}
		//check puzzle[2][c] next

		if ((puzzle[2][c] == 0) && (res2 == 0)){

			glastwrite = "col123w11"; result = inspuzzle(2, c, v);

			return result;
		}
		//check puzzle[3[c] next
		if ((puzzle[3][c] == 0) && (res3 == 0)){

			glastwrite = "col123w12"; result = inspuzzle(3, c, v);
			return result;
		}
	} //end whichbox=4 and box1=1 and box7=0  
	//===========================================================================


	//===========================================================================
	if ((whichbox == 7) && (box1availablespots == 0) && (box4availablespots == 1)){

		//insert v in column c within box 4, in either row 4,5,6   	  
		//check puzzle[4][c] first

		if ((puzzle[4][c] == 0) && (res4 == 0)){

			glastwrite = "col123w13"; result = inspuzzle(4, c, v);
			return result;
		}
		//check puzzle[5][c] next

		if ((puzzle[5][c] == 0) && (res5 == 0)){

			glastwrite = "col123w14"; result = inspuzzle(5, c, v);
			return result;
		}
		//check puzzle[6][c] next
		if ((puzzle[6][c] == 0) && (res6 == 0)){

			glastwrite = "col456w15"; result = inspuzzle(6, c, v);
			return result;
		}
	} //end whichbox=7 and box1=0 and box4=1
	//now check whichbox=7 and box1=1 and box4=0

	if ((whichbox == 7) && (box1availablespots == 1) && (box4availablespots == 0)){

		//insert v in column c within box `, in either row 1,2,3   	  
		//check puzzle[1][c] first

		if ((puzzle[1][c] == 0) && (res1 == 0)){

			glastwrite = "col123w16"; result = inspuzzle(1, c, v);
			return result;
		}
		//check puzzle[2][c] next

		if ((puzzle[2][c] == 0) && (res2 == 0)){

			glastwrite = "col123w17"; result = inspuzzle(2, c, v);
			return result;
		}
		//check puzzle[3[c] next
		if ((puzzle[3][c] == 0) && (res3 == 0)){

			glastwrite = "col123w18"; result = inspuzzle(3, c, v);
			return result;
		}
	} //end whichbox=4 and box1=1 and box7=0  
	//===========================================================================


	return 0;

}
//============================================================================== 
//end col123();

//==========================================================    	
int  col789(int c, int v){
	//==========================================================
	//this routine should be called in a double loop where
	//col=7, val=1-9
	//then col=8 val=1-9
	//and finally col=9 val=1-9 
	// valid for columns 7,8,9
	////cout<<"in col789 "<<"c="<<c<<" v="<<v<<endl;
	//                         
	fnc = 1002;
	//readpuzzle();
//	readboxes();

	int result = 0;

	int whichbox = 0;
	int res1 = 0; int res2 = 0; int res3 = 0; int res4 = 0; int res5 = 0;
	int res6 = 0; int res7 = 0; int res8 = 0; int res9 = 0;

	int box3availablespots = 3;
	int box6availablespots = 3;
	int box9availablespots = 3;



	//start out and determine that value is only found in 1 box out of 3.

	//this is valid for any column 7-9

	res1 = finbox(3, v);
	if (res1>0){ whichbox = 3; }
	res2 = finbox(6, v);
	if ((res1>0) && (res2>0)){ return 0; }
	if (res2>0){ whichbox = 6; }
	res3 = finbox(9, v);
	if ((res3>0) && (whichbox>0)){ return 0; }
	if (res3>0){ whichbox = 9; }

	if (whichbox == 0){ return 0; }
	//need to make sure that if there is only one box currently with
	//the number v to insert, the number cannot already exist in the 
	//column you are working on
	result = fincol(c, v);
	if (result>0){ return 0; }
	//found num v in only 1 box (whichbox)


	//===============================================================
	if (whichbox != 3){
		//===============================================================
		//in box 3,we want to identify in (1,4,7)or(2,5,8) or(3,6,9) how many spots available
		//to insert number v
		//
		//    1| 2| 3|
		//    4| 5| 6|
		//    7| 8| 9|	

		//so we check rows 1,2,3 to see if num v is present.
		//if so, we decrease number of spots from 3 by 1 for each
		//row where v is found


		res1 = finrow(1, v);
		if (res1>0){ box3availablespots = 2; }
		res2 = finrow(2, v);
		if (res2>0){ box3availablespots--; }
		res3 = finrow(3, v);
		if (res3>0){ box3availablespots--; }

		//for box 3, positions we also decrement available	
		//spots if any of those positions already has a number in
		//it. However, we don't want to do this if box3availablespots is 
		//already 0.  Only if it is greater than 0.
		if ((puzzle[1][c]>0) && (res1 == 0) && (box3availablespots>0)){
			//we don't want to decrement box3availablespots again
			//if it has already been done because number v has
			//already been found to exist in row 1.

			box3availablespots--;
		}
		if ((puzzle[2][c]>0) && (res2 == 0) && (box3availablespots>0)){

			box3availablespots--;
		}
		if ((puzzle[3][c]>0) && (res3 == 0) && (box3availablespots>0)){

			box3availablespots--;
		}
		//=========================================================   
	}//end whichbox!=3 
	//=========================================================  


	//===============================================================
	if (whichbox != 6){
		//===============================================================
		//in box 6,we want to identify in (1,4,7)or(2,5,8) or(3,6,9) how many spots available   
		//to insert number v
		//
		//    1| 2| 3|
		//    4| 5| 6|
		//    7| 8| 9|	

		//so we check rows 4,5,6 to see if num v is present.
		//if so, we decrease number of spots from 3 by 1 for each
		//row where v is found


		res4 = finrow(4, v);
		if (res4>0){ box6availablespots = 2; }
		res5 = finrow(5, v);
		if (res5>0){ box6availablespots--; }
		res6 = finrow(6, v);
		if (res6>0){ box6availablespots--; }

		//for box 6, we also decrement available	
		//spots if any of those positions already has a number in
		//it. we don't want to do this if box4availablespots is 
		//already 0.  Only if it is greater than 0.
		if ((puzzle[4][c]>0) && (res4 == 0) && (box6availablespots>0)){
			//we don't want to decrement box6availablespots again
			//if it has already been done because number v has
			//already been found to exist in row 6.

			box6availablespots--;
		}
		if ((puzzle[5][c]>0) && (res5 == 0) && (box6availablespots>0)){

			box6availablespots--;
		}
		if ((puzzle[6][c]>0) && (res6 == 0) && (box6availablespots>0)){

			box6availablespots--;
		}
		//=========================================================   
	}//end whichbox!=6  
	//=========================================================  
	//===============================================================
	if (whichbox != 9){
		//===============================================================
		//in box 9,we want to identify in (1,4,7)or(2,5,8) or(3,6,9) how many spots available

		//to insert number v
		//
		//    1 2| 3|
		//    4 5| 6|
		//    7 8| 9|	

		//so we check rows 7,8,9 to see if num v is present.
		//if so, we decrease number of spots from 3 by 1 for each
		//row where v is found


		res7 = finrow(7, v);
		if (res7>0){ box9availablespots = 2; }
		res8 = finrow(8, v);
		if (res8>0){ box9availablespots--; }
		res9 = finrow(9, v);
		if (res9>0){ box9availablespots--; }

		//for box 9, we also decrement available	
		//spots if any of those positions already has a number in
		//it. we don't want to do this if box9availablespots is 
		//already 0.  Only if it is greater than 0.
		if ((puzzle[7][c]>0) && (res7 == 0) && (box9availablespots>0)){
			//we don't want to decrement box9availablespots again
			//if it has already been done because number v has
			//already been found to exist in row 9.

			box9availablespots--;
		}
		if ((puzzle[8][c]>0) && (res8 == 0) && (box9availablespots>0)){

			box9availablespots--;
		}
		if ((puzzle[9][c]>0) && (res9 == 0) && (box9availablespots>0)){

			box9availablespots--;
		}
		//=========================================================   
	}//end whichbox!=9 
	//=========================================================  

	//now we are ready to make a decision if we can insert num v somewhere in column c.
	//we know that num v is present in 1 box only.

	//we also know how many spots in the other two boxes for column c where num v could be 
	//inserted.  To successfully meet the algorithm requirements we need to have the following
	//outcomes:

	//if num v is in box 3then we need the combination of 0 insert spots in box 6 and 
	//1 insert spot in box 9 or we need 1 insert spot in box 6 and 0 insert spots in box 9
	//
	//if num v is in box 6 then we need the combination of 0 insert spots in box 3 and
	//1 insert spot in box 9 or we need 1 insert spot in box 3 and 0 insert spots in box 9
	//
	//if num v is in box 9 then we need the combination of 0 insert spots in box 3 and 
	//1 insert spot in box 6 or 1 insert spot in box 4and 0 insert spots in box 6. 
	//=====================================================================================
	if ((whichbox == 3) && (box6availablespots == 0) && (box9availablespots == 1)){

		//insert v in column c within box 9, in either row 7,8,9   	  
		//check puzzle[7][c] first

		if ((puzzle[7][c] == 0) && (res7 == 0)){

			glastwrite = "col789w1"; result = inspuzzle(7, c, v);

			return result;
		}
		//check puzzle[7][c] next

		if ((puzzle[8][c] == 0) && (res8 == 0)){

			glastwrite = "col789w2"; result = inspuzzle(8, c, v);
			return result;
		}
		//check puzzle[9][c] next
		if ((puzzle[9][c] == 0) && (res9 == 0)){

			glastwrite = "col789w3"; result = inspuzzle(9, c, v);
			return result;
		}
	} //end whichbox=3 and box6=0 and box9=1
	//now check whichbox=3 and box6=1 and box9=0

	if ((whichbox == 3) && (box6availablespots == 1) && (box9availablespots == 0)){

		//insert v in column c within box 6, in either row 4,5,6   	  
		//check puzzle[4][c] first

		if ((puzzle[4][c] == 0) && (res4 == 0)){

			glastwrite = "col789w4"; result = inspuzzle(4, c, v);
			return result;
		}
		//check puzzle[5][c] next

		if ((puzzle[5][c] == 0) && (res5 == 0)){

			glastwrite = "col789w5"; result = inspuzzle(5, c, v);
			return result;
		}
		//check puzzle[6][c] next
		if ((puzzle[6][c] == 0) && (res6 == 0)){

			glastwrite = "col789w6"; result = inspuzzle(6, c, v);
			return result;
		}
	} //end whichbox=3 and box6=1 and box9=0  
	//===========================================================================

	//===========================================================================
	if ((whichbox == 6) && (box3availablespots == 0) && (box9availablespots == 1)){

		//insert v in column c within box 9, in either row 7,8,9   	  
		//check puzzle[7][c] first

		if ((puzzle[7][c] == 0) && (res7 == 0)){

			glastwrite = "col789w7"; result = inspuzzle(7, c, v);
			return result;
		}
		//check puzzle[8][c] next

		if ((puzzle[8][c] == 0) && (res8 == 0)){

			glastwrite = "col789w8"; result = inspuzzle(8, c, v);
			return result;
		}
		//check puzzle[9][c] next
		if ((puzzle[9][c] == 0) && (res9 == 0)){

			glastwrite = "col789w9"; result = inspuzzle(9, c, v);
			return result;
		}
	} //end whichbox=6 and box3=0 and box9=1
	//now check whichbox=6 and box3=1 and box9=0

	if ((whichbox == 6) && (box3availablespots == 1) && (box9availablespots == 0)){

		//insert v in column c within box 3, in either row 1,2,3   	  
		//check puzzle[1][c] first

		if ((puzzle[1][c] == 0) && (res1 == 0)){

			glastwrite = "col789w10"; result = inspuzzle(1, c, v);
			return result;
		}
		//check puzzle[2][c] next

		if ((puzzle[2][c] == 0) && (res2 == 0)){

			glastwrite = "col789w11"; result = inspuzzle(2, c, v);

			return result;
		}
		//check puzzle[3[c] next
		if ((puzzle[3][c] == 0) && (res3 == 0)){

			glastwrite = "col789w12"; result = inspuzzle(3, c, v);
			return result;
		}
	} //end whichbox=6and box3=1 and box9=0  
	//===========================================================================


	//===========================================================================
	if ((whichbox == 9) && (box3availablespots == 0) && (box6availablespots == 1)){

		//insert v in column c within box 6, in either row 4,5,6   	  
		//check puzzle[4][c] first

		if ((puzzle[4][c] == 0) && (res4 == 0)){

			glastwrite = "col789w13"; result = inspuzzle(4, c, v);
			return result;
		}
		//check puzzle[5][c] next

		if ((puzzle[5][c] == 0) && (res5 == 0)){

			glastwrite = "col789w14"; result = inspuzzle(5, c, v);
			return result;
		}
		//check puzzle[6][c] next
		if ((puzzle[6][c] == 0) && (res6 == 0)){

			glastwrite = "col789w15"; result = inspuzzle(6, c, v);
			return result;
		}
	} //end whichbox=9 and box3=0 and box6=1
	//now check whichbox=9 and box3=1 and box6=0

	if ((whichbox == 9) && (box3availablespots == 1) && (box6availablespots == 0)){

		//insert v in column c within box 3, in either row 1,2,3   	  
		//check puzzle[1][c] first

		if ((puzzle[1][c] == 0) && (res1 == 0)){

			glastwrite = "col789w16"; result = inspuzzle(1, c, v);
			return result;
		}
		//check puzzle[2][c] next

		if ((puzzle[2][c] == 0) && (res2 == 0)){

			glastwrite = "col789w17"; result = inspuzzle(2, c, v);
			return result;
		}
		//check puzzle[3[c] next
		if ((puzzle[3][c] == 0) && (res3 == 0)){

			glastwrite = "col789w18"; result = inspuzzle(3, c, v);
			return result;
		}
	} //end whichbox=6 and box3=1 and box9=0  
	//===========================================================================


	return 0;

}
//============================================================================== 
//end col789();

//===============================================================================
void insertboxinpuzzle(int b,int i,int v){
//	cout<<"Inserting box "<<b<< "into puzzle"<<endl;

	int r, c;
	switch (b){
	case 1:
		if (i < 4){ r = 1; c = i;  }
		else{
			if (i < 7){ r = 2; c = i - 3; }
			else{
				r = 3; c = i - 6;
			}
		}
		break;
	case 2: 
		if (i < 4){ r = 1; c = i+3; }
		else{
			if (i < 7){ r = 2; c = i; }
			else{
				r = 3; c = i - 3;
			}
		}
		break;
	case 3: 
		if (i < 4){ r = 1; c = i + 6; }
		else{
			if (i < 7){ r = 2; c = i+3; }
			else{
				r = 3; c = i;
			}
		}
		break;
	case 4:
		if (i < 4){ r = 4; c = i; }
		else{
			if (i < 7){ r = 5; c = i - 3; }
			else{
				r = 6; c = i-6;
			}
		}
		break;

	case 5: 
		if (i < 4){ r = 4; c = i + 3; }
		else{
			if (i < 7){ r = 5; c = i; }
			else{
				r = 6; c = i - 3;
			}
		}
		break;

	case 6:
		if (i < 4){ r = 4; c = i + 6; }
		else{
			if (i < 7){ r = 5; c = i+3; }
			else{
				r = 6; c = i;
			}
		}
		break;

	case 7:
		if (i < 4){ r = 7; c = i; }
		else{
			if (i < 7){ r = 8; c = i - 3; }
			else{
				r = 9; c = i-6;
			}
		}
		break;

	case 8: 
		if (i < 4){ r = 7; c = i+3; }
		else{
			if (i < 7){ r = 8; c = i; }
			else{
				r = 9; c = i - 3;
			}
		}
		break;
		
	case 9: 
		if (i < 4){ r = 7; c = i + 6; }
		else{
			if (i < 7){ r = 8; c = i+3; }
			else{
				r = 9; c = i;
			}
		}
		break;
	}
	glastwrite = "**********insertboxinpuzzle***********";
	inspuzzle(r, c, v);
	
	return;
}
//########################################################## 
//====================================================
int cornercancel(int b, int v){
	//====================================================
	int res = finbox(b, v);
	//already in box.  done.
	if (res>0){ return 0; }
	int insertspots = 9;
	int colres1 = 0; int colres2 = 0; int colres3 = 0;
	int rowres1 = 0; int rowres2 = 0; int rowres3 = 0;

	//limit this algorithm to boxes 1,3,7 and 9.
	//the corner boxes.
	switch (b){
		//return if not corner box.
	case 2:case 4:case 5:case 6:case 8:return 0; break;
		break;
	}

	//box 1
	//if box =1 then rows are 1,2,3 and cols are 1,2,3
//	readbox(b);

	switch (b){
	case 1:

		colres1 = fincol(1, v);
		if (colres1>0){ insertspots = insertspots - 3; }
		colres2 = fincol(2, v);
		if (colres2>0){ insertspots = insertspots - 3; }
		colres3 = fincol(3, v);
		if (colres3>0){ insertspots = insertspots - 3; }
		//i think we should get out if v is found in more than
		//1 column 
		if (insertspots != 6){ return 0; }

		//now check rows, but insertspots will be decremented
		//by 2 if v is found  
		rowres1 = finrow(1, v);
		rowres2 = finrow(2, v);
		rowres3 = finrow(3, v);
		break;
	case 2:

		colres1 = fincol(4, v);
		if (colres1>0){ insertspots = insertspots - 3; }
		colres2 = fincol(5, v);
		if (colres2>0){ insertspots = insertspots - 3; }
		colres3 = fincol(6, v);
		if (colres3>0){ insertspots = insertspots - 3; }
		//i think we should get out if v is found in more than
		//1 column 
		if (insertspots != 6){ return 0; }

		//now check rows, but insertspots will be decremented
		//by 2 if v is found  
		rowres1 = finrow(1, v);
		rowres2 = finrow(2, v);
		rowres3 = finrow(3, v);
		break;
	case 3:

		colres1 = fincol(7, v);
		if (colres1>0){ insertspots = insertspots - 3; }
		colres2 = fincol(8, v);
		if (colres2>0){ insertspots = insertspots - 3; }
		colres3 = fincol(9, v);
		if (colres3>0){ insertspots = insertspots - 3; }
		//i think we should get out if v is found in more than
		//1 column 
		if (insertspots != 6){ return 0; }

		//now check rows, but insertspots will be decremented
		//by 2 if v is found  
		rowres1 = finrow(1, v);
		rowres2 = finrow(2, v);
		rowres3 = finrow(3, v);
		break;
	case 4:

		colres1 = fincol(1, v);
		if (colres1>0){ insertspots = insertspots - 3; }
		colres2 = fincol(2, v);
		if (colres2>0){ insertspots = insertspots - 3; }
		colres3 = fincol(3, v);
		if (colres3>0){ insertspots = insertspots - 3; }
		//i think we should get out if v is found in more than
		//1 column 
		if (insertspots != 6){ return 0; }

		//now check rows, but insertspots will be decremented
		//by 2 if v is found  
		rowres1 = finrow(4, v);
		rowres2 = finrow(5, v);
		rowres3 = finrow(6, v);
		break;
	case 5:

		colres1 = fincol(4, v);
		if (colres1>0){ insertspots = insertspots - 3; }
		colres2 = fincol(5, v);
		if (colres2>0){ insertspots = insertspots - 3; }
		colres3 = fincol(6, v);
		if (colres3>0){ insertspots = insertspots - 3; }
		//i think we should get out if v is found in more than
		//1 column 
		if (insertspots != 6){ return 0; }

		//now check rows, but insertspots will be decremented
		//by 2 if v is found  
		rowres1 = finrow(4, v);
		rowres2 = finrow(5, v);
		rowres3 = finrow(6, v);
		break;
	case 6:

		colres1 = fincol(7, v);
		if (colres1>0){ insertspots = insertspots - 3; }
		colres2 = fincol(8, v);
		if (colres2>0){ insertspots = insertspots - 3; }
		colres3 = fincol(9, v);
		if (colres3>0){ insertspots = insertspots - 3; }
		//i think we should get out if v is found in more than
		//1 column 
		if (insertspots != 6){ return 0; }

		//now check rows, but insertspots will be decremented
		//by 2 if v is found  
		rowres1 = finrow(4, v);
		rowres2 = finrow(5, v);
		rowres3 = finrow(6, v);

	case 7:

		colres1 = fincol(1, v);
		if (colres1>0){ insertspots = insertspots - 3; }
		colres2 = fincol(2, v);
		if (colres2>0){ insertspots = insertspots - 3; }
		colres3 = fincol(3, v);
		if (colres3>0){ insertspots = insertspots - 3; }
		//i think we should get out if v is found in more than
		//1 column 
		if (insertspots != 6){ return 0; }

		//now check rows, but insertspots will be decremented
		//by 2 if v is found  
		rowres1 = finrow(7, v);
		rowres2 = finrow(8, v);
		rowres3 = finrow(9, v);
		break;

	case 8:

		colres1 = fincol(4, v);
		if (colres1>0){ insertspots = insertspots - 3; }
		colres2 = fincol(5, v);
		if (colres2>0){ insertspots = insertspots - 3; }
		colres3 = fincol(6, v);
		if (colres3>0){ insertspots = insertspots - 3; }
		//i think we should get out if v is found in more than
		//1 column 
		if (insertspots != 6){ return 0; }

		//now check rows, but insertspots will be decremented
		//by 2 if v is found  
		rowres1 = finrow(7, v);
		rowres2 = finrow(8, v);
		rowres3 = finrow(9, v);
		break;

	case 9:

		colres1 = fincol(7, v);
		if (colres1>0){ insertspots = insertspots - 3; }
		colres2 = fincol(8, v);
		if (colres2>0){ insertspots = insertspots - 3; }
		colres3 = fincol(9, v);
		if (colres3>0){ insertspots = insertspots - 3; }
		//i think we should get out if v is found in more than
		//1 column 
		if (insertspots != 6){ return 0; }

		//now check rows, but insertspots will be decremented
		//by 2 if v is found  
		rowres1 = finrow(7, v);
		rowres2 = finrow(8, v);
		rowres3 = finrow(9, v);
		break;

		break;
	}


	//the rest is box independent*************************

	int rescount = 0;
	if (rowres1>0){ rescount++; }
	if (rowres2>0){ rescount++; }
	if (rowres3>0){ rescount++; }
	if (rescount != 1) { return 0; }
	insertspots = 4;
	//  if ((rowres1>0)||(rowres2>0)||(rowres3>0)){insertspots=4;}  bad code 2 lines
	//  else{return 0;}
	//so now we have verified that the number has been found
	//in one row and one column. Therefore we have whittled
	//down the insertspots to 4. in order to get down to 1
	//we have to do some more checks on how many blank and 
	//how many occupied spaces were crossed by the row and
	//column hits for v.
	//

	int cand1 = 0; int cand2 = 0; int cand3 = 0; int cand4 = 0;

	if ((colres1>0) && (rowres1>0)){
		cand1 = 5; cand2 = 6; cand3 = 8; cand4 = 9;
	}

	if ((colres1>0) && (rowres2>0)){
		cand1 = 2; cand2 = 3; cand3 = 8; cand4 = 9;
	}

	if ((colres1>0) && (rowres3>0)){
		cand1 = 2; cand2 = 3; cand3 = 5; cand4 = 6;
	}

	//=======================================   	
	if ((colres2>0) && (rowres1>0)){
		cand1 = 4; cand2 = 6; cand3 = 7; cand4 = 9;
	}

	if ((colres2>0) && (rowres2>0)){
		cand1 = 1; cand2 = 3; cand3 = 7; cand4 = 9;
	}

	if ((colres2>0) && (rowres3>0)){
		cand1 = 1; cand2 = 3; cand3 = 4; cand4 = 6;
	}
	//=======================================   	
	if ((colres3>0) && (rowres1>0)){
		cand1 = 4; cand2 = 5; cand3 = 7; cand4 = 8;
	}

	if ((colres3>0) && (rowres2>0)){
		cand1 = 1; cand2 = 2; cand3 = 7; cand4 = 8;
	}

	if ((colres3>0) && (rowres3>0)){
		cand1 = 1; cand2 = 2; cand3 = 4; cand4 = 5;
	}
	//=======================================   	


	//if cand1 is not 0 then we can skip checking any other rows
	//and columns, because we have met the conditions to check 
	//for blanks among the candidates.  We need a total of 1 blank
	//space.  The insert candidate will be the blank 1 if the other
	//three are occupied.
	//we only pay attention to whichcandidateisinsertpoint if insertspots ends up = 1

	int insertpoint = 0;

	if (cand1>0){
		if (box[b].val[cand1] != 0){ insertspots--; }
		else{ insertpoint = cand1; }
		if (box[b].val[cand2] != 0){ insertspots--; }
		else{ insertpoint = cand2; }
		if (box[b].val[cand3] != 0){ insertspots--; }
		else{ insertpoint = cand3; }
		if (box[b].val[cand4] != 0){ insertspots--; }
		else{ insertpoint = cand4; }
		if (insertspots == 1){
			if (box[b].val[insertpoint] == 0){
				//box[b].val[insertpoint] = v;
				insertboxinpuzzle(b,insertpoint,v);
				return 0;
			}
		}
	}
	return 0;
}
//====================================================         


//=====================================================================
int newalgorithm(int r, int v){
	//=====================================================================	
	//first check to make sure v is not in row                            	
	//check box 1 2 3 for 1 occurrence of v                               	
	//this is valid for rows 1,2,3                                          
	//insertspots=9;                                                        
	//if v in a box then insertspots=6;                                     
	//if box =3 then check 1 thru 6 for occupied.                           
	//decrement insertspots for each occupied                               
	//should end up with insertspots=2                                      
	//find first blank in 1 thru 6                                          
	//check if v is found in that col. if it is                             
	//then insertspot is the other blank in 1thru 6                         
	//if not, check the other blank spot for v in that col.                 
	//if v in that col then insert spot was the first blank in 1 thru 6.    
	//similar algorithm for if v found in box 2 or box 1.                   
	//similar algorittm for boxes 4 5 6 and also 7,8,9  

	int res = finrow(r, v);

	if (res>0){ return 0; }

	int box1 = 0; int box2 = 0; int box3 = 0;
	switch (r){
	case 1:case 2:case 3: box1 = 1; box2 = 2; box3 = 3; break;
	case 4:case 5:case 6: box1 = 4; box2 = 5; box3 = 6; break;
	case 7:case 8:case 9: box1 = 7; box2 = 8; box3 = 9; break;
		break;
	}
	//look for v in 1 box only                   
	int boxcount = 0;
	int boxres1 = 0; int boxres2 = 0; int boxres3 = 0;

	boxres1 = finbox(box1, v);
	if (boxres1>0){ boxcount++; }
	boxres2 = finbox(box2, v);
	if (boxres2>0){ boxcount++; if (boxcount > 1){ return 0; } }
	boxres3 = finbox(box3, v);
	if (boxres3>0){ boxcount++; if (boxcount > 1){ return 0; } }
	if (boxcount == 0){ return 0; }

	//now we know v appears in only one box. find which box and start decrementing insertspots when
	//occupied squares are found. otherwise start taking note of which squares are blank and save
	//that for later.

	int insertspots = 6;
	int firstblank = 0;
	int secondblank = 0;

	if (boxres1>0){
		if (puzzle[r][4] != 0){ insertspots--; }
		else{ firstblank = 4; }
		if (puzzle[r][5] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 5; } else{ secondblank = 5; } }
		if (puzzle[r][6] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 6; } else{ secondblank = 6; } }
		if (puzzle[r][7] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 7; } else{ secondblank = 7; } }
		if (puzzle[r][8] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 8; } else{ secondblank = 8; } }
		if (puzzle[r][9] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 9; } else{ secondblank = 9; } }
		if (insertspots != 2){ return 0; }
	}
	if (boxres2>0){
		if (puzzle[r][1] != 0){ insertspots--; }
		else{ firstblank = 1; }
		if (puzzle[r][2] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 2; } else{ secondblank = 2; } }
		if (puzzle[r][3] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 3; } else{ secondblank = 3; } }
		if (puzzle[r][7] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 7; } else{ secondblank = 7; } }
		if (puzzle[r][8] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 8; } else{ secondblank = 8; } }
		if (puzzle[r][9] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 9; } else{ secondblank = 9; } }
		if (insertspots != 2){ return 0; }
	}
	if (boxres3>0){
		if (puzzle[r][1] != 0){ insertspots--; }
		else{ firstblank = 1; }
		if (puzzle[r][2] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 2; } else{ secondblank = 2; } }
		if (puzzle[r][3] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 3; } else{ secondblank = 3; } }
		if (puzzle[r][4] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 4; } else{ secondblank = 4; } }
		if (puzzle[r][5] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 5; } else{ secondblank = 5; } }
		if (puzzle[r][6] != 0){ insertspots--; }
		else{ if (firstblank == 0){ firstblank = 6; } else{ secondblank = 6; } }
		if (insertspots != 2){ return 0; }
	}
	//ok we have two insertspots  and two blanks identified.  Now we look for v in each blank column.
	//if we find it in 1 then the insertspot is the other. if we find it both or neither the conditions for the 
	//algorithm were not met and we get out.

	int firstblankresult = 0;
	int secondblankresult = 0;
	int resultcount = 0;
	firstblankresult = fincol(firstblank, v);
	if (firstblankresult>0){ resultcount++; }
	secondblankresult = fincol(secondblank, v);
	if (secondblankresult>0){ resultcount++; }
	if (resultcount != 1){ return 0; }

	//now we are ready to pick the insert column for v in row r.

	int insertcolumn = 0;
	if (firstblankresult>0){ insertcolumn = secondblank; }
	if (secondblankresult>0){ insertcolumn = firstblank; }
	glastwrite = "newalgorithmw1"; res = inspuzzle(r, insertcolumn, v);
	return res;
	return 0;
}
//==========================================================================
//end newalgorithm
//==========================================================================

//========================================================================
int getpuzzleandeditmask()
//========================================================================
//  This function determines what input file will be used.  If i.txt exists,
//  then it will be used as the puzzle to solve.  If it does not exist, then
//  one of the saved html files from the websudoku site will be used.  Any level
//  puzzle can be selected.  To solve the puzzle, first you right click on "
//  view frame source".  Then right click anywhere in the html file and click 
//  on "save as" and just save it as the default file name.  After it has been
//  saved, then you can close that tab on your browser.  To see the puzzle being
//  solved next to the puzzle, hit middle button on browser to shrink it to half
//  a screen.   Then click on the linux virtual machine and move the terminal
//  window adjacent to the puzzle on the web page and type ./a.out at the cursor
//  and watch as the puzzle gets solved.
//  methodology updated on 03/17/16 by me  Marion Barbee.
{
	int offset;
	string line;
	file.close();
	ifstream file;
	file.open("i.txt");
	if (file.is_open()){ puzzletype = "manual input"; ranonce = true; return 0; }
	// The following allows for different level puzzles to be selected as well as accounting for
	// the naming conventions of the website which may be view-source_show...or view-source_view


	//website has changed naming convention.  Need to modify or wildcard this.

	file.open("view-source_view.websudoku.com__level=4.html");
	if (!(file.is_open())){ file.open("view-source_show.websudoku.com__level=4.html"); }
	if ((file.is_open()) && (puzzletype == "none")){ puzzletype = "EVIL"; }

	if (!(file.is_open())){ file.open("view-source_view.websudoku.com__level=3.html"); }
	if (!(file.is_open())){ file.open("view-source_show.websudoku.com__level=3.html"); }
	if ((file.is_open()) && (puzzletype == "none")){ puzzletype = "HARD"; }

	if (!(file.is_open())){ file.open("view-source_view.websudoku.com__level=2.html"); }
	if (!(file.is_open())){ file.open("view-source_show.websudoku.com__level=2.html"); }
	if ((file.is_open()) && (puzzletype == "none")){ puzzletype = "MEDIUM"; }


	if (!(file.is_open())){ file.open("view-source_view.websudoku.com__level=1.html"); }
	if (!(file.is_open())){ file.open("view-source_show.websudoku.com__level=1.html"); }
	if ((file.is_open()) && (puzzletype == "none")){ puzzletype = "EASY"; }

	//to account for filename change
	if (!(file.is_open())){ file.open("view-source_https___nine.websudoku.com__level=4.html"); }
	if (!(file.is_open())){ file.open("view-source_https___show.websudoku.com__level=4.html"); }
	if (!(file.is_open())){ file.open("view-source_https___view.websudoku.com__level=4.html"); }
	if ((file.is_open()) && (puzzletype == "none")){ puzzletype = "EVIL"; }

	if (!(file.is_open())){ file.open("view-source_https___nine.websudoku.com__level=3.html"); }
	if (!(file.is_open())){ file.open("view-source_https___show.websudoku.com__level=3.html"); }
	if (!(file.is_open())){ file.open("view-source_https___view.websudoku.com__level=3.html"); }
	if ((file.is_open()) && (puzzletype == "none")){ puzzletype = "HARD"; }

	if (!(file.is_open())){ file.open("view-source_https___nine.websudoku.com__level=2.html"); }
	if (!(file.is_open())){ file.open("view-source_https___show.websudoku.com__level=2.html"); }
	if (!(file.is_open())){ file.open("view-source_https___view.websudoku.com__level=2.html"); }
	if ((file.is_open()) && (puzzletype == "none")){ puzzletype = "MEDIUM"; }

	if (!(file.is_open())){ file.open("view-source_https___nine.websudoku.com__level=1.html"); }
	if (!(file.is_open())){ file.open("view-source_https___show.websudoku.com__level=1.html"); }
	if (!(file.is_open())){ file.open("view-source_https___view.websudoku.com__level=1.html"); }
	if ((file.is_open()) && (puzzletype == "none")){ puzzletype = "EASY"; }

	if (!(file.is_open())){ file.open("webpuzzle.html"); }
	if ((file.is_open()) && (puzzletype == "none")){ puzzletype = "batch"; }
	if (!(file.is_open())){ cout << "ERROR! NO INPUT PUZZLE FOUND" << endl; exit(0); }

	// cheat is a string var that stores the completed puzzle found on the web page html frame source.
	// To prepare the puzzle for solving, the editmask has to be applied to the cheat string to blank
	// out the squares to be solved. Once the binary editmask has been applied, then the puzzle is copied
	// to i.txt and used as input to the program.  If i.txt already exists, then this process is skipped.
	// The allows manual creation of puzzles to be solved.  At the end of the solution, i.txt, the
	//  saveinitialpuzzle files are erased, as well as the view-source...files from the
	// websudoku site.

	//string str("var cheat=");  change in chrome
	string str("cheat=");
	string str2("editmask");
	int answerarray[82];
	int array[150];
	int mask[150];
	int curline = 0;
	int i = 1;
	char character;
	while (getline(file, line)) {
		curline++;
		//cout << "curline= " << curline << endl;
		if (line.find(str) != string::npos){
			//cout<<"var cheat= found line= "<<curline<<endl;
			//cout<<line<<endl; 
			offset = 14; //change in chrome
			//offset = 8;

			i = 1;
			while (i <= 81){
				character = line[offset];
				//cout<<"character="<<character<<endl;

				//Store the ascii digits as numeric digits by subtracting ascii value for '0'

				array[i] = character - '0';
				// cout<<"i= "<<i<<" "<<"array[i]= "<<array[i]<<endl;
				offset++;
				i++;

			}
		}
		if (line.find(str2) != string::npos){
			// cout<<"editmask found line= "<<curline<<endl;
			//   cout<<line<<endl;
			offset = 44;

			i = 1;
			while (i <= 81){
				character = line[offset];
				//	cout<<"character="<<character<<endl;
				mask[i] = character - '0';
				//	cout<<"i= "<<i<<" "<<"mask[i]= "<<mask[i]<<endl;
				offset++;
				i++;
			}
		}
	}
	file.close();

	// Apply editmask to blank out squares to be solved.

	for (int j = 1; j <= 81; j++){
		// Save answered puzzle for diagnostic purposes

		answerarray[j] = array[j];
		if (mask[j] == 1){
			array[j] = 0;
		}
		//	cout<<array[j]<<endl;
	}

	//Chop 81 digit string in to 9 rows of 9.   
	//Store puzzle to be solved in memory, write it to i.txt and print it out.  

	int zrow = 1;
	for (int index = 1; index <= 9; index++)
		puzzle[zrow][index] = array[index];
	zrow = 2;

	for (int index = 10; index <= 18; index++)
		puzzle[zrow][index - 9] = array[index];
	zrow = 3;
	for (int index = 19; index <= 27; index++)
		puzzle[zrow][index - 18] = array[index];
	zrow = 4;
	for (int index = 28; index <= 36; index++)
		puzzle[zrow][index - 27] = array[index];
	zrow = 5;
	for (int index = 37; index <= 45; index++)
		puzzle[zrow][index - 36] = array[index];
	zrow = 6;
	for (int index = 46; index <= 54; index++)
		puzzle[zrow][index - 45] = array[index];
	zrow = 7;
	for (int index = 55; index <= 63; index++)
		puzzle[zrow][index - 54] = array[index];
	zrow = 8;
	for (int index = 64; index <= 72; index++)
		puzzle[zrow][index - 63] = array[index];
	zrow = 9;
	for (int index = 73; index <= 81; index++)
		puzzle[zrow][index - 72] = array[index];


	writeinitialpuzzle();
	saveinitialpuzzle();
	popp();
	return 0;
}
 
//==================================================================
 
//==========================================================
//                                                                                     
// end program solve                                                           
// Author Marion Barbee                                                                
// Completed Sep 5, 2018                                                                      
//                                                                                     
//##########################################################     
















