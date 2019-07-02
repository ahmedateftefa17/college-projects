/**
 *
 *  >>> PLEASE READ THE FOLLOWING!
 *  *** IMPORTANT ***
 *  1. THERE IS NO NEED TO ENTER POINTS IN ORDER; AS THE PROGRAM WILL SORT THEM *** CCW ***
 *    BY THEIR *** ANGLES RELATIVE TO POLYGON'S CENTRE ***.
 *    AND ALL OUTPUTS WILL BE PRINTED IN THIS ORDER.
 *  2. ANY OPERATION WORKS BY DEFAULT WITH *** ALL POINTS OF POLYGONS *** 
 *    UNLESS THE OPERATION'S DESCRIPTION IS TO EXCLUDE REDUNDANT POINTS OF POLYGON.
 *  3. "Inside_Circle" AND "Inside_Rectangle" OPERATIONS RETURN POLYGONS IDS WHICH ARE
 *    *** COMPLETELY INSIDE ***.
 *  4. "List_Rectangles" OPERATION IS LIST *** RECTANGLES ONLY, SQUARES ARE EXCLUDED ***.
 *
 *
 *
 */


#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>

using namespace std;

#define PI 3.14159265358979323846

class Point{
public:
  float x, y;
  int polygonsNumber = 0;
  float angle; // this angle is relative to polygon's center.
  Point();
  Point(string handle, char splitter = ',');
  Point(float handleX, float handleY);
  bool operator==(Point& p);
  friend ostream& operator<<(ostream& out, Point p){
    out << "(" << p.x << "," << p.y << ")";
    return out;
  }
};

class Polygon{
public:
  int iSize = 0, uSize = 0, aSize = 0, rSize = 0;
  float cx = 0, cy = 0;
  vector<Point> iPoints, uPoints, aPoints, rPoints, pointsByX, pointsByY;
  Polygon();
  Polygon(string handlePolygonString);
  Polygon(vector<Point> handlePointsVector);
  float getPerimeter();
  bool isRectangle();
  bool isTrapezoid();
  float getArea();
  bool hasPointInside(Point p);
  bool isIntersect(Polygon poly);
};

class fn{
public:
  static float length(Point p1, Point p2);
  static bool isRightAngle(Point p1, Point p2, Point p3);
  static float angle(Point p1, Point p2, Point p3);
  static float getMinX(vector<Polygon> handlePolygonsVector);
  static float getMaxX(vector<Polygon> handlePolygonsVector);
  static float getMinY(vector<Polygon> handlePolygonsVector);
  static float getMaxY(vector<Polygon> handlePolygonsVector);
  static void serPointsPolygonsNumber(vector<Polygon> handlePolygons, vector<Point>& handlePoints);
  static string getString(string handle, char startChar, char endChar);
  static string replaceCharBetween(string handle, char startChar, char replaceChar, char replaceCharBy, char endChar);
  static vector<string> explodeString(string handle, char splittingChar);
  static float slope(Point p1, Point p2);
  static vector<Point> getUniqPoints(vector<Point> handlePoints);
  static float lineConstant(float slope, Point p);
  static Point slove2Lines(float m1, float m2, float c1, float c2, Point p1, Point p2);
  static bool isPointBetween(Point p, Point p1, Point p2);
  static float sign(Point p1, Point p2, Point p3);
  static bool pointInTriangle (Point pt, Point v1, Point v2, Point v3);

};

