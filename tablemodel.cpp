#include "tablemodel.h"
#include <QStringListModel>
#include <QDebug>
TableModel::TableModel(QWidget *parent) :
    QAbstractTableModel(parent)
{
}

TableModel::~TableModel()
{

}

QVariant TableModel::getData(const QModelIndex &index, int role) const
{
     return this->data(index,role);
}

void TableModel::append(const PlayListItem &item)
{
    if(isRepepetiveItem(item))
        return;

    PlayListItem *temp = new PlayListItem(item);
    beginInsertRows(QModelIndex(),count(),count());
    listContainer.append(temp);
    endInsertRows();
    emit ModelContainerChanged("new file appended:"+temp->filePath);
}

void TableModel::append(const QList<PlayListItem> &items)
{
    if(items.count() == 0)
        return;
    beginInsertRows(QModelIndex(),count(),count()+items.count()-1);
    for(int i=0;i<items.count();i++){
        if(!isRepepetiveItem(items[i]))
            listContainer.append(new PlayListItem(items[i]));
    }
    endInsertRows();
    emit ModelContainerChanged("new list appended");
}

void TableModel::insert(int index, const QList<PlayListItem> &items)
{
    if(items.count() == 0)
        return;
    beginInsertRows(QModelIndex(),index,index+items.count());
    for(int i=0,k=index;i<items.count();i++,k++){
        if(!isRepepetiveItem(items[i]))
            listContainer.insert(k,new PlayListItem(items.at(i)));
    }
    endInsertRows();
    emit ModelContainerChanged("new list inserted");
}

bool TableModel::removeOne(PlayListItem *item)
{
    int row = listContainer.indexOf(item);
    if(row<0)
        return false;
    beginRemoveRows(QModelIndex(),row,row);
    listContainer.removeAt(row);
    endRemoveRows();
    emit ModelContainerChanged("file removed");
    return true;
}

int TableModel::removeAll(PlayListItem *item)
{
    if(!listContainer.contains(item))
        return 0;
    beginResetModel();
    int removedItems = listContainer.removeAll(item);
    endResetModel();
    emit ModelContainerChanged("files removed");
    return removedItems;
}

void TableModel::freeTable()
{
    if(!listContainer.count())
        return;
    QListIterator<PlayListItem*>a(listContainer);
    while(a.hasNext()){
        removeAll(a.next());
    }
    emit ModelContainerChanged("all list members were removed");
}

void TableModel::removeAt(int index)
{
    if(index < 0 || index >= count())
        return ;
    beginRemoveRows(QModelIndex(),index,index);
    listContainer.removeAt(index);
    endRemoveRows();
    emit ModelContainerChanged("file removed with index");
}

int TableModel::count() const
{
    return listContainer.count();
}

void TableModel::insert(int index, PlayListItem &item)
{
    if(isRepepetiveItem(item)){
        return;
    }
    beginInsertRows(QModelIndex(),index,index + 1);
    listContainer.insert(index,new PlayListItem(item));
    endInsertRows();
    emit ModelContainerChanged("new file inserted");
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return count();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(role==Qt::DisplayRole){
        if(index.column() == 0)
            return listContainer[index.row()]->absoluteFileName();
        if(index.column() == 1)
            return QString::number(listContainer[index.row()]->lenght);
        if(index.column() == 2)
            return listContainer[index.row()]->format;
    }
    else if(role == Qt::TextAlignmentRole){
        if(index.column() == 0)
            return Qt::AlignLeft;
        else
            return Qt::AlignCenter;
    }
    else if(role == FilePathRole){
        return listContainer[index.row()]->filePath;
    }

    return QVariant();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch (section) {
            case 0: return tr("Filename");
            case 1: return tr("Length"  );
            case 2: return tr("Format"  );
            }
        }
        else if(orientation == Qt::Vertical){
            return "";
        }
    }
    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash <int,QByteArray>returnData;
    QByteArray valueData;

    returnData.insert(FilePathRole,"FilePath");
    return returnData;
}

bool TableModel::swapRows(int i, int j)
{
    if(i<count() && j<count() && i>=0 && j>=0){
        listContainer.swapItemsAt(i ,j);
        return true;
    }
    return false;
}

bool TableModel::isValidRow(int row) const
{
    if(row < count() && row >= 0)
        return true;
    return false;
}

PlayListItem *TableModel::dataAtIndex(int row)
{
    if(row == -1)
        return nullptr;
    return listContainer.at(row);
}

bool TableModel::isRepepetiveItem(PlayListItem obj)
{
    for(int i=0;i<listContainer.count();i++){
        if(*listContainer[i] == obj)
            return true;
    }
    return false;
}

