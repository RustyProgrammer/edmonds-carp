﻿// Win32Project1.cpp : Defines the entry point for the application.
//

#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#pragma warning(disable:4996)
#define icon
#define mystyle  *_*_*_* 


//inceputul codului
#include<conio.h>
#include <comdef.h>
#include <stdlib.h>
#include <stdio.h>
#include "Resource.h"
#include "stdafx.h"
#include "Win32Project1.h"
#include <commdlg.h>
#include <windows.h>
#include<time.h>
#include<fstream>
#include<cstring>
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
//////////////Functii de masurare tim de executie algoritm
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
   QueryPerformanceFrequency(&li);
	

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

//
//
//    StartCounter();   functie de start
//    
//    GetCounter();    functie de returneaza timpul trecut de la start
//    
//

//////////////////////////


 int memorie[6],increment=0;
char szFileName[MAX_PATH] = "";
void desenare(HDC hdc);
char mesaj[100];
int nod_dest,nr_noduri;
int nod1,nod2,cap,legaturi[500][3],poz=0;
float mem_timp[10];
int cont_timp=1;
int mem_flux[10],mem_noduri[10];
int j=0;	
int id1=0,id2=0,contor_pozitii=0;
HWND graf_nod[200];
void Paint(HWND hwnd);

clock_t begin,end;
int time_spent;
float tmp;
int contor_noduri=1;
struct poz_buton{

int up_x;
int start_x;
int up_y;
int start_y;
int id;
};
poz_buton vector_poz[500];

struct muchie
{		
	int buton1;		
	int buton2;		
	int capacitate;		
};		
muchie muchii_coordonate[500];

enum EMode
{
	eDisplayBar,
	eDisplayBUTTON,
	eDisplayPixels,
	out
};

bool verificare_vecini_nod[750][750];
void reinitializare_matrice();

// Global variable for current mode
EMode gMode=out;
void DisplayBar(HDC hdc);
void DisplayText(HDC hdc);
HWND  hWnd;

HWND Grafic[10];
typedef struct celula
{
	int nod;
	celula *next;
}*lista;
lista graf[1001],v,q,aux; // graful memorat  ca vectori de liste si variabile auxiliare
int cost[1001][1001],tata[1001],n,mm,flow; //m=nr de muchii   n= valoarea nodului tinta
bool ok,viz[1001]; //variabile  in care se tine minte daca a fost parcurs sau nu un anumit nod
 // functie cu rol de a updata valoarea fluxului


//#include "definitions.h"
#define BUTTON_ID      1001
#define MAX_LOADSTRING 100
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;	
RECT		drawrect,wndrect;
HDC			hDC;
int verificare_nod(int nod);
char matr_adiacenta[1000][1000],nr_matr=0;
void creare_graf_mod_grafic();
void validare_graf_func(HWND hdlg);
int verificare_input(int input,HWND hWnd);
int verificare_input_nod(int input,HWND hWnd);
void demo(HWND hdlg);
BOOL CALLBACK nrnoduri(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam);
BOOL CALLBACK delatastatura(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam);
BOOL CALLBACK muchii(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam);
BOOL CALLBACK capacitate_muchie(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam)		
{		
int bState;		
		static int ok_cancel=TRUE; //stabileste dacă s-a închis cu OK sau		
	//Cancel		
	switch (message)		
	{		
		case WM_DESTROY:		
			EndDialog(hdlg,ok_cancel);		
		return TRUE;		
			case WM_COMMAND:		
			switch (LOWORD(wParam))		
				{		
				case IDOK: //S-a apăsat OK		
				//Functie care citeste un întreg dintr-o casetă	de text		
					muchii_coordonate[contor_pozitii].capacitate=(int)GetDlgItemInt(hdlg,IDC_EDIT1,&bState,true);		
					ok_cancel=TRUE;		
					//Functia care duce la încheierea dialogului		
					EndDialog(hdlg, true);		
			break;		
			
				}		
			return TRUE;		
			}		
	return FALSE;		
	}		
void Paint_Grafic(HWND hwnd);
void prand_noduri(HWND hWnd)
{
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_NRNODURI), hWnd,(DLGPROC)nrnoduri, NULL);
}
void pmuchii(HWND hWnd)
{
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_ADAUGAREMUCHIE), hWnd,(DLGPROC)muchii, NULL);
}
void pCREARETASTATURA(HWND hWnd)
{
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDCREARETASTATURA), hWnd,(DLGPROC)delatastatura, NULL);
}
void pcapacitate_muchie(HWND hWnd)		
{		
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd,(DLGPROC)capacitate_muchie, NULL);		
}
///////////////////////////////////////////////functiile pentru flux
void update(){
     int nod=n,min=100000;
     while (tata[nod]!=-1){
           if (cost[tata[nod]][nod]<min) 
			   min=cost[tata[nod]][nod];
           nod=tata[nod];
           }
     nod=n; flow+=min;
     while (tata[nod]!=-1){
           cost[tata[nod]][nod]-=min;
           cost[nod][tata[nod]]+=min;
           nod=tata[nod];
           }
}
 //parcurgearea grafului 
