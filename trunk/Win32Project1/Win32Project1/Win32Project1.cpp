﻿// Win32Project1.cpp : Defines the entry point for the application.
//
#define _CRT_SECURE_NO_DEPRECATE
//inceputul codului
#include<conio.h>
#include <comdef.h>
#include <stdlib.h>
#include <stdio.h>
#include "resource.h"
#include "stdafx.h"
#include "Win32Project1.h"
#include <commdlg.h>
#include <windows.h>
//#include "definitions.h"

INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;	
char matr_adiacenta[1000][1000],nr_matr=0;


struct graph
{
 int nod;

 graph *next;

};

graph *v;
int nr_noduri=6;

#include<string.h>



//BOOL CALLBACK WndBINARDialogProc(HWND hdlg, UINT message, WPARAM wParam,
//LPARAM lParam)
//{
//int bState;
//static int ok_cancel=TRUE; //stabileste dacă s-a închis cu OK sau
////Cancel
//switch (message)
//{
//case WM_DESTROY:
//EndDialog(hdlg,ok_cancel);
//return TRUE;
//case WM_COMMAND:
//switch (LOWORD(wParam))
//{
//case IDOK: //S-a apăsat OK
////Functie care citeste un întreg dintr-o casetă
////de text
//T1 =(int)GetDlgItemInt(hdlg,IDC_T1,&bState,true);
//if(T1>255) T1=255;
//if(T1<0) T1=0;
//T2 =(int)GetDlgItemInt(hdlg,IDC_T2,&bState,true);
//if(T2>255) T2=255;
//if(T2<0) T2=0;
//ok_cancel=TRUE;
////Functia care duce la încheierea dialogului
//EndDialog(hdlg, true);
//break;
//case IDCANCEL: //S-a apăsat Cancel
//ok_cancel=FALSE;
//EndDialog(hdlg, false);
//break;
//}
//return TRUE;
//}
//return FALSE;
//}
BOOL CALLBACK WndBINARDialogProc(HWND hdlg, UINT message, WPARAM wParam,
LPARAM lParam);

void citire_nr_noduri(HWND hWnd)
	
{
	int nr;
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd,
(DLGPROC)WndBINARDialogProc, NULL);
	

}

void generare_rand_matr(char*szFileName,HWND hWnd)
{
		FILE*f=fopen(szFileName,"r+");
		citire_nr_noduri(hWnd);
     for (int ii=0;ii<nr_noduri;ii++)
		  for (int j=0;j<nr_noduri;j++)
			  { matr_adiacenta[ii][j]=rand()%2;
	 
	   // printf("%d   ",matr_adiacenta[i][j]);
	 
	 }

	 fprintf(f,"%d\n",nr_noduri);

	 
     for (int ii=0;ii<nr_noduri;ii++)
	 {   
		 
		 fprintf(f,"%d ",rand()%99); 
		 
		 for (int j=0;j<nr_noduri;j++)
			  {fprintf(f,"%d ",matr_adiacenta[ii][j]);
		// printf("%d ",matr_adiacenta[i][j]);
		 }
		 fprintf(f,"\n");

	 }


 fclose(f);
 MessageBox(hWnd,"SUccess","Success",MB_OK);
}



void creare_matrice(char *szFileName,HWND hWnd)
{
	char nume[1][50];
    // strcpy(nume[1],szFileName);
	FILE*f;
		f=fopen(szFileName,"r");

	fscanf(f,"%d",&nr_matr);
	int nod=0,ok;
	v=(graph*)malloc(nr_matr*sizeof(graph));
	while(!feof(f))
	{   int val_nod;
	   fscanf(f,"%d",&v[nod].nod);
		v[nod].next=NULL;
		graph *aux=v[nod].next;
	for(int ii=0;ii<nr_matr;ii++)
	{
		  fscanf(f,"%d",&val_nod);
		  if(val_nod==1){

		  if (v[nod].next==NULL)
		  {
				v[nod].next=(graph*)malloc(sizeof(graph));
				v[nod].next->nod=ii;
				aux=v[nod].next;
				aux->next=NULL;
		  
		  }
		  else{
		  
		  aux->next=(graph*)malloc(sizeof(graph));
		  aux=aux->next;
		  aux->nod=ii;
		  aux->next=NULL;	  
		  
		  }
		  }
	}

	nod++;


  }
	nr_noduri=nod;
	fclose(f);
	MessageBox(hWnd,"SUccess","Success",MB_OK);
}



void afisare()
{
	for(int ii=0;ii<nr_noduri;ii++)
	{
				//printf("nodul %d are vecinii -> ",v[ii].nod);

				graph *aux=v[ii].next;
				while(aux)
				{
						//printf("%d ",aux->nod);
						aux=aux->next;			
				
				}
	//    printf("\n");
	
	}





}


