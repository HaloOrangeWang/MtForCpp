#include "total.h"

MonsterInfoListItem::MonsterInfoListItem(QWidget *parent): QWidget(parent)
{

}

void MonsterInfoListItem::Init()
{
    //初始化
    head = new QGraphicsView(this);
    label_hp = new QLabel(this);
    label_atk = new QLabel(this);
    label_pdef = new QLabel(this);
    label_exp = new QLabel(this);
    label_gold = new QLabel(this);
    label_damage = new QLabel(this);
    label_name_val = new QLabel(this);
    label_hp_val = new QLabel(this);
    label_atk_val = new QLabel(this);
    label_pdef_val = new QLabel(this);
    label_exp_val = new QLabel(this);
    label_gold_val = new QLabel(this);
    label_damage_val = new QLabel(this);

    //设置颜色，对齐方式
    label_hp->setStyleSheet("color:#cccccc;");
    label_hp->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_hp->setFixedSize(64, 20);
    label_hp->setText(QString::fromStdWString(L"生命值"));
    label_atk->setStyleSheet("color:#cccccc;");
    label_atk->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_atk->setFixedSize(64, 20);
    label_atk->setText(QString::fromStdWString(L"攻击力"));
    label_pdef->setStyleSheet("color:#cccccc;");
    label_pdef->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_pdef->setFixedSize(64, 20);
    label_pdef->setText(QString::fromStdWString(L"防御力"));
    label_exp->setStyleSheet("color:#cccccc;");
    label_exp->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_exp->setFixedSize(64, 20);
    label_exp->setText(QString::fromStdWString(L"经验"));
    label_gold->setStyleSheet("color:#cccccc;");
    label_gold->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_gold->setFixedSize(64, 20);
    label_gold->setText(QString::fromStdWString(L"金币"));
    label_damage->setStyleSheet("color:#cccccc;");
    label_damage->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_damage->setFixedSize(64, 20);
    label_damage->setText(QString::fromStdWString(L"预期伤害"));
    label_name_val->setStyleSheet("color:#ffffff;");
    label_name_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_name_val->setFixedSize(96, 20);
    label_hp_val->setStyleSheet("color:#ffffff;");
    label_hp_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_hp_val->setFixedSize(64, 20);
    label_atk_val->setStyleSheet("color:#ffffff;");
    label_atk_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_atk_val->setFixedSize(64, 20);
    label_pdef_val->setStyleSheet("color:#ffffff;");
    label_pdef_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_pdef_val->setFixedSize(64, 20);
    label_exp_val->setStyleSheet("color:#ffffff;");
    label_exp_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_exp_val->setFixedSize(64, 20);
    label_gold_val->setStyleSheet("color:#ffffff;");
    label_gold_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_gold_val->setFixedSize(64, 20);
    label_damage_val->setStyleSheet("color:#ffffff;");
    label_damage_val->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_damage_val->setFixedSize(64, 20);

    //设置头像大小
    head->setFixedSize(34,34);

    //布局
    head->move(32, 32);
    label_hp->move(110, 6);
    label_atk->move(190, 6);
    label_pdef->move(270, 6);
    label_name_val->move(0, 64);
    label_hp_val->move(110, 26);
    label_atk_val->move(190, 26);
    label_pdef_val->move(270, 26);
    label_exp->move(110, 62);
    label_gold->move(190, 62);
    label_damage->move(270, 62);
    label_exp_val->move(110, 82);
    label_gold_val->move(190, 82);
    label_damage_val->move(270, 82);

    //加载事件过滤器
    head->installEventFilter(this);
}