void bfs()
{
     v=(celula*)malloc(sizeof(celula));
	 v->nod=1;
	 v->next=0; 
	 q=v; 
	 tata[1]=-1; 
	 ok=0;
     memset(viz,0,sizeof(viz)); 
	 viz[1]=1;
     while (v!=0) {
           for (lista p=graf[v->nod];p; p=p->next)
		   {
               if (viz[p->nod]==0&&cost[v->nod][p->nod]>0) 
			   {
				   if (p->nod!=n) 
					 {
						  aux=(celula*)malloc(sizeof(celula)); 
						  aux->nod=p->nod; 
						  q->next=aux; 
						  q=aux; 
						  q->next=0;
				     } 
					 tata[p->nod]=v->nod;
					 viz[p->nod]=1;
			   }
                if (viz[n]==1)
				{
					ok=1; 
				    update(); 
				    viz[n]=0; 
				}
           }
      v=v->next;
     }
}
          int verificare=0;
//functie cu citirea din fisier
void Edmonds_Karp(HWND hdlg)
{
  
	
	HDC hdc;
	OPENFILENAME fon;
	hdc=GetDC(hdlg);
	ZeroMemory(&fon,sizeof(fon));
	fon.lStructSize = sizeof(fon);
	fon.hwndOwner = hdlg;
	fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	fon.lpstrFile =szFileName;
	fon.nMaxFile = MAX_PATH;
	fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	fon.lpstrDefExt =TEXT("txt");
	if(GetOpenFileName(&fon)){
	
	FILE*in=fopen(szFileName,"r+");
	


	//begin=clock();

	StartCounter();
	int ii,x,c,y; fscanf(in,"%d%d",&n,&mm);

	for (ii=1; ii<=mm; ++ii) 
	{
		fscanf(in,"%d%d%d",&x,&y,&c); cost[x][y]=c;
		v=(celula*)malloc(sizeof(celula));
		v->nod=y;
		v->next=graf[x]; 
		graf[x]=v;
		v=(celula*)malloc(sizeof(celula));
		v->nod=x;
		v->next=graf[y];
		graf[y]=v;
	}
		ok=1;
		while (ok==1) 
			bfs();
		tmp=GetCounter();
		 char msg[30];   
		 sprintf(msg," fluxul maxim este %d  \n",flow);
		 MessageBox(hdlg,msg,"Success",MB_OK);
		verificare=1;
		 fclose(in);}
}

/////////////
//functie de crearea aleatoare a matrici de vecini impreuna cu capacitatile lor
void rand_list(HWND hdlg)
{
	int bState;
	int nr_noduri1=(int)GetDlgItemInt(hdlg,IDC_EDIT2,&bState,true);
	if (nr_noduri1>401)
	{MessageBox(hWnd," Valoare introdusa este pre mare ! \n Va rugam sa introduce-ti o valoare intre 1<=>400!","Atentie!",MB_OK | MB_ICONERROR); goto fin;}
	else{
	
	int rand_cap[401][401];
	HDC hdc;
	OPENFILENAME fon;
	hdc=GetDC(hdlg);
	ZeroMemory(&fon,sizeof(fon));
	fon.lStructSize = sizeof(fon);
	fon.hwndOwner = hdlg;
	fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	fon.lpstrFile =szFileName;
	fon.nMaxFile = MAX_PATH;
	fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	fon.lpstrDefExt =TEXT("txt");
	if(GetOpenFileName(&fon))
	{
	 FILE*in=fopen(szFileName,"w");
	fprintf(in," ");
	
	

	
	
	 int nr_muchii=0;
	 for(int q=1;q<=nr_noduri1;q++)
		for(int q1=1;q1<=nr_noduri1;q1++)
			if(q1>q)
			{
				rand_cap[q][q1]=rand()%30;nr_muchii++;}
			else 
				rand_cap[q][q1]=0;
		
			fprintf(in,"%d %d \n ",nr_noduri1,nr_muchii);
		    for(int q=1;q<=nr_noduri1;q++)
			   for(int q1=1;q1<=nr_noduri1;q1++)
	               if(q1>q)   
					 fprintf(in,"%d %d %d \n",q,q1,rand_cap[q][q1]);
	fclose(in);
	}
	fin:;
    }
	
}
//functie creare graf de la tastatura
void creare_de_la_tast(HWND hdlg)
{
	int bState;
	
	nod1= (int)GetDlgItemInt(hdlg,IDC_EDIT1,&bState,true);
	if(verificare_input_nod(nod1,hdlg))
		nod1=0;
	nod2= (int)GetDlgItemInt(hdlg,IDC_EDIT2,&bState,true);
	if(verificare_input_nod(nod2,hdlg))
		nod2=0;
	 cap=(int)GetDlgItemInt(hdlg,IDC_EDIT3,&bState,true);
	 if (cap<0)
		{ MessageBox(hWnd," Capacitatea introdusa este pre mica ! \n Va rugam sa introduce-ti o valoare mai mare decat 0!","Atentie!",MB_OK | MB_ICONERROR);
	 cap=0;
	 }
	///scanf("%d %d %d",&nod1,&nod2,&cap);
	//fprintf(in," %d %d %d \n",nod1,nod2,cap);
	//printf("doresti sa mai adaugi legaturi?\n 1->NU 0->DA");
	legaturi[poz][0]=nod1;
	legaturi[poz][1]=nod2;
	legaturi[poz][2]=cap;
}
void scriere_doc(HWND hdlg)
{
	HDC hdc;
	OPENFILENAME fon;
	hdc=GetDC(hdlg);
	ZeroMemory(&fon,sizeof(fon));
	fon.lStructSize = sizeof(fon);
	fon.hwndOwner = hdlg;
	fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	fon.lpstrFile =szFileName;
	fon.nMaxFile = MAX_PATH;
	fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	fon.lpstrDefExt =TEXT("txt");
	if(GetOpenFileName(&fon))
	{
	FILE*f=fopen(szFileName,"r+");
	fprintf(f,"%d %d \n",nod_dest,nr_noduri);
	for (int ii=0;ii<poz;ii++)
		fprintf(f,"%d %d %d\n",legaturi[ii][0],legaturi[ii][1],legaturi[ii][2]);
	fclose(f);
	}
	
	}

