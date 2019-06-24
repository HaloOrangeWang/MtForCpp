#include "total.h"

StoreWindow* wstore;

StoreWindow::StoreWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StoreWindow)
{
    ui->setupUi(this);
    Init();

    border_color_it = 0;
    choice_num = 4;
    target_pos = -1;
    choose_no = 0;
}

void StoreWindow::Init()
{
    this->setFocusPolicy(Qt::StrongFocus);

    ui->graphicsView_2->setStyleSheet("border:3px solid #FFFFFF;");
    ui->graphicsView_2->setFocusPolicy(Qt::NoFocus);

    ui->label->setFocusPolicy(Qt::NoFocus);
    ui->label_2->setFocusPolicy(Qt::NoFocus);
    ui->label_3->setFocusPolicy(Qt::NoFocus);
    ui->label_4->setFocusPolicy(Qt::NoFocus);
    ui->label_5->setFocusPolicy(Qt::NoFocus);
    ui->label_6->setFocusPolicy(Qt::NoFocus);

    BorderColorTimer = new QTimer();
    connect(BorderColorTimer, SIGNAL(timeout()), this, SLOT(OnColorTimerTriggered()));
    BorderColorTimer->start(100);
}

void StoreWindow::OpenStore()
{
    choose_no = 0;
    ui->graphicsView_2->setGeometry(32, 112, 192, 32);
}

void StoreWindow::OnColorTimerTriggered()
{
    if (border_color_it <= 4)
        border_color_it++;
    else
        border_color_it = 0;

    ui->graphicsView_2->setStyleSheet(QString::fromStdString("border:3px solid #") + QString::fromStdString(BorderColor[border_color_it]) + QString::fromStdString(";"));
}

void StoreWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up){ //向上
        if (choose_no > 0)
        {
            choose_no -= 1;
            ui->graphicsView_2->setGeometry(32, 112 + 48 * choose_no, 192, 32);
        }
        else
            choose_no = 0;
    }else if (event->key() == Qt::Key_Down){ //向下
        if (choose_no <= choice_num - 2)
        {
            choose_no += 1;
            ui->graphicsView_2->setGeometry(32, 112 + 48 * choose_no, 192, 32);
        }
        else
            choose_no = choice_num - 1;
    }else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Space){
        if (choose_no != choice_num - 1)
        {
            handle_store(choose_no, target_pos);

            if (Vars.store_no == 1)
            {
                int store_price = ((Vars.BuyTimes + 1) * (Vars.BuyTimes + 1) - (Vars.BuyTimes + 1) + 2) * 10;
                ui->label->setText(QString::fromStdWString(L"你若给我 ") + QString::number(store_price) + QString::fromStdWString(L" 个金币"));
                ui->label_2->setText(" ");
                ui->label_7->setText(QString::fromStdWString(L"我就可以帮你"));
                ui->label_8->setText(" ");
                ui->label_3->setText(QString::fromStdWString(L"提升 ") + QString::number(100 * (Vars.BuyTimes + 1)) + QString::fromStdWString(L" 点生命"));
                ui->label_4->setText(QString::fromStdWString(L"提升 2 点攻击力"));
                ui->label_5->setText(QString::fromStdWString(L"提升 4 点防御力"));
                ui->label_6->setText(QString::fromStdWString(L"离开商店"));
            }
            if (Vars.store_no >= 2) //一次性的商店。买完后窗口直接关闭
            {
                this->close();
                Vars.OperationStatus = 0; //恢复主塔操作
            }
        }else{
            this->close();
            Vars.OperationStatus = 0; //恢复主塔操作
        }
    }
}

StoreWindow::~StoreWindow()
{
    delete ui;
}
