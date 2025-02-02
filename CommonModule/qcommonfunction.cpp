#include "qcommonfunction.h"
#include <QIcon>
#include <QApplication>
#include <QFileDialog>

QCommonFunction::QCommonFunction(QObject *parent) :
    QObject(parent)
{
}

void QCommonFunction::SelectDirectory( QWidget* pParent, QString& strPath )
{
    QDir dir( QDir::currentPath( ) );
    dir.cdUp( );
    strPath = QFileDialog::getExistingDirectory( pParent,
                                                        "请选择导出数据保存的目录",
                                                 dir.absolutePath( ),
                                                 QFileDialog::ShowDirsOnly );
}

void QCommonFunction::SetWindowIcon( QWidget *pWidget )
{
    if ( NULL == pWidget ) {
        return;
    }

    QIcon icon( "./Image/Logo.gif" );
    pWidget->setWindowIcon( icon );
}

void QCommonFunction::SetApplicationIcon( )
{
    QIcon icon( "./Image/Logo.gif" );
    QApplication::setWindowIcon( icon );
}

void QCommonFunction::SetScrollAreaStyleSheet( QScrollArea *pScrArea )
{
    if ( NULL == pScrArea ) {
        return;
    }

    pScrArea->setStyleSheet( "border-image: url(./Image/Login.png);" );
}

void QCommonFunction::GetTableViewStyleSheet( QString &strTabViewStyleSheet )
{
    strTabViewStyleSheet = "QTableView { selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 0.5, y2: 0.5, stop: 0 #FF92BB, stop: 1 white);}";
}

void QCommonFunction::GetCbxStyleSheet( QString &strCbxStyleSheet )
{
    strCbxStyleSheet = "QComboBox::down-arrow { border-image: url(./Image/CbxDownArrow.png);}\n";
}

void QCommonFunction::GetDlgLoginStyleSheet( QString &strDlgStyleSheet )
{
    //"QDialog#DlgLogin { border-image: url(./Image/Login.png); }";
    strDlgStyleSheet = "QDialog { border-image: url(./Image/Login.png); }\n";
}

void QCommonFunction::GetUIStyleSheet( QString &strStyleSheet )
{
    QFile file( "./Image/UI.qss" );
    if ( file.open( QIODevice::ReadOnly ) ) {
        strStyleSheet = file.readAll( );
        file.close( );
    }

    return;
    QString strBtnStyleSheet;
    GetButtonStyleSheet( strBtnStyleSheet );

    QString strDlgStyleSheet;
    GetDlgLoginStyleSheet( strDlgStyleSheet );

    QString strTabViewStyleSheet;
    GetTableViewStyleSheet( strTabViewStyleSheet );

    //QString strCbxStyleSheet;
    //GetCbxStyleSheet( strCbxStyleSheet );

    strStyleSheet = QString( "%1%2%3" ).arg(
                strBtnStyleSheet,
                strDlgStyleSheet,
                strTabViewStyleSheet );

    //InformationBox( NULL, strStyleSheet );
}

void QCommonFunction::GetButtonStyleSheet( QString &strBtnStyleSheet )
{
    strBtnStyleSheet = "QPushButton { border-image: url(./Image/ButtonDefault.png); }\n\
                        QPushButton::pressed { border-image: url(./Image/ButtonDown.png); }\n";
    //"QPushButton::hover { background-image: url(./Image/ButtonHover.png); }\n";
}

void QCommonFunction::CryptString( QString& strValue )
{
    strValue = GetTextCodec( )->fromUnicode( strValue ).toBase64( ).toHex( );
}

void QCommonFunction::DecryptString( QString& strValue )
{
    strValue = QByteArray::fromBase64( QByteArray::fromHex( GetTextCodec( )->fromUnicode( strValue ) ) );
}

