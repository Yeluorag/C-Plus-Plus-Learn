class Point 
{
public:
	Point(int xVal = 0, int yVal = 0) : x(xVal), y(yVal) { }
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int xVal) { x = xVal; }
	void setY(int yVal) { y = yVal; }
private:
	int x, y;
};

class RefPtr			// 辅助类
{ // all private, user not allowed.
friend class SmartPtr;	// So SmartPtr can use this directly.
RefPtr(Point *ptr) : p(ptr), count(1) {}
~RefPtr() { delete p; }

int count;			// refrece count
Point *p;			// base obj pointer
};	

class SmartPtr
{
public:
	SmartPtr(Point *ptr) : rp(new RefPtr(ptr)) { }
	SmartPtr(const SmartPtr &sp) : rp(sp.rp) { ++ rp->count; }
	SmartPtr& operator=(const SmartPtr& rhs) {
		++ rhs.rp->count;
		if(-- rp->count == 0)
			delete rp;
		rp = rhs.rp;
		return *this;
	}
private:
	RefPtr *rp;
};

// test