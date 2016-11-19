#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include <vtkJPEGReader.h>
#include <vtkExtractVOI.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>

int main()
{
	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName("001.jpg");
	reader->Update();

	vtkSmartPointer<vtkExtractVOI> voi = vtkSmartPointer<vtkExtractVOI>::New();
	voi->SetInputConnection(reader->GetOutputPort());
	voi->SetVOI(100, 150, 100, 150, 0, 0);
	voi->Update();

	vtkSmartPointer<vtkImageActor> actor1 = vtkSmartPointer<vtkImageActor>::New();
	actor1->SetInputData(reader->GetOutput());
	
	vtkSmartPointer<vtkImageActor> actor2 = vtkSmartPointer<vtkImageActor>::New();
	actor2->SetInputData(voi->GetOutput());

	vtkSmartPointer<vtkRenderer>  render1 = vtkSmartPointer<vtkRenderer>::New();
	render1->AddActor(actor1);
	render1->SetViewport(0, 0, 0.5, 1);
	render1->SetBackground(0.7, 0.7, 0.7);

	vtkSmartPointer<vtkRenderer> render2 = vtkSmartPointer<vtkRenderer>::New();
	render2->AddActor(actor2);
	render2->SetBackground(0.7, 0.7, 0.7);
	render2->SetViewport(0.5, 0, 1, 1);

	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	window->AddRenderer(render1);
	window->AddRenderer(render2);
	window->SetSize(640, 480);
	window->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);

	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
	interactor->SetInteractorStyle(style);
	interactor->Start();

	return EXIT_SUCCESS;
}