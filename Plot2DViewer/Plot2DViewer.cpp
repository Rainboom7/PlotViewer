#include <windows.h>
#include <windowsx.h>
#include "Data.h"
#include "Scene3D.h"
#include "Model2D.h"
#include "EllyipticCoordinates.h"
#include "ParametricFuntion.h"
#include"Utils.h"
#include"Coordinates.h"


//EllipticFunction *ellyptic = new EllipticFunction(5);


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

	//ellyptic->setFunctions(parametricSpiralX, parametricSpiralY);
	//ellyptic->setBorders(0, 12 * M_PI);

	HWND hWnd = CreateWindow(						// hWnd - ����������, ���������������� ����; ������� �������� ���� ��������� ���������� hWnd ��������� ���������
		(LPCSTR)"MainWindowClass",					// ��� �������� ������
		(LPCSTR)"Plot2D Viewer",					// ��������� ����
		WS_OVERLAPPEDWINDOW,						// ����� ����
		200, 200, 400, 400,							// ���������� �� ������ ������ �������� ���� ����, ��� ������ � ������
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������������ ����� �������� ��������� - �������� ���� ��������� ��������� ���������, ������� ������� ��������� � ��������� �� ��������������� �����
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))				// ������� GetMessage �������� �� ������� ��������� � ������� ��� � ��������� msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// ������� DispatchMessage ��������� ������� � ������������� ������ ������� ���������
	}

	return 0;
}

Scene3D scene(L, R, B, T);
Model3D model("faces.txt","vertices.txt");
//Model2D model;

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// ������� ��������� ��������� � ������������ ��� ���������, ������������ ����
{
	switch (msg)
	{
	case WM_PAINT:
	{
		HDC dc = GetDC(hWnd);
		scene.Clear(dc);// ����� �������������� � ������ Camera2D ������, ����������� �� ������� ������� ������� ���� hWnd
		SetBkColor(dc, 0x00FFFFFF);
		//scene.Plot(dc, ellyptic);		// ����� �������������� � ������ Scene2D ������, ����������� �� ��������� ������� ���������
		scene.render(dc, model);
		ReleaseDC(hWnd, dc);
		return DefWindowProc(hWnd, msg, wParam, lParam);
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
			auto n = scene.getN();
			auto t = scene.getT();
			scene.setN(SpinAroundPoint(n,t,M_PI/30));
			//model.Apply(RotationSecond(model.GetVertexX(0), model.GetVertexY(0), model.GetVertexZ(0),
			//							model.GetVertexX(2), model.GetVertexY(2), model.GetVertexZ(2), M_PI/60));
			//model.Apply();
			break;
		}
		//D
		case 0x44:
		{
			auto n = scene.getN();
			auto t = scene.getT();
			scene.setN(SpinAroundPoint(n,t, -M_PI / 30));
			//model.Apply(RotationSecond(model.GetVertexX(0), model.GetVertexY(0), model.GetVertexZ(0),
			//	model.GetVertexX(2), model.GetVertexY(2), model.GetVertexZ(2),-M_PI / 60));
			//model.Apply();
			break;
		}
		//B
		case 0x42:
		{
			
			//scene.setN(SpinAroundPointX(scene.getN(), scene.getT(), 3));
		//	auto v = findVectForOnePointAndOX(Coordinates(2, 2, 0));
			//model.Apply(RotationFirst(model.GetVertexY(1), model.GetVertexZ(1),M_PI/60));
			model.Apply(Rotation3DZ(M_PI/60));
			model.Apply();
			break;
		}
			//C
		case 0x43: 
		{//
			//auto v = findVectForOnePointAndOX(Coordinates(2, 2, 0));
			//model.Apply(RotationFirst(model.GetVertexY(1), model.GetVertexZ(1), -M_PI / 60));
			model.Apply(Rotation3DZ(-M_PI / 60));
			model.Apply();
			//scene.setN(SpinAroundPointX(scene.getN(), scene.getT(), -3));
			//	model.Apply(Rotation3DY(-M_PI / 60));
			//	model.Apply();
			break;
		}
				   //E
		case 0x45:
		{
			model.Apply(Rotation3DX(M_PI / 60));
			model.Apply();
			break;
			//G
		}
		case 0x47:
		{
			model.Apply(Rotation3DX(-M_PI / 60));
			model.Apply();
			break;
			//G
		}
		case 0x46:
			model.Apply(Mapping03D());
			model.Apply();
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
		ReleaseDC(hWnd, dc);
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}

	case WM_CREATE:
	{
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
	return 0;
}