void reinitializare(char*fisier,HWND hdlg)
{
	HDC hdc;
	OPENFILENAME fon;
	hdc=GetDC(hdlg);
	ZeroMemory(&fon,sizeof(fon));
	fon.lStructSize = sizeof(fon);
	fon.hwndOwner = hdlg;
	fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	fon.lpstrFile =szFileName;
	fon.nMaxFile = MAX_PATH;
	fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	fon.lpstrDefExt =TEXT("txt");
	if(GetOpenFileName(&fon))
	{
	FILE*f=fopen(szFileName,"w");
	fprintf(f," ");
	fclose(f);
	}

nod_dest=NULL,nr_noduri=NULL;
nod1=NULL,nod2=NULL,cap=NULL,poz=0;

 graf[1001]=NULL,v=NULL,q=NULL,aux=NULL; // graful memorat  ca vectori de liste si variabile auxiliare
tata[1001]=NULL,n=NULL,mm=NULL,flow=NULL; //m=nr de muchii   n= valoarea nodului tinta
 ok=NULL;
  time_spent=0;
 tmp=0;
 /////////////
 for(int q=1;q<=cont_timp;q++)
			DestroyWindow(Grafic[q]);
 
legaturi[MAX_PATH][3]=NULL;
mem_timp[6]=NULL;
 cont_timp=1;

}
// sfarsitul codului
//Procedurile de fereastră a casetelor de dialog


BOOL CALLBACK nrnoduri(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam)
{
	//int bState;
	static int ok_cancel=TRUE; //stabileste dacă s-a închis cu OK sau
	//Cancel
	switch (message)
	{
		case WM_DESTROY:
			EndDialog(hdlg,ok_cancel);
		return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam))
		{
			case IDOK: //S-a apăsat OK
		//Functie care citeste un întreg dintr-o casetă	de text
				rand_list(hdlg);
				ok_cancel=TRUE;
				//Functia care duce la încheierea dialogulu
				EndDialog(hdlg, true);
			break;
			case IDCANCEL: //S-a apăsat Cancel
				ok_cancel=FALSE;
				EndDialog(hdlg, false);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK muchii(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam)
{
	//int bState;
	static int ok_cancel=TRUE; //stabileste dacă s-a închis cu OK sau
	//Cancel
	switch (message)
	{
		case WM_DESTROY:
			EndDialog(hdlg,ok_cancel);
		return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{

				case IDC_BUTTON1:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_HELPADAUGAREMUCHII), hWnd, About); 
					break;
				case IDOK: //S-a apăsat OK
					//Functie care citeste un întreg dintr-o casetă	de text
					creare_de_la_tast(hdlg);
					ok_cancel=TRUE;
					//Functia care duce la încheierea dialogului
					EndDialog(hdlg, true);
				break;
				case IDCANCEL: //S-a apăsat Cancel
					ok_cancel=FALSE;
					EndDialog(hdlg, false);
				break;
			}
			return TRUE;
		}
	return FALSE;
}

BOOL CALLBACK delatastatura(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam)
{
	int bState;
	static int ok_cancel=TRUE; //stabileste dacă s-a închis cu OK sau
	//Cancel
	switch (message)
	{
		case WM_DESTROY:
			EndDialog(hdlg,ok_cancel);
		return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_BUTTON1:
				pmuchii(hdlg);
		
				   poz++;

				break;
				case IDC_BUTTON2:
					nod_dest=(int)GetDlgItemInt(hdlg,IDC_EDIT2,&bState,true);
					if (verificare_input(nod_dest,hWnd))
						nod_dest=0;
				break;
				case IDC_BUTTON3:
					 nr_noduri=(int)GetDlgItemInt(hdlg,IDC_EDIT3,&bState,true);
					 if(verificare_input(nr_noduri,hWnd))
						   nr_noduri=0;


				break;

				//case IDC_BUTTON1:
					//DialogBox(hInst, MAKEINTRESOURCE(IDD_HELPADAUGAREMUCHII), hWnd, About); 
				//	break;
				case IDOK: //S-a apăsat OK
					//Functie care citeste un întreg dintr-o casetă de text
					//creare_de_la_tast();
					scriere_doc(hdlg);
					ok_cancel=TRUE;
					//Functia care duce la încheierea dialogului
					EndDialog(hdlg, true);
				break;
				case IDCANCEL: //S-a apăsat Cancel
					ok_cancel=FALSE;
					EndDialog(hdlg, false);
				break;
			}
			return TRUE;
		}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//sfarsit proceduri

