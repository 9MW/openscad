#include "parameterspinbox.h"

ParameterSpinBox::ParameterSpinBox(ParameterObject *parameterobject, bool showDescription)
{
	object = parameterobject;
	setName(QString::fromStdString(object->name));
	setValue();
	connect(doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(onChanged(double)));
	if (showDescription == true) {
		setDescription(object->description);
	}
	else {
		doubleSpinBox->setToolTip(object->description);
	}
}

void ParameterSpinBox::onChanged(double)
{
	object->focus = true;
	object->value = ValuePtr(doubleSpinBox->value());
	emit changed();
}

void ParameterSpinBox::setParameterFocus()
{
	this->doubleSpinBox->setFocus();
	object->focus = false;
}

void ParameterSpinBox::setValue()
{
	if (object->values->toDouble() > 0) {
		setPrecision(object->values->toDouble());
		this->doubleSpinBox->setSingleStep(object->values->toDouble());
	}
	else {
		setPrecision(object->defaultValue->toDouble());
		this->doubleSpinBox->setSingleStep(1/pow(10,decimalPrecision));
	}
	this->doubleSpinBox->setDecimals(decimalPrecision);
	this->stackedWidgetRight->setCurrentWidget(this->pageSpin);
	this->stackedWidgetBelow->hide();
	this->doubleSpinBox->setRange(object->value->toDouble()-1000, object->value->toDouble()+1000);
	this->doubleSpinBox->setValue(object->value->toDouble());
}
