#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC)DlgProc);
}

HWND radio[30];

HWND hAnswer1, hAnswer2, hAnswer3;
TCHAR Answer1[25], Answer2[25], Answer3[25];

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	TCHAR str[100];
	const double questions = 13;
	static int right_answers = 0;
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case  WM_INITDIALOG:
		for (int i = 0; i < 30; i++)
		{
			radio[i] = GetDlgItem(hWnd, IDC_RADIO1+i);
		}

		hAnswer1 = GetDlgItem(hWnd, IDC_EDIT3);
		hAnswer2 = GetDlgItem(hWnd, IDC_EDIT5);
		hAnswer3 = GetDlgItem(hWnd, IDC_EDIT4);
		return TRUE;

	case WM_COMMAND:

		if (LOWORD(wp) == IDOK)
		{
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

			
			double result = (right_answers / questions) * 100;

			_stprintf_s(str, TEXT("Вы набрали - %.2f/100"), result);
			MessageBox(hWnd, str, TEXT("Результаты"), MB_OK | MB_ICONINFORMATION);
			right_answers = 0;

			
		}
		return TRUE;
	}
	return FALSE;
}