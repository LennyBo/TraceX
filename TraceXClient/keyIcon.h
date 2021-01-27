#ifndef KEYICON_H
#define KEYICON_H

#include <QWidget>

class QLabel;
class QHBoxLayout;

class KeyIcon : public QWidget
{
    Q_OBJECT
public:
    KeyIcon(int keyGroup, QWidget *parent = nullptr);

private:
    QHBoxLayout *layout;
    QLabel *lblKey1, *lblKey2;
};

#endif // KEYICON_H
