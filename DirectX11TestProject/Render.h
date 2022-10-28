#pragma once

#include <windows.h>
#include <memory>
#include "Direct3d.h"

class Render {
private:

	std::shared_ptr<Direct3d> d3d;

public:

	explicit Render(const HWND hWnd);

	void init(void);
	void update(void);
	void draw(void) const;

};

