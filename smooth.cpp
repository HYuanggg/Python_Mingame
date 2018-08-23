#include "smooth.h"
#include <stdlib.h> 
#include <cmath>

using namespace std;


/**
 * @brief 
 *
 * @param orivalue
 * @param newvalue
 * @param prenewvalue
 * @param nextnewvalue
 * @param weight_data
 * @param weight_smooth
 *
 * @return 
 */
double SmoothStep(double orivalue, 
    double &newvalue, 
    double prenewvalue, 
    double nextnewvalue, 
    double weight_data, 
    double weight_smooth){

  double aux = newvalue;
  newvalue += weight_data * (orivalue - newvalue);
  newvalue += weight_smooth * (prenewvalue + nextnewvalue - (2.0 * newvalue));
  return fabs(aux - newvalue);
}
//Added for smoothing path using CS373 smoother algorithm by Junqiao Zhao
/**
 * @brief  平滑折线路径的函数，具体原理参照CS373课程。返回值为一条新的路径，数据类型为vector<std::pair<double, double>>
 *
 * @param pointlist 当前的路径点，数据类型是vector<pair<int, int>>
 * @param weight_data 参数值，具体含义需要参考公开课视频。
 * @param weight_smooth 参数值，具体含义需要参考公开课视频。
 * @param tolerance 参数值，用来控制迭代次数。
 */
std::vector<std::pair<double, double>>Smoother::quadricSmoother(
    vector<pair<double, double>> &pointlist, 
    const double &weight_data, 
    const double &weight_smooth, 
    const double &tolerance)
{

  vector<pair<double, double>> newpointlist(pointlist.size());

  for (size_t i = 0; i < pointlist.size(); ++i) {
    newpointlist[i] = make_pair(pointlist[i].first, pointlist[i].second);
  }
  double change = tolerance;
  while (change >= tolerance)
  {
    change = 0.0;
    for (int i = 1; i < (int)newpointlist.size() - 1; ++i)
    {
      //first
      change += SmoothStep(
	  pointlist[i].first, 
	  newpointlist[i].first, 
	  newpointlist[i - 1].first, 
	  newpointlist[i + 1].first,
	  weight_data, 
	  weight_smooth);

      //second
      change += SmoothStep( 
	  pointlist[i].second,
	  newpointlist[i].second,
	  newpointlist[i - 1].second,
	  newpointlist[i + 1].second, 
	  weight_data, 
	  weight_smooth);
    }
  }
  for (size_t i = 0; i < pointlist.size(); i++) {
    pointlist[i] = (make_pair(newpointlist[i].first, newpointlist[i].second));
  }
  return newpointlist;
}
