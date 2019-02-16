#pragma once
#include <QItemDelegate>
class MItemDelegate : public QItemDelegate
{
public:
	MItemDelegate();
	~MItemDelegate();
	
	QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