int main(int argc, char const *argv[]) {

  /* uncomment to enable Test Cases Mode *
  string nextTestCaseExists;
  do {
    cout << "------------------------TEST CASE START------------------------" << endl;
    /* Main Code */
    string inputPolygons;
    string queryLine;
    vector<string> inputPolygonsVector;
    vector<Polygon> Polygons;
    vector<Point> Points;
    getline(cin, inputPolygons);
    inputPolygons = fn::getString(inputPolygons, '[', ']');
    inputPolygonsVector = fn::explodeString(inputPolygons, ';');
    for(int i = 0; i < inputPolygonsVector.size(); i++) Polygons.push_back(Polygon(inputPolygonsVector[i]));
    for(int i = 0; i < Polygons.size(); i++)
      for(int j = 0; j < Polygons[i].iSize; j++)
        Points.push_back(Polygons[i].iPoints[j]);
    Points = fn::getUniqPoints(Points);
    fn::serPointsPolygonsNumber(Polygons, Points);
    getline(cin, queryLine);
    while(queryLine != "Quit"){
      string operation = fn::explodeString(queryLine, ' ')[0];
      /* Level 1 */
      if(operation == "Number_Polygons")  cout << Polygons.size() << endl;
      if(queryLine == "Total_Number_Points"){
        int total = 0;
        for (int i = 0; i < Polygons.size(); i++) total += Polygons[i].iSize;
        cout << total << endl;
      }
      if(operation == "Minimum_X") cout << fn::getMinX(Polygons) << endl; 
      if(operation == "Maximum_X") cout << fn::getMaxX(Polygons) << endl; 
      if(operation == "Minimum_Y") cout << fn::getMinY(Polygons) << endl; 
      if(operation == "Maximum_Y") cout << fn::getMaxY(Polygons) << endl; 
      if(operation == "Enclosing_Rectangle"){
        float minX = fn::getMinX(Polygons); float maxX = fn::getMaxX(Polygons);
        float minY = fn::getMinY(Polygons); float maxY = fn::getMaxY(Polygons);
        cout << Point(maxX, maxY) << "," << Point(minX, maxY) << "," << Point(minX, minY) << "," << Point(maxX, minY)<< endl;
      }
      if(operation == "Total_Redundant_Points"){
        int total = 0;
        for (int i = 0; i < Polygons.size(); i++) total += Polygons[i].iSize - Polygons[i].rSize;
        if(total == 0) cout << "none"; else cout << total;
        cout << endl;
      }
      /* Level 2 */
      if(operation == "Polygon_Points"){
        string parameter = fn::explodeString(queryLine, ' ')[1];
        int n = atoi(parameter.c_str());
        int size = Polygons[n-1].rSize;
        for(int i = 0; i < size; i++){
          cout << Polygons[n-1].rPoints[i];
          if(i < size - 1) cout << ",";
        }
        cout << endl;
      }
      if(operation == "Point_Polygons"){
        string parameter = fn::explodeString(queryLine, ' ')[1];
        Point p = Point(parameter);
        vector<int> polygonsIDs;
        for(int i = 0; i < Polygons.size(); i++)
          for(int j = 0; j < Polygons[i].iSize; j++)
            if(Polygons[i].iPoints[j] == p){
              polygonsIDs.push_back(i+1);
              break;
            }
        for(int i = 0; i < polygonsIDs.size(); i++){
          cout << polygonsIDs[i];
          if(i < polygonsIDs.size() - 1) cout << ",";
        }
        if(polygonsIDs.size() == 0) cout << "none";
        cout << endl;
      }
      if(operation == "List_Polygons_Points"){
        vector<string> parameters = fn::explodeString(queryLine, ' ');
        int n = atoi(parameters[2].c_str());
        vector<int> polygonsIDs;
        for(int i = 0; i < Polygons.size(); i++)
          if( (parameters[1] == "More" && Polygons[i].rSize > n) 
            || (parameters[1] == "Less" && Polygons[i].rSize < n)
            || (parameters[1] == "Equal" && Polygons[i].rSize == n) )
            polygonsIDs.push_back(i+1);
        for(int i = 0; i < polygonsIDs.size(); i++){
          cout << polygonsIDs[i];
          if(i < polygonsIDs.size() - 1) cout << ",";
        }
        if(polygonsIDs.size() == 0) cout << "none";
        cout << endl;
      }
      if(operation == "List_Points_Polygons"){
        vector<string> parameters = fn::explodeString(queryLine, ' ');
        int n = atoi(parameters[2].c_str());
        vector<Point> result;
        for(int i = 0; i < Points.size(); i++)
          if( (parameters[1] == "More" && Points[i].polygonsNumber > n) 
            || (parameters[1] == "Less" && Points[i].polygonsNumber < n)
            || (parameters[1] == "Equal" && Points[i].polygonsNumber == n) )
            result.push_back(Points[i]);
        for(int i = 0; i < result.size(); i++){
          cout << result[i];
          if(i < result.size() - 1) cout << ",";
        }
        if(result.size() == 0) cout << "none";
        cout << endl;
      }
      if(operation == "Polygon_Perimeter"){
        string parameter = fn::explodeString(queryLine, ' ')[1];
        int n = atoi(parameter.c_str());
        cout << Polygons[n-1].getPerimeter() << endl;
      }
      if(operation == "List_Triangles"){
        vector<int> temp;
        for(int i = 0; i < Polygons.size(); i++)
          if(Polygons[i].rPoints.size() == 3) 
            temp.push_back(i+1);
        for(int i = 0; i < temp.size(); i++){
          cout << temp[i];
          if(i < temp.size() - 1) cout << ",";
        }
        if(temp.size() == 0) cout << "none";
        cout << endl;
      }
      if(operation == "List_Rectangles"){
        vector<int> temp;
        for(int i = 0; i < Polygons.size(); i++)
          if(Polygons[i].isRectangle()) 
            temp.push_back(i+1);
        for(int i = 0; i < temp.size(); i++){
          cout << temp[i];
          if(i < temp.size() - 1) cout << ",";
        }
        if(temp.size() == 0) cout << "none";
        cout << endl;
      }
      if(operation == "List_Trapezoid"){
        vector<int> temp;
        for(int i = 0; i < Polygons.size(); i++)
          if(Polygons[i].isTrapezoid()) 
            temp.push_back(i+1);
        for(int i = 0; i < temp.size(); i++){
          cout << temp[i];
          if(i < temp.size() - 1) cout << ",";
        }
        if(temp.size() == 0) cout << "none";
        cout << endl;
      }
      /* Level 3 */
      if(operation == "Inside_Rectangle"){
        string parameter = fn::explodeString(queryLine, ' ')[1];
        Polygon poly = Polygon(parameter);
        vector<int> polygonsIDs;
        for(int i = 0; i < Polygons.size(); i++){
          bool inside = true;
          for(int j = 0; j < Polygons[i].rSize; j++){
            bool in = poly.hasPointInside(Polygons[i].rPoints[j]);
            if(!in){
              inside = false;
              break;
            }
          }
          if(inside)  polygonsIDs.push_back(i+1);
        }
        for(int i = 0; i < polygonsIDs.size(); i++){
          cout << polygonsIDs[i];
          if(i < polygonsIDs.size() - 1) cout << ",";
        }
        if(polygonsIDs.size() == 0) cout << "none";
        cout << endl;
      }
      if(operation == "Inside_Circle"){
        string parameters = fn::explodeString(queryLine, ' ')[1];
        vector<string> vparameters = fn::explodeString(parameters, ',');
        Point c = Point(atof(vparameters[0].substr(1).c_str()),atof(vparameters[1].substr(0, vparameters[1].length() - 1).c_str()));
        float r = atof(vparameters[2].c_str());
        vector<int> polygonsIDs;
        for(int i = 0; i < Polygons.size(); i++){
          bool inside = true;
          for(int j = 0; j < Polygons[i].rSize; j++)
            if(fn::length(c, Polygons[i].rPoints[j]) > r){
              inside = false;
              break;
            }
          if(inside)  polygonsIDs.push_back(i+1);
        }
        for(int i = 0; i < polygonsIDs.size(); i++){
          cout << polygonsIDs[i];
          if(i < polygonsIDs.size() - 1) cout << ",";
        }
        if(polygonsIDs.size() == 0) cout << "none";
        cout << endl;

      }
      if(operation == "Polygon_Area"){
        string parameter = fn::explodeString(queryLine, ' ')[1];
        int n = atoi(parameter.c_str());
        cout << Polygons[n-1].getArea() << endl;
      }
      if(operation == "Polygons_Area_Range"){
        string parameters = fn::explodeString(queryLine, ' ')[1];
        float minArea = atof(fn::explodeString(parameters, ',')[0].c_str());
        float maxArea = atof(fn::explodeString(parameters, ',')[1].c_str());
        vector<int> temp;
        for(int i = 0; i < Polygons.size(); i++)
          if(Polygons[i].getArea() < maxArea && Polygons[i].getArea() > minArea) 
            temp.push_back(i+1);
        for(int i = 0; i < temp.size(); i++){
          cout << temp[i];
          if(i < temp.size() - 1) cout << ",";
        }
        if(temp.size() == 0) cout << "none";
        cout << endl;
      }
      if(operation == "Polygons_Enclosing_Point"){
        string parameter = fn::explodeString(queryLine, ' ')[1];
        Point p = Point(parameter);
        vector<int> polygonsIDs;
        for(int i = 0; i < Polygons.size(); i++)
          if(Polygons[i].hasPointInside(p))
            polygonsIDs.push_back(i+1);
        for(int i = 0; i < polygonsIDs.size(); i++){
          cout << polygonsIDs[i];
          if(i < polygonsIDs.size() - 1) cout << ",";
        }
        if(polygonsIDs.size() == 0) cout << "none";
        cout << endl;
      }
      if(operation == "Is_Intersecting"){
        string parameters = fn::explodeString(queryLine, ' ')[1];
        int st = atoi(fn::explodeString(parameters, ',')[0].c_str()) - 1;
        int nd = atoi(fn::explodeString(parameters, ',')[1].c_str()) - 1;
        if(Polygons[nd].isIntersect(Polygons[st])) cout << "TRUE" << endl;
        else cout << "FALSE" << endl;
      }
      if(operation == "Intersecting_Group"){
        string parameter = fn::explodeString(queryLine, ' ')[1];
        vector<string> vparameters = fn::explodeString(parameter, ',');
        vector<int> polyIds(vparameters.size());
        for(int i = 0; i < vparameters.size(); i++)
          polyIds[i] = atoi(vparameters[i].c_str());
        bool intersecting = false;
        for(int i = 0; i < polyIds.size(); i++){
          for(int j = 0; j < polyIds.size(); j++){
            if(j == i) continue;            
            intersecting = Polygons[polyIds[i]-1].isIntersect(Polygons[polyIds[j]-1]);
            if(!intersecting) break;
          }
          if(!intersecting) break;
        }
        if(intersecting) cout << "TRUE";
        else cout << "FALSE";
        cout << endl;
      }
      if(operation == "Largest_Intersecting_Pair"){
        int iPair = 0;
        for(int i = 0; i < Polygons.size(); i++) iPair += i;
        vector<float> pairAreaSum(iPair);
        vector<bool> pairIntersect(iPair);
        vector<Point> pairIndex(iPair);
        for(int i = 0, k = 0; i < Polygons.size(); i++){
          for(int j = i + 1; j < Polygons.size(); j++){
            pairAreaSum[k] = Polygons[i].getArea() + Polygons[j].getArea();
            pairIntersect[k] = Polygons[i].isIntersect(Polygons[j]);
            pairIndex[k] = Point(i, j);
            k++;
          }          
        }
        float indexPairAreaSum = 0;
        for(int i = 1; i < iPair; i++)
          if(pairAreaSum[i] > pairAreaSum[indexPairAreaSum] && pairIntersect[i]) indexPairAreaSum = i;
        cout << pairIndex[indexPairAreaSum].x+1 << "," << pairIndex[indexPairAreaSum].y+1 << endl;
      }
      /*  */
      getline(cin, queryLine);
    }
    /* uncomment to enable Test Cases Mode *
    cout << "-------------------------TEST CASE END-------------------------" << endl;
    getline(cin, nextTestCaseExists);
    if(nextTestCaseExists == "Done") break;
  } while(nextTestCaseExists == "Again");
  /**/
  return 0;
}