void matrice_adiacenta()
{
			
	for (int ii=0;ii<nr_noduri;ii++)
	{
			
		for(int j=0;j<nr_noduri;j++)
		{
			graph *aux=v[ii].next;
			int ok=0;
			while(aux)
			{
					if (aux->nod==j)
					{  // printf("%d ",1);
					     ok=1;
						break;
					}
				aux=aux->next;	
	 	}

			//if (ok==0)
				//printf("%d ",0);
			


		}

		//printf("\n");

	}


}

// sfarsitul codului 





//Procedura de fereastră a casetei de dialog
BOOL CALLBACK WndBINARDialogProc(HWND hdlg, UINT message, WPARAM wParam,
LPARAM lParam)
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
//Functie care citeste un întreg dintr-o casetă
//de text

	nr_noduri=(int)GetDlgItemInt(hdlg,IDC_EDIT4,&bState,true);



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











#define MAX_LOADSTRING 100

// Global Variables:
							// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, "Edmonds-Karp", CS_BYTEALIGNWINDOW|CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
#define BUTTON_ID      1001



//void functie()
//{char szFileName[MAX_PATH];
//	HWND hwnd;
//GetModuleFileName(hInstance, szFileName, MAX_PATH);
//MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
//
//}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


	////////////////////////////////

	//declaratii nu toate iti trebuie
int wmId, wmEvent,ii=0;
	PAINTSTRUCT ps;
	

//////////////////////////////



	
	//PAINTSTRUCT ps;
	char szFileName[MAX_PATH] = "";
	HPEN bluePen; 
	HGDIOBJ oldPen;
	HFONT font;
	//HDC hdc;
	static HWND hButton;
				HDC hdc,hdc2;
	LPCSTR Y;
	HICON hicon, hicon_sm;
	HWND d1=NULL, d2=NULL, d3=NULL;
   // HDC hDC;
	OPENFILENAME fon;

	switch (message)
	{
		case WM_CREATE:
      
       hButton = CreateWindow( "button", "?",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                980, 450, 
                20, 20,
                hWnd, (HMENU) BUTTON_ID,
                hInst, NULL );

	   hButton = CreateWindow( "button", "Start",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                940, 10, 
                70, 20,
                hWnd, (HMENU) 1,
                hInst, NULL );

	    hButton = CreateWindow( "button", "Crearea din fisier",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                870, 40, 
                130, 20,
                hWnd, (HMENU) 2,
                hInst, NULL );

		 hButton = CreateWindow( "button", "Crearea Random",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                730, 40, 
                130, 20,
                hWnd, (HMENU) 7,
                hInst, NULL );
		
		hButton = CreateWindow( "button", "Stergere",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                940, 70, 
                70, 20,
                hWnd, (HMENU) 3,
                hInst, NULL );

		hButton = CreateWindow( "button", "Atrib/Modif",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                940, 100, 
                70, 20,
                hWnd, (HMENU) 4,
                hInst, NULL );

		hButton = CreateWindow( "button", "Help!",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                940, 130, 
                70, 20,
                hWnd, (HMENU) 5,
                hInst, NULL );

		hButton = CreateWindow( "button", "Exit",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                940, 160, 
                70, 20,
                hWnd, (HMENU) 6,
                hInst, NULL );

      break;


	  hdc=GetDC(hWnd);
// funcţii de desenare
ReleaseDC(hWnd,hdc);

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDOK:
			int nr;
			
			
			
			break;


		case 7:
			 if (szFileName)
			 {
				char szFileName[MAX_PATH] = "";
			 
			 }
			hdc=GetDC(hWnd);
							ZeroMemory(&fon,sizeof(fon));
							fon.lStructSize = sizeof(fon);
							fon.hwndOwner = hWnd;
							fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
							fon.lpstrFile =szFileName;
							fon.nMaxFile = MAX_PATH;
							fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
							fon.lpstrDefExt =TEXT("txt");
							GetOpenFileName(&fon);


			generare_rand_matr(szFileName,hWnd);
			creare_matrice(szFileName,hWnd);
			break;


		case 2:
			////////////////


	               if (szFileName)
					   char szFileName[MAX_PATH] = "";
	//
							hdc=GetDC(hWnd);
							ZeroMemory(&fon,sizeof(fon));
							fon.lStructSize = sizeof(fon);
							fon.hwndOwner = hWnd;
							fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
							fon.lpstrFile =szFileName;
							
	          
					
							fon.nMaxFile = MAX_PATH;
							fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
							fon.lpstrDefExt =TEXT("txt");
							GetOpenFileName(&fon);
													



			////////////////
			creare_matrice(szFileName,hWnd);
			char cuvant[100];
			sprintf(cuvant,"%s %d","ana are mere",4);
			MessageBox(hWnd,cuvant,"Success",MB_OK);
			break;

		case 5:
			
			
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			
			
			break;
		case 6:
			DestroyWindow(hWnd);
			break;
		case BUTTON_ID:

			


			
			
			//MessageBox(0,cuvant_out(),"INFORMATII",0);//functie pentru buton
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		////////////////////
		EndPaint(hWnd, &ps);
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
