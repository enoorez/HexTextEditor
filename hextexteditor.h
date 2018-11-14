/*
 * ʮ�������ı��༭��
 * �༭���������ı��༭�����:
 *  1. �кſ�
 *  2. ʮ�������ı���
 *  3. ASCII���
 * ʮ�������ı��༭���ṩ�Ĺ�����:
 *  1. ������Ķ������������ı�����ʽ��ʾ
 *  2. �ṩ�޸ĵĹ���

 *  �����ᷢ�����ź�:
     void    wheelUp( int nLine );    ���������Ϲ���
     void    wheelDown( int nLine );  ���������¹������Ǹ�
     void    mouseOnLineNumer( const QPoint& pos ); ������к���
     void    mouseOnHexText( const QPoint& pos );   �����ʮ�������ַ�����
     void    mouseOnString( const QPoint& pos );    ������ַ�����
 */
#ifndef HEXTEXTEDITOR_H
#define HEXTEXTEDITOR_H
#include <QAbstractScrollArea>
#include <QWheelEvent>
#include "tokenlist.h"
#include "qscrollbar.h"


class QScrollBar;
class QMenu;

#define LINE_ITEM_COUNT 16


// ѡ������ṹ
typedef struct SelectRangle
{
    int     mLineNumber;
    int     mRow;    // �к�
    int     mCount;  // ѡ�и���

    void    setRangle( int beginIndex , int endIndex )
    {
        mLineNumber = beginIndex/LINE_ITEM_COUNT;
        mRow = beginIndex % LINE_ITEM_COUNT;
        mCount = endIndex - beginIndex > 16 ? 16 : endIndex - beginIndex;
    }

}SelectRangle;


enum ColumnCode
{
    e_lineNumber, // �к���
    e_hexText,// ʮ�������ı���
    e_string,// �ַ�����
};


class HexEidtStack
{
public:


public:
    typedef struct NODE
    {
        int    index;
        int    data;
        bool   isInsert;
    }NODE;

    bool    isEmpty( )const {return mData.isEmpty(); }
    int     size( )const{return mData.size ();};
    void    clear( ){mData.clear();};
    void    push( int index,unsigned char data ,bool isInsert=false) {mData.push_back(NODE{index,data,isInsert});}
    bool    pop(NODE& data )
    { 
        if( mData.isEmpty( ) )
            return false;
        data = mData.last( );
        mData.erase( --mData.end( ) );
        return true;
    };

protected:
    QList<NODE> mData;

};

class HexTextEditor : public QAbstractScrollArea
{
    Q_OBJECT

public:
    HexTextEditor( QWidget* parent =nullptr);

public:
    class Cursor
    {
        int mPos;
        int mLineWidth;
    public:
        Cursor(int pos,int lineWidth=LINE_ITEM_COUNT) :mPos(pos),mLineWidth(lineWidth){}

        void moveNext(){++mPos;}
        void movePre(){--mPos;}
        void moveNextLine(int lineWidth=-1){ mPos+= lineWidth==-1?mLineWidth:lineWidth;}
        void movePreLine(int lineWidth=-1){mPos-=lineWidth==-1?mLineWidth:lineWidth;}
        void setPos(int pos){mPos=pos;}
        int pos()const{return mPos;}

        int lineWidth() const;
        void setLineWidth(int lineWidth);
    };

protected:
    /*
     * �к����Ŀ��Ȼ������кŵĴ�С�������.
     */
    int             getLineNumberColumnWidth( )const;

    /**
      * �к��� | ʮ�������ı��� | �ַ�����
      * һ������������, ÿ������֮��Ŀ�϶Ϊ5�����ص�.
      */
    bool            isOnHexTextColumn( const QPoint& pos );
    bool            isOnLineNumberColumn( const QPoint& pos );
    bool            isOnStringColumn( const QPoint& pos );

    virtual void    paintSelectRect( QPainter& painter );
    virtual void    paintCursor(QPainter& painter);
    virtual void    paintLineNumber( QPainter& painter );
    virtual void    paintHexText( QPainter& painter );
    virtual void    paintString( QPainter& painter );
    virtual void    paintHexTextLine( QPainter& painter ,
                                      int line, int row, // ���������괦��ʼ��
                                      const char * pStr ,   // ���Ի����ַ���(Ĭ����47���ַ�)
                                      int    nSize ,/*�ַ������ַ�����*/
                                      int   nIndex  // �ַ����׵�ַ����������������
                                      );
    void            drawText( QPainter& painter ,
                              const char *pStr ,
                              int   nLen ,
                              ColumnCode column ,
                              int line ,
                              int row );