void QCommonFunction::ReadAllFile( const QString &strFile, QByteArray &byData )
{
   QFile file( strFile );
   if ( !file.exists( ) ) {
       return;
   }

   if ( !file.open( QFile::ReadOnly ) ) {
       return;
   }

   byData = file.readAll( );
   file.close( );
}

void QCommonFunction::GetAppCaptureImagePath( QString &strPath )
{
   strPath = qApp->applicationDirPath( ) + "/CaptureImage/";

   QDir dir(  strPath );
   if ( dir.exists( ) ) {
       return;
   }

   dir.mkpath( strPath );
}

void QCommonFunction::GetImageFromBase64( QByteArray& byImage, const QString& strBase64 )
{
    QByteArray byBase64 = strBase64.toUtf8( );
    byImage = QByteArray::fromBase64( byBase64 );
}

void QCommonFunction::GetImageBase64(QString &strBase64, const QString &strFile)
{
    if ( !QFile::exists( strFile ) ) {
        return;
    }

    QFile file( strFile );
    if ( !file.open( QFile::ReadOnly ) ) {
        return;
    }

    QByteArray byFile = file.readAll( );
    file.close( );

    GetImageBase64( strBase64, byFile );
}

void QCommonFunction::GetImageBase64( QString &strBase64, const QByteArray &byFile )
{
    strBase64 = byFile.toBase64( );
}

void QCommonFunction::String2DateTime( const QString &strDateTime, QDateTime &dtDateTime )
{
    dtDateTime = QDateTime::fromString( strDateTime, "yyyy-MM-dd HH:mm:ss" );
}

void QCommonFunction::String2Date( const QString& strDate, QDate& dtDate )
{
    dtDate = QDate::fromString( strDate, "yyyy-MM-dd" );
}

void QCommonFunction::String2Time( const QString& strTime, QTime& dtTime )
{
    dtTime = QTime::fromString( strTime, "HH:mm:ss" );
}

void QCommonFunction::DateTime2String( const QDateTime& dtDateTime, QString& strDateTime )
{
    strDateTime = dtDateTime.toString( "yyyy-MM-dd HH:mm:ss" );
}

void QCommonFunction::Date2String( const QDate& dtDate, QString& strDate )
{
    strDate = dtDate.toString( "yyyy-MM-dd" );
}

void QCommonFunction::Time2String( const QTime& dtTime, QString& strTime )
{
    strTime = dtTime.toString( "HH:mm:ss" );
}

void QCommonFunction::GetCurrentDateTime( QString &strDateTime )
{
    strDateTime = QDateTime::currentDateTime( ).toString( "yyyy-MM-dd HH:mm:ss" );
}

void QCommonFunction::GetDateTimeDigital( const QDateTime &dtDateTime, QString &strDateTime )
{
    strDateTime = dtDateTime.toString( "yyyyMMddHHmmss" );
}

void QCommonFunction::GetCurrentDateTimeDigital( QString &strDateTime )
{
    strDateTime = QDateTime::currentDateTime( ).toString( "yyyyMMddHHmmss" );
}

QTextCodec* QCommonFunction::GetTextCodec( )
{
    static QTextCodec* pCodec = NULL;

    if ( NULL != pCodec ) {
        return pCodec;
    }

    QList<QByteArray> lstCodec = pCodec->availableCodecs( );
    QString strText;
    bool bFound = false;

    for ( int nIndex = 0; nIndex < lstCodec.count( ); nIndex++ ) {
        QByteArray byData = lstCodec[ nIndex ];
        strText = QString( byData );
        qDebug( ) << strText << endl;

        if ( 0 == strText.toUpper().compare( "GB18030" ) ||
             0 == strText.toUpper().compare( "GBK" ) ||
             0 == strText.toUpper().compare( "GB2312" ) ) {
            bFound = true;
            break;
        }
    }

    if ( !bFound ) {
        strText = QString( "System" );
    }

    pCodec = QTextCodec::codecForName( strText.toLatin1( ) );
    return pCodec;
}

