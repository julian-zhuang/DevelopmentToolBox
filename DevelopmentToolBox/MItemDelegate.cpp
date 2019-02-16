    #include "MItemDelegate.h"
#include <QModelIndex>
#include <QLineEdit>
#include <qcombobox.h>
#include <qspinbox.h>

MItemDelegate::MItemDelegate()
{
}


MItemDelegate::~MItemDelegate()
{
}

QWidget * MItemDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	if (index.column() == 0) {
		return new QLineEdit(parent);
	}
	if (index.column() == 1) {
		QComboBox *t_Combox = new QComboBox(parent);
		t_Combox->addItem("Str");
		t_Combox->addItem("Int8");
		t_Combox->addItem("Int16");
		t_Combox->addItem("Int32");
		t_Combox->addItem("Int64");
		t_Combox->addItem("UInt8");
		t_Combox->addItem("UInt16");
		t_Combox->addItem("UInt32");
		t_Combox->addItem("UInt64");
		t_Combox->addItem("Real32");
		t_Combox->addItem("Real64");
		return t_Combox;
	}
	if (index.column() == 2) {
		QString t_Str = index.sibling(index.row(), index.column() - 1).data().toString();
		if (t_Str == "Str") {
			return new QLineEdit(parent);
		}
		if (t_Str == "Int8") {
			auto t_Widget = new QSpinBox(parent);
			t_Widget->setRange(-128, 127);
			return t_Widget;
		}
		if (t_Str == "Int16") {
			auto t_Widget = new QSpinBox(parent);
			t_Widget->setRange(-32768, 32767);
			return t_Widget;
		}
		if (t_Str == "Int32") {
			auto t_Widget = new QSpinBox(parent);
			t_Widget->setRange(-2147483648, 2147483647);
			return t_Widget;
		}
		if (t_Str == "UInt8") {
			auto t_Widget = new QSpinBox(parent);
			t_Widget->setRange(0, 255);
			return t_Widget;
		}
		if (t_Str == "UInt16") {
			auto t_Widget = new QSpinBox(parent);
			t_Widget->setRange(0, 65535);
			return t_Widget;
		}
		if (t_Str == "UInt32") {
			auto t_Widget = new QSpinBox(parent);
			t_Widget->setRange(0, 4294967295);
			return t_Widget;
		}
		if (t_Str == "Real32") {
			auto t_Widget = new QDoubleSpinBox(parent);
			t_Widget->setRange(-3.40E+38, 3.40E+38);
			return t_Widget;
		}
		if (t_Str == "Real64") {
			auto t_Widget = new QDoubleSpinBox(parent);
			t_Widget->setRange(-1.79769313486231570E+308, 1.79769313486231570E+308);
			return t_Widget;
		}
	}
	return nullptr;
}

void MItemDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
	if (index.column() == 0) {
		((QLineEdit *)(editor))->setText(index.data(2).toString());
	}
	if (index.column() == 1) {
		((QComboBox *)(editor))->setCurrentText(index.data(Qt::DisplayRole).toString());
	}
	if (index.column() == 2) {
		QString t_Str = index.sibling(index.row(), index.column() - 1).data().toString();
		if (t_Str == "str") {
			((QLineEdit*)editor)->setText(index.data(Qt::DisplayRole).toString());
			return;
		}
		if (t_Str == "Int8") {
			auto t_Widget = new QSpinBox(editor);
			t_Widget->setRange(-128, 127);
			return;
		}
		if (t_Str == "Int16") {
			auto t_Widget = new QSpinBox(editor);
			t_Widget->setRange(-32768, 32767);
			return;
		}
		if (t_Str == "Int32") {
			auto t_Widget = new QSpinBox(editor);
			t_Widget->setRange(-2147483648, 2147483647);
			return;
		}
		if (t_Str == "UInt8") {
			auto t_Widget = new QSpinBox(editor);
			t_Widget->setRange(0, 255);
			return;
		}
		if (t_Str == "UInt16") {
			auto t_Widget = new QSpinBox(editor);
			t_Widget->setRange(0, 65535);
			return;
		}
		if (t_Str == "UInt32") {
			auto t_Widget = new QSpinBox(editor);
			t_Widget->setRange(0, 4294967295);
			return;
		}
		if (t_Str == "Real32") {
			auto t_Widget = new QDoubleSpinBox(editor);
			t_Widget->setRange(-3.40E+38, 3.40E+38);
			return;
		}
		if (t_Str == "Real64") {
			auto t_Widget = new QDoubleSpinBox(editor);
			t_Widget->setRange(-1.79769313486231570E+308, 1.79769313486231570E+308);
			return;
		}
	}
}

void MItemDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
	if (index.column() == 0) {
		model->setData(index, ((QLineEdit *)(editor))->text(), Qt::EditRole);
		return;
	}
	if (index.column() == 1) {
		model->setData(index, ((QComboBox *)(editor))->currentText(), Qt::EditRole);
		return;
	}
	if (index.column() == 2) {
		QString t_Str = index.sibling(index.row(), index.column() - 1).data().toString();
		if (t_Str == "Str") {
			model->setData(index, ((QLineEdit *)(editor))->text(), Qt::EditRole);
			return;
		}
		if (t_Str == "Int8") {
			auto jk = ((QSpinBox *)(editor))->value();
			model->setData(index, QString::number(((QSpinBox *)(editor))->value()), Qt::EditRole);
			return;
		}
		if (t_Str == "Int16") {
			model->setData(index, QString::number(((QSpinBox *)(editor))->value()), Qt::EditRole);
			return;
		}
		if (t_Str == "Int32") {
			model->setData(index, QString::number(((QSpinBox *)(editor))->value()), Qt::EditRole);
			return;
		}
		if (t_Str == "UInt8") {
			model->setData(index, QString::number(((QSpinBox *)(editor))->value()), Qt::EditRole);
			return;
			return;
		}
		if (t_Str == "UInt16") {
			model->setData(index, QString::number(((QSpinBox *)(editor))->value()), Qt::EditRole);
			return;
			return;
		}
		if (t_Str == "UInt32") {
			model->setData(index, QString::number(((QSpinBox *)(editor))->value()), Qt::EditRole);
			return;
			return;
		}
		if (t_Str == "Real32") {
			model->setData(index, QString::number(((QDoubleSpinBox *)(editor))->value()), Qt::EditRole);
			return;
		}
		if (t_Str == "Real64") {
			model->setData(index, QString::number(((QDoubleSpinBox *)(editor))->value()), Qt::EditRole);
			return;
		}
	}
}
