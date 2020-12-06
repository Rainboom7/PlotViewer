#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"
#include "ParametricFuntion.h"
#include "Model2D.h"
#include "Colors.h"


class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
	const double STEP = 0.1;
public:
	Scene2D(double L, double R, double B, double T) : Camera2D(L, R, B, T)
	{
	}
	void Plot(HDC dc, ParametricFunction *f, bool axes=true)
	{
		Axes(dc);
		if (axes)
			Axes(dc);
		
	
		double x, y;
		double step = sqrt(1.0 / (10 * W));
		//double step =(f->getMax()-f->getMin())/(( R - L));
		double t= f->getMin();
		MoveTo(f->getDecartX(t), f->getDecartY(t));
		for (t = f->getMin(); t <= f->getMax(); t +=step) {
			x = f->getDecartX(t);
			y = f->getDecartY(t);
			LineTo(dc, x, y);
			//MoveTo(x, y);
		}
		t = f->getMax();
		x = f->getDecartX(t);
		y = f->getDecartY(t);
		LineTo(dc, x, y);
		//MoveTo(x, y);

	//	MoveTo(L, 0);
	//	for (double i = this->L; i < this->R; i+=STEP)
	//	{
			
	//		LineTo(dc, i, f(i));
	//		MoveTo(i, f(i));
	//	}
	}
	void renderModel(HDC dc, Model2D model) {
		double x,y,factor;
		int e1, e2;
		Axes(dc);
		HPEN colors[7] = {whitePen, redPen,orangePen,yellowPen,greenPen,dsbluePen,bluePen};
		int edge_rows = model.getEdges().getRows();
		int i;
		for ( i= 0; i < 3; i++) {
			e1 = model.getEdges().getCell(i, 0);
			e2 = model.getEdges().getCell(i, 1);

			factor = model.getVertices().getCell(2, e1);
			x = model.getVertices().getCell(0, e1)/ factor;
			y = model.getVertices().getCell(1, e1)/ factor;
			MoveTo( x, y);

			factor = model.getVertices().getCell(2, e2);
			x = model.getVertices().getCell(0, e2)/factor;
			y = model.getVertices().getCell(1, e2)/factor;
			LineTo(dc, x, y);
		}
		int k = 0;
		for (i; i < edge_rows; i++) {
			e1 = model.getEdges().getCell(i, 0);
			e2 = model.getEdges().getCell(i, 1);

			x = model.getVertices().getCell(0, e1);
			y = model.getVertices().getCell(1, e1);
			MoveTo(x, y);


			x = model.getVertices().getCell(0, e2);
			y = model.getVertices().getCell(1, e2);
			LineTo(dc, x-k*0.25, y,colors[k]);
			k++;
		}
	

	}
};

#endif SCENE_2D_H
