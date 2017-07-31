#pragma once
//#ifndef _DBSCAN_H_
//#define _DBSCAN_H_
//#endif
#pragma once
#include <vector>
class Point2D {
private:
	double x;
	double y;
	bool isKey;
	bool isClassed;
	int cluster;
public:
	Point2D() {
		this->x = 0;
		this->y = 0;
		this->isKey = false;
		this->isClassed = false;
		this->cluster = 0;
	}
	Point2D(double x, double y) {
		this->x = x;
		this->y = y;
		this->isKey = false;
		this->isClassed = false;
		this->cluster = 0;
	}
	double GetX() {
		return this->x;
	}
	double GetY() {
		return this->y;
	}
	void setX(double xx){
		this->x = xx;
	}
	void setY(double yy){
		this->y = yy;
	}
	bool getKey() {
		return this->isKey;
	}
	void setKey(bool b) {
		this->isKey = b;
	}
	bool WheKey() {
		return this->isKey;
	}
	void setCluster(int c) {
		this->cluster = c;
	}
	int getCluster() {
		return this->cluster;
	}
	void setClassed(bool b) {
		this->isClassed = b;
	}
	bool getClassed() {
		return this->isClassed;
	}
};
class Point3D{
private:
	double x;
	double y;
	double z;
public:
	Point3D() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Point3D(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	double GetX() {
		return this->x;
	}
	double GetY() {
		return this->y;
	}
	double GetZ() {
		return this->z;
	}
	void setX(double xx){
		this->x = xx;
	}
	void setY(double yy){
		this->y = yy;
	}
	void setZ(double zz){
		this->z = zz;
	}
};
double static getDisP(Point2D &p1, Point2D &p2) {
	double dx = p1.GetX() - p2.GetX();
	double dy = p1.GetY() - p2.GetY();
	return dx*dx + dy*dy;
}

std::vector<int> static isKeyPoint(std::vector<Point2D> &lst, Point2D &p, double e, int minPts) {
	int count = 0;
	std::vector<int> tmpList = std::vector<int>();
	for (int i = 0; i<lst.size(); i++) {
		Point2D p2 = lst[i];
		if (getDisP(p, p2) <= e) {
			++count;
			tmpList.push_back(i);
		}
	}
	if (count >= minPts) {
		p.setKey(true);
		return tmpList;
	}
	//tmpList.empty();
	return tmpList;
}
void static expandCluster(Point2D &p, std::vector<int> &nei, int c, double e, int minPts, std::vector<Point2D> &lst) {
	p.setCluster(c);
	for (int i = 0; i<nei.size(); i++) {
		if (lst[nei[i]].getClassed() == false) {	//Î´·ÃÎÊ
			lst[nei[i]].setClassed(true);
			std::vector<int> tmpList = std::vector<int>();
			tmpList = isKeyPoint(lst, lst[nei[i]], e, minPts);
			if (tmpList.size() >= minPts) {
				for (int k = 0; k<tmpList.size(); k++) {
					bool flag = false;
					for (int j = 0; j<nei.size(); j++) {
						if (nei[j] == tmpList[k]) {
							flag = true;
							break;
						}
					}
					if (flag == false)
						nei.push_back(tmpList[k]);
				}
			}
		}
		//¼ÓÈëc
		lst[nei[i]].setCluster(c);

	}
}
void static dbscan(std::vector<Point2D> &lst, double e, int minPts) {
	int c = 0;
	for (int i = 0; i<lst.size(); i++) {
		if (lst[i].getClassed())
			continue;
		std::vector<int> tmpList = std::vector<int>();
		tmpList = isKeyPoint(lst, lst[i], e, minPts);
		if (tmpList.size() >= minPts) {
			c++;
			expandCluster(lst[i], tmpList, c, e, minPts, lst);
		}
	}
}

int static getClusterNum(std::vector<Point2D> &lst){
	int clusterNum = 0;
	for (int p = 0; p < lst.size(); p++){
		if (clusterNum < lst[p].getCluster()){
			clusterNum = lst[p].getCluster();
		}
	}
	return clusterNum;
}

