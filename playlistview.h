#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H
#include <QListView>
#include "ListModel.h"
#include <QWidget>
#include <QFileInfo>
namespace Ui {
class PlayListView;
}

class PlayListView : public QListView
{
    Q_OBJECT

public:
    enum acceptableFormats{NotValid,data,txt,vga,mp3};
    explicit PlayListView(QWidget *parent = nullptr);
    ~PlayListView();
    Q_ENUM(acceptableFormats)
private:
    Ui::PlayListView *ui;
    ListModel        *listModel  = nullptr;

    // Methods
    void tryList();
    void setupProperties();
    void dropEvent(QDropEvent *e) override;
    void dragEnterEvent(QDragEnterEvent *e) override;

public slots:
    void onModelListChanged(QString msg);
    void requestToPlayItem(const QModelIndex &item);

signals:
    void playingItemListRequested(int itemNumber);
};

#endif // PLAYLISTVIEW_H
