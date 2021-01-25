#ifndef COMBOBOXCOLOR_H
#define COMBOBOXCOLOR_H

#include <QObject>
#include <QWidget>
#include <QComboBox>

class ComboBoxColor : public QComboBox
{
public:
    ComboBoxColor(QWidget *parent = nullptr);

    QComboBox *cbColor;
    QPixmap *pixmap[8];
};

#endif // COMBOBOXCOLOR_H
