#ifndef CHC_COLOR_H
#define CHC_COLOR_H

class CHC_Color
{
public:
	int r, g, b;
	CHC_Color() {}
	CHC_Color(int _r, int _g, int _b) {
		r = _r, g = _g, b = _b;
	}
	void setColor(int _r, int _g, int _b) {
		r = _r, g = _g, b = _b;
	}
	void setColor(const CHC_Color & col) {
		r = col.r, g = col.g, b = col.b;
	}
	void operator=(const CHC_Color & c) {
		r = c.r, g = c.g, b = c.b;
	}
	void add(const CHC_Color & c) {
		r |= c.r, g |= c.g, b |= c.b;
	}
	bool operator==(const CHC_Color & c) {
		return r == c.r && g == c.g && b == c.b;
	}
	bool operator!=(const CHC_Color & c) {
		return !((*this)==c);
	}
	bool operator>=(const CHC_Color & c) {
		return r >= c.r && g >= c.g && b >= c.b;
	}
	bool notZero() {
		return (r|g|b)>0;
	}
	int changeToRGB();
};

#endif