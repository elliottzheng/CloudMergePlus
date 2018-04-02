#include <RegistrationTools.h>
#include <SimpleCloud.h>
#include<cstdlib>
#include<iostream>
#include"MyReadpcd.h"
using namespace std;
using namespace CCLib;

typedef PointProjectionTools::Transformation ScaledTransformation;

//SimpleCloud 转换为 PointCloud
void SimpleToPointCloud(SimpleCloud& scloud, pcl::PointCloud<pcl::PointXYZ>& pcloud)
{
	pcloud.clear();
	for (int i = 0; i < scloud.size(); i++)
	{
		const CCVector3* point=scloud.getPoint(i);
		pcloud.push_back(pcl::PointXYZ(point->x, point->y, point->z));
	}
}

//PointCloud 转换为 SimpleCloud
void PointCloudToSimple(pcl::PointCloud<pcl::PointXYZ>& pcloud, SimpleCloud& scloud)
{
	scloud.clear();
	for (int i = 0; i < pcloud.size(); i++)
	{
		pcl::PointXYZ point = pcloud.points[i];
		scloud.addPoint(CCVector3(point.x, point.y, point.z));
	}
}


using namespace pcl;
int main()
{

	SimpleCloud* lcloud = new SimpleCloud();
	MPCR::MyreadPCD("L.pcd", *lcloud);
	SimpleCloud* rcloud = new SimpleCloud();
	rcloud->reserve(50);
	for (int i = 0; i < 50; i++)
	{
		rcloud->addPoint(CCVector3(rand() % 500, rand() % 500, rand() % 500));
	}
	MPCR::MyWritePCD("NEW.pcd", *rcloud);

	ScaledTransformation trans;
	HornRegistrationTools::FindAbsoluteOrientation(lcloud, rcloud, trans);
	PointCloud<PointXYZ> plcloud,prcloud;
	SimpleToPointCloud(*lcloud, plcloud);
	SimpleToPointCloud(*rcloud, prcloud);
	MPCR::writePCD("L.pcd", plcloud);
	MPCR::writePCD("R.pcd", prcloud);
	cout << HornRegistrationTools::ComputeRMS(lcloud, rcloud, trans) << endl;
	cout << trans.T.x << ',' << trans.T.y << ',' << trans.T.z << ',' << endl;
	lcloud->applyTransformation(trans);
	//SimpleToPointCloud(*lcloud, plcloud);
	//writePCD("L2.pcd", plcloud);*/
	system("pause");
}