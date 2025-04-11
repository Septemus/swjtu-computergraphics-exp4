#pragma once
template <typename T>
class Cordinate
{
private:
	T x;
	T y;
public:
	Cordinate(T x, T y);
	const T getX() const{
		return this->x;
	}
	const T getY() const{
		return this->y;
	}
	void setX(T x) {
		this->x = x;
	}
	void setY(T y) {
		this->y = y;
	}
};

template<typename T>
Cordinate<T>::Cordinate(T x, T y) {
	this->x = x;
	this->y = y;
}