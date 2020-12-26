#include "ListModel.h"
#include <QStringListModel>
#include <QDebug>
ListModel::ListModel(QWidget *parent) :
    QAbstractListModel(parent)
{

}

ListModel::~ListModel()
{

}

void ListModel::append(const PlayListItem &item)
{
    if(isRepepetiveItem(item))
        return;
    PlayListItem *temp = new PlayListItem(item);
    beginInsertRows(QModelIndex(),count(),count());
    listContainer.append(temp);
    endInsertRows();
    emit ModelContainerChanged("new file appended");
}

void ListModel::append(const QList<PlayListItem> &items)
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

void ListModel::insert(int index, const QList<PlayListItem> &items)
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

bool ListModel::removeOne(PlayListItem *item)
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

int ListModel::removeAll(PlayListItem *item)
{
    if(!listContainer.contains(item))
        return 0;
    beginResetModel();
    int removedItems = listContainer.removeAll(item);
    endResetModel();
    emit ModelContainerChanged("files removed");
    return removedItems;
}

void ListModel::removeAt(int index)
{
    if(index < 0 || index >= count())
        return ;
    beginRemoveRows(QModelIndex(),index,index);
    listContainer.removeAt(index);
    endRemoveRows();
    emit ModelContainerChanged("file removed with index");
}

int ListModel::count() const
{
    return listContainer.count();
}

void ListModel::insert(int index, PlayListItem &item)
{
    if(isRepepetiveItem(item)){
        return;
    }
    PlayListItem *temp = new PlayListItem(item);
    beginInsertRows(QModelIndex(),index,index + 1);
    listContainer.insert(index,new PlayListItem(item));
    endInsertRows();
    emit ModelContainerChanged("new file inserted");
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    return count();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(role==Qt::DisplayRole){
    if(index.column() == 0)
        return listContainer[index.row()]->absoluteFileName() + '\t' +  QString::number(listContainer[index.row()]->lenght) +
                '\t' +listContainer[index.row()]->format;
    }
    return QVariant();
}

int ListModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

bool ListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

bool ListModel::isRepepetiveItem(PlayListItem obj)
{
    for(int i=0;i<listContainer.count();i++){
        if(*listContainer[i] == obj)
            return true;
    }
    return false;
}

