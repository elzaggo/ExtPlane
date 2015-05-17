#ifndef FLOATDATAREF_H
#define FLOATDATAREF_H

#include "dataref.h"

class FloatDataRef : public DataRef {
    Q_OBJECT

public:
    FloatDataRef(QObject *parent, QString name, XPLMDataRef ref);
    float value();
    void setValue(float newValue);
    void incValue(float deltaValue);
    virtual void updateValue();
    virtual QString valueString();
    virtual void setValue(QString &newValue);
    virtual void incValue(QString &deltaValue);
private:
    float _value;
};

#endif // FLOATDATAREF_H
