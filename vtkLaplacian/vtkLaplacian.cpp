#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageActor.h>
#include <vtkJPEGReader.h>
#include <vtkImageLaplacian.h>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>
#include <iostream>

int main()
{
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName("001.jpg");
    reader->Update();

    vtkSmartPointer<vtkImageLaplacian> laplacian = vtkSmartPointer<vtkImageLaplacian>::New();
    laplacian->SetInputConnection(reader->GetOutputPort());
    laplacian->SetDimensionality(2);

    double range[2];
    laplacian->GetOutput()->GetScalarRange(range);
    std::cout<<range[0]<<" "<<range[1];

    vtkSmartPointer<vtkImageShiftScale> shiftscale = vtkSmartPointer<vtkImageShiftScale>::New();
    shiftscale->SetInputConnection(laplacian->GetOutputPort());
    shiftscale->SetOutputScalarTypeToUnsignedChar();
    shiftscale->SetScale(255/(range[1]-range[0]));
    shiftscale->SetShift(range[0]);
    shiftscale->Update();

    vtkSmartPointer<vtkImageActor> actor_1 = vtkSmartPointer<vtkImageActor>::New();
    actor_1->SetInputData(reader->GetOutput());

    vtkSmartPointer<vtkImageActor> actor_2 = vtkSmartPointer<vtkImageActor>::New();
    actor_2->SetInputData(shiftscale->GetOutput());

    vtkSmartPointer<vtkRenderer> render_1 = vtkSmartPointer<vtkRenderer>::New();
    render_1->AddActor(actor_1);
    render_1->SetBackground(0.8,0.7,0.8);
    render_1->SetViewport(0,0,0.5,1);

    vtkSmartPointer<vtkRenderer> render_2 = vtkSmartPointer<vtkRenderer>::New();
    render_2->AddActor(actor_2);
    render_2->SetBackground(0.8,0.7,0.8);
    render_2->SetViewport(0.5,0,1,1);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->AddRenderer(render_1);
    window->AddRenderer(render_2);
    window->Render();
    window->SetSize(600,480);

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    interactor->SetInteractorStyle(style);

    interactor->Start();

    return EXIT_SUCCESS;
}
