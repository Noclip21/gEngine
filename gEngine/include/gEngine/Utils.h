#ifndef UTILS_H
#define UTILS_H
#define PI 3.14159265

#include <vector>
#include <iostream>
#include <sstream>

using namespace std;


#include "prologue.h"
namespace utils
{
	struct vector2
	{
		double x,y;

		inline vector2()						{ x = 0; y = 0;										}
		inline vector2(double px,double py)		{ x = px; y = py;									}
		inline vector2 operator + (double n)	{ return vector2(x+n,y+n);							}
		inline vector2 operator - (double n)	{ return vector2(x-n,y-n);							}
		inline vector2 operator * (double n)	{ return vector2(x*n,y*n);							}
		inline vector2 operator + (vector2 &v2) { return vector2(x+v2.x,y+v2.y);					}
		inline vector2 operator - (vector2 &v2) { return vector2(x-v2.x,y-v2.y);					}
		inline vector2 operator * (vector2 &v2) { return vector2(x*v2.x,y*v2.y);					}
	};
	struct vector3
	{
		double x,y,z;

		inline vector3()								{ x = y = z = 0;										}
		inline vector3(	double px,double py,double pz)	{ x = px; y = py; z = pz;								}
		inline vector3 operator + (double n)			{ return vector3(x+n,y+n,z+n);							}
		inline vector3 operator - (double n)			{ return vector3(x-n,y-n,z-n);							}
		inline vector3 operator * (double n)			{ return vector3(x*n,y*n,z*n);							}
		inline vector3 operator + (vector3 &v3)			{ return vector3(x+v3.x,y+v3.y,z+v3.z);					}
		inline vector3 operator - (vector3 &v3)			{ return vector3(x-v3.x,y-v3.y,z-v3.z);					}
		inline vector3 operator * (vector3 &v3)			{ return vector3(x*v3.x,y*v3.y,z*v3.z);					}
	};

	
	static string toStringi(int n)
	{
		stringstream ss;
		ss << n;
		return ss.str();
	}
	static string toStringd(double n)
	{
		stringstream ss;
		ss << n;
		return ss.str();
	}


		// Array methods
	template <class T>
	static int findObject(T &obj,vector<T*> &v)
	{
		for(size_t i=0; i < v.size(); i++)
			if(&obj == v[i]) return i;
		return -1;
	}
	template <class T>
	static int findObject(T &obj,vector<T> &v)
	{
		for(size_t i=0; i < v.size(); i++)
			if(obj == v[i]) return i;
		return -1;
	}


	template <typename T>
	static bool removeObject(T &obj,vector<T*> &v)
	{
		int pos = findObject(obj,v);
		if(pos >= 0)
		{
			v.erase(v.begin()+pos);
			return true;
		}
		return false;
	}
	template <typename T>
	static bool removeObject(T &obj,vector<T> &v)
	{
		int pos = findObject(obj,v);
		if(pos >= 0)
		{
			v.erase(v.begin()+pos);
			return true;
		}
		return false;
	}


		// Math methods
	static double dist(pair<double,double> pos1,pair<double,double> pos2)
	{
		return sqrt(pow(pos1.first - pos2.first,2) + pow(pos1.second - pos2.second,2));
	}
}
#include "epilogue.h"

#endif