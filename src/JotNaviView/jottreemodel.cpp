
#include <QtGui>

#include "jottreeitem.h"
#include "jottreemodel.h"
#include <QtSql>

//!
JotTreeModel::JotTreeModel(const QStringList &headers, const QString tablename, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    for (QString header : headers)
        rootData << header ;

    rootItem = new JotTreeItem(rootData,"0");
    setupModelData(tablename, rootItem);
}
//! [0]

//! [1]
JotTreeModel::~JotTreeModel()
{
    delete rootItem;
}
//! [1]

//! [2]
int JotTreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
 /*   if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();*/
}
//! [2]

QVariant JotTreeModel::data(const QModelIndex &index, int role) const
{
 /*
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    JotTreeItem *item = getItem(index);

    return item->data(index.column());
 */
    if (!index.isValid())
        return QVariant();

    JotTreeItem *item = static_cast<JotTreeItem*>(index.internalPointer());

    //判断显示的对象是checkbox，并且位于第一列
    if (role==Qt::CheckStateRole && index.column()==0)
        return static_cast<int>( item->isChecked() ? Qt::Checked : Qt::Unchecked );

    if (role != Qt::DisplayRole)
        return QVariant();

    return item->data(index.column());
}

QString JotTreeModel::getItemId(const QModelIndex &index) const
{
    if (!index.isValid())
        return "NULL";
    JotTreeItem *item = getItem(index);
    return item->SelfId();

}

//! [3]
Qt::ItemFlags JotTreeModel::flags(const QModelIndex &index) const
{
/*
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
*/
    if (index.isValid()){
    if (index.column()==0)   //如果是第一列的结点，则使其有显示checkbox的能力
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return Qt::NoItemFlags;
}
//! [3]

//! [4]
JotTreeItem *JotTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        JotTreeItem *item = static_cast<JotTreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}
//! [4]

QVariant JotTreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}


QModelIndex JotTreeModel::index(int row, int column, const QModelIndex &parent) const
{

    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    JotTreeItem *parentItem = getItem(parent);

    JotTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}


bool JotTreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool JotTreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    JotTreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex JotTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    JotTreeItem *childItem = getItem(index);
    JotTreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

bool JotTreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool JotTreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    JotTreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

//! [8]
int JotTreeModel::rowCount(const QModelIndex &parent) const
{
    JotTreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}
//! [8]

bool JotTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
/*
   if (role != Qt::EditRole)
        return false;

    JotTreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
  */
    if (role==Qt::CheckStateRole && index.column()==0)
    {
        JotTreeItem *item = static_cast<JotTreeItem*>(index.internalPointer());
        if (value==Qt::Unchecked)
        {
            //m_checkedList.removeOne(index);
            item->setCheckState(false);
            emit(dataChanged(index, index));
        }
        else if(value==Qt::Checked)
        {
            //m_checkedList.append(index);
            item->setCheckState(true);
            emit(dataChanged(index, index));
        }
        int childCount = rowCount(index);
        if (childCount > 0)
        {
            //判断是否有子节点
            for (int i=0; i<childCount; i++)
            {
                //获得子节点的index
                QModelIndex child = this->index(i, 0, index);
                //递归，改变子节点的checkbox状态
                setData(child, value, Qt::CheckStateRole);
            }
        }
    }
    return true;
}

bool JotTreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

// todo：use database source to replace this part, 用数据库记录代替lines
void JotTreeModel::setupModelData(const QString tablename, JotTreeItem *parent)
{
    QList<JotTreeItem*> parents; //like a stack,push the latest item into when find new child, popup the top item when children lookup finished
    QList<int> depths; //we have to change it to level
    parents << parent;
    depths << 0;
    int depth = 0;


    QString sql = "WITH RECURSIVE P (selfId, name, type, parentId, PATH, DEPTH)  AS (SELECT selfId, name, type, parentId, name||'/' AS PATH, 0 AS DEPTH FROM ";
            sql += tablename;
            sql += "  WHERE parentId = 0 UNION ALL ";
            sql += " SELECT  C.selfId, C.name, C.type, C.parentId, P.PATH||C.name||'/',  P.DEPTH + 1 AS DEPTH FROM ";
            sql += tablename;
            sql += " C JOIN P ON C.parentId = P.selfId) ";
            sql += " SELECT selfId , name, type, parentId, PATH, DEPTH FROM P ORDER BY PATH ASC;";
    QSqlQuery query;
    qDebug() << sql;
    query.exec(sql);
    while (query.next()) {
        qDebug() << query.value(0).toInt() << ", " << query.value(1).toString() << ", " << query.value(2).toInt() << ", " << query.value(3).toInt() << ", " << query.value(4).toString() << ", " << query.value(5).toInt();
        depth = query.value(5).toInt();

        QVector<QVariant> columnData;
        columnData << query.value(1).toString() << query.value(2).toInt() << query.value(0).toInt();
        if(depth > depths.last()){
           qDebug() << depth << "depths.last():" << depths.last();
           if (parents.last()->childCount() > 0) {
               qDebug() << "run in new parent";
               parents << parents.last()->child(parents.last()->childCount()-1);
               depths << depth;
           }
        }else {
            qDebug() << depth << "less";
            while (depth < depths.last() && parents.count() > 0) {
                parents.pop_back();
                depths.pop_back();
            }
         }
         JotTreeItem *parent = parents.last();
         if(parent == nullptr)
         qDebug() << "FAILED";
         parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
         for (int column = 0; column < columnData.size(); ++column)
             parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
         parent->child(parent->childCount() - 1)->SetId(query.value(0).toString());

 }
}

void JotTreeModel::setCheckedStrList(JotTreeItem *item, QStringList &checkedStrList)
{
    if (item->isChecked())
    {
        checkedStrList.append(item->data(0).toString());
    }

    int childCount = item->childCount();
    if (childCount > 0)
    {
        // 判断是否有子节点
        for (int i=0; i<childCount; i++)
        {
            JotTreeItem *child = item->child(i);
            // 递归调用setCheckedStrList;
            setCheckedStrList(child, checkedStrList);
        }
    }
}

void JotTreeModel::getCheckedItemData(QString& resStr)
{
    QStringList checkedStrList;
    setCheckedStrList(rootItem, checkedStrList);

    for (int i=0; i<checkedStrList.size(); i++)
    {
        resStr += checkedStrList[i] + QString("\n");
    }
}
