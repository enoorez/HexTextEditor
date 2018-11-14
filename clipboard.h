#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>


class Clipboard
{
public:
    Clipboard();
    ~Clipboard();

    static QByteArray getData();

};
#endif // CLIPBOARD_H
