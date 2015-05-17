/*
 *  floatarraydataref.h
 *  extplane-plugin
 *
 *  Created by bobgates on 2011/07/23.
 *  Modified by Ville Ranki <ville.ranki@iki.fi>
 */

#ifndef FloatArrayDataRef_H
#define FloatArrayDataRef_H

#include "dataref.h"
#include <QVector>

class FloatArrayDataRef : public DataRef {
    Q_OBJECT
    
public:
    FloatArrayDataRef(QObject *parent, QString name, XPLMDataRef ref);
    ~FloatArrayDataRef();
    QVector<float> & value();
    virtual void updateValue();
    virtual QString valueString();
    virtual void setValue(QString &newValue);
    virtual void incValue(QString &deltaValue);
private:
    QVector<float> _values; // Actual values in a vector
    int _length; // Length of dataref, as given by X-Plane
    float * _valueArray; // Array for reading & writing values. Allocated dynamically.
};

#endif // FloatArrayDataRef_H
