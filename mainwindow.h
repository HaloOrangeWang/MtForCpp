#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QMessageBox>
#include "variables.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void LoadImageBeforeGame(); //初始化一些设置（如信号插槽等）
    void InitGraphics(); //初始化主界面
    void DisplayFloor(int floor); //展示楼层信息
    void DisplayData(); //展示状态数据
    void GameStart(); //游戏内容的初始化

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    int display_it;
    int opendoor_it;
    int updown_it;
    int fight_period_it;
    int fight_end_it;
    int gain_item_it;
    int OpenDoorTargetPos;
    int OpenDoorTempData;
    int FightTargetPos;
    int MonsterIDTemp;
    int OldFloor;

    int keyUpCnt; //按键松开的时间

    QTimer* NormalTimer; //层内动态效果的定时器
    QTimer* OpenDoorTimer; //播放开门动画的定时器
    QTimer* CutTimer; //转场动画的计时器
    QTimer* FightTimer; //战斗的计时器
    QTimer* GainItemTimer; //获得物品的计时器

    QImage ImgWall;
    QImage ImgUpstairs;
    QImage ImgDownstairs;
    QImage ImgYDoor[4];
    QImage ImgBDoor[4];
    QImage ImgRDoor[4];
    QImage ImgGDoor[4];
    QImage ImgIDoor[4];
    QImage ImgFalseWall[4];
    QImage ImgMonsters[MONSTER_NUM][4];
    QImage ImgBraver[4][2];
    QImage ImgStoreLeft;
    QImage ImgStoreMiddle[4];
    QImage ImgStoreRight;
    QImage ImgYKey;
    QImage ImgBKey;
    QImage ImgRKey;
    QImage ImgBottle1;
    QImage ImgBottle2;
    QImage ImgRGem;
    QImage ImgBGem;
    QImage ImgSword;
    QImage ImgShield;
    QImage ImgNpcOld[4];
    QImage ImgNpcRed[4];
    QImage ImgNpcThief[4];

    QGraphicsScene *scene_m;
    QGraphicsScene *scene_b;
    QGraphicsScene *scene_store;
    QGraphicsScene *scene_floor;
    QGraphicsPixmapItem **pixmap_items;

    void HideFightWindow();

public slots:
    void OnNormalTimerTriggered();
    void OnOpenDoorTimerTriggered();
    void OnCutTimerTriggered();
    void OnFightTimerTriggered();
    void OnGainItemTimerTriggered();
};

#endif // MAINWINDOW_H
