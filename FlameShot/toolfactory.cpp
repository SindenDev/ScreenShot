

#include "toolfactory.h"
#include "arrowtool.h"
#include "circletool.h"
#include "copytool.h"
#include "exittool.h"
#include "linetool.h"
#include "markertool.h"
#include "movetool.h"
#include "penciltool.h"
#include "rectangletool.h"
#include "savetool.h"
#include "selectiontool.h"
#include "sizeindicatortool.h"
#include "undotool.h"
#include "blurtool.h"
#include "redotool.h"
#include "pintool.h"
#include "texttool.h"

ToolFactory::ToolFactory(QObject *parent) : QObject(parent) {

}

CaptureTool* ToolFactory::CreateTool(
        CaptureButton::ButtonType t,
        QObject *parent)
{
    CaptureTool *tool;
    switch (t) {
    case CaptureButton::TYPE_ARROW:
        tool = new ArrowTool(parent);
        break;
    case CaptureButton::TYPE_CIRCLE:
        tool = new CircleTool(parent);
        break;
    case CaptureButton::TYPE_COPY:
        tool = new CopyTool(parent);
        break;
    case CaptureButton::TYPE_EXIT:
        tool = new ExitTool(parent);
        break;
    case CaptureButton::TYPE_DRAWER:
        tool = new LineTool(parent);
        break;
    case CaptureButton::TYPE_MARKER:
        tool = new MarkerTool(parent);
        break;
    case CaptureButton::TYPE_MOVESELECTION:
        tool = new MoveTool(parent);
        break;
    case CaptureButton::TYPE_PENCIL:
        tool = new PencilTool(parent);
        break;
    case CaptureButton::TYPE_RECTANGLE:
        tool = new RectangleTool(parent);
        break;
    case CaptureButton::TYPE_SAVE:
        tool = new SaveTool(parent);
        break;
    case CaptureButton::TYPE_SELECTION:
        tool = new SelectionTool(parent);
        break;
    case CaptureButton::TYPE_SELECTIONINDICATOR:
        tool = new SizeIndicatorTool(parent);
        break;
    case CaptureButton::TYPE_UNDO:
        tool = new UndoTool(parent);
        break;
    case CaptureButton::TYPE_REDO:
        tool = new RedoTool(parent);
        break;
    case CaptureButton::TYPE_BLUR:
        tool = new BlurTool(parent);
        break;
    case CaptureButton::TYPE_PIN:
        tool = new PinTool(parent);
        break;
    case CaptureButton::TYPE_TEXT:
        tool = new TextTool(parent);
        break;
    default:
        tool = nullptr;
        break;
    }
    return tool;
}
