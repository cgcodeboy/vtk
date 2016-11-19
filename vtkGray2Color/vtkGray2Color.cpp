#include <vtkSmartPointer.h>
#include <vtkLookupTable.h>
#include <vtkBMPReader.h>
#include <vtkImageActor.h>
#include <vtkImageMapToColors.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>

int main()
{
	vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFileName("002.bmp");
	reader->Update();
	
	vtkSmartPointer<vtkLookupTable> table = vtkSmartPointer<vtkLookupTable>::New();
	table->SetHueRange(0.0, 0.5);
	table->SetRange(0, 255);
	table->SetValueRange(0.0, 1.0);
	table->Build();

	vtkSmartPointer<vtkImageMapToColors> m2c = vtkSmartPointer<vtkImageMapToColors>::New();
	m2c->SetInputConnection(reader->GetOutputPort());
	m2c->SetLookupTable(table);
	m2c->Update();

	vtkSmartPointer<vtkImageActor> actor1 = vtkSmartPointer<vtkImageActor>::New();
	actor1->SetInputData(m2c->GetOutput());

	vtkSmartPointer<vtkImageActor> actor2 = vtkSmartPointer<vtkImageActor>::New();
	actor2->SetInputData(reader->GetOutput());

	vtkSmartPointer<vtkRenderer> render1 = vtkSmartPointer<vtkRenderer>::New();
	render1->AddActor(actor1);
	render1->SetViewport(0, 0, 0.5, 1);
	render1->SetBackground(0.7, 0.7, 0.7);

	vtkSmartPointer<vtkRenderer> render2 = vtkSmartPointer<vtkRenderer>::New();
	render2->AddActor(actor2);
	render2->SetViewport(0.5, 0, 1, 1);
	render2->SetBackground(0.7, 0.7, 0.7);

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
}