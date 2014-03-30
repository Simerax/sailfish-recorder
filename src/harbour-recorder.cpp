/*
    A simple audio recording tool.
    Copyright (C) 2014  Corné Dorrestijn

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtQuick>
#include "harbour-recorder.h"
#include <sailfishapp.h>


int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/template.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //
    // To display the view, call "show()" (will show fullscreen on device).

    qmlRegisterType<Recorder>("harbour.recorder.Recorder", 1, 0, "Recorder");

    return SailfishApp::main(argc, argv);
}

Recorder::Recorder(QObject *parent) : QObject(parent) {
    QCoreApplication::setOrganizationName("corne.info");
    QCoreApplication::setOrganizationDomain("www.corne.info");
    QCoreApplication::setApplicationName("Recorder");

    audioRecorder = new QAudioRecorder(this);
    curRecordingState = 0;
}

int Recorder::recordingState() {
    return curRecordingState;
}

QStringList Recorder::getExistingFiles() {
    QDir dir(getLocation());
    dir.setSorting(QDir::Time);
    dir.setFilter(QDir::Files);
    QStringList list = dir.entryList();
    return list;
}

void Recorder::removeFile(QString filename) {
    QFile(getLocation() + "/" + filename).remove();
}

QString Recorder::startRecording() {
    if(audioRecorder->state() == QMediaRecorder::StoppedState) {
        qWarning() << " === Recording started ===";
        QDateTime currentDate = QDateTime::currentDateTime();

        QString location = getLocation() + "/recording-" + currentDate.toString("yyyyMMddHHmmss") + ".wav";

        if(!QDir(getLocation()).exists()) {
            bool madeDirs = QDir().mkpath(getLocation());
            if(!madeDirs) {
                return "nofolder";
            }
        }

        audioRecorder->setOutputLocation(QUrl(location));
        audioRecorder->record();
        curRecordingState = 1;
        emit recordingChanged();
        return "recording";
    }
    return "recording";
}


void Recorder::pauseRecording() {
    curRecordingState = 2;
    audioRecorder->pause();
    emit recordingChanged();
}

void Recorder::resumeRecording() {
    curRecordingState = 1;
    audioRecorder->record();
    emit recordingChanged();
}

void Recorder::stopRecording() {
    // doesnt work in cover?
    // if(audioRecorder->state() == QMediaRecorder::RecordingState) {
    qWarning() << " === Recording stopped ===";
    audioRecorder->stop();
    curRecordingState = 0;
    emit recordingChanged();
    // }
}

void Recorder::setLocation(QString location) {
    QSettings settings;
    settings.setValue("recorder/fileLocation", location);
}

QString Recorder::getLocation() {
    QSettings settings;
    return settings.value("recorder/fileLocation",  QDir::homePath() + "/Recordings").toString();
}
