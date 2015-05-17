#ifndef DOUBLEDATAREF_H
#define DOUBLEDATAREF_H

#include "dataref.h"

class DoubleDataRef : public DataRef {
    Q_OBJECT

public:
    DoubleDataRef(QObject *parent, QString name, XPLMDataRef ref);
    double value();
    void setValue(double newValue);
    void incValue(double deltaValue);
    virtual void updateValue();
    virtual QString valueString();
    virtual void setValue(QString &newValue);
    virtual void incValue(QString &deltaValue);
private:
    double _value;
};

#endif // DOUBLEDATAREF_H
