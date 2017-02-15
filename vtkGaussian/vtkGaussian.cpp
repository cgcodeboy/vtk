#include <vtkImageGaussianSmooth.h>
#include <vtkSmartPointer.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>

int main()
{
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName("001.jpg");
    reader->Update();

    vtkSmartPointer<vtkImageGaussianSmooth> gaussianSmooth = vtkSmartPointer<vtkImageGaussianSmooth>::New();
    gaussianSmooth->SetInputConnection(reader->GetOutputPort());
    gaussianSmooth->Update();

    vtkSmartPointer<vtkImageActor> originActor = vtkSmartPointer<vtkImageActor>::New();
    originActor->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkRenderer> originRender = vtkSmartPointer<vtkRenderer>::New();
    originRender->AddActor(originActor);
    originRender->SetBackground(0.8,0.8,0.8);
    originRender->SetViewport(0,0,0.5,1);

    vtkSmartPointer<vtkImageActor> gaussianSmoothActor = vtkSmartPointer<vtkImageActor>::New();
    gaussianSmoothActor->SetInputData(gaussianSmooth->GetOutput());

    vtkSmartPointer<vtkRenderer> gaussianSmoothRender = vtkSmartPointer<vtkRenderer>::New();
    gaussianSmoothRender->AddActor(gaussianSmoothActor);
    gaussianSmoothRender->SetBackground(0.7,0.7,0.7);
    gaussianSmoothRender->SetViewport(0.5,0,1,1);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->AddRenderer(originRender);
    window->AddRenderer(gaussianSmoothRender);
    window->SetSize(600,480);
    window->Render();

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    interactor->SetInteractorStyle(style);

    interactor->Start();

    return EXIT_SUCCESS;
}
