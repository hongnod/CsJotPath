

#ifndef JotTreeModel_H
#define JotTreeModel_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class JotTreeItem;

//! [0]
class JotTreeModel : public QAbstractItemModel
{
    CS_OBJECT(JotTreeModel)

public:
    JotTreeModel(const QStringList &headers, const QString tablename,
              QObject *parent = nullptr);
    ~JotTreeModel() override;
//! [0] //! [1]
    QString  getItemId(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
//! [1]

//! [2]
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    void setCheckedStrList(JotTreeItem *item, QStringList &checkedStrList);
    void getCheckedItemData(QString& resStr);
private:
    void setupModelData(const QString tablename, JotTreeItem *parent);
    JotTreeItem *getItem(const QModelIndex &index) const;

    JotTreeItem *rootItem = nullptr;
};
//! [2]

#endif // JotTreeModel_H
