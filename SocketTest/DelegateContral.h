/*******************************************************************
 *  Copyright(c) 2018-2020 Company Name
 *  All rights reserved.
 *
 *  文件名称: DelegateContral.h
 *  简要描述: 代理类及数据角色定义
 *  创建日期:
 *  作者:
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
 ******************************************************************/
#ifndef DELEGATECONTRAL_H
#define DELEGATECONTRAL_H

#include <QStyledItemDelegate>
#include <QStringList>

enum E_ROLE_TYPE
{
    E_CTRL_ROLE      = Qt::UserRole + 1,    //控件类型角色
    E_USER_DATA_ROLE = Qt::UserRole + 2,    //用户数据角色
};

enum class E_USER_DATA:int     //数据类型角色
{
    /***********
     * 数据类型
     ***********/
    E_STR_DATA,         //Str(char *)
    E_BOOL_DATA,        //bool
    E_INT8_DATA,        //char
    E_REAL_DATA,       //double
    E_INT32_DATA,       //int
    E_FLOAT_DATA,       //float
    E_INT16_DATA,       //short
    E_INT64_DATA,       //long long int
    E_UINT8_DATA,       //unsigned char
    E_UINT32_DATA,      //unsigned int
    E_UINT16_DATA,      //unsigned short
    E_UINT64_DATA,      //unsigned long long int

    /***********
     * 控件类型
     ***********/
    E_SPINBOX_CTRL,     //QSpinBox
    E_COMBOBOX_CTRL,    //QComboBox
    E_LINEEDIT_CTRL,    //QLineEdit

    /***********
     * 默认类型
     ***********/
    E_DEFAULT_CTRL      //初始化
};

class CustomDelegate :public QStyledItemDelegate
{
public:
    explicit CustomDelegate(QObject *parent = nullptr);
    ~CustomDelegate()Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void SetReadOnlyMode();

private:
    mutable E_USER_DATA m_ctrlType;
    mutable E_USER_DATA m_dataType;
    QStringList DatTypes;
    bool m_ReadOnlyMode;
};

Q_DECLARE_METATYPE(E_USER_DATA)

#endif // DELEGATECONTRAL_H
