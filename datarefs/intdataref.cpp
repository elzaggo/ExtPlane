#include "intdataref.h"
#include "../util/console.h"

IntDataRef::IntDataRef(QObject *parent, QString name, XPLMDataRef ref) : DataRef(parent, name, ref), _value(-999999)
{
    _typeString = "i";
    _type = xplmType_Int;
}

int IntDataRef::value() {
    return _value;
}

void IntDataRef::updateValue() {
   int newValue = XPLMGetDatai(_ref);
    if(_value != newValue) {
        _value = newValue;
        emit changed(this);
    }
}

void IntDataRef::setValue(int newValue) {
    if(!isWritable()) {
        INFO << "Tried to write read-only dataref" << name();
        return;
    }
    DEBUG << name() << newValue;
    _value = newValue;
    XPLMSetDatai(ref(), _value);
    emit changed(this);
}

void IntDataRef::incValue(int deltaValue) {
    if(!isWritable()) {
        INFO << "Tried to write read-only dataref" << name();
        return;
    }
    DEBUG << name() << deltaValue;
    _value += deltaValue;
    XPLMSetDatai(ref(), _value);
    emit changed(this);
}

QString IntDataRef::valueString() {
    return QString::number(value());
}

void IntDataRef::setValue(QString &newValue) {
    bool ok = false;
    int value = newValue.toInt(&ok);
    if(ok) {
        setValue(value);
    } else {
        INFO << "Cannot set value " << newValue;
    }
}

void IntDataRef::incValue(QString &deltaValue) {
    bool ok = false;
    int value = deltaValue.toInt(&ok);
    if(ok) {
        incValue(value);
    } else {
        INFO << "Cannot inc value by " << deltaValue;
    }
}
