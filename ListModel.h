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
    QString absoluteFileName(){
        QFileInfo fileInfoChecker(filePath);
        return fileInfoChecker.fileName().remove(".txt");
    }
};

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QWidget *parent = nullptr);
    ~TableModel();
    void insert(int index, PlayListItem& item);
    void append(const PlayListItem& item);
    void append(const QList<PlayListItem>& items);
    void insert(int index,const QList<PlayListItem>& items);
    void removeAt(int index);
    bool removeOne(PlayListItem *item);
    int  removeAll(PlayListItem *item);
    int count() const;
protected:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                    int role = Qt::DisplayRole) const override;
    //virtual Qt::DropActions supportedDropActions() const override;
    //virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
    QList <PlayListItem*> listContainer;

    bool isRepepetiveItem(PlayListItem obj);
signals:
    void ModelContainerChanged(QString msg);

};

#endif // PLAYLISTVIEW_H
