#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLookupTable.h>
#include <vtkPolyDataMapper.h>
#include <vtkCurvatures.h>
#include <vtkTextProperty.h>
#include <vtkScalarBarActor.h>
#include <vtkPolyDataReader.h>

int main()
{
    vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName("fran_cut.vtk");
    reader->Update();

    vtkSmartPointer<vtkCurvatures> curvature = vtkSmartPointer<vtkCurvatures>::New();
    curvature->SetInputData(reader->GetOutput());
    curvature->SetCurvatureTypeToMaximum();
    curvature->Update();

    vtkSmartPointer<vtkLookupTable> table = vtkSmartPointer<vtkLookupTable>::New();
    table->SetHueRange(0.0,0.5);
    table->SetAlphaRange(0.0,1.0);
    table->SetValueRange(1.0,1.0);
    table->SetRange(curvature->GetOutput()->GetScalarRange());
    table->Build();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(curvature->GetOutput());
    mapper->SetLookupTable(table);
    mapper->SetScalarRange(curvature->GetOutput()->GetScalarRange());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkTextProperty> textPro = vtkSmartPointer<vtkTextProperty>::New();
    textPro->SetFontSize(0.5);
    textPro->SetColor(0.5,1.0,1.0);

    vtkSmartPointer<vtkScalarBarActor> scalarActor = vtkSmartPointer<vtkScalarBarActor>::New();
    scalarActor->SetLookupTable(table);
    scalarActor->SetNumberOfLabels(10);
    scalarActor->SetLabelTextProperty(textPro);
    scalarActor->SetHeight(0.5);
    scalarActor->SetWidth(0.1);

    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
    render->SetBackground(0.7,0.7,0.7);
    render->AddActor(actor);
    render->AddActor(scalarActor);

    vtkSmartPointer<vtkRenderWindow> window = vtkSmartPointer<vtkRenderWindow>::New();
    window->SetSize(600,480);
    window->AddRenderer(render);
    window->Render();

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(window);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    interactor->SetInteractorStyle(style);
    interactor->Start();

    return EXIT_SUCCESS;
}
