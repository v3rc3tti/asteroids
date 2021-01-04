#pragma once

#include "Win32PixelWindow.h"

class ToroidalWindow : public Win32PixelWindow {
	void drawPixel(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b) override {
		if (x < 0) {
			x += getWidth();
		} else if (x >= getWidth()) {
			x -= getWidth();
		}

		if (y < 0) {
			y += getHeight();
		} else if (y >= getHeight()) {
			y -= getHeight();
		}

		Win32PixelWindow::drawPixel(x, y, r, g, b);
	}
};