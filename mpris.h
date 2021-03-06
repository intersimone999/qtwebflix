#ifndef MPRIS_H
#define MPRIS_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QDBusObjectPath>
#include <QDebug>

class Mpris : public QObject
{
    Q_OBJECT

    // org.mpris.MediaPlayer2.Player
    Q_PROPERTY( double Rate READ Rate WRITE SetRate )
    Q_PROPERTY( qlonglong Position READ Position )
    Q_PROPERTY( double MinimumRate READ MinimumRate )
    Q_PROPERTY( double MaximumRate READ MaximumRate )
    Q_PROPERTY( bool CanControl READ CanControl )
    Q_PROPERTY( bool CanPlay READ CanPlay )
    Q_PROPERTY( bool CanPause READ CanPause )
    Q_PROPERTY( bool CanSeek READ CanSeek )
    Q_PROPERTY( bool CanGoNext READ CanGoNext )
    Q_PROPERTY( bool CanGoPrevious READ CanGoPrevious )
    Q_PROPERTY( QString PlaybackStatus READ PlaybackStatus )
    Q_PROPERTY( QString LoopStatus READ LoopStatus WRITE SetLoopStatus )
    Q_PROPERTY( bool Shuffle READ Shuffle WRITE SetShuffle )
    Q_PROPERTY( QVariantMap Metadata READ Metadata )
    Q_PROPERTY( double Volume READ Volume WRITE SetVolume )

    // org.mpris.MediaPlayer2
    Q_PROPERTY( bool CanQuit READ CanQuit )
    Q_PROPERTY( bool CanRaise READ CanRaise )
    Q_PROPERTY( QString DesktopEntry READ DesktopEntry )
    Q_PROPERTY( bool HasTrackList READ HasTrackList )
    Q_PROPERTY( QString Identity READ Identity )
    Q_PROPERTY( QStringList SupportedMimeTypes READ SupportedMimeTypes )
    Q_PROPERTY( QStringList SupportedUriSchemes READ SupportedUriSchemes )

public:
    Mpris(QObject *p, QString name);
    virtual ~Mpris();

    // org.mpris.MediaPlayer2.Player
    void Next() { qDebug()<<"next"; }
    void Previous() {  qDebug()<<"previous"; }
    void Pause();
    void PlayPause() {  qDebug()<<"pause"; }
    void Stop() {  qDebug()<<"stop"; }
    void StopAfterCurrent() {  qDebug()<<"stop after current"; }
    void Play();
    void Seek(qlonglong pos) {  qDebug()<<pos; }
    void SetPosition(const QDBusObjectPath &, qlonglong pos) { qDebug()<<pos; }
    void OpenUri(const QString &) { }
    QString PlaybackStatus() const;
    QString LoopStatus() { return "sthm"; }
    void SetLoopStatus(const QString &s) { emit setRepeat(QLatin1String("None")!=s); }
    QVariantMap Metadata() const;
    int Rate() const { return 1.0; }
    void SetRate(double) { }
    bool Shuffle() { return false; }
    void SetShuffle(bool s) { emit setRandom(s); }
    double Volume() const { return 100.0; }
    void SetVolume(double v) { emit setVolume(v*100); }
    qlonglong Position() const;
    double MinimumRate() const { return 1.0; }
    double MaximumRate() const { return 1.0; }
    bool CanControl() const { return true; }
    bool CanPlay() const { return true; }
    bool CanPause() const { return true; }
    bool CanSeek() const { return true; }
    bool CanGoNext() const { return true; }
    bool CanGoPrevious() const { return true; }

    // org.mpris.MediaPlayer2
    bool CanQuit() const { return true; }
    bool CanRaise() const { return true; }
    bool HasTrackList() const { return false; }
    QString Identity() const { return QLatin1String("Cantata"); }
    QString DesktopEntry() const {
        #ifdef ENABLE_KDE_SUPPORT
        // Desktop file is installed in $prefix/share/applications/kde4/
        // rather than in $prefix/share/applications. The standard way to
        // represent this dir is with a "kde4-" prefix. See:
        // http://standards.freedesktop.org/menu-spec/1.0/go01.html#term-desktop-file-id
        return QLatin1String("kde4-cantata");
        #else
        return QLatin1String("cantata");
        #endif
    }

    QStringList SupportedUriSchemes() const { return QStringList(); }
    QStringList SupportedMimeTypes() const { return QStringList(); }

public:
    void updateCurrentSong();

public Q_SLOTS:
    void Raise();
    void Quit() { qDebug() << "Quit"; }

Q_SIGNALS:
    // org.mpris.MediaPlayer2.Player
    void setRandom(bool toggle);
    void setRepeat(bool toggle);
    void setSeekId(qint32 songId, quint32 time);
    void setVolume(int vol);

    void showMainWindow();

public Q_SLOTS:
    void updateCurrentCover(const QString &fileName);

private Q_SLOTS:
    void updateStatus();

private:
    void signalUpdate(const QString &property, const QVariant &value);
    void signalUpdate(const QVariantMap &map);

private:
    //MPDStatusValues status;
    QString currentCover;
    //Song currentSong;
    int pos;

    QString serviceName;
};


#endif // MPRIS_H