    virtual void    paintEvent( QPaintEvent * event );
    virtual void    wheelEvent( QWheelEvent * e );
    virtual void    resizeEvent( QResizeEvent * event );
    virtual void    mouseMoveEvent( QMouseEvent * e );
    virtual void    mousePressEvent( QMouseEvent * e );
    virtual void    mouseReleaseEvent( QMouseEvent * e );
    virtual void    keyPressEvent( QKeyEvent * e );
    virtual void    keyReleaseEvent( QKeyEvent * e );
    virtual void    contextMenuEvent( QContextMenuEvent *event );


public:
    static int      getNumerOfDigit( int num );
    static void     hexToString( const char* pHex , int nLen , char* pBuff );
    static void     getHexString( const char* pHex , int nLen , char* pBuff );


signals:
    void            wheelUp( int nLine );  // ���������Ϲ���ʱ
    void            wheelDown( int nLine );// ���������¹���ʱ
    void            mouseOnLineNumer( const QPoint& pos ); // ��꾭���к���ʱ
    void            mouseOnHexText( int  line , int row ); // ��꾭��ʮ�������ı���ʱ
    void            mouseOnString( int  line , int row );  // ��꾭���ַ�����ʱ
    void            menuPopup( QMenu *menu );

public slots:
    void            menuCopyTriggered( );  // ����ʮ�������ı�
    void            menuCopyAsCStyle();
    void            menuSelectAllTriggered( ); // ȫѡ
    void            menuGotoByteTriggered(); // ��ת��ָ����ַ
    void            menuGotoLineTriggered( ); // ��ת��ָ����
    void            menuEditTriggered( ); // �༭
    void            menuParseFromHex();
    void            menuParseFromString();
    void            menuParseFromHexString();

    void            scrollbarMove( int nStep );

public:

    // ��������
    void            setFont(const QFont& font );
    void            setVisualPos(int pos );
    int             getVisualPos( )const;

    int             getVisualLine( )const; 
    void            setVisualLine( int line );

    bool            posIsOnVisual( int pos )const;
    bool            lineIsOnVisual( int line)const;

    int             positionToLineNumber(int pos )const;
    int             lineToPosition( int line )const;

    int             mousePosToIndex(const QPoint& pos );


    int             getMaxVisualLine( )const; 

    int             getLineHeight( )const;
    int             getCharWidth( )const ;

    // ���ù���������һ�ε�����
    int             getRollStep( ) const;
    void            setRollStep( int rollStep );

    void            setHexData( const QByteArray& Data );
    QByteArray      hexData()const;

    // ����ѡ���������Ϊ: [��ʼ��ַ,������ַ)
    void            setSelection( int nBeginIndex , int nEndIndex );
    bool            getSelectionText(QString& selectText );
    int             getSlectionLength( )const;
    void            highlight( int nLine , int row , int count ,const QColor& color);

    void            addToken( const TokenList::Token& token );
    bool            updateToken( const TokenList::Token& token );
    TokenList::Token* findToken( int line , int row );

    void            clearToken( );
    void            cleaer( );


public:
    QByteArray      getRowData( )const;
    bool            edit( int nIndex , const char data );
    void            undo( ); // ����
    void            redo( ); // ����
    int             findString( const QString& string);
    int             findByte( const unsigned char* byte , int size);

    void            configureColor( ); // ����һ���Ի���, ����������ɫ
    QColor          getColorSelect() const;
    void            setColorSelect(const QColor &colorSelect);

    QColor          getBKColor() const;
    void            setBKColor(const QColor &bKColor);

    QColor          getFontColor() const;
    void            setFontColor(const QColor &fontColor);

    QColor          getBKColorLineNumber() const;
    void            setBKColorLineNumber(const QColor &bKColorLineNumber);

    QColor          getColorLineNumer() const;
    void            setColorLineNumer(const QColor &colorLineNumer);

protected:
    QByteArray      mHexData;   // ����������(������ʾ)


    QList<SelectRangle>    mSelect; // ��ѡ�е���

    int             mCurLine;  // �༭�����Ӳ��ֵ��к�
    int             mMaxLine;  // �ı�����ʵ�ʵ��������
    int             mMaxVisualLine; // �༭���ܿ��Ӳ��ֵ��������

    int             mRollStep ; // ������ÿ�ι����ĺ���

    int             mLineHeight; // �и�
    int             mCharWidth; // �ֿ�

    QColor          mColorLineNumer; // �кŵ���ɫ 
    QColor          mBKColorLineNumber;// �кŵı�����ɫ
    QColor          mColorHexText; // ʮ�������ı�������ɫ
    QColor          mBKColorHexText; // ʮ�������ı����ı�����ɫ
    QColor          mColorSelect; // ѡ������ı�����ɫ


    QFontMetrics*   mFontMetrics; // ������Ϣ

    TokenList       mTokenList; // ��ɫ��

private:
    bool            mControlKeyStatus;
    HexEidtStack    mEditUndoStack; 
    HexEidtStack    mEditRedoStack;
    Cursor          mCursor;

    QScrollBar*     mScrollBar;
    bool            mMouseLbuttonStatus; //true : ��굯��, false: ��갴��
    int             mSelectBeginIndex; // ѡ������Ŀ�ʼ�ֽ�
    int             mSelectEndIndex;// ѡ������Ľ����ֽ�

    int             mLineNumberWidth; // �к����Ŀ���
    int             mHexTextWidth; // ʮ�������ı����Ŀ���
    int             mStringWidth; // �ַ������Ŀ���
};

#endif // HEXTEXTEDITOR_H