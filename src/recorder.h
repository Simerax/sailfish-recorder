#ifndef RECORDER_H
#define RECORDER_H

#include <QtMultimedia/QAudioRecorder>
#include <QSettings>
#include <QSortFilterProxyModel>

class Recorder : public QAudioRecorder
{
    Q_OBJECT
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(int sampleRate READ sampleRate WRITE setSampleRate NOTIFY sampleRateChanged)
    Q_PROPERTY(QMultimedia::EncodingQuality encodingQuality READ encodingQuality WRITE setEncodingQuality NOTIFY encodingQualityChanged)
    Q_PROPERTY(QMultimedia::EncodingMode encodingMode READ encodingMode WRITE setEncodingMode NOTIFY encodingModeChanged)
    Q_PROPERTY(Recorder::Codec codec READ codec WRITE setCodec NOTIFY codecChanged)
    Q_PROPERTY(QString durationLabel READ durationLabel NOTIFY durationLabelChanged)
    Q_PROPERTY(bool recursiveSearch READ recursiveSearch WRITE setRecursiveSearch NOTIFY recursiveSearchChanged)
    Q_PROPERTY(QString sdCardPath MEMBER mSdCardPath CONSTANT)
    Q_PROPERTY(QString defaultStoragePath MEMBER defaultStoragePath CONSTANT)

public:

    enum Codec
    {
        Vorbis,
        Speex,
        PCM,
        FLAC
    };
    Q_ENUM(Codec)

    explicit Recorder(QObject* parent = 0);

    Q_INVOKABLE bool shouldMigrate() const;
    Q_INVOKABLE bool migrate();

    QString location() const;
    void setLocation(const QString &);

    int sampleRate() const;
    void setSampleRate(const int &sampleRate);

    QMultimedia::EncodingQuality encodingQuality() const;
    void setEncodingQuality(QMultimedia::EncodingQuality quality);

    QMultimedia::EncodingMode encodingMode() const;
    void setEncodingMode(QMultimedia::EncodingMode &mode);

    Recorder::Codec codec() const;
    void setCodec(const Codec &codec);

    QString durationLabel() const;

    bool recursiveSearch() const;
    void setRecursiveSearch(bool recursiveSearch);

    Q_INVOKABLE static QString formatTime(const qint64 &msec);

public slots:
    void startRecording();
    void removeFile(const QString &filePath);
    void renameFile(const QString &oldPath, const QString &newPath);

signals:
    void pathCreationFailed();
    void locationChanged();
    void sampleRateChanged();
    void encodingQualityChanged();
    void encodingModeChanged();
    void codecChanged();
    void durationLabelChanged();
    void recursiveSearchChanged();

private:
    static const QString defaultStoragePath;

    QSettings settings;
    QString mSdCardPath;
};

#endif // RECORDER_H
