

#include "modificationcommand.h"
#include <QPainter>

ModificationCommand::ModificationCommand(QPixmap *p, CaptureTool *t) :
    m_pixmap(p), m_tool(t)
{
    setText(t->name());
}

void ModificationCommand::undo() {
    m_tool->undo(*m_pixmap);
}

void ModificationCommand::redo() {
    QPainter p(m_pixmap);
    p.setRenderHint(QPainter::Antialiasing);
    m_tool->process(p, *m_pixmap, true);
}
