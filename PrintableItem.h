#pragma once
#include <ostream>
using std::ostream;
#ifndef PRINTABLEITEM_H
#define PRINTABLEITEM_H


class PrintableItem
{
private:
	char spriteDesign;
	int x;
	int y;
public:
	PrintableItem(): spriteDesign('O'), x(0), y(0) {};
	PrintableItem(char design, int x_val, int y_val) : spriteDesign(design), x(x_val), y(y_val) {};
	PrintableItem(const PrintableItem& obj) {
		spriteDesign = obj.spriteDesign;
		x = obj.x;
		y = obj.y;
	}

	int getX()const noexcept {
		return x;
	}
	int getY()const noexcept {
		return y;
	}

	//potentially throw exception if x value is outside window view. 
	void setX(int xPos) {
		x = xPos;
	}
	//potentially throw exception if y value is outside window view. 
	void setY(int yPos) {
		y = yPos;
	}
	void setDesign(unsigned char newDes) {
		spriteDesign = newDes;
	}

	char draw()const {
		return spriteDesign;
	}


	PrintableItem operator=(const PrintableItem& other) {
		if (this != &other) {
			spriteDesign = other.spriteDesign;
			x = other.x;
			y = other.y;
		}
		return *this;
	}
	friend ostream& operator << (ostream&, const PrintableItem&);

};

ostream& operator<<(ostream& os, const PrintableItem& sprite) {
	os << sprite.draw();
	return os;
}

#endif
