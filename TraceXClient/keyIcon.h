#ifndef KEYICON_H
#define KEYICON_H

#include <QWidget>

class QLabel;
class QHBoxLayout;

class KeyIcon : public QWidget
{
    Q_OBJECT
public:
    explicit KeyIcon(int keyGroup, QWidget *parent = nullptr);

    QLabel *lblKey1, *lblKey2;
    QHBoxLayout *layout;
};

#endif // KEYICON_H
