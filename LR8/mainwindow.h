#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimediaWidgets/QVideoWidget>
#include<QFileDialog>
#include<QCoreApplication>
#include<QDebug>
#include<QShortcut>
#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QMediaPlaylist *playlist;
    QStandardItemModel  *modelList;
    QHash <QUrl,qint64> hash;
    QShortcut *keyDel;
    int indexRow;

protected:
    /**
     * @brief event Обработка событий
     * @param event Событие
     * @return Событие
     */
    bool event(QEvent *event) override;

private:
    /**
     * @brief openPlaylist Открытие плейлиста
     */
    void openPlaylist();
    /**
     * @brief optionsTableView Настройки отоображения плейлиста
     */
    void optionsTableView();
    /**
     * @brief optionsVolume Настройки звука
     */
    void optionsVolume();
    /**
     * @brief optionsVideoTime Настройки позиции в видео
     */
    void optionsVideoTime();
    /**
     * @brief generalOptions Общие настройки внешнего вида
     */
    void generalOptions();
    /**
     * @brief generalOptions_2 Продолжение общих настроек
     */
    void generalOptions_2();
    /**
     * @brief key Горячая клавиша
     */
    void key();
    /**
     * @brief nextPrevious Переход к следующему видео
     */
    void nextPrevious();
    /**
     * @brief writeBin Запись в бинарный файл
     */
    void writeBin();
    /**
     * @brief readBin Чтение бинарного файла
     */
    void readBin();

private slots:
    /**
     * @brief playVideo Переход к вкладке с просмотром видео
     */
    void playVideo();
    /**
     * @brief pauseVideo Сохранение позиции и остановка видео
     */
    void pauseVideo(int);
    /**
     * @brief typeToVolume Отображение значения звука
     */
    void typeToVolume(int);
    /**
     * @brief getPosition Установка позиции в проигрывателе
     */
    void getPosition();
    /**
     * @brief findInHash Поиск последней точки воспроизведения
     */
    void findInHash();
    /**
     * @brief startInTab Просмотр с сохраненной позиции из вкладки с видео
     */
    void startInTab();
    /**
     * @brief indexToDelete Удаление видео из плейлиста
     */
    void indexToDelete();
    /**
     * @brief message Информационное сообщение
     */
    void message();
    /**
     * @brief previous Переход к предыдущему видео
     */
    void previous();
    /**
     * @brief next Переход к следующему видео
     */
    void next();
};
#endif // MAINWINDOW_H
