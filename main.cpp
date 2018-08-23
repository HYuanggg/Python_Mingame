
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstring>
#include <string>
#include <thread>
#include <stdlib.h>
#include "nature.h"
#include "event.h"
#include "TS_receiver.h"
#include "runtime_info/log.h"
#include "acc.h"
#include "run.h"

using namespace std;
using namespace TiEV;

extern unsigned char radarData[MAXN][MAXM];
extern RoadMap rdMap;

int CarStatus_Turn;
int CarStatus_Gear;
int CarStatus_Velocity;

string roadmapFile;

#define cdebug(x) cout << #x << " = " << x << endl

int main(int argv, char ** argc) {
  cout << argv << endl;
  if(argv != 2) {											//输入参数为2
    cout << "Usage : ./Trajsender pathfilename " << endl;
    return 0;
  }

  roadmapFile = (string)argc[1];							//地图文件名
  cout << roadmapFile << endl;
  memset(radarData, 0, sizeof(radarData));
  rdMap.readRoadMap(roadmapFile);							//地图数据

  thread rec = thread(zcm_rec);								//通信
  rec.detach();
  thread acc = thread(Acc_func,2,2);						//自适应巡航
  acc.detach();
  run();

  return 0;
}
