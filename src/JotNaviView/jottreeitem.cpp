

#include "jottreeitem.h"

#include <QStringList>
#include <QtCore>
//! [0]
JotTreeItem::JotTreeItem(const QVector<QVariant> &data, QString itemId, JotTreeItem *parent)
{
    parentItem = parent;
    itemData = data;
    SetId(itemId);
}
//! [0]

//! [1]
JotTreeItem::~JotTreeItem()
{
    //qDeleteAll(childItems);
}
//! [1]

//! [2]
JotTreeItem *JotTreeItem::child(int number)
{
    return childItems.value(number);
}
//! [2]

//! [3]
int JotTreeItem::childCount() const
{
    return childItems.count();
}
//! [3]

//! [4]
int JotTreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<JotTreeItem*>(this));

    return 0;
}
//! [4]

//! [5]
int JotTreeItem::columnCount() const
{
    return itemData.count();
}
//! [5]

//! [6]
QVariant JotTreeItem::data(int column) const
{
    return itemData.value(column);
}
//! [6]

//! [7]
bool JotTreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        JotTreeItem *item = new JotTreeItem(data,"", this);
        childItems.insert(position, item);
    }

    return true;
}
//! [7]

//! [8]
bool JotTreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    for (JotTreeItem *child : childItems)
        child->insertColumns(position, columns);

    return true;
}
//! [8]

//! [9]
JotTreeItem *JotTreeItem::parent()
{
    return parentItem;
}
//! [9]

//! [10]
bool JotTreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
//! [10]

bool JotTreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    for (JotTreeItem *child : childItems)
        child->removeColumns(position, columns);

    return true;
}

//! [11]
bool JotTreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}
//! [11]

bool JotTreeItem::SetId(QString id)
{
   selfId = id;
   return true;
}

QString JotTreeItem::SelfId()
{
  return selfId;
}

bool JotTreeItem::isChecked()
{
    return ifChecked;
}

void JotTreeItem::setCheckState(bool state)
{
    ifChecked = state;
}