void QCommonFunction::SingleApplication( const char* pGUID )
{
    if ( NULL == pGUID ) {
        return;
    }

    QSharedMemory* pShareMem = new QSharedMemory( pGUID );

    if ( pShareMem->attach( ) ) {
        delete pShareMem;
        exit( 0 );
    } else {
        pShareMem->create( 1024 );
    }
}

void QCommonFunction::UninstallExcel( )
{
    qDebug( ) << Q_FUNC_INFO << "not install excel" << endl;
    QString strText = "请确认，你是否已经正确安装了Excel软件！";
    CriticalBox( NULL, strText );
}

void QCommonFunction::SetNeededColumnName( QAxObject *pWorksheet, QSqlQueryModel *pModel )
{
   if ( NULL == pWorksheet || NULL == pModel ) {
       return;
   }

   QAxObject* pCell;
   QVariant varRet;
   int nCols = pModel->columnCount( );

   for ( int j = 1; j < 1 + nCols; j++ ) {
       pCell = pWorksheet->querySubObject( "Cells( int, int )", 1, j );
       varRet = pModel->headerData( j - 1, Qt::Horizontal );
       varRet = pCell->dynamicCall( "SetValue( const QVariant& )", varRet );
   }
}

void QCommonFunction::Convert2ExcelValue( QString& strValue, QVariant& varValue )
{
    if ( QVariant::Date == varValue.type( ) ) {
        strValue = varValue.toDate( ).toString( "yyyy-MM-dd" );
    } else if ( QVariant::DateTime == varValue.type( ) ) {
        strValue = varValue.toDateTime( ).toString( "yyyy-MM-dd HH:mm:ss" );
    } else {
        strValue = varValue.toString( );
    }
}

bool QCommonFunction::ExportData2Excel( QString& strDir, QSqlQueryModel* pModel )
{
    bool bRet = false;
    QAxObject* pExcel = new QAxObject( "Excel.Application" );
    if ( NULL == pExcel || pExcel->isNull( ) ) {
        UninstallExcel( );
        return bRet;
    }

    if ( NULL == pModel ) {
        return bRet;
    }

    if ( strDir.isEmpty( ) ) {
        strDir = qApp->applicationDirPath( );
    }

    QString strFile;
    strFile = strDir + "\\" + QDateTime::currentDateTime( ).toString( "yyyyMMddHHmmss" ) + ".xls";

    QVariant varRet = pExcel->dynamicCall( "SetVisible(bool)", false );

    QAxObject* pWorkbooks = pExcel->querySubObject( "WorkBooks" );
    varRet = pWorkbooks->dynamicCall( "Add" );

    QAxObject* pWorkbook = pExcel->querySubObject( "ActiveWorkbook" );
    QAxObject* pWorksheet = pWorkbook->querySubObject( "WorkSheets( int )", 1 );

    //QAxObject* pWorksheets = pWorkbook->querySubObject("WorkSheets");
    //int nSheetCount = pWorksheets->property( "Count" ).toInt( );

    int nCols = pModel->columnCount( );
    int nRows = pModel->rowCount( ) + 1; // Title
    //QAxObject* pUsedRange = pWorksheet->querySubObject( "Cells( int, int )", nRows, nCols );
    QAxObject* pCell;
    QSqlRecord sqlRecord;
    QString strValue;

    SetNeededColumnName( pWorksheet, pModel );

    for ( int i = 2; i < 1 + nRows; i++ ) {
        sqlRecord = pModel->record( i - 2 );
        qDebug( ) << "Row" << endl;

        for ( int j = 1; j < 1 + nCols; j++ ) {
            pCell = pWorksheet->querySubObject( "Cells( int, int )", i, j );
            varRet = sqlRecord.value( j - 1 );
            //strValue = varRet.toString( );
            Convert2ExcelValue( strValue, varRet );
            qDebug( ) << strValue << " ";
            varRet = pCell->dynamicCall( "SetValue( const QVariant& )", strValue );
        }
    }

    pWorkbook->dynamicCall("SaveAs( const QString& )", strFile );
    //QMessageBox::information( NULL, "OK", "保存成功！" );
    varRet = pWorkbook->dynamicCall( "Close( )" );
    pWorksheet->clear( );

    varRet = pExcel->dynamicCall( "Quit( )" );

    delete pExcel;

    bRet = true;
    return bRet;
}

