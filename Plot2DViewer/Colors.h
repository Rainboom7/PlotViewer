#pragma once
#include "windef.h"
const HPEN redPen = CreatePen(PS_SOLID, 5, 0x000000FF);
const HPEN greenPen = CreatePen(PS_SOLID, 9, 0x0000FF00);
const HPEN bluePen = CreatePen(PS_SOLID, 9, RGB(128, 0, 128));
const HPEN blackPen = CreatePen(PS_SOLID, 5, 0x00000000);
const HPEN whitePen = CreatePen(PS_SOLID, 12, 0x00FFFFFF);
const HPEN orangePen = CreatePen(PS_SOLID, 9, RGB(255, 165, 0));
const HPEN yellowPen = CreatePen(PS_SOLID, 9, RGB(255, 255, 0));
const HPEN dsbluePen = CreatePen(PS_SOLID, 9, RGB(0, 255, 255));


