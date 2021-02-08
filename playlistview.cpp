#include "playlistview.h"
#include "ui_playlistview.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>
#include <QMimeData>
#include <QDir>
#include <QMetaEnum>
#include <QHeaderView>
#include "tableitemdelegate.h"
#include "draghandler.h"

PlayListView::PlayListView(QWidget *parent) :
    QTableView(parent),
    ui(new Ui::PlayListView)
{
    ui->setupUi(this);

    tableModel = new TableModel(this);
    this->setModel(tableModel);
    itemDelegate = new TableItemDelegate(this);
    dragLabel = new DragLabelItem(nullptr);
    setupProperties();
    tryList();
}

PlayListView::~PlayListView()
{
    dragLabel->deleteLater();
    delete ui;
}

void PlayListView::setPressingMode(const bool &mode)
{
    _pressingMode = mode;
}

bool PlayListView::pressingMode() const
{
    return _pressingMode;
}

int PlayListView::currentRow() const
{
    return this->indexAt(mouseEvent->pos()).row();
}

void PlayListView::tryList()
{
    tableModel->append(PlayListItem("1",5,"best"));
    tableModel->append(PlayListItem("2",6,"best"));
    tableModel->append(PlayListItem("4",7,"best"));
    tableModel->append(PlayListItem("5",8,"best"));
    QList<PlayListItem> items;
    PlayListItem item(PlayListItem("6",9,"best"));
    items <<item;
    tableModel->append(items);
    QList<PlayListItem> items2;
    PlayListItem ie(PlayListItem("3",10,"best"));
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
    this->setDragDropMode        (QAbstractItemView::DragDrop);
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

    this->verticalHeader()->setSectionsMovable(true);
    this->verticalHeader()->setDragEnabled(true);
    this->verticalHeader()->setProperty("orientation","Vertical");
    this->verticalHeader()->setDragDropMode(QAbstractItemView::InternalMove);
    this->verticalHeader()->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->verticalHeader()->hide();


    connect(this,&PlayListView::mousePositionUpdated,dragLabel,&DragLabelItem::updateLabelPosition);
    connect(tableModel,&TableModel::ModelContainerChanged,this,&PlayListView::onModelListChanged);
    connect(this,&PlayListView::mouseReleased,dragLabel,&DragLabelItem::mouseReleased);
    connect(this,&QAbstractItemView::doubleClicked,this,&PlayListView::requestToPlayItem);


}

void PlayListView::handleDragging()
{
    int row = this->indexAt(mouseEvent->pos()).row();
    if(tableModel->isValidRow(row)){
        dragLabel->configureLabel(row,tableModel->dataAtIndex(row),itemDelegateForRow(row),true);
        setItemDelegateForRow(row,itemDelegate);
    }
    int x = mouseEvent->x() + 1300;
    int y = mouseEvent->y() + 850;
    dragLabel->setGeometry(x,y,170,10);
}

void PlayListView::swapItems()
{
    this->setItemDelegateForRow(dragLabel->labelRow(),dragLabel->defaultDelegate());
    int newRow = this->indexAt(mouseEvent->pos()).row();
    int oldRow = dragLabel->labelRow();
    tableModel->swapRows(oldRow,newRow);
}
void PlayListView::handleReleasing()
{
    this->setItemDelegateForRow(dragLabel->labelRow(),dragLabel->defaultDelegate());
    emit mouseReleased();
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
        if(verifyFileFormat(filePath)){
            e->accept();
            qDebug()<<"f";
        }
    }
    else{
        qDebug()<<"Not Url";
    }
}

void PlayListView::dragLeaveEvent(QDragLeaveEvent *e)
{

}

void PlayListView::dragMoveEvent(QDragMoveEvent *e)
{
//    qDebug()<<"DragMoveEvent";
}

void PlayListView::mouseReleaseEvent(QMouseEvent *event)
{
    mouseEvent = event;
    int row = currentRow();
    setPressingMode(false);
    this->setCursor(Qt::ArrowCursor);
    handleReleasing();
//    this->selectRow(row);

}

void PlayListView::mouseMoveEvent(QMouseEvent *event)
{
    mouseEvent = event;
    int row = currentRow();
    if(!tableModel->isValidRow(row)){
        return;
    }
    if(!pressingMode()){
        return;
    }
    if(!dragLabel->draggingMode()){
        qDebug()<<"setting dragging up!";
        handleDragging();
    }
    else{
        if(dragLabel->labelRow() != row){
            swapItems();
            handleDragging();
            this->selectRow(-1);
        }
        QPoint point = mapToGlobal(QPoint(15,(row + 2)*30-10));
        emit mousePositionUpdated(point.x(),point.y());
    }
}

void PlayListView::mousePressEvent(QMouseEvent *event)
{
    mouseEvent = event;
    int row = currentRow();
    if(!tableModel->isValidRow(row)){
        setPressingMode(false);
    }
    else{
        setPressingMode(true);
        this->setCursor(Qt::ClosedHandCursor);
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
    emit playingItemListRequested(filePath.toString(),item.row());
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