void QCommonFunction::LoadChartType( QComboBox* pCbx )
{
    pCbx->clear( );

    QString strValues[ ][ 3 ] = { { "折线", "line" },
                                  { "柱状", "bar" },
                                  { "饼状", "pie" } };

    for ( int nIndex = 0; nIndex < 3; nIndex++ ) {
        pCbx->addItem( strValues[ nIndex ][ 0 ], strValues[ nIndex ][ 1 ] );
    }
}

void QCommonFunction::DisableHelpButton( QWidget *pWidget )
{
    Qt::WindowFlags flags = pWidget->windowFlags( );
    flags &= ( ~Qt::WindowContextHelpButtonHint );
    pWidget->setWindowFlags( flags ); // Help
}

void QCommonFunction::DisableCloseButton( QWidget *pWidget )
{
    Qt::WindowFlags flags = pWidget->windowFlags( );
    flags &= ( ~Qt::WindowCloseButtonHint );
    pWidget->setWindowFlags( flags ); // Close
}

void QCommonFunction::SetButtonMiniSize( QAbstractButton *pBtn, int nWidth, int nHeight )
{
    if ( NULL == pBtn ) {
        return;
    }

    pBtn->setMinimumSize( nWidth, nHeight );
}

void QCommonFunction::SetMessageBoxProperty( QMessageBox& msgBox, QMessageBox::Icon icon,
                                             QString& strTitle, QString& strText, Qt::WindowModality winModality,
                                             bool bDisableHelpButton,bool bDisableCloseButton )
{
    msgBox.setIcon( icon );
    msgBox.setWindowTitle( strTitle );
    msgBox.setText( strText );
    msgBox.setWindowModality( winModality );

    if ( bDisableHelpButton ) {
        DisableHelpButton( &msgBox );
    }

    if ( bDisableCloseButton ) {
        DisableCloseButton( &msgBox );
    }
}

void QCommonFunction::InformationBox( QWidget *pParent, QString& strText )
{
  QMessageBox messageBox( pParent );
  QString strTitle = "提示";

  SetMessageBoxProperty( messageBox,  QMessageBox::Information,
                         strTitle, strText, Qt::ApplicationModal );

  QPushButton* pBtn = messageBox.addButton( "确定", QMessageBox::ActionRole );
  SetButtonMiniSize( pBtn );


  messageBox.exec( );
}

void QCommonFunction::CriticalBox( QWidget *pParent, QString& strText )
{
  QMessageBox messageBox( pParent );
  QString strTitle = "错误";

  SetMessageBoxProperty( messageBox,  QMessageBox::Critical,
                         strTitle, strText, Qt::ApplicationModal );

  QPushButton* pBtn = messageBox.addButton( "确定", QMessageBox::ActionRole );
  SetButtonMiniSize( pBtn );


  messageBox.exec( );
}

QMessageBox::StandardButtons QCommonFunction::MessageBox( QString &strTitle, QString &strText, QWidget *pParent, QMessageBox::Icon icon )
{
    QMessageBox::StandardButtons stdButtons;
    QMessageBox messageBox( pParent );

    SetMessageBoxProperty( messageBox,  icon,
                           strTitle, strText, Qt::ApplicationModal );

    QAbstractButton *btnOK = ( QAbstractButton* ) messageBox.addButton( "确定", QMessageBox::ActionRole );
    SetButtonMiniSize( btnOK );

    QAbstractButton *btnCancel = ( QAbstractButton* ) messageBox.addButton( "取消", QMessageBox::ActionRole );
    SetButtonMiniSize( btnCancel );

    messageBox.exec( );
    QAbstractButton* btnClicked = messageBox.clickedButton( );

    if ( btnClicked == btnOK ) {
        stdButtons = QMessageBox::Ok;
    } else if ( btnClicked == btnCancel ) {
        stdButtons = QMessageBox::Cancel;
    }

    return stdButtons;
}

