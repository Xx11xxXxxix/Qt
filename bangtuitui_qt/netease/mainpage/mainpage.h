#ifndef MAINPAGE_H
#define MAINPAGE_H
#include "widgets/recommendwidget.h"
#include <QWidget>
#include <QPushButton>
#include "widgets/audioplayer.h"
#include <QVBoxLayout>
#include "../api/recommendapi.h"
#include"../api/songapi.h"
class MainPage : public QWidget {
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);
private slots:
    void onRecommendButtonClicked();
    void onRecommendReceived(const QList<Song>& songs);
    void onSongClicked(qint64 songId);
private:
    QPushButton* recommendButton;
    RecommendWidget* recommendWidget;
    void setupUI();
    QVBoxLayout* layout;
    AudioPlayer* audioPlayer;



};


#endif
