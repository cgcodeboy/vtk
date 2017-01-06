#ifndef MY_CALLBACK_H
#define MY_CALLBACK_H

#include <vtkCommand.h>
#include <vtkSmartPointer.h>
#include <vtkObject.h>
#include <vtkBoxWidget.h>
#include <vtkTransform.h>
#include <vtkProp3D.h>

class MyCallback:public vtkCommand{
public:
	static MyCallback *New()
	{
            return new MyCallback();
	}

	virtual void Execute(vtkObject *caller, unsigned long eventId, void* callData)
        {
            vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
            vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
            widget->GetTransform(transform);
            widget->GetProp3D()->SetUserTransform(transform);
            widget->Delete();
        }
};

#endif
