#pragma once

class Singleton
{
protected:
	Singleton()
	{}
private:
	static Singleton* p;
public:
	static Singleton* initance();
};