// Global Variables:
							// current instance

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int nCmdShow)
{
	// TODO: Place code here.
	MSG msg={};

	// Initialize global strings
//	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	 const wchar_t CLASS_NAME[]  = L"Sample Window Class"; //crearea unei clase in clasa windows
	WNDCLASS wc = { };
	wc.style			= CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc		= WndProc;
	wc.hInstance		= hInstance;
	wc.lpszClassName	= szWindowClass;
	wc.hIcon			= LoadIcon(NULL,IDI_SHIELD);// imi incarca un bmp in stanga sus ca iconita
	wc.hCursor			= LoadCursor(NULL, IDC_HAND);
	wc.hbrBackground	=( HBRUSH)(COLOR_WINDOW+2);
	wc.lpszMenuName = NULL;
	RegisterClass(&wc);
	hInst = hInstance; // Store instance handle in our global variable
	hWnd = CreateWindowEx(0,						// Optional window styles.
						szWindowClass,					  // Window class. clasa din care face parte fereastra
						"Edmonds-Karp Alghorithm",		 // Window text// textul pe care l vreau afisat in taskbar
						WS_OVERLAPPEDWINDOW|CS_BYTEALIGNWINDOW|WS_BORDER,			 // Window style
						 // Size and position
						  0, 0,1350, 720, // primele doua sunt x, y din stanga sus...iar urmatoareale latimea si inaltimea
						 NULL,// Parent window  
						  NULL, // Menu
						  hInstance,// Instance handle
						  NULL); // Additional application data
	// Test if the window was created successfully
	if (hWnd==NULL)
   {
	   MessageBox(NULL, TEXT("Window could not be opened!"),szWindowClass, MB_ICONERROR);
      return 0;
   }

   ShowWindow(hWnd, SW_MAXIMIZE);
   UpdateWindow(hWnd);

   hDC = GetDC(hWnd);
   Paint(hWnd);
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)>0)
	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}
	return 0;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//////////////////////////////////////////////////////////////////////////

