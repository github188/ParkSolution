﻿#ifndef QPLATETHREAD_H
#define QPLATETHREAD_H

#include "LPRModule_global.h"
#include <QThread>
#include "qplateevent.h"
#include <winsock2.h>
#include <windows.h>
#include "../CommonModule/qcommonfunction.h"
#include "../ConfigModule/qconfigurator.h"
#include "../CommonModule/qbasethread.h"
#include <QStringList>
#include "LPKernelEx.h"
#include <QMutex>
#include <QMutexLocker>

#define PLATE_RESULT_ITEMS ( int ) 8

class LPRMODULESHARED_EXPORT QPlateThread : public QBaseThread
{
    Q_OBJECT
public:
    static QPlateThread* GetInstance( );

    void PostPlateFileRecognize( QString& strFile, int nChannel, bool bMultiThread = false, bool bDeleteFile = false );
    void PostPlateFileRecognize( QString& strFile, QString& strIP, bool bMultiThread = false, bool bDeleteFile = false );
    void PostPlateFileRecognize( QByteArray& byData, QString& strFile, int nChannel, bool bMultiThread = false, bool bDeleteFile = false );

    void PostPlateVideoRecognize( QByteArray& byVideo, int nWidth, int nHeight, int nChanne, bool bMultiThread = false );
    void PostPlateVideoRecognize( QByteArray& byVideo, int nWidth, int nHeight, QString& strIP, bool bMultiThread = false );
    void PostPlateVideoRecognize( QByteArray& byVideo, int nWidth, int nHeight, int nChannel, QString& strIP, bool bMultiThread = false );

    void PostPlateInitEvent( int nFormat, int nChannel, bool bMultiThread = false );
    void PostPlateUninitEvent( int nChannel, bool bMultiThread = false );
    bool SetRecognizeFlag( );
    void SetRecognizeFlag( bool bRecognize );
    bool GetRecognizeFlag( );
    void SetPlateWay( int nWay );
    void SetPlateMultiThread( bool bMulti );
    bool GetPlateMultiThread( );
    void SetDongleOneWay( bool bOneWay );

    ~QPlateThread( );

protected:
    void run( );
    void customEvent( QEvent *e );

    bool ThreadInitialize( );
    void ThreadUninitialize( );

    void PostEvent( QEvent *pEvent );

private:
    explicit QPlateThread(QObject *parent = 0);

    void FileRecognize( QPlateEvent* pEvent );
    void VideoRecognize( QPlateEvent* pEvent );
    void InitSDK( QPlateEvent* pEvent );
    void UninitSDK( QPlateEvent* pEvent );

    BOOL InitVZSDK( int nFormat, qint32 nChannel  );
    void UninitVZSDK( qint32 nChannel  );

    QString GetPlateMoveDirection( int nDirection );
    QString GetWidthHeight( TH_PlateResult* pResult );
    QString GetPlateColor( qint32 nColor );
    void GetResultInfo( QStringList& lstResult, QString& strFile, bool bSuccess, qint32 nNum, TH_PlateResult* pResult );
    void SendUIResult( int nChannel, bool bSuccess, qint32 nNum, TH_PlateResult* pResult, bool bVideo, QPlateEvent* pEvent );

    QPlateThread* CreateSubThread( QString& strThreadKey );
    static QPlateThread* NewThread( );

private:
    static QPlateThread* pThreadInstance;
    QTextCodec* pCodec;
    QString strPlatePath;
    bool bStopRecognize;
    int nPlateWay;
    bool bDongleOneWay;
    bool bPlateMultiThread;
    typedef QHash< QString, QPlateThread* > QThreadHash;
    QThreadHash objSubThreadHash;
    ParkSolution::QIntStringHash hashChannelPlate;
    bool bOutputAllPlate;
    QConfigurator* pConfigurator;
    
signals:
    void PlateResult( QStringList lstPlateParam, int nChannel, bool bSuccess, bool bVideo );
    void PlateIpcResult( QStringList lstPlateParam, int nChannel, QString strIP, bool bSuccess, bool bVideo );
    void UIPlateResult( QString strPlate, int nChannel, bool bSuccess,
                        bool bVideo, int nWidth, int nHeight, int nConfidence,
                        QString strDirection, QByteArray byData, QRect rectPlate, QRect rectVideo );
    
private slots:
    void HandlePlateResult( QStringList lstPlateParam, int nChannel, bool bSuccess, bool bVideo );
    void HandlePlateIpcResult( QStringList lstPlateParam, int nChannel, QString strIP, bool bSuccess, bool bVideo );
    void HandleUIPlateResult( QString strPlate, int nChannel, bool bSuccess,
                        bool bVideo, int nWidth, int nHeight, int nConfidence,
                        QString strDirection, QByteArray byData, QRect rectPlate, QRect rectVideo );
};

#endif // QPLATETHREAD_H