QMessageBox::StandardButtons QCommonFunction::SaveDataBox(QWidget *pParent)
{
    QMessageBox::StandardButtons stdButtons;
    QMessageBox messageBox( pParent );
    QString strTitle = "提示";
    QString strText = "确定要保存数据吗？";

    SetMessageBoxProperty( messageBox,  QMessageBox::Question,
                           strTitle, strText, Qt::ApplicationModal );

    QAbstractButton *btnOK = ( QAbstractButton* ) messageBox.addButton( "确定", QMessageBox::ActionRole );
    SetButtonMiniSize( btnOK );

    QAbstractButton *btnCancel = ( QAbstractButton* ) messageBox.addButton( "取消", QMessageBox::ActionRole );
    SetButtonMiniSize( btnCancel );

    messageBox.exec( );
    QAbstractButton* btnClicked = messageBox.clickedButton( );

    if ( btnClicked == btnOK ) {
        stdButtons = QMessageBox::Ok;
    } else if ( btnClicked == btnCancel ) {
        stdButtons = QMessageBox::Cancel;
    }

    return stdButtons;
}

bool QCommonFunction::CloseDiaglogBox( QWidget *pParent, QCloseEvent *pEvent )
{
    bool bRet = false;
    QMessageBox messageBox( pParent );
    QString strTitle = "提示";
    QString strText = "确定要关闭该对话框吗？";

    SetMessageBoxProperty( messageBox,  QMessageBox::Question,
                           strTitle, strText, Qt::ApplicationModal );

    QAbstractButton *btnOK = ( QAbstractButton* ) messageBox.addButton( "确定", QMessageBox::ActionRole );
    SetButtonMiniSize( btnOK );

    QAbstractButton *btnCancel = ( QAbstractButton* ) messageBox.addButton( "取消", QMessageBox::ActionRole );
    SetButtonMiniSize( btnCancel );

    messageBox.exec( );
    QAbstractButton* btnClicked = messageBox.clickedButton( );

    if ( btnClicked == btnOK ) {
        pEvent->accept( );
        bRet = true;
    } else if ( btnClicked == btnCancel ) {
        pEvent->ignore( );
    }

    return bRet;
}

QMessageBox::StandardButtons QCommonFunction::DeleteDataBox( QWidget *pParent, QString& strText )
{
    QMessageBox::StandardButtons stdButtons;
    QMessageBox messageBox( pParent );
    QString strTitle = "提示";

    SetMessageBoxProperty( messageBox,  QMessageBox::Question,
                           strTitle, strText, Qt::ApplicationModal );

    QAbstractButton *btnOK = ( QAbstractButton* ) messageBox.addButton( "确定", QMessageBox::ActionRole );
    SetButtonMiniSize( btnOK );

    QAbstractButton *btnCancel = ( QAbstractButton* ) messageBox.addButton( "取消", QMessageBox::ActionRole );
    SetButtonMiniSize( btnCancel );

    messageBox.exec( );
    QAbstractButton* btnClicked = messageBox.clickedButton( );

    if ( btnClicked == btnOK ) {
        stdButtons = QMessageBox::Ok;
    } else if ( btnClicked == btnCancel ) {
        stdButtons = QMessageBox::Cancel;
    }

    return stdButtons;
}

