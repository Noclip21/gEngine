#ifndef UTILS_H
#define UTILS_H
#define PI 3.14159265

#include <vector>
#include <iostream>

using namespace std;


#include "prologue.h"
class G_DECLSPEC Utils
{
public:
	
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
	

	template <typename T>
	static void kill(T &obj)
	{
		if(&obj) delete &obj;
	}
	template <typename T>
	static void kill(T **obj)
	{
		if(*obj) delete *obj;
		*obj = NULL;
	}


	static double dist(pair<double,double> pos1,pair<double,double> pos2)
	{
		return sqrt(pow(pos1.first - pos2.first,2) + pow(pos1.second - pos2.second,2));
	}
};
#include "epilogue.h"

#endif