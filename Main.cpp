/* Copyright (C) I-Feng Lin - All Rights Reserved
* Written by I-Feng Lin <bee2016 gmail.com>, June 2016
*/
#include "Vector2.h"
#include "TXTReader.h"
#include "TXTWriter.h"

#include <iostream>

using namespace std;

double calcDistance(const Vector2, const Vector2, const Vector2);
vector<Vector2> douglasPeucker(const vector<Vector2>, const int, const int, const double);
void printPoints(const vector<Vector2>);

int main()
{
	const double threshold = 5;
	vector<Vector2> points = TXTReader::ReadVector2("C:\\Users\\i-fen\\Documents\\VisualizationTechniques\\EX4\\VToSD_input.txt");
	vector<Vector2> result_points = douglasPeucker(points, 0, points.size() - 1, threshold);	
	TXTWriter::WriteVector2("C:\\Users\\i-fen\\Documents\\VisualizationTechniques\\EX4\\VToSD_output.txt", result_points);

	// print in console
	cout << "Distance threshold = " << threshold << endl;
	cout << "Input points:" << endl;
	printPoints(points);
	cout << endl << "Output points:" << endl;
	printPoints(result_points);
	system("PAUSE");
	return 0;
}

vector<Vector2> douglasPeucker(const vector<Vector2> points, const int head, const int end, const double threshold) {
	int i, i_max;
	vector<Vector2> result_points, v2;
	double d, maxDistance = 0;

	for (i = head + 1; i < end ; i++) {
		d = calcDistance(points.at(head), points.at(end), points.at(i));
		if (d > maxDistance) {
			i_max = i;
			maxDistance = d;
		}
	}
	if (maxDistance > threshold){
		// recursion in two parts
		//// calculate the first part
		result_points = douglasPeucker(points, head, i_max, threshold);

		//// calculate the second part
		v2 = douglasPeucker(points, i_max, end, threshold);

		//// combine the results of two parts
		//// note: skip the first point in the second vector to avoid repeating point.
		result_points.insert(result_points.end(), v2.begin()+1, v2.end());

		// output for debugging
		//cout << "Max point: " << points.at(i_max).x << "," << points.at(i_max).y << endl;

		return result_points;
	}
	else{
		// return only the head and end points
		result_points.push_back(points.at(head));
		result_points.push_back(points.at(end));

		// output for debugging
		// cout << "Return points: " << points.at(head).x << "," << points.at(head).y << " ; "<< points.at(end).x << ", " << points.at(end).y << endl;

		return result_points;
	}
	
}

double calcDistance(const Vector2 p1, const Vector2 p2, const Vector2 t) {
	// calculate the distance from point t to a line between p1 and p2
	return abs((p2.y - p1.y)*t.x - (p2.x - p1.x)*t.y + p2.x*p1.y - p2.y*p1.x) / sqrt(pow((p2.y - p1.y), 2) + pow((p2.x - p1.x), 2));
}

void printPoints(const vector<Vector2> v) {
	// print the points in a vector v
	for (std::vector<Vector2>::const_iterator i = v.begin(); i != v.end(); ++i)
		std::cout << (*i).x << ',' << (*i).y << endl;
}