void timp_edmonds_carp(HWND hWnd)
{  
	flow=0;
	if(cont_timp<7)
	{
	Edmonds_Karp(hWnd);
	//MessageBox(hWnd,"1","check",MB_OK);
	if (verificare){
	char timp[1000];

	//tmp=end-begin;
	mem_flux[cont_timp]=flow;
	mem_timp[cont_timp]=tmp;
	mem_noduri[cont_timp]=n;
		if (verificare){
	cont_timp++;
	sprintf(timp,"%f ",tmp);
	MessageBox(hWnd,timp,"TIMP",MB_OK);
	verificare=0;
		}
	
	}
	
	}
	else
		MessageBox(hWnd,"Ati depasit numarul maxim de 6 comparatii\nApasati reinitializare","Warning",MB_OK);
	//sprintf(timp,"%s",time_spent);
	//MessageBox(hWnd,"3","check",MB_OK);
	//	MessageBox(hWnd,timp,"Timp",MB_OK);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int f,g;
	int id_buton;
	//RECT  rect = { 110,110, 200, 200};
	int wmId=0, wmEvent=0;
	HWND hButton1=NULL,hButton2=NULL,hButton3=NULL,hButton4=NULL,hButton5=NULL,hButton6=NULL,hButton7=NULL,hButton9=NULL,hButton10=NULL;
	HDC hdc=NULL;
	PAINTSTRUCT ps;
	
	HBRUSH      brLogBrush;
	 LOGBRUSH    LogBrush;
	OPENFILENAME fon;
	static POINT p1;
	static POINT p2;
	switch (message)
	{
		//functie pentru desenarea pe suprafata de lucru a diferitelor elemente de grafica
		case WM_LBUTTONDOWN:
				
		p1.x=LOWORD(lParam);
		p1.y=HIWORD(lParam);
		
		 id_buton=contor_noduri+500;
		
		
		
		char a[10];		
		sprintf(a,"%d",contor_noduri);
		if (p1.x<690 && p1.x>10 && p1.y>240 && p1.y<650 && verificare_vecini_nod[p1.x][p1.y]==0)
				{
			graf_nod[contor_noduri]= CreateWindowEx( NULL,"button", a ,
				WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
				p1.x,p1.y, 
				20,20,
				hWnd,(HMENU) id_buton,
				hInst, NULL );
			
			verificare_vecini_nod[p1.x][p1.y]=1;
			//f=p1.x-20;
			//g=p1.y-20;
			for(f=p1.x-40;f<p1.x+40;f++)
				for(g=p1.y-40;g<p1.y+40;g++)
					verificare_vecini_nod[f][g]=1;
			vector_poz[contor_noduri].up_x=p1.x;
		vector_poz[contor_noduri].up_y=p1.y;
		vector_poz[contor_noduri].start_x=p1.x+20;
		vector_poz[contor_noduri].start_y=p1.y+10;
		vector_poz[contor_noduri].id=contor_noduri+500;
		contor_noduri++;
		hdc=GetDC(hWnd); //Obtinerea contextului grafic
	//	Ellipse(hdc,p2.x-8,p2.y-8,p2.x+8,p2.y+8);
	//	MoveToEx(hdc,p2.x,p2.y,NULL);
	//	LineTo(hdc,p1.x,p1.y);
		
		//p2=p1;
		ReleaseDC(hWnd,hdc); }//Eliberarea contextului grafic
		return 0;
		
	
		case WM_CREATE:
			GetClientRect(hWnd,&wndrect);	
			hButton2 = CreateWindowEx( NULL,"button", "Random",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
						wndrect.left+10 , wndrect.top+130, 
						130, 25,
						hWnd, (HMENU) 14,
						hInst, NULL );
			 hButton1 = CreateWindowEx( NULL,"BUTTON", "Start",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON  ,
						wndrect.left+10,wndrect.top+ 10, 
						130, 25,
						hWnd, (HMENU) 1,
						hInst, NULL );

			 hButton3 = CreateWindowEx(NULL, "button", "Creare",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
						wndrect.left+10, wndrect.top+40, 
						130, 25,
						hWnd, (HMENU) 8,
						hInst, NULL );

			 hButton4 = CreateWindowEx(NULL, "button", "Reinitializare",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
						wndrect.left+10, wndrect.top+70, 
						130, 25,
						hWnd, (HMENU) 9,
						hInst, NULL );
	
			hButton5 = CreateWindowEx(NULL, "button", "Info!",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
						wndrect.left+10, wndrect.top+100, 
						130, 25,
						hWnd, (HMENU) 5,
						hInst, NULL );

			hButton6 = CreateWindowEx( NULL,"button", "Grafic",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
						wndrect.left+10, wndrect.top+160, 
						130, 25,
						hWnd, (HMENU) 25,
						hInst, NULL );

			hButton7 = CreateWindowEx( NULL,"button", "Exit",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
						wndrect.left+10, wndrect.top+190, 
						130, 25,
						hWnd, (HMENU) 6,
						hInst, NULL );
			hButton6 = CreateWindowEx( NULL,"button", "Validare Graf",		
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,		
							wndrect.left+10, wndrect.top+680,		
						130, 25,		
						hWnd, (HMENU) 20,		
						hInst, NULL );
			hButton9 = CreateWindowEx( NULL,"button", "Reinitializare Suprafata",		
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,		
							wndrect.left+250, wndrect.top+680,		
						160, 25,		
						hWnd, (HMENU) 44,		
						hInst, NULL );
			hButton10 = CreateWindowEx( NULL,"button", "Demonstratie",		
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,		
							wndrect.left+700, wndrect.top+680,		
						130, 25,		
						hWnd, (HMENU) 10,		
						hInst, NULL );
			hButton10 = CreateWindowEx( NULL,"button", "?",		
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,		
							wndrect.left+140,wndrect.top+ 10,		
						20, 25,		
						hWnd, (HMENU) 11,		
						hInst, NULL );
			hButton10 = CreateWindowEx( NULL,"button", "?",		
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,		
							wndrect.left+140, wndrect.top+40,		
						20, 25,		
						hWnd, (HMENU) 12,		
						hInst, NULL );

			hButton10 = CreateWindowEx( NULL,"button", "?",		
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,		
							wndrect.left+140, wndrect.top+70,		
						20, 25,		
						hWnd, (HMENU) 13,		
						hInst, NULL );

			hButton10 = CreateWindowEx( NULL,"button", "?",		
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,		
							wndrect.left+140, wndrect.top+130,		
						20, 25,		
						hWnd, (HMENU) 15,		
						hInst, NULL );

		break;
			case WM_COMMAND:
				wmId    = LOWORD(wParam);
				wmEvent = HIWORD(wParam);
			if (id1==0)		
				id1=wmId;		
			else id2=wmId;		
				if (id1 && id2 && verificare_nod(id1) && verificare_nod(id2))		
				{		
				muchii_coordonate[contor_pozitii].buton1=id1;		
				    muchii_coordonate[contor_pozitii].buton2=id2;		
				pcapacitate_muchie(hWnd);		
					contor_pozitii++;		
		
					}		
				if(verificare_nod(id1)==0)
					id1=0;
				if(verificare_nod(id2)==0)
					id2=0;
		
					
			if (id1 && id2 && verificare_nod(id1) && verificare_nod(id2)){		
				id1=0;id2=0;			
				InvalidateRect(hWnd,NULL,TRUE);		
				}
			switch (wmId)
			{
			case 44:
				reinitializare_matrice();
				break;

		     	case 15:
					    DialogBox(hInst, MAKEINTRESOURCE(IDD_RANDOM), hWnd, About); 
				break;
				case 20:	

					validare_graf_func(hWnd);
				break;
				
				case 10:
					  demo(hWnd);
					break;
				
				case 14:
					prand_noduri(hWnd);   //functie ce creaza random nodurile si legaturile dintre ele intr-un graf orientat
				break;
				case 1:
					timp_edmonds_carp(hWnd);
				break;
				case 9:
					reinitializare(szFileName,hWnd);
				break;
				case 8:
					pCREARETASTATURA(hWnd);//functie folosita la crearea arborelui de la tastatura
				break;
				case 5:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About); 
					
				break;
				case 6:
					PostQuitMessage(0);
				break;
				case 25:
					gMode=eDisplayBUTTON;
				break;

				case 11:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_HELPSTART), hWnd, About); 
					break;

					case 12:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_HELPCREARE), hWnd, About); 
					break;

					case 13:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_HELPREINITIALIZARE), hWnd, About); 
					break;

				case 201:
					
					sprintf(mesaj," Numarul de noduri este %d .\nFluxul maxim din graf este de %d.\n Timpul de executie al algoritmului este de %f \n",mem_noduri[1],mem_flux[1],mem_timp[1]);
					MessageBox(hWnd,mesaj,"Informatii !",MB_OK);

					break;
					case 202:
					//char mesaj[100];
					sprintf(mesaj," Numarul de noduri este %d .\nFluxul maxim din graf este de %d.\n Timpul de executie al algoritmului este de %f \n",mem_noduri[2],mem_flux[2],mem_timp[2]);
					MessageBox(hWnd,mesaj,"Informatii !",MB_OK);

					break;
					case 203:
					//char mesaj[100];
					sprintf(mesaj," Numarul de noduri este %d .\nFluxul maxim din graf este de %d.\n Timpul de executie al algoritmului este de %f \n",mem_noduri[3],mem_flux[3],mem_timp[3]);
					MessageBox(hWnd,mesaj,"Informatii !",MB_OK);

					break;
					case 204:
					//char mesaj[100];
					sprintf(mesaj," Numarul de noduri este %d .\nFluxul maxim din graf este de %d.\n Timpul de executie al algoritmului este de %f \n",mem_noduri[4],mem_flux[4],mem_timp[4]);
					MessageBox(hWnd,mesaj,"Informatii !",MB_OK);

					break;
					case 205:
					//char mesaj[100];
					sprintf(mesaj," Numarul de noduri este %d .\nFluxul maxim din graf este de %d.\n Timpul de executie al algoritmului este de %f \n",mem_noduri[5],mem_flux[5],mem_timp[5]);
					MessageBox(hWnd,mesaj,"Informatii !",MB_OK);

					break;
					case 206:
					//char mesaj[100];
					sprintf(mesaj," Numarul de noduri este %d .\nFluxul maxim din graf este de %d.\n Timpul de executie al algoritmului este de %f \n",mem_noduri[6],mem_flux[6],mem_timp[6]);
					MessageBox(hWnd,mesaj,"Informatii !",MB_OK);

					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			// Force a redraw when a key is pressed
		case WM_KEYDOWN:
			gMode=eDisplayBUTTON;
			
			 desenare(hdc);
			InvalidateRect(hWnd,NULL,TRUE);
		break;
					
		case WM_PAINT:
				hdc=BeginPaint(hWnd,&ps);
			//	GetClientRect(hWnd,&rect);
				///////////////////////////////////////////////////cadran I
				LogBrush.lbStyle = BS_PATTERN;
				LogBrush.lbColor = RGB(255, 0, 255);
				LogBrush.lbHatch = HS_DIAGCROSS;
				brLogBrush = CreateBrushIndirect(&LogBrush);
			    SelectObject(hdc, brLogBrush);
				Rectangle(hdc, 0, 0, 150,230);
				////////////////////////////////////////////////cadran II
				LogBrush.lbStyle = BS_HATCHED;
				LogBrush.lbColor = RGB(220,220,220);
				LogBrush.lbHatch =	HS_HORIZONTAL;
				brLogBrush = CreateBrushIndirect(&LogBrush);
			    SelectObject(hdc, brLogBrush);
				Rectangle(hdc, 150, 0, 700,230);
				//////////////////////////////////////////////////////cadran III
				LogBrush.lbStyle = BS_HATCHED;
				LogBrush.lbColor = RGB(220,220,220);
				LogBrush.lbHatch =	HS_CROSS;
				brLogBrush = CreateBrushIndirect(&LogBrush);
			    SelectObject(hdc, brLogBrush);
				Rectangle(hdc, 700, 0, 1370,750);
				
				////////////////////////////////////////////////////
				LogBrush.lbStyle = BS_HATCHED;
				LogBrush.lbColor = RGB(255, 0, 255);
				LogBrush.lbHatch = HS_CROSS;
				brLogBrush = CreateBrushIndirect(&LogBrush);
				 SelectObject(hdc, brLogBrush);
				Rectangle(hdc, 0, 0, 180,230);
				////////////////////////////////////////////////////////
				DeleteObject(brLogBrush);
				desenare(hdc);
				creare_graf_mod_grafic();
				EndPaint(hWnd,&ps);
		//////////////////pentru desenare
				break;
		case WM_ACTIVATE:
			Paint(hWnd);
		break;
		case WM_DESTROY:
				PostQuitMessage(0);
			break;
		default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
	}
	return (INT_PTR)FALSE;
}
void Paint(HWND hwnd)
{
	HDC hdc=GetDC(hwnd);
	DisplayText(hDC);
	RECT wndrect;
	GetClientRect(hwnd,&wndrect);
	drawrect.bottom = wndrect.bottom ;
	drawrect.left	= wndrect.left + 700;
	drawrect.right	= wndrect.right;
	drawrect.top	= wndrect.top ;
	FrameRect(hDC,&drawrect,CreateSolidBrush(0xffffff));
	drawrect.bottom = wndrect.bottom - 1;
	drawrect.left	= wndrect.left + 699;
	drawrect.right	= wndrect.right -1;
	drawrect.top	= wndrect.top +1;
	FrameRect(hDC,&drawrect,CreateSolidBrush(0xffffff));
	drawrect.bottom = 230;
	drawrect.left	= NULL;
	drawrect.right	= wndrect.left + 700;
	drawrect.top	= NULL;
	FrameRect(hDC,&drawrect,CreateSolidBrush(0xffffff));
	drawrect.bottom = 231;
	drawrect.left	= NULL;
	drawrect.right	= wndrect.left + 700;
	drawrect.top	= NULL;
	FrameRect(hDC,&drawrect,CreateSolidBrush(0xffffff));
}

