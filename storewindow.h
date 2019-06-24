#ifndef STOREWINDOW_H
#define STOREWINDOW_H

#include <QWidget>
#include <QTimer>
#include <string.h>

using namespace std;

namespace Ui {
class StoreWindow;
}

class StoreWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StoreWindow(QWidget *parent = nullptr);
    ~StoreWindow();

    void Init();
    void OpenStore();
    int choice_num; //有多少个选项
    int target_pos; //商店在楼层中的位置
    Ui::StoreWindow *ui;

protected:
    void keyPressEvent(QKeyEvent *event);

private:

    int border_color_it;
    int choose_no; //选择了第几项

    const string BorderColor[6] = {"FFFFFF", "CCCCCC", "999999", "666666", "999999", "CCCCCC"};
    QTimer* BorderColorTimer;

public slots:
    void OnColorTimerTriggered();
};

extern StoreWindow* wstore;

#endif // STOREWINDOW_H
