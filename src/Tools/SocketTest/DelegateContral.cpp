#include <QtDebug>
#include <QSpinBox>
#include <QVariant>
#include <QComboBox>
#include <QLineEdit>
#include <limits>

#include "DelegateContral.h"

CustomDelegate::CustomDelegate(QObject *parent):QStyledItemDelegate (parent)
{
    m_ctrlType = E_USER_DATA::E_DEFAULT_CTRL;
    m_dataType = E_USER_DATA::E_DEFAULT_CTRL;
    DatTypes.clear();
    DatTypes.append("Str");
    DatTypes.append("Bool");
    DatTypes.append("Int8");
    DatTypes.append("Int16");
    DatTypes.append("Int32");
    DatTypes.append("Int64");
    DatTypes.append("UInt8");
    DatTypes.append("UInt16");
    DatTypes.append("UInt32");
    DatTypes.append("UInt64");
    DatTypes.append("Float");
    DatTypes.append("Double");
    m_ReadOnlyMode = false;
}

CustomDelegate::~CustomDelegate()
{

}

QWidget *CustomDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int Col = index.column();
    int Row = index.row();

    if (m_ReadOnlyMode == true && Col != 3){
        return nullptr;
    }

    m_ctrlType = index.model()->data(index, E_ROLE_TYPE::E_CTRL_ROLE).value<E_USER_DATA>();
    m_dataType = index.model()->data(index, E_ROLE_TYPE::E_USER_DATA_ROLE).value<E_USER_DATA>();

    QWidget *ReturnPoint = nullptr;
    if (Col == 0){
        QLineEdit *pLineEdit = new QLineEdit(parent);
        ReturnPoint = pLineEdit;
    }
    if (Col == 1){
        QComboBox *pComBox = new QComboBox(parent);
        ReturnPoint = pComBox;
    }
    if (Col == 2){
        if (index.sibling(Row,1).data().toString() == "Str"){
            QSpinBox *pSpinBox = new QSpinBox(parent);
            pSpinBox->setMinimum(0);
            pSpinBox->setMaximum(INT_MAX);
            ReturnPoint = pSpinBox;
        }
    }
    if (Col == 3){
        QString TypeStr = index.sibling(Row,1).data().toString();
        if (TypeStr == "Str"){
            QLineEdit *pLineEdit = new QLineEdit(parent);
            ReturnPoint = pLineEdit;
        }
        if (TypeStr == "Bool"){
            QComboBox *pComBox = new QComboBox(parent);
            ReturnPoint = pComBox;
        }
        if (TypeStr == "Int8"){
            QSpinBox *pSpinBox = new QSpinBox(parent);
            ReturnPoint = pSpinBox;
        }
        if (TypeStr == "Int16"){
            QSpinBox *pSpinBox = new QSpinBox(parent);
            ReturnPoint = pSpinBox;
        }
        if (TypeStr == "Int32"){
            QSpinBox *pSpinBox = new QSpinBox(parent);
            ReturnPoint = pSpinBox;
        }
        if (TypeStr == "Int64"){
            QDoubleSpinBox *pDoubleSpinBox = new QDoubleSpinBox(parent);
            ReturnPoint = pDoubleSpinBox;
        }
        if (TypeStr == "UInt8"){
            QSpinBox *pSpinBox = new QSpinBox(parent);
            ReturnPoint = pSpinBox;
        }
        if (TypeStr == "UInt16"){
            QSpinBox *pSpinBox = new QSpinBox(parent);
            ReturnPoint = pSpinBox;
        }
        if (TypeStr == "UInt32"){
            QDoubleSpinBox *pDoubleSpinBox = new QDoubleSpinBox(parent);
            ReturnPoint = pDoubleSpinBox;
        }
        if (TypeStr == "UInt64"){
            QDoubleSpinBox *pDoubleSpinBox = new QDoubleSpinBox(parent);
            ReturnPoint = pDoubleSpinBox;
        }
        if (TypeStr == "Float"){
            QDoubleSpinBox *pDoubleSpinBox = new QDoubleSpinBox(parent);
            ReturnPoint = pDoubleSpinBox;
        }
        if (TypeStr == "Double"){
            QDoubleSpinBox *pDoubleSpinBox = new QDoubleSpinBox(parent);
            pDoubleSpinBox = pDoubleSpinBox;
        }
    }
    if (Col == 4){
        QLineEdit *pLineEdit = new QLineEdit(parent);
        ReturnPoint = pLineEdit;
    }
    return ReturnPoint;
}

void CustomDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int Col = index.column();
    int Row = index.row();

    if( Col == 0){
        QLineEdit *pLineEdit = (QLineEdit*)(editor);
        pLineEdit->setText(index.data().toString());

    }
    if( Col == 1){
        QComboBox *pComBox = (QComboBox*)(editor);
        pComBox->addItems(DatTypes);
        pComBox->setCurrentText(index.data().toString());
    }
    if( Col == 2){
        QSpinBox *pSpinBox = (QSpinBox*)(editor);
        pSpinBox->setValue(index.data().toString().toUInt());
    }
    if( Col == 3){
        QString TypeStr = index.sibling(Row,1).data().toString();
        if (TypeStr == "Str"){
            QLineEdit *pLineEdit =  (QLineEdit*)(editor);
            pLineEdit->setMaxLength(index.sibling(Row,2).data().toString().toUInt());
            pLineEdit->setText(index.data().toString());
        }
        if (TypeStr == "Bool"){
            QComboBox *pComBox =  (QComboBox*)(editor);
            pComBox->addItem("1");
            pComBox->addItem("0");
            pComBox->setCurrentText(index.data().toString());
        }
        if (TypeStr == "Int8"){
            QSpinBox *pSpinBox =  (QSpinBox*)(editor);
            pSpinBox->setMinimum(std::numeric_limits<char>::min());
            pSpinBox->setMaximum(std::numeric_limits<char>::max());
            pSpinBox->setValue(index.data().toString().toInt());
        }
        if (TypeStr == "Int16"){
            QSpinBox *pSpinBox = (QSpinBox*)(editor);
            pSpinBox->setMinimum(std::numeric_limits<short>::min());
            pSpinBox->setMaximum(std::numeric_limits<short>::max());
            pSpinBox->setValue(index.data().toString().toInt());
        }
        if (TypeStr == "Int32"){
            QSpinBox *pSpinBox = (QSpinBox*)(editor);
            pSpinBox->setMinimum(std::numeric_limits<int>::min());
            pSpinBox->setMaximum(std::numeric_limits<int>::max());
            pSpinBox->setValue(index.data().toString().toInt());
        }
        if (TypeStr == "Int64"){
            QDoubleSpinBox *pDoubleSpinBox = (QDoubleSpinBox*)(editor);
            pDoubleSpinBox->setDecimals(0);
            pDoubleSpinBox->setMinimum(std::numeric_limits<long long int>::min());
            pDoubleSpinBox->setMaximum(std::numeric_limits<long long int>::max());
            pDoubleSpinBox->setValue(index.data().toString().toLongLong());
        }
        if (TypeStr == "UInt8"){
            QSpinBox *pSpinBox = (QSpinBox*)(editor);
            pSpinBox->setMinimum(std::numeric_limits<unsigned char>::min());
            pSpinBox->setMaximum(std::numeric_limits<unsigned char>::min());
            pSpinBox->setValue(index.data().toString().toUInt());
        }
        if (TypeStr == "UInt16"){
            QSpinBox *pSpinBox = (QSpinBox*)(editor);
            pSpinBox->setMinimum(std::numeric_limits<unsigned short>::min());
            pSpinBox->setMaximum(std::numeric_limits<unsigned short>::min());
            pSpinBox->setValue(index.data().toString().toUInt());
        }
        if (TypeStr == "UInt32"){
            QDoubleSpinBox *pDoubleSpinBox = (QDoubleSpinBox*)(editor);
            pDoubleSpinBox->setDecimals(0);
            pDoubleSpinBox->setMinimum(std::numeric_limits<unsigned int>::min());
            pDoubleSpinBox->setMaximum(std::numeric_limits<unsigned int>::min());
            pDoubleSpinBox->setValue(index.data().toString().toUInt());
        }
        if (TypeStr == "UInt64"){
            QDoubleSpinBox *pDoubleSpinBox = (QDoubleSpinBox*)(editor);
            pDoubleSpinBox->setDecimals(0);
            pDoubleSpinBox->setMinimum(std::numeric_limits<unsigned long long int>::min());
            pDoubleSpinBox->setMaximum(std::numeric_limits<unsigned long long int>::min());
            pDoubleSpinBox->setValue(index.data().toString().toULongLong());
        }
        if (TypeStr == "Float"){
            QDoubleSpinBox *pDSpinBox = (QDoubleSpinBox*)(editor);
            pDSpinBox->setMinimum(std::numeric_limits<float>::min());
            pDSpinBox->setMaximum(std::numeric_limits<float>::max());
            pDSpinBox->setDecimals(2);
            pDSpinBox->setValue(index.data().toString().toFloat());
        }
        if (TypeStr == "Double"){
            QDoubleSpinBox *pDoubleSpinBox =  (QDoubleSpinBox*)(editor);
            pDoubleSpinBox->setMinimum(std::numeric_limits<double>::min());
            pDoubleSpinBox->setMaximum(std::numeric_limits<double>::max());
            pDoubleSpinBox->setDecimals(5);
            pDoubleSpinBox->setValue(index.data().toString().toDouble());
        }
    }
    if( Col == 4){
        QLineEdit *pLineEdit = (QLineEdit*)(editor);
        pLineEdit->setText(index.data().toString());
    }
    return;
}

void CustomDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int Col = index.column();
    int Row = index.row();

    if( Col == 0){
        QLineEdit *pLineEdit = (QLineEdit*)(editor);
        model->setData(index,pLineEdit->text(),Qt::EditRole);
    }
    if( Col == 1){
        QComboBox *pComBox = (QComboBox*)(editor);
        model->setData(index,pComBox->currentText(),Qt::EditRole);
        if (pComBox->currentText() == "Str"){
            model->setData(index.sibling(Row,2),"1");
        }
        if (pComBox->currentText() == "Bool"){
            model->setData(index.sibling(Row,2),"1");
        }
        if (pComBox->currentText() == "Int8"){
            model->setData(index.sibling(Row,2),"1");
        }
        if (pComBox->currentText() == "Int16"){
            model->setData(index.sibling(Row,2),"2");
        }
        if (pComBox->currentText() == "Int32"){
            model->setData(index.sibling(Row,2),"4");
        }
        if (pComBox->currentText() == "Int64"){
            model->setData(index.sibling(Row,2),"8");
        }
        if (pComBox->currentText() == "UInt8"){
            model->setData(index.sibling(Row,2),"1");
        }
        if (pComBox->currentText() == "UInt16"){
            model->setData(index.sibling(Row,2),"2");
        }
        if (pComBox->currentText() == "UInt32"){
            model->setData(index.sibling(Row,2),"4");
        }
        if (pComBox->currentText() == "UInt64"){
            model->setData(index.sibling(Row,2),"8");
        }
        if (pComBox->currentText() == "Float"){
            model->setData(index.sibling(Row,2),"4");
        }
        if (pComBox->currentText() == "Double"){
            model->setData(index.sibling(Row,2),"8");
        }
    }
    if( Col == 2){
        QSpinBox *pSpinBox = (QSpinBox*)(editor);
        model->setData(index,QString::number(pSpinBox->value()),Qt::EditRole);
    }
    if( Col == 3){
        QString TypeStr = index.sibling(Row,1).data().toString();
        if (TypeStr == "Str"){
            QLineEdit *pLineEdit =  (QLineEdit*)(editor);
            model->setData(index,pLineEdit->text(),Qt::EditRole);
        }
        if (TypeStr == "Bool"){
            QComboBox *pComBox =  (QComboBox*)(editor);
            model->setData(index,pComBox->currentText(),Qt::EditRole);
        }
        if (TypeStr == "Int8"){
            QSpinBox *pSpinBox =  (QSpinBox*)(editor);
            model->setData(index,pSpinBox->value(),Qt::EditRole);
        }
        if (TypeStr == "Int16"){
            QSpinBox *pSpinBox = (QSpinBox*)(editor);
            model->setData(index,pSpinBox->value(),Qt::EditRole);
        }
        if (TypeStr == "Int32"){
            QSpinBox *pSpinBox = (QSpinBox*)(editor);
            model->setData(index,pSpinBox->value(),Qt::EditRole);
        }
        if (TypeStr == "Int64"){
            QDoubleSpinBox *pDoubleSpinBox = (QDoubleSpinBox*)(editor);
            model->setData(index,QString::number(pDoubleSpinBox->value(),'f',0), Qt::EditRole);
        }
        if (TypeStr == "UInt8"){
            QSpinBox *pSpinBox = (QSpinBox*)(editor);
            model->setData(index,pSpinBox->value(),Qt::EditRole);
        }
        if (TypeStr == "UInt16"){
            QSpinBox *pSpinBox = (QSpinBox*)(editor);
            model->setData(index,pSpinBox->value(),Qt::EditRole);
        }
        if (TypeStr == "UInt32"){
            QDoubleSpinBox *pDoubleSpinBox = (QDoubleSpinBox*)(editor);
            model->setData(index,pDoubleSpinBox->value(),Qt::EditRole);
        }
        if (TypeStr == "UInt64"){
            QDoubleSpinBox *pDoubleSpinBox = (QDoubleSpinBox*)(editor);
            model->setData(index,QString::number(pDoubleSpinBox->value(),'f',0), Qt::EditRole);
        }
        if (TypeStr == "Float"){
            QDoubleSpinBox *pDoubleSpinBox = (QDoubleSpinBox*)(editor);
            model->setData(index,pDoubleSpinBox->value(),Qt::EditRole);
        }
        if (TypeStr == "Double"){
            QDoubleSpinBox *pDoubleSpinBox =  (QDoubleSpinBox*)(editor);
            model->setData(index,pDoubleSpinBox->value(),Qt::EditRole);
        }
    }
    if( Col == 4){
        QLineEdit *pLineEdit = (QLineEdit*)(editor);
         model->setData(index,pLineEdit->text(),Qt::EditRole);
    }
    return;
}

void CustomDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

void CustomDelegate::SetReadOnlyMode()
{
    m_ReadOnlyMode = true;
}