void Paint_Grafic(HWND hwnd)
{
	char nume[10];
	//calculare coeficient inmultire
	float coeficient=0;
	float timp_maxim=0;
	for(int yy=0;yy<=cont_timp;yy++)
		if(timp_maxim<mem_timp[yy])
			timp_maxim=mem_timp[yy];
	coeficient=400/(timp_maxim*100)*100*1.6;
	for(int q=1;q<=cont_timp;q++)
			DestroyWindow(Grafic[q]);
	for(int kkk=1;kkk<cont_timp;kkk++)
	{	sprintf(nume,"Test %d",kkk);
		Grafic[kkk]= CreateWindowEx( NULL,"button", nume ,
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
						701,(kkk-1)*100+5,//701,(kkk-1)*100+5, 
						100,100,//mem_timp[kkk]*coeficient,100,
						hwnd,(HMENU)kkk+50,
				    	hInst, NULL );
	}
	
	
}
void desenare(HDC hdc)
{	
	 DisplayText(hDC);
	switch(gMode)
	{
	case eDisplayBUTTON:
		{
		Paint_Grafic(hWnd);
		gMode=eDisplayBar;}
		
	case eDisplayBar:
		DisplayBar(hdc);
		//creare_graf_mod_grafic();}
		break;
	default: return;
	}
	

}
void DisplayBar(HDC hdc)
{
	int colour;
	float coeficient=0;
	float timp_maxim=0;
	for(int yy=0;yy<=cont_timp;yy++)
		if(timp_maxim<mem_timp[yy])
			timp_maxim=mem_timp[yy];
	coeficient=400/(timp_maxim*100)*100*1.6;
	int jj,jjj,yyy;
	jjj=5;
	yyy=jjj+100;
	for(int kkk=1;kkk<cont_timp;kkk++)
	{
		colour=RGB(rand()%255,rand()%255,rand()%255);
		for( jj=801;jj<mem_timp[kkk]*coeficient+701;jj++)
		{
					for( jjj;jjj<yyy;jjj++)
					{
						Sleep(0.2);
						SetPixel(hdc, jj, jjj, colour);
					}
					jjj=yyy-100;
		}
		yyy=yyy+100;
	}

}

