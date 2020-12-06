
#include <windows.h>
#include <windowsx.h>
#include "Data.h"
#include "Scene2D.h"
#include "Model2D.h"
#include "EllyipticCoordinates.h"
#include "ParametricFuntion.h"
#include"Utils.h"


EllipticFunction *ellyptic = new EllipticFunction(5);


LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// �������� ������� ���������
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// �������� ���������
{
	// ������ ������������ ����� �������� ��������� - �������� ����: ������� ����������� ������� ����� wc, ����� �������� ���� hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// ��� ������� ���������, ������������ �� ������ �������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// ������������� ����������, ���������� ����� ������ ���������� ��� ������� ������
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// ���� � ������� ������ �����������
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// ��� �������� ������, ������������ ��� �������� ����������� ����
	RegisterClass(&wc);								// ����������� ������ wc
	
	ellyptic->setFunctions(parametricSpiralX, parametricSpiralY);
	ellyptic->setBorders(0, 12*M_PI);

	HWND hWnd = CreateWindow(						// hWnd - ����������, ���������������� ����; ������� �������� ���� ��������� ���������� hWnd ��������� ���������
		(LPCSTR)"MainWindowClass",					// ��� �������� ������
		(LPCSTR)"Plot2D Viewer",					// ��������� ����
		WS_OVERLAPPEDWINDOW,						// ����� ����
		200,200,400,400,							// ���������� �� ������ ������ �������� ���� ����, ��� ������ � ������
		nullptr,nullptr,hInstance,nullptr);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������������ ����� �������� ��������� - �������� ���� ��������� ��������� ���������, ������� ������� ��������� � ��������� �� ��������������� �����
	MSG msg;
	while(GetMessage(&msg,nullptr,0,0))				// ������� GetMessage �������� �� ������� ��������� � ������� ��� � ��������� msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// ������� DispatchMessage ��������� ������� � ������������� ������ ������� ���������
	}

	return 0;
}

// � �������� ������ ����������� ������ ���� ���������� ���������� - �������� ������ ������ Scene2D
// ��� ���������� �������� �������������� ����������� ��������� � �������, ������������� � ���� ������

Scene2D scene(L,R,B,T);
Model2D model;

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// ������� ��������� ��������� � ������������ ��� ���������, ������������ ����
{
	switch(msg)
	{
	case WM_PAINT:
		{
			HDC dc = GetDC(hWnd);
			scene.Clear(dc);// ����� �������������� � ������ Camera2D ������, ����������� �� ������� ������� ������� ���� hWnd
			SetBkColor(dc, 0x00FFFFFF);
			//scene.Plot(dc, ellyptic);		// ����� �������������� � ������ Scene2D ������, ����������� �� ��������� ������� ���������
			scene.renderModel(dc, model);
			ReleaseDC(hWnd,dc);
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT:
		{
			scene.Move(-2, 0);
			break;
		}
		//A
		case 0x41:
		{
			double x = model.getPrismCenterX();
			double y = model.getPrismCenterY();
			model.apply(RotationCenter(2, x, y));
			model.apply();
			break;
		}
		//D
		case 0x44:
		{
			double x = model.getPrismCenterX();
			double y = model.getPrismCenterY();
			model.apply(RotationCenter(-2, x, y));
			model.apply();
			break;
		}
		//B
		case 0x42:
			model.apply(Translation(1,1));
			model.apply();
			break;
		//C
		case 0x43: {
			double *abc = findABC(
				model.getVertices().getCell(0, 0), model.getVertices().getCell(1, 0),
				model.getVertices().getCell(0, 2), model.getVertices().getCell(1, 2)
			);
			model.apply(MappingLine(abc[0], abc[1], abc[2]));
			model.apply();
			break;
		}
		//E
		case 0x45:
			model.apply(Scaling(0.9,1.5));
			model.apply();
			break;
		//G
		case 0x47:
			model.apply(Scaling(1.2, 0.6));
			model.apply();
			break;
		//F
		case 0x46:
			model.apply(Mapping0());
			model.apply();
			break;
		case VK_RIGHT:
		{
			scene.Move(2, 0);
			break;
		}
		case VK_UP:
		{
			scene.Move(0, -2);
			break;
		}
		case VK_DOWN:
		{
			scene.Move(0, 2);
			break;
		}
		}
		InvalidateRect(hWnd, NULL, FALSE);	// ����� ��������� WM_PAINT
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		//HDC dc = GetDC(hWnd);
		double dz = GET_WHEEL_DELTA_WPARAM(wParam);
		POINT P;
		//GetCursorPos(&P);
		P.x = GET_X_LPARAM(lParam);
		P.y = GET_Y_LPARAM(lParam);
		ScreenToClient(hWnd, &P);
		scene.zoom(dz, P.x, P.y);
		//ReleaseDC(hWnd, dc);
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		scene.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		if (scene.IsDragging())
		{
			scene.Drag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			InvalidateRect(hWnd, nullptr, false);
		}
		return 0;
	}
	case WM_LBUTTONUP:
	{
		scene.StopDragging();
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	}
	case WM_SIZE:
		{
			HDC dc = GetDC(hWnd);
			scene.SetResolution(dc);
			ReleaseDC(hWnd,dc);
			InvalidateRect(hWnd,nullptr,false);
			return 0;
		}

	case WM_CREATE: 
		{
		ifstream f_edg("input_edg.txt");
		ifstream f_vert("input_vert.txt");
		if(model.getEdgesFromFile(f_edg)
			&&
			model.getVerticesFromFile(f_vert)
		   )
			return 0;
		throw exception("Cant read files");
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

	default:
		{
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
	}
	return 0;
}
