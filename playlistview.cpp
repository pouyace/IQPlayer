#include "playlistview.h"
#include "ui_playlistview.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>
#include <QMimeData>
#include <QDir>
#include <QMetaEnum>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QHeaderView>
#include <QStyledItemDelegate>

PlayListView::PlayListView(QWidget *parent) :
    QTableView(parent),
    ui(new Ui::PlayListView)
{
    ui->setupUi(this);

    this->setContentsMargins(0,2,2,2);
    listModel = new TableModel(this);
    this->setModel(listModel);
    setupProperties();
    QHeaderView *horiz = this->horizontalHeader();
    QHeaderView *vert = this->verticalHeader();
    horiz->setProperty("orientation","Horizontal");
    horiz->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    vert->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    horiz->setStretchLastSection(false);
    horiz->setSectionResizeMode(QHeaderView::Fixed);
    vert->hide();
    horiz->setSectionsClickable(false);

    connect(this,&QAbstractItemView::doubleClicked,this,&PlayListView::requestToPlayItem);
    tryList();

}

PlayListView::~PlayListView()
{
    delete ui;
}

void PlayListView::tryList()
{
    listModel->append(PlayListItem("Pouya",5,"best"));
    listModel->append(PlayListItem("pa",6,"best"));
    listModel->append(PlayListItem("df",7,"best"));
    listModel->append(PlayListItem("sd",8,"best"));
    QList<PlayListItem> items;
    PlayListItem item(PlayListItem("Posdfuya",9,"best"));
    items <<item;
    listModel->append(items);
    QList<PlayListItem> items2;
    PlayListItem ie(PlayListItem("Poasuya",10,"best"));
    items2<<ie<<ie<<ie;
    listModel->insert(2,items2);
}

void PlayListView::setupProperties()
{
    this->setMaximumWidth(300);
    this->setMinimumWidth(260);
    this->setMinimumHeight(100);
    this->setProperty("class","playListWidget");
    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDragDropMode(QAbstractItemView::InternalMove);
    this->setDropIndicatorShown(true);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->resizeColumnsToContents();
    this->setCornerButtonEnabled(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(listModel,&TableModel::ModelContainerChanged,this,&PlayListView::onModelListChanged);
}
void PlayListView::dropEvent(QDropEvent *e)
{
    qDebug()<<"drop event";
    QString filePath = e->mimeData()->urls().first().path().remove(0,1);
    listModel->append(PlayListItem(filePath));
}

void PlayListView::dragEnterEvent(QDragEnterEvent *e)
{
    bool exists,readable,dir,isFile;
    if(e->mimeData()->hasUrls()){
        QString filePath = e->mimeData()->urls().first().path().remove(0,1);
        qDebug()<<"this is the filePath:"<<filePath;
        QFileInfo fileInfoChecker(filePath);
        QString suffix = fileInfoChecker.suffix();
        isFile = fileInfoChecker.isFile();
        exists = fileInfoChecker.exists();
        readable = fileInfoChecker.isReadable();
        if(isFile && exists && readable){
            QMetaEnum metaEnum = QMetaEnum::fromType<acceptableFormats>();
            switch (metaEnum.keyToValue(suffix.toStdString().c_str())) {
            case acceptableFormats::NotValid:break;
            case acceptableFormats::txt:e->acceptProposedAction();break;
            case acceptableFormats::mp3:e->acceptProposedAction();break;
            case acceptableFormats::data:e->acceptProposedAction();break;
            default:break;
            }
        }
        else{
            qDebug()<<"isFile:"<<isFile;
            qDebug()<<"exists:"<<exists;
            qDebug()<<"isreadable:"<<readable;
            qDebug()<<"suffix"<<suffix;
        }
    }
    else{
        qDebug()<<"Not Url";
    }
}

void PlayListView::onResizingViewList()
{
    int widthSize = this->width() / 6;
    this->setColumnWidth(0,widthSize * 2.3);
    this->setColumnWidth(1,widthSize);
    this->setColumnWidth(2,widthSize * 2);

}

void PlayListView::onModelListChanged(QString msg)
{
    qDebug()<<msg;
}

void PlayListView::requestToPlayItem(const QModelIndex &item)
{
//    int No = -1;
//    for(int i=0; i<this->listModel->count(); i++){
//        if(this->listModel->index(i) == item){
//            No = i;
//            break;
//        }
//    }
//    if(No >= 0){
//        playingItemListRequested(No);
//    }
}
