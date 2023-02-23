#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

struct point
{
	double x, y;
};

point P[100000];
int num_pair;

bool sortbyx(point a, point b)
{
	return a.x < b.x;
}
bool sortbyy(point a, point b)
{
	return a.y < b.y;
}
float distance(point a, point b) 
{ 
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); 
}
float cloest_pair(point* A, int start, int end)
{
	//只剩兩點
	if (start == end - 1)
		return distance(A[start], A[end]);
	//只剩三點
	if (start == end - 2)
	{
		double buffer1 = distance(A[start], A[start + 1]);
		double buffer2 = distance(A[start], A[start + 2]);
		double buffer3 = distance(A[start + 1], A[start + 2]);
		buffer1 = buffer1 < buffer2 ? buffer1 : buffer2;
		buffer1 = buffer1 < buffer3 ? buffer1 : buffer3;
		return buffer1;
	}
	//divide
	int middle = (start + end) / 2; 
	//conquer
	double d = min(cloest_pair(A, start, middle), cloest_pair(A, middle+1, end));
	//combine
	int key = 0;
	//找最靠近中線的點，且距離小於左右兩邊的距離 
	for (int i = start;i <= end;i++)
		if (fabs(A[middle].x -A[i].x) < d)
			P[key++] = A[i];
	//把找完的點依y去排序，並任取一點P[i]，則P[i]和P[i+7]距離一定大於d
	sort(P, P + key, sortbyy);
	double min_distance = d;
	//尋找橫跨兩測的最近點，一個點最多找六個點計算距離即可，否則矛盾，接著比較是否比左or右區域的點之距離還要小
	for (int i = 0;i < key-1;i++)
		for (int j = i + 1; j<min(i+7, key);j++)
			if (distance(P[i], P[j]) < min_distance)
				min_distance = distance(P[i], P[j]);
	return min_distance;
}
int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		cin >> num_pair;
		point* A = new point[num_pair]{};
		for (int i = 0;i < num_pair;i++)//input
			cin >> A[i].x >> A[i].y;
		sort(A, A + num_pair, sortbyx);//根據x為主做排序
		double d = cloest_pair(A, 0, num_pair-1);//closest pair of point 
		cout <<d << endl;
		delete [] A;
	}
	return 0;
}