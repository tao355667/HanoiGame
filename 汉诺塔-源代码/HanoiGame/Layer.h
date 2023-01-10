#pragma once
#include "BasicWidget.h"
#include "graphics.h"
class Layer :
	public BasicWidget
{
public:
	Layer(int x, int y, int w, int h);
	void show() override;//œ‘ æ≤„
};