void DisplayText(HDC hdc)
{
	char buf[2048];

	int x=190;
	int y=10;

	int len=sprintf(buf," Edmonds-Karp Test Software ");
	TextOut(hdc,x,y,buf,len);

	y+=50;
	len=sprintf(buf,"Aceasta aplicatie a fost dezvoltata ");
	TextOut(hdc,x,y,buf,len);

	y+=20;
	len=sprintf(buf,"cu scopul testari algoritmului Edmonds-Karp !");
	TextOut(hdc,x,y,buf,len);

	y+=20;
	len=sprintf(buf,"In cazul in care intampinati probleme, folositi Help-ul aplicatiei!");
	TextOut(hdc,x,y,buf,len);

//	SetTextColor(hdc,RGB(rand()%255,rand()%255,rand()%255));

	y+=20;
	len=sprintf(buf,"");
	TextOut(hdc,x,y,buf,len);

	//SetTextColor(hdc,RGB(0,0,255));

	y+=20;
	len=sprintf(buf,"");
	TextOut(hdc,x,y,buf,len);

//	SetTextColor(hdc,RGB(0,0,0));

	y+=20;
	len=sprintf(buf,"");
	TextOut(hdc,x,y,buf,len);
	
	
}
void creare_graf_mod_grafic()		
	{		
	PAINTSTRUCT ps;		
	HDC hdc;HPEN pen;		
				  hdc=GetDC(hWnd);		
			  pen = CreatePen(PS_SOLID,2,RGB(0,0,255));		
				  SelectObject(hdc,pen);		
				for (int j=0;j<contor_pozitii;j++)		
				{		int x_text,y_text,len; 
						char capacitate[10];

					MoveToEx( hdc,  vector_poz[muchii_coordonate[j].buton1-500].start_x,vector_poz[muchii_coordonate[j].buton1-500].start_y, NULL);		
						LineTo( hdc, vector_poz[muchii_coordonate[j].buton2-500].start_x, vector_poz[muchii_coordonate[j].buton2-500].start_y);		
			
						x_text=((vector_poz[muchii_coordonate[j].buton2-500].start_x-vector_poz[muchii_coordonate[j].buton1-500].start_x)/2)+vector_poz[muchii_coordonate[j].buton1-500].start_x;
						y_text=((vector_poz[muchii_coordonate[j].buton2-500].start_y-vector_poz[muchii_coordonate[j].buton1-500].start_y)/2)+vector_poz[muchii_coordonate[j].buton1-500].start_y-10;
						len=sprintf(capacitate,"%d",muchii_coordonate[j].capacitate);
						TextOut(hdc,x_text,y_text,capacitate,strlen(capacitate));
		}		

}
int verificare_nod(int nod)		
	{		
			
		for(int j=0;j<=contor_noduri;j++)		
			if (nod==vector_poz[j].id)		
				return 1;		
		 return 0;		
			
		
	}		
		
