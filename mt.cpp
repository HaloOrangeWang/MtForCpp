#include "total.h"

void print_floor()
{
    int x, y;
    system("clear"); //linux
    //system("cls"); //windows
    printf("第%d层\n", Braver.floor);
    printf("等级\t%d\n", Braver.level);
    printf("生命值\t%d\n", Braver.hp);
    printf("攻击力\t%d\n", Braver.atk);
    printf("防御力\t%d\n", Braver.pdef);
    printf("经验\t%d\n", Braver.exp);
    printf("金币\t%d\n", Braver.gold);
    printf("黄锁匙\t%d\n", Braver.key1);
    printf("蓝锁匙\t%d\n", Braver.key2);
    printf("红锁匙\t%d\n", Braver.key3);
    for(x = 0; x <= X+1; x++){
        printf("██");
    }
    printf("\n");
    for(y = 0; y <= Y - 1; y++){
        printf("██");
        for(x=0; x <= X - 1; x++){
            if (Braver.pos_x == x && Braver.pos_y == y)
                printf("△ ");
            else if (Tower[Braver.floor][y * X + x] == 0) //空地
                printf("  ");
            else if (Tower[Braver.floor][y * X + x] >= 1 && Tower[Braver.floor][y * X + x] <= 9) //墙
                printf("□ ");
            else if (Tower[Braver.floor][y * X + x] == 11 || Tower[Braver.floor][y * X + x] == 12) //下楼
                printf("下");
            else if (Tower[Braver.floor][y * X + x] == 10) //上楼
                printf("上");
            else if (Tower[Braver.floor][y * X + x] == 21) //门
                printf("门");
            else if (Tower[Braver.floor][y * X + x] == 31) //黄钥匙
                printf("↑ ");
            else
                printf("%02d", Tower[Braver.floor][y * X + x]);
        }
        printf("██\n");
    }
    for(x = 0; x <= X+1; x++){
        printf("██");
    }
    printf("\n");
}

void game_init()
{
    //初始化楼层信息，主角信息，怪物信息，以及其他全局变量
    init_tower();
    init_monsters();
    Braver = BRAVER();
    Vars = GLOBAL_VARS();

    //画出零层的图像
    if (GUI_MODE == 0)
        print_floor();
}

int calc_damage(int monster_id)
{
    //计算伤害值。值得说明的是，-1表示打不动对方防御，-2表示双方都打不动对方防御
    if (Braver.atk <= Monster[monster_id].pdef)
    {
        if (Monster[monster_id].atk > Braver.pdef)
            return -1;
        else
            return -2;
    }else{
        if (Monster[monster_id].atk > Braver.pdef){
            int atk_times = (Monster[monster_id].hp - 1) / (Braver.atk - Monster[monster_id].pdef);
            return atk_times * (Monster[monster_id].atk - Braver.pdef);
        }else{
            return 0;
        }
    }
}

