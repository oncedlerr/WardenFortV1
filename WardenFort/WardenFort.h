#ifndef WARDENFORT_H
#define WARDENFORT_H

#include <QMainWindow>
#include <pcap.h>

QT_BEGIN_NAMESPACE
namespace Ui {
    class WardenFort;
}
QT_END_NAMESPACE

class WardenFort : public QMainWindow
{
    Q_OBJECT

public:
    WardenFort(QWidget* parent = nullptr);
    ~WardenFort();
    void setLabelText(const QString& text); // Method to set the label text

private slots:
    void on_comboBox_activated(int index);
    void on_pushButton_clicked();

private:
    Ui::WardenFort* ui;
};
#endif // WARDENFORT_H
