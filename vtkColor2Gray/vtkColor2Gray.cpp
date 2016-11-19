#include <vtkSmartPointer.h>
#include <vtkJPEGReader.h>
#include <vtkPNGReader.h>
#include <vtkBMPReader.h>
#include <vtkBMPWriter.h>
#include <vtkImageActor.h>
#include <vtkImageLuminance.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>

int main()
{
	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName("test.jpg");
	reader->Update();

	vtkSmartPointer<vtkImageLuminance> luminance = vtkSmartPointer<vtkImageLuminance>::New();
	luminance->SetInputConnection(reader->GetOutputPort());
	luminance->Update();

	vtkSmartPointer<vtkBMPWriter> writer = vtkSmartPointer<vtkBMPWriter>::New();
	writer->SetFileName("002.bmp");
	writer->SetInputConnection(luminance->GetOutputPort());
	writer->Write();

	vtkSmartPointer<vtkImageActor> actor1 = vtkSmartPointer<vtkImageActor>::New();
	actor1->SetInputData(reader->GetOutput());

	vtkSmartPointer<vtkImageActor> actor2 = vtkSmartPointer<vtkImageActor>::New();
	actor2->SetInputData(luminance->GetOutput());

	vtkSmartPointer<vtkRenderer> render1 = vtkSmartPointer<vtkRenderer>::New();
	render1->AddActor(actor1);
	render1->SetBackground(0.7, 0.7, 0.7);
	render1->SetViewport(0, 0, 0.5, 1);

	vtkSmartPointer<vtkRenderer> render2 = vtkSmartPointer<vtkRenderer>::New();
	render2->AddActor(actor2);
	render2->SetBackground(0.5, 0.6, 0.7);
	render2->SetViewport(0.5, 0, 1, 1);

	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	window->AddRenderer(render1);
	window->AddRenderer(render2);
	window->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);

	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
	interactor->SetInteractorStyle(style);

	interactor->Start();
	return EXIT_SUCCESS;
}