bool QCommonFunction::SystemCloseEvent( QWidget* pParent, QCloseEvent *pEvent )
{
    bool bRet = true;
    QMessageBox messageBox( pParent );
    QString strTitle = "提示";
    QString strText = "确定要退出吗？";

    SetMessageBoxProperty( messageBox,  QMessageBox::Question,
                           strTitle, strText, Qt::ApplicationModal );

    QAbstractButton *btnOK = ( QAbstractButton* ) messageBox.addButton( "确定", QMessageBox::ActionRole );
    SetButtonMiniSize( btnOK );

    QAbstractButton *btnCancel = ( QAbstractButton* ) messageBox.addButton( "取消", QMessageBox::ActionRole );
    SetButtonMiniSize( btnCancel );

    messageBox.exec( );
    QAbstractButton* btnClicked = messageBox.clickedButton( );

    if ( btnClicked == btnOK ) {
        pEvent->accept( );
        bRet = true;
    } else if ( btnClicked == btnCancel ) {
        pEvent->ignore( );
        bRet = false;
    }

    return bRet;
}

void QCommonFunction::GetSpName( ParkSolution::SpType eSpType, QString& strSpName )
{
    ParkSolution::SpName spName;

    switch ( eSpType ) {
    case ParkSolution::SpVehicleEnter :
        strSpName = spName.strSpVehicleEnter;
        break;

    case ParkSolution::SpQueryServiceData :
        strSpName = spName.strSpQueryServiceData;
        break;

    case ParkSolution::SpQueryCustomerData :
        strSpName = spName.strSpQueryCustomerData;
        break;

    case ParkSolution::SpQueryCustomerVehicleData :
        strSpName = spName.strSpQueryCustomerVehicleData;
        break;

    case ParkSolution::SpQueryCommonDataInfo :
        strSpName = spName.strSpQueryCommonDataInfo;
        break;

    case ParkSolution::SpChangeCustomerVehicleDataUI :
        strSpName = spName.strSpChangeCustomerVehicleData;
        break;

    case ParkSolution::SpChangeCustomerVehicleDataDelete :
        strSpName = spName.strSpIgnoreOrDeleteCustomer;
        break;

    case ParkSolution::SpChangeServiceRecordUI :
        strSpName = spName.strSpChangeServiceRecord;
        break;

    case ParkSolution::SpChangeServiceRecordDelete :
        strSpName = spName.strSpChangeServiceRecord;
        break;

    case ParkSolution::SpImportCustomer :
        strSpName = spName.strSpImportCustomer;
        break;

    case ParkSolution::SpExportCustomer :
        strSpName = spName.strSpExportCustomer;
        break;

    case ParkSolution::SpQueryUserInfo :
        strSpName = spName.strSpQueryUserInfo;
        break;

    case ParkSolution::SpQueryInOutImage :
        strSpName = spName.strSpQueryInOutImage;
        break;

    case ParkSolution::SpQueryCommonDataByType :
        strSpName = spName.strSpQueryCommonDataByType;
        break;

    case ParkSolution::SpChangeCommonDataUI :
        strSpName = spName.strSpChangeCommonData;
        break;

    case ParkSolution::SpChangeCommonDataDelete :
        strSpName = spName.strSpChangeCommonData;
        break;

    case ParkSolution::SpWriteInOutRecord :
        strSpName = spName.strSpWriteInOutRecord;
        break;

    case ParkSolution::SpQueryInOutRecord :
        strSpName = spName.strSpQueryInOutRecord;
        break;

    case ParkSolution::SpReportInfo :
        strSpName = spName.strSpReportInfo;
        break;

    case ParkSolution::SpChartInfo :
        strSpName = spName.strSpChartInfo;
        break;

    case ParkSolution::SpQueryCustomerDataByPlate :
        strSpName = spName.strSpQueryCustomerDataByPlate;
        break;

    case ParkSolution::SpQueryVehicleDataByCustomer :
        strSpName = spName.strSpQueryVehicleDataByCustomer;
        break;

    case ParkSolution::SpQueryServiceDataByPlate :
        strSpName = spName.strSpQueryServiceDataByPlate;
        break;

    case ParkSolution::SpExportReport2Excel :
        strSpName = spName.strSpExportReport2Excel;
        break;
    }
}

