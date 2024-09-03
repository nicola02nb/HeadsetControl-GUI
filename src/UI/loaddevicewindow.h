#ifndef LOADDEVICEWINDOW_H
#define LOADDEVICEWINDOW_H

#include <QDialog>

namespace Ui {
class loaddevicewindow;
}

class LoaddeviceWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoaddeviceWindow(const QStringList& devices, QWidget *parent = nullptr);
    ~LoaddeviceWindow();

    int getDeviceIndex();  

private:
    Ui::loaddevicewindow *ui;
};

#endif // LOADDEVICEWINDOW_H