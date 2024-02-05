#pragma once

#include "Math/Vector3.h"

class RenderTransform
{
private:
	Vector3 m_row[3];

public:
	RenderTransform();
	~RenderTransform();

};