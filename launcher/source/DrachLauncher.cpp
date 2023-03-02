// DrachLauncher.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "DrachLauncher.h"

#include <strsafe.h>
#include <lmcons.h>
#include <string>

#include <thread>
#include <iostream>
#include <chrono>

#ifdef _DEBUG
#define ENGINE_DLL L"\\engine\\Engine_Debug.dll"
#define EDITOR_DLL L"\\editor\\Editor_Debug.dll"
#endif
#include <cassert>
#ifdef _RELEASE
#define ENGINE_DLL L"\\engine\\Engine_Release.dll"
#define EDITOR_DLL L"\\editor\\Editor_Release.dll"
#endif


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int, HWND&);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
	LoadStringW(hInstance, IDC_DRACHLAUNCHER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	MSG msg;
	{
		bool running = true;

		EngineInterface* engineAPI = nullptr;
		EngineAPI fetchEngineAPI;
		EditorAPI fetchEditorAPI;
		HINSTANCE hDLL;

		wchar_t buffer[500];
		GetCurrentDirectory(500, buffer);

		std::wstring workingPath = std::wstring(buffer);

		std::wstring enginePath(workingPath + ENGINE_DLL);
		hDLL = /*LoadLibrary(ENGINE_DLL)*/ LoadLibrary(enginePath.c_str());
		auto error = GetLastError();

		assert(hDLL != NULL && "Could not find Engine_[Version].dll");
		fetchEngineAPI = (EngineAPI)GetProcAddress(hDLL, "ExportInterface");
		assert(fetchEngineAPI != NULL && "Could not find ExportInterface method");
		engineAPI = fetchEngineAPI();


		std::wstring editorPath(workingPath + EDITOR_DLL);
		hDLL = LoadLibrary(editorPath.c_str());
		fetchEditorAPI = (EditorAPI)GetProcAddress(hDLL, "ExportInterface");


		// Start
		// Perform application initialization:
		HWND winIns;
		if (!InitInstance(hInstance, nCmdShow, winIns))
		{
			return FALSE;
		}
		StartContext data = { winIns };

		RECT clientRect;
		GetClientRect(winIns, &clientRect);

		data.myWindowWidth = clientRect.right - clientRect.left;
		data.myWindowHeight = clientRect.bottom - clientRect.top;



		if (engineAPI)
			running = engineAPI->OnStart(data, fetchEditorAPI ? fetchEditorAPI() : nullptr);

		SetWindowLongPtr(winIns, GWLP_USERDATA, (LONG_PTR)(engineAPI));

		HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRACHLAUNCHER));



		// Update
		// Main message loop:

		auto currentTime = std::chrono::high_resolution_clock::now();
		auto prevTime = currentTime;
		std::chrono::duration<float> deltaTime;

		while (running)
		{
			currentTime = std::chrono::high_resolution_clock::now();
			if (engineAPI)
			{
				RuntimeContext context{ deltaTime.count() };
				running = engineAPI->OnUpdate(context);
			}


			if (!running)break;

			deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - prevTime);
			prevTime = currentTime;


			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (msg.message == WM_QUIT)
				running = false;

		}
	}


	//if (engineAPI)
	//	delete engineAPI;
	//engineAPI = nullptr;
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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRACHLAUNCHER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DRACHLAUNCHER);
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND& anOutput)
{
	hInst = hInstance; // Store instance handle in our global variable

	anOutput = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!anOutput)
	{
		return FALSE;
	}

	ShowWindow(anOutput, nCmdShow);
	UpdateWindow(anOutput);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	EngineInterface* interface = (EngineInterface*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (interface)
	{
		interface->OnWinProc(hWnd, message, wParam, lParam);
	}
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
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
