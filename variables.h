#ifndef VARIABLES_H
#define VARIABLES_H

#include <iostream>
#include <string>

using namespace std;

#define TOTAL_FLOOR 10 //总层数
#define X 11 //每层的x长度
#define Y 11 //每层的y长度
#define MONSTER_NUM 11 //怪物的数量

#define MOVE_LEFT 0;
#define MOVE_UP 1;
#define MOVE_RIGHT 2;
#define MOVE_DOWN 3;

#define GUI_MODE 1 //是否为图形化界面状态

typedef int FLOOR[X * Y];

struct MONSTER
{
    int hp; //血量
    int atk; //攻击力
    int pdef; //防御力
    int attrib; //怪物属性，如中毒/先攻等
    int exp; //经验值
    int gold; //金币
    int img_y;
    bool boss; //是否为boss
    wstring name; //怪物名称
    string img;
};

class BRAVER
{
public:
    int status; //状态
    int level; //等级
    int hp; //血量
    int atk; //攻击力
    int pdef; //防御力
    int pos_x; //当前x位置
    int pos_y; //当前y位置
    int floor; //当前层数
    int exp; //经验值
    int gold; //金币
    int key1; //钥匙1
    int key2; //钥匙2
    int key3; //钥匙3
    int face; //朝向
    BRAVER();
};

class GLOBAL_VARS
{
public:
    int end_no; //结局编号
    int dialog_no; //对话编号
    int store_no; //商店编号
    wstring gain_item_msg; //获得物品时显示内容
    wstring hint_msg; //提示内容
    int OperationStatus; //操作状态。0为正常游戏中，1为对话框状态，2为游戏结束状态
    int OpenFloor2DoorCnt; //2层和8层的门需要打败一定数量的卫兵才能打开
    int OpenFloor8DoorCnt;
    int BuyTimes; //商店买的次数
    bool BuyKeyInFloor6; //是否在六层买过蓝钥匙
    bool BuyKeyInFloor7; //是否在七层买过黄钥匙
    bool CutInFloor3; //3层被打的转场
    GLOBAL_VARS();
};

extern BRAVER Braver; //勇者的信息
extern MONSTER Monster[MONSTER_NUM]; //怪物的信息
extern FLOOR Tower[TOTAL_FLOOR];
extern GLOBAL_VARS Vars; //一些关键的全局变量

void init_monsters(); //初始化全局变量
void init_tower();

#endif // VARIABLES_H
