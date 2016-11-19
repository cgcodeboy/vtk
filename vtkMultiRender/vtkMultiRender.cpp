#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>

int main()
{
	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	for (int i = 0; i < 4; i++)
	{
		vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
		sphere->SetRadius(2);
		sphere->SetThetaResolution(5+5*i);

		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(sphere->GetOutputPort());

		vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);
		actor->GetProperty()->SetColor(double(i + 1) / 5, double(i + 1) / 10, double(i + 1) / 15);

		vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
		render->AddActor(actor);
		render->SetBackground(double(i + 1) / 4, double(i + 1) / 4, double(i + 1) / 4);
		render->SetViewport(0.5*(i % 2), i>1 ? 0 : 0.5, 0.5 + 0.5*(i % 2), 0.5 + (i>1 ? 0 : 0.5));
		window->AddRenderer(render);
	}

	window->SetSize(640, 480);
	window->SetPosition(50, 50);
	window->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	interactor->SetInteractorStyle(style);

	interactor->Start();
}