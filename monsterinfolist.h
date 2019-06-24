#ifndef MONSTERINFOLIST_H
#define MONSTERINFOLIST_H

#include <QListWidget>
#include <QPalette>

class MonsterInfoList: public QListWidget
{
    Q_OBJECT
public:
    explicit MonsterInfoList(QListWidget *person=0);
    //void Init();
    QListWidgetItem *currentItem; //当前的项
    void addItem(int monster_id); //在列表中新加一项

private:
    int item_index;
};

#endif // MONSTERINFOLIST_H
