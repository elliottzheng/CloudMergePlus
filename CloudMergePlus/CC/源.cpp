#include <pcl/io/pcd_io.h>
#include "RegistrationTools.h"
#include"SimpleCloud.h"
#include<cstdlib>
#include<iostream>

using namespace std;
using namespace CCLib;

typedef PointProjectionTools::Transformation ScaledTransformation;

int main()
{
	
	SimpleCloud* lcloud = new SimpleCloud();
	lcloud->reserve(50);
	SimpleCloud* rcloud = new SimpleCloud();
	rcloud->reserve(50);
	for (int i = 0; i < 50; i++)
	{
		
		CCVector3 v(rand() % 500, rand() % 500, rand() % 500);
		lcloud->addPoint(v);
		//cout << v.z << endl;
		v.z += 200;
		//cout << v.z << endl;
		rcloud->addPoint(v);
	}
	
	ScaledTransformation trans;
	HornRegistrationTools::FindAbsoluteOrientation(lcloud, rcloud, trans);
	cout<<HornRegistrationTools::ComputeRMS(lcloud,rcloud, trans)<<endl;
	cout << trans.T.x<<','<< trans.T.y<<','<< trans.T.z <<','<< endl;
	lcloud->applyTransformation(trans);
	system("pause");
}