#include <vtkSmartPointer.h>
#include <vtkPolydataReader.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include "MyVtkWindow.h"

int main()
{
    vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName("fran_cut.vtk");
    reader->Update();

    vtkSmartPointer<vtkSmoothPolyDataFilter> filter = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    filter->SetInputConnection(reader->GetOutputPort());
    filter->SetNumberOfIterations(100);
    filter->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(filter->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkPolyDataMapper> originMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    originMapper->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkActor> originActor = vtkSmartPointer<vtkActor>::New();
    originActor->SetMapper(mapper);

    MyVtkWindow *window = new MyVtkWindow;
    window->addActor(actor);
    window->addActor(originActor);
    window->startRenderWindow();

    return EXIT_SUCCESS;
}
