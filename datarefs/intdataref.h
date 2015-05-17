#ifndef INTDATAREF_H
#define INTDATAREF_H

#include "dataref.h"

class IntDataRef : public DataRef {
    Q_OBJECT

public:
    IntDataRef(QObject *parent, QString name, XPLMDataRef ref);
    int value();
    void setValue(int newValue);
    void incValue(int deltaValue);
    virtual void updateValue();
    virtual QString valueString();
    virtual void setValue(QString &newValue);
    virtual void incValue(QString &deltaValue);
private:
    int _value;
};

#endif // INTDATAREF_H
