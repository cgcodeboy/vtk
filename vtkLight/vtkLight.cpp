#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkLight.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h> 
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main()
{
	vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
	cylinder->SetHeight(10);
	cylinder->SetRadius(2);
	cylinder->SetResolution(20);

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(cylinder->GetOutputPort());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
	render->AddActor(actor);
	render->SetBackground(0.7, 0.7, 0.7);

	vtkSmartPointer<vtkLight> light0 = vtkSmartPointer<vtkLight>::New();
	light0->SetPosition(0, 0,1);
	light0->SetColor(0.2, 0.5, 0.8);
	light0->SetFocalPoint(render->GetActiveCamera()->GetFocalPoint());
	render->AddLight(light0);

	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	window->SetSize(600, 480);
	window->SetPosition(50, 50);
	window->AddRenderer(render);
	window->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	interactor->SetInteractorStyle(style);
	interactor->Start();

	return EXIT_SUCCESS;
}