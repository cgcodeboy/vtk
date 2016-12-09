#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageActor.h>
#include <vtkImageCanvasSource2D.h>

int main()
{
    vtkSmartPointer<vtkImageCanvasSource2D> canvas1 = vtkSmartPointer<vtkImageCanvasSource2D>::New();
    canvas1->SetScalarTypeToUnsignedChar();
    canvas1->SetNumberOfScalarComponents(3);
    canvas1->SetExtent(0,100,0,100,0,0);
    canvas1->SetDrawColor(50,100,150);
    canvas1->FillBox(0,100,0,100);
    canvas1->SetDrawColor(150,200,250);
    canvas1->FillBox(20,60,20,60);
    canvas1->Update();

    vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
    actor->SetInputData(canvas1->GetOutput());

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render->AddActor(actor);
    render->SetBackground(0.7,0.7,0.7);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->SetSize(600,480);
    window->AddRenderer(render);
    window->Render();

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    interactor->SetInteractorStyle(style);

    interactor->Start();
    return EXIT_SUCCESS;
}