int handle_keypress(int key_no, int& target_pos, int& old_data)
{
    // 返回操作状态。0为可以操作，1为对话框模式，2为已经game_over, 3为正在开门中, 4为上下楼转场, 5为打开自动战斗画面, 6为打开获得物品界面, 7为开启商店处理, 8为三层被打的转场，9为怪物手册处理
    // 首先找出要移动的目标位置.如果超出了地图范围，则直接返回
    old_data = -1;
    if (key_no == 0) { //向左
        Braver.face = 1; //0/1/2/3分别代表下左右上
        if (Braver.pos_x == 0)
            return 0;
        else
            target_pos = Braver.pos_y * X + (Braver.pos_x - 1);
    }else if (key_no == 1){ //向上
        Braver.face = 3;
        if (Braver.pos_y == 0)
            return 0;
        else
            target_pos = (Braver.pos_y - 1) * X + Braver.pos_x;
    }else if (key_no == 2){ //向右
        Braver.face = 2;
        if (Braver.pos_x == X - 1)
            return 0;
        else
            target_pos = Braver.pos_y * X + (Braver.pos_x + 1);
    }else if (key_no == 3){ //向下
        Braver.face = 0;
        if (Braver.pos_y == Y - 1)
            return 0;
        else
            target_pos = (Braver.pos_y + 1) * X + Braver.pos_x;
    }else{
        return 0;
    }
    old_data = Tower[Braver.floor][target_pos];
    if (Tower[Braver.floor][target_pos] == 0){
        //平地 直接走过去
        Braver.pos_x = target_pos % X;
        Braver.pos_y = target_pos / X;
        return 0;
    }
    else if ((Tower[Braver.floor][target_pos] >= 1 && Tower[Braver.floor][target_pos] <= 9) || Tower[Braver.floor][target_pos] == 41 || Tower[Braver.floor][target_pos] == 43){
        //撞墙 位置不变化
        return 0;
    }
    else if (Tower[Braver.floor][target_pos] == 10){
        //上楼
        if (Braver.floor != TOTAL_FLOOR - 1){
            Braver.floor += 1;
            int target_pos_upper = 0;
            for (int _it = 0; _it <= X * Y - 1; _it++){
                if (Tower[Braver.floor][_it] == 11){
                    target_pos_upper = _it;
                    break;
                }
            }
            Braver.pos_x = target_pos_upper % X;
            Braver.pos_y = target_pos_upper / X;
        }
        return 4;
    }else if (Tower[Braver.floor][target_pos] == 11){
        //下楼
        if (Braver.floor != 0){
            Braver.floor -= 1;
            int target_pos_lower = 0;
            for (int _it = 0; _it <= X * Y - 1; _it++){
                if (Tower[Braver.floor][_it] == 10){
                    target_pos_lower = _it;
                    break;
                }
            }
            Braver.pos_x = target_pos_lower % X;
            Braver.pos_y = target_pos_lower / X;
        }
        return 4;
    }else if (Tower[Braver.floor][target_pos] == 12){
        //触发结局一：离开。直接Game Over
        Vars.end_no = 1;
        Vars.dialog_no = 1;
        //show_dialog();
        return 1;
    }else if (Tower[Braver.floor][target_pos] == 13){
        //3层被打的转场
        Braver.pos_x = target_pos % X;
        Braver.pos_y = target_pos / X;
        Tower[2][6 * X + 4] = 61;
        Tower[2][7 * X + 4] = 60;
        Tower[2][8 * X + 3] = 60;
        Tower[2][8 * X + 5] = 60;
        Tower[2][9 * X + 4] = 60;
        Vars.CutInFloor3 = true;
        return 8;
    }else if (Tower[Braver.floor][target_pos] == 14){
        Vars.hint_msg = L"11层之后的内容，还未制作完成。";
        return 1;
    }else if (Tower[Braver.floor][target_pos] == 21){
        //黄门
        if (Braver.key1 >= 1){
            Braver.key1 -= 1;
            Tower[Braver.floor][target_pos] = 0;
        }
        return 3;
    }else if (Tower[Braver.floor][target_pos] == 22){
        //蓝门
        if (Braver.key2 >= 1){
            Braver.key2 -= 1;
            Tower[Braver.floor][target_pos] = 0;
        }
        return 3;
    }else if (Tower[Braver.floor][target_pos] == 23){
        //红门
        if (Braver.key3 >= 1){
            Braver.key3 -= 1;
            Tower[Braver.floor][target_pos] = 0;
        }
        return 3;
    }else if (Tower[Braver.floor][target_pos] == 24){
        //绿门
        if (Vars.OpenFloor8DoorCnt >= 2){
            Tower[Braver.floor][target_pos] = 0;
        }
        return 3;
    }else if (Tower[Braver.floor][target_pos] == 25){
        //铁门
        if (Vars.OpenFloor2DoorCnt >= 2){
            Tower[Braver.floor][target_pos] = 0;
        }
        return 3;
    }else if (Tower[Braver.floor][target_pos] == 26){
        //暗墙
        Tower[Braver.floor][target_pos] = 0;
        return 3;
    }else if (Tower[Braver.floor][target_pos] == 31){
        //黄钥匙
        Tower[Braver.floor][target_pos] = 0;
        Braver.key1 += 1;
        Vars.gain_item_msg = L"获得了一把黄钥匙";
        return 6;
    }else if (Tower[Braver.floor][target_pos] == 32){
        //蓝钥匙
        Tower[Braver.floor][target_pos] = 0;
        Braver.key2 += 1;
        Vars.gain_item_msg = L"获得了一把蓝钥匙";
        return 6;
    }else if (Tower[Braver.floor][target_pos] == 33){
        //红钥匙
        Tower[Braver.floor][target_pos] = 0;
        Braver.key3 += 1;
        Vars.gain_item_msg = L"获得了一把红钥匙";
        return 6;
    }else if (Tower[Braver.floor][target_pos] == 34){
        //小血瓶
        Tower[Braver.floor][target_pos] = 0;
        Braver.hp += 50;
        Vars.gain_item_msg = L"获得了小血瓶 生命值增加50";
        return 6;
    }else if (Tower[Braver.floor][target_pos] == 35){
        //大血瓶
        Tower[Braver.floor][target_pos] = 0;
        Braver.hp += 200;
        Vars.gain_item_msg = L"获得了大血瓶 生命值增加200";
        return 6;
    }else if (Tower[Braver.floor][target_pos] == 36){
        //红宝石
        Tower[Braver.floor][target_pos] = 0;
        Braver.atk += 1;
        Vars.gain_item_msg = L"攻击力增加1点";
        return 6;
    }else if (Tower[Braver.floor][target_pos] == 37){
        //蓝宝石
        Tower[Braver.floor][target_pos] = 0;
        Braver.pdef += 1;
        Vars.gain_item_msg = L"防御力增加1点";
        return 6;
    }else if (Tower[Braver.floor][target_pos] == 38){
        //铁剑
        Tower[Braver.floor][target_pos] = 0;
        Braver.atk += 10;
        Vars.gain_item_msg = L"获得了铁剑 攻击力增加10点";
        return 6;
    }else if (Tower[Braver.floor][target_pos] == 39){
        //铁盾
        Tower[Braver.floor][target_pos] = 0;
        Braver.pdef += 10;
        Vars.gain_item_msg = L"获得了铁盾 防御力增加10点";
        return 6;
    }else if (Tower[Braver.floor][target_pos] == 42){
        //商店处理
        Vars.store_no = 1;
        return 7;
    }else if (Tower[Braver.floor][target_pos] == 44){
        Vars.hint_msg = L"谢谢你救了我，\n为了感谢你的帮助请收下这些礼物.\n（收到1000金币）";
        Braver.gold += 1000;
        return 1;
    }else if (Tower[Braver.floor][target_pos] == 45){
        //商人处理
        Vars.store_no = 2;
        return 7;
    }else if (Tower[Braver.floor][target_pos] == 46){
        //盗贼处理
        if (target_pos == 6 * X + 2)
            Vars.hint_msg = L"你清醒了吗？你到监狱时还处在昏迷中，\n魔法警卫把你扔到我这个房间。但你很幸运，\n我刚完成逃跑的暗道你就醒了，我们一起越狱吧。";
        else
            Vars.hint_msg = L"我们终于逃出来了。你的剑和盾被警卫拿走了，\n你必须先找到武器。我知道铁剑在5楼，铁盾在9楼，\n你最好先取得它们。我现在有事要做没法帮你，再见。";
        return 1;
    }else if (Tower[Braver.floor][target_pos] == 47){
        Vars.hint_msg = L"有些门不能用钥匙打开。\n只有当你打败它的守卫后才会自动打开。";
        return 1;
    }else if (Tower[Braver.floor][target_pos] == 48){
        //商人处理
        if (Vars.BuyKeyInFloor6 == true)
        {
            Vars.hint_msg = L"魔塔一共50层，每10层为一个区域。\n如果不打败此区域的头目\n就不能到更高的地方";
            return 1;
        }
        else
        {
            Vars.store_no = 3;
            return 7;
        }
    }else if (Tower[Braver.floor][target_pos] == 49){
        Vars.hint_msg = L"你购买了礼物后再与商人对话，\n他会告诉你一些重要的消息。";
        return 1;
    }else if (Tower[Braver.floor][target_pos] == 50){
        //商人处理
        if (Vars.BuyKeyInFloor7 == true)
        {
            Vars.hint_msg = L"在商店里你最好选择提升防御，\n只有在攻击力低于敌人的防御力时才提升攻击力。";
            return 1;
        }
        else
        {
            Vars.store_no = 4;
            return 7;
        }
    }else if (Tower[Braver.floor][target_pos] >= 51){
        //怪物
        int monster_id = Tower[Braver.floor][target_pos] - 51;
        int damage = calc_damage(monster_id);
        if (damage == -2){
            //在打不过时，不进行任何处理
            Vars.hint_msg = L"你还不能打败他";
            return 1;
        }else if (damage == -1 || damage >= Braver.hp){
            //在打不过时，不进行任何处理
            Vars.hint_msg = L"你还不能打败他";
            return 1;
        }else{
            //Braver.hp -= damage;
            //Braver.gold += Monster[monster_id].gold;
            //Braver.exp += Monster[monster_id].exp;
            //Tower[Braver.floor][target_pos] = 0;
            if (monster_id == 6)
                Vars.OpenFloor2DoorCnt += 1;
            if (monster_id == 7)
                Vars.OpenFloor8DoorCnt += 1;
            return 5;
        }
    }
    return 0;
}