/* Functions */
string fn::getString(string handle, char startChar, char endChar) {
  string result;
  for (unsigned int i = handle.find(startChar) + 1; i < handle.find(endChar); i++) result += handle[i];
  return result;
}
string fn::replaceCharBetween(string handle, char startChar, char replaceChar, char replaceCharBy, char endChar) {
  for (unsigned int stringIndex = 0; stringIndex < handle.length(); stringIndex++)
    if (handle[stringIndex] == startChar)
      for (; handle[stringIndex] != endChar; stringIndex++)
        if (handle[stringIndex] == replaceChar) handle[stringIndex] = replaceCharBy;
  return handle;
}
vector<string> fn::explodeString(string handle, char splittingChar) {
  vector<string> result;
  for (unsigned int stringIndex = 0, vectorIndex = 0; stringIndex < handle.length(); stringIndex++)
    if (handle[stringIndex] != splittingChar) {
      result.resize(vectorIndex + 1);
      result[vectorIndex] += handle[stringIndex];
    }
    else vectorIndex++;
  return result;
}
float fn::length(Point p1, Point p2){
  return sqrt(pow(abs(p1.x-p2.x),2)+pow(abs(p1.y-p2.y),2));
}
bool fn::isRightAngle(Point p1, Point p2, Point p3){
  return abs(pow(length(p1,p2),2)+pow(length(p2,p3),2)-pow(length(p1,p3),2)) < 0.0001;
}
float fn::angle(Point p1, Point p2, Point p3){
  float angleInDeg = ( acos(
    ( pow(fn::length(p1, p3), 2) - pow(fn::length(p1, p2), 2) - pow(fn::length(p2, p3),2) ) /
    ( -2 * fn::length(p1, p2) * fn::length(p2, p3) ) 
  ) * 180.0 ) / (PI);
  if(p3.y < p2.y) angleInDeg = 360 - angleInDeg;
  return angleInDeg;
}
float fn::slope(Point p1, Point p2){
  return (p2.y - p1.y) / (p2.x - p1.x);
}
float fn::lineConstant(float slope, Point p){
  return (p.y) - (slope * p.x);
}
Point fn::slove2Lines(float m1, float m2, float c1, float c2, Point p1, Point p2){
  float x, y;
  if(!isinf(m1) && !isinf(m2)){ x = ( c2 - c1 ) / ( m1 - m2 );  y = ( m1 * x - c1 ); }
  if(!isinf(m1) && isinf(m2)){ x = p2.x;   y = (m1 * x) + c1; }
  if(isinf(m1) && !isinf(m2)){ x = p1.x;   y = (m2 * x) + c2; }
  return Point(x, y);
}
bool fn::isPointBetween(Point p, Point p1, Point p2){
  return abs( fn::length(p, p1) + fn::length(p, p2) - fn::length(p1, p2) ) < 0.0001
        && fn::slope(p1, p) == slope(p, p2);
}
float fn::getMinX(vector<Polygon> handlePolygonsVector){
  float minX = handlePolygonsVector[0].pointsByX[0].x;
  for (int i = 0; i < handlePolygonsVector.size(); i++)
    if(handlePolygonsVector[i].pointsByX[0].x < minX)
      minX = handlePolygonsVector[i].pointsByX[0].x;
  return minX;
}
float fn::getMaxX(vector<Polygon> handlePolygonsVector){
  float maxX = handlePolygonsVector[0].pointsByX[0].x;
  for (int i = 0; i < handlePolygonsVector.size(); i++)
    if(handlePolygonsVector[i].pointsByX.back().x > maxX)
      maxX = handlePolygonsVector[i].pointsByX.back().x;
  return maxX;
}
float fn::getMinY(vector<Polygon> handlePolygonsVector){
  float minY = handlePolygonsVector[0].pointsByY[0].y;
  for (int i = 0; i < handlePolygonsVector.size(); i++)
    if(handlePolygonsVector[i].pointsByY[0].y < minY) 
      minY = handlePolygonsVector[i].pointsByY[0].y;
  return minY;
}
float fn::getMaxY(vector<Polygon> handlePolygonsVector){
  float maxY = handlePolygonsVector[0].pointsByY[0].y;
  for (int i = 0; i < handlePolygonsVector.size(); i++)
    if(handlePolygonsVector[i].pointsByY.back().y > maxY) 
      maxY = handlePolygonsVector[i].pointsByY.back().y;
  return maxY;
}
void fn::serPointsPolygonsNumber(vector<Polygon> handlePolygons, vector<Point>& handlePoints){
  for(int i = 0; i < handlePolygons.size(); i++)
    for(int j = 0; j < handlePolygons[i].rSize; j++)
      for(int k = 0; k < handlePoints.size(); k++)
        if(handlePolygons[i].rPoints[j] == handlePoints[k])
          handlePoints[k].polygonsNumber++;
}

