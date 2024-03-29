// 1612041_MidTerm_FlagTest.cpp : Defines the entry point for the application.
//


#include "stdafx.h"
#include <gdiplus.h>
#pragma comment (lib, "gdiplus")
using namespace Gdiplus;
#include "1612041_MidTerm_FlagTest.h"
#include <windowsx.h>
#include <time.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <cwchar>



#define MAX_LOADSTRING 100
#define BUFFER_SIZE 255

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


												//khai bao cac du lieu
WCHAR DiaChiHinhAnh[10][BUFFER_SIZE];
WCHAR DapAn[15][BUFFER_SIZE];    // Dap an dung chi tu 1 den 10 ung voi 10 tam hinh, 5 dap an phu
int ThuTu[10];	//Phat sinh ngau nhien tu 1 den 10 de random cau hoi
int TraiPhai[10];	 //Phat sinh ngau nhien dap an dung nam ben trai hoac phai

int score;
int currentQ;

HWND Question;
HWND btn1;
HWND btn2;
HDC hdc;



// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnDestroy(HWND hwnd);
void OnPaint(HWND hwnd);
void createRandom();
void createData();
void phanPhoiCauHoiTraiPhai();



//ham sinh so ngau nhien tu min den max-1
int Random(int min, int max)
{	return rand() % (max - min) + min;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY1612041MIDTERMFLAGTEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1612041MIDTERMFLAGTEST));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MY1612041MIDTERMFLAGTEST));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY1612041MIDTERMFLAGTEST);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
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
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		200, 200, 600, 500, nullptr, nullptr, hInstance, nullptr);

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
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
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


BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	//Lay font cua hdh
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	srand(time(NULL));	//De moi lan chay srand 1 lan thoi
	createData();
	createRandom();

	WCHAR temp[BUFFER_SIZE];
	wsprintf(temp, L"Question %d:  Which flag is this?", currentQ + 1);

	Question = CreateWindowEx(NULL, L"STATIC", temp, WS_CHILD | WS_VISIBLE, 220, 40, 250, 40, hwnd,
	NULL, lpCreateStruct->hInstance, NULL);
	SetWindowFont(Question, hFont, true);


	btn1 = CreateWindowEx(NULL, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 350, 150, 50,
	hwnd, (HMENU)IDC_BTNCHOOSE1, lpCreateStruct->hInstance, NULL);
	SetWindowFont(btn1, hFont, true);

	btn2 = CreateWindowEx(NULL, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 350, 350, 150, 50,
	hwnd, (HMENU)IDC_BTNCHOOSE2, lpCreateStruct->hInstance, NULL);
	SetWindowFont(btn2, hFont, true);


	phanPhoiCauHoiTraiPhai();


	return TRUE;
}



void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	WCHAR temp[BUFFER_SIZE];
	switch (id)
	{
	case IDC_BTNCHOOSE1:
		GetWindowText(btn1, temp, BUFFER_SIZE);
		if ((wcscmp(temp, DapAn[ThuTu[currentQ]]) == 0))	//tuc chon dung
		{
			score += 10;
		}
		
		if (currentQ == 9)  //Da la cau hoi cuoi cung
		{
			wsprintf(temp, L"Diem so cua ban la %d", score);
			MessageBox(0, temp, L"Tro choi ket thuc!", 0);
			DestroyWindow(hwnd);
			return;
		};

		currentQ++;
		phanPhoiCauHoiTraiPhai();
		wsprintf(temp, L"Question %d:  Which flag is this?", currentQ + 1);
		SetWindowText(Question, temp);
		//Uu tien goi ham VM_PAINT
		InvalidateRect(hwnd, NULL, false);
		UpdateWindow(hwnd);
		break;
	case IDC_BTNCHOOSE2:
		GetWindowText(btn2, temp, BUFFER_SIZE);
		if ((wcscmp(temp, DapAn[ThuTu[currentQ]]) == 0))	//tuc chon dung
		{
			score += 10;
		}
		if (currentQ == 9)  //Da la cau hoi cuoi cung
		{
			wsprintf(temp, L"Diem so cua ban la %d", score);
			MessageBox(0, temp, L"Tro choi ket thuc!", 0);
			DestroyWindow(hwnd);
			return;
		};

		currentQ++;
		phanPhoiCauHoiTraiPhai();
		wsprintf(temp, L"Question %d:  Which flag is this?", currentQ + 1);
		SetWindowText(Question, temp);
		//Uu tien goi ham VM_PAINT
		InvalidateRect(hwnd, NULL, false);
		UpdateWindow(hwnd);
		break;
	}
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
	DestroyWindow(hwnd);
	return;
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	ULONG_PTR gdiplusToken;
	hdc = BeginPaint(hwnd, &ps);

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	{

		Graphics graphics(hdc);
		Image image = (DiaChiHinhAnh[ThuTu[currentQ]]);
		graphics.DrawImage(&image, 150, 80);

	}

	GdiplusShutdown(gdiplusToken);

	EndPaint(hwnd, &ps);
}




void createRandom()
{
	for (int i = 0; i<10; i++)
	{
		ThuTu[i] = Random(0, 10);
		for (int j = 0; j<i; j++)
		{

			if (ThuTu[i] == ThuTu[j]) //Hinh nay da duoc xuat hien
			{
				i--;   // Thi random lai
				break;
			}
		}
	}

	for (int i = 0; i<10; i++)
	{
		TraiPhai[i] = Random(0, 2);
	}
}

void createData()    
{
	score = 0;
	currentQ = 0;
	WCHAR path[BUFFER_SIZE];
	GetCurrentDirectory(BUFFER_SIZE, path);
	for (int i = 0; i < 10; i++)
	{
		wsprintf(DiaChiHinhAnh[i], L"%s\\hinh\\%d.png", path, i + 1);
		//wsprintf(DiaChiHinhAnh[i], L"D:\\hinh\\%d.png", i + 1);
	}
	

	wsprintf(DapAn[0], L"Germany");
	wsprintf(DapAn[1], L"France");
	wsprintf(DapAn[2], L"Argentina");
	wsprintf(DapAn[3], L"Uruguay");
	wsprintf(DapAn[4], L"Italia");
	wsprintf(DapAn[5], L"Japan");
	wsprintf(DapAn[6], L"Brazil");
	wsprintf(DapAn[7], L"Canada");
	wsprintf(DapAn[8], L"Croatia");
	wsprintf(DapAn[9], L"Portugal");
	wsprintf(DapAn[10], L"Thailand");
	wsprintf(DapAn[11], L"Russia");
	wsprintf(DapAn[12], L"Korea");
	wsprintf(DapAn[13], L"VietNam");
	wsprintf(DapAn[14], L"China");


}


void phanPhoiCauHoiTraiPhai()
{	
	int temp;
	if (TraiPhai[currentQ] == 0)
	{
		SetWindowText(btn1, DapAn[ThuTu[currentQ]]);
		do
		{
			temp = Random(0, 15);
			SetWindowText(btn2, DapAn[temp]);
		} while (temp == ThuTu[currentQ]);
	}
	else
	{
		SetWindowText(btn2, DapAn[ThuTu[currentQ]]);
		do
		{
			temp = Random(0, 15);
			SetWindowText(btn1, DapAn[temp]);
		} while (temp == ThuTu[currentQ]);
	}
}