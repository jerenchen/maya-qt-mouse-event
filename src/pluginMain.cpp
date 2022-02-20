#include <maya/MFnPlugin.h>
#include <maya/MPxCommand.h>
#include <maya/MArgDatabase.h>
#include <maya/MArgList.h>
#include <maya/MSyntax.h>
#include <maya/MQtUtil.h>

#include <QtWidgets/QWidget>
#include "mouseeventfilter.h"
static MouseButtonEvent mouseButtonEvent;

class simpleMouseEventCmd : public MPxCommand
{
public:
  MStatus doIt(const MArgList& args) override;
  static void* creator() {return new simpleMouseEventCmd;}
  static MSyntax newSyntax();
};

MSyntax simpleMouseEventCmd::newSyntax()
{
  MSyntax syntax;
  syntax.useSelectionAsDefault(false);
  syntax.addFlag("l", "listen", MSyntax::kUnsigned);
  return syntax;
}

// event implementation 
void MouseButtonEvent::OnRMBRelease()
{
    MGlobal::displayInfo("Rigth Mouse Button Released!");
}
void MouseButtonEvent::OnMMBRelease()
{
    MGlobal::displayInfo("Middle Mouse Button Released!");
}
void MouseButtonEvent::OnLMBRelease()
{
    MGlobal::displayInfo("Left Mouse Button Released!");
}
void MouseButtonEvent::OnMouseButtonRelease()
{
  MGlobal::displayInfo("Mouse Button Released!");
}

// command implementation
MStatus simpleMouseEventCmd::doIt(const MArgList& args)
{
    MStatus status = MStatus::kSuccess;

    MArgParser argData(syntax(), args, &status);

    if (argData.isFlagSet("listen"))
    {
        // we listen to mouse release on time control
        QWidget* ctrl = MQtUtil::findControl("timeControl1");
        if (ctrl)
        {
            if (argData.flagArgumentBool("listen", 0))
            { 
                ctrl->installEventFilter(&mouseButtonEvent);
            }
            else
            {
                ctrl->removeEventFilter(&mouseButtonEvent);
            }
        }
    }

    return status;
}


MStatus initializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin plugin(obj, "Maya Qt Example", "Any", "Any");
    status = plugin.registerCommand(
        "simpleMouseEvent",
        simpleMouseEventCmd::creator,
        simpleMouseEventCmd::newSyntax
    );
    if (!status)
    {
        status.perror("Failed to register simpleMouseEvent");
    }

    return status;
}

MStatus uninitializePlugin(MObject obj)
{
    MStatus   status;
    MFnPlugin plugin( obj );

    // make sure we remove the event when unloading the plug-in
    QWidget* ctrl = MQtUtil::findControl("timeControl1");
    if (ctrl)
    {
        ctrl->removeEventFilter(&mouseButtonEvent);
    }

    status = plugin.deregisterCommand("simpleMouseEvent");
    if (!status)
    {
        status.perror("Failed to deregister simpleMouseEvent");
    }

    return status;
}