void show_dialog()
{
    switch (Vars.dialog_no)
    {
    case 1:
        //结局对话。
        switch(Vars.end_no)
        {
        case 1:
            printf("结局一：离开\n勇士离开了MT\n[1]重新开始\n");
            break;
        case 2:
            printf("结局二：失败\n勇士被击败了\n[1]重新开始\n");
            break;
        }
        break;
    case 2:
        //你还不能打败他.
        printf("你还不能打败他\n[1]确定\n");
        break;
    default:
        break;
    }
}

int handle_dialog(int key_no)
{
    //处理对话框中的按键操作
    //结局对话。当键入1时重新开始游戏
    switch(Vars.dialog_no)
    {
    case 1:
        //结局对话。
        if (key_no == '1') //如果输入了‘1’则重新开始，否则重新输入
            return 2;
        else
            return 1;
    case 2:
        if (key_no == '1')
            return 0;
        else
            return 1;
    default:
        break;
    }
    return 1;
}

void handle_store(int choice_no, int target_pos)
{
    // 商店处理
    int store_price = ((Vars.BuyTimes + 1) * (Vars.BuyTimes + 1) - (Vars.BuyTimes + 1) + 2) * 10;
    switch(Vars.store_no)
    {
    case 1:
        //商店1，第一个提升能力的商店
        if (choice_no == 0 && Braver.gold >= store_price)
        {
            Braver.gold -= store_price;
            Braver.hp += (Vars.BuyTimes + 1) * 100;
            Vars.BuyTimes += 1;
        }else if (choice_no == 1 && Braver.gold >= store_price){
            Braver.gold -= store_price;
            Braver.atk += 2;
            Vars.BuyTimes += 1;
        }else if (choice_no == 2 && Braver.gold >= store_price){
            Braver.gold -= store_price;
            Braver.pdef += 4;
            Vars.BuyTimes += 1;
        }
        break;
    case 2:
        //二层的祝福魔法
        if (choice_no == 0)
        {
            Braver.atk += int(Braver.atk * 0.03);
            Braver.pdef += int(Braver.pdef * 0.03);
            Tower[Braver.floor][target_pos] = 0;
        }
        break;
    case 3:
        //六层的蓝钥匙
        if (choice_no == 0 && Braver.gold >= 50)
        {
            Braver.gold -= 50;
            Braver.key2 += 1;
            Vars.BuyKeyInFloor6 = true;
        }
        break;
    case 4:
        //七层的黄钥匙
        if (choice_no == 0 && Braver.gold >= 50)
        {
            Braver.gold -= 50;
            Braver.key1 += 5;
            Vars.BuyKeyInFloor7 = true;
        }
        break;
    default:
        break;
    }
}

set<int> get_monster_list()
{
    set<int> monster_id_list = set<int>();
    for (int t = 0; t <= X * Y - 1; t++)
    {
        if (Tower[Braver.floor][t] >= 51)
        {
            if (monster_id_list.find(Tower[Braver.floor][t] - 51) == monster_id_list.end())
                monster_id_list.insert(Tower[Braver.floor][t] - 51);
        }
    }
    return monster_id_list;
}