void validare_graf_func(HWND hdlg)		
	{		
		HDC hdc;		
	OPENFILENAME fon;		
		hdc=GetDC(hdlg);		
		ZeroMemory(&fon,sizeof(fon));		
		fon.lStructSize = sizeof(fon);		
		fon.hwndOwner = hdlg;		
		fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");		
		fon.lpstrFile =szFileName;		
		fon.nMaxFile = MAX_PATH;		
		fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;		
		fon.lpstrDefExt =TEXT("txt");		
		if(GetOpenFileName(&fon))		
		{		
			
				FILE*g=fopen(szFileName,"w");		
		fprintf(g," ");		
		fclose(g);		
			
		FILE*f=fopen(szFileName,"a");		
		fprintf(f,"%d %d\n",contor_noduri-1,contor_pozitii);		
			
		for (int j=0;j<contor_pozitii;j++)		
			fprintf(f,"%d %d %d \n",muchii_coordonate[j].buton1-500,muchii_coordonate[j].buton2-500,muchii_coordonate[j].capacitate);		
			
			
			
		fclose(f);		
		}		
			
}
void reinitializare_matrice()
{
	int alpha,beta;
	for(alpha=10;alpha<700;alpha++)
		for(beta=240;beta<700;beta++)
			verificare_vecini_nod[alpha][beta]=0;

	for (int j4=1;j4<contor_noduri;j4++)
	    DestroyWindow(graf_nod[j4]);

	contor_noduri=1;
	InvalidateRect(hWnd,NULL,TRUE);	
	contor_pozitii=0;

}

int next_nod_valid(int nod){
	int ok=0;
	for (int j=0;j<increment;j++)
		if (nod==memorie[j])
			ok=1;

	return ok;


}

void Edmonds_Karp2()
{
  
	
	
	
	FILE*in=fopen(szFileName,"r+");
	


	//begin=clock();

	StartCounter();
	int ii,x,c,y; fscanf(in,"%d%d",&n,&mm);

	for (ii=1; ii<=mm; ++ii) 
	{
		fscanf(in,"%d%d%d",&x,&y,&c); cost[x][y]=c;
		v=(celula*)malloc(sizeof(celula));
		v->nod=y;
		v->next=graf[x]; 
		graf[x]=v;
		v=(celula*)malloc(sizeof(celula));
		v->nod=x;
		v->next=graf[y];
		graf[y]=v;
	}
		ok=1;
		while (ok==1) 
			bfs();
		tmp=GetCounter();
		// char msg[30];   
		 //sprintf(msg," fluxul maxim este %d  \n",flow);
		// MessageBox(hdlg,msg,"Success",MB_OK);
		verificare=1;
		 fclose(in);
}

void timp_edmonds_carp2(HWND hWnd)
{  
	flow=0;
	if(cont_timp<7)
	{
	Edmonds_Karp2();
	//MessageBox(hWnd,"1","check",MB_OK);
	if (verificare){
	char timp[1000];

	//tmp=end-begin;
	mem_flux[cont_timp]=flow;
	mem_timp[cont_timp]=tmp;
	mem_noduri[cont_timp]=n;
		if (verificare){
	cont_timp++;
	//sprintf(timp,"%f ",tmp);
	//MessageBox(hWnd,timp,"TIMP",MB_OK);
	verificare=0;
		}
	
	}
	
	}
	else
		MessageBox(hWnd,"Ati depasit numarul maxim de 6 comparatii\nApasati reinitializare","Warning",MB_OK);
	//sprintf(timp,"%s",time_spent);
	//MessageBox(hWnd,"3","check",MB_OK);
	//	MessageBox(hWnd,timp,"Timp",MB_OK);
}

void demo(HWND hdlg)
{
   
	int rand_cap[401][401];
	HDC hdc;
	OPENFILENAME fon;
	hdc=GetDC(hdlg);
	ZeroMemory(&fon,sizeof(fon));
	fon.lStructSize = sizeof(fon);
	fon.hwndOwner = hdlg;
	fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	fon.lpstrFile =szFileName;
	fon.nMaxFile = MAX_PATH;
	fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	fon.lpstrDefExt =TEXT("txt");
	if(GetOpenFileName(&fon))
	{
	 
	
	for (int j=0;j<6;j++){
		FILE*in=fopen(szFileName,"w");
	fprintf(in," ");
	int nr_noduri1=rand()%401;
	

	while(nr_noduri1<11 && next_nod_valid(nr_noduri1))
	              nr_noduri1=rand()%401;

	memorie[increment]=nr_noduri;
	increment++;

	
	
	 int nr_muchii=0;
	 for(int q=1;q<=nr_noduri1;q++)
		for(int q1=1;q1<=nr_noduri1;q1++)
			if(q1>q)
			{
				rand_cap[q][q1]=rand()%30;nr_muchii++;}
			else 
				rand_cap[q][q1]=0;
		
			fprintf(in,"%d %d \n ",nr_noduri1,nr_muchii);
		    for(int q=1;q<=nr_noduri1;q++)
			   for(int q1=1;q1<=nr_noduri1;q1++)
	               if(q1>q)   
					   fprintf(in,"%d %d %d \n",q,q1,rand_cap[q][q1]);
	
	fclose(in);
	timp_edmonds_carp2(hWnd);
	}
	
    }
}

int verificare_input(int input,HWND hWnd)
{

	if (input>400 || input <0)
	{MessageBox(hWnd," Valoare introdusa nu este corecta ! \n Va rugam sa introduce-ti o valoare intre 0<=>400!","Atentie!",MB_OK | MB_ICONERROR);return 1;}

	return 0;
}

int verificare_input_nod(int input,HWND hWnd)
{

	if (input>400 || input <2)
	{MessageBox(hWnd," Valoare introdusa nu este corecta ! \n Va rugam sa introduce-ti o valoare intre 2<=>400!","Atentie!",MB_OK | MB_ICONERROR);return 1;}

	return 0;
}



