

#include "capturecontext.h"

QPixmap CaptureContext::selectedScreenshotArea() const {
    if (selection.isNull()) {
        return screenshot;
    } else {
        return screenshot.copy(selection);
    }
}
