#ifndef MONSTERINFOLISTITEM_H
#define MONSTERINFOLISTITEM_H

#include <QWidget>
#include <QGraphicsView>
#include <QLabel>

class MonsterInfoListItem: public QWidget
{
    Q_OBJECT
public:
    explicit MonsterInfoListItem(QWidget* parent=0);
    QGraphicsView* head;
    QLabel* label_hp;
    QLabel* label_atk;
    QLabel* label_pdef;
    QLabel* label_exp;
    QLabel* label_gold;
    QLabel* label_damage;
    QLabel* label_name_val;
    QLabel* label_hp_val;
    QLabel* label_atk_val;
    QLabel* label_pdef_val;
    QLabel* label_exp_val;
    QLabel* label_gold_val;
    QLabel* label_damage_val;
    void Init();
};

#endif // MONSTERINFOLISTITEM_H
