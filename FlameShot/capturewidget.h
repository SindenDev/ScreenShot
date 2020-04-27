
#pragma once

#include "capturebutton.h"
#include "capturecontext.h"
#include "capturetool.h"
#include "confighandler.h"
#include "selectionwidget.h"
#include "utilitypanel.h"
#include "buttonhandler.h"
#include <QWidget>
#include <QUndoStack>
#include <QPointer>

class QPaintEvent;
class QResizeEvent;
class QMouseEvent;
class CaptureModification;
class QNetworkAccessManager;
class QNetworkReply;
class ColorPicker;
class Screenshot;
class NotifierBox;
class HoverEventFilter;

class CaptureWidget : public QWidget {
    Q_OBJECT

public:

    explicit CaptureWidget(const uint id = 0,
                           const QString &savePath = QString(),
                           bool fullScreen = true,
                           QWidget *parent = nullptr);
    ~CaptureWidget();


    void updateButtons();
    QPixmap pixmap();

public slots:
    void deleteToolwidgetOrClose();

signals:
    void captureTaken(uint id, QPixmap p);
    void captureFailed(uint id);
    void colorChanged(const QColor &c);
    void thicknessChanged(const int thickness);

private slots:

    // TODO replace with tools
    void copyScreenshot();
    void saveScreenshot();
    void undo();
    void redo();
    void togglePanel();
    void childEnter();
    void childLeave();

    void leftResize();
    void rightResize();
    void upResize();
    void downResize();

    void setState(CaptureButton *b);
    void processTool(CaptureTool *t);
    void handleButtonSignal(CaptureTool::Request r);
    void setDrawColor(const QColor &c);
    void setDrawThickness(const int &t);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void wheelEvent(QWheelEvent *);
    void resizeEvent(QResizeEvent *);
    void moveEvent(QMoveEvent *);

    // Context information
    CaptureContext m_context;

    // Main ui color
    QColor m_uiColor;
    // Secondary ui color
    QColor m_contrastUiColor;

    // Outside selection opacity
    int m_opacity;
    // utility flags
    bool m_mouseIsClicked;
    bool m_rightClick;
    bool m_newSelection;
    bool m_grabbing;
    bool m_showInitialMsg;
    bool m_captureDone;
    bool m_previewEnabled;
    bool m_adjustmentButtonPressed;

private:
    void initContext(const QString &savePath, bool fullscreen);
    void initPanel();
    void initSelection();
    void initShortcuts();
    void updateSizeIndicator();
    void updateCursor();
    void pushToolToStack();
    void makeChild(QWidget *w);

    QRect extendedSelection() const;
    QRect extendedRect(QRect *r) const;

    QUndoStack m_undoStack;
    QPointer<CaptureButton> m_sizeIndButton;
    // Last pressed button
    QPointer<CaptureButton> m_activeButton;
    QPointer<CaptureTool> m_activeTool;
    QPointer<QWidget> m_toolWidget;

    ButtonHandler *m_buttonHandler;
    UtilityPanel *m_panel;
    ColorPicker *m_colorPicker;
    ConfigHandler m_config;
    NotifierBox *m_notifierBox;
    HoverEventFilter *m_eventFilter;
    SelectionWidget *m_selection;

    QPoint m_dragStartPoint;
    SelectionWidget::SideType m_mouseOverHandle;
    uint m_id;
};
