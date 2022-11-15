#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <commctrl.h>
#include "resource.h"

#pragma comment(lib,"comctl32")

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC)DlgProc);
}

HWND radio[30];

HWND hAnswer1, hAnswer2, hAnswer3;
TCHAR Answer1[25], Answer2[25], Answer3[25];

HWND hTemp;

HWND hEdit16, hEdit17;
HWND hScroll16, hScroll17;

HWND hProgress;

HWND hTime;

BOOL FLAG = TRUE;

HANDLE hThread;

DWORD WINAPI Thread(LPVOID lp)
{
	int minutes = 0;
	int seconds = 5;
	TCHAR tchar[5];
	while (seconds != 0 || minutes != 0)
	{
		if (seconds == 0) {
			seconds = 59;
			minutes--;
		}
		wsprintf(tchar, TEXT("%d:%d"), minutes, seconds);
		SetWindowText(hTime, tchar);
		Sleep(1000);
		seconds--;
	}
	FLAG = FALSE;
	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	TCHAR str[100];
	const double questions = 15;
	static int right_answers = 0;

	if (FLAG == FALSE) {
		FLAG = TRUE;
		unsigned int result = MessageBox(hWnd, TEXT("Время вышло"), TEXT("Викторина экстренно закрывается!"), MB_OK | MB_ICONERROR);
		
		if (result == IDOK) {
			PostQuitMessage(0);
			return TRUE;
		}
	}

	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case  WM_INITDIALOG: {
		// Загрузим меню из ресурсов приложения
		HMENU hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
		// Присоединим меню к главному окну приложения
		SetMenu(hWnd, hMenu);
		for (int i = 0; i < 30; i++)
		{
			radio[i] = GetDlgItem(hWnd, IDC_RADIO1 + i);
		}

		hAnswer1 = GetDlgItem(hWnd, IDC_EDIT3);
		hAnswer2 = GetDlgItem(hWnd, IDC_EDIT5);
		hAnswer3 = GetDlgItem(hWnd, IDC_EDIT4);
		hScroll16 = GetDlgItem(hWnd, IDC_SPIN16);
		hScroll17 = GetDlgItem(hWnd, IDC_SPIN17);
		hEdit16 = GetDlgItem(hWnd, IDC_EDIT16);
		hEdit17 = GetDlgItem(hWnd, IDC_EDIT17);
		hProgress = GetDlgItem(hWnd, IDC_PROGRESS1);
		hTime = GetDlgItem(hWnd, IDC_EDIT1);
		SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, questions)); // Установка интервала для индикатора 
		SendMessage(hProgress, PBM_SETSTEP, 5, 0); // Установка шага приращения  индикатора 
		SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(0, 0, 0))); // Установка цвета заполняемых прямоугольников


		SendMessage(hScroll16, UDM_SETRANGE32, 0, 100);
		SendMessage(hScroll17, UDM_SETRANGE32, 2000, 3000);
		UDACCEL pAcceleration[3] = { {1,1}, {5,5}, {10,10} };
		SendMessage(hScroll16, UDM_SETACCEL, 3, LPARAM(pAcceleration));
		SendMessage(hScroll17, UDM_SETACCEL, 3, LPARAM(pAcceleration));
		SendMessage(hScroll16, UDM_SETBUDDY, WPARAM(hEdit16), 0);
		SendMessage(hScroll17, UDM_SETBUDDY, WPARAM(hEdit17), 0);
		SetWindowText(hEdit16, TEXT("0"));
		SetWindowText(hEdit17, TEXT("2022"));
		hThread = CreateThread(NULL, 0, Thread, hTime, 0, NULL);
		

		return TRUE;

	}

	

	case WM_COMMAND:

		if (LOWORD(wp) == ID_MENU_EXIT) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			
		}
		

		if (LOWORD(wp) == IDOK)
		{
			SuspendThread(hThread);
			LRESULT lResult = SendMessage(radio[0], BM_GETCHECK, 0, 0);
			LRESULT RResult;
			LRESULT MResult;

			if (lResult == BST_CHECKED) right_answers++;
			lResult = SendMessage(radio[3], BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED) right_answers++;
			lResult = SendMessage(radio[7], BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED) right_answers++;
			lResult = SendMessage(radio[9], BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED) right_answers++;
			lResult = SendMessage(radio[13], BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED) right_answers++;
			lResult = SendMessage(radio[17], BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED) right_answers++;
			lResult = SendMessage(radio[20], BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED) right_answers++;

			lResult = SendMessage(radio[21], BM_GETCHECK, 0, 0);
			MResult = SendMessage(radio[22], BM_GETCHECK, 0, 0);
			RResult = SendMessage(radio[23], BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED && RResult == BST_CHECKED && MResult != BST_CHECKED) right_answers++;

			lResult = SendMessage(radio[24], BM_GETCHECK, 0, 0);
			MResult = SendMessage(radio[25], BM_GETCHECK, 0, 0);
			RResult = SendMessage(radio[26], BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED && RResult == BST_CHECKED && MResult != BST_CHECKED) right_answers++;


			lResult = SendMessage(radio[27], BM_GETCHECK, 0, 0);
			MResult = SendMessage(radio[28], BM_GETCHECK, 0, 0);
			RResult = SendMessage(radio[29], BM_GETCHECK, 0, 0);
			if (lResult == BST_CHECKED && MResult == BST_CHECKED && RResult != BST_CHECKED) right_answers++;

			GetWindowText(hAnswer1, Answer1, 25);
			GetWindowText(hAnswer2, Answer2, 25);
			GetWindowText(hAnswer3, Answer3, 25);
		
			if (!lstrcmpi(Answer1, _T("Hello!"))) {
				right_answers++;
			}

			if (!lstrcmpi(Answer2, _T("goto"))) {
				right_answers++;
			}

			if (!lstrcmpi(Answer3, _T("switch"))) {
				right_answers++;
			}

			if (SendMessage(hScroll16, UDM_GETPOS32, 0, 0) == 20) {
				right_answers++;
			}
			if (SendMessage(hScroll17, UDM_GETPOS32, 0, 0) == 2038) {
				right_answers++;
			}
			double result = (right_answers / questions) * 100;

			_stprintf_s(str, TEXT("Вы набрали - %.2f/100"), result);
			SendMessage(hProgress, PBM_SETPOS, right_answers, 15); // Установка текущей позиции индикатора
			MessageBox(hWnd, str, TEXT("Результаты"), MB_OK | MB_ICONINFORMATION);
			right_answers = 0;


			TerminateThread(hThread,0);
			hThread = CreateThread(NULL, 0, Thread, hTime, 0, NULL);
			
			
		}
		return TRUE;
	}
	return FALSE;
}