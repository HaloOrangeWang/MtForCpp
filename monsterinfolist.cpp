#include "total.h"

MonsterInfoList::MonsterInfoList(QListWidget *parent): QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus); //去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //水平滚动条关闭
    //设置列表样式
    this->setStyleSheet("QListWidget{\
                        background:black;\
                        color:white;\
                        border:none;\
                    }\
                    QListWidget::item{\
                        border:none;\
                            height: 110px;\
                    }\
                    QScrollBar:vertical {\
                        background:transparent;\
                        width:9px;\
                        margin: 0px 0px 2px 0px;\
                    }\
                    QScrollBar::handle:vertical {\
                        background: rgb(195, 195, 195);\
                        min-height: 20px;\
                        border-radius: 3px;\
                    }\
                    QScrollBar::handle:vertical:hover{\
                        background:rgba(0,0,0,30%);\
                    }\
                    QScrollBar::add-line:vertical {\
                        height: 0px;\
                        subcontrol-position: bottom;\
                        subcontrol-origin: margin;\
                    }\
                    QScrollBar::sub-line:vertical {\
                        height: 0px;\
                        subcontrol-position: top;\
                        subcontrol-origin: margin;\
                    }");
    item_index = 0;
}

void MonsterInfoList::addItem(int monster_id){
    MonsterInfoListItem* message_list_item = new MonsterInfoListItem(); //创建一个自己定义的消息类

    QPalette pal(message_list_item->palette());
    if (item_index % 2 == 0)
        pal.setColor(QPalette::Base, "#000000");
    else
        pal.setColor(QPalette::Base, "#444444");
    message_list_item->setAutoFillBackground(true);
    message_list_item->setPalette(pal);
    item_index++;

    message_list_item->Init();
    message_list_item->label_hp_val->setText(QString::number(Monster[monster_id].hp));
    message_list_item->label_name_val->setText(QString::fromStdWString(Monster[monster_id].name));
    message_list_item->label_atk_val->setText(QString::number(Monster[monster_id].atk));
    message_list_item->label_pdef_val->setText(QString::number(Monster[monster_id].pdef));
    message_list_item->label_exp_val->setText(QString::number(Monster[monster_id].exp));
    message_list_item->label_gold_val->setText(QString::number(Monster[monster_id].gold));
    int exp_damage = calc_damage(monster_id);
    if (exp_damage >= 0)
        message_list_item->label_damage_val->setText(QString::number(exp_damage));
    else {
        message_list_item->label_damage_val->setText("?????");
    }

    QGraphicsScene *scene_m = new QGraphicsScene;
    scene_m->addPixmap(QPixmap::fromImage(QImage(Monster[monster_id].img.c_str()).copy(0, Monster[monster_id].img_y, 32, 32)));
    message_list_item->head->setScene(scene_m);
    message_list_item->head->show();
    message_list_item->head->setStyleSheet("background:transparent;border:none;");

    QListWidgetItem* newItem = new QListWidgetItem();
    this->insertItem(0, newItem);
    this->setItemWidget(newItem, message_list_item); //将buddy赋给该newItem
    newItem->setHidden(false);
}