vector<Point> fn::getUniqPoints(vector<Point> handlePoints) {
  vector<Point> uniqList;
  for (int i = 0; i < handlePoints.size(); i++) {
    bool repeated = false;
    for (int j = 0; j < uniqList.size(); j++) if (handlePoints[i] == uniqList[j]) repeated = true;
    if (repeated) continue;
    uniqList.push_back(handlePoints[i]);
  }
  return uniqList;
}

/* Point */
Point::Point(){  x = 0;  y = 0;  }
Point::Point(string handle, char splitter){
  string handleStringPure = fn::getString(handle, '(', ')');
  vector<string> stringAxis = fn::explodeString(handleStringPure, splitter);
  x = atof(stringAxis[0].c_str());
  y = atof(stringAxis[1].c_str());
}
Point::Point(float handleX, float handleY){  x = handleX;  y = handleY;  }
bool Point::operator==(Point& p) {
  if(this->x != p.x) return false;
  if(this->y != p.y) return false;
  return true;
}

/* Polygon */
Polygon::Polygon(){  iSize = 0;    rSize = 0;  }
Polygon::Polygon(vector<Point> handlePointsVector) {
  iPoints = handlePointsVector;
  pointsByX = iPoints;   pointsByY = iPoints;
  sort(pointsByX.begin(), pointsByX.end(), [](Point p1, Point p2) { return p1.x < p2.x; });
  sort(pointsByY.begin(), pointsByY.end(), [](Point p1, Point p2) { return p1.y < p2.y; });
}
Polygon::Polygon(string handlePolygonString) {
  string sPoints =  fn::replaceCharBetween(handlePolygonString, '(', ',', '&', ')');
  vector<string> vsPoints = fn::explodeString(sPoints, ',');
  iPoints.resize(vsPoints.size());
  for(int i = 0; i < vsPoints.size(); i++)
    iPoints[i] = Point(vsPoints[i], '&');
  iSize = iPoints.size();
  pointsByX = iPoints;   pointsByY = iPoints;
  sort(pointsByX.begin(), pointsByX.end(), [](Point p1, Point p2) { return p1.x < p2.x; });
  sort(pointsByY.begin(), pointsByY.end(), [](Point p1, Point p2) { return p1.y < p2.y; });
  uPoints = fn::getUniqPoints(iPoints);
  uSize = uPoints.size();
  for(int i = 0; i < uSize; i++)
    cx += uPoints[i].x, cy += uPoints[i].y;
  cx /= uSize;    cy /= uSize;
  for(int i = 0; i < iSize; i++)
    iPoints[i].angle = fn::angle(Point(cx+1, cy), Point(cx, cy), iPoints[i]);
  aPoints = iPoints;
  sort(aPoints.begin(), aPoints.end(), [](Point p1, Point p2) { return p1.angle < p2.angle; });
  rPoints = fn::getUniqPoints(aPoints);
  /**
   * cout << "-----------POLY--------------" << endl;
   * for(int i = 0; i < iSize; i++)
   * cout << iPoints[i] << endl;
   */
  vector<int> indexToRem;
  for(int i = 0; i < rPoints.size(); i++){
    int u = i + 1;
    int v = i + 2;
    if(i + 2 == rPoints.size())   v = 0;
    if(i + 1 == rPoints.size()) { u = 0; v = 1; }
    if( (fn::slope(rPoints[i], rPoints[u]) == fn::slope(rPoints[u], rPoints[v])))
      indexToRem.push_back(u);
  }
  for(int i = 0; i < indexToRem.size(); i++)
    rPoints.erase(rPoints.begin()+indexToRem[i]-i);
  /**
   * cout << "-----------SORT--------------" << endl;
   * for(int i = 0; i < rPoints.size(); i++)
   * cout << rPoints[i] << endl;
   */
  rSize = rPoints.size();

}
float Polygon::getPerimeter(){
  float perimeter = 0;
  for(int i = 1; i < rPoints.size(); i++){
    perimeter += fn::length(rPoints[i-1], rPoints[i]);
    if(i + 1 ==  rPoints.size()) perimeter += fn::length(rPoints[i], rPoints[0]);
  }
  return perimeter;
}
bool Polygon::isRectangle(){
  if(rPoints.size() != 4) return false;
  if(fn::length(rPoints[0], rPoints[1]) == fn::length(rPoints[1], rPoints[2])) return false;
  return fn::isRightAngle(rPoints[0], rPoints[1], rPoints[2])
        && fn::isRightAngle(rPoints[1], rPoints[2], rPoints[3])
        && fn::isRightAngle(rPoints[2], rPoints[3], rPoints[0])
        && fn::isRightAngle(rPoints[3], rPoints[0], rPoints[1]);
}
bool Polygon::isTrapezoid(){
  if(rPoints.size() != 4) return false;
  return (fn::slope(rPoints[0], rPoints[1]) == fn::slope(rPoints[3], rPoints[2]) 
        && fn::slope(rPoints[1], rPoints[2]) != fn::slope(rPoints[0], rPoints[3]))
      || (fn::slope(rPoints[1], rPoints[2]) == fn::slope(rPoints[0], rPoints[3]) 
        && fn::slope(rPoints[0], rPoints[1]) != fn::slope(rPoints[3], rPoints[2]));
}
float Polygon::getArea(){
  float area = 0;
  for(int i = 0; i < rSize; i++)
    if(i < rSize - 1)   area += (rPoints[i].x * rPoints[i+1].y) - (rPoints[i+1].x * rPoints[i].y);
    else area += (rPoints[i].x * rPoints[0].y) - (rPoints[0].x * rPoints[i].y);
  return area * 0.5;
}
float fn::sign(Point p1, Point p2, Point p3){
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}
bool fn::pointInTriangle (Point pt, Point v1, Point v2, Point v3){
    bool b1, b2, b3;
    b1 = fn::sign(pt, v1, v2) < 0.0;
    b2 = fn::sign(pt, v2, v3) < 0.0;
    b3 = fn::sign(pt, v3, v1) < 0.0;
    return ((b1 == b2) && (b2 == b3));
}
bool Polygon::hasPointInside(Point p){
  p.angle = fn::angle(Point(cx+1, cy), Point(cx, cy), p);
  int u = 0, v = 0;
  for(int i = 0; i < rSize; i++){
    if(rPoints[i].angle > p.angle) {
      v = i;
      break;
    }
  }
  if(v == 0) u = rSize - 1;
  else u = v - 1;
  return fn::pointInTriangle(p, Point(cx, cy), rPoints[u], rPoints[v]);
}

bool Polygon::isIntersect(Polygon poly){
  bool intersecting = false;
  for(int i = 0; i < poly.iSize; i++){
    if(this->hasPointInside(poly.iPoints[i])){
      intersecting = true;
      break;
    }
  }
  return intersecting;
}