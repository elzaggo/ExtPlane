#include "floatdataref.h"
#include "../util/console.h"

FloatDataRef::FloatDataRef(QObject *parent, QString name, XPLMDataRef ref) : DataRef(parent, name, ref), _value(-999999.0f) {
    _typeString = "f";
    _type = xplmType_Float;
}

float FloatDataRef::value() {
    return _value;
}

void FloatDataRef::updateValue() {
   float newValue = XPLMGetDataf(_ref);
    if(_value != newValue) {
        _value = newValue;
        emit changed(this);
    }
}

void FloatDataRef::setValue(float newValue) {
    if(!isWritable()) {
        INFO << "Tried to write read-only dataref" << name();
        return;
    }
    _value = newValue;
    XPLMSetDataf(ref(), _value);
    emit changed(this);
}

void FloatDataRef::incValue(float deltaValue) {
    if(!isWritable()) {
        INFO << "Tried to write read-only dataref" << name();
        return;
    }
    _value += deltaValue;
    XPLMSetDataf(ref(), _value);
    emit changed(this);
}

QString FloatDataRef::valueString() {
    return QString::number(value(), 'g', 10);
}

void FloatDataRef::setValue(QString &newValue) {
    bool ok = false;
    float value = newValue.toFloat(&ok);
    if(ok) {
        setValue(value);
    } else {
        INFO << "Cannot set value " << newValue;
    }
}

void FloatDataRef::incValue(QString &deltaValue) {
    bool ok = false;
    float value = deltaValue.toFloat(&ok);
    if(ok) {
        incValue(value);
    } else {
        INFO << "Cannot increment with value " << deltaValue;
    }
}
