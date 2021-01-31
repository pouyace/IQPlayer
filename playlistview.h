#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H
#include <QListView>
#include "tablemodel.h"
#include <QWidget>
#include <QFileInfo>
#include <QTableView>
#include <QDebug>
#include <QLabel>
namespace Ui {
class PlayListView;
}

class TableItemDelegate;
class DragLabelItem;
class PlayListView : public QTableView
{
    Q_OBJECT

public:
    enum acceptableFormats{NotValid,data,txt,vga,mp3};
    explicit PlayListView(QWidget *parent = nullptr);
    ~PlayListView();
    Q_ENUM(acceptableFormats)
private:
    Ui::PlayListView *ui;
    TableModel          *tableModel     = nullptr;
    QMouseEvent         *mouseEvent     = nullptr;
    TableItemDelegate   *itemDelegate   = nullptr;
    DragLabelItem       *dragLabel      = nullptr;
    // Methods
    void tryList();
    void setupProperties();
    void handleDragging();
    void swapItems();
    void handleReleasing();
    void dropEvent(QDropEvent *e) override;
    void dragEnterEvent(QDragEnterEvent *e) override;    
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    bool verifyFileFormat(QString filePath);

public slots:
    void onResizingViewList();
    void onModelListChanged(QString msg);
    void requestToPlayItem(const QModelIndex &item);
    void onOpenFiles(QStringList files);

signals:
    void mousePositionUpdated(int x, int y);
    void mouseReleased();
    void playingItemListRequested(QString filePath,int row);
};

#endif // PLAYLISTVIEW_H
