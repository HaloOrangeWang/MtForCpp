#ifndef MT_H
#define MT_H

#include <set>
using namespace std;

void game_init(); //游戏开始
void game_over(); //游戏结束
int calc_damage(int monster_id); //计算伤害
int handle_keypress(int key_no, int& target_pos, int& old_data); //对一个按键的处理判断

void print_floor(); //打印一层中的场景

void show_dialog();
void handle_store(int choice_no, int target_pos);
int handle_dialog(int key_no);
set<int> get_monster_list();

#endif // MT_H
