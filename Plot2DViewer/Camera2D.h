#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double L, R, B, T;					// Мировые координаты границ рабочей области окна
	int W, H;							// Разрешение рабочей области окна
	int WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
	{
		return (int)((X - L) / (R - L) * W);
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
	{
		return (int)((T - Y) / (T - B) * H);
	}
	double ScreenToWorldX(int X)		// Переход от экранных координат к мировым (для абсциссы)
	{
		double Xs = (double)X + 0.5;
		return L + (R - L) * (Xs / W);
	}
	double ScreenToWorldY(int Y)		// Переход от экранных координат к мировым (для ординаты)
	{
		double Ys = (double)Y + 0.5;
		return (T - (T - B) * (Ys / H));
	}
private:
	double posX, posY;					// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
	int previousX, previousY;
	bool isDragging = false;
	void updatePrevious(int X, int Y)
	{
		previousX = X;
		previousY = Y;
	}
public:
	Camera2D(double L, double R, double B, double T) : L(L), R(R), B(B), T(T)
	{
	//	this->H = this->T - this->B;
		//this->W = this->L - this->R;
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);		
		Rectangle(dc, 0, 0, r.right, r.bottom);
		FillRect(dc, &r, (HBRUSH)(CreateSolidBrush(0x00000000)));
	}
	void zoom(double dz, int X, int Y)
	{
		/*
		COLORREF PenColor = RGB(255, 0, 0);
		HPEN pen = (HPEN) SelectObject(dc,CreatePen(PS_SOLID,3,PenColor));
		Ellipse(dc,X-2,Y-2,X+2,Y+2);
		DeleteObject(SelectObject(dc,pen));
		*/
		double
			k = (dz > 0) ? 1.2 : 0.8,
			Xw = ScreenToWorldX(X),
			Yw = ScreenToWorldY(Y);

		L = Xw - (Xw - L) / k;
		R = Xw + (R - Xw) / k;
		B = Yw - (Yw - B) / k;
		T = Yw + (T - Yw) / k;
	}
	void SetResolution(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		//auto dH =  r.right-this->H;
		//auto dW =  r.bottom -this->W;
		W = r.right+1;
		H = r.bottom+1;
		//if (dH !=0) {
		//if(dh!=0||)
		double
			BT = (this->B + this->T) / 2.0,
			LR = (this->R - this->L) / 2.0*H / W;

		this->B= BT - LR;
		this->T= BT + LR;
			
	//}
		//else if( dW != 0) {1
		//	this->L = (this->L + this->R) / 2 - (this->T - this->B)*W / H;
			//this->R = (this->L + this->R) / 2 + (this->T - this->B)*W / H;
	//	}
		//else if (dW != 0 && dH != 0) {
			//this->B = (this->B + this->T) / 2 - (this->R - this->L)*H / W;
			//this->T = (this->B + this->T) / 2 + (this->R - this->L)*H / W;
			//this->L = (this->L + this->R) / 2 - (this->T - this->B)*W / H;
			//this->R = (this->L + this->R) / 2 + (this->T - this->B)*W / H;
		//}

	}
	void Move(int X, int Y)
	{
		double
			deltaX = (R - L) * X / W,
			deltaY = (T - B) * Y / H;
		L -= deltaX;
		R -= deltaX;
		B += deltaY;
		T += deltaY;
	}
	void MoveTo(double X, double Y)
	{
		// Перемещение графического курсора (posX, posY)
		// Обратите внимание, что мы действуем в мировых координатах
		posX = X;
		posY = Y;
	}
	void LineTo(HDC dc, double X, double Y, HPEN pen = NULL)
	{
		// Отрисовка линии из текущей позиции графического курсора в точку (X, Y) и его перемещение в эту точку
		// Обратите внимание, что мы действуем в мировых координатах
		// При отрисовке линии могут быть использованы WinApi функции
		// ::MoveToEx(dc, Xs, Ys, nullptr) и ::LineTo(dc, Xs, Ys)
		if (pen == NULL) {
			pen = CreatePen(PS_SOLID, 3, RGB(255,255,255));
		}
		SelectObject(dc, pen);
		::MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), NULL);
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X, Y);
	}
	void StartDragging(int X, int Y)
	{
		updatePrevious(X, Y);
		isDragging = true;
	}
	bool IsDragging()
	{
		return isDragging;
	}
	void Drag(int X, int Y)
	{
		int dx = X - previousX;
		int dy = Y - previousY;
		Move(dx, dy);
		updatePrevious(X, Y);
	}
	void StopDragging()
	{
		isDragging = false;
	}
	void Axes(HDC dc)
	{
		// Отрисовка координатных осей
		MoveTo(L, 0);
		LineTo(dc, R, 0);

		MoveTo(0, B);
		LineTo(dc, 0, T);
	}


};

#endif CAMERA_2D_H
