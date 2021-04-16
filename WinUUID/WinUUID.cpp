// WinUUID.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WinUUID.h"
#include <winsock.h>
#include "atlbase.h"
#include "atlstr.h"
#include "gdiplus.h"   

#pragma comment(lib,"gdiplus.lib")

#define _WIN32_WINNT 0x5000 //定义WINNT的宏 

using namespace Gdiplus;

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void OutputDebugPrintf(const char* strOutputString, ...)
{
    char strBuffer[4096] = { 0 };
    va_list vlArgs;
    va_start(vlArgs, strOutputString);
    _vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);
    //vsprintf(strBuffer, strOutputString, vlArgs);
    va_end(vlArgs);
    OutputDebugString(CA2W(strBuffer));
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINUUID, szWindowClass, MAX_LOADSTRING);


 
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINUUID));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW ;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINUUID));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    // wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.hbrBackground = CreateSolidBrush(RGB(251, 255, 242));
    // wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINUUID);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   /*HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }*/

   // ShowWindow(hWnd, nCmdShow);
   // UpdateWindow(hWnd);


   HWND hwnd = CreateWindow(szWindowClass, TEXT("Noble Qiao~"),
                WS_POPUP | WS_SYSMENU | WS_VISIBLE,
               ::GetSystemMetrics(SM_CXSCREEN) - 260,
               0,
              260, 70,
             NULL, NULL, hInstance, NULL);

   if (!hwnd) {
       return FALSE;
   }
      
   ::SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
   SetLayeredWindowAttributes(hwnd, 0, (255 * 70) / 150, LWA_ALPHA);


   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
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
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
        

            TCHAR greeting[] = _T("安院移动互联专业 NB");

            // 获取计算机名称
            CString strName = _T("");
            DWORD nSize = MAX_COMPUTERNAME_LENGTH + 1;
            ::GetComputerName(strName.GetBuffer(nSize), &nSize);
            strName.ReleaseBuffer();

            // OutputDebugPrintf("\nHello：%s\n", strName);

            
            // 设置字体颜色
            SetTextColor(hdc, RGB(255, 0, 0));
            // 绘制版权信息
            TextOut(hdc, 10, 45, greeting, _tcslen(greeting));

            // 设置字体
            LOGFONT logfont; //改变输出字体 
            ZeroMemory(&logfont, sizeof(LOGFONT));
            // logfont.lfCharSet = GB2312_CHARSET; 
            logfont.lfHeight = -34; //设置字体的大小
            HFONT hFont = CreateFontIndirect(&logfont);
            SelectObject(hdc, hFont);


            // 设置字体颜色
            SetTextColor(hdc, RGB(255, 0, 0));
            // 设置透明背景
            SetBkMode(hdc, TRANSPARENT);
            // 绘制文本
            TextOut(hdc, 10, 5, strName, _tcslen(strName));


            // DeleteObject(hdc);
           

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


// “关于”框的消息处理程序。
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
