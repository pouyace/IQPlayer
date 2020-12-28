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

    tableModel = new TableModel(this);
    this->setModel(tableModel);

    setupProperties();
    tryList();
}

PlayListView::~PlayListView()
{
    delete ui;
}

void PlayListView::tryList()
{
    tableModel->append(PlayListItem("Pouya",5,"best"));
    tableModel->append(PlayListItem("pa",6,"best"));
    tableModel->append(PlayListItem("df",7,"best"));
    tableModel->append(PlayListItem("sd",8,"best"));
    QList<PlayListItem> items;
    PlayListItem item(PlayListItem("Posdfuya",9,"best"));
    items <<item;
    tableModel->append(items);
    QList<PlayListItem> items2;
    PlayListItem ie(PlayListItem("Poasuya",10,"best"));
    items2<<ie<<ie<<ie;
    tableModel->insert(2,items2);
}

void PlayListView::setupProperties()
{
    this->setContentsMargins     (0,2,2,2);
    this->setMaximumWidth        (300);
    this->setMinimumWidth        (260);
    this->setMinimumHeight       (100);
    this->setProperty            ("class","playListWidget");
    this->setDragEnabled         (true);
    this->setAcceptDrops         (true);
    this->setDragDropMode        (QAbstractItemView::InternalMove);
    this->setDropIndicatorShown  (true);
    this->setSelectionMode       (QAbstractItemView::SingleSelection);
    this->resizeColumnsToContents();
    this->setCornerButtonEnabled (false);
    this->setSelectionBehavior   (QAbstractItemView::SelectRows);

    this->horizontalHeader()->setStretchLastSection(false);;
    this->horizontalHeader()->setProperty("orientation","Horizontal");
    this->horizontalHeader()->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);
    this->horizontalHeader()->setStretchLastSection(false);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->horizontalHeader()->setSectionsClickable(false);

    this->verticalHeader()->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->verticalHeader()->hide();

    connect(tableModel,&TableModel::ModelContainerChanged,this,&PlayListView::onModelListChanged);
    connect(this,&QAbstractItemView::doubleClicked,this,&PlayListView::requestToPlayItem);

}
void PlayListView::dropEvent(QDropEvent *e)
{
    qDebug()<<"drop event";
    QString path;
    QList<QUrl> filePath = e->mimeData()->urls();
    QListIterator<QUrl>urlListIterator(filePath);
    while(urlListIterator.hasNext()){
        path = urlListIterator.next().path().remove(0,1);
        if(verifyFileFormat(path))
            tableModel->append(PlayListItem(path,0));
    }
}

void PlayListView::dragEnterEvent(QDragEnterEvent *e)
{
    bool exists,readable,dir,isFile;
    if(e->mimeData()->hasUrls()){
        QString filePath = e->mimeData()->urls().first().path().remove(0,1);
        qDebug()<<"this is the filePath:"<<filePath;
        if(verifyFileFormat(filePath))
            e->acceptProposedAction();
    }
    else{
        qDebug()<<"Not Url";
    }
}

bool PlayListView::verifyFileFormat(QString filePath)
{
    bool exists,readable,dir,isFile;
    QFileInfo fileInfoChecker(filePath);
    isFile = fileInfoChecker.isFile();
    exists = fileInfoChecker.exists();
    readable = fileInfoChecker.isReadable();
    QString suffix = fileInfoChecker.suffix();
    QMetaEnum metaEnum = QMetaEnum::fromType<acceptableFormats>();
    switch (metaEnum.keyToValue(suffix.toStdString().c_str())) {
    case acceptableFormats::NotValid:   return false;
    case acceptableFormats::txt:        return true;
    case acceptableFormats::mp3:        return true;
    case acceptableFormats::data:       return true;
    default:
    {   qDebug()<<"isFile:"<<isFile;
        qDebug()<<"exists:"<<exists;
        qDebug()<<"isreadable:"<<readable;
        qDebug()<<"suffix"<<suffix;return false;
    }
    }
    return false;
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
    QVariant filePath = (this->tableModel->getData(item,TableModel::FilePathRole));
    qDebug()<<"filePath= " << filePath.toString();
    emit playingItemListRequested(filePath.toString());
}

void PlayListView::onOpenFiles(QStringList files)
{
    QString file;
    QStringListIterator filesIterator(files);
    while(filesIterator.hasNext()){
        file = filesIterator.next();
        if(verifyFileFormat(file))
            tableModel->append(PlayListItem(file,0));
    }
}
