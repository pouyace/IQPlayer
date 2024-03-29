#ifndef LISTMODEL_H
#define LISTMODEL_H
#include "QVBoxLayout"
#include <QListView>
#include <QStringListModel>
#include <QFileInfo>
struct PlayListItem{
    QString filePath;
    int     lenght;
    QString format;
    PlayListItem(QString filepath="",int timeLenght=0,QString fileFormat=""){

        filePath = filepath;
        lenght = timeLenght;
        if(fileFormat.length()==0){
            QFileInfo fileChecker(filepath);
            QString suffix = fileChecker.suffix();
            fileFormat = suffix;
        }
        format  = fileFormat;
    }
    PlayListItem(const PlayListItem& obj){
        filePath = obj.filePath;
        lenght =obj.lenght;
        format = obj.format;
    }
    friend bool operator==(const PlayListItem& myObj1,const PlayListItem& myObj2){

        if(/*myObj1.format == myObj2.format && myObj1.lenght == myObj2.lenght &&*/ myObj1.filePath == myObj2.filePath)
            return true;
        else
            return false;
    }
    friend QDataStream & operator <<(QDataStream &out,const PlayListItem &myObj){
        out<<myObj.filePath;
        out<<myObj.lenght;
        out<<myObj.format;
        return out;
    }
    QString absoluteFileName(){
        QFileInfo fileInfoChecker(filePath);
        return fileInfoChecker.fileName().remove(".txt");
    }

};
Q_DECLARE_METATYPE(PlayListItem)

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum ModelRoles{FilePathRole = Qt::UserRole};
    explicit TableModel(QWidget *parent = nullptr);
    ~TableModel();
    QVariant getData(const QModelIndex& index,int role) const;
    void insert(int index, PlayListItem& item);
    void append(const PlayListItem& item);
    void append(const QList<PlayListItem>& items);
    void insert(int index,const QList<PlayListItem>& items);
    void removeAt(int index);
    bool removeOne(PlayListItem *item);
    int  removeAll(PlayListItem *item);
    void freeTable();
    int count() const;
    bool swapRows(int i,int j);
    bool isValidRow(int row)const;
    PlayListItem* dataAtIndex(int row);
    //virtual Qt::DropActions supportedDropActions() const override;
protected:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                    int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

private:
    QList <PlayListItem*> listContainer;

    bool isRepepetiveItem(PlayListItem obj);
signals:
    void ModelContainerChanged(QString msg);

};

#endif // PLAYLISTVIEW_H