void QCommonFunction::GetSpXmlPattern( ParkSolution::SpType eSpType, QString& strXmlPattern )
{
    ParkSolution::SpXmlPattern xmlPattern;

    switch ( eSpType ) {
    case ParkSolution::SpVehicleEnter :
        strXmlPattern = xmlPattern.strXmlVehicle;
        break;

    case ParkSolution::SpQueryServiceData :
        strXmlPattern = xmlPattern.strXmlQueryServiceData;
        break;

    case ParkSolution::SpQueryCustomerData :
        strXmlPattern = xmlPattern.strXmlQueryCustomerData;
        break;

    case ParkSolution::SpQueryCustomerVehicleData :
        strXmlPattern = xmlPattern.strXmlQueryCustomerVehicleData;
        break;

    case ParkSolution::SpQueryCommonDataInfo :
        strXmlPattern = xmlPattern.strXmlQueryCommonDataInfo;
        break;

    case ParkSolution::SpChangeCustomerVehicleDataUI :
        strXmlPattern = xmlPattern.strXmlChangeCustomerVehicleDataUI;
        break;

    case ParkSolution::SpChangeCustomerVehicleDataDelete :
        strXmlPattern = xmlPattern.strXmlChangeCustomerVehicleDataDelete;
        break;

    case ParkSolution::SpChangeServiceRecordUI :
        strXmlPattern = xmlPattern.strXmlChangeServiceRecordUI;
        break;

    case ParkSolution::SpChangeServiceRecordDelete :
        strXmlPattern = xmlPattern.strXmlChangeServiceRecordDelete;
        break;

    case ParkSolution::SpImportCustomer :
        strXmlPattern = xmlPattern.strXmlImportCustomer;
        break;

    case ParkSolution::SpExportCustomer :
        strXmlPattern = xmlPattern.strXmlExportCustomer;
        break;

    case ParkSolution::SpQueryUserInfo :
        strXmlPattern = xmlPattern.strXmlQueryUserInfo;
        break;

    case ParkSolution::SpQueryInOutImage :
        strXmlPattern = xmlPattern.strXmlQueryInOutImage;
        break;

    case ParkSolution::SpQueryCommonDataByType :
        strXmlPattern = xmlPattern.strXmlQueryCommonDataByType;
        break;

    case ParkSolution::SpChangeCommonDataUI :
        strXmlPattern = xmlPattern.strXmlChangeCommonDataUI;
        break;

    case ParkSolution::SpChangeCommonDataDelete :
        strXmlPattern = xmlPattern.strXmlChangeCommonDataDelete;
        break;

    case ParkSolution::SpWriteInOutRecord :
        strXmlPattern = xmlPattern.strXmlWriteInOutRecord;
        break;

    case ParkSolution::SpQueryInOutRecord :
        strXmlPattern = xmlPattern.strXmlQueryInOutRecord;
        break;

    case ParkSolution::SpReportInfo :
        strXmlPattern = xmlPattern.strXmlReportInfo;
        break;

    case ParkSolution::SpChartInfo :
        strXmlPattern = xmlPattern.strXmlChartInfo;
        break;

    case ParkSolution::SpQueryCustomerDataByPlate :
        strXmlPattern = xmlPattern.strXmlQueryCustomerDataByPlate;
        break;

    case ParkSolution::SpQueryVehicleDataByCustomer :
        strXmlPattern = xmlPattern.strXmlQueryVehicleDataByCustomer;
        break;

    case ParkSolution::SpQueryServiceDataByPlate :
        strXmlPattern = xmlPattern.strXmlQueryServiceDataByPlate;
        break;

    case ParkSolution::SpExportReport2Excel :
        strXmlPattern = xmlPattern.strXmlExportReport2Excel;
        break;
    }
}
