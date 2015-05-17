#include "doubledataref.h"
#include "../util/console.h"

DoubleDataRef::DoubleDataRef(QObject *parent, QString name, XPLMDataRef ref) : DataRef(parent, name, ref), _value(-999999.0f) {
    _typeString = "d";
    _type = xplmType_Double;
}

double DoubleDataRef::value() {
    return _value;
}

void DoubleDataRef::updateValue() {
   double newValue = XPLMGetDatad(_ref);
    if(_value != newValue) {
        _value = newValue;
        emit changed(this);
    }
}

void DoubleDataRef::setValue(double newValue) {
    if(!isWritable()) {
        INFO << "Tried to write read-only dataref" << name();
        return;
    }
    DEBUG << name() << newValue;
    _value = newValue;
    XPLMSetDataf(ref(), _value);
    emit changed(this);
}

void DoubleDataRef::incValue(double deltaValue) {
    if(!isWritable()) {
        INFO << "Tried to write read-only dataref" << name();
        return;
    }
    DEBUG << name() << deltaValue;
    _value += deltaValue;
    XPLMSetDataf(ref(), _value);
    emit changed(this);
}

QString DoubleDataRef::valueString() {
    return QString::number(value(), 'g', 10);
}

void DoubleDataRef::setValue(QString &newValue) {
    bool ok = false;
    double value = newValue.toDouble(&ok);
    if(ok) {
        setValue(value);
    } else {
        INFO << "Cannot set value " << newValue;
    }
}

void DoubleDataRef::incValue(QString &deltaValue) {
    bool ok = false;
    double value = deltaValue.toDouble(&ok);
    if(ok) {
        incValue(value);
    } else {
        INFO << "Cannot increment with " << deltaValue;
    }
}
