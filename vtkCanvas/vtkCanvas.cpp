#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>

int main()
{
	vtkSmartPointer<vtkImageCanvasSource2D> canvas = vtkSmartPointer<vtkImageCanvasSource2D>::New();
	canvas->SetExtent(0, 100, 0, 100, 0, 100);
	canvas->SetScalarTypeToUnsignedChar();
	canvas->SetNumberOfScalarComponents(3);
	canvas->SetDrawColor(50, 100,150);
	canvas->FillBox(20, 80, 20, 80);
	canvas->Update();
	canvas->SetDrawColor(255, 150, 150);
	canvas->FillTriangle(0, 0, 20, 0, 0, 20);
	canvas->FillTriangle(80, 0, 100, 0, 100, 20);
	canvas->FillTriangle(100, 80, 100, 100, 80, 100);
	canvas->FillTriangle(0, 80, 20, 100, 0, 100);
	canvas->Update();


	vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
	actor->SetInputData(canvas->GetOutput());

	vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
	render->AddActor(actor);
	render->SetBackground(0.5, 0.6, 0.7);

	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	window->AddRenderer(render);
	window->SetSize(640, 480);
	window->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);
	
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	interactor->SetInteractorStyle(style);

	interactor->Start();
}