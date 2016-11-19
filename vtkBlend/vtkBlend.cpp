#include <vtkSmartPointer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkImageBlend.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkImageMapToColors.h>
#include <vtkLookupTable.h>
#include <vtkInteractorStyleImage.h>

int main()
{
	vtkSmartPointer<vtkJPEGReader> reader1 = vtkSmartPointer<vtkJPEGReader>::New();
	reader1->SetFileName("003.jpg");
	reader1->Update();

	vtkSmartPointer<vtkJPEGReader> reader2 = vtkSmartPointer<vtkJPEGReader>::New();
	reader2->SetFileName("004.jpg");
	reader2->Update();

	vtkSmartPointer<vtkImageBlend> blend = vtkSmartPointer<vtkImageBlend>::New();
	blend->AddInputConnection( reader1->GetOutputPort());
	blend->AddInputConnection(reader2->GetOutputPort());
	blend->SetOpacity(0, 0.6);
	blend->SetOpacity(1, 0.4);
	blend->Update();

	vtkSmartPointer<vtkImageActor> actor1 = vtkSmartPointer<vtkImageActor>::New();
	actor1->SetInputData(reader1->GetOutput());

	vtkSmartPointer<vtkImageActor> actor2 = vtkSmartPointer<vtkImageActor>::New();
	actor2->SetInputData(reader2->GetOutput());

	vtkSmartPointer<vtkImageActor> actor3 = vtkSmartPointer<vtkImageActor>::New();
	actor3->SetInputData(blend->GetOutput());

	vtkSmartPointer<vtkRenderer> render1 = vtkSmartPointer<vtkRenderer>::New();
	render1->AddActor(actor1);
	render1->SetViewport(0, 0, 0.5, 0.5);
	render1->SetBackground(0.5, 0.5, 0.5);

	vtkSmartPointer<vtkRenderer> render2 = vtkSmartPointer<vtkRenderer>::New();
	render2->AddActor(actor2);
	render2->SetViewport(0.5, 0, 1, 0.5);
	render2->SetBackground(0.4, 0.5, 0.6);

	vtkSmartPointer<vtkRenderer> render3 = vtkSmartPointer<vtkRenderer>::New();
	render3->AddActor(actor3);
	render3->ResetCamera();
	render3->SetViewport(0, 0.5, 1, 1);
	render3->SetBackground(0.6, 0.5, 0.4);

	vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
	window->SetSize(640, 480);
	window->AddRenderer(render1);
	window->AddRenderer(render2);
	window->AddRenderer(render3);
	window->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);

	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
	interactor->SetInteractorStyle(style);

	interactor->Start();

	return EXIT_SUCCESS;

	//vtkSmartPointer<vtkLookupTable> imgFirstColorMap =
	//	vtkSmartPointer<vtkLookupTable>::New(); // hot color map
	//imgFirstColorMap->SetRange(0.0, 255.0);
	//imgFirstColorMap->SetHueRange(0.0, 0.1);
	//imgFirstColorMap->SetValueRange(0.4, 0.8);
	//imgFirstColorMap->Build();

	//vtkSmartPointer<vtkLookupTable> imgSecondColorMap =
	//	vtkSmartPointer<vtkLookupTable>::New(); // cold color map
	//imgSecondColorMap->SetRange(0.0, 255.0);
	//imgSecondColorMap->SetHueRange(0.67, 0.68);
	//imgSecondColorMap->SetValueRange(0.4, 0.8);
	//imgSecondColorMap->Build();

	/*vtkSmartPointer<vtkJPEGReader> imgReader =
		vtkSmartPointer<vtkJPEGReader>::New();
	imgReader->SetFileName("003.jpg");

	vtkSmartPointer<vtkJPEGReader> imgReaderMoving =
		vtkSmartPointer<vtkJPEGReader>::New();
	imgReaderMoving->SetFileName("004.jpg");*/

	/*vtkSmartPointer<vtkImageMapToColors> firstColorMapper =
		vtkSmartPointer<vtkImageMapToColors>::New();
	firstColorMapper->SetInputConnection(imgReader->GetOutputPort());
	firstColorMapper->SetLookupTable(imgFirstColorMap);

	vtkSmartPointer<vtkImageMapToColors> secondColorMapper =
		vtkSmartPointer<vtkImageMapToColors>::New();
	secondColorMapper->SetInputConnection(imgReaderMoving->GetOutputPort());
	secondColorMapper->SetLookupTable(imgSecondColorMap);*/

	/*vtkSmartPointer<vtkImageBlend> imgBlender =
		vtkSmartPointer<vtkImageBlend>::New();
	imgBlender->SetOpacity(0, 0.5);
	imgBlender->SetOpacity(1, 0.5);
	imgBlender->AddInputConnection(imgReader->GetOutputPort());
	imgBlender->AddInputConnection(imgReaderMoving->GetOutputPort());

	vtkSmartPointer<vtkDataSetMapper> imgDataSetMapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	imgDataSetMapper->SetInputConnection(imgBlender->GetOutputPort());

	vtkSmartPointer<vtkActor> imgActor =
		vtkSmartPointer<vtkActor>::New();
	imgActor->SetMapper(imgDataSetMapper);

	vtkSmartPointer<vtkRenderer> imgRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	imgRenderer->AddActor(imgActor);

	vtkSmartPointer<vtkRenderWindow> imgRenderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	imgRenderWindow->AddRenderer(imgRenderer);

	vtkSmartPointer<vtkRenderWindowInteractor> imgInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imgInteractor->SetRenderWindow(imgRenderWindow);
	imgInteractor->Initialize();
	imgInteractor->Start();

	return EXIT_SUCCESS;*/
}