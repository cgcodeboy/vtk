#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include "MyCallback.h"

int main()
{
	vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
	cone->SetRadius(0.5);
	cone->SetHeight(3);
	cone->SetResolution(20);
	cone->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(cone->GetOutputPort());
	mapper->Update();

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
	render->AddActor(actor);
	render->SetBackground(0.5, 0.6, 0.5);

	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	window->AddRenderer(render);
	window->SetSize(600, 480);
	window->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    interactor->SetInteractorStyle(style);

    vtkSmartPointer<MyCallback> callback = vtkSmartPointer<MyCallback>::New();

    vtkSmartPointer<vtkBoxWidget> widget = vtkSmartPointer<vtkBoxWidget>::New();
    widget->SetInteractor(interactor);
    widget->SetPlaceFactor(1.5);
    widget->SetProp3D(actor);
    widget->AddObserver(vtkCommand::RightButtonPressEvent,callback);
    widget->PlaceWidget();

    widget->On();

	interactor->Initialize();
    interactor->Start();

    return EXIT_SUCCESS;
}
