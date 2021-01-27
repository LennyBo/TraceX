#include "comboboxcolor.h"

#include "constants.h"

ComboBoxColor::ComboBoxColor(QWidget *parent) : QComboBox(parent)
{
    this->addItem("Choisir une couleur");
    for(int i = 0; i < NUMBER_COLORS; i++)
    {
        pixmap[i] = new QPixmap(15,15);
        pixmap[i]->fill(QColor(COLORS[i]));        
        this->addItem("");
        this->setItemData(i,*pixmap[i],Qt::DecorationRole);
    }
}
