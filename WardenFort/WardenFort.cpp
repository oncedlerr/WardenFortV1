#include "WardenFort.h"
#include "ui_WardenFort.h"
#include <pcap.h>

WardenFort::WardenFort(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::WardenFort)
{
    ui->setupUi(this);
}

void WardenFort::setLabelText(const QString& text) {
    ui->label->setText(text); // Set text of the label
}

WardenFort::~WardenFort()
{
    delete ui;
}

void WardenFort::on_comboBox_activated(int index)
{
    // Implement the slot functionality here
}

void WardenFort::on_pushButton_clicked()
{
    // Implement the push button click functionality here
}
