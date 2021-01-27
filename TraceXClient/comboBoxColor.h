#ifndef COMBOBOXCOLOR_H
#define COMBOBOXCOLOR_H

#include <QComboBox>

class ComboBoxColor : public QComboBox
{
public:
    ComboBoxColor(QWidget *parent = nullptr);

private:
    QComboBox *cbColor;
    QPixmap *pixmap[8];
};

#endif // COMBOBOXCOLOR_H
